%{
#include <string.h>
#include "../../../include/sql-compiler/gen/grammar.tab.h"
%}
%%
"cr" { return CREATE; }
"db" { return DATABASE; }
"tb" { return TABLE; }
"use" { return USE; }
"cl" { return CLOSE; }
"(" { return OP; }
")" { return CP; }
"," { return COMMA; }
"string" { yylval = strdup(yytext); return S_DATATYPE; }
"int" { yylval = strdup(yytext); return I_DATATYPE; }
"float" { yylval = strdup(yytext); return F_DATATYPE; }

[a-zA-Z_][a-zA-Z0-9_]* { yylval = strdup(yytext); return IDENTIFIER; }

"\""[a-zA-Z_][a-zA-Z0-9_]*"\"" { yylval = strdup(yytext); return S_DATA; }
[0-9][0-9]* { yylval = strdup(yytext); return I_DATA; }
[0-9][0-9]*"."[0-9][0-9]* { yylval = strdup(yytext); return F_DATA; }

";" { return EOS; }
\n { return EOL; }
[ \t] { /* ignore whitespace */ }
.  { printf("Mystery character %c\n", *yytext); }
%%
