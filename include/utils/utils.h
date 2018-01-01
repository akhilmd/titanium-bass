#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>

#include "../../include/tools/clt.h"

#define PORT 8080

int yyerror(char *s);
char *prompt_create(char *dname);
void init_globals();
int sock_create();