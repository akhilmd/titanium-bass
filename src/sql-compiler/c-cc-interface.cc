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

const char* database_select1(void** db, char* table_name, char** col_names, int noc) {
     Database* new_db = reinterpret_cast<Database*>(*db);
    if (new_db == NULL) {
        return (new string("ERROR: Please connect to a database first!"))->c_str();
    }
    // new_db->insert(string(table_name),{"Harsh","45"});
    // new_db->insert(string(table_name),{"Harsh","45"});
    // new_db->insert(string(table_name),{"Harsh","45"});
    // new_db->insert(string(table_name),{"Harsh","45"});

    vector<string> v_col_names;
    int i = 0;
    for (i=0;i<noc;++i) {
        v_col_names.push_back(string(col_names[i]));
    }

    string* ret_val = new string (
        new_db->select(
            string(table_name),
            v_col_names
        )
    );
    return ret_val->c_str();
}

const char* database_select2(void** db, char* table_name, char* where_column, char* where_item) {
    Database* new_db = reinterpret_cast<Database*>(*db);
    if (new_db == NULL) {
        return (new string("ERROR: Please connect to a database first!"))->c_str();
    }
    string* ret_val = new string (
        new_db->select(
            string(table_name),
            string(where_column),
            string(where_item)
        )
    );
    return ret_val->c_str();
}


const char* database_insert(void** db, char* table_name, char** data_item_list, int nodi) {
    Database* new_db = reinterpret_cast<Database*>(*db);
    if (new_db == NULL) {
        return (new string("ERROR: Please connect to a database first!"))->c_str();
    }
    vector<string> v_col_names;
    int i = 0;
    for (i=nodi-1;i>=0;--i) {
        v_col_names.push_back(string(data_item_list[i]));
    }

    string* ret_val = new string (
        new_db->insert(
            string(table_name),
            v_col_names
        )
    );
    return ret_val->c_str();
}

const char* database_update(void** db, char* table_name, char* col_nam, char* d_item, char* where_column, char* where_item) {
    Database* new_db = reinterpret_cast<Database*>(*db);
    if (new_db == NULL) {
        return (new string("ERROR: Please connect to a database first!"))->c_str();
    }

    string* ret_val = new string (
        new_db->update (
            string(table_name),
            string(col_nam),
            string(d_item),
            string(where_column),
            string(where_item)
        )
    );

    return ret_val->c_str();
}

const char* database_delete(void** db, char* table_name){
    Database* new_db = reinterpret_cast<Database*>(*db);
    if (new_db == NULL) {
        return (new string("ERROR: Please connect to a database first!"))->c_str();
    }
    string* ret_val = new string (
        new_db->delete_rows (
            string(table_name)
        )
    );
}

const char* database_delete1(void** db, char* table_name, char* where_column, char* where_item){
    Database* new_db = reinterpret_cast<Database*>(*db);
    if (new_db == NULL) {
        return (new string("ERROR: Please connect to a database first!"))->c_str();
    }
    string* ret_val = new string (
        new_db->delete_rows (
            string(table_name),
            string(where_column),
            string(where_item)
        )
    );
}

const char* database_table_drop(void** db, char* table_name){
    Database* new_db = reinterpret_cast<Database*>(*db);
    if (new_db == NULL) {
        return (new string("ERROR: Please connect to a database first!"))->c_str();
    }
    string* ret_val = new string (
        new_db->drop_table (
            string(table_name)
            )
        );
}

const char* database_drop(void** db, char* database_name){
    Database* new_db = reinterpret_cast<Database*>(*db);
    if (new_db == NULL) {
        return (new string("ERROR: Please connect to a database first!"))->c_str();
    }
    string* ret_val = new string (new_db->drop ());
}

const char* database_start_transaction(void** db){
    Database* new_db = reinterpret_cast<Database*>(*db);
    if (new_db == NULL) {
        return (new string("ERROR: Please connect to a database first!"))->c_str();
    }
    string* ret_val = new string (new_db->start ());
}

const char* database_commit_transaction(void** db){
    Database* new_db = reinterpret_cast<Database*>(*db);
    if (new_db == NULL) {
        return (new string("ERROR: Please connect to a database first!"))->c_str();
    }
    string* ret_val = new string (new_db->commit ());
}

const char* database_rollback_transaction(void** db){
    Database* new_db = reinterpret_cast<Database*>(*db);
    if (new_db == NULL) {
        return (new string("ERROR: Please connect to a database first!"))->c_str();
    }
    string* ret_val = new string (new_db->rollback ());
}