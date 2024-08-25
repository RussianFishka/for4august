// пролог
%locations
%{
extern int yylineno;
%}
%{
#include "myAst.h"
#include "cellandother.h"
//#include "lexer.h"
#include <iostream>
#include <string>
#include <variant>
#include <vector>
#include <map>
int yylex(void);
void yyerror(const char*);
%}
%{
std::string labirint{"tests/labirint2.txt"};
struct Position position{};
%}
%{
std::vector<std::vector<CELL>> maze = loadMaze(labirint, position);
//void myyyerror(const YYLTYPE* loc, const char* s);
%}
%{
struct Robot robot{position, maze};
%}
%code requires{
#include "cellandother.h"
#include "myAst.h"
} // Нужно, чтобы union знал о всех структурах

%union {
    int number;
    bool boolean;
    std::string* text;
    CELL cell;
    Node * node;
    std::vector<Node*>* vecnode;
    //std::vector<int>* intArray;
    //std::vector<bool>* boolArray;
    //std::vector<CELL>* cellArray;
}
//to declare exclusively nonterminal symbols, use the
//safer %nterm: instead of type (terminals as well)
//A character token kind doesn’t need to be declared e.g '+'
%token <boolean> CBOOLEAN BOOLEAN
%token <number> NUMBER
%token <text> IDENTIFIER
%token <cell> CELLEAN
%token VAR ASSIGN LEFT RIGHT UP DOWN SENDDRONS GETDRONSCOUNT
%token FUNC CALL PROGRAM VARDECLARATION TYPE DIMENSION  VALUE CONST INT BOOL CELLL
%token count DIM INDEX TO name WHILE CHECK DO SWITCH CONDITION angleVALUES angleVAR angleDIMENSIONS angleVARDECLARATION
%left VALUES
%left DIMENSIONS
%left ADD SUB // объявление токенов + указание их приоритета
%left OR AND
%left EQ
%left MAX MIN
%left NOT
%left MUL DIV // the one declared later has higher precedence and is grouped first.
%nterm <node> expression value onevar while_loop condition_list switch_statement function_declaration function_call
%nterm <node> program_declaration program_list assignment var_value vardeclaration statement movement
%nterm <vecnode> expression_list values value_list var_list dim_list assign_list statement_list dimension_list dimensions
%nterm <text> type
%%
//input:
//    | input line
//    | line
 //   ;

start:
    program_declaration { ProgramNodePerf((ProgramNode *)$1); }

// только ValueNodes
assignment:
    '<' ASSIGN '>' '<' VALUE '>' expression '<' '/' VALUE '>' '<' TO '>' assign_list '<' '/' TO '>' '<' '/' ASSIGN '>'{  $$ = new AssignNode($7,*$15,yylineno); delete $15;
                                                                                                                            std::cout << "Assignment" << std::endl;
                                                                                                                            }
    ;
assign_list:
      var_value {$$ = new std::vector<Node*>();
                 $$->push_back($1);}
      | assign_list  var_value{$$ = $1; $$->push_back($2);}
      ;
expression: // переменная или операция или просто значение
    //{std::cout << "with " << std::endl;}
     value {}
    | '<' ADD '>' expression_list '<' '/' ADD '>' {
            //if ($3->size() < 2) {
            //    yyerror(yylineno, "Addition requires at least two operands");
            //    YYERROR;
            //}
            std::cout << "Addition with " << $4->size() << " elements" << std::endl;
            $$ = new MultiOpNode(std::move(*$4), add, yylineno);
            delete $4;  // Освобождаем память
        }
    | '<' SUB '>' expression expression '<' '/' SUB '>' {
            std::cout << "Subtraction" << std::endl;
            //auto node = $3;
            //if(node->type == val && (ValueNode*)node->vartype == vcell){
            //        yyerror(yylineno, "arifmetic operations with cell...");
            //        YYERROR;
            //}
            //node = $4;
            //if(node->type == val && (ValueNode*)node->vartype == vcell){
            //       yyerror(yylineno, "arifmetic operations with cell...");
            //       YYERROR;
            //}
            $$ = new BinaryOpNode($4, $5, sub, yylineno);
        }
    | '<' MUL '>' expression_list '<' '/' MUL '>' {
            std::cout << "Multiplication with " << $4->size() << " elements" << std::endl;
            $$ = new MultiOpNode(std::move(*$4), mul, yylineno);
            delete $4;  // Освобождаем память
        }
    | '<' DIV '>' expression expression '<' '/' DIV '>' {
            std::cout << "Division" << std::endl;
            $$ = new BinaryOpNode($4, $5, divv, yylineno);
        }
    | '<' EQ '>' expression_list '<' '/' EQ '>' {
            //if ($3->size() < 2) {
            //    yyerror(yylineno, "Equality check requires at least two operands");
            //    YYERROR;
            //}
            std::cout << "Equality Check with " << $4->size() << " elements" << std::endl;
            $$ = new MultiOpNode(std::move(*$4), eq, yylineno);
            delete $4;  // Освобождаем память
        }
    | '<' NOT '>' expression '<' '/' NOT '>' {
            std::cout << "Logical NOT" << std::endl;
            //auto node = $3;
            //if(node->type == val && (ValueNode*)node->vartype == vcell){
            //        yyerror(yylineno, "arifmetic operations with cell...");
            //        YYERROR;
            //}
            $$ = new UnaryOpNode($4, nott, yylineno);
        }
    | '<' AND '>' expression_list '<' '/' AND '>' {
            std::cout << "Logical AND with " << $4->size() << " elements" << std::endl;
            $$ = new MultiOpNode(std::move(*$4), andd, yylineno);
            delete $4;  // Освобождаем память
        }
    | '<' OR '>' expression_list '<' '/' OR '>' {
            //if ($3->size() < 2) {
            //    yyerror(yylineno, "Logical OR requires at least two operands");
            //    YYERROR;
            //}
            std::cout << "Logical OR with " << $4->size() << " elements" << std::endl;
            $$ = new MultiOpNode(std::move(*$4), orr, yylineno);
            delete $4;  // Освобождаем память
        }
    | '<' MAX '>' expression_list '<' '/' MAX '>' {
            //if ($3->size() < 2) {
            //    yyerror(yylineno, "Maximum requires at least two operands");
            //    YYERROR;
            //}
            std::cout << "Maximum with " << $4->size() << " elements" << std::endl;
            $$ = new MultiOpNode(std::move(*$4), maxx, yylineno);
            delete $4;  // Освобождаем память
        }
    | '<' MIN '>' expression_list '<' '/' MIN '>' {
            //if ($3->size() < 2) {
            //    yyerror(yylineno, "Minimum requires at least two operands");
            //    YYERROR;
            //}
            std::cout << "Minimum with " << $4->size() << " elements" << std::endl;
            $$ = new MultiOpNode(std::move(*$4), minn, yylineno);
            delete $4;  // Освобождаем память
        }
    ; // обращение к переменной это тоже выражение
expression_list:
    expression { auto node = $1;
        $$ = new std::vector<Node*>();
        $$->push_back($1); } // никаких cell в арифметике быть не должно
    | expression_list expression {
        $$ = $1; $$->push_back($2); }
;
value: // то с чем возможны операции
    NUMBER { /*std::cout << "show your way" << std::endl;*/ $$ = new ValueNode($1, yylineno); }
    | BOOLEAN { $$ = new ValueNode($1, yylineno); }
    | CELLEAN { $$ = new ValueNode($1, yylineno); }
     // По имени переменной можно будет ее найти на поздней стадии
    | var_value {$$ = $1;}
    // когда dim_list пуст, тогда немногомерная переменная
    ;
var_value:
    angleVAR name '=' '<' IDENTIFIER '>' dim_list '/' VAR '>' {$$ = new ValueNode(*$5, *$7, yylineno); delete $7; delete $5; } // только единичные штуки
    ;
dim_list:
      /* пустое правило */ { $$ = new std::vector<Node *>(); } // написаны максимальные измерения
        | dim_list '<' DIM '>' '<' INDEX '>' expression '<' '/' INDEX '>' '<' '/' DIM '>' { $$ = $1; $$->push_back($8); }
        ;  // опциональное поле это здесь подчеркивается
movement:
    '<' LEFT '>' expression '<' '/' LEFT '>' { /*std::cout << "Move Left" << std::endl;*/ $$ = new MoveNode(left,&robot, yylineno, $4); }
    | '<' RIGHT '>' expression '<' '/' RIGHT '>' { /*std::cout << "Move Right" << std::endl;*/ $$ = new MoveNode(right,&robot, yylineno, $4); }
    | '<' UP '>' expression '<' '/' UP '>' { /*std::cout << "Move Up" << std::endl;*/ $$ = new MoveNode(up,&robot, yylineno, $4);}
    | '<' DOWN '>' expression '<' '/' DOWN '>' { /*std::cout << "Move Down" << std::endl;*/ $$ = new MoveNode(down,&robot, yylineno, $4); }
    | '<' SENDDRONS '>' expression '<' '/' SENDDRONS '>' { /*std::cout << "Move SendDrons" << std::endl;*/ $$ = new MoveNode(senddrones,&robot, yylineno, $4); }
    | '<' GETDRONSCOUNT '>' IDENTIFIER '<' '/' GETDRONSCOUNT  '>' {  $$ = new MoveNode(getdrones,&robot, yylineno, *$4); delete $4; }
    ;

vardeclaration:
     angleVARDECLARATION '>' var_list '<' '/' VARDECLARATION '>' { $$ = new Vardecl(*$3, yylineno); delete $3; std::cout << "Variable Declaration" << std::endl; }
    ;

var_list:
    /* пустое правило */ { std::cout << "chop chop" << std::endl; $$ = new std::vector<Node *>();} // пустышка
    | var_list onevar{ $$ = $1; $$->push_back($2); }
    ;
onevar:
    angleVAR '=' IDENTIFIER '[' CONST '=' CBOOLEAN ']' '>' '<' TYPE '>' type '<' '/' TYPE '>' dimensions values '<' '/' VAR '>' {
       // произведение всех измерений dimensions
        /*std::cout << "chap chap" << std::endl;*/
        Vartype vart;
        if (*$13 == "INT") {
            vart = vint;
        } else if (*$13 == "BOOL") {
            vart = vbool;
        } else if (*$13 == "CELL") {
            vart = vcell;
        }
        $$ = new VardecNode(vart,*$3, $7, *$18, *$19, yylineno);
        delete $13;
        delete $3;
        delete $18;
        delete $19;
    }
    ;
type:
    INT { $$ = new std::string("INT"); }
    | BOOL { $$ = new std::string("BOOL"); }
    | CELLL { $$ = new std::string("CELL"); }
    ;

dimensions:
    //Обработка размерностей
    // тут может возникнуть ошибка number != dimlistsize
     /* пустое правило */ { /*std::cout << "chipI chipI" << std::endl;*/ $$ = new std::vector<Node *>(); } // опциональное поле это здесь подчеркивается
     | dimensions angleDIMENSIONS count '=' NUMBER '>' dimension_list '<' '/' DIMENSIONS '>' {
     std::cout << "chip chip" << std::endl;
     if($7->size() != $5){
     //   myyyerror("Dimensions count != dimensions");
        std::cout << "Dimensions count != dimensions" << std::endl;
        YYERROR;
     }
     delete $1;
     $$ = $7; // num 0 и dim нет - подходит
          std::cout << "chip chip" << std::endl;
     }
    ;

dimension_list:
    { $$ = new std::vector<Node *>(); } // опциональное поле это здесь подчеркивается
    | dimension_list '<' DIMENSION '>' expression '<' '/' DIMENSION '>' { $$ = $1; $$->push_back($5); } // написаны максимальные измерения
    ;

values:
    //Обработка значений
    { $$ = new std::vector<Node*>(); std::cout << "chup chup " << std::endl; } // блок может отсутствовать => отказались от инициализации
    | values angleVALUES '>' value_list '<' '/' VALUES '>' { delete $1; $$ = $4; } // тоже можно было отказаться от инициализации когда пустой value_list
    ;

value_list:
     /* пустое правило */ { std::cout << "chup chup " << std::endl; $$ = new std::vector<Node*>(); }
    | value_list '<' VALUE '>' expression '<' '/' VALUE '>' { $$ = $1; $$->push_back($5); } // одинаковость типов выше проверяется
    ;

while_loop:
    '<' WHILE '>' '<' CHECK '>' expression '<' '/' CHECK '>' '<' DO '>' statement_list '<' '/' WHILE '>' { std::cout << "While Loop" << std::endl;
                                                                                                          $$ = new WhileNode($7,*$15, yylineno);
                                                                                                          delete $15;  // Освобождаем память
                                                                                                           }
    ;

switch_statement:
    '<' SWITCH '>' condition_list '<' '/' SWITCH '>' { $$ = $4; std::cout << "Switch Statement" << std::endl; }
    ;

condition_list:
    '<' CONDITION '>' '<' CHECK '>' expression '<' '/' CHECK '>' '<' DO '>' statement_list '<' '/' DO '>' '<' '/' CONDITION '>' { $$ = new SwitchNode(yylineno);
                                                                                                                                 ((SwitchNode *)$$)->expressions.push_back($7);
                                                                                                                                 ((SwitchNode *)$$)->groups_statements.push_back(*$15);
                                                                                                                                 delete $15;
                                                                                                                                 }
    | condition_list '<' CONDITION '>' '<' CHECK '>' expression '<' '/' CHECK '>' '<' DO '>' statement_list  '<' '/' DO '>' '<' '/' CONDITION '>' {
                                                                                                                                 $$ = $1;
                                                                                                                                 ((SwitchNode *)$$)->expressions.push_back($8);
                                                                                                                                 ((SwitchNode *)$$)->groups_statements.push_back(*$16);
                                                                                                                                 delete $16;
                                                                                                                                 }
    ; //{$$ = new SwitchNode(yylineno);}

function_declaration:
    '<' FUNC name '=' IDENTIFIER '>' statement_list '<' '/' FUNC '>' { $$ = new FunctionNode(*$5, *$7, yylineno); delete $7; delete $5; std::cout << "Function Declaration" << std::endl; }
    ;

function_call:
    '<' CALL '>' IDENTIFIER '<' '/' CALL '>' { $$ = new FunctionCNode(*$4, yylineno); delete $4; }
    ;

program_declaration:
    '<' PROGRAM '>' program_list '<' '/' PROGRAM '>' { $$ = $4; std::cout << "Program Declaration" << std::endl; }
    ;

program_list:
    function_declaration {$$ = new ProgramNode(yylineno); ((ProgramNode *)$$)->declarations.push_back($1);}
    | vardeclaration {$$ = new ProgramNode(yylineno); ((ProgramNode *)$$)->declarations.push_back($1);}
    | program_list function_declaration {$$ = $1; ((ProgramNode *)$$)->declarations.push_back($2);}
    | program_list vardeclaration {$$ = $1; ((ProgramNode *)$$)->declarations.push_back($2);}
    ;

statement:
     assignment
    | vardeclaration
    | movement
    | expression
    | while_loop
    | switch_statement
    | function_call
    ;

statement_list:
    /*пустое правило*/ { /*std::cout << "I wanna see " << std::endl;*/ $$ = new std::vector<Node *>();}
    | statement_list statement { /*std::cout << "I wanna see again " << std::endl;*/ $$ = $1; $$->push_back($2); } // вектор
    ;

%%
void yyerror(const char *s) {
}
//void myyyerror(const YYLTYPE* loc, const char* s) {
//    std::cerr << "Error: " << s << " at line " << loc->first_line << ", column " << loc->first_column << std::endl;
//}
