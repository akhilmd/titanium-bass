#include "../../include/sql-compiler/parser.h"
#include "../../include/backend/backend.h"

using namespace std;

string parse(string S) {
	Database* db = new Database("dummy-db");
	
	//Testing Duplicates
	// db->create_table("dummy-table", {{"id","int"},{"name","string"}});
	
	db->create_table("dummy-table-stu", {{"id", "int"}, {"name", "string"}, {"marks","float"}, {"age", "int"}}, {"id", "name", "marks", "age"});
	db->create_table("dummy-table-teach", {{"id", "int"}, {"name", "string"}, {"subject","string"}}, {"id", "name", "marks"});
	
	return db->insert("dummy-table-stu", {"134", "Ezio", "99.1234", "20"});
	
}