#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <set>
#include <iterator>
#include <sys/stat.h>

using namespace std;

class Entry {
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

class Relation {
    private:
        map<string, string> schema;
        string relation_name;
        vector<Entry> data_rows;
        int row_size;

    public:
		Relation();
        Relation(string relation_name, map<string, string> schema);
        Relation(string relation_name, map<string, string> schema, vector<Entry> rows);
        Relation(string relation_name, map<string, string> schema, vector<string> keys, string primary_key);
        ~Relation();

        void set_name(string rName) { relation_name = rName; }
        bool delete_row(string att_name, string att_value);
        string getName() { return relation_name; }
        
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
};

class Database {
    private:
        string db_name;
		
        vector<Relation*> relations;
		int relations_size;
		
        void flush_to_disk(); // Used by destructor
        void get_from_disk(); // Used by constructor

        bool is_created;
        bool is_open;
    public:
        Database(string db_name);
        ~Database();

        // All functions return a message that is to be displayed
        // on the CLI if at all.

        // Creates a database with the name db_name.
        string create();

        // If database is not created, return error in all
        // the following functions unless specified otherwise.

        // Makes database ready for operations.
        string open();

        // If database is not opened, return error in all
        // the following functions unless specified otherwise.

        // Create a table file and a schema file for that table.
        string create_table (string relation_name, map<string, string> schema);

        // Insert a row of data into table.
        // Will call insert_row of appropriate Relation object.
        string insert(string relation_name, vector<string> data_items);

        // Returns formatted data
        string select(string relation_name);

        string select(
            string relation_name,
            string where_column_name,
            string where_data_item);

        string select(string relation_name, vector<string> column_names);

        string select(
            string relation_name,
            string where_column_name,
            string where_data_item,
            vector<string> column_names);

        // Update table
        string update(
            string relation_name,
            string column_name,
            string data_item,
            string where_column_name,
            string where_data_item);

        // delete() would be a better name but key-word

        // Delete all rows in a table
        string remove(string relation_name);
        string remove(
            string relation_name,
            string where_column_name,
            string where_data_item);

        string drop_table(string relation_name);

        // Drop database
        // Delete folder
        string drop();

        // Start a transaction.
        // Keeps a copy of the whole database in case
        // rollback needs to happen.
        string start();

        // Apply changes in a transaction.
        // Deletes the copy created by start.
        string commit();

        // Undo changes in a transaction.
        // Deletes currect files and makes the rollback files
        // as the main data files.
        string rollback();

        // Close any open file objects.
        // Remove lock on DB.
        string close();
		
		string get_db_name() { return db_name; }
};