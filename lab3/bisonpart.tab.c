/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 3 "bisonpart.y"

extern int yylineno;
#line 6 "bisonpart.y"

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
#line 18 "bisonpart.y"

std::string labirint{"tests/labirint3.txt"};
struct Position position{};
#line 22 "bisonpart.y"

std::vector<std::vector<CELL>> maze = loadMaze(labirint, position);
//void myyyerror(const YYLTYPE* loc, const char* s);
#line 26 "bisonpart.y"

struct Robot robot{position, maze};

#line 98 "bisonpart.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "bisonpart.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_CBOOLEAN = 3,                   /* CBOOLEAN  */
  YYSYMBOL_BOOLEAN = 4,                    /* BOOLEAN  */
  YYSYMBOL_NUMBER = 5,                     /* NUMBER  */
  YYSYMBOL_IDENTIFIER = 6,                 /* IDENTIFIER  */
  YYSYMBOL_CELLEAN = 7,                    /* CELLEAN  */
  YYSYMBOL_VAR = 8,                        /* VAR  */
  YYSYMBOL_ASSIGN = 9,                     /* ASSIGN  */
  YYSYMBOL_LEFT = 10,                      /* LEFT  */
  YYSYMBOL_RIGHT = 11,                     /* RIGHT  */
  YYSYMBOL_UP = 12,                        /* UP  */
  YYSYMBOL_DOWN = 13,                      /* DOWN  */
  YYSYMBOL_SENDDRONS = 14,                 /* SENDDRONS  */
  YYSYMBOL_GETDRONSCOUNT = 15,             /* GETDRONSCOUNT  */
  YYSYMBOL_FUNC = 16,                      /* FUNC  */
  YYSYMBOL_CALL = 17,                      /* CALL  */
  YYSYMBOL_PROGRAM = 18,                   /* PROGRAM  */
  YYSYMBOL_VARDECLARATION = 19,            /* VARDECLARATION  */
  YYSYMBOL_TYPE = 20,                      /* TYPE  */
  YYSYMBOL_DIMENSION = 21,                 /* DIMENSION  */
  YYSYMBOL_VALUE = 22,                     /* VALUE  */
  YYSYMBOL_CONST = 23,                     /* CONST  */
  YYSYMBOL_INT = 24,                       /* INT  */
  YYSYMBOL_BOOL = 25,                      /* BOOL  */
  YYSYMBOL_CELLL = 26,                     /* CELLL  */
  YYSYMBOL_count = 27,                     /* count  */
  YYSYMBOL_DIM = 28,                       /* DIM  */
  YYSYMBOL_INDEX = 29,                     /* INDEX  */
  YYSYMBOL_TO = 30,                        /* TO  */
  YYSYMBOL_name = 31,                      /* name  */
  YYSYMBOL_WHILE = 32,                     /* WHILE  */
  YYSYMBOL_CHECK = 33,                     /* CHECK  */
  YYSYMBOL_DO = 34,                        /* DO  */
  YYSYMBOL_SWITCH = 35,                    /* SWITCH  */
  YYSYMBOL_CONDITION = 36,                 /* CONDITION  */
  YYSYMBOL_angleVALUES = 37,               /* angleVALUES  */
  YYSYMBOL_angleVAR = 38,                  /* angleVAR  */
  YYSYMBOL_angleDIMENSIONS = 39,           /* angleDIMENSIONS  */
  YYSYMBOL_angleVARDECLARATION = 40,       /* angleVARDECLARATION  */
  YYSYMBOL_VALUES = 41,                    /* VALUES  */
  YYSYMBOL_DIMENSIONS = 42,                /* DIMENSIONS  */
  YYSYMBOL_ADD = 43,                       /* ADD  */
  YYSYMBOL_SUB = 44,                       /* SUB  */
  YYSYMBOL_OR = 45,                        /* OR  */
  YYSYMBOL_AND = 46,                       /* AND  */
  YYSYMBOL_EQ = 47,                        /* EQ  */
  YYSYMBOL_MAX = 48,                       /* MAX  */
  YYSYMBOL_MIN = 49,                       /* MIN  */
  YYSYMBOL_NOT = 50,                       /* NOT  */
  YYSYMBOL_MUL = 51,                       /* MUL  */
  YYSYMBOL_DIV = 52,                       /* DIV  */
  YYSYMBOL_53_ = 53,                       /* '<'  */
  YYSYMBOL_54_ = 54,                       /* '>'  */
  YYSYMBOL_55_ = 55,                       /* '/'  */
  YYSYMBOL_56_ = 56,                       /* '='  */
  YYSYMBOL_57_ = 57,                       /* '['  */
  YYSYMBOL_58_ = 58,                       /* ']'  */
  YYSYMBOL_YYACCEPT = 59,                  /* $accept  */
  YYSYMBOL_start = 60,                     /* start  */
  YYSYMBOL_assignment = 61,                /* assignment  */
  YYSYMBOL_assign_list = 62,               /* assign_list  */
  YYSYMBOL_expression = 63,                /* expression  */
  YYSYMBOL_expression_list = 64,           /* expression_list  */
  YYSYMBOL_value = 65,                     /* value  */
  YYSYMBOL_var_value = 66,                 /* var_value  */
  YYSYMBOL_dim_list = 67,                  /* dim_list  */
  YYSYMBOL_movement = 68,                  /* movement  */
  YYSYMBOL_vardeclaration = 69,            /* vardeclaration  */
  YYSYMBOL_var_list = 70,                  /* var_list  */
  YYSYMBOL_onevar = 71,                    /* onevar  */
  YYSYMBOL_type = 72,                      /* type  */
  YYSYMBOL_dimensions = 73,                /* dimensions  */
  YYSYMBOL_dimension_list = 74,            /* dimension_list  */
  YYSYMBOL_values = 75,                    /* values  */
  YYSYMBOL_value_list = 76,                /* value_list  */
  YYSYMBOL_while_loop = 77,                /* while_loop  */
  YYSYMBOL_switch_statement = 78,          /* switch_statement  */
  YYSYMBOL_condition_list = 79,            /* condition_list  */
  YYSYMBOL_function_declaration = 80,      /* function_declaration  */
  YYSYMBOL_function_call = 81,             /* function_call  */
  YYSYMBOL_program_declaration = 82,       /* program_declaration  */
  YYSYMBOL_program_list = 83,              /* program_list  */
  YYSYMBOL_statement = 84,                 /* statement  */
  YYSYMBOL_statement_list = 85             /* statement_list  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   573

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  59
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  67
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  366

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   307


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    55,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      53,    56,    54,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    57,     2,    58,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    74,    74,    78,    81,    85,    87,    91,    92,   101,
     115,   120,   124,   133,   142,   147,   156,   165,   176,   179,
     183,   184,   185,   187,   191,   194,   195,   198,   199,   200,
     201,   202,   203,   207,   211,   212,   215,   234,   235,   236,
     242,   243,   257,   258,   263,   264,   268,   269,   273,   280,
     284,   289,   298,   302,   306,   310,   311,   312,   313,   317,
     318,   319,   320,   321,   322,   323,   327,   328
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "CBOOLEAN", "BOOLEAN",
  "NUMBER", "IDENTIFIER", "CELLEAN", "VAR", "ASSIGN", "LEFT", "RIGHT",
  "UP", "DOWN", "SENDDRONS", "GETDRONSCOUNT", "FUNC", "CALL", "PROGRAM",
  "VARDECLARATION", "TYPE", "DIMENSION", "VALUE", "CONST", "INT", "BOOL",
  "CELLL", "count", "DIM", "INDEX", "TO", "name", "WHILE", "CHECK", "DO",
  "SWITCH", "CONDITION", "angleVALUES", "angleVAR", "angleDIMENSIONS",
  "angleVARDECLARATION", "VALUES", "DIMENSIONS", "ADD", "SUB", "OR", "AND",
  "EQ", "MAX", "MIN", "NOT", "MUL", "DIV", "'<'", "'>'", "'/'", "'='",
  "'['", "']'", "$accept", "start", "assignment", "assign_list",
  "expression", "expression_list", "value", "var_value", "dim_list",
  "movement", "vardeclaration", "var_list", "onevar", "type", "dimensions",
  "dimension_list", "values", "value_list", "while_loop",
  "switch_statement", "condition_list", "function_declaration",
  "function_call", "program_declaration", "program_list", "statement",
  "statement_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-267)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -40,    -4,    23,  -267,   -26,  -267,    32,   -23,    36,  -267,
    -267,    60,  -267,     7,    -7,  -267,  -267,   -28,    10,    70,
      33,    50,  -267,   104,    71,   106,   111,    77,  -267,    57,
      79,  -267,   112,  -267,    -3,    78,  -267,  -267,  -267,   105,
     144,  -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,
    -267,   135,    84,    87,    88,    91,    92,    96,    97,   118,
     123,   124,   132,   143,   153,   156,   157,   158,   178,   203,
     206,   214,   216,   128,   115,   171,   192,    22,    22,    22,
      22,    22,   142,   265,   205,   219,    22,    22,    22,    22,
      22,    22,    22,    22,    22,    22,   220,   221,   270,   127,
     366,   224,   225,   226,   227,   228,   229,   232,   253,   254,
     235,  -267,    58,    22,    64,    69,    86,    90,    94,   236,
      99,    22,  -267,   238,   240,   251,   237,   262,   274,   275,
     277,   279,   280,   283,   284,   -25,   119,  -267,   255,   204,
     276,   314,   327,   340,   285,   353,   286,   321,  -267,   122,
     296,   331,   342,   330,   341,   352,   351,    22,   328,   326,
     358,   363,   339,   362,   373,   374,   372,   375,   376,   371,
     368,   377,     3,   170,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   389,   392,   390,   391,   393,   400,   394,
     395,   396,   397,   398,   399,   401,   378,    95,   406,   419,
     402,   403,  -267,  -267,  -267,  -267,  -267,  -267,  -267,   404,
     407,   413,  -267,  -267,   408,  -267,  -267,  -267,  -267,  -267,
    -267,  -267,   409,  -267,  -267,  -267,   411,   412,   414,   432,
     434,   427,    22,   415,  -267,  -267,   410,   417,  -267,   418,
     420,   421,   423,    22,   447,   442,   424,   425,   426,   428,
     429,   430,   431,   443,   450,   452,   448,   433,  -267,    22,
     435,   436,   437,   438,   454,   455,   440,   457,   457,  -267,
     444,   445,   469,   -17,   446,   -19,  -267,    39,     1,   464,
     449,   451,   456,   453,   471,   458,  -267,   459,   191,   461,
     470,   498,  -267,   497,   462,   476,   479,   480,  -267,   463,
     465,   467,   468,   472,   473,   474,   475,    11,  -267,  -267,
     -15,  -267,   466,   477,   478,  -267,   252,    17,   481,   482,
     388,   483,   484,   485,   489,   301,    12,    22,   487,   488,
     509,   515,   490,   492,   491,   493,   494,  -267,  -267,   495,
     496,   499,   500,    22,   501,   502,  -267,  -267,   503,   506,
     507,  -267,   510,   512,   508,   511,   513,   514,   517,   516,
    -267,  -267,   518,   519,  -267,  -267
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     2,     0,     1,     0,     0,     0,    56,
      55,     0,    34,     0,     0,    58,    57,     0,     0,     0,
       0,     0,    35,     0,     0,     0,     0,     0,    54,     0,
       0,    66,     0,    33,     0,     0,    21,    20,    22,     0,
       0,    59,    62,     7,    23,    61,    60,    63,    64,    65,
      67,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    18,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    52,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    19,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    25,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    27,    28,    29,    30,    31,    32,    53,     0,
       0,     0,    49,     8,     0,    15,    14,    12,    16,    17,
      13,    10,     0,    37,    38,    39,     0,     0,     0,     0,
       0,     0,     0,     0,     9,    11,     0,     0,    24,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    40,     0,
       0,     0,     0,     0,     0,    44,     0,     0,     0,    66,
       0,     0,     0,     0,     0,     0,     5,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     6,     0,     0,     0,
       0,     0,    46,     0,     0,     0,     0,     0,    66,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    66,    42,
       0,    36,     0,     0,     0,    48,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    45,    26,     0,
       0,     0,     0,     0,     0,     0,     4,     3,     0,     0,
       0,    41,     0,     0,     0,     0,     0,     0,     0,     0,
      47,    50,     0,     0,    51,    43
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -267,  -267,  -267,   160,   -34,   139,  -267,  -159,  -267,   416,
       6,  -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,
    -267,   522,  -267,  -267,  -267,  -267,  -266
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     2,    41,   275,   111,   112,    43,    44,   172,    45,
      46,    17,    22,   226,   265,   318,   273,   301,    47,    48,
     110,    10,    49,     3,    11,    50,    34
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      42,    36,    37,   278,    38,    36,    37,   319,    38,    13,
      20,   159,     9,     1,     4,    36,    37,    15,    38,    39,
     282,    36,    37,     5,    38,    21,    36,    37,     6,    38,
     160,    12,   307,   334,   285,    39,   283,     7,    18,    39,
     320,     7,   317,   101,   102,   103,   104,   105,    19,    39,
      40,     7,    13,   113,   288,    39,   198,     7,   199,   119,
      39,   121,    36,    37,   316,    38,    23,   335,    36,    37,
     325,    38,     7,    36,    37,   100,    38,    39,   137,   138,
     137,   137,   137,   137,   137,     8,   137,   146,    24,    25,
      36,    37,   287,    38,    36,    37,    39,    38,    36,    37,
       7,    38,    39,    36,    37,    26,    38,    39,   276,   276,
      27,   136,    29,    14,    32,   174,   286,   139,   286,   223,
     224,   225,   140,   183,    39,    28,    36,    37,    39,    38,
      30,    31,    39,    33,    51,    35,    52,    39,    74,   141,
      75,    76,    77,   142,    96,    78,    79,   143,   106,   125,
      80,    81,   145,    53,    54,    55,    56,    57,    58,    59,
      39,    60,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    82,    97,   161,   173,    61,    83,    84,    62,
      54,    55,    56,    57,    58,    59,    85,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    86,   242,    73,
      53,    54,    55,    56,    57,    58,    59,    87,    60,   250,
      88,    89,    90,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    61,    98,   266,    62,   114,   115,   116,
     117,   118,    91,   120,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    42,    99,   297,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    92,   108,   163,
      93,    53,    54,    55,    56,    57,    58,    59,    94,    60,
      95,   107,   109,    42,   122,   123,   124,   126,   127,   128,
     129,   130,   131,    42,    61,   132,   133,    62,   135,   144,
     134,   147,   150,   336,   148,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,   149,   176,   324,   162,   350,
      53,    54,    55,    56,    57,    58,    59,   151,    60,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,   152,
     153,   164,   154,    61,   155,   156,    62,   157,   158,   170,
     168,   171,   177,   179,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,   178,   180,   333,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,   181,   182,   165,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
     185,   184,   166,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,   186,   188,   167,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,   187,   189,   169,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,   190,
     192,   191,   195,   196,   193,   210,   194,   228,   277,   328,
     222,   197,   200,   201,   227,   202,   203,   204,   205,   206,
     207,   208,   209,   211,   214,   212,   233,   213,   215,   216,
     217,   218,   219,   220,   239,   221,   240,   229,   230,   231,
     241,   232,   234,   235,   236,   244,   237,   251,   238,   243,
     245,   252,   246,   260,   247,   248,   249,   253,   254,   255,
     261,   263,   257,   256,   258,   259,   262,   271,   264,   267,
     268,   269,   270,   274,   272,    39,   281,   279,   289,   280,
     294,   284,   290,   300,   299,   302,   304,   291,   293,   305,
     292,   329,   306,   295,   296,   298,   303,   308,   339,   309,
     310,   321,   311,   332,   340,   312,   342,   313,   314,   315,
     322,   323,   356,    16,   326,   344,   327,   363,     0,   330,
     331,   337,   338,     0,   341,   343,     0,   345,   357,   346,
     347,     0,   348,   362,   349,   351,     0,   352,   353,   354,
     355,     0,     0,   358,     0,   175,   359,   360,   361,     0,
       0,     0,   364,   365
};

static const yytype_int16 yycheck[] =
{
      34,     4,     5,   269,     7,     4,     5,    22,     7,    16,
      38,    36,     6,    53,    18,     4,     5,    11,     7,    38,
      37,     4,     5,     0,     7,    53,     4,     5,    54,     7,
      55,    54,   298,    21,    53,    38,    53,    40,    31,    38,
      55,    40,   308,    77,    78,    79,    80,    81,    55,    38,
      53,    40,    16,    87,    53,    38,    53,    40,    55,    93,
      38,    95,     4,     5,    53,     7,    56,    55,     4,     5,
      53,     7,    40,     4,     5,    53,     7,    38,   112,   113,
     114,   115,   116,   117,   118,    53,   120,   121,    18,    56,
       4,     5,    53,     7,     4,     5,    38,     7,     4,     5,
      40,     7,    38,     4,     5,    55,     7,    38,   267,   268,
       6,    53,     6,    53,    57,   149,   275,    53,   277,    24,
      25,    26,    53,   157,    38,    54,     4,     5,    38,     7,
      19,    54,    38,    54,    56,    23,    31,    38,     3,    53,
      56,    54,    54,    53,    16,    54,    54,    53,     6,    22,
      54,    54,    53,     9,    10,    11,    12,    13,    14,    15,
      38,    17,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    54,    58,    55,    53,    32,    54,    54,    35,
      10,    11,    12,    13,    14,    15,    54,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    54,   232,    55,
       9,    10,    11,    12,    13,    14,    15,    54,    17,   243,
      54,    54,    54,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    32,    53,   259,    35,    88,    89,    90,
      91,    92,    54,    94,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,   278,    53,    55,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    54,    53,    55,
      54,     9,    10,    11,    12,    13,    14,    15,    54,    17,
      54,     6,    53,   307,    54,    54,     6,    53,    53,    53,
      53,    53,    53,   317,    32,    53,    33,    35,    53,    53,
      36,    53,    55,   327,    54,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    54,    10,    55,    53,   343,
       9,    10,    11,    12,    13,    14,    15,    55,    17,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    55,
      55,    55,    55,    32,    55,    55,    35,    54,    54,    53,
      55,    20,    11,    13,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    12,    14,    55,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    15,    17,    55,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      54,    53,    55,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    35,    55,    55,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    43,    45,    55,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    46,
      48,    47,    51,    55,    49,    33,    50,     8,   268,    41,
      52,    54,    53,    53,    28,    54,    54,    54,    54,    54,
      54,    54,    53,    53,    44,    54,    33,    54,    54,    54,
      54,    54,    54,    54,    22,    54,    22,    55,    55,    55,
      33,    54,    54,    54,    53,    55,    54,    20,    54,    54,
      53,    29,    54,    30,    54,    54,    53,    53,    53,    53,
      30,    33,    53,    55,    54,    54,    34,    33,    55,    54,
      54,    54,    54,    53,    39,    38,    27,    53,    34,    54,
      29,    55,    53,     5,    34,     8,    30,    56,    55,    30,
      54,    28,    32,    55,    55,    54,    54,    54,     9,    54,
      53,    55,    54,    34,     9,    53,    34,    54,    54,    54,
      53,    53,    22,    11,    53,    42,    54,    21,    -1,    55,
      55,    54,    54,    -1,    54,    54,    -1,    53,    36,    54,
      54,    -1,    53,    36,    54,    54,    -1,    55,    55,    53,
      53,    -1,    -1,    55,    -1,   149,    55,    54,    54,    -1,
      -1,    -1,    54,    54
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    53,    60,    82,    18,     0,    54,    40,    53,    69,
      80,    83,    54,    16,    53,    69,    80,    70,    31,    55,
      38,    53,    71,    56,    18,    56,    55,     6,    54,     6,
      19,    54,    57,    54,    85,    23,     4,     5,     7,    38,
      53,    61,    63,    65,    66,    68,    69,    77,    78,    81,
      84,    56,    31,     9,    10,    11,    12,    13,    14,    15,
      17,    32,    35,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    55,     3,    56,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    16,    58,    53,    53,
      53,    63,    63,    63,    63,    63,     6,     6,    53,    53,
      79,    63,    64,    63,    64,    64,    64,    64,    64,    63,
      64,    63,    54,    54,     6,    22,    53,    53,    53,    53,
      53,    53,    53,    33,    36,    53,    53,    63,    63,    53,
      53,    53,    53,    53,    53,    53,    63,    53,    54,    54,
      55,    55,    55,    55,    55,    55,    55,    54,    54,    36,
      55,    55,    53,    55,    55,    55,    55,    55,    55,    55,
      53,    20,    67,    53,    63,    68,    10,    11,    12,    13,
      14,    15,    17,    63,    53,    54,    35,    43,    55,    45,
      46,    47,    48,    49,    50,    51,    55,    54,    53,    55,
      53,    53,    54,    54,    54,    54,    54,    54,    54,    53,
      33,    53,    54,    54,    44,    54,    54,    54,    54,    54,
      54,    54,    52,    24,    25,    26,    72,    28,     8,    55,
      55,    55,    54,    33,    54,    54,    53,    54,    54,    22,
      22,    33,    63,    54,    55,    53,    54,    54,    54,    53,
      63,    20,    29,    53,    53,    53,    55,    53,    54,    54,
      30,    30,    34,    33,    55,    73,    63,    54,    54,    54,
      54,    33,    39,    75,    53,    62,    66,    62,    85,    53,
      54,    27,    37,    53,    55,    53,    66,    53,    53,    34,
      53,    56,    54,    55,    29,    55,    55,    55,    54,    34,
       5,    76,     8,    54,    30,    30,    32,    85,    54,    54,
      53,    54,    53,    54,    54,    54,    53,    85,    74,    22,
      55,    55,    53,    53,    55,    53,    53,    54,    41,    28,
      55,    55,    34,    55,    21,    55,    63,    54,    54,     9,
       9,    54,    34,    54,    42,    53,    54,    54,    53,    54,
      63,    54,    55,    55,    53,    53,    22,    36,    55,    55,
      54,    54,    36,    21,    54,    54
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    59,    60,    61,    61,    62,    62,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    63,    64,    64,
      65,    65,    65,    65,    66,    67,    67,    68,    68,    68,
      68,    68,    68,    69,    70,    70,    71,    72,    72,    72,
      73,    73,    74,    74,    75,    75,    76,    76,    77,    78,
      79,    79,    80,    81,    82,    83,    83,    83,    83,    84,
      84,    84,    84,    84,    84,    84,    85,    85
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,    23,    23,     1,     2,     1,     8,     9,
       8,     9,     8,     8,     8,     8,     8,     8,     1,     2,
       1,     1,     1,     1,    10,     0,    16,     8,     8,     8,
       8,     8,     8,     7,     0,     2,    23,     1,     1,     1,
       0,    11,     0,     9,     0,     8,     0,     9,    19,     8,
      23,    24,    11,     8,     8,     1,     1,     2,     2,     1,
       1,     1,     1,     1,     1,     1,     0,     2
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* start: program_declaration  */
#line 74 "bisonpart.y"
                        { ProgramNodePerf((ProgramNode *)(yyvsp[0].node)); }
#line 1534 "bisonpart.tab.c"
    break;

  case 3: /* assignment: '<' ASSIGN '>' '<' VALUE '>' movement '<' '/' VALUE '>' '<' TO '>' assign_list '<' '/' TO '>' '<' '/' ASSIGN '>'  */
#line 78 "bisonpart.y"
                                                                                                                    {  (yyval.node) = new AssignNode((yyvsp[-16].node),*(yyvsp[-8].vecnode),yylineno); delete (yyvsp[-8].vecnode);
                                                                                                                            std::cout << "Assignment" << std::endl;
                                                                                                                            }
#line 1542 "bisonpart.tab.c"
    break;

  case 4: /* assignment: '<' ASSIGN '>' '<' VALUE '>' expression '<' '/' VALUE '>' '<' TO '>' assign_list '<' '/' TO '>' '<' '/' ASSIGN '>'  */
#line 81 "bisonpart.y"
                                                                                                                         {(yyval.node) = new AssignNode((yyvsp[-16].node),*(yyvsp[-8].vecnode),yylineno); delete (yyvsp[-8].vecnode);
                                                                                                                          std::cout << "Assignment" << std::endl;}
#line 1549 "bisonpart.tab.c"
    break;

  case 5: /* assign_list: var_value  */
#line 85 "bisonpart.y"
                {(yyval.vecnode) = new std::vector<Node*>();
                 (yyval.vecnode)->push_back((yyvsp[0].node));}
#line 1556 "bisonpart.tab.c"
    break;

  case 6: /* assign_list: assign_list var_value  */
#line 87 "bisonpart.y"
                              {(yyval.vecnode) = (yyvsp[-1].vecnode); (yyval.vecnode)->push_back((yyvsp[0].node));}
#line 1562 "bisonpart.tab.c"
    break;

  case 7: /* expression: value  */
#line 91 "bisonpart.y"
           {}
#line 1568 "bisonpart.tab.c"
    break;

  case 8: /* expression: '<' ADD '>' expression_list '<' '/' ADD '>'  */
#line 92 "bisonpart.y"
                                                  {
            //if ($3->size() < 2) {
            //    yyerror(yylineno, "Addition requires at least two operands");
            //    YYERROR;
            //}
            std::cout << "Addition with " << (yyvsp[-4].vecnode)->size() << " elements" << std::endl;
            (yyval.node) = new MultiOpNode(std::move(*(yyvsp[-4].vecnode)), add, yylineno);
            delete (yyvsp[-4].vecnode);  // Освобождаем память
        }
#line 1582 "bisonpart.tab.c"
    break;

  case 9: /* expression: '<' SUB '>' expression expression '<' '/' SUB '>'  */
#line 101 "bisonpart.y"
                                                        {
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
            (yyval.node) = new BinaryOpNode((yyvsp[-5].node), (yyvsp[-4].node), sub, yylineno);
        }
#line 1601 "bisonpart.tab.c"
    break;

  case 10: /* expression: '<' MUL '>' expression_list '<' '/' MUL '>'  */
#line 115 "bisonpart.y"
                                                  {
            std::cout << "Multiplication with " << (yyvsp[-4].vecnode)->size() << " elements" << std::endl;
            (yyval.node) = new MultiOpNode(std::move(*(yyvsp[-4].vecnode)), mul, yylineno);
            delete (yyvsp[-4].vecnode);  // Освобождаем память
        }
#line 1611 "bisonpart.tab.c"
    break;

  case 11: /* expression: '<' DIV '>' expression expression '<' '/' DIV '>'  */
#line 120 "bisonpart.y"
                                                        {
            std::cout << "Division" << std::endl;
            (yyval.node) = new BinaryOpNode((yyvsp[-5].node), (yyvsp[-4].node), divv, yylineno);
        }
#line 1620 "bisonpart.tab.c"
    break;

  case 12: /* expression: '<' EQ '>' expression_list '<' '/' EQ '>'  */
#line 124 "bisonpart.y"
                                                {
            //if ($3->size() < 2) {
            //    yyerror(yylineno, "Equality check requires at least two operands");
            //    YYERROR;
            //}
            std::cout << "Equality Check with " << (yyvsp[-4].vecnode)->size() << " elements" << std::endl;
            (yyval.node) = new MultiOpNode(std::move(*(yyvsp[-4].vecnode)), eq, yylineno);
            delete (yyvsp[-4].vecnode);  // Освобождаем память
        }
#line 1634 "bisonpart.tab.c"
    break;

  case 13: /* expression: '<' NOT '>' expression '<' '/' NOT '>'  */
#line 133 "bisonpart.y"
                                             {
            std::cout << "Logical NOT" << std::endl;
            //auto node = $3;
            //if(node->type == val && (ValueNode*)node->vartype == vcell){
            //        yyerror(yylineno, "arifmetic operations with cell...");
            //        YYERROR;
            //}
            (yyval.node) = new UnaryOpNode((yyvsp[-4].node), nott, yylineno);
        }
#line 1648 "bisonpart.tab.c"
    break;

  case 14: /* expression: '<' AND '>' expression_list '<' '/' AND '>'  */
#line 142 "bisonpart.y"
                                                  {
            std::cout << "Logical AND with " << (yyvsp[-4].vecnode)->size() << " elements" << std::endl;
            (yyval.node) = new MultiOpNode(std::move(*(yyvsp[-4].vecnode)), andd, yylineno);
            delete (yyvsp[-4].vecnode);  // Освобождаем память
        }
#line 1658 "bisonpart.tab.c"
    break;

  case 15: /* expression: '<' OR '>' expression_list '<' '/' OR '>'  */
#line 147 "bisonpart.y"
                                                {
            //if ($3->size() < 2) {
            //    yyerror(yylineno, "Logical OR requires at least two operands");
            //    YYERROR;
            //}
            std::cout << "Logical OR with " << (yyvsp[-4].vecnode)->size() << " elements" << std::endl;
            (yyval.node) = new MultiOpNode(std::move(*(yyvsp[-4].vecnode)), orr, yylineno);
            delete (yyvsp[-4].vecnode);  // Освобождаем память
        }
#line 1672 "bisonpart.tab.c"
    break;

  case 16: /* expression: '<' MAX '>' expression_list '<' '/' MAX '>'  */
#line 156 "bisonpart.y"
                                                  {
            //if ($3->size() < 2) {
            //    yyerror(yylineno, "Maximum requires at least two operands");
            //    YYERROR;
            //}
            std::cout << "Maximum with " << (yyvsp[-4].vecnode)->size() << " elements" << std::endl;
            (yyval.node) = new MultiOpNode(std::move(*(yyvsp[-4].vecnode)), maxx, yylineno);
            delete (yyvsp[-4].vecnode);  // Освобождаем память
        }
#line 1686 "bisonpart.tab.c"
    break;

  case 17: /* expression: '<' MIN '>' expression_list '<' '/' MIN '>'  */
#line 165 "bisonpart.y"
                                                  {
            //if ($3->size() < 2) {
            //    yyerror(yylineno, "Minimum requires at least two operands");
            //    YYERROR;
            //}
            std::cout << "Minimum with " << (yyvsp[-4].vecnode)->size() << " elements" << std::endl;
            (yyval.node) = new MultiOpNode(std::move(*(yyvsp[-4].vecnode)), minn, yylineno);
            delete (yyvsp[-4].vecnode);  // Освобождаем память
        }
#line 1700 "bisonpart.tab.c"
    break;

  case 18: /* expression_list: expression  */
#line 176 "bisonpart.y"
               { auto node = (yyvsp[0].node);
        (yyval.vecnode) = new std::vector<Node*>();
        (yyval.vecnode)->push_back((yyvsp[0].node)); }
#line 1708 "bisonpart.tab.c"
    break;

  case 19: /* expression_list: expression_list expression  */
#line 179 "bisonpart.y"
                                 {
        (yyval.vecnode) = (yyvsp[-1].vecnode); (yyval.vecnode)->push_back((yyvsp[0].node)); }
#line 1715 "bisonpart.tab.c"
    break;

  case 20: /* value: NUMBER  */
#line 183 "bisonpart.y"
           { /*std::cout << "show your way" << std::endl;*/ (yyval.node) = new ValueNode((yyvsp[0].number), yylineno); }
#line 1721 "bisonpart.tab.c"
    break;

  case 21: /* value: BOOLEAN  */
#line 184 "bisonpart.y"
              { (yyval.node) = new ValueNode((yyvsp[0].boolean), yylineno); }
#line 1727 "bisonpart.tab.c"
    break;

  case 22: /* value: CELLEAN  */
#line 185 "bisonpart.y"
              { (yyval.node) = new ValueNode((yyvsp[0].cell), yylineno); }
#line 1733 "bisonpart.tab.c"
    break;

  case 23: /* value: var_value  */
#line 187 "bisonpart.y"
                {(yyval.node) = (yyvsp[0].node);}
#line 1739 "bisonpart.tab.c"
    break;

  case 24: /* var_value: angleVAR name '=' '<' IDENTIFIER '>' dim_list '/' VAR '>'  */
#line 191 "bisonpart.y"
                                                              {(yyval.node) = new ValueNode(*(yyvsp[-5].text), *(yyvsp[-3].vecnode), yylineno); delete (yyvsp[-3].vecnode); delete (yyvsp[-5].text); }
#line 1745 "bisonpart.tab.c"
    break;

  case 25: /* dim_list: %empty  */
#line 194 "bisonpart.y"
                                        { (yyval.vecnode) = new std::vector<Node *>(); }
#line 1751 "bisonpart.tab.c"
    break;

  case 26: /* dim_list: dim_list '<' DIM '>' '<' INDEX '>' expression '<' '/' INDEX '>' '<' '/' DIM '>'  */
#line 195 "bisonpart.y"
                                                                                          { (yyval.vecnode) = (yyvsp[-15].vecnode); (yyval.vecnode)->push_back((yyvsp[-8].node)); }
#line 1757 "bisonpart.tab.c"
    break;

  case 27: /* movement: '<' LEFT '>' expression '<' '/' LEFT '>'  */
#line 198 "bisonpart.y"
                                             { /*std::cout << "Move Left" << std::endl;*/ (yyval.node) = new MoveNode(left,&robot, yylineno, (yyvsp[-4].node)); }
#line 1763 "bisonpart.tab.c"
    break;

  case 28: /* movement: '<' RIGHT '>' expression '<' '/' RIGHT '>'  */
#line 199 "bisonpart.y"
                                                 { /*std::cout << "Move Right" << std::endl;*/ (yyval.node) = new MoveNode(right,&robot, yylineno, (yyvsp[-4].node)); }
#line 1769 "bisonpart.tab.c"
    break;

  case 29: /* movement: '<' UP '>' expression '<' '/' UP '>'  */
#line 200 "bisonpart.y"
                                           { /*std::cout << "Move Up" << std::endl;*/ (yyval.node) = new MoveNode(up,&robot, yylineno, (yyvsp[-4].node));}
#line 1775 "bisonpart.tab.c"
    break;

  case 30: /* movement: '<' DOWN '>' expression '<' '/' DOWN '>'  */
#line 201 "bisonpart.y"
                                               { /*std::cout << "Move Down" << std::endl;*/ (yyval.node) = new MoveNode(down,&robot, yylineno, (yyvsp[-4].node)); }
#line 1781 "bisonpart.tab.c"
    break;

  case 31: /* movement: '<' SENDDRONS '>' expression '<' '/' SENDDRONS '>'  */
#line 202 "bisonpart.y"
                                                         { /*std::cout << "Move SendDrons" << std::endl;*/ (yyval.node) = new MoveNode(senddrones,&robot, yylineno, (yyvsp[-4].node)); }
#line 1787 "bisonpart.tab.c"
    break;

  case 32: /* movement: '<' GETDRONSCOUNT '>' IDENTIFIER '<' '/' GETDRONSCOUNT '>'  */
#line 203 "bisonpart.y"
                                                                  {  (yyval.node) = new MoveNode(getdrones,&robot, yylineno, *(yyvsp[-4].text)); delete (yyvsp[-4].text); }
#line 1793 "bisonpart.tab.c"
    break;

  case 33: /* vardeclaration: angleVARDECLARATION '>' var_list '<' '/' VARDECLARATION '>'  */
#line 207 "bisonpart.y"
                                                                 { (yyval.node) = new Vardecl(*(yyvsp[-4].vecnode), yylineno); delete (yyvsp[-4].vecnode); std::cout << "Variable Declaration" << std::endl; }
#line 1799 "bisonpart.tab.c"
    break;

  case 34: /* var_list: %empty  */
#line 211 "bisonpart.y"
                                      { std::cout << "chop chop" << std::endl; (yyval.vecnode) = new std::vector<Node *>();}
#line 1805 "bisonpart.tab.c"
    break;

  case 35: /* var_list: var_list onevar  */
#line 212 "bisonpart.y"
                     { (yyval.vecnode) = (yyvsp[-1].vecnode); (yyval.vecnode)->push_back((yyvsp[0].node)); }
#line 1811 "bisonpart.tab.c"
    break;

  case 36: /* onevar: angleVAR '=' IDENTIFIER '[' CONST '=' CBOOLEAN ']' '>' '<' TYPE '>' type '<' '/' TYPE '>' dimensions values '<' '/' VAR '>'  */
#line 215 "bisonpart.y"
                                                                                                                                {
       // произведение всех измерений dimensions
        /*std::cout << "chap chap" << std::endl;*/
        Vartype vart;
        if (*(yyvsp[-10].text) == "INT") {
            vart = vint;
        } else if (*(yyvsp[-10].text) == "BOOL") {
            vart = vbool;
        } else if (*(yyvsp[-10].text) == "CELL") {
            vart = vcell;
        }
        (yyval.node) = new VardecNode(vart,*(yyvsp[-20].text), (yyvsp[-16].boolean), *(yyvsp[-5].vecnode), *(yyvsp[-4].vecnode), yylineno);
        delete (yyvsp[-10].text);
        delete (yyvsp[-20].text);
        delete (yyvsp[-5].vecnode);
        delete (yyvsp[-4].vecnode);
    }
#line 1833 "bisonpart.tab.c"
    break;

  case 37: /* type: INT  */
#line 234 "bisonpart.y"
        { (yyval.text) = new std::string("INT"); }
#line 1839 "bisonpart.tab.c"
    break;

  case 38: /* type: BOOL  */
#line 235 "bisonpart.y"
           { (yyval.text) = new std::string("BOOL"); }
#line 1845 "bisonpart.tab.c"
    break;

  case 39: /* type: CELLL  */
#line 236 "bisonpart.y"
            { (yyval.text) = new std::string("CELL"); }
#line 1851 "bisonpart.tab.c"
    break;

  case 40: /* dimensions: %empty  */
#line 242 "bisonpart.y"
                                       { /*std::cout << "chipI chipI" << std::endl;*/ (yyval.vecnode) = new std::vector<Node *>(); }
#line 1857 "bisonpart.tab.c"
    break;

  case 41: /* dimensions: dimensions angleDIMENSIONS count '=' NUMBER '>' dimension_list '<' '/' DIMENSIONS '>'  */
#line 243 "bisonpart.y"
                                                                                             {
     std::cout << "chip chip" << std::endl;
     if((yyvsp[-4].vecnode)->size() != (yyvsp[-6].number)){
     //   myyyerror("Dimensions count != dimensions");
        std::cout << "Dimensions count != dimensions" << std::endl;
        YYERROR;
     }
     delete (yyvsp[-10].vecnode);
     (yyval.vecnode) = (yyvsp[-4].vecnode); // num 0 и dim нет - подходит
          std::cout << "chip chip" << std::endl;
     }
#line 1873 "bisonpart.tab.c"
    break;

  case 42: /* dimension_list: %empty  */
#line 257 "bisonpart.y"
    { (yyval.vecnode) = new std::vector<Node *>(); }
#line 1879 "bisonpart.tab.c"
    break;

  case 43: /* dimension_list: dimension_list '<' DIMENSION '>' expression '<' '/' DIMENSION '>'  */
#line 258 "bisonpart.y"
                                                                        { (yyval.vecnode) = (yyvsp[-8].vecnode); (yyval.vecnode)->push_back((yyvsp[-4].node)); }
#line 1885 "bisonpart.tab.c"
    break;

  case 44: /* values: %empty  */
#line 263 "bisonpart.y"
    { (yyval.vecnode) = new std::vector<Node*>(); std::cout << "chup chup " << std::endl; }
#line 1891 "bisonpart.tab.c"
    break;

  case 45: /* values: values angleVALUES '>' value_list '<' '/' VALUES '>'  */
#line 264 "bisonpart.y"
                                                           { delete (yyvsp[-7].vecnode); (yyval.vecnode) = (yyvsp[-4].vecnode); }
#line 1897 "bisonpart.tab.c"
    break;

  case 46: /* value_list: %empty  */
#line 268 "bisonpart.y"
                                       { std::cout << "chup chup " << std::endl; (yyval.vecnode) = new std::vector<Node*>(); }
#line 1903 "bisonpart.tab.c"
    break;

  case 47: /* value_list: value_list '<' VALUE '>' expression '<' '/' VALUE '>'  */
#line 269 "bisonpart.y"
                                                            { (yyval.vecnode) = (yyvsp[-8].vecnode); (yyval.vecnode)->push_back((yyvsp[-4].node)); }
#line 1909 "bisonpart.tab.c"
    break;

  case 48: /* while_loop: '<' WHILE '>' '<' CHECK '>' expression '<' '/' CHECK '>' '<' DO '>' statement_list '<' '/' WHILE '>'  */
#line 273 "bisonpart.y"
                                                                                                         { std::cout << "While Loop" << std::endl;
                                                                                                          (yyval.node) = new WhileNode((yyvsp[-12].node),*(yyvsp[-4].vecnode), yylineno);
                                                                                                          delete (yyvsp[-4].vecnode);  // Освобождаем память
                                                                                                           }
#line 1918 "bisonpart.tab.c"
    break;

  case 49: /* switch_statement: '<' SWITCH '>' condition_list '<' '/' SWITCH '>'  */
#line 280 "bisonpart.y"
                                                     { (yyval.node) = (yyvsp[-4].node); std::cout << "Switch Statement" << std::endl; }
#line 1924 "bisonpart.tab.c"
    break;

  case 50: /* condition_list: '<' CONDITION '>' '<' CHECK '>' expression '<' '/' CHECK '>' '<' DO '>' statement_list '<' '/' DO '>' '<' '/' CONDITION '>'  */
#line 284 "bisonpart.y"
                                                                                                                                { (yyval.node) = new SwitchNode(yylineno);
                                                                                                                                 ((SwitchNode *)(yyval.node))->expressions.push_back((yyvsp[-16].node));
                                                                                                                                 ((SwitchNode *)(yyval.node))->groups_statements.push_back(*(yyvsp[-8].vecnode));
                                                                                                                                 delete (yyvsp[-8].vecnode);
                                                                                                                                 }
#line 1934 "bisonpart.tab.c"
    break;

  case 51: /* condition_list: condition_list '<' CONDITION '>' '<' CHECK '>' expression '<' '/' CHECK '>' '<' DO '>' statement_list '<' '/' DO '>' '<' '/' CONDITION '>'  */
#line 289 "bisonpart.y"
                                                                                                                                                  {
                                                                                                                                 (yyval.node) = (yyvsp[-23].node);
                                                                                                                                 ((SwitchNode *)(yyval.node))->expressions.push_back((yyvsp[-16].node));
                                                                                                                                 ((SwitchNode *)(yyval.node))->groups_statements.push_back(*(yyvsp[-8].vecnode));
                                                                                                                                 delete (yyvsp[-8].vecnode);
                                                                                                                                 }
#line 1945 "bisonpart.tab.c"
    break;

  case 52: /* function_declaration: '<' FUNC name '=' IDENTIFIER '>' statement_list '<' '/' FUNC '>'  */
#line 298 "bisonpart.y"
                                                                     { (yyval.node) = new FunctionNode(*(yyvsp[-6].text), *(yyvsp[-4].vecnode), yylineno); delete (yyvsp[-4].vecnode); delete (yyvsp[-6].text); std::cout << "Function Declaration" << std::endl; }
#line 1951 "bisonpart.tab.c"
    break;

  case 53: /* function_call: '<' CALL '>' IDENTIFIER '<' '/' CALL '>'  */
#line 302 "bisonpart.y"
                                             { (yyval.node) = new FunctionCNode(*(yyvsp[-4].text), yylineno); delete (yyvsp[-4].text); }
#line 1957 "bisonpart.tab.c"
    break;

  case 54: /* program_declaration: '<' PROGRAM '>' program_list '<' '/' PROGRAM '>'  */
#line 306 "bisonpart.y"
                                                     { (yyval.node) = (yyvsp[-4].node); std::cout << "Program Declaration" << std::endl; }
#line 1963 "bisonpart.tab.c"
    break;

  case 55: /* program_list: function_declaration  */
#line 310 "bisonpart.y"
                         {(yyval.node) = new ProgramNode(yylineno); ((ProgramNode *)(yyval.node))->declarations.push_back((yyvsp[0].node));}
#line 1969 "bisonpart.tab.c"
    break;

  case 56: /* program_list: vardeclaration  */
#line 311 "bisonpart.y"
                     {(yyval.node) = new ProgramNode(yylineno); ((ProgramNode *)(yyval.node))->declarations.push_back((yyvsp[0].node));}
#line 1975 "bisonpart.tab.c"
    break;

  case 57: /* program_list: program_list function_declaration  */
#line 312 "bisonpart.y"
                                        {(yyval.node) = (yyvsp[-1].node); ((ProgramNode *)(yyval.node))->declarations.push_back((yyvsp[0].node));}
#line 1981 "bisonpart.tab.c"
    break;

  case 58: /* program_list: program_list vardeclaration  */
#line 313 "bisonpart.y"
                                  {(yyval.node) = (yyvsp[-1].node); ((ProgramNode *)(yyval.node))->declarations.push_back((yyvsp[0].node));}
#line 1987 "bisonpart.tab.c"
    break;

  case 66: /* statement_list: %empty  */
#line 327 "bisonpart.y"
                                    { /*std::cout << "I wanna see " << std::endl;*/ (yyval.vecnode) = new std::vector<Node *>();}
#line 1993 "bisonpart.tab.c"
    break;

  case 67: /* statement_list: statement_list statement  */
#line 328 "bisonpart.y"
                               { /*std::cout << "I wanna see again " << std::endl;*/ (yyval.vecnode) = (yyvsp[-1].vecnode); (yyval.vecnode)->push_back((yyvsp[0].node)); }
#line 1999 "bisonpart.tab.c"
    break;


#line 2003 "bisonpart.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 331 "bisonpart.y"

void yyerror(const char *s) {
}
//void myyyerror(const YYLTYPE* loc, const char* s) {
//    std::cerr << "Error: " << s << " at line " << loc->first_line << ", column " << loc->first_column << std::endl;
//}
