#include <stdio.h>
#include <string>
#include <vector>

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
    Database* new_db = reinterpret_cast<Database*>(*db);
    if (new_db == NULL) {
        return (new string("ERROR: Please connect to a database first!"))->c_str();
    }

    vector<string> v_col_names;
    vector<string> v_col_dts;

    // database exists

    int i = 0;
    for (i=0;i<noc;++i) {
        v_col_names.push_back(string(col_names[i]));
        v_col_dts.push_back(string(col_dts[i]));
    }
    string* ret_val = new string (
        new_db->create_table (
            string(table_name),
            v_col_dts,
            v_col_names
        )
    );
    return ret_val->c_str();
}

const char* database_select(void** db, char* table_name) {
    Database* new_db = reinterpret_cast<Database*>(*db);
    if (new_db == NULL) {
            return (new string("ERROR: Please connect to a database first!"))->c_str();
    }
    // vector<string> v_col_names;
    // char* colnames1 = "Harsh";
    // char** colnames = &colnames1;
    // int i = 0;
    // for (i=0;i<1;++i) {
    //      v_col_names.push_back(string(colnames[i]));
    //  }
    //  new_db->insert(string(table_name),v_col_names);
    string* ret_val = new string(new_db->select(string(table_name)));
    return ret_val->c_str();
}
