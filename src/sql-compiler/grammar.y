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
%token FROM
%token IDENTIFIER
%token SELECT
%token INSERT
%token COMMA 
%token OP CP
%token EQI
%token EOS
%token EOL
%token STAR
%token WHERE
%token UPDATE
%token SET
%token VALUES INTO
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

    | SELECT STAR FROM IDENTIFIER EOS EOL {
        printf("%s\n", database_select(&db, $4)); }
    
    | SELECT colnames FROM IDENTIFIER EOS EOL {
        printf("%s\n", database_select1(&db, $4, col_names,noc));
        noc = 0;
    }

    | SELECT STAR FROM IDENTIFIER WHERE IDENTIFIER EQI d_item EOS EOL {
        printf("%s\n", database_select2(&db, $4, $6, $8));
    }

    | INSERT INTO IDENTIFIER VALUES OP data-items CP EOS EOL {
        printf("%s\n", database_insert(&db, $4, col_names, noc));
        noc = 0;
    }

    | UPDATE IDENTIFIER SET IDENTIFIER EQI d_item WHERE IDENTIFIER EQI d_item EOS EOL {
        printf("%s\n", database_update(&db, $2, $4, $6, $8, $10));
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
        // rudimentary check for duplicate columns
        int i = 0;
        for (i=0;i<noc;++i) {
            if (strcmp(col_names[i], $1) == 0) {
                // error out
                yyerror("Duplicate column names");
                return 0;
            }
        }
        // We are supporting only 10 columns
        col_names[noc] = $1;
        noc++;
    };
colnames: col_name COMMA colnames
    |
    col_name
    ;
col_name: IDENTIFIER {
    col_names[noc] = $1;
    noc++;
    }
    ;
data-items: d_item COMMA data-items
    |
    d_item
    ;
d_item: I_DATA { $$ = $1; col_names[noc] =$1; noc++; }
    | F_DATA  { $$ = $1; col_names[noc] =$1; noc++;}
    | S_DATA  { $$ = $1; col_names[noc] =$1; noc++; }
    | IDENTIFIER { $$ = $1; col_names[noc] =$1; noc++; }
    ;
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