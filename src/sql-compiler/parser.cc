#include "../../include/sql-compiler/parser.h"
#include "../../include/backend/backend.h"

using namespace std;

string parse(string S) {
	Database* db = new Database("dummy-db");
	return db->create();
}