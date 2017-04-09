%{
#include <stdio.h>
#include <string.h>
#include "../../../include/sql-compiler/c-cc-interface.h"

void* db;

int noc;
char** col_names;
char** col_dts;

%}
%token CREATE
%token USE
%token CLOSE
%token DATABASE
%token TABLE
%token IDENTIFIER
%token COMMA
%token OP CP
%token EOS
%token EOL
%token S_DATA S_DATATYPE F_DATA F_DATATYPE I_DATA I_DATATYPE
%%
query:
    | EOL
    | CREATE dbase EOS EOL {
        printf("%s\n", database_create(db, $2));
    }
    
    | CREATE table EOS EOL {
        printf("%s\n", database_create_table(&db, $2, col_names, col_dts, noc));
        noc = 0;
    }
    
    | USE DATABASE IDENTIFIER EOS EOL {
        printf("%s\n", database_use(&db, $3));
    }
    
    | CLOSE DATABASE IDENTIFIER EOS EOL {
        printf("%s\n", database_close(&db, $3));
    }
    ;
dbase: DATABASE IDENTIFIER {
        $$ = $2;
    }
    ;
table: TABLE IDENTIFIER OP col_def_list CP {
        $$ = $2;
    }
    ;
col_def_list: col_def | col_def COMMA col_def_list  {
    }
    ;
col_def: IDENTIFIER datatype {
        // We are supporting only 10 columns
        col_names[noc] = $1;
        noc++;
    };
datatype: S_DATATYPE {
        col_dts[noc] = $1;
    }
    | I_DATATYPE {
        col_dts[noc] = $1;
    }
    | F_DATATYPE {
        col_dts[noc] = $1;
    }
    ;
%%