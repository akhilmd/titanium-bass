#include <stdio.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>

using namespace std;

bool create_DB(string DB_name);
bool create_table(string table_name, string table_columns[]);
bool insert_into_table(string table_name, string row_values[]);
bool check_DB_exists(string DB_name);
bool check_table_exists(string table_name);
string *sort_by_param(string table_name, string param)	//for groupby
string *retrive_info(string table_name, string columns[]) // For select statments

/** 

 More functions will be added
 If more functions are needed, please add them here

**/

