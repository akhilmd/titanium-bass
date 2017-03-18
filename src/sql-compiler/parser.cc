#include "../../include/sql-compiler/parser.h"
#include "../../include/backend/backend.h"

using namespace std;

string parse(string S) {
	Database* db = new Database("dummy-db");
	
	//Testing Duplicates
	// db->create_table("dummy-table", {{"id","int"},{"name","string"}});
	// db->create_table("dummy-table", {{"id","int"},{"name","string"}});
	
	return db->create_table("dummy-table", {{"id","int"},{"name","string"}});
	
}