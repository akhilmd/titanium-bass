#include "../../include/utils/utils.h"

int sock_create() {
	int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
      
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
      
    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
	
	return new_socket;
}

int yyerror(char *s) {
	strcpy(output, s);
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
	output = malloc(sizeof(char) * 200);
	strcpy(dname, "");
}
