#include "../../include/sql-compiler/parser.h"
#include "../../include/backend/backend.h"

using namespace std;

string parse(string S) {
	Database* db = new Database("dummy-db");
	
	//Testing Duplicates
	// db->create_table("dummy-table", {{"id","int"},{"name","string"}});
	
	db->create_table("dummy-table-stu", {{"id", "int"}, {"name", "string"}, {"marks","float"}, {"age", "int"}}, {"id", "name", "marks", "age"});
	db->create_table("dummy-table-teach", {{"id", "int"}, {"name", "string"}, {"subject","string"}}, {"id", "name", "marks"});
	
	db->insert("dummy-table-stu", {"134", "Ezio", "99.1234", "20"});
	db->insert("dummy-table-stu", {"135", "Soap", "98.1234", "21"});
	db->insert("dummy-table-stu", {"136", "Price", "94.1234", "22"});
	db->insert("dummy-table-stu", {"137", "Ghost", "93.1234", "23"});
	
	return db->select("dummy-table-stu");
}