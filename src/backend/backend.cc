#include "../../include/backend/backend.h"
#include <boost/filesystem.hpp>
#include <sys/file.h>
#include <stdio.h>

#include <fstream>

// include headers that implement a archive in simple text format
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

using namespace std;
namespace fs = boost::filesystem;
map<string, int> type_code = {{"int", 0}, {"string", 1}, {"float", 2}};


/* Database Class */
Database::Database(string db_name) {
    this->db_name = db_name;
    this->relations_size = 0;
    this->is_open = false;
    fs::path full_path( fs::current_path() );
    this->cwd = string(full_path.c_str());
}

Database::~Database() {

}


string Database::create() {
    string message = string("Current Working Directory: ") + this->cwd + string("\n");
    if (fs::create_directories(this->db_name)) {
        write_to_file();
        return message+string("Database Created");
    } else {
        return message+string("Database may already exist");
    }
}


string Database::connect() {
    // if connected to a db, close it first
    // cout << this->is_open << endl;
    if (this->is_open) {
        return string("ERROR: Please disconnect first!");
    }
    // check if db folder exists
    string db_path = this->cwd+"/"+this->db_name;
    if (fs::exists(db_path) && fs::is_directory(db_path)) {
        int fd = open((db_path + string("/lockfile")).c_str(), O_RDWR | O_CREAT, 0666);
        // lock db folder to this instance
        int rc =  flock(fd, LOCK_EX | LOCK_NB);
        if (rc) {
            return string("ERROR: Database connected to different process!");
        } else {
            this->is_open = true;
            return string("Connected to ")+db_name;
        }
    } else {
        return string("ERROR: database not created!");
    }
}

string Database::close() {
    if (!this->is_open) {
        return string("ERROR: Not connected to any database!");
    }
    string db_path = this->cwd+"/"+this->db_name;
    // int fd = open((db_path + string("/lockfile")).c_str(), O_CREAT);
    remove((db_path + string("/lockfile")).c_str());
    if (1) {
        this->is_open = false;
        return string("Disconnected from ") + this->db_name;
    } else {
        return string("ERROR: [unknown] Database.close failed!");
    }
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

void Database::set_relations(vector<Relation*> r) {
    this->relations = r;
}

vector<Relation*> Database::get_relations() {
    return this->relations;
}

void Database::set_relations_size(int s) {
    this->relations_size = s;
}

void Database::write_to_file() {
    ofstream ofs(cwd+"/"+db_name+"/"+"datafile");

    boost::archive::text_oarchive oa(ofs);
    oa << *this;
}

Database* Database::read_from_file () {
    Database newg;

    std::ifstream ifs(cwd+"/"+db_name+"/"+"datafile");
    boost::archive::text_iarchive ia(ifs);
    ia >> newg;

    Database* nn = new Database(newg.get_db_name());
    nn->set_relations(newg.get_relations());
    nn->set_relations_size(newg.get_relations().size());

    return nn;
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
    
    write_to_file();
    
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
    
    write_to_file();
    
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
    
    write_to_file();
    
    return "Updated " + to_string(change_count) + " row(s)";
}


string Database::delete_rows(string relation_name) {
    
    vector<Relation*>::iterator relation = get_table(relation_name);
    
    if(relation == relations.end())
        return "Backend error: Table does not exist";
    
    int count = (*relation)->clear_entries();
    
    write_to_file();
    
    return "Deleted " + to_string(count) + " row(s)";
}

string Database::delete_rows(
    string relation_name,
    string where_column_name,
    string where_data_item) {
    vector<Relation*>::iterator relation = get_table(relation_name);
    
    if(relation == relations.end())
        return "Backend error: Table does not exist";
    
    if ( (*relation)->get_schema().count(where_column_name) == 0 ) {
        return "Backend error: Invalid column name '" + where_column_name + "' in where clause";
    }
    
    vector<Entry*> row = (*relation)->get_rows();
    vector<string> col_names = (*relation)->get_col_names();
    vector<Entry*> select_rows;
    
    ptrdiff_t pos = find(col_names.begin(), col_names.end(), where_column_name) - col_names.begin();
    
    vector<vector<string>> rows;
    vector<int> del_indexs;
    
    for(int j = 0; j < row.size(); j++) {
        if(!row[j]->get_row()[pos].compare(where_data_item)) {
            // (*relation)->pop_row(j);
            del_indexs.push_back(j);
        }
    }
    
    if(!del_indexs.size()) {
        return "Backend error: Invalid data item '" + where_data_item + "'";
    }
    
    
    vector<int>::reverse_iterator del_it = del_indexs.rbegin();
    
    for(; del_it != del_indexs.rend(); del_it++)
        (*relation)->pop_row((*del_it));
    
    write_to_file();

    return "Deleted " + to_string(del_indexs.size()) + " row(s)";
}

string Database::drop_table(string relation_name) {
    
    vector<Relation*>::iterator relation = get_table(relation_name);
    
    if(relation == relations.end())
        return "Backend error: Table does not exist";
    
    string del_relation_name = (*relation)->get_name();
    
    delete_rows(del_relation_name);
    
    ptrdiff_t pos = find(relations.begin(), relations.end(), (*relation)) - relations.begin();
    
    delete relations[pos];
    relations.erase(relations.begin() + pos);
    
    write_to_file();

    return "Dropped relation '" + del_relation_name + "' ";
}

string Database::drop() {
    fs::remove_all(cwd+"/"+db_name);
    return "drop database";
}

string Database::start() {
    return "tbd: start";
}

string Database::commit() {
    return "tbd: commit";
}

string Database::rollback() {
    return "tbd: rollback";
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

int Relation::check_data_type(int col_num, string data_item) {
    switch(type_code[this->schema[this->col_names[col_num]]]) {
        case 0: {
            char* leftover;
            long val = strtol(data_item.c_str(), &leftover, 0);
            if(*leftover != '\0')
                return 1;
            break;
        }
        case 1: { // To be filled later 
            break;
        }
        case 2: {
            char* endptr = 0;
            strtod(data_item.c_str(), &endptr);
            if(*endptr != '\0' || endptr == data_item.c_str())
                return 3;
            break;
        }
    }
    
    return 0;
}


/* Entry Class */

Entry::Entry() {
    
}

Entry::Entry(vector<string> row) {
    this->row = row;
}

Entry::~Entry() {
    
}
