#include <stdio.h>
#include <string>

#include "../../include/sql-compiler/c-cc-interface.h"
#include "../../include/backend/backend.h"

using namespace std;

void* backend_init() {
    printf("Project Titanium-Bass\n");
    Database* db = NULL;

    return reinterpret_cast<void*>(db); 
}

const char* database_create(void* db, char* db_name) {
    Database* new_db = new Database(string(db_name));
    string* ret_val = new string(new_db->create());

    return ret_val->c_str();
}

const char* database_use(void** db, char* db_name) {
    Database* new_db = reinterpret_cast<Database*>(*db);
    if (new_db == NULL) {
        new_db = new Database(string(db_name));
    }

    string* ret_val = new string(new_db->connect());

    *db = reinterpret_cast<void*>(new_db);

    return ret_val->c_str();
}

const char* database_close(void** db, char* db_name) {
    Database* new_db = reinterpret_cast<Database*>(*db);
    if (new_db == NULL) {
        new_db = new Database(string(db_name));
    }

    if (string(db_name) != new_db->get_db_name()) {
        return (new string(string("ERROR: Not connected to ") +string(db_name)))->c_str();
    }

    string* ret_val = new string(new_db->close());
    *db = NULL;

    return ret_val->c_str();
}

const char* database_create_table(void** db, char* table_name, char** col_names, char** col_dts, int noc) {
    int i = 0;

    printf("%s\n", table_name);

    for (i=0;i<noc;++i) {
        printf("%s : %s\n", col_names[i], col_dts[i]);
    }
    return "okkda";
}