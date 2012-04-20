/* A Bison parser, made by GNU Bison 2.4.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006,
   2009, 2010 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "dmlyacc.yxx"

#include <CSql.h>
#include <stdlib.h>
#include "Parser.h"

class Predicate;
ParsedData *parsedData;
extern char yytext[];
int yylex( void );
void yyerror(const char* Msg);


/* Line 189 of yacc.c  */
#line 85 "dmlyacc.cxx"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     OR = 258,
     AND = 259,
     UMINUS = 260,
     STRING = 261,
     FIELD = 262,
     NUMBER_STRING = 263,
     BINARY_STRING = 264,
     DOUBLE = 265,
     OPERATOR = 266,
     PARAMETER = 267,
     ALLTABLE = 268,
     DESCRIBE = 269,
     PRIMARYINFO = 270,
     AUTO_INCREMENT = 271,
     GETCATALOGS = 272,
     GETDATATYPES = 273,
     GETTABLETYPES = 274,
     IMPORTEDKEY = 275,
     EXPORTEDKEY = 276,
     SELECT = 277,
     FROM = 278,
     WHERE = 279,
     BETWEEN = 280,
     IN = 281,
     NOT = 282,
     AS = 283,
     LIMIT = 284,
     OFFSET = 285,
     INNER = 286,
     OUTER = 287,
     CROSS = 288,
     JOIN = 289,
     LEFT = 290,
     IS = 291,
     INSERT = 292,
     INTO = 293,
     VALUES = 294,
     EXPLAIN = 295,
     PLAN = 296,
     DELETE = 297,
     UPDATE = 298,
     SET = 299,
     NULL_VALUE = 300,
     CREATE = 301,
     TABLE = 302,
     PRIMARY = 303,
     KEY = 304,
     DEFAULT = 305,
     INDEX = 306,
     ON = 307,
     HASH = 308,
     TREE = 309,
     TRIE = 310,
     UNIQUE = 311,
     DROP = 312,
     SIZE = 313,
     FOREIGN = 314,
     REFERENCES = 315,
     COMPACT = 316,
     TRUNCATE = 317,
     CACHE = 318,
     CONDITION = 319,
     FIELDLIST = 320,
     PK = 321,
     DIRECT = 322,
     DSN = 323,
     UNCACHE = 324,
     NOSCHEMA = 325,
     INT_TYPE = 326,
     LONG_TYPE = 327,
     SHORT_TYPE = 328,
     DOUBLE_TYPE = 329,
     TIMESTAMP_TYPE = 330,
     DATE_TYPE = 331,
     CHAR_TYPE = 332,
     TIME_TYPE = 333,
     BIGINT_TYPE = 334,
     FLOAT_TYPE = 335,
     TINYINT_TYPE = 336,
     BINARY_TYPE = 337,
     VARCHAR_TYPE = 338,
     DATE_DIFF = 339,
     DATE_ADD = 340,
     DATE_SUB = 341,
     HOUR = 342,
     MINUTE = 343,
     SECOND = 344,
     YEAR = 345,
     MONTH = 346,
     DAY = 347,
     INTERVAL = 348,
     TIME_DIFF = 349,
     TIME_ADD = 350,
     TIME_SUB = 351,
     TIMESTAMP_DIFF = 352,
     TIMESTAMP_ADD = 353,
     TIMESTAMP_SUB = 354,
     EXTRACT = 355,
     NOW = 356,
     USER = 357,
     PASSWORD = 358,
     ALTER = 359,
     FLUSH = 360,
     ADD = 361,
     COLUMN = 362,
     MODIFY = 363,
     RENAME = 364,
     TO = 365,
     GRANT = 366,
     RESTRICT = 367,
     REVOKE = 368,
     MIN = 369,
     MAX = 370,
     AVG = 371,
     SUM = 372,
     COUNT = 373,
     GROUP = 374,
     BY = 375,
     HAVING = 376,
     ORDER = 377,
     ASC = 378,
     DESC = 379,
     DISTINCT = 380
   };
#endif
/* Tokens.  */
#define OR 258
#define AND 259
#define UMINUS 260
#define STRING 261
#define FIELD 262
#define NUMBER_STRING 263
#define BINARY_STRING 264
#define DOUBLE 265
#define OPERATOR 266
#define PARAMETER 267
#define ALLTABLE 268
#define DESCRIBE 269
#define PRIMARYINFO 270
#define AUTO_INCREMENT 271
#define GETCATALOGS 272
#define GETDATATYPES 273
#define GETTABLETYPES 274
#define IMPORTEDKEY 275
#define EXPORTEDKEY 276
#define SELECT 277
#define FROM 278
#define WHERE 279
#define BETWEEN 280
#define IN 281
#define NOT 282
#define AS 283
#define LIMIT 284
#define OFFSET 285
#define INNER 286
#define OUTER 287
#define CROSS 288
#define JOIN 289
#define LEFT 290
#define IS 291
#define INSERT 292
#define INTO 293
#define VALUES 294
#define EXPLAIN 295
#define PLAN 296
#define DELETE 297
#define UPDATE 298
#define SET 299
#define NULL_VALUE 300
#define CREATE 301
#define TABLE 302
#define PRIMARY 303
#define KEY 304
#define DEFAULT 305
#define INDEX 306
#define ON 307
#define HASH 308
#define TREE 309
#define TRIE 310
#define UNIQUE 311
#define DROP 312
#define SIZE 313
#define FOREIGN 314
#define REFERENCES 315
#define COMPACT 316
#define TRUNCATE 317
#define CACHE 318
#define CONDITION 319
#define FIELDLIST 320
#define PK 321
#define DIRECT 322
#define DSN 323
#define UNCACHE 324
#define NOSCHEMA 325
#define INT_TYPE 326
#define LONG_TYPE 327
#define SHORT_TYPE 328
#define DOUBLE_TYPE 329
#define TIMESTAMP_TYPE 330
#define DATE_TYPE 331
#define CHAR_TYPE 332
#define TIME_TYPE 333
#define BIGINT_TYPE 334
#define FLOAT_TYPE 335
#define TINYINT_TYPE 336
#define BINARY_TYPE 337
#define VARCHAR_TYPE 338
#define DATE_DIFF 339
#define DATE_ADD 340
#define DATE_SUB 341
#define HOUR 342
#define MINUTE 343
#define SECOND 344
#define YEAR 345
#define MONTH 346
#define DAY 347
#define INTERVAL 348
#define TIME_DIFF 349
#define TIME_ADD 350
#define TIME_SUB 351
#define TIMESTAMP_DIFF 352
#define TIMESTAMP_ADD 353
#define TIMESTAMP_SUB 354
#define EXTRACT 355
#define NOW 356
#define USER 357
#define PASSWORD 358
#define ALTER 359
#define FLUSH 360
#define ADD 361
#define COLUMN 362
#define MODIFY 363
#define RENAME 364
#define TO 365
#define GRANT 366
#define RESTRICT 367
#define REVOKE 368
#define MIN 369
#define MAX 370
#define AVG 371
#define SUM 372
#define COUNT 373
#define GROUP 374
#define BY 375
#define HAVING 376
#define ORDER 377
#define ASC 378
#define DESC 379
#define DISTINCT 380




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 15 "dmlyacc.yxx"

   char *stringval;
   void *predicate;
   void *Expression;
   void *FunctionType;



/* Line 214 of yacc.c  */
#line 380 "dmlyacc.cxx"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 392 "dmlyacc.cxx"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  71
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   816

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  136
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  98
/* YYNRULES -- Number of rules.  */
#define YYNRULES  270
/* YYNRULES -- Number of states.  */
#define YYNSTATES  611

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   380

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     9,     2,     2,
     133,   134,     7,     5,   132,     6,     2,     8,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,   131,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,   135,     2,     2,     2,
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
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    11,    13,    15,    17,
      19,    21,    23,    25,    27,    29,    38,    46,    55,    62,
      72,    80,    84,    91,    96,   104,   107,   109,   112,   114,
     116,   118,   120,   124,   125,   134,   150,   166,   170,   172,
     175,   179,   182,   184,   186,   188,   191,   194,   207,   210,
     211,   213,   214,   217,   219,   222,   224,   228,   231,   233,
     236,   243,   251,   256,   257,   258,   260,   261,   263,   266,
     276,   277,   281,   284,   286,   289,   292,   294,   297,   303,
     310,   312,   313,   316,   318,   321,   325,   329,   333,   337,
     341,   345,   349,   353,   357,   360,   363,   365,   367,   374,
     382,   390,   397,   405,   413,   422,   430,   438,   445,   450,
     455,   457,   459,   461,   463,   465,   467,   469,   471,   473,
     475,   477,   480,   481,   485,   486,   490,   491,   494,   499,
     500,   503,   504,   507,   509,   512,   514,   517,   519,   522,
     524,   527,   530,   534,   538,   542,   547,   550,   554,   558,
     562,   567,   570,   577,   584,   591,   598,   605,   609,   613,
     620,   627,   632,   636,   640,   644,   648,   650,   651,   653,
     657,   660,   662,   667,   672,   677,   682,   687,   692,   694,
     697,   699,   703,   705,   707,   709,   711,   713,   715,   719,
     721,   724,   727,   729,   732,   735,   741,   746,   753,   754,
     757,   758,   761,   762,   765,   766,   768,   769,   772,   773,
     775,   783,   796,   800,   804,   809,   810,   813,   816,   819,
     820,   821,   823,   825,   826,   827,   830,   832,   836,   839,
     841,   844,   846,   853,   855,   856,   860,   861,   864,   865,
     868,   870,   872,   876,   879,   881,   884,   895,   898,   900,
     903,   905,   908,   910,   913,   915,   922,   923,   925,   927,
     929,   931,   933,   935,   937,   939,   941,   943,   945,   947,
     949
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     137,     0,    -1,   149,    -1,   160,    -1,   166,    -1,   167,
      -1,   208,    -1,   147,    -1,   200,    -1,   146,    -1,   140,
      -1,   145,    -1,   139,    -1,   138,    -1,   148,    -1,   109,
      52,   196,   111,   133,   212,   134,   168,    -1,   109,    52,
     196,    62,   112,   196,   168,    -1,   109,    52,   196,   113,
     133,   215,   134,   168,    -1,   114,    52,   196,   115,   196,
     168,    -1,   109,    52,   196,   114,   112,   196,   115,   196,
     168,    -1,   109,    56,   196,   114,   115,   196,   168,    -1,
     110,    68,   168,    -1,    51,   107,   196,   108,    11,   168,
      -1,    62,   107,   196,   168,    -1,   109,   107,   196,    49,
     108,    11,   168,    -1,   141,   142,    -1,   143,    -1,   132,
     143,    -1,    27,    -1,    42,    -1,    48,    -1,    47,    -1,
     117,   115,   189,    -1,    -1,   116,   141,    57,   196,   115,
     196,   144,   168,    -1,    51,    52,   196,    33,    27,   151,
     152,    28,   155,   178,   179,   182,   180,   181,   168,    -1,
      42,    43,   196,    33,    27,   151,   152,    28,   155,   178,
     179,   182,   180,   181,   168,    -1,    66,    52,   196,    -1,
      18,    -1,    19,   194,    -1,    19,    56,   194,    -1,    20,
     194,    -1,    22,    -1,    24,    -1,    23,    -1,    25,   194,
      -1,    26,   194,    -1,   150,    27,   151,   152,    28,   155,
     178,   179,   182,   180,   181,   168,    -1,    45,    46,    -1,
      -1,   130,    -1,    -1,   152,   153,    -1,   154,    -1,   132,
     154,    -1,   195,    -1,   195,    33,   196,    -1,   155,   159,
      -1,   194,    -1,   194,   156,    -1,    36,   158,   194,    57,
     189,   156,    -1,    40,   157,   158,   194,    57,   189,   156,
      -1,    38,   158,   194,   156,    -1,    -1,    -1,    37,    -1,
      -1,    39,    -1,   132,   194,    -1,    42,    43,   196,   161,
      44,   133,   162,   134,   168,    -1,    -1,   133,   152,   134,
      -1,   162,   163,    -1,   197,    -1,   132,   197,    -1,   164,
     165,    -1,   197,    -1,   132,   197,    -1,    47,    28,   196,
     178,   168,    -1,    48,   196,    49,   169,   178,   168,    -1,
     131,    -1,    -1,   169,   170,    -1,   171,    -1,   132,   171,
      -1,   196,    16,   172,    -1,   196,    16,   197,    -1,   196,
      16,    50,    -1,   172,     8,   172,    -1,   172,     9,   172,
      -1,   172,     7,   172,    -1,   172,     5,   172,    -1,   172,
       6,   172,    -1,   133,   172,   134,    -1,     6,   172,    -1,
       5,   172,    -1,   173,    -1,   177,    -1,    89,   133,   177,
     132,   177,   134,    -1,    90,   133,   177,    98,   177,   176,
     134,    -1,    91,   133,   177,    98,   177,   176,   134,    -1,
      99,   133,   177,   132,   177,   134,    -1,   100,   133,   177,
      98,   177,   175,   134,    -1,   101,   133,   177,    98,   177,
     175,   134,    -1,   102,   133,   174,   132,   177,   132,   177,
     134,    -1,   103,   133,   177,    98,   177,   174,   134,    -1,
     104,   133,   177,    98,   177,   174,   134,    -1,   105,   133,
     174,    28,   177,   134,    -1,    81,   133,   177,   134,    -1,
      83,   133,   177,   134,    -1,   175,    -1,   176,    -1,    92,
      -1,    93,    -1,    94,    -1,    95,    -1,    96,    -1,    97,
      -1,   196,    -1,   197,    -1,    50,    -1,    29,   189,    -1,
      -1,   124,   125,   183,    -1,    -1,   127,   125,   186,    -1,
      -1,    34,    13,    -1,    34,    13,    35,    13,    -1,    -1,
     126,   190,    -1,    -1,   183,   184,    -1,   185,    -1,   132,
     185,    -1,   196,    -1,   186,   187,    -1,   188,    -1,   132,
     188,    -1,   196,    -1,   196,   128,    -1,   196,   129,    -1,
     189,     3,   189,    -1,   189,     4,   189,    -1,   133,   189,
     134,    -1,    32,   133,   189,   134,    -1,   193,   192,    -1,
     190,     3,   190,    -1,   190,     4,   190,    -1,   133,   190,
     134,    -1,    32,   133,   190,   134,    -1,   193,   191,    -1,
     119,   133,   196,   134,    16,   197,    -1,   120,   133,   196,
     134,    16,   197,    -1,   122,   133,   196,   134,    16,   197,
      -1,   121,   133,   196,   134,    16,   197,    -1,   123,   133,
     196,   134,    16,   197,    -1,   196,    16,   197,    -1,   196,
      16,   196,    -1,   196,   193,    30,   197,     4,   197,    -1,
     196,   193,    31,   133,   164,   134,    -1,   196,    41,    32,
      50,    -1,   196,    41,    50,    -1,   173,    16,   173,    -1,
     173,    16,   196,    -1,   173,    16,   197,    -1,    32,    -1,
      -1,   196,    -1,   196,    33,   196,    -1,   196,   196,    -1,
     196,    -1,   119,   133,   196,   134,    -1,   120,   133,   196,
     134,    -1,   122,   133,   196,   134,    -1,   121,   133,   196,
     134,    -1,   123,   133,   196,   134,    -1,   123,   133,     7,
     134,    -1,     7,    -1,   196,     7,    -1,    12,    -1,   135,
      12,   135,    -1,    11,    -1,   198,    -1,    14,    -1,   199,
      -1,    17,    -1,    50,    -1,   106,   133,   134,    -1,    13,
      -1,     6,    13,    -1,     5,    13,    -1,    15,    -1,     6,
      15,    -1,     5,    15,    -1,    68,    52,   196,   201,   168,
      -1,    74,    52,   196,   168,    -1,   202,   203,   204,   205,
     206,   207,    -1,    -1,    69,   197,    -1,    -1,    70,   197,
      -1,    -1,    71,   196,    -1,    -1,    72,    -1,    -1,    73,
     197,    -1,    -1,    75,    -1,    51,    52,   196,   133,   212,
     134,   168,    -1,    51,    56,   196,    57,   196,   133,   152,
     134,   210,   209,   211,   168,    -1,    62,    52,   196,    -1,
      62,    56,   196,    -1,    67,    52,   196,   168,    -1,    -1,
      58,   210,    -1,    59,   210,    -1,    60,   210,    -1,    -1,
      -1,    61,    -1,    53,    -1,    -1,    -1,    63,    13,    -1,
     213,    -1,   213,   132,   221,    -1,   213,   214,    -1,   215,
      -1,   132,   215,    -1,   216,    -1,   217,   233,   218,   220,
     219,   232,    -1,   196,    -1,    -1,   133,    13,   134,    -1,
      -1,    55,   197,    -1,    -1,    32,    50,    -1,   231,    -1,
     222,    -1,   231,   132,   222,    -1,   222,   223,    -1,   224,
      -1,   132,   224,    -1,    64,    54,   133,   225,   134,    65,
     196,   133,   228,   134,    -1,   225,   226,    -1,   227,    -1,
     132,   227,    -1,   196,    -1,   228,   229,    -1,   230,    -1,
     132,   230,    -1,   196,    -1,    53,    54,   133,   152,   134,
     211,    -1,    -1,    21,    -1,    76,    -1,    77,    -1,    78,
      -1,    84,    -1,    86,    -1,    85,    -1,    79,    -1,    81,
      -1,    83,    -1,    80,    -1,    82,    -1,    88,    -1,    87,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    44,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    58,    65,    73,    79,    88,
      97,   106,   111,   118,   124,   132,   133,   135,   137,   137,
     137,   137,   142,   143,   145,   159,   166,   173,   180,   185,
     190,   196,   201,   206,   211,   216,   221,   227,   233,   237,
     239,   243,   245,   246,   248,   250,   251,   257,   258,   259,
     261,   275,   288,   292,   294,   295,   297,   298,   300,   306,
     314,   315,   318,   319,   325,   332,   333,   339,   346,   354,
     362,   363,   366,   367,   370,   372,   377,   382,   388,   394,
     400,   406,   412,   418,   422,   426,   430,   431,   433,   440,
     447,   455,   462,   469,   476,   487,   494,   501,   513,   521,
     529,   534,   540,   545,   550,   556,   561,   566,   572,   579,
     587,   596,   609,   611,   612,   614,   615,   617,   621,   625,
     627,   628,   630,   631,   633,   635,   641,   642,   644,   646,
     651,   656,   662,   670,   677,   678,   686,   702,   710,   717,
     718,   726,   742,   751,   760,   769,   778,   789,   800,   811,
     827,   853,   861,   869,   877,   887,   896,   900,   902,   907,
     912,   918,   924,   929,   934,   939,   944,   949,   954,   958,
     963,   964,   966,   967,   968,   969,   970,   971,   972,   985,
     986,   995,   997,   998,  1007,  1009,  1020,  1027,  1029,  1030,
    1036,  1037,  1044,  1045,  1052,  1053,  1058,  1059,  1065,  1066,
    1071,  1077,  1085,  1091,  1097,  1104,  1105,  1109,  1113,  1118,
    1122,  1123,  1127,  1133,  1138,  1139,  1145,  1146,  1148,  1149,
    1152,  1155,  1161,  1164,  1169,  1170,  1182,  1183,  1195,  1196,
    1201,  1202,  1203,  1205,  1206,  1208,  1210,  1217,  1218,  1220,
    1222,  1228,  1229,  1231,  1233,  1240,  1245,  1246,  1267,  1271,
    1275,  1279,  1283,  1287,  1291,  1296,  1301,  1306,  1311,  1317,
    1323
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "OR", "AND", "'+'", "'-'", "'*'", "'/'",
  "'%'", "UMINUS", "STRING", "FIELD", "NUMBER_STRING", "BINARY_STRING",
  "DOUBLE", "OPERATOR", "PARAMETER", "ALLTABLE", "DESCRIBE", "PRIMARYINFO",
  "AUTO_INCREMENT", "GETCATALOGS", "GETDATATYPES", "GETTABLETYPES",
  "IMPORTEDKEY", "EXPORTEDKEY", "SELECT", "FROM", "WHERE", "BETWEEN", "IN",
  "NOT", "AS", "LIMIT", "OFFSET", "INNER", "OUTER", "CROSS", "JOIN",
  "LEFT", "IS", "INSERT", "INTO", "VALUES", "EXPLAIN", "PLAN", "DELETE",
  "UPDATE", "SET", "NULL_VALUE", "CREATE", "TABLE", "PRIMARY", "KEY",
  "DEFAULT", "INDEX", "ON", "HASH", "TREE", "TRIE", "UNIQUE", "DROP",
  "SIZE", "FOREIGN", "REFERENCES", "COMPACT", "TRUNCATE", "CACHE",
  "CONDITION", "FIELDLIST", "PK", "DIRECT", "DSN", "UNCACHE", "NOSCHEMA",
  "INT_TYPE", "LONG_TYPE", "SHORT_TYPE", "DOUBLE_TYPE", "TIMESTAMP_TYPE",
  "DATE_TYPE", "CHAR_TYPE", "TIME_TYPE", "BIGINT_TYPE", "FLOAT_TYPE",
  "TINYINT_TYPE", "BINARY_TYPE", "VARCHAR_TYPE", "DATE_DIFF", "DATE_ADD",
  "DATE_SUB", "HOUR", "MINUTE", "SECOND", "YEAR", "MONTH", "DAY",
  "INTERVAL", "TIME_DIFF", "TIME_ADD", "TIME_SUB", "TIMESTAMP_DIFF",
  "TIMESTAMP_ADD", "TIMESTAMP_SUB", "EXTRACT", "NOW", "USER", "PASSWORD",
  "ALTER", "FLUSH", "ADD", "COLUMN", "MODIFY", "RENAME", "TO", "GRANT",
  "RESTRICT", "REVOKE", "MIN", "MAX", "AVG", "SUM", "COUNT", "GROUP", "BY",
  "HAVING", "ORDER", "ASC", "DESC", "DISTINCT", "';'", "','", "'('", "')'",
  "'`'", "$accept", "command", "alter_statement", "management_statement",
  "user_manager_statement", "privilege_list", "privilege_list_L",
  "privilege", "restrict_opt", "grant_statement", "copy_table_statement",
  "internal_statement", "other", "select_statement", "opt_explain",
  "opt_distinct", "field_list", "field_list_L", "field_with_as",
  "table_list", "join_exp", "opt_outer", "opt_join", "table_list_L",
  "insert_statement", "field_list_opt", "value_list", "value_list_L",
  "invalue_list", "invalue_list_L", "delete_statement", "update_statement",
  "semicolon_opt", "assign_list", "assign_list_L", "assign_stmt",
  "stmt_exp", "function_opt", "datetime_opt", "time_opt", "date_opt",
  "atom", "where_clause_opt", "group_by_opt", "order_by_opt", "limit_opt",
  "having_opt", "group_field_list", "group_field_list_L", "group_field",
  "order_field_list", "order_field_list_L", "order_field", "conditions",
  "hconditions", "hcondition", "condition", "not_opt", "table", "field",
  "ident", "value", "num_value", "doub_value", "cache_statement",
  "cache_opt", "hcond_cache", "vcond_cache", "pk_cache", "direct_opt",
  "dsn_opt", "no_schema", "ddl_statement", "opt_ind_type",
  "opt_constr_type", "opt_bucket", "create_defn_list_con",
  "create_defn_list", "create_defn_list_L", "create_defn", "field_defn",
  "field_name", "size_opt", "default_expr_opt", "null_expr_opt",
  "constraint_defn", "foreign_key_constraint", "foreign_key_constraint_L",
  "foreign_key_create", "fkField_list", "fkField_list_L", "fkField",
  "pkField_list", "pkField_list_L", "pkField", "primary_key_constraint",
  "auto_increment_key", "field_type", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,    43,    45,    42,    47,    37,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   318,   319,
     320,   321,   322,   323,   324,   325,   326,   327,   328,   329,
     330,   331,   332,   333,   334,   335,   336,   337,   338,   339,
     340,   341,   342,   343,   344,   345,   346,   347,   348,   349,
     350,   351,   352,   353,   354,   355,   356,   357,   358,   359,
     360,   361,   362,   363,   364,   365,   366,   367,   368,   369,
     370,   371,   372,   373,   374,   375,   376,   377,   378,   379,
     380,    59,    44,    40,    41,    96
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   136,   137,   137,   137,   137,   137,   137,   137,   137,
     137,   137,   137,   137,   137,   138,   138,   138,   138,   138,
     138,   139,   140,   140,   140,   141,   141,   142,   143,   143,
     143,   143,   144,   144,   145,   146,   146,   147,   148,   148,
     148,   148,   148,   148,   148,   148,   148,   149,   150,   150,
     151,   151,   152,   152,   153,   154,   154,   155,   155,   155,
     156,   156,   156,   156,   157,   157,   158,   158,   159,   160,
     161,   161,   162,   162,   163,   164,   164,   165,   166,   167,
     168,   168,   169,   169,   170,   171,   171,   171,   172,   172,
     172,   172,   172,   172,   172,   172,   172,   172,   173,   173,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   173,
     174,   174,   175,   175,   175,   176,   176,   176,   177,   177,
     177,   178,   178,   179,   179,   180,   180,   181,   181,   181,
     182,   182,   183,   183,   184,   185,   186,   186,   187,   188,
     188,   188,   189,   189,   189,   189,   189,   190,   190,   190,
     190,   190,   191,   191,   191,   191,   191,   192,   192,   192,
     192,   192,   192,   192,   192,   192,   193,   193,   194,   194,
     194,   195,   195,   195,   195,   195,   195,   195,   195,   195,
     196,   196,   197,   197,   197,   197,   197,   197,   197,   198,
     198,   198,   199,   199,   199,   200,   200,   201,   202,   202,
     203,   203,   204,   204,   205,   205,   206,   206,   207,   207,
     208,   208,   208,   208,   208,   209,   209,   209,   209,   209,
     210,   210,   210,   210,   211,   211,   212,   212,   213,   213,
     214,   215,   216,   217,   218,   218,   219,   219,   220,   220,
     221,   221,   221,   222,   222,   223,   224,   225,   225,   226,
     227,   228,   228,   229,   230,   231,   232,   232,   233,   233,
     233,   233,   233,   233,   233,   233,   233,   233,   233,   233,
     233
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     8,     7,     8,     6,     9,
       7,     3,     6,     4,     7,     2,     1,     2,     1,     1,
       1,     1,     3,     0,     8,    15,    15,     3,     1,     2,
       3,     2,     1,     1,     1,     2,     2,    12,     2,     0,
       1,     0,     2,     1,     2,     1,     3,     2,     1,     2,
       6,     7,     4,     0,     0,     1,     0,     1,     2,     9,
       0,     3,     2,     1,     2,     2,     1,     2,     5,     6,
       1,     0,     2,     1,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     2,     1,     1,     6,     7,
       7,     6,     7,     7,     8,     7,     7,     6,     4,     4,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     0,     3,     0,     3,     0,     2,     4,     0,
       2,     0,     2,     1,     2,     1,     2,     1,     2,     1,
       2,     2,     3,     3,     3,     4,     2,     3,     3,     3,
       4,     2,     6,     6,     6,     6,     6,     3,     3,     6,
       6,     4,     3,     3,     3,     3,     1,     0,     1,     3,
       2,     1,     4,     4,     4,     4,     4,     4,     1,     2,
       1,     3,     1,     1,     1,     1,     1,     1,     3,     1,
       2,     2,     1,     2,     2,     5,     4,     6,     0,     2,
       0,     2,     0,     2,     0,     1,     0,     2,     0,     1,
       7,    12,     3,     3,     4,     0,     2,     2,     2,     0,
       0,     1,     1,     0,     0,     2,     1,     3,     2,     1,
       2,     1,     6,     1,     0,     3,     0,     2,     0,     2,
       1,     1,     3,     2,     1,     2,    10,     2,     1,     2,
       1,     2,     1,     2,     1,     6,     0,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
      49,    38,     0,     0,    42,    44,    43,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    13,    12,    10,    11,     9,     7,
      14,     2,     0,     3,     4,     5,     8,     6,   180,     0,
       0,    39,   168,    41,    45,    46,     0,    48,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    81,     0,    28,    29,    31,    30,     0,
      26,     1,    51,    40,     0,     0,   170,    70,   122,     0,
       0,     0,     0,   212,   213,    81,    37,    81,   198,    81,
       0,     0,     0,    80,    21,     0,     0,     0,    25,    50,
       0,   181,   169,     0,     0,     0,   167,    81,   122,    83,
       0,     0,     0,     0,     0,    23,   214,     0,    81,   200,
     196,     0,     0,     0,     0,     0,     0,     0,     0,    27,
     178,     0,     0,     0,     0,     0,     0,    53,    55,   171,
      51,     0,     0,   166,   167,   121,     0,    78,     0,    82,
      81,     0,    51,   233,     0,   226,   229,   231,     0,     0,
      81,     0,     0,   182,   189,   184,   192,   186,   187,     0,
     199,   183,   185,   195,     0,   202,     0,     0,     0,     0,
       0,     0,    81,     0,     0,     0,     0,     0,     0,     0,
       0,    52,     0,   179,     0,    71,     0,   167,     0,   167,
     167,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   146,   167,    84,    79,     0,     0,
     120,     0,    85,    96,    97,   118,   119,     0,    81,     0,
     228,   258,   259,   260,   264,   267,   265,   268,   266,   261,
     263,   262,   270,   269,   234,     0,    22,   191,   194,   190,
     193,     0,   201,     0,   204,    81,     0,     0,     0,    81,
      81,    18,    33,     0,     0,     0,     0,     0,     0,   122,
      58,    54,    56,     0,     0,    73,     0,   144,   142,   143,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   166,     0,     0,   189,   192,   120,
      95,   119,   189,   192,    94,     0,     0,     0,     0,     0,
       0,     0,   210,     0,     0,   230,   227,   241,   244,   240,
       0,   238,     0,   188,   203,   205,   206,    16,    81,    81,
       0,    20,    24,     0,    81,   172,   173,   175,   174,   177,
     176,     0,    57,   124,    66,    66,    64,    59,     0,     0,
      81,    72,   145,     0,     0,     0,     0,     0,     0,     0,
       0,   112,   113,   114,   115,   116,   117,     0,   110,   111,
       0,     0,     0,   163,   164,   165,   158,   157,     0,   162,
       0,     0,    93,    91,    92,    90,    88,    89,     0,     0,
       0,     0,   243,     0,     0,     0,   236,   220,     0,   208,
      15,    17,    81,   167,    34,    68,     0,   131,    67,     0,
       0,    65,    66,   122,    74,    69,   108,   109,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   161,     0,
       0,   122,     0,     0,   245,   242,   235,   239,     0,   256,
     222,   221,   215,   207,   209,   197,    19,    32,     0,   167,
     126,     0,    63,     0,   124,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    76,   124,     0,
     250,     0,   248,   237,   257,   232,   220,   220,   220,   224,
     123,   133,   135,   166,   167,   130,     0,     0,   129,   167,
      62,     0,   131,    98,     0,     0,   101,     0,     0,     0,
       0,     0,   107,   159,     0,   160,    75,   131,   224,     0,
       0,   247,   216,   217,   218,     0,    81,     0,   132,   167,
       0,   167,   167,     0,     0,     0,     0,     0,   151,     0,
       0,    81,    63,   167,   126,    99,   100,   102,   103,     0,
     105,   106,    77,   126,   255,   249,     0,   225,   211,   134,
       0,   149,   147,   148,     0,     0,     0,     0,     0,   125,
     137,   139,   127,    47,    60,    63,   129,   104,   129,     0,
     150,     0,     0,     0,     0,     0,     0,   136,   140,   141,
       0,    61,    81,    81,     0,     0,     0,     0,     0,     0,
     138,   128,    36,    35,   254,     0,   252,     0,     0,     0,
       0,     0,     0,   246,   251,   152,   153,   155,   154,   156,
     253
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    23,    24,    25,    26,    69,    98,    70,   334,    27,
      28,    29,    30,    31,    32,   100,   136,   191,   137,   269,
     347,   412,   409,   342,    33,   105,   274,   351,   466,   506,
      34,    35,    94,   108,   149,   109,   222,   223,   367,   368,
     369,   224,   107,   407,   488,   531,   450,   480,   518,   481,
     559,   577,   560,   145,   485,   528,   214,   146,   270,   138,
     225,   301,   171,   172,    36,   118,   119,   175,   254,   326,
     399,   445,    37,   479,   442,   516,   154,   155,   230,   156,
     157,   158,   321,   439,   396,   316,   317,   392,   318,   471,
     511,   472,   595,   604,   596,   319,   475,   244
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -426
static const yytype_int16 yypact[] =
{
     700,  -426,    35,     1,  -426,  -426,  -426,     1,     1,    36,
      89,   131,     1,    24,    48,   115,   121,   170,   174,    53,
     180,   263,   247,   323,  -426,  -426,  -426,  -426,  -426,  -426,
    -426,  -426,   243,  -426,  -426,  -426,  -426,  -426,  -426,     1,
     314,  -426,    60,  -426,  -426,  -426,     1,  -426,     1,   278,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,   200,     1,  -426,  -426,  -426,  -426,   -40,
    -426,  -426,   210,  -426,   245,     1,  -426,    10,   306,     1,
      38,   288,   277,  -426,  -426,   200,  -426,   200,   359,   200,
     158,   318,   384,  -426,  -426,   326,     1,   247,  -426,  -426,
      78,  -426,  -426,   415,    78,   399,    56,   200,     6,  -426,
     428,   418,     1,     1,   436,  -426,  -426,   458,   200,   378,
    -426,   340,   321,   322,   344,   342,   350,     1,   345,  -426,
    -426,   328,   329,   332,   333,   334,     5,  -426,   426,   461,
     210,   -50,   341,   346,    56,   159,   335,  -426,     1,  -426,
     200,   197,   210,  -426,   348,   360,  -426,  -426,   285,   347,
     200,    93,   227,  -426,  -426,  -426,  -426,  -426,  -426,   361,
    -426,  -426,  -426,  -426,   458,   405,     1,     1,     1,     1,
       1,   466,   200,     1,     1,     1,     1,     1,    29,     1,
      78,  -426,     1,  -426,    78,  -426,   458,    56,    15,    56,
      56,   363,   364,   365,   376,   381,   383,   390,   392,   393,
     395,   396,   397,   477,  -426,   205,  -426,  -426,   400,   507,
      16,   554,   389,  -426,  -426,  -426,    34,    78,   200,    69,
    -426,  -426,  -426,  -426,  -426,  -426,  -426,  -426,  -426,  -426,
    -426,  -426,  -426,  -426,   398,    78,  -426,  -426,  -426,  -426,
    -426,   377,  -426,     1,   445,   200,   402,   403,   417,   200,
     200,  -426,   421,   406,   407,   408,   409,   411,   412,    13,
     274,  -426,  -426,    37,   130,  -426,    17,  -426,   530,  -426,
     218,   218,   218,   218,   218,   218,   218,   218,   282,   218,
     218,   282,   611,   343,  -426,    46,   175,  -426,  -426,  -426,
    -426,  -426,  -426,  -426,  -426,    23,   554,   554,   554,   554,
     554,    59,  -426,   485,   493,  -426,  -426,   416,  -426,   419,
     536,   518,   177,  -426,  -426,  -426,   490,  -426,   200,   200,
       1,  -426,  -426,   443,   200,  -426,  -426,  -426,  -426,  -426,
    -426,     1,  -426,   446,   533,   533,   538,  -426,     1,   458,
     200,  -426,  -426,   439,   442,   447,   479,   480,   448,   483,
     486,  -426,  -426,  -426,  -426,  -426,  -426,   451,  -426,  -426,
     487,   488,   559,  -426,  -426,  -426,  -426,  -426,   539,  -426,
     458,   459,  -426,   297,   297,  -426,  -426,  -426,     1,   460,
     462,   527,  -426,   527,   465,   544,   546,    81,   458,   528,
    -426,  -426,   200,    56,  -426,  -426,   489,   476,  -426,     1,
       1,  -426,   533,    13,  -426,  -426,  -426,  -426,   218,   218,
     218,   218,   218,   218,   218,   218,   218,   218,  -426,   601,
     458,    13,    78,     1,  -426,   416,  -426,  -426,   458,   594,
    -426,  -426,   284,  -426,  -426,  -426,  -426,   159,     1,    63,
     491,   562,   274,     1,   446,   495,   287,   287,   496,   295,
     295,   499,   282,   282,   498,   458,   186,  -426,   446,   204,
    -426,   258,  -426,  -426,  -426,  -426,    81,    81,    81,   557,
     501,  -426,  -426,   494,    63,   272,   300,   509,   587,    56,
    -426,   579,   476,  -426,   504,   505,  -426,   512,   513,   218,
     514,   515,  -426,  -426,   458,  -426,  -426,   476,   557,     1,
     576,  -426,  -426,  -426,  -426,   637,   200,     1,  -426,    63,
      20,    63,    63,   519,   529,   531,   532,   534,  -426,     1,
     638,   200,   241,    56,   491,  -426,  -426,  -426,  -426,   535,
    -426,  -426,  -426,   491,  -426,  -426,     1,  -426,  -426,  -426,
      22,  -426,   659,  -426,     1,     1,     1,     1,     1,   540,
    -426,   154,   631,  -426,  -426,   241,   587,  -426,   587,   537,
    -426,   541,   542,   543,   545,   547,     1,  -426,  -426,  -426,
     655,  -426,   200,   200,     1,   657,   658,   662,   664,   666,
    -426,  -426,  -426,  -426,  -426,   270,  -426,   458,   458,   458,
     458,   458,     1,  -426,  -426,  -426,  -426,  -426,  -426,  -426,
    -426
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -426,  -426,  -426,  -426,  -426,  -426,  -426,   574,  -426,  -426,
    -426,  -426,  -426,  -426,  -426,   -39,   -95,  -426,   500,  -236,
    -425,  -426,  -271,  -426,  -426,  -426,  -426,  -426,  -426,  -426,
    -426,  -426,   -21,  -426,  -426,   548,   -91,  -134,  -269,  -167,
    -106,  -166,   -97,  -365,  -293,  -139,  -339,  -426,  -426,   166,
    -426,  -426,   108,  -130,  -256,  -426,  -426,  -200,     0,  -426,
      -2,  -113,  -426,  -426,  -426,  -426,  -426,  -426,  -426,  -426,
    -426,  -426,  -426,  -426,   -77,   178,   508,  -426,  -426,  -103,
    -426,  -426,  -426,  -426,  -426,  -426,   298,  -426,   302,  -426,
    -426,   179,  -426,  -426,    95,  -426,  -426,  -426
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -88
static const yytype_int16 yytable[] =
{
      42,    42,    41,    43,   170,    42,    42,    44,    45,   141,
      49,   150,   213,    38,   198,   296,   -87,    96,   199,   200,
     199,   200,   372,   521,   522,   521,   522,   490,   306,   307,
     308,   309,   310,   189,   -86,   106,   267,    42,   226,    73,
      76,    38,   106,   103,    77,   -87,    78,    38,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,   252,    95,   -86,   115,   348,   116,   276,   120,   278,
     279,   111,    38,   102,   410,   257,    50,   110,   378,    46,
      51,    38,   190,   275,   195,   130,   147,   388,   143,   492,
      38,    39,    97,    75,   128,   483,   379,   173,   139,   273,
      53,   194,   139,   507,    54,    60,   247,   564,   248,    61,
     153,   159,   413,   227,   353,   354,   355,   356,   357,   358,
     359,   360,   313,   370,   371,   182,   315,   300,   304,   217,
     305,    52,   311,   314,   440,    47,    40,   190,   148,   246,
     581,   453,   441,   104,   215,   341,   110,   -87,   -87,   277,
     322,   352,   431,   534,   551,    55,   570,   382,   373,    48,
      62,   261,   199,   200,    40,   -86,   -86,    56,   543,   190,
      40,   112,   343,    57,   255,   153,   153,   258,   259,   375,
     377,   262,   263,   264,   265,   266,   268,    42,   139,   144,
     272,   190,   139,   500,   501,    40,   484,   131,   132,   133,
     134,   135,   218,   219,    40,   380,   381,   312,   163,    38,
     164,   165,   166,    40,   167,   383,   384,   385,   386,   387,
     121,   293,    58,   161,   162,   139,    59,   153,   520,   163,
      38,   164,   165,   166,   327,   167,   414,   294,   331,   332,
     249,   566,   250,   139,   199,   200,   295,   220,    63,   486,
     568,   324,   455,   456,   457,   458,   459,   460,   461,   462,
     463,   464,   349,   550,   350,   552,   553,   429,   299,   122,
      72,   123,   124,   447,    65,   521,   522,   344,   201,   345,
     202,   346,   578,   579,   486,   443,   203,   204,   205,    66,
     374,   376,   497,   498,    67,    68,   206,   207,   208,   209,
     210,   211,   212,   169,   308,   309,   310,   400,   401,   190,
     344,   397,   345,   404,   346,    64,   454,   467,   504,   486,
     505,   486,   486,    71,   169,   473,    74,    79,   402,   415,
     221,    93,    40,   539,   468,   106,   190,   469,   508,    42,
      99,   405,   476,   477,   478,   113,    42,    38,   161,   162,
     494,   495,   503,    40,   163,    38,   164,   165,   166,   532,
     167,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   361,   362,   363,   364,   365,   366,
     101,   446,   364,   365,   366,   114,    42,   361,   362,   363,
     509,   542,   510,   168,   306,   307,   308,   309,   310,   512,
     513,   514,   602,   565,   603,   218,   219,    42,    42,   451,
     452,   163,    38,   297,   165,   298,   201,   167,   202,   523,
     524,   525,   526,   527,   203,   204,   205,   582,   117,   583,
     139,   470,   125,   126,   206,   207,   208,   209,   210,   211,
     212,   127,   140,   142,   151,   152,   482,   160,   174,   169,
     299,    42,   176,   491,   177,   178,   179,   180,   181,   192,
     183,   184,   185,   161,   162,   186,   187,   188,   193,   163,
      40,   164,   165,   166,   196,   167,   253,   260,    40,   197,
     245,   201,   228,   202,   605,   606,   607,   608,   609,   203,
     204,   205,   229,   292,   251,   548,   280,   281,   282,   206,
     207,   208,   209,   210,   211,   212,   169,   470,   168,   283,
     563,   323,   218,   219,   284,   482,   285,   325,   163,    38,
     302,   165,   303,   286,   167,   287,   288,   561,   289,   290,
     291,   320,   330,   221,   200,    40,   328,   329,   333,   389,
     335,   336,   337,   338,   569,   339,   340,   390,   391,   394,
     395,   393,   571,   572,   573,   574,   575,   299,   403,   218,
     219,   592,   593,   398,   169,   163,    38,   164,   165,   166,
     406,   167,   408,   416,   561,   411,   417,   419,   420,   418,
     421,   422,   594,   424,   423,   425,   426,   427,   201,   428,
     202,   314,   430,   432,   437,   433,   203,   204,   205,   436,
     594,   438,   449,   444,   299,   465,   206,   207,   208,   209,
     210,   211,   212,   169,   448,   474,   161,   162,   487,   489,
     515,   530,   163,    38,   164,   165,   166,   519,   167,   493,
     496,   499,   502,   517,   529,   201,   533,   202,   535,   536,
     221,   546,    40,   203,   204,   205,   537,   538,   540,   541,
     547,   562,   554,   206,   207,   208,   209,   210,   211,   212,
     169,   168,   555,   522,   556,   557,   580,   558,   591,   567,
     584,   129,   576,   597,   598,   585,   586,   587,   599,   588,
     600,   589,   601,   549,   590,   256,   544,   221,   545,    40,
     271,   435,   201,   434,   202,     0,   216,   610,     0,     0,
     203,   204,   205,     0,     0,     0,     0,     0,     0,     0,
     206,   207,   208,   209,   210,   211,   212,   169,     1,     2,
       3,     0,     4,     5,     6,     7,     8,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     9,     0,     0,    10,    40,    11,    12,     0,
       0,    13,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    14,     0,     0,     0,    15,    16,    17,     0,
       0,     0,     0,     0,    18,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    19,
      20,     0,     0,     0,    21,     0,    22
};

static const yytype_int16 yycheck[] =
{
       2,     3,     2,     3,   117,     7,     8,     7,     8,   104,
      12,   108,   146,    12,   144,   215,     0,    57,     3,     4,
       3,     4,   291,     3,     4,     3,     4,   452,     5,     6,
       7,     8,     9,    28,     0,    29,     7,    39,   151,    39,
      42,    12,    29,    33,    46,    29,    48,    12,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,   174,    64,    29,    85,    28,    87,   197,    89,   199,
     200,    33,    12,    75,   345,   178,    52,    79,    32,    43,
      56,    12,   132,   196,   134,     7,   107,    28,    32,   454,
      12,    56,   132,    33,    96,    32,    50,   118,   100,   194,
      52,   140,   104,   468,    56,    52,    13,   532,    15,    56,
     112,   113,   348,   152,   280,   281,   282,   283,   284,   285,
     286,   287,    53,   289,   290,   127,   229,   218,   219,   150,
     221,   107,   227,    64,    53,    46,   135,   132,   132,   160,
     565,   412,    61,   133,   146,   132,   148,   131,   132,   134,
     245,   134,   388,   492,   134,   107,   134,   134,   292,    28,
     107,   182,     3,     4,   135,   131,   132,    52,   507,   132,
     135,   133,   269,    52,   176,   177,   178,   179,   180,   292,
     293,   183,   184,   185,   186,   187,   188,   189,   190,   133,
     192,   132,   194,   462,   463,   135,   133,   119,   120,   121,
     122,   123,     5,     6,   135,    30,    31,   228,    11,    12,
      13,    14,    15,   135,    17,   306,   307,   308,   309,   310,
      62,    16,    52,     5,     6,   227,    52,   229,   484,    11,
      12,    13,    14,    15,   255,    17,   349,    32,   259,   260,
      13,   534,    15,   245,     3,     4,    41,    50,    68,   449,
     543,   253,   418,   419,   420,   421,   422,   423,   424,   425,
     426,   427,   132,   519,   134,   521,   522,   380,    50,   111,
      27,   113,   114,   403,    27,     3,     4,    36,    81,    38,
      83,    40,   128,   129,   484,   398,    89,    90,    91,    42,
     292,   293,   459,   460,    47,    48,    99,   100,   101,   102,
     103,   104,   105,   106,     7,     8,     9,   328,   329,   132,
      36,   134,    38,   334,    40,    52,   413,   430,   132,   519,
     134,   521,   522,     0,   106,   438,    12,    49,   330,   350,
     133,   131,   135,   499,   431,    29,   132,   432,   134,   341,
     130,   341,    58,    59,    60,    57,   348,    12,     5,     6,
     456,   457,   465,   135,    11,    12,    13,    14,    15,   489,
      17,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    92,    93,    94,    95,    96,    97,
     135,   402,    95,    96,    97,   108,   388,    92,    93,    94,
     132,   504,   134,    50,     5,     6,     7,     8,     9,   476,
     477,   478,   132,   533,   134,     5,     6,   409,   410,   409,
     410,    11,    12,    13,    14,    15,    81,    17,    83,   119,
     120,   121,   122,   123,    89,    90,    91,   566,    69,   568,
     432,   433,   114,    49,    99,   100,   101,   102,   103,   104,
     105,   115,    27,    44,    16,    27,   448,    11,    70,   106,
      50,   453,   112,   453,   133,   133,   112,   115,   108,    33,
     115,   133,   133,     5,     6,   133,   133,   133,     7,    11,
     135,    13,    14,    15,   133,    17,    71,    11,   135,   133,
     133,    81,   134,    83,   597,   598,   599,   600,   601,    89,
      90,    91,   132,    16,   133,   516,   133,   133,   133,    99,
     100,   101,   102,   103,   104,   105,   106,   509,    50,   133,
     531,   134,     5,     6,   133,   517,   133,    72,    11,    12,
      13,    14,    15,   133,    17,   133,   133,   529,   133,   133,
     133,   133,   115,   133,     4,   135,   134,   134,   117,    54,
     134,   134,   134,   134,   546,   134,   134,    54,   132,    13,
      32,   132,   554,   555,   556,   557,   558,    50,   115,     5,
       6,   582,   583,    73,   106,    11,    12,    13,    14,    15,
     124,    17,    39,   134,   576,    37,   134,    98,    98,   132,
     132,    98,   584,   132,    98,    98,    98,    28,    81,    50,
      83,    64,   133,   133,    50,   133,    89,    90,    91,   134,
     602,    55,   126,    75,    50,     4,    99,   100,   101,   102,
     103,   104,   105,   106,   125,    21,     5,     6,   127,    57,
      63,    34,    11,    12,    13,    14,    15,   133,    17,   134,
     134,   132,   134,   132,   125,    81,    57,    83,   134,   134,
     133,    65,   135,    89,    90,    91,   134,   134,   134,   134,
      13,    13,   133,    99,   100,   101,   102,   103,   104,   105,
     106,    50,   133,     4,   133,   133,    35,   133,    13,   134,
     133,    97,   132,    16,    16,   134,   134,   134,    16,   134,
      16,   134,    16,   517,   576,   177,   508,   133,   509,   135,
     190,   393,    81,   391,    83,    -1,   148,   602,    -1,    -1,
      89,    90,    91,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      99,   100,   101,   102,   103,   104,   105,   106,    18,    19,
      20,    -1,    22,    23,    24,    25,    26,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    42,    -1,    -1,    45,   135,    47,    48,    -1,
      -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    62,    -1,    -1,    -1,    66,    67,    68,    -1,
      -1,    -1,    -1,    -1,    74,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   109,
     110,    -1,    -1,    -1,   114,    -1,   116
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    18,    19,    20,    22,    23,    24,    25,    26,    42,
      45,    47,    48,    51,    62,    66,    67,    68,    74,   109,
     110,   114,   116,   137,   138,   139,   140,   145,   146,   147,
     148,   149,   150,   160,   166,   167,   200,   208,    12,    56,
     135,   194,   196,   194,   194,   194,    43,    46,    28,   196,
      52,    56,   107,    52,    56,   107,    52,    52,    52,    52,
      52,    56,   107,    68,    52,    27,    42,    47,    48,   141,
     143,     0,    27,   194,    12,    33,   196,   196,   196,    49,
     196,   196,   196,   196,   196,   196,   196,   196,   196,   196,
     196,   196,   196,   131,   168,   196,    57,   132,   142,   130,
     151,   135,   196,    33,   133,   161,    29,   178,   169,   171,
     196,    33,   133,    57,   108,   168,   168,    69,   201,   202,
     168,    62,   111,   113,   114,   114,    49,   115,   196,   143,
       7,   119,   120,   121,   122,   123,   152,   154,   195,   196,
      27,   152,    44,    32,   133,   189,   193,   168,   132,   170,
     178,    16,    27,   196,   212,   213,   215,   216,   217,   196,
      11,     5,     6,    11,    13,    14,    15,    17,    50,   106,
     197,   198,   199,   168,    70,   203,   112,   133,   133,   112,
     115,   108,   196,   115,   133,   133,   133,   133,   133,    28,
     132,   153,    33,     7,   151,   134,   133,   133,   189,     3,
       4,    81,    83,    89,    90,    91,    99,   100,   101,   102,
     103,   104,   105,   173,   192,   196,   171,   168,     5,     6,
      50,   133,   172,   173,   177,   196,   197,   151,   134,   132,
     214,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,   233,   133,   168,    13,    15,    13,
      15,   133,   197,    71,   204,   196,   212,   215,   196,   196,
      11,   168,   196,   196,   196,   196,   196,     7,   196,   155,
     194,   154,   196,   152,   162,   197,   189,   134,   189,   189,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,    16,    16,    32,    41,   193,    13,    15,    50,
     172,   197,    13,    15,   172,   172,     5,     6,     7,     8,
       9,   152,   168,    53,    64,   215,   221,   222,   224,   231,
     133,   218,   152,   134,   196,    72,   205,   168,   134,   134,
     115,   168,   168,   117,   144,   134,   134,   134,   134,   134,
     134,   132,   159,   178,    36,    38,    40,   156,    28,   132,
     134,   163,   134,   177,   177,   177,   177,   177,   177,   177,
     177,    92,    93,    94,    95,    96,    97,   174,   175,   176,
     177,   177,   174,   173,   196,   197,   196,   197,    32,    50,
      30,    31,   134,   172,   172,   172,   172,   172,    28,    54,
      54,   132,   223,   132,    13,    32,   220,   134,    73,   206,
     168,   168,   196,   115,   168,   194,   124,   179,    39,   158,
     158,    37,   157,   155,   197,   168,   134,   134,   132,    98,
      98,   132,    98,    98,   132,    98,    98,    28,    50,   197,
     133,   155,   133,   133,   224,   222,   134,    50,    55,   219,
      53,    61,   210,   197,    75,   207,   168,   189,   125,   126,
     182,   194,   194,   158,   178,   177,   177,   177,   177,   177,
     177,   177,   177,   177,   177,     4,   164,   197,   178,   152,
     196,   225,   227,   197,    21,   232,    58,    59,    60,   209,
     183,   185,   196,    32,   133,   190,   193,   127,   180,    57,
     156,   194,   179,   134,   176,   176,   134,   175,   175,   132,
     174,   174,   134,   197,   132,   134,   165,   179,   134,   132,
     134,   226,   210,   210,   210,    63,   211,   132,   184,   133,
     190,     3,     4,   119,   120,   121,   122,   123,   191,   125,
      34,   181,   189,    57,   182,   134,   134,   134,   134,   177,
     134,   134,   197,   182,   211,   227,    65,    13,   168,   185,
     190,   134,   190,   190,   133,   133,   133,   133,   133,   186,
     188,   196,    13,   168,   156,   189,   180,   134,   180,   196,
     134,   196,   196,   196,   196,   196,   132,   187,   128,   129,
      35,   156,   181,   181,   133,   134,   134,   134,   134,   134,
     188,    13,   168,   168,   196,   228,   230,    16,    16,    16,
      16,    16,   132,   134,   229,   197,   197,   197,   197,   197,
     230
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1464 of yacc.c  */
#line 44 "dmlyacc.yxx"
    { YYACCEPT; }
    break;

  case 3:

/* Line 1464 of yacc.c  */
#line 45 "dmlyacc.yxx"
    { YYACCEPT; }
    break;

  case 4:

/* Line 1464 of yacc.c  */
#line 46 "dmlyacc.yxx"
    { YYACCEPT; }
    break;

  case 5:

/* Line 1464 of yacc.c  */
#line 47 "dmlyacc.yxx"
    { YYACCEPT; }
    break;

  case 6:

/* Line 1464 of yacc.c  */
#line 48 "dmlyacc.yxx"
    { YYACCEPT; }
    break;

  case 7:

/* Line 1464 of yacc.c  */
#line 49 "dmlyacc.yxx"
    { YYACCEPT; }
    break;

  case 8:

/* Line 1464 of yacc.c  */
#line 50 "dmlyacc.yxx"
    { YYACCEPT; }
    break;

  case 9:

/* Line 1464 of yacc.c  */
#line 51 "dmlyacc.yxx"
    { YYACCEPT; }
    break;

  case 10:

/* Line 1464 of yacc.c  */
#line 52 "dmlyacc.yxx"
    { YYACCEPT; }
    break;

  case 11:

/* Line 1464 of yacc.c  */
#line 53 "dmlyacc.yxx"
    { YYACCEPT; }
    break;

  case 12:

/* Line 1464 of yacc.c  */
#line 54 "dmlyacc.yxx"
    { YYACCEPT; }
    break;

  case 13:

/* Line 1464 of yacc.c  */
#line 55 "dmlyacc.yxx"
    { YYACCEPT; }
    break;

  case 14:

/* Line 1464 of yacc.c  */
#line 56 "dmlyacc.yxx"
    {YYACCEPT;}
    break;

  case 15:

/* Line 1464 of yacc.c  */
#line 59 "dmlyacc.yxx"
    {
            parsedData->setStmtType(AlterStatement);
            parsedData->setAlterType(ALTERADD);
            parsedData->setTableName((yyvsp[(3) - (8)].stringval));
            free((yyvsp[(3) - (8)].stringval)); 
	}
    break;

  case 16:

/* Line 1464 of yacc.c  */
#line 66 "dmlyacc.yxx"
    {
            parsedData->setStmtType(AlterStatement);
            parsedData->setAlterType(ALTERDROP);
            parsedData->setTableName((yyvsp[(3) - (7)].stringval));
            parsedData->setIndexName((yyvsp[(6) - (7)].stringval)); 
            free((yyvsp[(3) - (7)].stringval));
	}
    break;

  case 17:

/* Line 1464 of yacc.c  */
#line 74 "dmlyacc.yxx"
    {
            printf(" Not Implemented\n");
            free((yyvsp[(3) - (8)].stringval));
            YYABORT;
	}
    break;

  case 18:

/* Line 1464 of yacc.c  */
#line 80 "dmlyacc.yxx"
    {
            parsedData->setStmtType(AlterStatement);
            parsedData->setAlterType(ALTERTABLERENAME);
            parsedData->setTableName((yyvsp[(3) - (6)].stringval));
            parsedData->setIndexName((yyvsp[(5) - (6)].stringval)); 
            free((yyvsp[(3) - (6)].stringval)); free((yyvsp[(5) - (6)].stringval));

	}
    break;

  case 19:

/* Line 1464 of yacc.c  */
#line 89 "dmlyacc.yxx"
    {
            parsedData->setStmtType(AlterStatement);
            parsedData->setAlterType(ALTERFIELDRENAME);
            parsedData->setTableName((yyvsp[(3) - (9)].stringval));
            parsedData->setIndexName((yyvsp[(6) - (9)].stringval));
            parsedData->setPKTableName((yyvsp[(8) - (9)].stringval));
            free((yyvsp[(3) - (9)].stringval)); free((yyvsp[(5) - (9)].stringval)); free((yyvsp[(8) - (9)].stringval));
        }
    break;

  case 20:

/* Line 1464 of yacc.c  */
#line 98 "dmlyacc.yxx"
    {
            parsedData->setStmtType(AlterStatement);
            parsedData->setAlterType(ALTERINDEXRENAME);
            parsedData->setTableName((yyvsp[(3) - (7)].stringval));
            parsedData->setIndexName((yyvsp[(6) - (7)].stringval)); 
            free((yyvsp[(3) - (7)].stringval)); free((yyvsp[(5) - (7)].stringval));
        }
    break;

  case 21:

/* Line 1464 of yacc.c  */
#line 107 "dmlyacc.yxx"
    {
           parsedData->setStmtType(MgmtStatement);
	}
    break;

  case 22:

/* Line 1464 of yacc.c  */
#line 112 "dmlyacc.yxx"
    {
            parsedData->setStmtType(UserStatement);
            parsedData->createUserNode((char*)(yyvsp[(3) - (6)].stringval),(char*)(yyvsp[(5) - (6)].stringval));
            free((yyvsp[(3) - (6)].stringval));
            free((yyvsp[(5) - (6)].stringval));
	}
    break;

  case 23:

/* Line 1464 of yacc.c  */
#line 119 "dmlyacc.yxx"
    {
            parsedData->setStmtType(UserStatement);
            parsedData->dropUserNode((char*)(yyvsp[(3) - (4)].stringval));
            free((yyvsp[(3) - (4)].stringval));
        }
    break;

  case 24:

/* Line 1464 of yacc.c  */
#line 125 "dmlyacc.yxx"
    {
            parsedData->setStmtType(UserStatement);
            parsedData->alterUserNode((char*)(yyvsp[(3) - (7)].stringval),(char*)(yyvsp[(6) - (7)].stringval));
            free((yyvsp[(3) - (7)].stringval));
            free((yyvsp[(6) - (7)].stringval));
	}
    break;

  case 31:

/* Line 1464 of yacc.c  */
#line 138 "dmlyacc.yxx"
    {
        parsedData->insertPrivilege((yyvsp[(1) - (1)].stringval));
    }
    break;

  case 34:

/* Line 1464 of yacc.c  */
#line 146 "dmlyacc.yxx"
    {
            parsedData->setStmtType(DclStatement);
            parsedData->setTableName((yyvsp[(4) - (8)].stringval));
            parsedData->grantDclNode((yyvsp[(6) - (8)].stringval));
    }
    break;

  case 35:

/* Line 1464 of yacc.c  */
#line 160 "dmlyacc.yxx"
    {
            parsedData->setStmtType(CopyTableStatement);
            parsedData->setPKTableName((yyvsp[(3) - (15)].stringval));
            parsedData->setCreateTbl();
            free((yyvsp[(3) - (15)].stringval));
        }
    break;

  case 36:

/* Line 1464 of yacc.c  */
#line 167 "dmlyacc.yxx"
    {
            parsedData->setStmtType(CopyTableStatement);
            parsedData->setPKTableName((yyvsp[(3) - (15)].stringval));
            free((yyvsp[(3) - (15)].stringval));
        }
    break;

  case 37:

/* Line 1464 of yacc.c  */
#line 174 "dmlyacc.yxx"
    {
            parsedData->setStmtType(CompactTableStatement);
            parsedData->setTableName((yyvsp[(3) - (3)].stringval));
            free((yyvsp[(3) - (3)].stringval));
        }
    break;

  case 38:

/* Line 1464 of yacc.c  */
#line 181 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetTables);
	}
    break;

  case 39:

/* Line 1464 of yacc.c  */
#line 186 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetColumns);
        }
    break;

  case 40:

/* Line 1464 of yacc.c  */
#line 191 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetIndexes);
                   
        }
    break;

  case 41:

/* Line 1464 of yacc.c  */
#line 197 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetPriIndex);
        }
    break;

  case 42:

/* Line 1464 of yacc.c  */
#line 202 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetCatalogs);
        }
    break;

  case 43:

/* Line 1464 of yacc.c  */
#line 207 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetTableType);
        }
    break;

  case 44:

/* Line 1464 of yacc.c  */
#line 212 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetDataType);
        }
    break;

  case 45:

/* Line 1464 of yacc.c  */
#line 217 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetImportKey);
        }
    break;

  case 46:

/* Line 1464 of yacc.c  */
#line 222 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetExportKey);
        }
    break;

  case 47:

/* Line 1464 of yacc.c  */
#line 228 "dmlyacc.yxx"
    {
            parsedData->setStmtType(SelectStatement);
            parsedData->setCacheWorthy(true);
        }
    break;

  case 48:

/* Line 1464 of yacc.c  */
#line 234 "dmlyacc.yxx"
    {
           parsedData->setExplain();
	}
    break;

  case 50:

/* Line 1464 of yacc.c  */
#line 240 "dmlyacc.yxx"
    { 
            parsedData->setDistinct();
        }
    break;

  case 56:

/* Line 1464 of yacc.c  */
#line 252 "dmlyacc.yxx"
    {
            parsedData->insertFieldAlias((char*)(yyvsp[(3) - (3)].stringval));
            free((char*)(yyvsp[(3) - (3)].stringval));
        }
    break;

  case 60:

/* Line 1464 of yacc.c  */
#line 262 "dmlyacc.yxx"
    {
           parsedData->insertJoinType(INNER_JOIN);
           Condition *cond = parsedData->getCondition();
           Predicate *pred = cond->getPredicate();
           if (pred == NULL) {
               parsedData->setCondition((Predicate*)(yyvsp[(5) - (6)].predicate));
           } else {
               Predicate *newPred;
               newPred = parsedData->insertPredicate(pred, OpAnd, (Predicate*)(yyvsp[(5) - (6)].predicate));
               parsedData->setCondition(newPred);
           }

        }
    break;

  case 61:

/* Line 1464 of yacc.c  */
#line 276 "dmlyacc.yxx"
    {
           parsedData->insertJoinType(LEFT_JOIN);
           Condition *cond = parsedData->getCondition();
           Predicate *pred = cond->getPredicate();
           if (pred == NULL) {
               parsedData->setCondition((Predicate*)(yyvsp[(6) - (7)].predicate));
           } else {
               Predicate *newPred;
               newPred = parsedData->insertPredicate(pred, OpAnd, (Predicate*)(yyvsp[(6) - (7)].predicate));
               parsedData->setCondition(newPred);
           }
        }
    break;

  case 62:

/* Line 1464 of yacc.c  */
#line 289 "dmlyacc.yxx"
    {
            parsedData->insertJoinType(INNER_JOIN);
        }
    break;

  case 68:

/* Line 1464 of yacc.c  */
#line 301 "dmlyacc.yxx"
    {
            parsedData->insertJoinType(INNER_JOIN);
        }
    break;

  case 69:

/* Line 1464 of yacc.c  */
#line 307 "dmlyacc.yxx"
    {
            parsedData->setStmtType(InsertStatement);
            parsedData->setTableName((yyvsp[(3) - (9)].stringval)); 
            free((yyvsp[(3) - (9)].stringval));
        }
    break;

  case 73:

/* Line 1464 of yacc.c  */
#line 320 "dmlyacc.yxx"
    {
            parsedData->insertValue((char*)(yyvsp[(1) - (1)].stringval));
            free((yyvsp[(1) - (1)].stringval));
        }
    break;

  case 74:

/* Line 1464 of yacc.c  */
#line 326 "dmlyacc.yxx"
    {
            parsedData->insertValue((char*)(yyvsp[(2) - (2)].stringval));
            free((yyvsp[(2) - (2)].stringval));
        }
    break;

  case 76:

/* Line 1464 of yacc.c  */
#line 334 "dmlyacc.yxx"
    {
            parsedData->insertInValue((char*)(yyvsp[(1) - (1)].stringval));
            free((yyvsp[(1) - (1)].stringval));
        }
    break;

  case 77:

/* Line 1464 of yacc.c  */
#line 340 "dmlyacc.yxx"
    {
            parsedData->insertInValue((char*)(yyvsp[(2) - (2)].stringval));
            free((yyvsp[(2) - (2)].stringval));
        }
    break;

  case 78:

/* Line 1464 of yacc.c  */
#line 347 "dmlyacc.yxx"
    {
            parsedData->setStmtType(DeleteStatement);
            parsedData->setTableName((yyvsp[(3) - (5)].stringval)); 
            free((yyvsp[(3) - (5)].stringval));
	}
    break;

  case 79:

/* Line 1464 of yacc.c  */
#line 355 "dmlyacc.yxx"
    {
            parsedData->setStmtType(UpdateStatement);
            parsedData->setTableName((yyvsp[(2) - (6)].stringval)); 
            free( (yyvsp[(2) - (6)].stringval) );
	}
    break;

  case 85:

/* Line 1464 of yacc.c  */
#line 373 "dmlyacc.yxx"
    {
           parsedData->insertUpdateExpression( (char*) (yyvsp[(1) - (3)].stringval), (Expression* ) (yyvsp[(3) - (3)].Expression));
           free( (yyvsp[(1) - (3)].stringval) ); free((yyvsp[(2) - (3)].stringval));
        }
    break;

  case 86:

/* Line 1464 of yacc.c  */
#line 378 "dmlyacc.yxx"
    { 
            parsedData->insertUpdateValue( (char*) (yyvsp[(1) - (3)].stringval), (char*) (yyvsp[(3) - (3)].stringval));
            free( (yyvsp[(1) - (3)].stringval) ); free((yyvsp[(2) - (3)].stringval));free( (yyvsp[(3) - (3)].stringval) ); 
        }
    break;

  case 87:

/* Line 1464 of yacc.c  */
#line 383 "dmlyacc.yxx"
    {
            parsedData->insertUpdateValue( (char*) (yyvsp[(1) - (3)].stringval), (char*) (yyvsp[(3) - (3)].stringval));
            free( (yyvsp[(1) - (3)].stringval) ); free((yyvsp[(2) - (3)].stringval));free( (yyvsp[(3) - (3)].stringval) );
        }
    break;

  case 88:

/* Line 1464 of yacc.c  */
#line 389 "dmlyacc.yxx"
    {
            Expression* exp;
            exp=parsedData->insertExpression((Expression *)(yyvsp[(1) - (3)].Expression), division, (Expression *)(yyvsp[(3) - (3)].Expression));
            (yyval.Expression)=exp;
        }
    break;

  case 89:

/* Line 1464 of yacc.c  */
#line 395 "dmlyacc.yxx"
    {
            Expression* exp;
            exp=parsedData->insertExpression((Expression *)(yyvsp[(1) - (3)].Expression), modulus, (Expression *)(yyvsp[(3) - (3)].Expression));
            (yyval.Expression)=exp;
        }
    break;

  case 90:

/* Line 1464 of yacc.c  */
#line 401 "dmlyacc.yxx"
    {
            Expression* exp;
            exp=parsedData->insertExpression((Expression *)(yyvsp[(1) - (3)].Expression), multiplication, (Expression *)(yyvsp[(3) - (3)].Expression));
            (yyval.Expression)=exp;
        }
    break;

  case 91:

/* Line 1464 of yacc.c  */
#line 407 "dmlyacc.yxx"
    {
            Expression* exp;
            exp=parsedData->insertExpression((Expression *)(yyvsp[(1) - (3)].Expression), addition, (Expression *)(yyvsp[(3) - (3)].Expression));
            (yyval.Expression)=exp;
        }
    break;

  case 92:

/* Line 1464 of yacc.c  */
#line 413 "dmlyacc.yxx"
    {
            Expression* exp;
            exp=parsedData->insertExpression((Expression *)(yyvsp[(1) - (3)].Expression), subtraction, (Expression *)(yyvsp[(3) - (3)].Expression));
            (yyval.Expression)=exp;
        }
    break;

  case 93:

/* Line 1464 of yacc.c  */
#line 419 "dmlyacc.yxx"
    {
            (yyval.Expression)=(yyvsp[(2) - (3)].Expression);
        }
    break;

  case 94:

/* Line 1464 of yacc.c  */
#line 423 "dmlyacc.yxx"
    {
            (yyval.Expression) = (yyvsp[(2) - (2)].Expression);
        }
    break;

  case 95:

/* Line 1464 of yacc.c  */
#line 427 "dmlyacc.yxx"
    {
            (yyval.Expression) = (yyvsp[(2) - (2)].Expression);
        }
    break;

  case 98:

/* Line 1464 of yacc.c  */
#line 434 "dmlyacc.yxx"
    {
              Expression* exp;
              parsedData->setFunctionType(DATEDIFF);
              exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (6)].Expression), DATEDIFF, (Expression *)(yyvsp[(5) - (6)].Expression));
            (yyval.Expression)=exp;
        }
    break;

  case 99:

/* Line 1464 of yacc.c  */
#line 441 "dmlyacc.yxx"
    {
	         Expression* exp;
             parsedData->setFunctionType((*(FunctionType *)(yyvsp[(6) - (7)].FunctionType)));
             exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (7)].Expression), (*(FunctionType *)(yyvsp[(6) - (7)].FunctionType)), (Expression *)(yyvsp[(5) - (7)].Expression));
             (yyval.Expression)=exp;
	    }
    break;

  case 100:

/* Line 1464 of yacc.c  */
#line 448 "dmlyacc.yxx"
    {
             Expression* exp;
             //parsedData->setFunctionType((*(FunctionType *)$6));
             parsedData->setFunctionType((FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+3));
             exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (7)].Expression), (FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+3), (Expression *)(yyvsp[(5) - (7)].Expression));
             (yyval.Expression)=exp;
        }
    break;

  case 101:

/* Line 1464 of yacc.c  */
#line 456 "dmlyacc.yxx"
    {
              Expression* exp;
              parsedData->setFunctionType(TIMEDIFF);
              exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (6)].Expression), TIMEDIFF, (Expression *)(yyvsp[(5) - (6)].Expression));
            (yyval.Expression)=exp;
        }
    break;

  case 102:

/* Line 1464 of yacc.c  */
#line 463 "dmlyacc.yxx"
    {
             Expression* exp;
             parsedData->setFunctionType((*(FunctionType *)(yyvsp[(6) - (7)].FunctionType)));
             exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (7)].Expression), (*(FunctionType *)(yyvsp[(6) - (7)].FunctionType)), (Expression *)(yyvsp[(5) - (7)].Expression));
             (yyval.Expression)=exp;
        }
    break;

  case 103:

/* Line 1464 of yacc.c  */
#line 470 "dmlyacc.yxx"
    {
             Expression* exp;
             parsedData->setFunctionType((FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+3));
             exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (7)].Expression), (FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+3), (Expression *)(yyvsp[(5) - (7)].Expression));
             (yyval.Expression)=exp;
        }
    break;

  case 104:

/* Line 1464 of yacc.c  */
#line 477 "dmlyacc.yxx"
    {
              Expression* exp;
              int diff=0;
              FunctionType val = (*(FunctionType *)(yyvsp[(3) - (8)].FunctionType));
              if( val == DATEADDWITHYEAR || val == DATEADDWITHMON || val == DATEADDWITHDAY ) diff = 24;
              else diff = 21;
              parsedData->setFunctionType((FunctionType)((int)(*(FunctionType *)(yyvsp[(3) - (8)].FunctionType)+diff)));
              exp=parsedData->insertExpression((Expression *)(yyvsp[(5) - (8)].Expression), (FunctionType)((int)(*(FunctionType *)(yyvsp[(3) - (8)].FunctionType))+diff), (Expression *)(yyvsp[(7) - (8)].Expression));
            (yyval.Expression)=exp;
        }
    break;

  case 105:

/* Line 1464 of yacc.c  */
#line 488 "dmlyacc.yxx"
    {
             Expression* exp;
             parsedData->setFunctionType((FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+12));
             exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (7)].Expression), (FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+12), (Expression *)(yyvsp[(5) - (7)].Expression));
             (yyval.Expression)=exp;
        }
    break;

  case 106:

/* Line 1464 of yacc.c  */
#line 495 "dmlyacc.yxx"
    {
             Expression* exp;
             parsedData->setFunctionType((FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+15));
             exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (7)].Expression), (FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+15), (Expression *)(yyvsp[(5) - (7)].Expression));
             (yyval.Expression)=exp;
        }
    break;

  case 107:

/* Line 1464 of yacc.c  */
#line 502 "dmlyacc.yxx"
    {
            FunctionType val = UNKNOWN_FUNCTION;
            //if((*(FunctionType *)$3) >=8)
              // val = (FunctionType)((int)(*(FunctionType *)$3)+36);
            //else
               val = (FunctionType)((int)(*(FunctionType *)(yyvsp[(3) - (6)].FunctionType))+30);
            Expression* exp;
            parsedData->setFunctionType(val);
            exp=parsedData->insertExpression((Expression *)(yyvsp[(5) - (6)].Expression), val,NULL);
            (yyval.Expression)=exp;
	    }
    break;

  case 108:

/* Line 1464 of yacc.c  */
#line 514 "dmlyacc.yxx"
    {
            Expression* exp;
            parsedData->setFunctionType(DATEFROMTIMESTAMP);
            exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (4)].Expression), DATEFROMTIMESTAMP, NULL);
            (yyval.Expression)=exp;

        }
    break;

  case 109:

/* Line 1464 of yacc.c  */
#line 522 "dmlyacc.yxx"
    {
            Expression* exp;
            parsedData->setFunctionType(TIMEFROMTIMESTAMP);
            exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (4)].Expression), TIMEFROMTIMESTAMP, NULL);
            (yyval.Expression)=exp;
        }
    break;

  case 110:

/* Line 1464 of yacc.c  */
#line 530 "dmlyacc.yxx"
    {
           FunctionType val = *(FunctionType *)(yyvsp[(1) - (1)].FunctionType);
           (yyval.FunctionType) = &val;
        }
    break;

  case 111:

/* Line 1464 of yacc.c  */
#line 535 "dmlyacc.yxx"
    {
           FunctionType val = *(FunctionType *)(yyvsp[(1) - (1)].FunctionType);
           (yyval.FunctionType) = &val;
        }
    break;

  case 112:

/* Line 1464 of yacc.c  */
#line 541 "dmlyacc.yxx"
    { 
             FunctionType val = TIMEADDWITHHOUR;
             (yyval.FunctionType) = &val;
        }
    break;

  case 113:

/* Line 1464 of yacc.c  */
#line 546 "dmlyacc.yxx"
    {
             FunctionType val = TIMEADDWITHMIN;
             (yyval.FunctionType) = &val;
        }
    break;

  case 114:

/* Line 1464 of yacc.c  */
#line 551 "dmlyacc.yxx"
    {
             FunctionType val = TIMEADDWITHSEC;
             (yyval.FunctionType) = &val;
        }
    break;

  case 115:

/* Line 1464 of yacc.c  */
#line 557 "dmlyacc.yxx"
    {
	        FunctionType val = DATEADDWITHYEAR;
            (yyval.FunctionType) = &val;
	    }
    break;

  case 116:

/* Line 1464 of yacc.c  */
#line 562 "dmlyacc.yxx"
    {
	        FunctionType val = DATEADDWITHMON;
            (yyval.FunctionType) = &val;
        }
    break;

  case 117:

/* Line 1464 of yacc.c  */
#line 567 "dmlyacc.yxx"
    {
            FunctionType val = DATEADDWITHDAY;
            (yyval.FunctionType) = &val;
        }
    break;

  case 118:

/* Line 1464 of yacc.c  */
#line 573 "dmlyacc.yxx"
    {
            Expression* exp;
            exp=parsedData->insertExpression((char *)(yyvsp[(1) - (1)].stringval));
            free((yyvsp[(1) - (1)].stringval));
            (yyval.Expression)=exp;
        }
    break;

  case 119:

/* Line 1464 of yacc.c  */
#line 580 "dmlyacc.yxx"
    {
            Expression* exp;
            bool flag = false;
            exp=parsedData->insertExpression((char *)(yyvsp[(1) - (1)].stringval), flag);
            free((yyvsp[(1) - (1)].stringval));
            (yyval.Expression)=exp;
        }
    break;

  case 120:

/* Line 1464 of yacc.c  */
#line 588 "dmlyacc.yxx"
    {
            Expression* exp;
            exp=parsedData->insertExpression("NULL");
            free((yyvsp[(1) - (1)].stringval));
            (yyval.Expression)=exp;
        }
    break;

  case 121:

/* Line 1464 of yacc.c  */
#line 597 "dmlyacc.yxx"
    {
           Condition *cond = parsedData->getCondition();
           Predicate *pred = cond->getPredicate();
           if (pred == NULL) {
               parsedData->setCondition((Predicate*)(yyvsp[(2) - (2)].predicate));
           } else {
                Predicate *newPred;
                newPred = parsedData->insertPredicate(pred, OpAnd, (Predicate*)(yyvsp[(2) - (2)].predicate));
                parsedData->setCondition(newPred);
           }

        }
    break;

  case 127:

/* Line 1464 of yacc.c  */
#line 618 "dmlyacc.yxx"
    {
            parsedData->setLimit(atoi((yyvsp[(2) - (2)].stringval)), 0);
        }
    break;

  case 128:

/* Line 1464 of yacc.c  */
#line 622 "dmlyacc.yxx"
    {
            parsedData->setLimit(atoi((yyvsp[(2) - (4)].stringval)), atoi((yyvsp[(4) - (4)].stringval)));
        }
    break;

  case 135:

/* Line 1464 of yacc.c  */
#line 636 "dmlyacc.yxx"
    {
            parsedData->insertGroupField((char*)(yyvsp[(1) - (1)].stringval));
            free( (yyvsp[(1) - (1)].stringval) );
        }
    break;

  case 139:

/* Line 1464 of yacc.c  */
#line 647 "dmlyacc.yxx"
    {
            parsedData->insertOrderByField((char*)(yyvsp[(1) - (1)].stringval));
            free( (yyvsp[(1) - (1)].stringval) );
        }
    break;

  case 140:

/* Line 1464 of yacc.c  */
#line 652 "dmlyacc.yxx"
    {
            parsedData->insertOrderByField((char*)(yyvsp[(1) - (2)].stringval));
            free( (yyvsp[(1) - (2)].stringval) );
        }
    break;

  case 141:

/* Line 1464 of yacc.c  */
#line 657 "dmlyacc.yxx"
    {
            parsedData->insertOrderByField((char*)(yyvsp[(1) - (2)].stringval), true);
            free( (yyvsp[(1) - (2)].stringval) );
        }
    break;

  case 142:

/* Line 1464 of yacc.c  */
#line 663 "dmlyacc.yxx"
    {
            Predicate *pred;
            pred = parsedData->insertPredicate((Predicate*) (yyvsp[(1) - (3)].predicate), OpOr, (Predicate*) (yyvsp[(3) - (3)].predicate));
            //parsedData->setCondition((Predicate*)pred);
            (yyval.predicate)= pred;

        }
    break;

  case 143:

/* Line 1464 of yacc.c  */
#line 671 "dmlyacc.yxx"
    {
            Predicate *pred;
            pred = parsedData->insertPredicate((Predicate*) (yyvsp[(1) - (3)].predicate), OpAnd, (Predicate*) (yyvsp[(3) - (3)].predicate));
            //parsedData->setCondition((Predicate*)pred);
            (yyval.predicate)= pred;
        }
    break;

  case 144:

/* Line 1464 of yacc.c  */
#line 677 "dmlyacc.yxx"
    { (yyval.predicate)=(yyvsp[(2) - (3)].predicate); }
    break;

  case 145:

/* Line 1464 of yacc.c  */
#line 679 "dmlyacc.yxx"
    {
            Predicate *pred;
            pred = parsedData->insertPredicate((Predicate*) (yyvsp[(3) - (4)].predicate), OpNot, NULL);
            //parsedData->setCondition((Predicate*)pred);
            (yyval.predicate)= pred;

        }
    break;

  case 146:

/* Line 1464 of yacc.c  */
#line 687 "dmlyacc.yxx"
    {
            if( (yyvsp[(1) - (2)].stringval) == (char*) 1 )
            {
                Predicate *pred;
                pred = parsedData->insertPredicate((Predicate*) (yyvsp[(2) - (2)].predicate), OpNot, NULL);
                //parsedData->setCondition((Predicate*)pred);
                (yyval.predicate)= pred;
            }
            else
            {
                //parsedData->setCondition((Predicate*)$2);
                (yyval.predicate)=(yyvsp[(2) - (2)].predicate);
            }
        }
    break;

  case 147:

/* Line 1464 of yacc.c  */
#line 703 "dmlyacc.yxx"
    {
            Predicate *pred;
            pred = parsedData->insertPredicate((Predicate*) (yyvsp[(1) - (3)].predicate), OpOr, (Predicate*) (yyvsp[(3) - (3)].predicate));
            parsedData->setHavingCondition((Predicate*)pred);
            (yyval.predicate)= pred;

        }
    break;

  case 148:

/* Line 1464 of yacc.c  */
#line 711 "dmlyacc.yxx"
    {
            Predicate *pred;
            pred = parsedData->insertPredicate((Predicate*) (yyvsp[(1) - (3)].predicate), OpAnd, (Predicate*) (yyvsp[(3) - (3)].predicate));
            parsedData->setHavingCondition((Predicate*)pred);
            (yyval.predicate)= pred;
        }
    break;

  case 149:

/* Line 1464 of yacc.c  */
#line 717 "dmlyacc.yxx"
    { (yyval.predicate)=(yyvsp[(2) - (3)].predicate); }
    break;

  case 150:

/* Line 1464 of yacc.c  */
#line 719 "dmlyacc.yxx"
    {
            Predicate *pred;
            pred = parsedData->insertPredicate((Predicate*) (yyvsp[(3) - (4)].predicate), OpNot, NULL);
            parsedData->setHavingCondition((Predicate*)pred);
            (yyval.predicate)= pred;

        }
    break;

  case 151:

/* Line 1464 of yacc.c  */
#line 727 "dmlyacc.yxx"
    {
            if( (yyvsp[(1) - (2)].stringval) == (char*) 1 )
            {
                Predicate *pred;
                pred = parsedData->insertPredicate((Predicate*) (yyvsp[(2) - (2)].predicate), OpNot, NULL);
                parsedData->setHavingCondition((Predicate*)pred);
                (yyval.predicate)= pred;
            }
            else
            {
                parsedData->setHavingCondition((Predicate*)(yyvsp[(2) - (2)].predicate));
                (yyval.predicate)=(yyvsp[(2) - (2)].predicate);
            }
        }
    break;

  case 152:

/* Line 1464 of yacc.c  */
#line 743 "dmlyacc.yxx"
    {
            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(5) - (6)].stringval));
            Predicate *pred;
            void **ptr = parsedData->insertCondValueAndGetPtr((char*)(yyvsp[(3) - (6)].stringval), (char*)(yyvsp[(6) - (6)].stringval), false, AGG_MIN, true);
            pred = parsedData->insertPredicate((char*) (yyvsp[(3) - (6)].stringval), op, ptr, AGG_MIN);
            free( (yyvsp[(1) - (6)].stringval) ); free ((yyvsp[(3) - (6)].stringval)); free ((yyvsp[(5) - (6)].stringval)); free ((yyvsp[(6) - (6)].stringval));
            (yyval.predicate)=pred;
        }
    break;

  case 153:

/* Line 1464 of yacc.c  */
#line 752 "dmlyacc.yxx"
    {
            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(5) - (6)].stringval));
            Predicate *pred;
            void **ptr = parsedData->insertCondValueAndGetPtr((char*)(yyvsp[(3) - (6)].stringval), (char*)(yyvsp[(6) - (6)].stringval), false, AGG_MAX, true);
            pred = parsedData->insertPredicate((char*) (yyvsp[(3) - (6)].stringval), op, ptr, AGG_MAX);
            free( (yyvsp[(1) - (6)].stringval) ); free ((yyvsp[(3) - (6)].stringval)); free ((yyvsp[(5) - (6)].stringval)); free ((yyvsp[(6) - (6)].stringval));
            (yyval.predicate)=pred;
        }
    break;

  case 154:

/* Line 1464 of yacc.c  */
#line 761 "dmlyacc.yxx"
    {
            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(5) - (6)].stringval));
            Predicate *pred;
            void **ptr = parsedData->insertCondValueAndGetPtr((char*)(yyvsp[(3) - (6)].stringval), (char*)(yyvsp[(6) - (6)].stringval), false, AGG_SUM, true);
            pred = parsedData->insertPredicate((char*) (yyvsp[(3) - (6)].stringval), op, ptr, AGG_SUM);
            free( (yyvsp[(1) - (6)].stringval) ); free ((yyvsp[(3) - (6)].stringval)); free ((yyvsp[(5) - (6)].stringval)); free ((yyvsp[(6) - (6)].stringval));
            (yyval.predicate)=pred;
        }
    break;

  case 155:

/* Line 1464 of yacc.c  */
#line 770 "dmlyacc.yxx"
    {
            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(5) - (6)].stringval));
            Predicate *pred;
            void **ptr = parsedData->insertCondValueAndGetPtr((char*)(yyvsp[(3) - (6)].stringval), (char*)(yyvsp[(6) - (6)].stringval), false, AGG_AVG, true);
            pred = parsedData->insertPredicate((char*) (yyvsp[(3) - (6)].stringval), op, ptr, AGG_AVG);
            free( (yyvsp[(1) - (6)].stringval) ); free ((yyvsp[(3) - (6)].stringval)); free ((yyvsp[(5) - (6)].stringval)); free ((yyvsp[(6) - (6)].stringval));
            (yyval.predicate)=pred;
        }
    break;

  case 156:

/* Line 1464 of yacc.c  */
#line 779 "dmlyacc.yxx"
    {
            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(5) - (6)].stringval));
            Predicate *pred;
            void **ptr = parsedData->insertCondValueAndGetPtr((char*)(yyvsp[(3) - (6)].stringval), (char*)(yyvsp[(6) - (6)].stringval), false, AGG_COUNT, true);
            pred = parsedData->insertPredicate((char*) (yyvsp[(3) - (6)].stringval), op, ptr, AGG_COUNT);
            free( (yyvsp[(1) - (6)].stringval) ); free ((yyvsp[(3) - (6)].stringval)); free ((yyvsp[(5) - (6)].stringval)); free ((yyvsp[(6) - (6)].stringval));
            (yyval.predicate)=pred;
        }
    break;

  case 157:

/* Line 1464 of yacc.c  */
#line 790 "dmlyacc.yxx"
    {
            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(2) - (3)].stringval));
			bool opLike = false;
            if (op == OpLike) opLike = true;
            Predicate *pred;
            void **ptr = parsedData->insertCondValueAndGetPtr((char*)(yyvsp[(1) - (3)].stringval), (char*)(yyvsp[(3) - (3)].stringval), opLike);
            pred = parsedData->insertPredicate((char*) (yyvsp[(1) - (3)].stringval), op, ptr);
            free( (yyvsp[(1) - (3)].stringval) ); free((yyvsp[(2) - (3)].stringval)); free( (yyvsp[(3) - (3)].stringval) ); 
            (yyval.predicate)=pred;
        }
    break;

  case 158:

/* Line 1464 of yacc.c  */
#line 801 "dmlyacc.yxx"
    {
            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(2) - (3)].stringval));
            Predicate *pred;
            parsedData->insertCondValue((char*) (yyvsp[(1) - (3)].stringval));
            parsedData->insertCondValue((char*) (yyvsp[(3) - (3)].stringval));
            pred = parsedData->insertPredicate((char*) (yyvsp[(1) - (3)].stringval), op, (char*) (yyvsp[(3) - (3)].stringval));
            free( (yyvsp[(1) - (3)].stringval) ); free((yyvsp[(2) - (3)].stringval)); free( (yyvsp[(3) - (3)].stringval) );
            (yyval.predicate)=pred;
        }
    break;

  case 159:

/* Line 1464 of yacc.c  */
#line 812 "dmlyacc.yxx"
    {
            void **ptr1 = parsedData->insertCondValueAndGetPtr((char*)(yyvsp[(1) - (6)].stringval), (char*)(yyvsp[(4) - (6)].stringval));
            void **ptr2 = parsedData->insertCondValueAndGetPtr((char*)(yyvsp[(1) - (6)].stringval), (char*)(yyvsp[(6) - (6)].stringval));
            Predicate *finalPred;
 //           pred1 = parsedData->insertPredicate((char*) $1, OpGreaterThanEquals, ptr1);
//            pred2 = parsedData->insertPredicate((char*) $1, OpLessThanEquals, ptr2);
            finalPred = parsedData->insertBetPredicate((char*) (yyvsp[(1) - (6)].stringval), 
                        OpGreaterThanEquals, ptr1, OpLessThanEquals, ptr2);
                        //OpLessThanEquals, ptr2, OpGreaterThanEquals, ptr1);

            if( (yyvsp[(2) - (6)].stringval) == (char*) 1 )
                finalPred = parsedData->insertPredicate(finalPred, OpNot, NULL);
            free( (yyvsp[(1) - (6)].stringval) );  free( (yyvsp[(4) - (6)].stringval) );  free( (yyvsp[(6) - (6)].stringval) );
            (yyval.predicate)= finalPred;
        }
    break;

  case 160:

/* Line 1464 of yacc.c  */
#line 828 "dmlyacc.yxx"
    {
            ListIterator valIter = parsedData->getInValueList().getIterator();
            FieldValue *value1, *value2;
            Predicate *pred1, *pred2, *finalPred;
            void **ptr1, **ptr2;
            if (valIter.hasElement()) {
               value1 = (FieldValue*) valIter.nextElement();
               ptr1 = parsedData->insertCondValueAndGetPtr((char*)(yyvsp[(1) - (6)].stringval), value1->parsedString);
               pred1 = parsedData->insertPredicate((char*) (yyvsp[(1) - (6)].stringval), OpEquals, ptr1);
               finalPred=pred1;
            }
            while (valIter.hasElement()) {
               value2 = (FieldValue*) valIter.nextElement();
               ptr2 = parsedData->insertCondValueAndGetPtr((char*)(yyvsp[(1) - (6)].stringval), value2->parsedString);
               pred2 = parsedData->insertPredicate((char*) (yyvsp[(1) - (6)].stringval), OpEquals, ptr2);
               finalPred = parsedData->insertPredicate(pred1, OpOr, pred2);
               pred1= finalPred;     
            }
            parsedData->resetInValueList();
            if( (yyvsp[(2) - (6)].stringval) == (char*)1)
                finalPred = parsedData->insertPredicate(finalPred, OpNot, NULL);

            free( (yyvsp[(1) - (6)].stringval) );  
            (yyval.predicate)= finalPred;
        }
    break;

  case 161:

/* Line 1464 of yacc.c  */
#line 854 "dmlyacc.yxx"
    {
            Predicate *pred;
            parsedData->insertCondValue((char*) (yyvsp[(1) - (4)].stringval));
            pred = parsedData->insertNullPredicate((char*) (yyvsp[(1) - (4)].stringval), OpIsNull, false);
            free( (yyvsp[(1) - (4)].stringval) ); free((yyvsp[(2) - (4)].stringval)); free( (yyvsp[(3) - (4)].stringval) );
            (yyval.predicate)=pred;  
        }
    break;

  case 162:

/* Line 1464 of yacc.c  */
#line 862 "dmlyacc.yxx"
    {
            Predicate *pred;
            parsedData->insertCondValue((char*) (yyvsp[(1) - (3)].stringval));
            pred = parsedData->insertNullPredicate((char*) (yyvsp[(1) - (3)].stringval), OpIsNull, true);
            free( (yyvsp[(1) - (3)].stringval) ); free((yyvsp[(2) - (3)].stringval)); free( (yyvsp[(3) - (3)].stringval) );
            (yyval.predicate)=pred;  
        }
    break;

  case 163:

/* Line 1464 of yacc.c  */
#line 870 "dmlyacc.yxx"
    {
            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(2) - (3)].stringval));
            Predicate *pred;
            pred = parsedData->insertPredicate(((Expression*)(yyvsp[(1) - (3)].Expression)), op, ((Expression*)(yyvsp[(3) - (3)].Expression)));
            (yyval.predicate)=pred;
 
        }
    break;

  case 164:

/* Line 1464 of yacc.c  */
#line 878 "dmlyacc.yxx"
    {

            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(2) - (3)].stringval));
            parsedData->insertCondValue((char*) (yyvsp[(3) - (3)].stringval));
            Predicate *pred;
            pred = parsedData->insertPredicate(((Expression*)(yyvsp[(1) - (3)].Expression)), op, (char*) (yyvsp[(3) - (3)].stringval));
            (yyval.predicate)=pred;
            
        }
    break;

  case 165:

/* Line 1464 of yacc.c  */
#line 888 "dmlyacc.yxx"
    {
            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(2) - (3)].stringval));
            void **ptr = parsedData->insertCondValueAndGetPtr((char*)"dummy", (char*)(yyvsp[(3) - (3)].stringval), false, AGG_UNKNOWN, false, true);
            Predicate *pred;
            pred = parsedData->insertPredicate(((Expression*)(yyvsp[(1) - (3)].Expression)), op, ptr);
            (yyval.predicate)=pred;
        }
    break;

  case 166:

/* Line 1464 of yacc.c  */
#line 897 "dmlyacc.yxx"
    { (yyval.stringval)=(char*) 1;
	}
    break;

  case 167:

/* Line 1464 of yacc.c  */
#line 900 "dmlyacc.yxx"
    { (yyval.stringval)=(char*) 0; }
    break;

  case 168:

/* Line 1464 of yacc.c  */
#line 903 "dmlyacc.yxx"
    {
            parsedData->insertTableName((char*)(yyvsp[(1) - (1)].stringval));
            free( (yyvsp[(1) - (1)].stringval) );
        }
    break;

  case 169:

/* Line 1464 of yacc.c  */
#line 908 "dmlyacc.yxx"
    {
            parsedData->insertTableName((char*)(yyvsp[(1) - (3)].stringval), (char*)(yyvsp[(3) - (3)].stringval));
            free( (yyvsp[(1) - (3)].stringval) ); free((yyvsp[(3) - (3)].stringval));
        }
    break;

  case 170:

/* Line 1464 of yacc.c  */
#line 913 "dmlyacc.yxx"
    {
            parsedData->insertTableName((char*)(yyvsp[(1) - (2)].stringval), (char*)(yyvsp[(2) - (2)].stringval));
            free( (yyvsp[(1) - (2)].stringval) ); free((yyvsp[(2) - (2)].stringval));
        }
    break;

  case 171:

/* Line 1464 of yacc.c  */
#line 919 "dmlyacc.yxx"
    {
            parsedData->insertField((char*)(yyvsp[(1) - (1)].stringval));
            free( (yyvsp[(1) - (1)].stringval) );
            
        }
    break;

  case 172:

/* Line 1464 of yacc.c  */
#line 925 "dmlyacc.yxx"
    { 
            parsedData->insertField((char*)(yyvsp[(3) - (4)].stringval), AGG_MIN);
            free( (yyvsp[(1) - (4)].stringval) );
        }
    break;

  case 173:

/* Line 1464 of yacc.c  */
#line 930 "dmlyacc.yxx"
    { 
            parsedData->insertField((char*)(yyvsp[(3) - (4)].stringval), AGG_MAX);
            free( (yyvsp[(1) - (4)].stringval) );
        }
    break;

  case 174:

/* Line 1464 of yacc.c  */
#line 935 "dmlyacc.yxx"
    { 
            parsedData->insertField((char*)(yyvsp[(3) - (4)].stringval), AGG_SUM);
            free( (yyvsp[(1) - (4)].stringval) );
        }
    break;

  case 175:

/* Line 1464 of yacc.c  */
#line 940 "dmlyacc.yxx"
    { 
            parsedData->insertField((char*)(yyvsp[(3) - (4)].stringval), AGG_AVG);
            free( (yyvsp[(1) - (4)].stringval) );
        }
    break;

  case 176:

/* Line 1464 of yacc.c  */
#line 945 "dmlyacc.yxx"
    { 
            parsedData->insertField((char*)(yyvsp[(3) - (4)].stringval), AGG_COUNT);
            free( (yyvsp[(1) - (4)].stringval) );
        }
    break;

  case 177:

/* Line 1464 of yacc.c  */
#line 950 "dmlyacc.yxx"
    { 
            parsedData->insertField("*", AGG_COUNT);
            free( (yyvsp[(1) - (4)].stringval) );
        }
    break;

  case 178:

/* Line 1464 of yacc.c  */
#line 955 "dmlyacc.yxx"
    { 
            parsedData->insertField("*");
        }
    break;

  case 179:

/* Line 1464 of yacc.c  */
#line 959 "dmlyacc.yxx"
    {
            parsedData->insertField("*");
        }
    break;

  case 180:

/* Line 1464 of yacc.c  */
#line 963 "dmlyacc.yxx"
    { (yyval.stringval) = (yyvsp[(1) - (1)].stringval); }
    break;

  case 181:

/* Line 1464 of yacc.c  */
#line 964 "dmlyacc.yxx"
    { (yyval.stringval) = (yyvsp[(2) - (3)].stringval); }
    break;

  case 182:

/* Line 1464 of yacc.c  */
#line 966 "dmlyacc.yxx"
    { (yyval.stringval) = (yyvsp[(1) - (1)].stringval); }
    break;

  case 184:

/* Line 1464 of yacc.c  */
#line 968 "dmlyacc.yxx"
    { (yyval.stringval) = (yyvsp[(1) - (1)].stringval); }
    break;

  case 186:

/* Line 1464 of yacc.c  */
#line 970 "dmlyacc.yxx"
    { (yyval.stringval) = (yyvsp[(1) - (1)].stringval); }
    break;

  case 187:

/* Line 1464 of yacc.c  */
#line 971 "dmlyacc.yxx"
    { (yyval.stringval) = (char*) 0; }
    break;

  case 188:

/* Line 1464 of yacc.c  */
#line 973 "dmlyacc.yxx"
    {
              char *str=(char*)malloc(20);
              time_t rawtime;
              struct tm * timeinfo;
              time ( &rawtime );
              timeinfo = localtime ( &rawtime );
              sprintf(str,"%d-%d-%d %d:%d:%d",timeinfo->tm_year+1900,timeinfo->tm_mon+1,timeinfo->tm_mday,timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec);
              (yyval.stringval)=str;


        }
    break;

  case 189:

/* Line 1464 of yacc.c  */
#line 985 "dmlyacc.yxx"
    { (yyval.stringval) =  (yyvsp[(1) - (1)].stringval); }
    break;

  case 190:

/* Line 1464 of yacc.c  */
#line 987 "dmlyacc.yxx"
    {
             char *n;
             n=(char*)malloc(30);
             strcpy(n,"-");
             strcat(n,(char*)(yyvsp[(2) - (2)].stringval));
             (yyval.stringval)=n;
             free((yyvsp[(2) - (2)].stringval));
        }
    break;

  case 191:

/* Line 1464 of yacc.c  */
#line 995 "dmlyacc.yxx"
    { (yyval.stringval) =  (yyvsp[(2) - (2)].stringval); }
    break;

  case 192:

/* Line 1464 of yacc.c  */
#line 997 "dmlyacc.yxx"
    { (yyval.stringval) = (yyvsp[(1) - (1)].stringval); }
    break;

  case 193:

/* Line 1464 of yacc.c  */
#line 999 "dmlyacc.yxx"
    {
             char *d;
             d=(char*)malloc(30);
             strcpy(d,"-");
             strcat(d,(char*)(yyvsp[(2) - (2)].stringval));
             (yyval.stringval)=d;
             free((yyvsp[(2) - (2)].stringval));
        }
    break;

  case 194:

/* Line 1464 of yacc.c  */
#line 1007 "dmlyacc.yxx"
    { (yyval.stringval) = (yyvsp[(2) - (2)].stringval); }
    break;

  case 195:

/* Line 1464 of yacc.c  */
#line 1010 "dmlyacc.yxx"
    {
            if (!Conf::config.useCache())
            {
              printf("CACHE_TABLE is set to FALSE in csql.conf file.\n");
              free((yyvsp[(3) - (5)].stringval));
              YYABORT;
            }
            parsedData->setStmtType(CacheTableStatement);
            parsedData->setTableName((yyvsp[(3) - (5)].stringval)); 
        }
    break;

  case 196:

/* Line 1464 of yacc.c  */
#line 1021 "dmlyacc.yxx"
    {
            parsedData->setStmtType(CacheTableStatement);
            parsedData->setUnCache(true);
            parsedData->setTableName((yyvsp[(3) - (4)].stringval)); 
        }
    break;

  case 199:

/* Line 1464 of yacc.c  */
#line 1031 "dmlyacc.yxx"
    {
            parsedData->setHCondFld(true);
            parsedData->setHCondition((char*)(yyvsp[(2) - (2)].stringval));
         }
    break;

  case 201:

/* Line 1464 of yacc.c  */
#line 1038 "dmlyacc.yxx"
    {
            parsedData->setVCondFld(true);
            parsedData->setVCondition((char*)(yyvsp[(2) - (2)].stringval));
            free((yyvsp[(2) - (2)].stringval));
         }
    break;

  case 203:

/* Line 1464 of yacc.c  */
#line 1046 "dmlyacc.yxx"
    {
            parsedData->setPkFld(true);
            parsedData->setIndexName((char*)(yyvsp[(2) - (2)].stringval));
            free((yyvsp[(2) - (2)].stringval));
         }
    break;

  case 205:

/* Line 1464 of yacc.c  */
#line 1054 "dmlyacc.yxx"
    {
            parsedData->setDirect(true);
         }
    break;

  case 207:

/* Line 1464 of yacc.c  */
#line 1060 "dmlyacc.yxx"
    {
             parsedData->setDSN(true);
             parsedData->setPKTableName((char*)(yyvsp[(2) - (2)].stringval));
             free((yyvsp[(2) - (2)].stringval));
         }
    break;

  case 209:

/* Line 1464 of yacc.c  */
#line 1067 "dmlyacc.yxx"
    {
             parsedData->setNoSchema(true);
         }
    break;

  case 210:

/* Line 1464 of yacc.c  */
#line 1072 "dmlyacc.yxx"
    {
            parsedData->setStmtType(CreateTableStatement);
            parsedData->setTableName((yyvsp[(3) - (7)].stringval)); 
            free((yyvsp[(3) - (7)].stringval));
        }
    break;

  case 211:

/* Line 1464 of yacc.c  */
#line 1078 "dmlyacc.yxx"
    {
            parsedData->setStmtType(CreateIndexStatement);
            parsedData->setIndexName((yyvsp[(3) - (12)].stringval)); 
            parsedData->setTableName((yyvsp[(5) - (12)].stringval)); 
            free((yyvsp[(3) - (12)].stringval));
            free((yyvsp[(5) - (12)].stringval));
        }
    break;

  case 212:

/* Line 1464 of yacc.c  */
#line 1086 "dmlyacc.yxx"
    {
            parsedData->setStmtType(DropTableStatement);
            parsedData->setTableName((yyvsp[(3) - (3)].stringval)); 
            free((yyvsp[(3) - (3)].stringval));
        }
    break;

  case 213:

/* Line 1464 of yacc.c  */
#line 1092 "dmlyacc.yxx"
    {
            parsedData->setStmtType(DropIndexStatement);
            parsedData->setIndexName((yyvsp[(3) - (3)].stringval)); 
            free((yyvsp[(3) - (3)].stringval));
        }
    break;

  case 214:

/* Line 1464 of yacc.c  */
#line 1098 "dmlyacc.yxx"
    {
            parsedData->setStmtType(TruncateStatement);
            parsedData->setTableName((yyvsp[(3) - (4)].stringval)); 
            free((yyvsp[(3) - (4)].stringval));
        }
    break;

  case 216:

/* Line 1464 of yacc.c  */
#line 1106 "dmlyacc.yxx"
    {
            parsedData->setIndexType(hashIndex);
        }
    break;

  case 217:

/* Line 1464 of yacc.c  */
#line 1110 "dmlyacc.yxx"
    {
            parsedData->setIndexType(treeIndex);
        }
    break;

  case 218:

/* Line 1464 of yacc.c  */
#line 1114 "dmlyacc.yxx"
    {
            parsedData->setIndexType(trieIndex);
        }
    break;

  case 219:

/* Line 1464 of yacc.c  */
#line 1118 "dmlyacc.yxx"
    {
            parsedData->setIndexType(hashIndex);
        }
    break;

  case 221:

/* Line 1464 of yacc.c  */
#line 1124 "dmlyacc.yxx"
    {
            parsedData->setUnique(true);
        }
    break;

  case 222:

/* Line 1464 of yacc.c  */
#line 1128 "dmlyacc.yxx"
    {
            parsedData->setUnique(true);
            parsedData->setPrimary(true);
        }
    break;

  case 223:

/* Line 1464 of yacc.c  */
#line 1133 "dmlyacc.yxx"
    {
            parsedData->setUnique(false);
            parsedData->setPrimary(false);
        }
    break;

  case 225:

/* Line 1464 of yacc.c  */
#line 1140 "dmlyacc.yxx"
    {
            parsedData->setBucketSize(atoi((yyvsp[(2) - (2)].stringval)));
            free((yyvsp[(2) - (2)].stringval));
        }
    break;

  case 231:

/* Line 1464 of yacc.c  */
#line 1156 "dmlyacc.yxx"
    {
            parsedData->insertFldDef();
        }
    break;

  case 233:

/* Line 1464 of yacc.c  */
#line 1165 "dmlyacc.yxx"
    {
            parsedData->setFldName((yyvsp[(1) - (1)].stringval));
            free((yyvsp[(1) - (1)].stringval));
        }
    break;

  case 235:

/* Line 1464 of yacc.c  */
#line 1171 "dmlyacc.yxx"
    {
            DbRetVal rv = parsedData->setFldLength(atoi((yyvsp[(2) - (3)].stringval)));
            if (rv != OK) {
                yyerror("Binary field length < 256");
                free((yyvsp[(2) - (3)].stringval));
                YYABORT;
            }
            free((yyvsp[(2) - (3)].stringval));
        }
    break;

  case 237:

/* Line 1464 of yacc.c  */
#line 1184 "dmlyacc.yxx"
    {
            DbRetVal rv = parsedData->setDefaultValue((yyvsp[(2) - (2)].stringval));
            if(rv != OK){
                yyerror("Invalid Default value.");
                free((yyvsp[(2) - (2)].stringval));
                YYABORT;
            }
            free((yyvsp[(2) - (2)].stringval));
        }
    break;

  case 239:

/* Line 1464 of yacc.c  */
#line 1197 "dmlyacc.yxx"
    {
            parsedData->setFldNotNull(true);
        }
    break;

  case 246:

/* Line 1464 of yacc.c  */
#line 1211 "dmlyacc.yxx"
    {
            parsedData->setForeign(true);
            parsedData->setPKTableName((char*)(yyvsp[(7) - (10)].stringval));
            parsedData->insertForeignKeyList();
        }
    break;

  case 250:

/* Line 1464 of yacc.c  */
#line 1223 "dmlyacc.yxx"
    {
           parsedData->insertFKField((char*)(yyvsp[(1) - (1)].stringval));
           free((yyvsp[(1) - (1)].stringval));
        }
    break;

  case 254:

/* Line 1464 of yacc.c  */
#line 1234 "dmlyacc.yxx"
    {
           parsedData->insertPKField((char*)(yyvsp[(1) - (1)].stringval));
           free((yyvsp[(1) - (1)].stringval));
        }
    break;

  case 255:

/* Line 1464 of yacc.c  */
#line 1241 "dmlyacc.yxx"
    {
           parsedData->setPrimary(true);
        }
    break;

  case 257:

/* Line 1464 of yacc.c  */
#line 1247 "dmlyacc.yxx"
    {
           DataType type = parsedData->getFldType();
           if(type > 4)
           {
               yyerror("AUTO_INCREMENT KEY can't be created other than INTEGER field ");
               free((yyvsp[(1) - (1)].stringval));
               YYABORT;
           }
           DbRetVal ret = parsedData->setAutoIncreament(true);
           if(ret != OK){
               yyerror("A table should have ony one AUTO_INCREMENT KEY ");
               free((yyvsp[(1) - (1)].stringval));
               YYABORT;
           }
           parsedData->setFldNotNull(true);
           parsedData->setAutoFldName(parsedData->getFldName());
           parsedData->setPrimary(true);
        }
    break;

  case 258:

/* Line 1464 of yacc.c  */
#line 1268 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeInt);
        }
    break;

  case 259:

/* Line 1464 of yacc.c  */
#line 1272 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeLong);
        }
    break;

  case 260:

/* Line 1464 of yacc.c  */
#line 1276 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeShort);
        }
    break;

  case 261:

/* Line 1464 of yacc.c  */
#line 1280 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeLongLong);
        }
    break;

  case 262:

/* Line 1464 of yacc.c  */
#line 1284 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeByteInt);
        }
    break;

  case 263:

/* Line 1464 of yacc.c  */
#line 1288 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeFloat);
        }
    break;

  case 264:

/* Line 1464 of yacc.c  */
#line 1292 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeDouble);
        }
    break;

  case 265:

/* Line 1464 of yacc.c  */
#line 1297 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeDate);
        }
    break;

  case 266:

/* Line 1464 of yacc.c  */
#line 1302 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeTime);
        }
    break;

  case 267:

/* Line 1464 of yacc.c  */
#line 1307 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeTimeStamp);
        }
    break;

  case 268:

/* Line 1464 of yacc.c  */
#line 1312 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeString);
            parsedData->setFldLength(2);
        }
    break;

  case 269:

/* Line 1464 of yacc.c  */
#line 1318 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeVarchar);
            parsedData->setFldLength(2);
        }
    break;

  case 270:

/* Line 1464 of yacc.c  */
#line 1324 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeBinary);
            parsedData->setFldLength(1);
        }
    break;



/* Line 1464 of yacc.c  */
#line 4256 "dmlyacc.cxx"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



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
		      yytoken, &yylval);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1684 of yacc.c  */
#line 1329 "dmlyacc.yxx"


extern int lexEof;
void yyerror(const char* Msg) { 
    if( lexEof == 0 )
        fprintf(stderr, "[Parser: %s] %s\n", Msg, yytext);

    return;
}

