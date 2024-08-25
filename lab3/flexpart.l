%option noyywrap
%option header-file="lexer.h"
%{
#include <iostream>
#include "bisonpart.tab.h"
#include <string>
#include "cellandother.h"
void MYyyerror(const char* s, char symb);
// обновляет ylineno
// обновляет yyloc и передает данные в бизон
%}
%option yylineno
%%
"<VALUES" { return angleVALUES;}
"<VARDECLARATION" { return angleVARDECLARATION;}
"<VAR" { return angleVAR; }
"<DIMENSIONS" { return angleDIMENSIONS;}
"<" { /*printf("%c\n",yytext[0]);*/ return yytext[0]; }
">" { /*printf("%c\n",yytext[0]);*/ return yytext[0]; }
"/" { return yytext[0]; }
"=" { return yytext[0]; }
"[" { return yytext[0]; }
"]" { return yytext[0]; }
[0-9]* { yylval.number = std::stoi(yytext); /*printf(" this is num \n"); */return NUMBER; }
-[1-9]([0-9])* { yylval.number = std::stoi(yytext); return NUMBER; }
ADD  { return ADD; }
AND  { return AND; }
ASSIGN  { return ASSIGN; }
BOOL  { return BOOL; }
CALL  { return CALL; }
CELL  { return CELLL; }
CHECK  { return CHECK; }
CONDITION  { return CONDITION; }
CONST  { return CONST; }
count { return count; }
DIM { return DIM; }
DIMENSIONS  { return DIMENSIONS; }
DIMENSION  { return DIMENSION; }
DIV  { return DIV; }
DO  { return DO; }
DOWN  { return DOWN; }
EMPTY  { yylval.cell = EMPTY; return CELLEAN; }
EQ  { return EQ; }
EXIT   { yylval.cell = EXIT; return CELLEAN; }
GETDRONSCOUNT { return GETDRONSCOUNT; }
FALSE  { yylval.boolean = false; return CBOOLEAN; }
false { yylval.boolean = false; return BOOLEAN; }
FUNC  {  /*printf("This text !\n");*/ return FUNC; }
INDEX { return INDEX; }
INT  { return INT; }
LEFT  { return LEFT; }
MAX  { return MAX; }
MIN  { return MIN; }
MUL  { return MUL; }
NOT  { return NOT; }
name { return name; }
OR  { return OR; }
PROGRAM  { /*printf("This text !\n");*/ return PROGRAM; }
RIGHT  { return RIGHT; }
SUB  { return SUB; }
SWITCH  { return SWITCH; }
SENDDRONS { return SENDDRONS;}
TO  { return TO;}
TRUE  { yylval.boolean = true; return CBOOLEAN; }
true  { yylval.boolean = true; return BOOLEAN; }
TYPE  { return TYPE; }
UNDEF  { yylval.cell = UNDEF; return CELLEAN; }
UP  { return UP; }
VALUES  { return VALUES; }
VALUE  { return VALUE; }
VARDECLARATION  { return VARDECLARATION; }
VAR  { return VAR; }
WALL   { yylval.cell = WALL; return CELLEAN; }
WHILE  { return WHILE; }
[a-zA-Z_][a-zA-Z0-9_]*  { yylval.text = new std::string(yytext); return IDENTIFIER; }
[ \t]   {/*printf("not text !\n");*/}
[\r] { /* Игнорируем переводы строки и возвраты каретки */ }
[\n] {/*printf(" !!! \n");*/}
.       { printf("%c",yytext[0]); MYyyerror("This is a wrong thing that was founded", yytext[0]); }
%%
void MYyyerror(const char* s, char symb) {
    fprintf(stderr, "\nthis symbol \n Error at line %d: %s ", yylineno, s);
}
//int yywrap() {
//    return 1;
//}