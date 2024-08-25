/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_BISONPART_TAB_H_INCLUDED
# define YY_YY_BISONPART_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 29 "bisonpart.y"

#include "cellandother.h"
#include "myAst.h"

#line 54 "bisonpart.tab.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    CBOOLEAN = 258,                /* CBOOLEAN  */
    BOOLEAN = 259,                 /* BOOLEAN  */
    NUMBER = 260,                  /* NUMBER  */
    IDENTIFIER = 261,              /* IDENTIFIER  */
    CELLEAN = 262,                 /* CELLEAN  */
    VAR = 263,                     /* VAR  */
    ASSIGN = 264,                  /* ASSIGN  */
    LEFT = 265,                    /* LEFT  */
    RIGHT = 266,                   /* RIGHT  */
    UP = 267,                      /* UP  */
    DOWN = 268,                    /* DOWN  */
    SENDDRONS = 269,               /* SENDDRONS  */
    GETDRONSCOUNT = 270,           /* GETDRONSCOUNT  */
    FUNC = 271,                    /* FUNC  */
    CALL = 272,                    /* CALL  */
    PROGRAM = 273,                 /* PROGRAM  */
    VARDECLARATION = 274,          /* VARDECLARATION  */
    TYPE = 275,                    /* TYPE  */
    DIMENSION = 276,               /* DIMENSION  */
    VALUE = 277,                   /* VALUE  */
    CONST = 278,                   /* CONST  */
    INT = 279,                     /* INT  */
    BOOL = 280,                    /* BOOL  */
    CELLL = 281,                   /* CELLL  */
    count = 282,                   /* count  */
    DIM = 283,                     /* DIM  */
    INDEX = 284,                   /* INDEX  */
    TO = 285,                      /* TO  */
    name = 286,                    /* name  */
    WHILE = 287,                   /* WHILE  */
    CHECK = 288,                   /* CHECK  */
    DO = 289,                      /* DO  */
    SWITCH = 290,                  /* SWITCH  */
    CONDITION = 291,               /* CONDITION  */
    angleVALUES = 292,             /* angleVALUES  */
    angleVAR = 293,                /* angleVAR  */
    angleDIMENSIONS = 294,         /* angleDIMENSIONS  */
    angleVARDECLARATION = 295,     /* angleVARDECLARATION  */
    VALUES = 296,                  /* VALUES  */
    DIMENSIONS = 297,              /* DIMENSIONS  */
    ADD = 298,                     /* ADD  */
    SUB = 299,                     /* SUB  */
    OR = 300,                      /* OR  */
    AND = 301,                     /* AND  */
    EQ = 302,                      /* EQ  */
    MAX = 303,                     /* MAX  */
    MIN = 304,                     /* MIN  */
    NOT = 305,                     /* NOT  */
    MUL = 306,                     /* MUL  */
    DIV = 307                      /* DIV  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 34 "bisonpart.y"

    int number;
    bool boolean;
    std::string* text;
    CELL cell;
    Node * node;
    std::vector<Node*>* vecnode;
    //std::vector<int>* intArray;
    //std::vector<bool>* boolArray;
    //std::vector<CELL>* cellArray;

#line 135 "bisonpart.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;

int yyparse (void);


#endif /* !YY_YY_BISONPART_TAB_H_INCLUDED  */
