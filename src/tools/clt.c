#include "../../include/tools/clt.h"

int main(int argc, char **argv) {
    typedef struct yy_buffer_state * YY_BUFFER_STATE;
    YY_BUFFER_STATE  bp;
    char line[100];

    db = backend_init();

    // Support only 10 columns
    noc = 0;
    col_names = malloc(10 * sizeof (char*));
    col_dts = malloc(10 * sizeof (char*));
   
    while (1) {
        printf("tdb >>> ");
        gets(line);
        if (!strcmp(line, "exit")) break;
        strcat(line, "\n"); /* grammer requires EOL */
        bp = yy_scan_string(line);
        yy_switch_to_buffer(bp);

        yyparse();

        yy_flush_buffer(bp);
        yy_delete_buffer (bp);
    }
    // calc_c_cpp_close(calc);
}

int yyerror(char *s) {
    fprintf(stderr, "ERROR: %s!\n", s);
    printf("at: %s\n", yytext);
}
