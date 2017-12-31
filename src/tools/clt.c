#include "../../include/tools/clt.h"

int main(int argc, char **argv) {
    typedef struct yy_buffer_state * YY_BUFFER_STATE;
    YY_BUFFER_STATE  bp;
    
	init_globals();
    while (1) {
		char *prompt = prompt_create(dname);
		
		char *line = readline(prompt);
		
		if(!line || !strcmp(line, "exit;")) 
			break;
		
        if(*line) 
			add_history(line);
		
		strcat(line, "\n"); /* grammar requires EOL */
		
		bp = yy_scan_string(line);
        yy_switch_to_buffer(bp);

        yyparse();

        yy_flush_buffer(bp);
        yy_delete_buffer (bp);
		
		free(line);
    }
    // calc_c_cpp_close(calc);
}

int yyerror(char *s) {
    fprintf(stderr, "ERROR: %s!\n", s);
    printf("at: %s\n", yytext);
    nodi = 0;
    noc = 0;
}

char *prompt_create(char *dname) {
	char* prompt = malloc((strlen(dname)+strlen(DEFAULT_PROMPT)) * sizeof(char));
	strcpy(prompt, dname);
	strcat(prompt, DEFAULT_PROMPT);
	return prompt;
}

void init_globals() {
	db = backend_init();
	
    nodi = 0;
    dat_items = malloc(10 * sizeof (char*));

    // Support only 10 columns
    noc = 0;
    col_names = malloc(10 * sizeof (char*));
    col_dts = malloc(10 * sizeof (char*));
    dname = malloc(100 * sizeof(char));
	strcpy(dname, "");
}
