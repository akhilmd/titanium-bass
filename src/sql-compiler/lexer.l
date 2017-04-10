%{
#include <string.h>
#include "../../../include/sql-compiler/gen/grammar.tab.h"
%}
%%
"create" { return CREATE; }
"database" { return DATABASE; }
"table" { return TABLE; }
"select" { return SELECT; }
"use" { return USE; }
"from" { return FROM; }
"close" { return CLOSE; }
"insert" { return INSERT; }
"update" { return UPDATE; }
"set" { return SET; }
"(" { return OP; }
")" { return CP; }
"," { return COMMA; }
"*" { return STAR; }
"where" { return WHERE;  }
"values" { return VALUES; }
"into" { return INTO; }
"string" { yylval = strdup(yytext); return S_DATATYPE; }
"int" { yylval = strdup(yytext); return I_DATATYPE; }
"float" { yylval = strdup(yytext); return F_DATATYPE; }

[a-zA-Z_][a-zA-Z0-9_]* { yylval = strdup(yytext); return IDENTIFIER; }

L?\'(\\.|[^\\"])*\' {
	char* text = strdup(yytext);
	char* new_text = malloc(sizeof(char) * (strlen(text) - 1));
	text[strlen(text) - 1] = '\0';
	strcpy(new_text, text+1);
	free(text);
	yylval = new_text;
	return S_DATA;
}

[0-9][0-9]* { yylval = strdup(yytext); return I_DATA; }
[0-9][0-9]*"."[0-9][0-9]* { yylval = strdup(yytext); return F_DATA; }
";" { return EOS; }
\n { return EOL; }
"=" { return EQI; }
[ \t] { /* ignore whitespace */ }
.  { printf("Mystery character %c\n", *yytext); }
%%
