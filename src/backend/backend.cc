#include "../../include/backend/backend.h"

using namespace std;

map<string, int> type_code = {{"int", 0}, {"string", 1}, {"float", 2}};

// Dummy Implementation unless otherwise specified


/* Database Class */
Database::Database(string db_name) {
    this->db_name = db_name;
    this->relations_size = 0;
}

Database::~Database() {

}


string Database::create() {
    return string("create");
}


string Database::open() {
    return "open";
}

string Database::print_table(Relation *relation_name, vector<string> col_names, vector<vector<string>> rows) {
    stringstream  seperator;
    stringstream  table_headings;
    stringstream  data;
    stringstream  table;
    
    const int atrribute_width = 10;
    
    vector<string>::iterator cols;
    
    // cols = (*relation)->get_col_names().begin();
    
    cols = col_names.begin();
    
    for(cols = col_names.begin(); cols != col_names.end(); cols++) {
        seperator << setfill('-') << setw(1) << "+" << setw(atrribute_width) << "-";
    }
    seperator << setw(1) << "+" << endl << setfill(' ') << setw(1);
    
    table << seperator.str();
    
    for(cols = col_names.begin(); cols != col_names.end(); cols++) {
        table_headings << "|" << setw(atrribute_width) << left << (*cols) << setw(1) ;
    }
    
    table_headings << setw(1) << "|" << endl;
    
    table << table_headings.str();
    table << seperator.str();
    
    // Do not delete for now
    // cout << setfill('-') << setw(1) << "+" << setw(15) << "-" << setw(1) << "+" << setw(15) << "-" << setw(1) << "+" << setw(5) << "-" << setw(1) << "+" << endl;
    // cout << setfill(' ') << setw(1) << "|" << setw(15) << left << "First Name" << setw(1) << "|" << setw(15) << left << "Last Name" << setw(1) << "|"  << setw(5) << left << "Age" << setw(1) << "|" << endl;
    // cout << (*(*relation)->get_rows().begin()[1]->get_row().begin());
    
    for(int j = 0; j < rows.size(); j++) {
        for(int k = 0; k < rows[j].size(); k++)
            table << "|" << setw(atrribute_width) << left << rows[j][k] << setw(1) ;
        table << setw(1) << "|" << endl << seperator.str();
    }
    
    return table.str();
}

string Database::create_table(string relation_name, vector <string> data_types, vector<string> col_names) {
    
    // Checking if table name exists
    vector<Relation*>::iterator i = get_table(relation_name);
    if(i != relations.end())
        return "Backend Error: Table already exists";
    
    // Else create
    map <string, string> schema;
    transform( col_names.begin(), col_names.end(), data_types.begin(), inserter(schema, schema.end()),[](string a, string b) {
        return make_pair(a, b);
    });
       
    Relation *r = new Relation(relation_name, schema, col_names);
    this->relations.push_back(r);
    this->relations_size++;
    return "Table created";
}

string Database::insert(string relation_name, vector<string> data_items) {
    
    // Check if relation existis
    vector<Relation*>::iterator relation = get_table(relation_name);
    
    if(relation == relations.end())
        return "Backend error: Table does not exisit";
    
    // Check if schema is followed
    if(data_items.size() > (*relation)->get_schema().size()) {
        return "Backend Error: Too many attributes given";
    }
    
    if(data_items.size() < (*relation)->get_schema().size()) {
        return "Backend Error: Too few attributes given";
    }
    
    for(int i = 0; i < data_items.size(); i++) {
        
        switch(type_code[(*relation)->get_schema()[(*relation)->get_col_names()[i]]]) {
            case 0: {
                char* leftover;
                long val = strtol(data_items[i].c_str(), &leftover, 0);
                if(*leftover != '\0')
                    return "Backend error: Invalid integer format";
                break;
            }
            case 1: { // To be filled later 
                break;
            }
            case 2: {
                char* endptr = 0;
                strtod(data_items[i].c_str(), &endptr);
                if(*endptr != '\0' || endptr == data_items[i].c_str())
                    return "Backend error: Invalid float format";
                break;
            }
        }
    }
    
    // Entry *e = new Entry(data_items);
    (*relation)->insert_row(data_items);
    (*relation)->increment_row_size();
    return "Row inserted";
}

string Database::select(string relation_name) {
    vector<Relation*>::iterator relation = get_table(relation_name);
    
    if(relation == relations.end())
        return "Backend error: Table does not exisit";
    
    vector<Entry*> row = (*relation)->get_rows();
    vector<vector<string>> rows;
    
    for(int j = 0; j < row.size(); j++) {
        vector<string> col_entries;
        for(int k = 0; k < row[j]->get_row().size(); k++)
            col_entries.push_back(row[j]->get_row()[k]);
        rows.push_back(col_entries);
    }
    
    return print_table((*relation), (*relation)->get_col_names(), rows);
    
}

string Database::select(
    string relation_name,
    string where_column_name,
    string where_data_item) {
    
    vector<Relation*>::iterator relation = get_table(relation_name);
    
    if(relation == relations.end())
        return "Backend error: Table does not exist";
    
    if ( (*relation)->get_schema().count(where_column_name) == 0 ) {
        return "Backend error: Column does not exist";
    }
    
    return select(relation_name, where_column_name, where_data_item, (*relation)->get_col_names());
}

string Database::select(string relation_name, vector<string> column_names) {
    
    vector<Relation*>::iterator relation = get_table(relation_name);
    
    if(relation == relations.end())
        return "Backend error: Table does not exist";
    
    vector<string>::iterator where_column_name;
    for(where_column_name = column_names.begin(); where_column_name != column_names.end(); where_column_name++) {
        if ( (*relation)->get_schema().count((*where_column_name)) == 0 ) {
            return "Backend error: Column '" + (*where_column_name) + "' does not exist";
        }
    }
    
    vector<Entry*> row = (*relation)->get_rows();
    vector<string> col_names = (*relation)->get_col_names();
    vector<Entry*> select_rows;
    vector<vector<string>> rows;
    
    for(int j = 0; j < row.size(); j++) {
        vector<string> col_entries;
        for(int k = 0; k < column_names.size(); k++) {
            ptrdiff_t pos = find(col_names.begin(), col_names.end(), column_names[k]) - col_names.begin();
            col_entries.push_back(row[j]->get_row()[pos]);
        }
        rows.push_back(col_entries);    
    }
    
    return print_table((*relation), column_names, rows);
}

string Database::select(
    string relation_name,
    string where_column_name,
    string where_data_item,
    vector<string> column_names) {
        
    vector<Relation*>::iterator relation = get_table(relation_name);
    
    if(relation == relations.end())
        return "Backend error: Table does not exist";
    
    if ( (*relation)->get_schema().count(where_column_name) == 0 ) {
        return "Backend error: Column does not exist";
    }
    
    vector<Entry*> row = (*relation)->get_rows();
    vector<string> col_names = (*relation)->get_col_names();
    vector<Entry*> select_rows;
    
    ptrdiff_t pos = find(col_names.begin(), col_names.end(), where_column_name) - col_names.begin();
    
    vector<vector<string>> rows;
    
    for(int j = 0; j < row.size(); j++) {
        vector<string> col_entries;
        if(!row[j]->get_row()[pos].compare(where_data_item)) {
            for(int k = 0; k < column_names.size(); k++) {
                ptrdiff_t pos_item = find(col_names.begin(), col_names.end(), column_names[k]) - col_names.begin();
                col_entries.push_back(row[j]->get_row()[pos_item]);
            }
            rows.push_back(col_entries);
        }
    }
    
    return print_table((*relation), column_names, rows);
    
}

string Database::update(
    string relation_name,
    string column_name,
    string data_item,
    string where_column_name,
    string where_data_item) {
    
    int change_count = 0;
    
    vector<Relation*>::iterator relation = get_table(relation_name);
    
    if(relation == relations.end())
        return "Backend error: Table does not exist";
    
    if ( (*relation)->get_schema().count(where_column_name) == 0 ) {
        return "Backend error: Invalid column name '" + where_column_name + "' in where clause";
    }
    
    if ( (*relation)->get_schema().count(column_name) == 0 ) {
        return "Backend error: Invalid column name '" + column_name + "' in set clause";
    }
    
    vector<Entry*> row = (*relation)->get_rows();
    vector<string> col_names = (*relation)->get_col_names();
    
    ptrdiff_t pos_where = find(col_names.begin(), col_names.end(), where_column_name) - col_names.begin();
    ptrdiff_t pos_set = find(col_names.begin(), col_names.end(), column_name) - col_names.begin();
    
    for(int j = 0; j < row.size(); j++) {
        if(!row[j]->get_row()[pos_where].compare(where_data_item)) {
            row[j]->update_row(pos_set, data_item);
            change_count++;
        }
    }
    return "Updated " + to_string(change_count) + " row(s)";
}


string Database::remove(string relation_name) {
    
    vector<Relation*>::iterator relation = get_table(relation_name);
    
    if(relation == relations.end())
        return "Backend error: Table does not exist";
    
    int count = (*relation)->clear_entries();
    
    return "Deleted " + to_string(count) + " row(s)";
}

string Database::remove(
    string relation_name,
    string where_column_name,
    string where_data_item) {
    return "remove 2";
}

string Database::drop_table(string relation_name) {
    return "drop_table";
}

string Database::drop() {
    return "drop database";
}

string Database::start() {
    return "start";
}

string Database::commit() {
    return "commit";
}

string Database::rollback() {
    return "rollback";
}

string Database::close() {
    return "close";
}

/* Relation Class */

Relation::Relation() {
    
    // this->relation_name = "";
    // this->data_rows = new Entry();
    
}

Relation::~Relation() {
    
}

Relation::Relation(string relation_name, map<string, string> schema, vector<string> col_names) {
    this->relation_name = relation_name;
    this->schema = schema;
    this->col_names = col_names;
}

vector<Relation*>::iterator Database::get_table(string relation_name) {
    vector<Relation*>::iterator relation;
    for(relation = relations.begin(); relation != relations.end(); relation++) {
        if(!(*relation)->get_name().compare(relation_name))
            break;
    }
    
    return relation;
}

void Relation::insert_row(vector<string> data_items) {
    Entry *e = new Entry(data_items);
    this->data_rows.push_back(e);
}

int Relation::clear_entries() { 
    data_rows.clear();
    int row_size = get_row_size();
    reset_row_size();
    return row_size;
}

/* Entry Class */

Entry::Entry() {
    
}

Entry::Entry(vector<string> row) {
    this->row = row;
}

Entry::~Entry() {
    
}