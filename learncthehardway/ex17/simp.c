#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

struct Address {
    int id;
    int set;
    char *name;
    char *email;
};

struct Database {
    struct Address *rows;
};

void Address_print(struct Address *addr) {
    printf("{id: %d, set: %d, name: %s, email: %s} at %p\n", 
            addr->id,
            addr->set,
            addr->name,
            addr->email,
            addr);
}

int main() {
    int max_rows = 10;
    int max_data = 10;

    printf("bananas\n");
    
    struct Database *db = malloc(sizeof(struct Database));
    db->rows = malloc(sizeof(struct Address) * max_rows);
    
    for (int i = 0; i < max_rows; i++) {
        struct Address addr = {.id=i, .set=1};
        addr.name = malloc(max_data);
        addr.email = malloc(max_data);
        db->rows[i] = addr;
    }
    
    struct Address *addr = &db->rows[2];
    strncpy(addr->name, "Bananas", max_data);

    for (int i = 0; i < max_rows; i++) {
        Address_print(&db->rows[i]);
    }
    

    for (int i = 0; i < max_rows; i++) {
        free(db->rows[i].name);
        free(db->rows[i].email);
    }
    free(db->rows);
    free(db);

    return 0;
}
