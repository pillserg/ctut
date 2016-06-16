#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


#define MAX_DATA 512
#define MAX_ROWS 100

struct Address {
    int id;
    int set;
    char name[MAX_DATA];
    char email[MAX_DATA];
};

struct Database {
    struct Address rows[MAX_ROWS];
};

typedef struct {
    FILE *file;
    struct Database *db;
} Connection;

void Database_close(Connection *conn);

void die(Connection *conn, const char *message) {
    if (errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }
    Database_close(conn);
    exit(1);
}


void Address_print(struct Address *addres) {
    printf("%d %s %s\n",
            addres->id,
            addres->name,
            addres->email);
}


void Database_load(Connection *conn) {
    size_t nmemb = 1;
    size_t block_size = sizeof(struct Database);
    
    // Read to *conn->db block_size nmemb times from *conn->file
    int rc = fread(conn->db, block_size, nmemb, conn->file);
    // rc is set too number of blocks read in our case it should be one
    if (rc != 1) {
        die(conn, "Failed to load database.");
    }
}


Connection *Database_open(const char *filename, char mode) {
    // allocate mem for Connection
    // also looks like we don't need this allocation in create mod
    // but whatever
    Connection *conn = malloc(sizeof(Connection));
    if (!conn) die(conn, "Memory error");
    
    // allocate mem for Database 
    // [all nested structs are sized thus everything should play out nicely]
    conn->db = malloc(sizeof(struct Database));
    if (!conn->db) die(conn, "Memory error");
    
    // create file if needed
    if (mode == 'c') {
        conn->file = fopen(filename, "w");
    // else open it for reading, i hope some analog of os.path are
    // provided by stdlib
    } else {
        conn->file = fopen(filename, "r+");
        // read db file in our preallocated memory
        if (conn->file) {
            Database_load(conn);
        } 
    }
    
    if (!conn->file) die(conn, "Failed to open the file");

    return conn;
}


void Database_close(Connection *conn) {
    printf("DEBUG: clearing out\n");
    if (conn) {
        // close file stream
        if (conn->file) fclose(conn->file);
        // free db memory
        if (conn->db) free(conn->db);
        // free connection memory
        free(conn);
    }
}

void Database_write(Connection *conn) {
    // set position indicator to beginning of file
    rewind(conn->file);
    // write our database to file
    // args are same as in fread
    int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
    if (rc != 1) die(conn, "Failed to write database.");
    
    // flush data to disk
    rc = fflush(conn->file);
    if (rc == -1) die(conn, "Cannot flush database.");
}


void Database_create(Connection *conn) {
    // put 0 addresses into preallocated db memory
    for (int i = 0; i < MAX_ROWS; i++) {
        // make a prototype to initialize it
        struct Address addr = {.id = i, .set = 0};
        // then just assign it
        conn->db->rows[i] = addr;
    }
}


void Database_set(Connection *conn, int id, const char *name, const char *email) {
    // get pointer to Addres by id
    // id is just an offset in db/rows as we can see
    struct Address *addr = &conn->db->rows[id];

    if (addr->set) die(conn, "Already set, delete it first");
    // mark addr as set, C11 True, False should look nicer...
    addr->set = 1;

    // WARNING: bug, read "how to break it" and fix it
    // ... with very long name it could fail (name wouldn't be terminated with \0
    // ... but other than this, can't see it yet
    //
    // Hey, i actually got it right :)
    char *res = strncpy(addr->name, name, MAX_DATA);
    // demo strncpy bug
    if (!res) die(conn, "Name copy failed");
    // strncopy wouldn't terminate strings > MAX_DATA
    addr->name[MAX_DATA] = '\0';

    res = strncpy(addr->email, email, MAX_DATA);
    if (!res) die(conn, "Email copy failed");
    addr->email[MAX_DATA] = '\0';
}


void Database_get(Connection *conn, int id) {
    // just get pointer to addr
    struct Address *addr = &conn->db->rows[id];
    // and print it if it's set
    if(addr->set) {
        Address_print(addr);
    } else {
        die(conn, "ID not set");
    }
}


void Database_delete(Connection *conn, int id) {
    // replace addr with 0 addr
    struct Address addr = {.id = id, .set = 0};
    conn->db->rows[id] = addr;
}


void Database_list(Connection *conn) {
    for (int i = 0; i < MAX_ROWS; i++) {
        struct Address *cur = &conn->db->rows[i];
        if (cur->set) {
            Address_print(cur);
        }
    }
}


int main(int argc, char *argv[]) {
    // die if no dbname
    if (argc < 3) {
        die(0, "USAGE: ex17 <dbfile> <action> [action params]\n");
    }
    
    // get filename string
    // and action char (chars are good for case :))
    char *filename = argv[1];
    char action = argv[2][0];
    // open connection to db file
    Connection *conn = Database_open(filename, action);

    int id = 0;
    // parse id
    if (argc > 3) id = atoi(argv[3]);
    if (id >= MAX_ROWS) die(conn, "There's not that many records\n");
    
    switch (action) {
        case 'c':
            Database_create(conn);
            Database_write(conn);
            break;

        case 'g':
            if (argc != 4) die(conn, "Need an id to get");

            Database_get(conn, id);
            break;

        case 's':
            if (argc != 6) die(conn, "Need id, name, email to set");
            Database_set(conn, id, argv[4], argv[5]);
            Database_write(conn);
            break;

        case 'd':
            if (argc != 4) die(conn, "Need and id to delete");
            Database_delete(conn, id);
            Database_write(conn);
            break;

        case 'l':
            Database_list(conn);
            break;

        default:
            die(conn, "Invalid action only: c=create, g=get, s=set, d=delete action are supported");
    }

    // cleanup
    Database_close(conn);

    return 0;
}
