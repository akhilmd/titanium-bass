#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <set>
#include <iterator>
#include <sys/stat.h>

using namespace std;

/*
	Read from DB class to understand
*/


class Entry
{
	private:
		vector<string> row;
		
	public:
		Entry();
		Entry(vector<string> row);
		~Entry();

		// Depends on parsers output
		// Used for alter table
		void set_row_by_string(int index, string data);
		
		vector<string> get_row() { return row; }

		Entry& operator=(const Entry& other);

		// Overloading Operators
		friend ostream& operator<<(ostream& os, Entry& obj);
		friend bool operator==(Entry& lhs, Entry& rhs);
		friend bool operator!=(Entry& lhs, Entry& rhs);
		
};

class Relation
{
	private:
		vector<string> schema;
		string relation_name;
		string primary_key;
		vector<Entry> data_rows;
		int row_size;
	public:
		Relation(string relation_name, vector<string> schema);
		Relation(string relation_name, vector<string> schema, vector<Entry> rows);
		Relation(string relation_name, vector<string> schema, vector<string> keys, string primary_key);
		~Relation();
		
		void set_name(string rName) { relation_name = rName; }
		bool delete_row(string att_name, string att_value);
		string getName() { return relation_name; }
		string get_primary_key() { return primary_key; }

		// Query functions
		bool select_statement(); // For select *
		bool select_statement(string att_name, string att_value); // For where cluase
		bool alter_statement(string att_name, string data);
		
		// Depends on parsers output
		bool insert_row(string data);
		bool insert_row(vector<string> data);
		
		//Operators Overloading
		Relation& operator=(const Relation& other);
		friend ostream& operator<<(ostream& os, Relation& obj);
		friend bool operator==(Relation& lhs, Relation& rhs);
		friend bool operator!=(Relation& lhs, Relation& rhs);

	/* ======================================================= */
};

class DB {
	private:
		string db_name;
		vector<Relation> relations;
		int relations_size;
	public:
		DB(string db_name);
		~DB();
		
		bool create_table(string relation_name, vector<string> schema); // Will call constructor of Relation
		bool insert_table(string relation_name, string data);
		bool insert_table(string relation_name, vector<string> data); // Will call insert_row of appropriate Relation obj
		bool alter_table(string relation_name, string att_name, string data);
		bool delete_table(string relation_name);
		bool select_from_table(string relation_name); // For select *
		bool select_from_table(string relation_name, string att_name, string att_value); // For where clause
		
		void flush_to_disk(); // Used by destructor
		void get_from_disk(); // Used by constructor
		
}

/** 

 More functions will be added
 If more functions are needed, please add them here

**/