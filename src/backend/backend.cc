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
	return "create";
}


string Database::open() {
	return "open";
}

string Database::create_table(string relation_name, map<string, string> schema, vector<string> col_names) {
	
	// Checking if table name exists
	vector<Relation*>::iterator i = get_table(relation_name);
	if(i != relations.end())
		return "Backend Error: Table already exists";
	
	// Else create
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
	
	// will try to make each as function calls
	stringstream  seperator;
	stringstream  table_headings;
	stringstream  data;
	stringstream  table;
	
	
	const char separator = ' ';
	const int atrribute_width = 10;
    
	vector<string>::iterator cols;
	
	// cols = (*relation)->get_col_names().begin();
	
	vector<string> col_names = (*relation)->get_col_names();
	
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
	
	
	vector<Entry*> row = (*relation)->get_rows();
	
	for(int j = 0; j < row.size(); j++) {
		for(int k = 0; k < row[j]->get_row().size(); k++)
			table << "|" << setw(atrribute_width) << left << row[j]->get_row()[k] << setw(1) ;
		table << setw(1) << "|" << endl << seperator.str();
	}
	
	return table.str();
}

string Database::select(
    string relation_name,
    string where_column_name,
    string where_data_item) {
	return "select 2";
}

string Database::select(string relation_name, vector<string> column_names) {
	return "select 3";
}

string Database::select(
    string relation_name,
    string where_column_name,
    string where_data_item,
    vector<string> column_names) {
	return "select 4";
}

string Database::update(
    string relation_name,
    string column_name,
    string data_item,
    string where_column_name,
    string where_data_item) {
	return "update";
}


string Database::remove(string relation_name) {
	return "remove 1";
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

/* Entry Class */

Entry::Entry() {
	
}

Entry::Entry(vector<string> row) {
	this->row = row;
}

Entry::~Entry() {
	
}