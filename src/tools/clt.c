#include "../../include/tools/clt.h"
#include "../../include/utils/utils.h"

void run_db() {
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
		free(prompt);
		
    }
	
	// calc_c_cpp_close(calc);
}

void run_python() {
	typedef struct yy_buffer_state * YY_BUFFER_STATE;
    YY_BUFFER_STATE  bp;
    
	init_globals();
    while (1) {
		
		int new_socket = sock_create();
		
		while(1) {
			char line[1024] = {0};
			int valread = read( new_socket , line, 1024);			
			strcat(line, "\n"); /* grammar requires EOL */
			
			printf("\nExecute: %s", line);
			bp = yy_scan_string(line);
			yy_switch_to_buffer(bp);

			yyparse();

			yy_flush_buffer(bp);
			yy_delete_buffer (bp);
			
			send(new_socket , output , strlen(output), 0 );
			// printf("Hello message sent\n");
			
		}
		return 0;
		
    }
}

void mode_select(char** args, int no_of_args) {
    int i = 0;
    char ptr[10];
    
    if(no_of_args == 0) {
        run_db();
    }
    
    else if(!strcmp(args[0], "-p")) {
        run_python();  
    }
}

int main(int argl, char **argv) {
    
	mode_select(argv + 1, argl - 1);
    
    return 0;
    
}

