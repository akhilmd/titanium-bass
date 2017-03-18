#include "../../include/backend/backend.h"

using namespace std;

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

string Database::create_table (string relation_name, map<string, string> schema) {
	
	// Checking if table name exists
	vector<Relation*>::iterator i;
	for(i = relations.begin(); i != relations.end(); i++) {
		if(!(*i)->getName().compare(relation_name))
			return "Error! table already exists";
	}
	
	// Else create
	Relation *r = new Relation(relation_name, schema);
	this->relations.push_back(r);
	this->relations_size++;
	return "Table created";
}

string Database::insert(string relation_name, vector<string> data_items) {
	return "insert";
}

string Database::select(string relation_name) {
	return "select 1";
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

Relation::Relation(string relation_name, map<string, string> schema) {
	this->relation_name = relation_name;
	this->schema = schema;
}

/* Entry Class */

Entry::Entry() {
	
}

Entry::~Entry() {
	
}