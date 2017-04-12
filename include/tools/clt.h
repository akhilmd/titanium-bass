#include <stdio.h>
#include <string.h>

#include "../../include/sql-compiler/c-cc-interface.h"

extern int yyerror(char*);
extern char* yytext;

extern void* db;
extern int noc;
extern char** col_names;
extern char** col_dts;

extern int nodi;
extern char** dat_items;

extern char* dname;