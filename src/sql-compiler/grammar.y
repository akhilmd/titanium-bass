%{
#include <stdio.h>
#include <string.h>
#include "../../../include/sql-compiler/c-cc-interface.h"
void* db;
int noc;
char** col_names;
char** col_dts;

int nodi;
char** dat_items;

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
%token DELETE
%token COMMA 
%token OP CP
%token EQI
%token EOS
%token EOL
%token STAR
%token WHERE
%token UPDATE
%token SET
%token DROP
%token VALUES INTO
%token START TRANSACTION
%token COMMIT ROLLBACK
%token S_DATA S_DATATYPE F_DATA F_DATATYPE I_DATA I_DATATYPE
%%
query:
    | EOL
    | CREATE dbase EOS EOL {
        printf("%s\n", database_create(db, $2));
    }
    ;
    | CREATE table EOS EOL {
        printf("%s\n", database_create_table(&db, $2, col_names, col_dts, noc));
        noc = 0;
    }
    ;
    | USE DATABASE IDENTIFIER EOS EOL {
        printf("%s\n", database_use(&db, $3));
    }
    ;
    | CLOSE DATABASE IDENTIFIER EOS EOL {
        printf("%s\n", database_close(&db, $3));
    }
    ;
    | SELECT STAR FROM IDENTIFIER EOS EOL {
        printf("%s\n", database_select(&db, $4));
    }
    ;
    | SELECT colnames FROM IDENTIFIER EOS EOL {
        printf("%s\n", database_select1(&db, $4, col_names,noc));
        noc = 0;
    }
    ;
    | SELECT STAR FROM IDENTIFIER WHERE IDENTIFIER EQI d_item EOS EOL {
        printf("%s\n", database_select2(&db, $4, $6, $8));
    }
    ;
    | SELECT colnames FROM IDENTIFIER WHERE IDENTIFIER EQI d_item EOS EOL {
        printf("%s\n", database_select3(&db, $4, col_names, noc, $6, $8));
        noc = 0;
    }
    ;
    | INSERT INTO IDENTIFIER VALUES OP data_items CP EOS EOL {
        printf("%s\n", database_insert(&db, $3, dat_items, nodi));
        nodi = 0;
    }
    ;
    | UPDATE IDENTIFIER SET IDENTIFIER EQI d_item WHERE IDENTIFIER EQI d_item EOS EOL {
        printf("%s\n", database_update(&db, $2, $4, $6, $8, $10));
    }
    ;
    | DELETE FROM IDENTIFIER EOS EOL {
        printf("%s\n", database_delete(&db, $3));
    }
    ;
    | DELETE FROM IDENTIFIER WHERE IDENTIFIER EQI d_item EOS EOL {
        printf("%s\n", database_delete1(&db, $3, $5, $7));
    }
    ;
    | DROP TABLE IDENTIFIER EOS EOL {
        printf("%s\n", database_table_drop(&db, $3));
    }
    ;
    | DROP dbase EOS EOL {
        printf("%s\n", database_drop(&db, $3));
    }
    ;
    | START TRANSACTION EOS EOL {
        printf("%s\n", database_start_transaction(&db));
    }
    ;
    | COMMIT TRANSACTION EOS EOL {
        printf("%s\n", database_commit_transaction(&db));
    }
    ;
    | ROLLBACK TRANSACTION EOS EOL {
        printf("%s\n", database_rollback_transaction(&db));
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
                noc = 0;
                yyerror("Duplicate column names");
                return 0;
            }
        }
        // We are supporting only 10 columns
        col_names[noc] = $1;
        noc++;
    }
    ;
colnames: col_name COMMA colnames
    |
    col_name
    ;
col_name: IDENTIFIER {
    col_names[noc] = $1;
    noc++;
    }
    ;
data_items: d_item COMMA data_items {
        dat_items[nodi] = $1; nodi++;
    }
    ;
    | d_item {
        dat_items[nodi] = $1; nodi++;
    };
d_item: I_DATA { $$ = $1; };
    | F_DATA  { $$ = $1; };
    | S_DATA  { $$ = $1; };
    ;
datatype: S_DATATYPE {
        col_dts[noc] = $1;
    }
    ;
    | I_DATATYPE {
        col_dts[noc] = $1;
    }
    ;
    | F_DATATYPE {
        col_dts[noc] = $1;
    }
    ;
%%