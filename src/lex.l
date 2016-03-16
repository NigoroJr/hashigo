%{
#include <string>
#include "nodes.hpp"
#include "parser.hpp"

#define SAVE_TOKEN yylval.string = new std::string(yytext, yyleng)
#define TOKEN(t) (yylval.token = t)

extern "C" int yylex();
%}

/* Suppress warnings */
%option noyywrap
%option noinput
%option nounput

%%
[ \t\n]             ;
[A-Z]+              SAVE_TOKEN; return T_INSTRUCTION;
[a-zA-Z0-9_:.-]+|\? SAVE_TOKEN; return T_ADDRESS;

"("                 return TOKEN(T_LPAREN);
")"                 return TOKEN(T_RPAREN);
"["                 return TOKEN(T_LBRACKET);
"]"                 return TOKEN(T_RBRACKET);
","                 return TOKEN(T_COMMA);
";"                 return TOKEN(T_SEMICOLON);

.                   fprintf(stderr, "Unknown token\n"); yyterminate();
%%
