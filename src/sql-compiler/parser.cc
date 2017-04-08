#include "../../include/sql-compiler/parser.h"
#include "../../include/backend/backend.h"

using namespace std;

string parse(string S) {
	Database* db = new Database("dummy-db");
	
	//Testing Duplicates
	// db->create_table("dummy-table", {{"id","int"},{"name","string"}});
	
	db->create_table("dummy-table-stu", {"int", "string", "float", "int"}, {"id", "name", "marks", "age"});
	db->create_table("dummy-table-teach", {"int", "string", "string"}, {"id", "name", "marks"});
	
	db->insert("dummy-table-stu", {"134", "Price", "99.1234", "20"});
	db->insert("dummy-table-stu", {"134", "Price", "99.1234", "20"});
	db->insert("dummy-table-stu", {"134", "Price", "99.1234", "20"});
	db->insert("dummy-table-stu", {"135", "Soap", "98.1234", "21"});
	db->insert("dummy-table-stu", {"136", "Gaz", "94.1234", "22"});
	db->insert("dummy-table-stu", {"137", "Roach", "93.1234", "23"});
	db->insert("dummy-table-stu", {"138", "Allen", "93.1234", "23"});
	db->insert("dummy-table-stu", {"139", "Nikolai", "93.1234", "23"});
	db->insert("dummy-table-stu", {"140", "Yuri", "93.1234", "23"});
	db->insert("dummy-table-stu", {"141", "Ghost", "93.1234", "23"});
	db->insert("dummy-table-stu", {"142", "Scarecrow", "93.1234", "23"});
	db->insert("dummy-table-stu", {"143", "Alex", "93.1234", "23"});
	db->insert("dummy-table-stu", {"144", "Hesh", "93.1234", "23"});
	db->insert("dummy-table-stu", {"145", "Gabriel", "93.1234", "23"});
	db->insert("dummy-table-stu", {"146", "Keegan", "93.1234", "23"});
	db->insert("dummy-table-stu", {"147", "Logan", "93.1234", "23"});
	db->insert("dummy-table-stu", {"148", "Riley", "93.1234", "23"});
	db->insert("dummy-table-stu", {"149", "Merrick", "93.1234", "23"});
	db->insert("dummy-table-stu", {"150", "Ghost", "93.1234", "24"});
	db->insert("dummy-table-stu", {"151", "Ghost", "93.1234", "25"});
	
	// return db->select("dummy-table-stu");
	// return db->select(	"dummy-table-stu",
						// "name",
						// "Ghost");
	// return db->select( "dummy-table-stu", {"id", "age", "name"});
	// return db->select( 	"dummy-table-stu",
						// "name",
						// "Ghost",
						// {"id", "age", "name"}
						// );
						
	// return db->update( 	"dummy-table-stu",  // UPDATE <table name>
						// "name",             // SET <set_attribute> = 
						// "Ezio",             // <new value>
						// "id",               // WHERE <where_attribute> = 
						// "134"               // <where value>
					// );
	db->remove("dummy-table-stu");
	return db->select("dummy-table-stu");

}					