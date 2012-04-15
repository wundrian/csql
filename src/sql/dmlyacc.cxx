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
#define YYFINAL  70
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   896

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  136
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  96
/* YYNRULES -- Number of rules.  */
#define YYNRULES  267
/* YYNRULES -- Number of states.  */
#define YYNSTATES  607

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
      72,    80,    84,    91,    96,   104,   106,   108,   110,   112,
     116,   117,   126,   142,   158,   162,   164,   167,   171,   174,
     176,   178,   180,   183,   186,   199,   202,   203,   205,   206,
     209,   211,   214,   216,   220,   223,   225,   228,   235,   243,
     248,   249,   250,   252,   253,   255,   258,   268,   269,   273,
     276,   278,   281,   284,   286,   289,   295,   302,   304,   305,
     308,   310,   313,   317,   321,   325,   329,   333,   337,   341,
     345,   349,   352,   355,   357,   359,   366,   374,   382,   389,
     397,   405,   414,   422,   430,   437,   442,   447,   449,   451,
     453,   455,   457,   459,   461,   463,   465,   467,   469,   472,
     473,   477,   478,   482,   483,   486,   491,   492,   495,   496,
     499,   501,   504,   506,   509,   511,   514,   516,   519,   522,
     526,   530,   534,   539,   542,   546,   550,   554,   559,   562,
     569,   576,   583,   590,   597,   601,   605,   612,   619,   624,
     628,   632,   636,   640,   642,   643,   645,   649,   652,   654,
     659,   664,   669,   674,   679,   684,   686,   689,   691,   695,
     697,   699,   701,   703,   705,   707,   711,   713,   716,   719,
     721,   724,   727,   733,   738,   745,   746,   749,   750,   753,
     754,   757,   758,   760,   761,   764,   765,   767,   775,   788,
     792,   796,   801,   802,   805,   808,   811,   812,   813,   815,
     817,   818,   819,   822,   824,   828,   831,   833,   836,   838,
     845,   847,   848,   852,   853,   856,   857,   860,   862,   864,
     868,   871,   873,   876,   887,   890,   892,   895,   897,   900,
     902,   905,   907,   914,   915,   917,   919,   921,   923,   925,
     927,   929,   931,   933,   935,   937,   939,   941
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     137,     0,    -1,   147,    -1,   158,    -1,   164,    -1,   165,
      -1,   206,    -1,   145,    -1,   198,    -1,   144,    -1,   140,
      -1,   143,    -1,   139,    -1,   138,    -1,   146,    -1,   109,
      52,   194,   111,   133,   210,   134,   166,    -1,   109,    52,
     194,    62,   112,   194,   166,    -1,   109,    52,   194,   113,
     133,   213,   134,   166,    -1,   114,    52,   194,   115,   194,
     166,    -1,   109,    52,   194,   114,   112,   194,   115,   194,
     166,    -1,   109,    56,   194,   114,   115,   194,   166,    -1,
     110,    68,   166,    -1,    51,   107,   194,   108,    11,   166,
      -1,    62,   107,   194,   166,    -1,   109,   107,   194,    49,
     108,    11,   166,    -1,    27,    -1,    42,    -1,    48,    -1,
      47,    -1,   117,   115,   187,    -1,    -1,   116,   141,    57,
     194,   115,   194,   142,   166,    -1,    51,    52,   194,    33,
      27,   149,   150,    28,   153,   176,   177,   180,   178,   179,
     166,    -1,    42,    43,   194,    33,    27,   149,   150,    28,
     153,   176,   177,   180,   178,   179,   166,    -1,    66,    52,
     194,    -1,    18,    -1,    19,   192,    -1,    19,    56,   192,
      -1,    20,   192,    -1,    22,    -1,    24,    -1,    23,    -1,
      25,   192,    -1,    26,   192,    -1,   148,    27,   149,   150,
      28,   153,   176,   177,   180,   178,   179,   166,    -1,    45,
      46,    -1,    -1,   130,    -1,    -1,   150,   151,    -1,   152,
      -1,   132,   152,    -1,   193,    -1,   193,    33,   194,    -1,
     153,   157,    -1,   192,    -1,   192,   154,    -1,    36,   156,
     192,    57,   187,   154,    -1,    40,   155,   156,   192,    57,
     187,   154,    -1,    38,   156,   192,   154,    -1,    -1,    -1,
      37,    -1,    -1,    39,    -1,   132,   192,    -1,    42,    43,
     194,   159,    44,   133,   160,   134,   166,    -1,    -1,   133,
     150,   134,    -1,   160,   161,    -1,   195,    -1,   132,   195,
      -1,   162,   163,    -1,   195,    -1,   132,   195,    -1,    47,
      28,   194,   176,   166,    -1,    48,   194,    49,   167,   176,
     166,    -1,   131,    -1,    -1,   167,   168,    -1,   169,    -1,
     132,   169,    -1,   194,    16,   170,    -1,   194,    16,   195,
      -1,   194,    16,    50,    -1,   170,     8,   170,    -1,   170,
       9,   170,    -1,   170,     7,   170,    -1,   170,     5,   170,
      -1,   170,     6,   170,    -1,   133,   170,   134,    -1,     6,
     170,    -1,     5,   170,    -1,   171,    -1,   175,    -1,    89,
     133,   175,   132,   175,   134,    -1,    90,   133,   175,    98,
     175,   174,   134,    -1,    91,   133,   175,    98,   175,   174,
     134,    -1,    99,   133,   175,   132,   175,   134,    -1,   100,
     133,   175,    98,   175,   173,   134,    -1,   101,   133,   175,
      98,   175,   173,   134,    -1,   102,   133,   172,   132,   175,
     132,   175,   134,    -1,   103,   133,   175,    98,   175,   172,
     134,    -1,   104,   133,   175,    98,   175,   172,   134,    -1,
     105,   133,   172,    28,   175,   134,    -1,    81,   133,   175,
     134,    -1,    83,   133,   175,   134,    -1,   173,    -1,   174,
      -1,    92,    -1,    93,    -1,    94,    -1,    95,    -1,    96,
      -1,    97,    -1,   194,    -1,   195,    -1,    50,    -1,    29,
     187,    -1,    -1,   124,   125,   181,    -1,    -1,   127,   125,
     184,    -1,    -1,    34,    13,    -1,    34,    13,    35,    13,
      -1,    -1,   126,   188,    -1,    -1,   181,   182,    -1,   183,
      -1,   132,   183,    -1,   194,    -1,   184,   185,    -1,   186,
      -1,   132,   186,    -1,   194,    -1,   194,   128,    -1,   194,
     129,    -1,   187,     3,   187,    -1,   187,     4,   187,    -1,
     133,   187,   134,    -1,    32,   133,   187,   134,    -1,   191,
     190,    -1,   188,     3,   188,    -1,   188,     4,   188,    -1,
     133,   188,   134,    -1,    32,   133,   188,   134,    -1,   191,
     189,    -1,   119,   133,   194,   134,    16,   195,    -1,   120,
     133,   194,   134,    16,   195,    -1,   122,   133,   194,   134,
      16,   195,    -1,   121,   133,   194,   134,    16,   195,    -1,
     123,   133,   194,   134,    16,   195,    -1,   194,    16,   195,
      -1,   194,    16,   194,    -1,   194,   191,    30,   195,     4,
     195,    -1,   194,   191,    31,   133,   162,   134,    -1,   194,
      41,    32,    50,    -1,   194,    41,    50,    -1,   171,    16,
     171,    -1,   171,    16,   194,    -1,   171,    16,   195,    -1,
      32,    -1,    -1,   194,    -1,   194,    33,   194,    -1,   194,
     194,    -1,   194,    -1,   119,   133,   194,   134,    -1,   120,
     133,   194,   134,    -1,   122,   133,   194,   134,    -1,   121,
     133,   194,   134,    -1,   123,   133,   194,   134,    -1,   123,
     133,     7,   134,    -1,     7,    -1,   194,     7,    -1,    12,
      -1,   135,    12,   135,    -1,    11,    -1,   196,    -1,    14,
      -1,   197,    -1,    17,    -1,    50,    -1,   106,   133,   134,
      -1,    13,    -1,     6,    13,    -1,     5,    13,    -1,    15,
      -1,     6,    15,    -1,     5,    15,    -1,    68,    52,   194,
     199,   166,    -1,    74,    52,   194,   166,    -1,   200,   201,
     202,   203,   204,   205,    -1,    -1,    69,   195,    -1,    -1,
      70,   195,    -1,    -1,    71,   194,    -1,    -1,    72,    -1,
      -1,    73,   195,    -1,    -1,    75,    -1,    51,    52,   194,
     133,   210,   134,   166,    -1,    51,    56,   194,    57,   194,
     133,   150,   134,   208,   207,   209,   166,    -1,    62,    52,
     194,    -1,    62,    56,   194,    -1,    67,    52,   194,   166,
      -1,    -1,    58,   208,    -1,    59,   208,    -1,    60,   208,
      -1,    -1,    -1,    61,    -1,    53,    -1,    -1,    -1,    63,
      13,    -1,   211,    -1,   211,   132,   219,    -1,   211,   212,
      -1,   213,    -1,   132,   213,    -1,   214,    -1,   215,   231,
     216,   218,   217,   230,    -1,   194,    -1,    -1,   133,    13,
     134,    -1,    -1,    55,   195,    -1,    -1,    32,    50,    -1,
     229,    -1,   220,    -1,   229,   132,   220,    -1,   220,   221,
      -1,   222,    -1,   132,   222,    -1,    64,    54,   133,   223,
     134,    65,   194,   133,   226,   134,    -1,   223,   224,    -1,
     225,    -1,   132,   225,    -1,   194,    -1,   226,   227,    -1,
     228,    -1,   132,   228,    -1,   194,    -1,    53,    54,   133,
     150,   134,   209,    -1,    -1,    21,    -1,    76,    -1,    77,
      -1,    78,    -1,    84,    -1,    86,    -1,    85,    -1,    79,
      -1,    81,    -1,    83,    -1,    80,    -1,    82,    -1,    88,
      -1,    87,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    44,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    58,    65,    73,    79,    88,
      97,   106,   111,   118,   124,   137,   137,   137,   137,   139,
     140,   142,   156,   163,   170,   177,   182,   187,   193,   198,
     203,   208,   213,   218,   224,   230,   234,   236,   240,   242,
     243,   245,   247,   248,   254,   255,   256,   258,   272,   285,
     289,   291,   292,   294,   295,   297,   303,   311,   312,   315,
     316,   322,   329,   330,   336,   343,   351,   359,   360,   363,
     364,   367,   369,   374,   379,   385,   391,   397,   403,   409,
     415,   419,   423,   427,   428,   430,   437,   444,   452,   459,
     466,   473,   484,   491,   498,   510,   518,   526,   531,   537,
     542,   547,   553,   558,   563,   569,   576,   584,   593,   606,
     608,   609,   611,   612,   614,   618,   622,   624,   625,   627,
     628,   630,   632,   638,   639,   641,   643,   648,   653,   659,
     667,   674,   675,   683,   699,   707,   714,   715,   723,   739,
     748,   757,   766,   775,   786,   797,   808,   824,   850,   858,
     866,   874,   884,   893,   897,   899,   904,   909,   915,   921,
     926,   931,   936,   941,   946,   951,   955,   960,   961,   963,
     964,   965,   966,   967,   968,   969,   982,   983,   992,   994,
     995,  1004,  1006,  1017,  1024,  1026,  1027,  1033,  1034,  1041,
    1042,  1049,  1050,  1055,  1056,  1062,  1063,  1068,  1074,  1082,
    1088,  1094,  1101,  1102,  1106,  1110,  1115,  1119,  1120,  1124,
    1130,  1135,  1136,  1142,  1143,  1145,  1146,  1149,  1152,  1158,
    1161,  1166,  1167,  1179,  1180,  1192,  1193,  1198,  1199,  1200,
    1202,  1203,  1205,  1207,  1214,  1215,  1217,  1219,  1225,  1226,
    1228,  1230,  1237,  1242,  1243,  1264,  1268,  1272,  1276,  1280,
    1284,  1288,  1293,  1298,  1303,  1308,  1314,  1320
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
  "user_manager_statement", "priviledge", "restrict_opt",
  "grant_statement", "copy_table_statement", "internal_statement", "other",
  "select_statement", "opt_explain", "opt_distinct", "field_list",
  "field_list_L", "field_with_as", "table_list", "join_exp", "opt_outer",
  "opt_join", "table_list_L", "insert_statement", "field_list_opt",
  "value_list", "value_list_L", "invalue_list", "invalue_list_L",
  "delete_statement", "update_statement", "semicolon_opt", "assign_list",
  "assign_list_L", "assign_stmt", "stmt_exp", "function_opt",
  "datetime_opt", "time_opt", "date_opt", "atom", "where_clause_opt",
  "group_by_opt", "order_by_opt", "limit_opt", "having_opt",
  "group_field_list", "group_field_list_L", "group_field",
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
     138,   139,   140,   140,   140,   141,   141,   141,   141,   142,
     142,   143,   144,   144,   145,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   147,   148,   148,   149,   149,   150,
     150,   151,   152,   152,   153,   153,   153,   154,   154,   154,
     154,   155,   155,   156,   156,   157,   158,   159,   159,   160,
     160,   161,   162,   162,   163,   164,   165,   166,   166,   167,
     167,   168,   169,   169,   169,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   171,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   171,   172,   172,   173,
     173,   173,   174,   174,   174,   175,   175,   175,   176,   176,
     177,   177,   178,   178,   179,   179,   179,   180,   180,   181,
     181,   182,   183,   184,   184,   185,   186,   186,   186,   187,
     187,   187,   187,   187,   188,   188,   188,   188,   188,   189,
     189,   189,   189,   189,   190,   190,   190,   190,   190,   190,
     190,   190,   190,   191,   191,   192,   192,   192,   193,   193,
     193,   193,   193,   193,   193,   193,   193,   194,   194,   195,
     195,   195,   195,   195,   195,   195,   196,   196,   196,   197,
     197,   197,   198,   198,   199,   200,   200,   201,   201,   202,
     202,   203,   203,   204,   204,   205,   205,   206,   206,   206,
     206,   206,   207,   207,   207,   207,   207,   208,   208,   208,
     208,   209,   209,   210,   210,   211,   211,   212,   213,   214,
     215,   216,   216,   217,   217,   218,   218,   219,   219,   219,
     220,   220,   221,   222,   223,   223,   224,   225,   226,   226,
     227,   228,   229,   230,   230,   231,   231,   231,   231,   231,
     231,   231,   231,   231,   231,   231,   231,   231
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     8,     7,     8,     6,     9,
       7,     3,     6,     4,     7,     1,     1,     1,     1,     3,
       0,     8,    15,    15,     3,     1,     2,     3,     2,     1,
       1,     1,     2,     2,    12,     2,     0,     1,     0,     2,
       1,     2,     1,     3,     2,     1,     2,     6,     7,     4,
       0,     0,     1,     0,     1,     2,     9,     0,     3,     2,
       1,     2,     2,     1,     2,     5,     6,     1,     0,     2,
       1,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     1,     1,     6,     7,     7,     6,     7,
       7,     8,     7,     7,     6,     4,     4,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     0,
       3,     0,     3,     0,     2,     4,     0,     2,     0,     2,
       1,     2,     1,     2,     1,     2,     1,     2,     2,     3,
       3,     3,     4,     2,     3,     3,     3,     4,     2,     6,
       6,     6,     6,     6,     3,     3,     6,     6,     4,     3,
       3,     3,     3,     1,     0,     1,     3,     2,     1,     4,
       4,     4,     4,     4,     4,     1,     2,     1,     3,     1,
       1,     1,     1,     1,     1,     3,     1,     2,     2,     1,
       2,     2,     5,     4,     6,     0,     2,     0,     2,     0,
       2,     0,     1,     0,     2,     0,     1,     7,    12,     3,
       3,     4,     0,     2,     2,     2,     0,     0,     1,     1,
       0,     0,     2,     1,     3,     2,     1,     2,     1,     6,
       1,     0,     3,     0,     2,     0,     2,     1,     1,     3,
       2,     1,     2,    10,     2,     1,     2,     1,     2,     1,
       2,     1,     6,     0,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
      46,    35,     0,     0,    39,    41,    40,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    13,    12,    10,    11,     9,     7,
      14,     2,     0,     3,     4,     5,     8,     6,   177,     0,
       0,    36,   165,    38,    42,    43,     0,    45,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    78,     0,    25,    26,    28,    27,     0,
       1,    48,    37,     0,     0,   167,    67,   119,     0,     0,
       0,     0,   209,   210,    78,    34,    78,   195,    78,     0,
       0,     0,    77,    21,     0,     0,    47,     0,   178,   166,
       0,     0,     0,   164,    78,   119,    80,     0,     0,     0,
       0,     0,    23,   211,     0,    78,   197,   193,     0,     0,
       0,     0,     0,     0,     0,     0,   175,     0,     0,     0,
       0,     0,     0,    50,    52,   168,    48,     0,     0,   163,
     164,   118,     0,    75,     0,    79,    78,     0,    48,   230,
       0,   223,   226,   228,     0,     0,    78,     0,     0,   179,
     186,   181,   189,   183,   184,     0,   196,   180,   182,   192,
       0,   199,     0,     0,     0,     0,     0,     0,    78,     0,
       0,     0,     0,     0,     0,     0,     0,    49,     0,   176,
       0,    68,     0,   164,     0,   164,   164,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     143,   164,    81,    76,     0,     0,   117,     0,    82,    93,
      94,   115,   116,     0,    78,     0,   225,   255,   256,   257,
     261,   264,   262,   265,   263,   258,   260,   259,   267,   266,
     231,     0,    22,   188,   191,   187,   190,     0,   198,     0,
     201,    78,     0,     0,     0,    78,    78,    18,    30,     0,
       0,     0,     0,     0,     0,   119,    55,    51,    53,     0,
       0,    70,     0,   141,   139,   140,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     163,     0,     0,   186,   189,   117,    92,   116,   186,   189,
      91,     0,     0,     0,     0,     0,     0,     0,   207,     0,
       0,   227,   224,   238,   241,   237,     0,   235,     0,   185,
     200,   202,   203,    16,    78,    78,     0,    20,    24,     0,
      78,   169,   170,   172,   171,   174,   173,     0,    54,   121,
      63,    63,    61,    56,     0,     0,    78,    69,   142,     0,
       0,     0,     0,     0,     0,     0,     0,   109,   110,   111,
     112,   113,   114,     0,   107,   108,     0,     0,     0,   160,
     161,   162,   155,   154,     0,   159,     0,     0,    90,    88,
      89,    87,    85,    86,     0,     0,     0,     0,   240,     0,
       0,     0,   233,   217,     0,   205,    15,    17,    78,   164,
      31,    65,     0,   128,    64,     0,     0,    62,    63,   119,
      71,    66,   105,   106,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   158,     0,     0,   119,     0,     0,
     242,   239,   232,   236,     0,   253,   219,   218,   212,   204,
     206,   194,    19,    29,     0,   164,   123,     0,    60,     0,
     121,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    73,   121,     0,   247,     0,   245,   234,
     254,   229,   217,   217,   217,   221,   120,   130,   132,   163,
     164,   127,     0,     0,   126,   164,    59,     0,   128,    95,
       0,     0,    98,     0,     0,     0,     0,     0,   104,   156,
       0,   157,    72,   128,   221,     0,     0,   244,   213,   214,
     215,     0,    78,     0,   129,   164,     0,   164,   164,     0,
       0,     0,     0,     0,   148,     0,     0,    78,    60,   164,
     123,    96,    97,    99,   100,     0,   102,   103,    74,   123,
     252,   246,     0,   222,   208,   131,     0,   146,   144,   145,
       0,     0,     0,     0,     0,   122,   134,   136,   124,    44,
      57,    60,   126,   101,   126,     0,   147,     0,     0,     0,
       0,     0,     0,   133,   137,   138,     0,    58,    78,    78,
       0,     0,     0,     0,     0,     0,   135,   125,    33,    32,
     251,     0,   249,     0,     0,     0,     0,     0,     0,   243,
     248,   149,   150,   152,   151,   153,   250
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    23,    24,    25,    26,    69,   330,    27,    28,    29,
      30,    31,    32,    97,   132,   187,   133,   265,   343,   408,
     405,   338,    33,   102,   270,   347,   462,   502,    34,    35,
      93,   105,   145,   106,   218,   219,   363,   364,   365,   220,
     104,   403,   484,   527,   446,   476,   514,   477,   555,   573,
     556,   141,   481,   524,   210,   142,   266,   134,   221,   297,
     167,   168,    36,   115,   116,   171,   250,   322,   395,   441,
      37,   475,   438,   512,   150,   151,   226,   152,   153,   154,
     317,   435,   392,   312,   313,   388,   314,   467,   507,   468,
     591,   600,   592,   315,   471,   240
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -444
static const yytype_int16 yypact[] =
{
     780,  -444,    57,     3,  -444,  -444,  -444,     3,     3,    37,
      48,    72,     3,    60,    68,    83,   144,   157,   167,   105,
     121,   179,   158,   199,  -444,  -444,  -444,  -444,  -444,  -444,
    -444,  -444,   198,  -444,  -444,  -444,  -444,  -444,  -444,     3,
     230,  -444,     2,  -444,  -444,  -444,     3,  -444,     3,   207,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,   134,     3,  -444,  -444,  -444,  -444,   211,
    -444,   163,  -444,   171,     3,  -444,     1,   280,     3,     8,
     265,   217,  -444,  -444,   134,  -444,   134,   275,   134,    84,
     252,   319,  -444,  -444,   254,     3,  -444,    94,  -444,  -444,
     343,    94,   327,    -1,   134,     7,  -444,   356,   346,     3,
       3,   363,  -444,  -444,   104,   134,   306,  -444,   266,   244,
     248,   267,   269,   289,     3,   270,  -444,   268,   276,   278,
     283,   285,    -4,  -444,   365,   392,   163,    28,   287,   288,
      -1,   122,   334,  -444,     3,  -444,   134,   482,   163,  -444,
     274,   282,  -444,  -444,   374,   295,   134,   150,   231,  -444,
    -444,  -444,  -444,  -444,  -444,   296,  -444,  -444,  -444,  -444,
     104,   329,     3,     3,     3,     3,     3,   391,   134,     3,
       3,     3,     3,     3,    31,     3,    94,  -444,     3,  -444,
      94,  -444,   104,    -1,    17,    -1,    -1,   297,   298,   299,
     307,   308,   310,   311,   312,   313,   315,   330,   331,   394,
    -444,   111,  -444,  -444,   530,   587,    13,   634,   229,  -444,
    -444,  -444,    16,    94,   134,    15,  -444,  -444,  -444,  -444,
    -444,  -444,  -444,  -444,  -444,  -444,  -444,  -444,  -444,  -444,
     332,    94,  -444,  -444,  -444,  -444,  -444,   279,  -444,     3,
     350,   134,   336,   337,   351,   134,   134,  -444,   355,   339,
     340,   341,   342,   344,   345,    61,   184,  -444,  -444,     4,
     128,  -444,    19,  -444,   464,  -444,   261,   261,   261,   261,
     261,   261,   261,   261,   255,   261,   261,   255,   691,   277,
    -444,   137,   173,  -444,  -444,  -444,  -444,  -444,  -444,  -444,
    -444,    77,   634,   634,   634,   634,   634,    36,  -444,   423,
     426,  -444,  -444,   349,  -444,   352,   469,   451,   147,  -444,
    -444,  -444,   412,  -444,   134,   134,     3,  -444,  -444,   371,
     134,  -444,  -444,  -444,  -444,  -444,  -444,     3,  -444,   366,
     452,   452,   455,  -444,     3,   104,   134,  -444,  -444,   364,
     367,   368,   404,   407,   375,   408,   410,  -444,  -444,  -444,
    -444,  -444,  -444,   377,  -444,  -444,   419,   420,   491,  -444,
    -444,  -444,  -444,  -444,   460,  -444,   104,   387,  -444,   262,
     262,  -444,  -444,  -444,     3,   388,   389,   461,  -444,   461,
     390,   476,   472,   141,   104,   453,  -444,  -444,   134,    -1,
    -444,  -444,   405,   403,  -444,     3,     3,  -444,   452,    61,
    -444,  -444,  -444,  -444,   261,   261,   261,   261,   261,   261,
     261,   261,   261,   261,  -444,   527,   104,    61,    94,     3,
    -444,   349,  -444,  -444,   104,   512,  -444,  -444,   245,  -444,
    -444,  -444,  -444,   122,     3,    43,   411,   477,   184,     3,
     366,   424,   224,   224,   425,   246,   246,   414,   255,   255,
     427,   104,   178,  -444,   366,   182,  -444,   209,  -444,  -444,
    -444,  -444,   141,   141,   141,   474,   421,  -444,  -444,   406,
      43,   281,   177,   429,   523,    -1,  -444,   503,   403,  -444,
     428,   430,  -444,   432,   433,   261,   434,   435,  -444,  -444,
     104,  -444,  -444,   403,   474,     3,   509,  -444,  -444,  -444,
    -444,   562,   134,     3,  -444,    43,    22,    43,    43,   443,
     444,   446,   456,   457,  -444,     3,   578,   134,   223,    -1,
     411,  -444,  -444,  -444,  -444,   463,  -444,  -444,  -444,   411,
    -444,  -444,     3,  -444,  -444,  -444,    25,  -444,   590,  -444,
       3,     3,     3,     3,     3,   471,  -444,   205,   560,  -444,
    -444,   223,   523,  -444,   523,   473,  -444,   475,   478,   480,
     484,   488,     3,  -444,  -444,  -444,   592,  -444,   134,   134,
       3,   591,   594,   600,   607,   608,  -444,  -444,  -444,  -444,
    -444,   225,  -444,   104,   104,   104,   104,   104,     3,  -444,
    -444,  -444,  -444,  -444,  -444,  -444,  -444
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -444,  -444,  -444,  -444,  -444,  -444,  -444,  -444,  -444,  -444,
    -444,  -444,  -444,    82,   -92,  -444,   422,  -314,  -431,  -444,
    -294,  -444,  -444,  -444,  -444,  -444,  -444,  -444,  -444,  -444,
     -23,  -444,  -444,   481,    26,  -130,  -268,   -94,   -88,   -28,
    -101,  -373,  -443,  -204,  -400,  -444,  -444,   113,  -444,  -444,
      55,  -122,  -413,  -444,  -444,  -200,     0,  -444,    -2,   -81,
    -444,  -444,  -444,  -444,  -444,  -444,  -444,  -444,  -444,  -444,
    -444,  -444,  -118,   124,   465,  -444,  -444,   -96,  -444,  -444,
    -444,  -444,  -444,  -444,   253,  -444,   256,  -444,  -444,   136,
    -444,  -444,    46,  -444,  -444,  -444
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -85
static const yytype_int16 yytable[] =
{
      42,    42,    41,    43,   146,    42,    42,    44,    45,   137,
      49,   292,   209,   -84,    38,    38,   -83,   486,   194,   368,
     195,   196,   195,   196,   185,   517,   518,    38,   517,   518,
     409,   139,   344,   166,   100,    74,   103,    42,   263,    72,
      75,   108,   -84,    38,    76,   -83,    77,   406,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,   112,    94,   113,   384,   117,   222,   516,   309,    38,
     427,   272,    99,   274,   275,   479,   107,   488,   253,   310,
      46,   143,   302,   303,   304,   305,   306,   562,   530,   248,
     103,   503,   169,   125,    47,   135,   564,   560,   269,   135,
      48,   126,   546,   539,   548,   549,    38,   149,   155,   157,
     158,   271,    50,    39,   449,   159,    51,   160,   161,   162,
      53,   163,   178,   213,    54,   195,   196,   289,   186,   311,
     577,   307,   140,   242,   101,    56,   186,    40,    40,   144,
     211,   109,   107,   290,   -84,   -84,   118,   -83,   -83,   318,
      40,   273,   291,   348,   164,   257,   547,    60,   369,   566,
     186,    61,   191,   243,   339,   244,    40,    52,   186,   374,
     251,   149,   149,   254,   255,    55,   480,   258,   259,   260,
     261,   262,   264,    42,   135,    65,   268,   375,   135,    63,
     496,   497,    40,   337,   436,   119,    57,   120,   121,    70,
      66,   308,   437,   376,   377,    67,    68,   371,   373,    58,
     165,   378,    62,   127,   128,   129,   130,   131,   190,    59,
     340,   135,   341,   149,   342,    71,   195,   196,   323,    40,
     223,    64,   327,   328,   302,   303,   304,   305,   306,   135,
     296,   300,    73,   301,   245,   482,   246,   320,   349,   350,
     351,   352,   353,   354,   355,   356,    78,   366,   367,   340,
     345,   341,   346,   342,   410,    92,   157,   158,    95,   304,
     305,   306,   159,    38,   160,   161,   162,   443,   163,   186,
     482,   393,   157,   158,   517,   518,   370,   372,   159,    38,
     160,   161,   162,    96,   163,   425,   519,   520,   521,   522,
     523,   396,   397,   472,   473,   474,    98,   400,   450,   103,
     500,   295,   501,   439,   186,   482,   504,   482,   482,   360,
     361,   362,   110,   411,   398,   111,   464,   164,   379,   380,
     381,   382,   383,   574,   575,    42,   465,   401,   357,   358,
     359,   505,    42,   506,   114,   463,    38,   357,   358,   359,
     360,   361,   362,   469,   508,   509,   510,   598,   578,   599,
     579,   493,   494,   528,   490,   491,   122,   165,   123,   124,
     136,   138,   147,   148,   156,   442,   170,   173,   172,   175,
     499,   174,    42,   165,   176,   179,   451,   452,   453,   454,
     455,   456,   457,   458,   459,   460,    40,   177,   188,   189,
     249,   180,   256,    42,    42,   447,   448,   561,   224,   181,
     288,   182,    40,   319,   225,   197,   183,   198,   184,   538,
     192,   193,   321,   199,   200,   201,   135,   466,   241,   247,
     276,   277,   278,   202,   203,   204,   205,   206,   207,   208,
     279,   280,   478,   281,   282,   283,   284,    42,   285,   487,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   286,   287,   316,   326,   535,   196,    40,
     324,   325,   329,   331,   332,   333,   334,   385,   335,   336,
     386,   387,   390,   391,   389,   394,   399,   214,   215,   544,
     402,   404,   407,   159,    38,   160,   161,   162,   412,   163,
     414,   413,   415,   466,   559,   416,   418,   417,   419,   420,
     424,   478,   601,   602,   603,   604,   605,   421,   422,   423,
     426,   428,   429,   557,   432,   310,   433,   434,   440,   445,
     444,   461,   216,   470,   485,   214,   215,   511,   483,   515,
     565,   159,    38,   293,   161,   294,   495,   163,   567,   568,
     569,   570,   571,   513,   525,   588,   589,   526,   489,   492,
     529,   498,   531,   197,   532,   198,   533,   534,   536,   537,
     557,   199,   200,   201,   542,   543,   550,   551,   590,   552,
     295,   202,   203,   204,   205,   206,   207,   208,   165,   553,
     554,   558,   214,   215,   518,   576,   590,   563,   159,    38,
     298,   161,   299,   572,   163,   587,   580,   593,   267,   581,
     594,   197,   582,   198,   583,   217,   595,    40,   584,   199,
     200,   201,   585,   596,   597,   212,   545,   586,   540,   202,
     203,   204,   205,   206,   207,   208,   165,   295,   252,   214,
     215,   541,   431,   430,   606,   159,    38,   160,   161,   162,
       0,   163,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   217,     0,    40,     0,     0,   197,     0,
     198,     0,     0,     0,     0,     0,   199,   200,   201,     0,
       0,     0,     0,     0,   295,     0,   202,   203,   204,   205,
     206,   207,   208,   165,     0,     0,   157,   158,     0,     0,
       0,     0,   159,    38,   160,   161,   162,     0,   163,     0,
       0,     0,     0,     0,     0,   197,     0,   198,     0,     0,
     217,     0,    40,   199,   200,   201,     0,     0,     0,     0,
       0,     0,     0,   202,   203,   204,   205,   206,   207,   208,
     165,   164,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   217,     0,    40,
       0,     0,   197,     0,   198,     0,     0,     0,     0,     0,
     199,   200,   201,     0,     0,     0,     0,     0,     0,     0,
     202,   203,   204,   205,   206,   207,   208,   165,     1,     2,
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
       2,     3,     2,     3,   105,     7,     8,     7,     8,   101,
      12,   211,   142,     0,    12,    12,     0,   448,   140,   287,
       3,     4,     3,     4,    28,     3,     4,    12,     3,     4,
     344,    32,    28,   114,    33,    33,    29,    39,     7,    39,
      42,    33,    29,    12,    46,    29,    48,   341,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    84,    64,    86,    28,    88,   147,   480,    53,    12,
     384,   193,    74,   195,   196,    32,    78,   450,   174,    64,
      43,   104,     5,     6,     7,     8,     9,   530,   488,   170,
      29,   464,   115,    95,    46,    97,   539,   528,   190,   101,
      28,     7,   515,   503,   517,   518,    12,   109,   110,     5,
       6,   192,    52,    56,   408,    11,    56,    13,    14,    15,
      52,    17,   124,   146,    56,     3,     4,    16,   132,   225,
     561,   223,   133,   156,   133,    52,   132,   135,   135,   132,
     142,   133,   144,    32,   131,   132,    62,   131,   132,   241,
     135,   134,    41,   134,    50,   178,   134,    52,   288,   134,
     132,    56,   134,    13,   265,    15,   135,   107,   132,    32,
     172,   173,   174,   175,   176,   107,   133,   179,   180,   181,
     182,   183,   184,   185,   186,    27,   188,    50,   190,    68,
     458,   459,   135,   132,    53,   111,    52,   113,   114,     0,
      42,   224,    61,    30,    31,    47,    48,   288,   289,    52,
     106,   134,   107,   119,   120,   121,   122,   123,   136,    52,
      36,   223,    38,   225,    40,    27,     3,     4,   251,   135,
     148,    52,   255,   256,     5,     6,     7,     8,     9,   241,
     214,   215,    12,   217,    13,   445,    15,   249,   276,   277,
     278,   279,   280,   281,   282,   283,    49,   285,   286,    36,
     132,    38,   134,    40,   345,   131,     5,     6,    57,     7,
       8,     9,    11,    12,    13,    14,    15,   399,    17,   132,
     480,   134,     5,     6,     3,     4,   288,   289,    11,    12,
      13,    14,    15,   130,    17,   376,   119,   120,   121,   122,
     123,   324,   325,    58,    59,    60,   135,   330,   409,    29,
     132,    50,   134,   394,   132,   515,   134,   517,   518,    95,
      96,    97,    57,   346,   326,   108,   427,    50,   302,   303,
     304,   305,   306,   128,   129,   337,   428,   337,    92,    93,
      94,   132,   344,   134,    69,   426,    12,    92,    93,    94,
      95,    96,    97,   434,   472,   473,   474,   132,   562,   134,
     564,   455,   456,   485,   452,   453,   114,   106,    49,   115,
      27,    44,    16,    27,    11,   398,    70,   133,   112,   112,
     461,   133,   384,   106,   115,   115,   414,   415,   416,   417,
     418,   419,   420,   421,   422,   423,   135,   108,    33,     7,
      71,   133,    11,   405,   406,   405,   406,   529,   134,   133,
      16,   133,   135,   134,   132,    81,   133,    83,   133,   500,
     133,   133,    72,    89,    90,    91,   428,   429,   133,   133,
     133,   133,   133,    99,   100,   101,   102,   103,   104,   105,
     133,   133,   444,   133,   133,   133,   133,   449,   133,   449,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,   133,   133,   133,   115,   495,     4,   135,
     134,   134,   117,   134,   134,   134,   134,    54,   134,   134,
      54,   132,    13,    32,   132,    73,   115,     5,     6,   512,
     124,    39,    37,    11,    12,    13,    14,    15,   134,    17,
     132,   134,    98,   505,   527,    98,    98,   132,    98,   132,
      50,   513,   593,   594,   595,   596,   597,    98,    98,    28,
     133,   133,   133,   525,   134,    64,    50,    55,    75,   126,
     125,     4,    50,    21,    57,     5,     6,    63,   127,   133,
     542,    11,    12,    13,    14,    15,   132,    17,   550,   551,
     552,   553,   554,   132,   125,   578,   579,    34,   134,   134,
      57,   134,   134,    81,   134,    83,   134,   134,   134,   134,
     572,    89,    90,    91,    65,    13,   133,   133,   580,   133,
      50,    99,   100,   101,   102,   103,   104,   105,   106,   133,
     133,    13,     5,     6,     4,    35,   598,   134,    11,    12,
      13,    14,    15,   132,    17,    13,   133,    16,   186,   134,
      16,    81,   134,    83,   134,   133,    16,   135,   134,    89,
      90,    91,   134,    16,    16,   144,   513,   572,   504,    99,
     100,   101,   102,   103,   104,   105,   106,    50,   173,     5,
       6,   505,   389,   387,   598,    11,    12,    13,    14,    15,
      -1,    17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   133,    -1,   135,    -1,    -1,    81,    -1,
      83,    -1,    -1,    -1,    -1,    -1,    89,    90,    91,    -1,
      -1,    -1,    -1,    -1,    50,    -1,    99,   100,   101,   102,
     103,   104,   105,   106,    -1,    -1,     5,     6,    -1,    -1,
      -1,    -1,    11,    12,    13,    14,    15,    -1,    17,    -1,
      -1,    -1,    -1,    -1,    -1,    81,    -1,    83,    -1,    -1,
     133,    -1,   135,    89,    90,    91,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    99,   100,   101,   102,   103,   104,   105,
     106,    50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   133,    -1,   135,
      -1,    -1,    81,    -1,    83,    -1,    -1,    -1,    -1,    -1,
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
     110,   114,   116,   137,   138,   139,   140,   143,   144,   145,
     146,   147,   148,   158,   164,   165,   198,   206,    12,    56,
     135,   192,   194,   192,   192,   192,    43,    46,    28,   194,
      52,    56,   107,    52,    56,   107,    52,    52,    52,    52,
      52,    56,   107,    68,    52,    27,    42,    47,    48,   141,
       0,    27,   192,    12,    33,   194,   194,   194,    49,   194,
     194,   194,   194,   194,   194,   194,   194,   194,   194,   194,
     194,   194,   131,   166,   194,    57,   130,   149,   135,   194,
      33,   133,   159,    29,   176,   167,   169,   194,    33,   133,
      57,   108,   166,   166,    69,   199,   200,   166,    62,   111,
     113,   114,   114,    49,   115,   194,     7,   119,   120,   121,
     122,   123,   150,   152,   193,   194,    27,   150,    44,    32,
     133,   187,   191,   166,   132,   168,   176,    16,    27,   194,
     210,   211,   213,   214,   215,   194,    11,     5,     6,    11,
      13,    14,    15,    17,    50,   106,   195,   196,   197,   166,
      70,   201,   112,   133,   133,   112,   115,   108,   194,   115,
     133,   133,   133,   133,   133,    28,   132,   151,    33,     7,
     149,   134,   133,   133,   187,     3,     4,    81,    83,    89,
      90,    91,    99,   100,   101,   102,   103,   104,   105,   171,
     190,   194,   169,   166,     5,     6,    50,   133,   170,   171,
     175,   194,   195,   149,   134,   132,   212,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
     231,   133,   166,    13,    15,    13,    15,   133,   195,    71,
     202,   194,   210,   213,   194,   194,    11,   166,   194,   194,
     194,   194,   194,     7,   194,   153,   192,   152,   194,   150,
     160,   195,   187,   134,   187,   187,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,    16,    16,
      32,    41,   191,    13,    15,    50,   170,   195,    13,    15,
     170,   170,     5,     6,     7,     8,     9,   150,   166,    53,
      64,   213,   219,   220,   222,   229,   133,   216,   150,   134,
     194,    72,   203,   166,   134,   134,   115,   166,   166,   117,
     142,   134,   134,   134,   134,   134,   134,   132,   157,   176,
      36,    38,    40,   154,    28,   132,   134,   161,   134,   175,
     175,   175,   175,   175,   175,   175,   175,    92,    93,    94,
      95,    96,    97,   172,   173,   174,   175,   175,   172,   171,
     194,   195,   194,   195,    32,    50,    30,    31,   134,   170,
     170,   170,   170,   170,    28,    54,    54,   132,   221,   132,
      13,    32,   218,   134,    73,   204,   166,   166,   194,   115,
     166,   192,   124,   177,    39,   156,   156,    37,   155,   153,
     195,   166,   134,   134,   132,    98,    98,   132,    98,    98,
     132,    98,    98,    28,    50,   195,   133,   153,   133,   133,
     222,   220,   134,    50,    55,   217,    53,    61,   208,   195,
      75,   205,   166,   187,   125,   126,   180,   192,   192,   156,
     176,   175,   175,   175,   175,   175,   175,   175,   175,   175,
     175,     4,   162,   195,   176,   150,   194,   223,   225,   195,
      21,   230,    58,    59,    60,   207,   181,   183,   194,    32,
     133,   188,   191,   127,   178,    57,   154,   192,   177,   134,
     174,   174,   134,   173,   173,   132,   172,   172,   134,   195,
     132,   134,   163,   177,   134,   132,   134,   224,   208,   208,
     208,    63,   209,   132,   182,   133,   188,     3,     4,   119,
     120,   121,   122,   123,   189,   125,    34,   179,   187,    57,
     180,   134,   134,   134,   134,   175,   134,   134,   195,   180,
     209,   225,    65,    13,   166,   183,   188,   134,   188,   188,
     133,   133,   133,   133,   133,   184,   186,   194,    13,   166,
     154,   187,   178,   134,   178,   194,   134,   194,   194,   194,
     194,   194,   132,   185,   128,   129,    35,   154,   179,   179,
     133,   134,   134,   134,   134,   134,   186,    13,   166,   166,
     194,   226,   228,    16,    16,    16,    16,    16,   132,   134,
     227,   195,   195,   195,   195,   195,   228
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
#line 143 "dmlyacc.yxx"
    {
            parsedData->setStmtType(DclStatement);
            parsedData->setTableName((yyvsp[(4) - (8)].stringval));
            parsedData->grantDclNode((yyvsp[(6) - (8)].stringval));
    }
    break;

  case 32:

/* Line 1464 of yacc.c  */
#line 157 "dmlyacc.yxx"
    {
            parsedData->setStmtType(CopyTableStatement);
            parsedData->setPKTableName((yyvsp[(3) - (15)].stringval));
            parsedData->setCreateTbl();
            free((yyvsp[(3) - (15)].stringval));
        }
    break;

  case 33:

/* Line 1464 of yacc.c  */
#line 164 "dmlyacc.yxx"
    {
            parsedData->setStmtType(CopyTableStatement);
            parsedData->setPKTableName((yyvsp[(3) - (15)].stringval));
            free((yyvsp[(3) - (15)].stringval));
        }
    break;

  case 34:

/* Line 1464 of yacc.c  */
#line 171 "dmlyacc.yxx"
    {
            parsedData->setStmtType(CompactTableStatement);
            parsedData->setTableName((yyvsp[(3) - (3)].stringval));
            free((yyvsp[(3) - (3)].stringval));
        }
    break;

  case 35:

/* Line 1464 of yacc.c  */
#line 178 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetTables);
	}
    break;

  case 36:

/* Line 1464 of yacc.c  */
#line 183 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetColumns);
        }
    break;

  case 37:

/* Line 1464 of yacc.c  */
#line 188 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetIndexes);
                   
        }
    break;

  case 38:

/* Line 1464 of yacc.c  */
#line 194 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetPriIndex);
        }
    break;

  case 39:

/* Line 1464 of yacc.c  */
#line 199 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetCatalogs);
        }
    break;

  case 40:

/* Line 1464 of yacc.c  */
#line 204 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetTableType);
        }
    break;

  case 41:

/* Line 1464 of yacc.c  */
#line 209 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetDataType);
        }
    break;

  case 42:

/* Line 1464 of yacc.c  */
#line 214 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetImportKey);
        }
    break;

  case 43:

/* Line 1464 of yacc.c  */
#line 219 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetExportKey);
        }
    break;

  case 44:

/* Line 1464 of yacc.c  */
#line 225 "dmlyacc.yxx"
    {
            parsedData->setStmtType(SelectStatement);
            parsedData->setCacheWorthy(true);
        }
    break;

  case 45:

/* Line 1464 of yacc.c  */
#line 231 "dmlyacc.yxx"
    {
           parsedData->setExplain();
	}
    break;

  case 47:

/* Line 1464 of yacc.c  */
#line 237 "dmlyacc.yxx"
    { 
            parsedData->setDistinct();
        }
    break;

  case 53:

/* Line 1464 of yacc.c  */
#line 249 "dmlyacc.yxx"
    {
            parsedData->insertFieldAlias((char*)(yyvsp[(3) - (3)].stringval));
            free((char*)(yyvsp[(3) - (3)].stringval));
        }
    break;

  case 57:

/* Line 1464 of yacc.c  */
#line 259 "dmlyacc.yxx"
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

  case 58:

/* Line 1464 of yacc.c  */
#line 273 "dmlyacc.yxx"
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

  case 59:

/* Line 1464 of yacc.c  */
#line 286 "dmlyacc.yxx"
    {
            parsedData->insertJoinType(INNER_JOIN);
        }
    break;

  case 65:

/* Line 1464 of yacc.c  */
#line 298 "dmlyacc.yxx"
    {
            parsedData->insertJoinType(INNER_JOIN);
        }
    break;

  case 66:

/* Line 1464 of yacc.c  */
#line 304 "dmlyacc.yxx"
    {
            parsedData->setStmtType(InsertStatement);
            parsedData->setTableName((yyvsp[(3) - (9)].stringval)); 
            free((yyvsp[(3) - (9)].stringval));
        }
    break;

  case 70:

/* Line 1464 of yacc.c  */
#line 317 "dmlyacc.yxx"
    {
            parsedData->insertValue((char*)(yyvsp[(1) - (1)].stringval));
            free((yyvsp[(1) - (1)].stringval));
        }
    break;

  case 71:

/* Line 1464 of yacc.c  */
#line 323 "dmlyacc.yxx"
    {
            parsedData->insertValue((char*)(yyvsp[(2) - (2)].stringval));
            free((yyvsp[(2) - (2)].stringval));
        }
    break;

  case 73:

/* Line 1464 of yacc.c  */
#line 331 "dmlyacc.yxx"
    {
            parsedData->insertInValue((char*)(yyvsp[(1) - (1)].stringval));
            free((yyvsp[(1) - (1)].stringval));
        }
    break;

  case 74:

/* Line 1464 of yacc.c  */
#line 337 "dmlyacc.yxx"
    {
            parsedData->insertInValue((char*)(yyvsp[(2) - (2)].stringval));
            free((yyvsp[(2) - (2)].stringval));
        }
    break;

  case 75:

/* Line 1464 of yacc.c  */
#line 344 "dmlyacc.yxx"
    {
            parsedData->setStmtType(DeleteStatement);
            parsedData->setTableName((yyvsp[(3) - (5)].stringval)); 
            free((yyvsp[(3) - (5)].stringval));
	}
    break;

  case 76:

/* Line 1464 of yacc.c  */
#line 352 "dmlyacc.yxx"
    {
            parsedData->setStmtType(UpdateStatement);
            parsedData->setTableName((yyvsp[(2) - (6)].stringval)); 
            free( (yyvsp[(2) - (6)].stringval) );
	}
    break;

  case 82:

/* Line 1464 of yacc.c  */
#line 370 "dmlyacc.yxx"
    {
           parsedData->insertUpdateExpression( (char*) (yyvsp[(1) - (3)].stringval), (Expression* ) (yyvsp[(3) - (3)].Expression));
           free( (yyvsp[(1) - (3)].stringval) ); free((yyvsp[(2) - (3)].stringval));
        }
    break;

  case 83:

/* Line 1464 of yacc.c  */
#line 375 "dmlyacc.yxx"
    { 
            parsedData->insertUpdateValue( (char*) (yyvsp[(1) - (3)].stringval), (char*) (yyvsp[(3) - (3)].stringval));
            free( (yyvsp[(1) - (3)].stringval) ); free((yyvsp[(2) - (3)].stringval));free( (yyvsp[(3) - (3)].stringval) ); 
        }
    break;

  case 84:

/* Line 1464 of yacc.c  */
#line 380 "dmlyacc.yxx"
    {
            parsedData->insertUpdateValue( (char*) (yyvsp[(1) - (3)].stringval), (char*) (yyvsp[(3) - (3)].stringval));
            free( (yyvsp[(1) - (3)].stringval) ); free((yyvsp[(2) - (3)].stringval));free( (yyvsp[(3) - (3)].stringval) );
        }
    break;

  case 85:

/* Line 1464 of yacc.c  */
#line 386 "dmlyacc.yxx"
    {
            Expression* exp;
            exp=parsedData->insertExpression((Expression *)(yyvsp[(1) - (3)].Expression), division, (Expression *)(yyvsp[(3) - (3)].Expression));
            (yyval.Expression)=exp;
        }
    break;

  case 86:

/* Line 1464 of yacc.c  */
#line 392 "dmlyacc.yxx"
    {
            Expression* exp;
            exp=parsedData->insertExpression((Expression *)(yyvsp[(1) - (3)].Expression), modulus, (Expression *)(yyvsp[(3) - (3)].Expression));
            (yyval.Expression)=exp;
        }
    break;

  case 87:

/* Line 1464 of yacc.c  */
#line 398 "dmlyacc.yxx"
    {
            Expression* exp;
            exp=parsedData->insertExpression((Expression *)(yyvsp[(1) - (3)].Expression), multiplication, (Expression *)(yyvsp[(3) - (3)].Expression));
            (yyval.Expression)=exp;
        }
    break;

  case 88:

/* Line 1464 of yacc.c  */
#line 404 "dmlyacc.yxx"
    {
            Expression* exp;
            exp=parsedData->insertExpression((Expression *)(yyvsp[(1) - (3)].Expression), addition, (Expression *)(yyvsp[(3) - (3)].Expression));
            (yyval.Expression)=exp;
        }
    break;

  case 89:

/* Line 1464 of yacc.c  */
#line 410 "dmlyacc.yxx"
    {
            Expression* exp;
            exp=parsedData->insertExpression((Expression *)(yyvsp[(1) - (3)].Expression), subtraction, (Expression *)(yyvsp[(3) - (3)].Expression));
            (yyval.Expression)=exp;
        }
    break;

  case 90:

/* Line 1464 of yacc.c  */
#line 416 "dmlyacc.yxx"
    {
            (yyval.Expression)=(yyvsp[(2) - (3)].Expression);
        }
    break;

  case 91:

/* Line 1464 of yacc.c  */
#line 420 "dmlyacc.yxx"
    {
            (yyval.Expression) = (yyvsp[(2) - (2)].Expression);
        }
    break;

  case 92:

/* Line 1464 of yacc.c  */
#line 424 "dmlyacc.yxx"
    {
            (yyval.Expression) = (yyvsp[(2) - (2)].Expression);
        }
    break;

  case 95:

/* Line 1464 of yacc.c  */
#line 431 "dmlyacc.yxx"
    {
              Expression* exp;
              parsedData->setFunctionType(DATEDIFF);
              exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (6)].Expression), DATEDIFF, (Expression *)(yyvsp[(5) - (6)].Expression));
            (yyval.Expression)=exp;
        }
    break;

  case 96:

/* Line 1464 of yacc.c  */
#line 438 "dmlyacc.yxx"
    {
	         Expression* exp;
             parsedData->setFunctionType((*(FunctionType *)(yyvsp[(6) - (7)].FunctionType)));
             exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (7)].Expression), (*(FunctionType *)(yyvsp[(6) - (7)].FunctionType)), (Expression *)(yyvsp[(5) - (7)].Expression));
             (yyval.Expression)=exp;
	    }
    break;

  case 97:

/* Line 1464 of yacc.c  */
#line 445 "dmlyacc.yxx"
    {
             Expression* exp;
             //parsedData->setFunctionType((*(FunctionType *)$6));
             parsedData->setFunctionType((FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+3));
             exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (7)].Expression), (FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+3), (Expression *)(yyvsp[(5) - (7)].Expression));
             (yyval.Expression)=exp;
        }
    break;

  case 98:

/* Line 1464 of yacc.c  */
#line 453 "dmlyacc.yxx"
    {
              Expression* exp;
              parsedData->setFunctionType(TIMEDIFF);
              exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (6)].Expression), TIMEDIFF, (Expression *)(yyvsp[(5) - (6)].Expression));
            (yyval.Expression)=exp;
        }
    break;

  case 99:

/* Line 1464 of yacc.c  */
#line 460 "dmlyacc.yxx"
    {
             Expression* exp;
             parsedData->setFunctionType((*(FunctionType *)(yyvsp[(6) - (7)].FunctionType)));
             exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (7)].Expression), (*(FunctionType *)(yyvsp[(6) - (7)].FunctionType)), (Expression *)(yyvsp[(5) - (7)].Expression));
             (yyval.Expression)=exp;
        }
    break;

  case 100:

/* Line 1464 of yacc.c  */
#line 467 "dmlyacc.yxx"
    {
             Expression* exp;
             parsedData->setFunctionType((FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+3));
             exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (7)].Expression), (FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+3), (Expression *)(yyvsp[(5) - (7)].Expression));
             (yyval.Expression)=exp;
        }
    break;

  case 101:

/* Line 1464 of yacc.c  */
#line 474 "dmlyacc.yxx"
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

  case 102:

/* Line 1464 of yacc.c  */
#line 485 "dmlyacc.yxx"
    {
             Expression* exp;
             parsedData->setFunctionType((FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+12));
             exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (7)].Expression), (FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+12), (Expression *)(yyvsp[(5) - (7)].Expression));
             (yyval.Expression)=exp;
        }
    break;

  case 103:

/* Line 1464 of yacc.c  */
#line 492 "dmlyacc.yxx"
    {
             Expression* exp;
             parsedData->setFunctionType((FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+15));
             exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (7)].Expression), (FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+15), (Expression *)(yyvsp[(5) - (7)].Expression));
             (yyval.Expression)=exp;
        }
    break;

  case 104:

/* Line 1464 of yacc.c  */
#line 499 "dmlyacc.yxx"
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

  case 105:

/* Line 1464 of yacc.c  */
#line 511 "dmlyacc.yxx"
    {
            Expression* exp;
            parsedData->setFunctionType(DATEFROMTIMESTAMP);
            exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (4)].Expression), DATEFROMTIMESTAMP, NULL);
            (yyval.Expression)=exp;

        }
    break;

  case 106:

/* Line 1464 of yacc.c  */
#line 519 "dmlyacc.yxx"
    {
            Expression* exp;
            parsedData->setFunctionType(TIMEFROMTIMESTAMP);
            exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (4)].Expression), TIMEFROMTIMESTAMP, NULL);
            (yyval.Expression)=exp;
        }
    break;

  case 107:

/* Line 1464 of yacc.c  */
#line 527 "dmlyacc.yxx"
    {
           FunctionType val = *(FunctionType *)(yyvsp[(1) - (1)].FunctionType);
           (yyval.FunctionType) = &val;
        }
    break;

  case 108:

/* Line 1464 of yacc.c  */
#line 532 "dmlyacc.yxx"
    {
           FunctionType val = *(FunctionType *)(yyvsp[(1) - (1)].FunctionType);
           (yyval.FunctionType) = &val;
        }
    break;

  case 109:

/* Line 1464 of yacc.c  */
#line 538 "dmlyacc.yxx"
    { 
             FunctionType val = TIMEADDWITHHOUR;
             (yyval.FunctionType) = &val;
        }
    break;

  case 110:

/* Line 1464 of yacc.c  */
#line 543 "dmlyacc.yxx"
    {
             FunctionType val = TIMEADDWITHMIN;
             (yyval.FunctionType) = &val;
        }
    break;

  case 111:

/* Line 1464 of yacc.c  */
#line 548 "dmlyacc.yxx"
    {
             FunctionType val = TIMEADDWITHSEC;
             (yyval.FunctionType) = &val;
        }
    break;

  case 112:

/* Line 1464 of yacc.c  */
#line 554 "dmlyacc.yxx"
    {
	        FunctionType val = DATEADDWITHYEAR;
            (yyval.FunctionType) = &val;
	    }
    break;

  case 113:

/* Line 1464 of yacc.c  */
#line 559 "dmlyacc.yxx"
    {
	        FunctionType val = DATEADDWITHMON;
            (yyval.FunctionType) = &val;
        }
    break;

  case 114:

/* Line 1464 of yacc.c  */
#line 564 "dmlyacc.yxx"
    {
            FunctionType val = DATEADDWITHDAY;
            (yyval.FunctionType) = &val;
        }
    break;

  case 115:

/* Line 1464 of yacc.c  */
#line 570 "dmlyacc.yxx"
    {
            Expression* exp;
            exp=parsedData->insertExpression((char *)(yyvsp[(1) - (1)].stringval));
            free((yyvsp[(1) - (1)].stringval));
            (yyval.Expression)=exp;
        }
    break;

  case 116:

/* Line 1464 of yacc.c  */
#line 577 "dmlyacc.yxx"
    {
            Expression* exp;
            bool flag = false;
            exp=parsedData->insertExpression((char *)(yyvsp[(1) - (1)].stringval), flag);
            free((yyvsp[(1) - (1)].stringval));
            (yyval.Expression)=exp;
        }
    break;

  case 117:

/* Line 1464 of yacc.c  */
#line 585 "dmlyacc.yxx"
    {
            Expression* exp;
            exp=parsedData->insertExpression("NULL");
            free((yyvsp[(1) - (1)].stringval));
            (yyval.Expression)=exp;
        }
    break;

  case 118:

/* Line 1464 of yacc.c  */
#line 594 "dmlyacc.yxx"
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

  case 124:

/* Line 1464 of yacc.c  */
#line 615 "dmlyacc.yxx"
    {
            parsedData->setLimit(atoi((yyvsp[(2) - (2)].stringval)), 0);
        }
    break;

  case 125:

/* Line 1464 of yacc.c  */
#line 619 "dmlyacc.yxx"
    {
            parsedData->setLimit(atoi((yyvsp[(2) - (4)].stringval)), atoi((yyvsp[(4) - (4)].stringval)));
        }
    break;

  case 132:

/* Line 1464 of yacc.c  */
#line 633 "dmlyacc.yxx"
    {
            parsedData->insertGroupField((char*)(yyvsp[(1) - (1)].stringval));
            free( (yyvsp[(1) - (1)].stringval) );
        }
    break;

  case 136:

/* Line 1464 of yacc.c  */
#line 644 "dmlyacc.yxx"
    {
            parsedData->insertOrderByField((char*)(yyvsp[(1) - (1)].stringval));
            free( (yyvsp[(1) - (1)].stringval) );
        }
    break;

  case 137:

/* Line 1464 of yacc.c  */
#line 649 "dmlyacc.yxx"
    {
            parsedData->insertOrderByField((char*)(yyvsp[(1) - (2)].stringval));
            free( (yyvsp[(1) - (2)].stringval) );
        }
    break;

  case 138:

/* Line 1464 of yacc.c  */
#line 654 "dmlyacc.yxx"
    {
            parsedData->insertOrderByField((char*)(yyvsp[(1) - (2)].stringval), true);
            free( (yyvsp[(1) - (2)].stringval) );
        }
    break;

  case 139:

/* Line 1464 of yacc.c  */
#line 660 "dmlyacc.yxx"
    {
            Predicate *pred;
            pred = parsedData->insertPredicate((Predicate*) (yyvsp[(1) - (3)].predicate), OpOr, (Predicate*) (yyvsp[(3) - (3)].predicate));
            //parsedData->setCondition((Predicate*)pred);
            (yyval.predicate)= pred;

        }
    break;

  case 140:

/* Line 1464 of yacc.c  */
#line 668 "dmlyacc.yxx"
    {
            Predicate *pred;
            pred = parsedData->insertPredicate((Predicate*) (yyvsp[(1) - (3)].predicate), OpAnd, (Predicate*) (yyvsp[(3) - (3)].predicate));
            //parsedData->setCondition((Predicate*)pred);
            (yyval.predicate)= pred;
        }
    break;

  case 141:

/* Line 1464 of yacc.c  */
#line 674 "dmlyacc.yxx"
    { (yyval.predicate)=(yyvsp[(2) - (3)].predicate); }
    break;

  case 142:

/* Line 1464 of yacc.c  */
#line 676 "dmlyacc.yxx"
    {
            Predicate *pred;
            pred = parsedData->insertPredicate((Predicate*) (yyvsp[(3) - (4)].predicate), OpNot, NULL);
            //parsedData->setCondition((Predicate*)pred);
            (yyval.predicate)= pred;

        }
    break;

  case 143:

/* Line 1464 of yacc.c  */
#line 684 "dmlyacc.yxx"
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

  case 144:

/* Line 1464 of yacc.c  */
#line 700 "dmlyacc.yxx"
    {
            Predicate *pred;
            pred = parsedData->insertPredicate((Predicate*) (yyvsp[(1) - (3)].predicate), OpOr, (Predicate*) (yyvsp[(3) - (3)].predicate));
            parsedData->setHavingCondition((Predicate*)pred);
            (yyval.predicate)= pred;

        }
    break;

  case 145:

/* Line 1464 of yacc.c  */
#line 708 "dmlyacc.yxx"
    {
            Predicate *pred;
            pred = parsedData->insertPredicate((Predicate*) (yyvsp[(1) - (3)].predicate), OpAnd, (Predicate*) (yyvsp[(3) - (3)].predicate));
            parsedData->setHavingCondition((Predicate*)pred);
            (yyval.predicate)= pred;
        }
    break;

  case 146:

/* Line 1464 of yacc.c  */
#line 714 "dmlyacc.yxx"
    { (yyval.predicate)=(yyvsp[(2) - (3)].predicate); }
    break;

  case 147:

/* Line 1464 of yacc.c  */
#line 716 "dmlyacc.yxx"
    {
            Predicate *pred;
            pred = parsedData->insertPredicate((Predicate*) (yyvsp[(3) - (4)].predicate), OpNot, NULL);
            parsedData->setHavingCondition((Predicate*)pred);
            (yyval.predicate)= pred;

        }
    break;

  case 148:

/* Line 1464 of yacc.c  */
#line 724 "dmlyacc.yxx"
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

  case 149:

/* Line 1464 of yacc.c  */
#line 740 "dmlyacc.yxx"
    {
            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(5) - (6)].stringval));
            Predicate *pred;
            void **ptr = parsedData->insertCondValueAndGetPtr((char*)(yyvsp[(3) - (6)].stringval), (char*)(yyvsp[(6) - (6)].stringval), false, AGG_MIN, true);
            pred = parsedData->insertPredicate((char*) (yyvsp[(3) - (6)].stringval), op, ptr, AGG_MIN);
            free( (yyvsp[(1) - (6)].stringval) ); free ((yyvsp[(3) - (6)].stringval)); free ((yyvsp[(5) - (6)].stringval)); free ((yyvsp[(6) - (6)].stringval));
            (yyval.predicate)=pred;
        }
    break;

  case 150:

/* Line 1464 of yacc.c  */
#line 749 "dmlyacc.yxx"
    {
            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(5) - (6)].stringval));
            Predicate *pred;
            void **ptr = parsedData->insertCondValueAndGetPtr((char*)(yyvsp[(3) - (6)].stringval), (char*)(yyvsp[(6) - (6)].stringval), false, AGG_MAX, true);
            pred = parsedData->insertPredicate((char*) (yyvsp[(3) - (6)].stringval), op, ptr, AGG_MAX);
            free( (yyvsp[(1) - (6)].stringval) ); free ((yyvsp[(3) - (6)].stringval)); free ((yyvsp[(5) - (6)].stringval)); free ((yyvsp[(6) - (6)].stringval));
            (yyval.predicate)=pred;
        }
    break;

  case 151:

/* Line 1464 of yacc.c  */
#line 758 "dmlyacc.yxx"
    {
            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(5) - (6)].stringval));
            Predicate *pred;
            void **ptr = parsedData->insertCondValueAndGetPtr((char*)(yyvsp[(3) - (6)].stringval), (char*)(yyvsp[(6) - (6)].stringval), false, AGG_SUM, true);
            pred = parsedData->insertPredicate((char*) (yyvsp[(3) - (6)].stringval), op, ptr, AGG_SUM);
            free( (yyvsp[(1) - (6)].stringval) ); free ((yyvsp[(3) - (6)].stringval)); free ((yyvsp[(5) - (6)].stringval)); free ((yyvsp[(6) - (6)].stringval));
            (yyval.predicate)=pred;
        }
    break;

  case 152:

/* Line 1464 of yacc.c  */
#line 767 "dmlyacc.yxx"
    {
            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(5) - (6)].stringval));
            Predicate *pred;
            void **ptr = parsedData->insertCondValueAndGetPtr((char*)(yyvsp[(3) - (6)].stringval), (char*)(yyvsp[(6) - (6)].stringval), false, AGG_AVG, true);
            pred = parsedData->insertPredicate((char*) (yyvsp[(3) - (6)].stringval), op, ptr, AGG_AVG);
            free( (yyvsp[(1) - (6)].stringval) ); free ((yyvsp[(3) - (6)].stringval)); free ((yyvsp[(5) - (6)].stringval)); free ((yyvsp[(6) - (6)].stringval));
            (yyval.predicate)=pred;
        }
    break;

  case 153:

/* Line 1464 of yacc.c  */
#line 776 "dmlyacc.yxx"
    {
            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(5) - (6)].stringval));
            Predicate *pred;
            void **ptr = parsedData->insertCondValueAndGetPtr((char*)(yyvsp[(3) - (6)].stringval), (char*)(yyvsp[(6) - (6)].stringval), false, AGG_COUNT, true);
            pred = parsedData->insertPredicate((char*) (yyvsp[(3) - (6)].stringval), op, ptr, AGG_COUNT);
            free( (yyvsp[(1) - (6)].stringval) ); free ((yyvsp[(3) - (6)].stringval)); free ((yyvsp[(5) - (6)].stringval)); free ((yyvsp[(6) - (6)].stringval));
            (yyval.predicate)=pred;
        }
    break;

  case 154:

/* Line 1464 of yacc.c  */
#line 787 "dmlyacc.yxx"
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

  case 155:

/* Line 1464 of yacc.c  */
#line 798 "dmlyacc.yxx"
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

  case 156:

/* Line 1464 of yacc.c  */
#line 809 "dmlyacc.yxx"
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

  case 157:

/* Line 1464 of yacc.c  */
#line 825 "dmlyacc.yxx"
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

  case 158:

/* Line 1464 of yacc.c  */
#line 851 "dmlyacc.yxx"
    {
            Predicate *pred;
            parsedData->insertCondValue((char*) (yyvsp[(1) - (4)].stringval));
            pred = parsedData->insertNullPredicate((char*) (yyvsp[(1) - (4)].stringval), OpIsNull, false);
            free( (yyvsp[(1) - (4)].stringval) ); free((yyvsp[(2) - (4)].stringval)); free( (yyvsp[(3) - (4)].stringval) );
            (yyval.predicate)=pred;  
        }
    break;

  case 159:

/* Line 1464 of yacc.c  */
#line 859 "dmlyacc.yxx"
    {
            Predicate *pred;
            parsedData->insertCondValue((char*) (yyvsp[(1) - (3)].stringval));
            pred = parsedData->insertNullPredicate((char*) (yyvsp[(1) - (3)].stringval), OpIsNull, true);
            free( (yyvsp[(1) - (3)].stringval) ); free((yyvsp[(2) - (3)].stringval)); free( (yyvsp[(3) - (3)].stringval) );
            (yyval.predicate)=pred;  
        }
    break;

  case 160:

/* Line 1464 of yacc.c  */
#line 867 "dmlyacc.yxx"
    {
            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(2) - (3)].stringval));
            Predicate *pred;
            pred = parsedData->insertPredicate(((Expression*)(yyvsp[(1) - (3)].Expression)), op, ((Expression*)(yyvsp[(3) - (3)].Expression)));
            (yyval.predicate)=pred;
 
        }
    break;

  case 161:

/* Line 1464 of yacc.c  */
#line 875 "dmlyacc.yxx"
    {

            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(2) - (3)].stringval));
            parsedData->insertCondValue((char*) (yyvsp[(3) - (3)].stringval));
            Predicate *pred;
            pred = parsedData->insertPredicate(((Expression*)(yyvsp[(1) - (3)].Expression)), op, (char*) (yyvsp[(3) - (3)].stringval));
            (yyval.predicate)=pred;
            
        }
    break;

  case 162:

/* Line 1464 of yacc.c  */
#line 885 "dmlyacc.yxx"
    {
            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(2) - (3)].stringval));
            void **ptr = parsedData->insertCondValueAndGetPtr((char*)"dummy", (char*)(yyvsp[(3) - (3)].stringval), false, AGG_UNKNOWN, false, true);
            Predicate *pred;
            pred = parsedData->insertPredicate(((Expression*)(yyvsp[(1) - (3)].Expression)), op, ptr);
            (yyval.predicate)=pred;
        }
    break;

  case 163:

/* Line 1464 of yacc.c  */
#line 894 "dmlyacc.yxx"
    { (yyval.stringval)=(char*) 1;
	}
    break;

  case 164:

/* Line 1464 of yacc.c  */
#line 897 "dmlyacc.yxx"
    { (yyval.stringval)=(char*) 0; }
    break;

  case 165:

/* Line 1464 of yacc.c  */
#line 900 "dmlyacc.yxx"
    {
            parsedData->insertTableName((char*)(yyvsp[(1) - (1)].stringval));
            free( (yyvsp[(1) - (1)].stringval) );
        }
    break;

  case 166:

/* Line 1464 of yacc.c  */
#line 905 "dmlyacc.yxx"
    {
            parsedData->insertTableName((char*)(yyvsp[(1) - (3)].stringval), (char*)(yyvsp[(3) - (3)].stringval));
            free( (yyvsp[(1) - (3)].stringval) ); free((yyvsp[(3) - (3)].stringval));
        }
    break;

  case 167:

/* Line 1464 of yacc.c  */
#line 910 "dmlyacc.yxx"
    {
            parsedData->insertTableName((char*)(yyvsp[(1) - (2)].stringval), (char*)(yyvsp[(2) - (2)].stringval));
            free( (yyvsp[(1) - (2)].stringval) ); free((yyvsp[(2) - (2)].stringval));
        }
    break;

  case 168:

/* Line 1464 of yacc.c  */
#line 916 "dmlyacc.yxx"
    {
            parsedData->insertField((char*)(yyvsp[(1) - (1)].stringval));
            free( (yyvsp[(1) - (1)].stringval) );
            
        }
    break;

  case 169:

/* Line 1464 of yacc.c  */
#line 922 "dmlyacc.yxx"
    { 
            parsedData->insertField((char*)(yyvsp[(3) - (4)].stringval), AGG_MIN);
            free( (yyvsp[(1) - (4)].stringval) );
        }
    break;

  case 170:

/* Line 1464 of yacc.c  */
#line 927 "dmlyacc.yxx"
    { 
            parsedData->insertField((char*)(yyvsp[(3) - (4)].stringval), AGG_MAX);
            free( (yyvsp[(1) - (4)].stringval) );
        }
    break;

  case 171:

/* Line 1464 of yacc.c  */
#line 932 "dmlyacc.yxx"
    { 
            parsedData->insertField((char*)(yyvsp[(3) - (4)].stringval), AGG_SUM);
            free( (yyvsp[(1) - (4)].stringval) );
        }
    break;

  case 172:

/* Line 1464 of yacc.c  */
#line 937 "dmlyacc.yxx"
    { 
            parsedData->insertField((char*)(yyvsp[(3) - (4)].stringval), AGG_AVG);
            free( (yyvsp[(1) - (4)].stringval) );
        }
    break;

  case 173:

/* Line 1464 of yacc.c  */
#line 942 "dmlyacc.yxx"
    { 
            parsedData->insertField((char*)(yyvsp[(3) - (4)].stringval), AGG_COUNT);
            free( (yyvsp[(1) - (4)].stringval) );
        }
    break;

  case 174:

/* Line 1464 of yacc.c  */
#line 947 "dmlyacc.yxx"
    { 
            parsedData->insertField("*", AGG_COUNT);
            free( (yyvsp[(1) - (4)].stringval) );
        }
    break;

  case 175:

/* Line 1464 of yacc.c  */
#line 952 "dmlyacc.yxx"
    { 
            parsedData->insertField("*");
        }
    break;

  case 176:

/* Line 1464 of yacc.c  */
#line 956 "dmlyacc.yxx"
    {
            parsedData->insertField("*");
        }
    break;

  case 177:

/* Line 1464 of yacc.c  */
#line 960 "dmlyacc.yxx"
    { (yyval.stringval) = (yyvsp[(1) - (1)].stringval); }
    break;

  case 178:

/* Line 1464 of yacc.c  */
#line 961 "dmlyacc.yxx"
    { (yyval.stringval) = (yyvsp[(2) - (3)].stringval); }
    break;

  case 179:

/* Line 1464 of yacc.c  */
#line 963 "dmlyacc.yxx"
    { (yyval.stringval) = (yyvsp[(1) - (1)].stringval); }
    break;

  case 181:

/* Line 1464 of yacc.c  */
#line 965 "dmlyacc.yxx"
    { (yyval.stringval) = (yyvsp[(1) - (1)].stringval); }
    break;

  case 183:

/* Line 1464 of yacc.c  */
#line 967 "dmlyacc.yxx"
    { (yyval.stringval) = (yyvsp[(1) - (1)].stringval); }
    break;

  case 184:

/* Line 1464 of yacc.c  */
#line 968 "dmlyacc.yxx"
    { (yyval.stringval) = (char*) 0; }
    break;

  case 185:

/* Line 1464 of yacc.c  */
#line 970 "dmlyacc.yxx"
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

  case 186:

/* Line 1464 of yacc.c  */
#line 982 "dmlyacc.yxx"
    { (yyval.stringval) =  (yyvsp[(1) - (1)].stringval); }
    break;

  case 187:

/* Line 1464 of yacc.c  */
#line 984 "dmlyacc.yxx"
    {
             char *n;
             n=(char*)malloc(30);
             strcpy(n,"-");
             strcat(n,(char*)(yyvsp[(2) - (2)].stringval));
             (yyval.stringval)=n;
             free((yyvsp[(2) - (2)].stringval));
        }
    break;

  case 188:

/* Line 1464 of yacc.c  */
#line 992 "dmlyacc.yxx"
    { (yyval.stringval) =  (yyvsp[(2) - (2)].stringval); }
    break;

  case 189:

/* Line 1464 of yacc.c  */
#line 994 "dmlyacc.yxx"
    { (yyval.stringval) = (yyvsp[(1) - (1)].stringval); }
    break;

  case 190:

/* Line 1464 of yacc.c  */
#line 996 "dmlyacc.yxx"
    {
             char *d;
             d=(char*)malloc(30);
             strcpy(d,"-");
             strcat(d,(char*)(yyvsp[(2) - (2)].stringval));
             (yyval.stringval)=d;
             free((yyvsp[(2) - (2)].stringval));
        }
    break;

  case 191:

/* Line 1464 of yacc.c  */
#line 1004 "dmlyacc.yxx"
    { (yyval.stringval) = (yyvsp[(2) - (2)].stringval); }
    break;

  case 192:

/* Line 1464 of yacc.c  */
#line 1007 "dmlyacc.yxx"
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

  case 193:

/* Line 1464 of yacc.c  */
#line 1018 "dmlyacc.yxx"
    {
            parsedData->setStmtType(CacheTableStatement);
            parsedData->setUnCache(true);
            parsedData->setTableName((yyvsp[(3) - (4)].stringval)); 
        }
    break;

  case 196:

/* Line 1464 of yacc.c  */
#line 1028 "dmlyacc.yxx"
    {
            parsedData->setHCondFld(true);
            parsedData->setHCondition((char*)(yyvsp[(2) - (2)].stringval));
         }
    break;

  case 198:

/* Line 1464 of yacc.c  */
#line 1035 "dmlyacc.yxx"
    {
            parsedData->setVCondFld(true);
            parsedData->setVCondition((char*)(yyvsp[(2) - (2)].stringval));
            free((yyvsp[(2) - (2)].stringval));
         }
    break;

  case 200:

/* Line 1464 of yacc.c  */
#line 1043 "dmlyacc.yxx"
    {
            parsedData->setPkFld(true);
            parsedData->setIndexName((char*)(yyvsp[(2) - (2)].stringval));
            free((yyvsp[(2) - (2)].stringval));
         }
    break;

  case 202:

/* Line 1464 of yacc.c  */
#line 1051 "dmlyacc.yxx"
    {
            parsedData->setDirect(true);
         }
    break;

  case 204:

/* Line 1464 of yacc.c  */
#line 1057 "dmlyacc.yxx"
    {
             parsedData->setDSN(true);
             parsedData->setPKTableName((char*)(yyvsp[(2) - (2)].stringval));
             free((yyvsp[(2) - (2)].stringval));
         }
    break;

  case 206:

/* Line 1464 of yacc.c  */
#line 1064 "dmlyacc.yxx"
    {
             parsedData->setNoSchema(true);
         }
    break;

  case 207:

/* Line 1464 of yacc.c  */
#line 1069 "dmlyacc.yxx"
    {
            parsedData->setStmtType(CreateTableStatement);
            parsedData->setTableName((yyvsp[(3) - (7)].stringval)); 
            free((yyvsp[(3) - (7)].stringval));
        }
    break;

  case 208:

/* Line 1464 of yacc.c  */
#line 1075 "dmlyacc.yxx"
    {
            parsedData->setStmtType(CreateIndexStatement);
            parsedData->setIndexName((yyvsp[(3) - (12)].stringval)); 
            parsedData->setTableName((yyvsp[(5) - (12)].stringval)); 
            free((yyvsp[(3) - (12)].stringval));
            free((yyvsp[(5) - (12)].stringval));
        }
    break;

  case 209:

/* Line 1464 of yacc.c  */
#line 1083 "dmlyacc.yxx"
    {
            parsedData->setStmtType(DropTableStatement);
            parsedData->setTableName((yyvsp[(3) - (3)].stringval)); 
            free((yyvsp[(3) - (3)].stringval));
        }
    break;

  case 210:

/* Line 1464 of yacc.c  */
#line 1089 "dmlyacc.yxx"
    {
            parsedData->setStmtType(DropIndexStatement);
            parsedData->setIndexName((yyvsp[(3) - (3)].stringval)); 
            free((yyvsp[(3) - (3)].stringval));
        }
    break;

  case 211:

/* Line 1464 of yacc.c  */
#line 1095 "dmlyacc.yxx"
    {
            parsedData->setStmtType(TruncateStatement);
            parsedData->setTableName((yyvsp[(3) - (4)].stringval)); 
            free((yyvsp[(3) - (4)].stringval));
        }
    break;

  case 213:

/* Line 1464 of yacc.c  */
#line 1103 "dmlyacc.yxx"
    {
            parsedData->setIndexType(hashIndex);
        }
    break;

  case 214:

/* Line 1464 of yacc.c  */
#line 1107 "dmlyacc.yxx"
    {
            parsedData->setIndexType(treeIndex);
        }
    break;

  case 215:

/* Line 1464 of yacc.c  */
#line 1111 "dmlyacc.yxx"
    {
            parsedData->setIndexType(trieIndex);
        }
    break;

  case 216:

/* Line 1464 of yacc.c  */
#line 1115 "dmlyacc.yxx"
    {
            parsedData->setIndexType(hashIndex);
        }
    break;

  case 218:

/* Line 1464 of yacc.c  */
#line 1121 "dmlyacc.yxx"
    {
            parsedData->setUnique(true);
        }
    break;

  case 219:

/* Line 1464 of yacc.c  */
#line 1125 "dmlyacc.yxx"
    {
            parsedData->setUnique(true);
            parsedData->setPrimary(true);
        }
    break;

  case 220:

/* Line 1464 of yacc.c  */
#line 1130 "dmlyacc.yxx"
    {
            parsedData->setUnique(false);
            parsedData->setPrimary(false);
        }
    break;

  case 222:

/* Line 1464 of yacc.c  */
#line 1137 "dmlyacc.yxx"
    {
            parsedData->setBucketSize(atoi((yyvsp[(2) - (2)].stringval)));
            free((yyvsp[(2) - (2)].stringval));
        }
    break;

  case 228:

/* Line 1464 of yacc.c  */
#line 1153 "dmlyacc.yxx"
    {
            parsedData->insertFldDef();
        }
    break;

  case 230:

/* Line 1464 of yacc.c  */
#line 1162 "dmlyacc.yxx"
    {
            parsedData->setFldName((yyvsp[(1) - (1)].stringval));
            free((yyvsp[(1) - (1)].stringval));
        }
    break;

  case 232:

/* Line 1464 of yacc.c  */
#line 1168 "dmlyacc.yxx"
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

  case 234:

/* Line 1464 of yacc.c  */
#line 1181 "dmlyacc.yxx"
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

  case 236:

/* Line 1464 of yacc.c  */
#line 1194 "dmlyacc.yxx"
    {
            parsedData->setFldNotNull(true);
        }
    break;

  case 243:

/* Line 1464 of yacc.c  */
#line 1208 "dmlyacc.yxx"
    {
            parsedData->setForeign(true);
            parsedData->setPKTableName((char*)(yyvsp[(7) - (10)].stringval));
            parsedData->insertForeignKeyList();
        }
    break;

  case 247:

/* Line 1464 of yacc.c  */
#line 1220 "dmlyacc.yxx"
    {
           parsedData->insertFKField((char*)(yyvsp[(1) - (1)].stringval));
           free((yyvsp[(1) - (1)].stringval));
        }
    break;

  case 251:

/* Line 1464 of yacc.c  */
#line 1231 "dmlyacc.yxx"
    {
           parsedData->insertPKField((char*)(yyvsp[(1) - (1)].stringval));
           free((yyvsp[(1) - (1)].stringval));
        }
    break;

  case 252:

/* Line 1464 of yacc.c  */
#line 1238 "dmlyacc.yxx"
    {
           parsedData->setPrimary(true);
        }
    break;

  case 254:

/* Line 1464 of yacc.c  */
#line 1244 "dmlyacc.yxx"
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

  case 255:

/* Line 1464 of yacc.c  */
#line 1265 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeInt);
        }
    break;

  case 256:

/* Line 1464 of yacc.c  */
#line 1269 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeLong);
        }
    break;

  case 257:

/* Line 1464 of yacc.c  */
#line 1273 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeShort);
        }
    break;

  case 258:

/* Line 1464 of yacc.c  */
#line 1277 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeLongLong);
        }
    break;

  case 259:

/* Line 1464 of yacc.c  */
#line 1281 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeByteInt);
        }
    break;

  case 260:

/* Line 1464 of yacc.c  */
#line 1285 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeFloat);
        }
    break;

  case 261:

/* Line 1464 of yacc.c  */
#line 1289 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeDouble);
        }
    break;

  case 262:

/* Line 1464 of yacc.c  */
#line 1294 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeDate);
        }
    break;

  case 263:

/* Line 1464 of yacc.c  */
#line 1299 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeTime);
        }
    break;

  case 264:

/* Line 1464 of yacc.c  */
#line 1304 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeTimeStamp);
        }
    break;

  case 265:

/* Line 1464 of yacc.c  */
#line 1309 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeString);
            parsedData->setFldLength(2);
        }
    break;

  case 266:

/* Line 1464 of yacc.c  */
#line 1315 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeVarchar);
            parsedData->setFldLength(2);
        }
    break;

  case 267:

/* Line 1464 of yacc.c  */
#line 1321 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeBinary);
            parsedData->setFldLength(1);
        }
    break;



/* Line 1464 of yacc.c  */
#line 4255 "dmlyacc.cxx"
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
#line 1326 "dmlyacc.yxx"


extern int lexEof;
void yyerror(const char* Msg) { 
    if( lexEof == 0 )
        fprintf(stderr, "[Parser: %s] %s\n", Msg, yytext);

    return;
}

