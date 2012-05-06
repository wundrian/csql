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
     REVOKE = 367,
     ALL = 368,
     PRIVILEGES = 369,
     MIN = 370,
     MAX = 371,
     AVG = 372,
     SUM = 373,
     COUNT = 374,
     GROUP = 375,
     BY = 376,
     HAVING = 377,
     ORDER = 378,
     ASC = 379,
     DESC = 380,
     DISTINCT = 381
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
#define REVOKE 367
#define ALL 368
#define PRIVILEGES 369
#define MIN 370
#define MAX 371
#define AVG 372
#define SUM 373
#define COUNT 374
#define GROUP 375
#define BY 376
#define HAVING 377
#define ORDER 378
#define ASC 379
#define DESC 380
#define DISTINCT 381




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
#line 382 "dmlyacc.cxx"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 394 "dmlyacc.cxx"

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
#define YYFINAL  75
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   780

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  137
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  101
/* YYNRULES -- Number of rules.  */
#define YYNRULES  273
/* YYNRULES -- Number of states.  */
#define YYNSTATES  623

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   381

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     9,     2,     2,
     134,   135,     7,     5,   133,     6,     2,     8,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,   132,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,   136,     2,     2,     2,
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
     130,   131
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    11,    13,    15,    17,
      19,    21,    23,    25,    27,    29,    31,    40,    48,    57,
      64,    74,    82,    86,    93,    98,   106,   109,   111,   114,
     116,   118,   120,   122,   125,   128,   130,   133,   135,   144,
     152,   168,   184,   188,   190,   193,   197,   200,   202,   204,
     206,   209,   212,   225,   228,   229,   231,   232,   235,   237,
     240,   242,   246,   249,   251,   254,   261,   269,   274,   275,
     276,   278,   279,   281,   284,   294,   295,   299,   302,   304,
     307,   310,   312,   315,   321,   328,   330,   331,   334,   336,
     339,   343,   347,   351,   355,   359,   363,   367,   371,   375,
     378,   381,   383,   385,   392,   400,   408,   415,   423,   431,
     440,   448,   456,   463,   468,   473,   475,   477,   479,   481,
     483,   485,   487,   489,   491,   493,   495,   498,   499,   503,
     504,   508,   509,   512,   517,   518,   521,   522,   525,   527,
     530,   532,   535,   537,   540,   542,   545,   548,   552,   556,
     560,   565,   568,   572,   576,   580,   585,   588,   595,   602,
     609,   616,   623,   627,   631,   638,   645,   650,   654,   658,
     662,   666,   668,   669,   671,   675,   678,   680,   685,   690,
     695,   700,   705,   710,   712,   715,   717,   721,   723,   725,
     727,   729,   731,   733,   737,   739,   742,   745,   747,   750,
     753,   759,   764,   771,   772,   775,   776,   779,   780,   783,
     784,   786,   787,   790,   791,   793,   801,   814,   818,   822,
     827,   830,   833,   836,   837,   839,   841,   842,   843,   846,
     848,   852,   855,   857,   860,   862,   869,   871,   872,   876,
     877,   880,   881,   884,   886,   888,   892,   895,   897,   900,
     911,   914,   916,   919,   921,   924,   926,   929,   931,   938,
     939,   941,   943,   945,   947,   949,   951,   953,   955,   957,
     959,   961,   963,   965
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     138,     0,    -1,   153,    -1,   164,    -1,   170,    -1,   171,
      -1,   212,    -1,   151,    -1,   204,    -1,   150,    -1,   141,
      -1,   148,    -1,   149,    -1,   140,    -1,   139,    -1,   152,
      -1,   109,    52,   200,   111,   134,   216,   135,   172,    -1,
     109,    52,   200,    62,   112,   200,   172,    -1,   109,    52,
     200,   113,   134,   219,   135,   172,    -1,   114,    52,   200,
     115,   200,   172,    -1,   109,    52,   200,   114,   112,   200,
     115,   200,   172,    -1,   109,    56,   200,   114,   115,   200,
     172,    -1,   110,    68,   172,    -1,    51,   107,   200,   108,
      11,   172,    -1,    62,   107,   200,   172,    -1,   109,   107,
     200,    49,   108,    11,   172,    -1,   142,   143,    -1,   144,
      -1,   133,   144,    -1,    27,    -1,    42,    -1,    48,    -1,
      47,    -1,   118,   119,    -1,   145,   146,    -1,   147,    -1,
     133,   147,    -1,   200,    -1,   116,   142,    57,   200,   115,
     145,   182,   172,    -1,   117,   142,    57,   200,    28,   145,
     172,    -1,    51,    52,   200,    33,    27,   155,   156,    28,
     159,   182,   183,   186,   184,   185,   172,    -1,    42,    43,
     200,    33,    27,   155,   156,    28,   159,   182,   183,   186,
     184,   185,   172,    -1,    66,    52,   200,    -1,    18,    -1,
      19,   198,    -1,    19,    56,   198,    -1,    20,   198,    -1,
      22,    -1,    24,    -1,    23,    -1,    25,   198,    -1,    26,
     198,    -1,   154,    27,   155,   156,    28,   159,   182,   183,
     186,   184,   185,   172,    -1,    45,    46,    -1,    -1,   131,
      -1,    -1,   156,   157,    -1,   158,    -1,   133,   158,    -1,
     199,    -1,   199,    33,   200,    -1,   159,   163,    -1,   198,
      -1,   198,   160,    -1,    36,   162,   198,    57,   193,   160,
      -1,    40,   161,   162,   198,    57,   193,   160,    -1,    38,
     162,   198,   160,    -1,    -1,    -1,    37,    -1,    -1,    39,
      -1,   133,   198,    -1,    42,    43,   200,   165,    44,   134,
     166,   135,   172,    -1,    -1,   134,   156,   135,    -1,   166,
     167,    -1,   201,    -1,   133,   201,    -1,   168,   169,    -1,
     201,    -1,   133,   201,    -1,    47,    28,   200,   182,   172,
      -1,    48,   200,    49,   173,   182,   172,    -1,   132,    -1,
      -1,   173,   174,    -1,   175,    -1,   133,   175,    -1,   200,
      16,   176,    -1,   200,    16,   201,    -1,   200,    16,    50,
      -1,   176,     8,   176,    -1,   176,     9,   176,    -1,   176,
       7,   176,    -1,   176,     5,   176,    -1,   176,     6,   176,
      -1,   134,   176,   135,    -1,     6,   176,    -1,     5,   176,
      -1,   177,    -1,   181,    -1,    89,   134,   181,   133,   181,
     135,    -1,    90,   134,   181,    98,   181,   180,   135,    -1,
      91,   134,   181,    98,   181,   180,   135,    -1,    99,   134,
     181,   133,   181,   135,    -1,   100,   134,   181,    98,   181,
     179,   135,    -1,   101,   134,   181,    98,   181,   179,   135,
      -1,   102,   134,   178,   133,   181,   133,   181,   135,    -1,
     103,   134,   181,    98,   181,   178,   135,    -1,   104,   134,
     181,    98,   181,   178,   135,    -1,   105,   134,   178,    28,
     181,   135,    -1,    81,   134,   181,   135,    -1,    83,   134,
     181,   135,    -1,   179,    -1,   180,    -1,    92,    -1,    93,
      -1,    94,    -1,    95,    -1,    96,    -1,    97,    -1,   200,
      -1,   201,    -1,    50,    -1,    29,   193,    -1,    -1,   125,
     126,   187,    -1,    -1,   128,   126,   190,    -1,    -1,    34,
      13,    -1,    34,    13,    35,    13,    -1,    -1,   127,   194,
      -1,    -1,   187,   188,    -1,   189,    -1,   133,   189,    -1,
     200,    -1,   190,   191,    -1,   192,    -1,   133,   192,    -1,
     200,    -1,   200,   129,    -1,   200,   130,    -1,   193,     3,
     193,    -1,   193,     4,   193,    -1,   134,   193,   135,    -1,
      32,   134,   193,   135,    -1,   197,   196,    -1,   194,     3,
     194,    -1,   194,     4,   194,    -1,   134,   194,   135,    -1,
      32,   134,   194,   135,    -1,   197,   195,    -1,   120,   134,
     200,   135,    16,   201,    -1,   121,   134,   200,   135,    16,
     201,    -1,   123,   134,   200,   135,    16,   201,    -1,   122,
     134,   200,   135,    16,   201,    -1,   124,   134,   200,   135,
      16,   201,    -1,   200,    16,   201,    -1,   200,    16,   200,
      -1,   200,   197,    30,   201,     4,   201,    -1,   200,   197,
      31,   134,   168,   135,    -1,   200,    41,    32,    50,    -1,
     200,    41,    50,    -1,   177,    16,   177,    -1,   177,    16,
     200,    -1,   177,    16,   201,    -1,    32,    -1,    -1,   200,
      -1,   200,    33,   200,    -1,   200,   200,    -1,   200,    -1,
     120,   134,   200,   135,    -1,   121,   134,   200,   135,    -1,
     123,   134,   200,   135,    -1,   122,   134,   200,   135,    -1,
     124,   134,   200,   135,    -1,   124,   134,     7,   135,    -1,
       7,    -1,   200,     7,    -1,    12,    -1,   136,    12,   136,
      -1,    11,    -1,   202,    -1,    14,    -1,   203,    -1,    17,
      -1,    50,    -1,   106,   134,   135,    -1,    13,    -1,     6,
      13,    -1,     5,    13,    -1,    15,    -1,     6,    15,    -1,
       5,    15,    -1,    68,    52,   200,   205,   172,    -1,    74,
      52,   200,   172,    -1,   206,   207,   208,   209,   210,   211,
      -1,    -1,    69,   201,    -1,    -1,    70,   201,    -1,    -1,
      71,   200,    -1,    -1,    72,    -1,    -1,    73,   201,    -1,
      -1,    75,    -1,    51,    52,   200,   134,   216,   135,   172,
      -1,    51,    56,   200,    57,   200,   134,   156,   135,   214,
     213,   215,   172,    -1,    62,    52,   200,    -1,    62,    56,
     200,    -1,    67,    52,   200,   172,    -1,    58,   214,    -1,
      59,   214,    -1,    60,   214,    -1,    -1,    61,    -1,    53,
      -1,    -1,    -1,    63,    13,    -1,   217,    -1,   217,   133,
     225,    -1,   217,   218,    -1,   219,    -1,   133,   219,    -1,
     220,    -1,   221,   237,   222,   224,   223,   236,    -1,   200,
      -1,    -1,   134,    13,   135,    -1,    -1,    55,   201,    -1,
      -1,    32,    50,    -1,   235,    -1,   226,    -1,   235,   133,
     226,    -1,   226,   227,    -1,   228,    -1,   133,   228,    -1,
      64,    54,   134,   229,   135,    65,   200,   134,   232,   135,
      -1,   229,   230,    -1,   231,    -1,   133,   231,    -1,   200,
      -1,   232,   233,    -1,   234,    -1,   133,   234,    -1,   200,
      -1,    53,    54,   134,   156,   135,   215,    -1,    -1,    21,
      -1,    76,    -1,    77,    -1,    78,    -1,    84,    -1,    86,
      -1,    85,    -1,    79,    -1,    81,    -1,    83,    -1,    80,
      -1,    82,    -1,    88,    -1,    87,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    44,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    59,    66,    74,    80,
      89,    98,   107,   112,   119,   125,   133,   134,   136,   139,
     140,   141,   142,   143,   151,   152,   154,   156,   158,   165,
     172,   179,   186,   193,   198,   203,   209,   214,   219,   224,
     229,   234,   240,   246,   250,   252,   256,   258,   259,   261,
     263,   264,   270,   271,   272,   274,   288,   301,   305,   307,
     308,   310,   311,   313,   319,   327,   328,   331,   332,   338,
     345,   346,   352,   359,   367,   375,   376,   379,   380,   383,
     385,   390,   395,   401,   407,   413,   419,   425,   431,   435,
     439,   443,   444,   446,   453,   460,   468,   475,   482,   489,
     500,   507,   514,   526,   534,   542,   547,   553,   558,   563,
     569,   574,   579,   585,   592,   600,   609,   622,   624,   625,
     627,   628,   630,   634,   638,   640,   641,   643,   644,   646,
     648,   654,   655,   657,   659,   664,   669,   675,   683,   690,
     691,   699,   715,   723,   730,   731,   739,   755,   764,   773,
     782,   791,   802,   813,   824,   840,   866,   874,   882,   890,
     900,   909,   913,   915,   920,   925,   931,   937,   942,   947,
     952,   957,   962,   967,   971,   976,   977,   979,   980,   981,
     982,   983,   984,   985,   998,   999,  1008,  1010,  1011,  1020,
    1022,  1033,  1040,  1042,  1043,  1049,  1050,  1057,  1058,  1065,
    1066,  1071,  1072,  1078,  1079,  1084,  1090,  1098,  1104,  1110,
    1118,  1122,  1126,  1131,  1136,  1140,  1146,  1151,  1152,  1158,
    1159,  1161,  1162,  1165,  1168,  1174,  1177,  1182,  1183,  1195,
    1196,  1208,  1209,  1214,  1215,  1216,  1218,  1219,  1221,  1223,
    1230,  1231,  1233,  1235,  1241,  1242,  1244,  1246,  1253,  1258,
    1259,  1280,  1284,  1288,  1292,  1296,  1300,  1304,  1309,  1314,
    1319,  1324,  1330,  1336
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
  "REVOKE", "ALL", "PRIVILEGES", "MIN", "MAX", "AVG", "SUM", "COUNT",
  "GROUP", "BY", "HAVING", "ORDER", "ASC", "DESC", "DISTINCT", "';'",
  "','", "'('", "')'", "'`'", "$accept", "command", "alter_statement",
  "management_statement", "user_manager_statement", "privilege_list",
  "privilege_list_L", "privilege", "grantee_list", "grantee_list_L",
  "grantee", "grant_statement", "revoke_statement", "copy_table_statement",
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
     380,   381,    59,    44,    40,    41,    96
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   137,   138,   138,   138,   138,   138,   138,   138,   138,
     138,   138,   138,   138,   138,   138,   139,   139,   139,   139,
     139,   139,   140,   141,   141,   141,   142,   142,   143,   144,
     144,   144,   144,   144,   145,   145,   146,   147,   148,   149,
     150,   150,   151,   152,   152,   152,   152,   152,   152,   152,
     152,   152,   153,   154,   154,   155,   155,   156,   156,   157,
     158,   158,   159,   159,   159,   160,   160,   160,   160,   161,
     161,   162,   162,   163,   164,   165,   165,   166,   166,   167,
     168,   168,   169,   170,   171,   172,   172,   173,   173,   174,
     175,   175,   175,   176,   176,   176,   176,   176,   176,   176,
     176,   176,   176,   177,   177,   177,   177,   177,   177,   177,
     177,   177,   177,   177,   177,   178,   178,   179,   179,   179,
     180,   180,   180,   181,   181,   181,   182,   182,   183,   183,
     184,   184,   185,   185,   185,   186,   186,   187,   187,   188,
     189,   190,   190,   191,   192,   192,   192,   193,   193,   193,
     193,   193,   194,   194,   194,   194,   194,   195,   195,   195,
     195,   195,   196,   196,   196,   196,   196,   196,   196,   196,
     196,   197,   197,   198,   198,   198,   199,   199,   199,   199,
     199,   199,   199,   199,   199,   200,   200,   201,   201,   201,
     201,   201,   201,   201,   202,   202,   202,   203,   203,   203,
     204,   204,   205,   206,   206,   207,   207,   208,   208,   209,
     209,   210,   210,   211,   211,   212,   212,   212,   212,   212,
     213,   213,   213,   213,   214,   214,   214,   215,   215,   216,
     216,   217,   217,   218,   219,   220,   221,   222,   222,   223,
     223,   224,   224,   225,   225,   225,   226,   226,   227,   228,
     229,   229,   230,   231,   232,   232,   233,   234,   235,   236,
     236,   237,   237,   237,   237,   237,   237,   237,   237,   237,
     237,   237,   237,   237
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     8,     7,     8,     6,
       9,     7,     3,     6,     4,     7,     2,     1,     2,     1,
       1,     1,     1,     2,     2,     1,     2,     1,     8,     7,
      15,    15,     3,     1,     2,     3,     2,     1,     1,     1,
       2,     2,    12,     2,     0,     1,     0,     2,     1,     2,
       1,     3,     2,     1,     2,     6,     7,     4,     0,     0,
       1,     0,     1,     2,     9,     0,     3,     2,     1,     2,
       2,     1,     2,     5,     6,     1,     0,     2,     1,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     1,     1,     6,     7,     7,     6,     7,     7,     8,
       7,     7,     6,     4,     4,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     0,     3,     0,
       3,     0,     2,     4,     0,     2,     0,     2,     1,     2,
       1,     2,     1,     2,     1,     2,     2,     3,     3,     3,
       4,     2,     3,     3,     3,     4,     2,     6,     6,     6,
       6,     6,     3,     3,     6,     6,     4,     3,     3,     3,
       3,     1,     0,     1,     3,     2,     1,     4,     4,     4,
       4,     4,     4,     1,     2,     1,     3,     1,     1,     1,
       1,     1,     1,     3,     1,     2,     2,     1,     2,     2,
       5,     4,     6,     0,     2,     0,     2,     0,     2,     0,
       1,     0,     2,     0,     1,     7,    12,     3,     3,     4,
       2,     2,     2,     0,     1,     1,     0,     0,     2,     1,
       3,     2,     1,     2,     1,     6,     1,     0,     3,     0,
       2,     0,     2,     1,     1,     3,     2,     1,     2,    10,
       2,     1,     2,     1,     2,     1,     2,     1,     6,     0,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
      54,    43,     0,     0,    47,    49,    48,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    14,    13,    10,    11,    12,
       9,     7,    15,     2,     0,     3,     4,     5,     8,     6,
     185,     0,     0,    44,   173,    46,    50,    51,     0,    53,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    86,     0,    29,    30,    32,
      31,     0,     0,    27,     0,     1,    56,    45,     0,     0,
     175,    75,   127,     0,     0,     0,     0,   217,   218,    86,
      42,    86,   203,    86,     0,     0,     0,    85,    22,     0,
      33,     0,     0,    26,     0,    55,     0,   186,   174,     0,
       0,     0,   172,    86,   127,    88,     0,     0,     0,     0,
       0,    24,   219,     0,    86,   205,   201,     0,     0,     0,
       0,     0,     0,     0,     0,    28,     0,   183,     0,     0,
       0,     0,     0,     0,    58,    60,   176,    56,     0,     0,
     171,   172,   126,     0,    83,     0,    87,    86,     0,    56,
     236,     0,   229,   232,   234,     0,     0,    86,     0,     0,
     187,   194,   189,   197,   191,   192,     0,   204,   188,   190,
     200,     0,   207,     0,     0,     0,     0,     0,     0,    86,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    57,
       0,   184,     0,    76,     0,   172,     0,   172,   172,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   151,   172,    89,    84,     0,     0,   125,     0,
      90,   101,   102,   123,   124,     0,    86,     0,   231,   261,
     262,   263,   267,   270,   268,   271,   269,   264,   266,   265,
     273,   272,   237,     0,    23,   196,   199,   195,   198,     0,
     206,     0,   209,    86,     0,     0,     0,    86,    86,    19,
     127,    35,    37,    86,     0,     0,     0,     0,     0,     0,
     127,    63,    59,    61,     0,     0,    78,     0,   149,   147,
     148,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   171,     0,     0,   194,   197,
     125,   100,   124,   194,   197,    99,     0,     0,     0,     0,
       0,     0,     0,   215,     0,     0,   233,   230,   244,   247,
     243,     0,   241,     0,   193,   208,   210,   211,    17,    86,
      86,     0,    21,    25,     0,    34,    86,    39,   177,   178,
     180,   179,   182,   181,     0,    62,   129,    71,    71,    69,
      64,     0,     0,    86,    77,   150,     0,     0,     0,     0,
       0,     0,     0,     0,   117,   118,   119,   120,   121,   122,
       0,   115,   116,     0,     0,     0,   168,   169,   170,   163,
     162,     0,   167,     0,     0,    98,    96,    97,    95,    93,
      94,     0,     0,     0,     0,   246,     0,     0,     0,   239,
     226,     0,   213,    16,    18,    86,    36,    38,    73,     0,
     136,    72,     0,     0,    70,    71,   127,    79,    74,   113,
     114,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   166,     0,     0,   127,     0,     0,   248,   245,   238,
     242,     0,   259,   225,   224,   223,   212,   214,   202,    20,
       0,   172,   131,     0,    68,     0,   129,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    81,
     129,     0,   253,     0,   251,   240,   260,   235,   226,   226,
     226,   227,   128,   138,   140,   171,   172,   135,     0,     0,
     134,   172,    67,     0,   136,   103,     0,     0,   106,     0,
       0,     0,     0,     0,   112,   164,     0,   165,    80,   136,
     227,     0,     0,   250,   220,   221,   222,     0,    86,     0,
     137,   172,     0,   172,   172,     0,     0,     0,     0,     0,
     156,     0,     0,    86,    68,   172,   131,   104,   105,   107,
     108,     0,   110,   111,    82,   131,   258,   252,     0,   228,
     216,   139,     0,   154,   152,   153,     0,     0,     0,     0,
       0,   130,   142,   144,   132,    52,    65,    68,   134,   109,
     134,     0,   155,     0,     0,     0,     0,     0,     0,   141,
     145,   146,     0,    66,    86,    86,     0,     0,     0,     0,
       0,     0,   143,   133,    41,    40,   257,     0,   255,     0,
       0,     0,     0,     0,     0,   249,   254,   157,   158,   160,
     159,   161,   256
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    24,    25,    26,    27,    72,   103,    73,   270,   345,
     271,    28,    29,    30,    31,    32,    33,    34,   106,   143,
     199,   144,   280,   360,   425,   422,   355,    35,   111,   285,
     364,   478,   518,    36,    37,    98,   114,   156,   115,   230,
     231,   380,   381,   382,   232,   113,   420,   500,   543,   462,
     492,   530,   493,   571,   589,   572,   152,   497,   540,   222,
     153,   281,   145,   233,   312,   178,   179,    38,   124,   125,
     182,   262,   337,   412,   458,    39,   491,   455,   528,   161,
     162,   238,   163,   164,   165,   332,   452,   409,   327,   328,
     405,   329,   483,   523,   484,   607,   616,   608,   330,   487,
     252
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -435
static const yytype_int16 yypact[] =
{
     427,  -435,    72,    19,  -435,  -435,  -435,    19,    19,    83,
      87,   120,    19,    63,    68,   126,   164,   179,   191,    94,
     198,   209,   238,   238,   274,  -435,  -435,  -435,  -435,  -435,
    -435,  -435,  -435,  -435,   254,  -435,  -435,  -435,  -435,  -435,
    -435,    19,   272,  -435,    16,  -435,  -435,  -435,    19,  -435,
      19,   251,    19,    19,    19,    19,    19,    19,    19,    19,
      19,    19,    19,    19,    19,   155,    19,  -435,  -435,  -435,
    -435,   222,   -12,  -435,     6,  -435,   207,  -435,   174,    19,
    -435,    -4,   316,    19,     1,   293,   247,  -435,  -435,   155,
    -435,   155,   305,   155,   193,   276,   349,  -435,  -435,   302,
    -435,    19,   238,  -435,    19,  -435,   208,  -435,  -435,   392,
     208,   388,   -20,   155,    14,  -435,   417,   415,    19,    19,
     437,  -435,  -435,   243,   155,   386,  -435,   345,   325,   326,
     350,   346,   356,    19,   351,  -435,   439,  -435,   334,   336,
     339,   342,   343,    -1,  -435,   446,   474,   207,   -10,   348,
     352,   -20,   109,   335,  -435,    19,  -435,   155,   277,   207,
    -435,   353,   354,  -435,  -435,   633,   357,   155,   184,   219,
    -435,  -435,  -435,  -435,  -435,  -435,   358,  -435,  -435,  -435,
    -435,   243,   412,    19,    19,    19,    19,    19,   473,   155,
      19,    19,    19,    19,    19,    19,    73,    19,   208,  -435,
      19,  -435,   208,  -435,   243,   -20,    32,   -20,   -20,   362,
     363,   364,   365,   366,   368,   372,   373,   374,   380,   382,
     383,   469,  -435,   187,  -435,  -435,   498,   540,     9,   602,
     395,  -435,  -435,  -435,    44,   208,   155,    76,  -435,  -435,
    -435,  -435,  -435,  -435,  -435,  -435,  -435,  -435,  -435,  -435,
    -435,  -435,   384,   208,  -435,  -435,  -435,  -435,  -435,   355,
    -435,    19,   449,   155,   387,   389,   408,   155,   155,  -435,
      38,  -435,  -435,   -35,   390,   391,   393,   394,   396,   397,
      47,   273,  -435,  -435,     4,   170,  -435,    71,  -435,   526,
    -435,   212,   212,   212,   212,   212,   212,   212,   212,   292,
     212,   212,   292,   644,   258,  -435,    77,   142,  -435,  -435,
    -435,  -435,  -435,  -435,  -435,  -435,    86,   602,   602,   602,
     602,   602,     5,  -435,   479,   480,  -435,  -435,   402,  -435,
     405,   527,   510,   189,  -435,  -435,  -435,   476,  -435,   155,
     155,    19,  -435,  -435,    19,  -435,   155,  -435,  -435,  -435,
    -435,  -435,  -435,  -435,    19,  -435,   422,   511,   511,   521,
    -435,    19,   243,   155,  -435,  -435,   424,   425,   428,   464,
     465,   436,   472,   482,  -435,  -435,  -435,  -435,  -435,  -435,
     445,  -435,  -435,   484,   485,   556,  -435,  -435,  -435,  -435,
    -435,   535,  -435,   243,   457,  -435,   230,   230,  -435,  -435,
    -435,    19,   458,   459,   531,  -435,   531,   461,   555,   551,
     169,   243,   534,  -435,  -435,   155,  -435,  -435,  -435,   492,
     483,  -435,    19,    19,  -435,   511,    47,  -435,  -435,  -435,
    -435,   212,   212,   212,   212,   212,   212,   212,   212,   212,
     212,  -435,   607,   243,    47,   208,    19,  -435,   402,  -435,
    -435,   243,   599,  -435,  -435,   261,  -435,  -435,  -435,  -435,
      19,    15,   494,   567,   273,    19,   422,   490,   266,   266,
     491,   241,   241,   495,   292,   292,   500,   243,   218,  -435,
     422,   237,  -435,   275,  -435,  -435,  -435,  -435,   169,   169,
     169,   564,   503,  -435,  -435,   499,    15,   249,   307,   512,
     603,   -20,  -435,   590,   483,  -435,   513,   516,  -435,   518,
     519,   212,   525,   528,  -435,  -435,   243,  -435,  -435,   483,
     564,    19,   597,  -435,  -435,  -435,  -435,   651,   155,    19,
    -435,    15,    75,    15,    15,   532,   533,   536,   537,   538,
    -435,    19,   652,   155,   333,   -20,   494,  -435,  -435,  -435,
    -435,   542,  -435,  -435,  -435,   494,  -435,  -435,    19,  -435,
    -435,  -435,    79,  -435,   664,  -435,    19,    19,    19,    19,
      19,   545,  -435,   117,   634,  -435,  -435,   333,   603,  -435,
     603,   539,  -435,   544,   546,   547,   549,   552,    19,  -435,
    -435,  -435,   662,  -435,   155,   155,    19,   670,   672,   673,
     674,   679,  -435,  -435,  -435,  -435,  -435,   279,  -435,   243,
     243,   243,   243,   243,    19,  -435,  -435,  -435,  -435,  -435,
    -435,  -435,  -435
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -435,  -435,  -435,  -435,  -435,   657,  -435,   594,   506,  -435,
     378,  -435,  -435,  -435,  -435,  -435,  -435,  -435,   -41,   -99,
    -435,   501,  -296,  -434,  -435,  -318,  -435,  -435,  -435,  -435,
    -435,  -435,  -435,  -435,  -435,   -23,  -435,  -435,   543,   -22,
    -129,  -288,   -66,   -14,  -275,  -101,  -380,  -344,  -187,  -408,
    -435,  -435,   171,  -435,  -435,   135,  -136,  -255,  -435,  -435,
    -219,     0,  -435,    -2,   -36,  -435,  -435,  -435,  -435,  -435,
    -435,  -435,  -435,  -435,  -435,  -435,  -435,   -93,   204,   548,
    -435,  -435,  -148,  -435,  -435,  -435,  -435,  -435,  -435,   320,
    -435,   324,  -435,  -435,   210,  -435,  -435,   115,  -435,  -435,
    -435
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -93
static const yytype_int16 yytable[] =
{
      44,    44,    43,    45,   307,    44,    44,    46,    47,   -92,
      51,   148,   150,   157,   385,   206,   366,   367,   368,   369,
     370,   371,   372,   373,   221,   383,   384,   197,    40,   109,
     502,    40,   361,   401,   117,   207,   208,   265,   -92,    44,
     423,    77,    80,   112,   -91,   101,    81,   495,    82,    79,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,   104,    99,   426,   121,   112,   122,   287,
     126,   289,   290,   -91,   207,   208,   112,   108,   533,   534,
     278,   116,   533,   534,    40,    40,   504,   177,    40,   326,
     154,   317,   318,   319,   320,   321,   546,    97,   344,   134,
     519,   180,   136,   284,   146,   444,   202,   465,   146,   391,
     576,   555,   207,   208,   151,    52,   160,   166,   235,    53,
      55,   102,   234,   198,    56,   203,    48,   392,    41,   324,
     110,   189,   198,    49,   225,   118,   322,   198,   198,   102,
     325,   -92,   -92,   593,   254,   260,    62,   155,    50,   496,
      63,   223,    42,   116,   333,    42,   467,   468,   469,   470,
     471,   472,   473,   474,   475,   476,   269,   288,   286,   346,
      54,   344,   393,   394,   386,    57,   -91,   -91,    58,   356,
     354,   263,   160,   160,   266,   267,   512,   513,   272,   272,
     274,   275,   276,   277,   279,    44,   146,   255,   283,   256,
     146,    64,   578,   304,   311,   315,   365,   316,    42,    42,
     563,   580,    42,   323,   582,   137,    59,   168,   169,   305,
      40,   395,   453,   170,    40,   171,   172,   173,   306,   174,
     454,    60,   257,   146,   258,   160,   551,   319,   320,   321,
     338,   532,   498,    61,   342,   343,   590,   591,   168,   169,
     347,   146,   533,   534,   170,   127,   171,   172,   173,   335,
     174,    66,   310,   168,   169,    67,    65,   388,   390,   170,
      40,   171,   172,   173,    75,   174,   562,   498,   564,   565,
      68,    76,   226,   227,    78,    69,    70,    97,   170,    40,
     171,   172,   173,   175,   174,   396,   397,   398,   399,   400,
      83,   387,   389,   362,   128,   363,   129,   130,   175,   357,
     107,   358,   498,   359,   498,   498,   413,   414,   176,   488,
     489,   490,   198,   417,   410,   466,   427,   228,   138,   139,
     140,   141,   142,   374,   375,   376,   207,   208,   105,   415,
     428,   100,   272,   480,    42,   112,   481,    40,    42,   176,
     119,   516,    44,   517,   418,   120,    71,   442,   209,    44,
     210,   377,   378,   379,   176,   544,   211,   212,   213,   357,
     198,   358,   520,   359,   123,   456,   214,   215,   216,   217,
     218,   219,   220,   176,   374,   375,   376,   377,   378,   379,
     131,   594,   459,   595,    42,   524,   525,   526,   132,    44,
     317,   318,   319,   320,   321,   509,   510,   479,   521,   577,
     522,   229,   614,    42,   615,   485,   209,   133,   210,   147,
      44,    44,   463,   464,   211,   212,   213,   535,   536,   537,
     538,   539,   149,   158,   214,   215,   216,   217,   218,   219,
     220,   515,   159,   146,   482,     1,     2,     3,   167,     4,
       5,     6,     7,     8,   506,   507,   181,   183,   494,   184,
     185,   187,   186,    44,   188,   503,   190,   191,   192,     9,
     193,    42,    10,   194,    11,    12,   195,   196,    13,   200,
     554,   201,   204,   261,   268,   303,   205,   237,   236,    14,
     334,   253,   259,    15,    16,    17,   291,   292,   293,   294,
     295,    18,   296,   226,   227,   560,   297,   298,   299,   170,
      40,   308,   172,   309,   300,   174,   301,   302,   331,   482,
     575,   336,   339,   341,   340,   348,   349,   494,   350,   351,
     208,   352,   353,   402,   403,   404,    19,    20,   406,   573,
     407,    21,   408,    22,    23,   226,   227,   419,   310,   411,
     421,   170,    40,   313,   172,   314,   581,   174,   424,   429,
     430,   431,   432,   433,   583,   584,   585,   586,   587,   434,
     435,   604,   605,   617,   618,   619,   620,   621,   437,   209,
     436,   210,   438,   439,   440,   441,   573,   211,   212,   213,
     310,   443,   445,   446,   606,   325,   449,   214,   215,   216,
     217,   218,   219,   220,   176,   450,   451,   226,   227,   457,
     461,   477,   606,   170,    40,   171,   172,   173,   460,   174,
     486,   209,   499,   210,   501,   505,   508,   527,   511,   211,
     212,   213,   229,   531,    42,   514,   529,   542,   541,   214,
     215,   216,   217,   218,   219,   220,   176,   545,   547,   168,
     169,   548,   310,   549,   550,   170,    40,   171,   172,   173,
     552,   174,   558,   553,   559,   574,   566,   567,   534,   592,
     568,   569,   570,   596,   229,   603,    42,   579,   588,   597,
      74,   598,   599,   209,   600,   210,   609,   601,   610,   611,
     612,   211,   212,   213,   175,   613,   135,   273,   224,   282,
     561,   214,   215,   216,   217,   218,   219,   220,   176,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   416,   602,   556,   209,   448,   210,   447,   622,
       0,   557,   264,   211,   212,   213,   229,     0,    42,     0,
       0,     0,     0,   214,   215,   216,   217,   218,   219,   220,
     176,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      42
};

static const yytype_int16 yycheck[] =
{
       2,     3,     2,     3,   223,     7,     8,     7,     8,     0,
      12,   110,    32,   114,   302,   151,   291,   292,   293,   294,
     295,   296,   297,   298,   153,   300,   301,    28,    12,    33,
     464,    12,    28,    28,    33,     3,     4,   185,    29,    41,
     358,    41,    44,    29,     0,    57,    48,    32,    50,    33,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    57,    66,   361,    89,    29,    91,   205,
      93,   207,   208,    29,     3,     4,    29,    79,     3,     4,
       7,    83,     3,     4,    12,    12,   466,   123,    12,   237,
     113,     5,     6,     7,     8,     9,   504,   132,   133,   101,
     480,   124,   104,   202,   106,   401,   147,   425,   110,    32,
     544,   519,     3,     4,   134,    52,   118,   119,   159,    56,
      52,   133,   158,   133,    56,   135,    43,    50,    56,    53,
     134,   133,   133,    46,   157,   134,   235,   133,   133,   133,
      64,   132,   133,   577,   167,   181,    52,   133,    28,   134,
      56,   153,   136,   155,   253,   136,   431,   432,   433,   434,
     435,   436,   437,   438,   439,   440,   189,   135,   204,   270,
     107,   133,    30,    31,   303,   107,   132,   133,    52,   280,
     133,   183,   184,   185,   186,   187,   474,   475,   190,   191,
     192,   193,   194,   195,   196,   197,   198,    13,   200,    15,
     202,   107,   546,    16,   226,   227,   135,   229,   136,   136,
     135,   555,   136,   236,   135,     7,    52,     5,     6,    32,
      12,   135,    53,    11,    12,    13,    14,    15,    41,    17,
      61,    52,    13,   235,    15,   237,   511,     7,     8,     9,
     263,   496,   461,    52,   267,   268,   129,   130,     5,     6,
     273,   253,     3,     4,    11,    62,    13,    14,    15,   261,
      17,    52,    50,     5,     6,    27,    68,   303,   304,    11,
      12,    13,    14,    15,     0,    17,   531,   496,   533,   534,
      42,    27,     5,     6,    12,    47,    48,   132,    11,    12,
      13,    14,    15,    50,    17,   317,   318,   319,   320,   321,
      49,   303,   304,   133,   111,   135,   113,   114,    50,    36,
     136,    38,   531,    40,   533,   534,   339,   340,   106,    58,
      59,    60,   133,   346,   135,   426,   362,    50,   120,   121,
     122,   123,   124,    92,    93,    94,     3,     4,   131,   341,
     363,   119,   344,   444,   136,    29,   445,    12,   136,   106,
      57,   133,   354,   135,   354,   108,   118,   393,    81,   361,
      83,    95,    96,    97,   106,   501,    89,    90,    91,    36,
     133,    38,   135,    40,    69,   411,    99,   100,   101,   102,
     103,   104,   105,   106,    92,    93,    94,    95,    96,    97,
     114,   578,   415,   580,   136,   488,   489,   490,    49,   401,
       5,     6,     7,     8,     9,   471,   472,   443,   133,   545,
     135,   134,   133,   136,   135,   451,    81,   115,    83,    27,
     422,   423,   422,   423,    89,    90,    91,   120,   121,   122,
     123,   124,    44,    16,    99,   100,   101,   102,   103,   104,
     105,   477,    27,   445,   446,    18,    19,    20,    11,    22,
      23,    24,    25,    26,   468,   469,    70,   112,   460,   134,
     134,   115,   112,   465,   108,   465,   115,    28,   134,    42,
     134,   136,    45,   134,    47,    48,   134,   134,    51,    33,
     516,     7,   134,    71,    11,    16,   134,   133,   135,    62,
     135,   134,   134,    66,    67,    68,   134,   134,   134,   134,
     134,    74,   134,     5,     6,   528,   134,   134,   134,    11,
      12,    13,    14,    15,   134,    17,   134,   134,   134,   521,
     543,    72,   135,   115,   135,   135,   135,   529,   135,   135,
       4,   135,   135,    54,    54,   133,   109,   110,   133,   541,
      13,   114,    32,   116,   117,     5,     6,   125,    50,    73,
      39,    11,    12,    13,    14,    15,   558,    17,    37,   135,
     135,   133,    98,    98,   566,   567,   568,   569,   570,   133,
      98,   594,   595,   609,   610,   611,   612,   613,   133,    81,
      98,    83,    98,    98,    28,    50,   588,    89,    90,    91,
      50,   134,   134,   134,   596,    64,   135,    99,   100,   101,
     102,   103,   104,   105,   106,    50,    55,     5,     6,    75,
     127,     4,   614,    11,    12,    13,    14,    15,   126,    17,
      21,    81,   128,    83,    57,   135,   135,    63,   133,    89,
      90,    91,   134,   134,   136,   135,   133,    34,   126,    99,
     100,   101,   102,   103,   104,   105,   106,    57,   135,     5,
       6,   135,    50,   135,   135,    11,    12,    13,    14,    15,
     135,    17,    65,   135,    13,    13,   134,   134,     4,    35,
     134,   134,   134,   134,   134,    13,   136,   135,   133,   135,
      23,   135,   135,    81,   135,    83,    16,   135,    16,    16,
      16,    89,    90,    91,    50,    16,   102,   191,   155,   198,
     529,    99,   100,   101,   102,   103,   104,   105,   106,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,   344,   588,   520,    81,   406,    83,   404,   614,
      -1,   521,   184,    89,    90,    91,   134,    -1,   136,    -1,
      -1,    -1,    -1,    99,   100,   101,   102,   103,   104,   105,
     106,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     136
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    18,    19,    20,    22,    23,    24,    25,    26,    42,
      45,    47,    48,    51,    62,    66,    67,    68,    74,   109,
     110,   114,   116,   117,   138,   139,   140,   141,   148,   149,
     150,   151,   152,   153,   154,   164,   170,   171,   204,   212,
      12,    56,   136,   198,   200,   198,   198,   198,    43,    46,
      28,   200,    52,    56,   107,    52,    56,   107,    52,    52,
      52,    52,    52,    56,   107,    68,    52,    27,    42,    47,
      48,   118,   142,   144,   142,     0,    27,   198,    12,    33,
     200,   200,   200,    49,   200,   200,   200,   200,   200,   200,
     200,   200,   200,   200,   200,   200,   200,   132,   172,   200,
     119,    57,   133,   143,    57,   131,   155,   136,   200,    33,
     134,   165,    29,   182,   173,   175,   200,    33,   134,    57,
     108,   172,   172,    69,   205,   206,   172,    62,   111,   113,
     114,   114,    49,   115,   200,   144,   200,     7,   120,   121,
     122,   123,   124,   156,   158,   199,   200,    27,   156,    44,
      32,   134,   193,   197,   172,   133,   174,   182,    16,    27,
     200,   216,   217,   219,   220,   221,   200,    11,     5,     6,
      11,    13,    14,    15,    17,    50,   106,   201,   202,   203,
     172,    70,   207,   112,   134,   134,   112,   115,   108,   200,
     115,    28,   134,   134,   134,   134,   134,    28,   133,   157,
      33,     7,   155,   135,   134,   134,   193,     3,     4,    81,
      83,    89,    90,    91,    99,   100,   101,   102,   103,   104,
     105,   177,   196,   200,   175,   172,     5,     6,    50,   134,
     176,   177,   181,   200,   201,   155,   135,   133,   218,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,   237,   134,   172,    13,    15,    13,    15,   134,
     201,    71,   208,   200,   216,   219,   200,   200,    11,   172,
     145,   147,   200,   145,   200,   200,   200,   200,     7,   200,
     159,   198,   158,   200,   156,   166,   201,   193,   135,   193,
     193,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   134,    16,    16,    32,    41,   197,    13,    15,
      50,   176,   201,    13,    15,   176,   176,     5,     6,     7,
       8,     9,   156,   172,    53,    64,   219,   225,   226,   228,
     235,   134,   222,   156,   135,   200,    72,   209,   172,   135,
     135,   115,   172,   172,   133,   146,   182,   172,   135,   135,
     135,   135,   135,   135,   133,   163,   182,    36,    38,    40,
     160,    28,   133,   135,   167,   135,   181,   181,   181,   181,
     181,   181,   181,   181,    92,    93,    94,    95,    96,    97,
     178,   179,   180,   181,   181,   178,   177,   200,   201,   200,
     201,    32,    50,    30,    31,   135,   176,   176,   176,   176,
     176,    28,    54,    54,   133,   227,   133,    13,    32,   224,
     135,    73,   210,   172,   172,   200,   147,   172,   198,   125,
     183,    39,   162,   162,    37,   161,   159,   201,   172,   135,
     135,   133,    98,    98,   133,    98,    98,   133,    98,    98,
      28,    50,   201,   134,   159,   134,   134,   228,   226,   135,
      50,    55,   223,    53,    61,   214,   201,    75,   211,   172,
     126,   127,   186,   198,   198,   162,   182,   181,   181,   181,
     181,   181,   181,   181,   181,   181,   181,     4,   168,   201,
     182,   156,   200,   229,   231,   201,    21,   236,    58,    59,
      60,   213,   187,   189,   200,    32,   134,   194,   197,   128,
     184,    57,   160,   198,   183,   135,   180,   180,   135,   179,
     179,   133,   178,   178,   135,   201,   133,   135,   169,   183,
     135,   133,   135,   230,   214,   214,   214,    63,   215,   133,
     188,   134,   194,     3,     4,   120,   121,   122,   123,   124,
     195,   126,    34,   185,   193,    57,   186,   135,   135,   135,
     135,   181,   135,   135,   201,   186,   215,   231,    65,    13,
     172,   189,   194,   135,   194,   194,   134,   134,   134,   134,
     134,   190,   192,   200,    13,   172,   160,   193,   184,   135,
     184,   200,   135,   200,   200,   200,   200,   200,   133,   191,
     129,   130,    35,   160,   185,   185,   134,   135,   135,   135,
     135,   135,   192,    13,   172,   172,   200,   232,   234,    16,
      16,    16,    16,    16,   133,   135,   233,   201,   201,   201,
     201,   201,   234
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
    { YYACCEPT; }
    break;

  case 15:

/* Line 1464 of yacc.c  */
#line 57 "dmlyacc.yxx"
    {YYACCEPT;}
    break;

  case 16:

/* Line 1464 of yacc.c  */
#line 60 "dmlyacc.yxx"
    {
            parsedData->setStmtType(AlterStatement);
            parsedData->setAlterType(ALTERADD);
            parsedData->setTableName((yyvsp[(3) - (8)].stringval));
            free((yyvsp[(3) - (8)].stringval)); 
	}
    break;

  case 17:

/* Line 1464 of yacc.c  */
#line 67 "dmlyacc.yxx"
    {
            parsedData->setStmtType(AlterStatement);
            parsedData->setAlterType(ALTERDROP);
            parsedData->setTableName((yyvsp[(3) - (7)].stringval));
            parsedData->setIndexName((yyvsp[(6) - (7)].stringval)); 
            free((yyvsp[(3) - (7)].stringval));
	}
    break;

  case 18:

/* Line 1464 of yacc.c  */
#line 75 "dmlyacc.yxx"
    {
            printf(" Not Implemented\n");
            free((yyvsp[(3) - (8)].stringval));
            YYABORT;
	}
    break;

  case 19:

/* Line 1464 of yacc.c  */
#line 81 "dmlyacc.yxx"
    {
            parsedData->setStmtType(AlterStatement);
            parsedData->setAlterType(ALTERTABLERENAME);
            parsedData->setTableName((yyvsp[(3) - (6)].stringval));
            parsedData->setIndexName((yyvsp[(5) - (6)].stringval)); 
            free((yyvsp[(3) - (6)].stringval)); free((yyvsp[(5) - (6)].stringval));

	}
    break;

  case 20:

/* Line 1464 of yacc.c  */
#line 90 "dmlyacc.yxx"
    {
            parsedData->setStmtType(AlterStatement);
            parsedData->setAlterType(ALTERFIELDRENAME);
            parsedData->setTableName((yyvsp[(3) - (9)].stringval));
            parsedData->setIndexName((yyvsp[(6) - (9)].stringval));
            parsedData->setPKTableName((yyvsp[(8) - (9)].stringval));
            free((yyvsp[(3) - (9)].stringval)); free((yyvsp[(5) - (9)].stringval)); free((yyvsp[(8) - (9)].stringval));
        }
    break;

  case 21:

/* Line 1464 of yacc.c  */
#line 99 "dmlyacc.yxx"
    {
            parsedData->setStmtType(AlterStatement);
            parsedData->setAlterType(ALTERINDEXRENAME);
            parsedData->setTableName((yyvsp[(3) - (7)].stringval));
            parsedData->setIndexName((yyvsp[(6) - (7)].stringval)); 
            free((yyvsp[(3) - (7)].stringval)); free((yyvsp[(5) - (7)].stringval));
        }
    break;

  case 22:

/* Line 1464 of yacc.c  */
#line 108 "dmlyacc.yxx"
    {
           parsedData->setStmtType(MgmtStatement);
	}
    break;

  case 23:

/* Line 1464 of yacc.c  */
#line 113 "dmlyacc.yxx"
    {
            parsedData->setStmtType(UserStatement);
            parsedData->createUserNode((char*)(yyvsp[(3) - (6)].stringval),(char*)(yyvsp[(5) - (6)].stringval));
            free((yyvsp[(3) - (6)].stringval));
            free((yyvsp[(5) - (6)].stringval));
	}
    break;

  case 24:

/* Line 1464 of yacc.c  */
#line 120 "dmlyacc.yxx"
    {
            parsedData->setStmtType(UserStatement);
            parsedData->dropUserNode((char*)(yyvsp[(3) - (4)].stringval));
            free((yyvsp[(3) - (4)].stringval));
        }
    break;

  case 25:

/* Line 1464 of yacc.c  */
#line 126 "dmlyacc.yxx"
    {
            parsedData->setStmtType(UserStatement);
            parsedData->alterUserNode((char*)(yyvsp[(3) - (7)].stringval),(char*)(yyvsp[(6) - (7)].stringval));
            free((yyvsp[(3) - (7)].stringval));
            free((yyvsp[(6) - (7)].stringval));
	}
    break;

  case 29:

/* Line 1464 of yacc.c  */
#line 139 "dmlyacc.yxx"
    { parsedData->insertPrivilege(PRIV_SELECT); }
    break;

  case 30:

/* Line 1464 of yacc.c  */
#line 140 "dmlyacc.yxx"
    { parsedData->insertPrivilege(PRIV_INSERT); }
    break;

  case 31:

/* Line 1464 of yacc.c  */
#line 141 "dmlyacc.yxx"
    { parsedData->insertPrivilege(PRIV_UPDATE); }
    break;

  case 32:

/* Line 1464 of yacc.c  */
#line 142 "dmlyacc.yxx"
    { parsedData->insertPrivilege(PRIV_DELETE); }
    break;

  case 33:

/* Line 1464 of yacc.c  */
#line 144 "dmlyacc.yxx"
    { 
            parsedData->insertPrivilege(PRIV_SELECT);
            parsedData->insertPrivilege(PRIV_INSERT);
            parsedData->insertPrivilege(PRIV_UPDATE);
            parsedData->insertPrivilege(PRIV_DELETE);
        }
    break;

  case 37:

/* Line 1464 of yacc.c  */
#line 156 "dmlyacc.yxx"
    { parsedData->insertGrantee((yyvsp[(1) - (1)].stringval)); }
    break;

  case 38:

/* Line 1464 of yacc.c  */
#line 159 "dmlyacc.yxx"
    {
            parsedData->setStmtType(DclStatement);
            parsedData->setTableName((yyvsp[(4) - (8)].stringval));
            parsedData->constructDclNodes(GRANTACCESS);
    }
    break;

  case 39:

/* Line 1464 of yacc.c  */
#line 166 "dmlyacc.yxx"
    {
            parsedData->setStmtType(DclStatement);
            parsedData->setTableName((yyvsp[(4) - (7)].stringval));
            parsedData->constructDclNodes(REVOKEACCESS);
    }
    break;

  case 40:

/* Line 1464 of yacc.c  */
#line 173 "dmlyacc.yxx"
    {
            parsedData->setStmtType(CopyTableStatement);
            parsedData->setPKTableName((yyvsp[(3) - (15)].stringval));
            parsedData->setCreateTbl();
            free((yyvsp[(3) - (15)].stringval));
        }
    break;

  case 41:

/* Line 1464 of yacc.c  */
#line 180 "dmlyacc.yxx"
    {
            parsedData->setStmtType(CopyTableStatement);
            parsedData->setPKTableName((yyvsp[(3) - (15)].stringval));
            free((yyvsp[(3) - (15)].stringval));
        }
    break;

  case 42:

/* Line 1464 of yacc.c  */
#line 187 "dmlyacc.yxx"
    {
            parsedData->setStmtType(CompactTableStatement);
            parsedData->setTableName((yyvsp[(3) - (3)].stringval));
            free((yyvsp[(3) - (3)].stringval));
        }
    break;

  case 43:

/* Line 1464 of yacc.c  */
#line 194 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetTables);
	}
    break;

  case 44:

/* Line 1464 of yacc.c  */
#line 199 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetColumns);
        }
    break;

  case 45:

/* Line 1464 of yacc.c  */
#line 204 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetIndexes);
                   
        }
    break;

  case 46:

/* Line 1464 of yacc.c  */
#line 210 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetPriIndex);
        }
    break;

  case 47:

/* Line 1464 of yacc.c  */
#line 215 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetCatalogs);
        }
    break;

  case 48:

/* Line 1464 of yacc.c  */
#line 220 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetTableType);
        }
    break;

  case 49:

/* Line 1464 of yacc.c  */
#line 225 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetDataType);
        }
    break;

  case 50:

/* Line 1464 of yacc.c  */
#line 230 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetImportKey);
        }
    break;

  case 51:

/* Line 1464 of yacc.c  */
#line 235 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetExportKey);
        }
    break;

  case 52:

/* Line 1464 of yacc.c  */
#line 241 "dmlyacc.yxx"
    {
            parsedData->setStmtType(SelectStatement);
            parsedData->setCacheWorthy(true);
        }
    break;

  case 53:

/* Line 1464 of yacc.c  */
#line 247 "dmlyacc.yxx"
    {
           parsedData->setExplain();
	}
    break;

  case 55:

/* Line 1464 of yacc.c  */
#line 253 "dmlyacc.yxx"
    { 
            parsedData->setDistinct();
        }
    break;

  case 61:

/* Line 1464 of yacc.c  */
#line 265 "dmlyacc.yxx"
    {
            parsedData->insertFieldAlias((char*)(yyvsp[(3) - (3)].stringval));
            free((char*)(yyvsp[(3) - (3)].stringval));
        }
    break;

  case 65:

/* Line 1464 of yacc.c  */
#line 275 "dmlyacc.yxx"
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

  case 66:

/* Line 1464 of yacc.c  */
#line 289 "dmlyacc.yxx"
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

  case 67:

/* Line 1464 of yacc.c  */
#line 302 "dmlyacc.yxx"
    {
            parsedData->insertJoinType(INNER_JOIN);
        }
    break;

  case 73:

/* Line 1464 of yacc.c  */
#line 314 "dmlyacc.yxx"
    {
            parsedData->insertJoinType(INNER_JOIN);
        }
    break;

  case 74:

/* Line 1464 of yacc.c  */
#line 320 "dmlyacc.yxx"
    {
            parsedData->setStmtType(InsertStatement);
            parsedData->setTableName((yyvsp[(3) - (9)].stringval)); 
            free((yyvsp[(3) - (9)].stringval));
        }
    break;

  case 78:

/* Line 1464 of yacc.c  */
#line 333 "dmlyacc.yxx"
    {
            parsedData->insertValue((char*)(yyvsp[(1) - (1)].stringval));
            free((yyvsp[(1) - (1)].stringval));
        }
    break;

  case 79:

/* Line 1464 of yacc.c  */
#line 339 "dmlyacc.yxx"
    {
            parsedData->insertValue((char*)(yyvsp[(2) - (2)].stringval));
            free((yyvsp[(2) - (2)].stringval));
        }
    break;

  case 81:

/* Line 1464 of yacc.c  */
#line 347 "dmlyacc.yxx"
    {
            parsedData->insertInValue((char*)(yyvsp[(1) - (1)].stringval));
            free((yyvsp[(1) - (1)].stringval));
        }
    break;

  case 82:

/* Line 1464 of yacc.c  */
#line 353 "dmlyacc.yxx"
    {
            parsedData->insertInValue((char*)(yyvsp[(2) - (2)].stringval));
            free((yyvsp[(2) - (2)].stringval));
        }
    break;

  case 83:

/* Line 1464 of yacc.c  */
#line 360 "dmlyacc.yxx"
    {
            parsedData->setStmtType(DeleteStatement);
            parsedData->setTableName((yyvsp[(3) - (5)].stringval)); 
            free((yyvsp[(3) - (5)].stringval));
	}
    break;

  case 84:

/* Line 1464 of yacc.c  */
#line 368 "dmlyacc.yxx"
    {
            parsedData->setStmtType(UpdateStatement);
            parsedData->setTableName((yyvsp[(2) - (6)].stringval)); 
            free( (yyvsp[(2) - (6)].stringval) );
	}
    break;

  case 90:

/* Line 1464 of yacc.c  */
#line 386 "dmlyacc.yxx"
    {
           parsedData->insertUpdateExpression( (char*) (yyvsp[(1) - (3)].stringval), (Expression* ) (yyvsp[(3) - (3)].Expression));
           free( (yyvsp[(1) - (3)].stringval) ); free((yyvsp[(2) - (3)].stringval));
        }
    break;

  case 91:

/* Line 1464 of yacc.c  */
#line 391 "dmlyacc.yxx"
    { 
            parsedData->insertUpdateValue( (char*) (yyvsp[(1) - (3)].stringval), (char*) (yyvsp[(3) - (3)].stringval));
            free( (yyvsp[(1) - (3)].stringval) ); free((yyvsp[(2) - (3)].stringval));free( (yyvsp[(3) - (3)].stringval) ); 
        }
    break;

  case 92:

/* Line 1464 of yacc.c  */
#line 396 "dmlyacc.yxx"
    {
            parsedData->insertUpdateValue( (char*) (yyvsp[(1) - (3)].stringval), (char*) (yyvsp[(3) - (3)].stringval));
            free( (yyvsp[(1) - (3)].stringval) ); free((yyvsp[(2) - (3)].stringval));free( (yyvsp[(3) - (3)].stringval) );
        }
    break;

  case 93:

/* Line 1464 of yacc.c  */
#line 402 "dmlyacc.yxx"
    {
            Expression* exp;
            exp=parsedData->insertExpression((Expression *)(yyvsp[(1) - (3)].Expression), division, (Expression *)(yyvsp[(3) - (3)].Expression));
            (yyval.Expression)=exp;
        }
    break;

  case 94:

/* Line 1464 of yacc.c  */
#line 408 "dmlyacc.yxx"
    {
            Expression* exp;
            exp=parsedData->insertExpression((Expression *)(yyvsp[(1) - (3)].Expression), modulus, (Expression *)(yyvsp[(3) - (3)].Expression));
            (yyval.Expression)=exp;
        }
    break;

  case 95:

/* Line 1464 of yacc.c  */
#line 414 "dmlyacc.yxx"
    {
            Expression* exp;
            exp=parsedData->insertExpression((Expression *)(yyvsp[(1) - (3)].Expression), multiplication, (Expression *)(yyvsp[(3) - (3)].Expression));
            (yyval.Expression)=exp;
        }
    break;

  case 96:

/* Line 1464 of yacc.c  */
#line 420 "dmlyacc.yxx"
    {
            Expression* exp;
            exp=parsedData->insertExpression((Expression *)(yyvsp[(1) - (3)].Expression), addition, (Expression *)(yyvsp[(3) - (3)].Expression));
            (yyval.Expression)=exp;
        }
    break;

  case 97:

/* Line 1464 of yacc.c  */
#line 426 "dmlyacc.yxx"
    {
            Expression* exp;
            exp=parsedData->insertExpression((Expression *)(yyvsp[(1) - (3)].Expression), subtraction, (Expression *)(yyvsp[(3) - (3)].Expression));
            (yyval.Expression)=exp;
        }
    break;

  case 98:

/* Line 1464 of yacc.c  */
#line 432 "dmlyacc.yxx"
    {
            (yyval.Expression)=(yyvsp[(2) - (3)].Expression);
        }
    break;

  case 99:

/* Line 1464 of yacc.c  */
#line 436 "dmlyacc.yxx"
    {
            (yyval.Expression) = (yyvsp[(2) - (2)].Expression);
        }
    break;

  case 100:

/* Line 1464 of yacc.c  */
#line 440 "dmlyacc.yxx"
    {
            (yyval.Expression) = (yyvsp[(2) - (2)].Expression);
        }
    break;

  case 103:

/* Line 1464 of yacc.c  */
#line 447 "dmlyacc.yxx"
    {
              Expression* exp;
              parsedData->setFunctionType(DATEDIFF);
              exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (6)].Expression), DATEDIFF, (Expression *)(yyvsp[(5) - (6)].Expression));
            (yyval.Expression)=exp;
        }
    break;

  case 104:

/* Line 1464 of yacc.c  */
#line 454 "dmlyacc.yxx"
    {
	         Expression* exp;
             parsedData->setFunctionType((*(FunctionType *)(yyvsp[(6) - (7)].FunctionType)));
             exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (7)].Expression), (*(FunctionType *)(yyvsp[(6) - (7)].FunctionType)), (Expression *)(yyvsp[(5) - (7)].Expression));
             (yyval.Expression)=exp;
	    }
    break;

  case 105:

/* Line 1464 of yacc.c  */
#line 461 "dmlyacc.yxx"
    {
             Expression* exp;
             //parsedData->setFunctionType((*(FunctionType *)$6));
             parsedData->setFunctionType((FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+3));
             exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (7)].Expression), (FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+3), (Expression *)(yyvsp[(5) - (7)].Expression));
             (yyval.Expression)=exp;
        }
    break;

  case 106:

/* Line 1464 of yacc.c  */
#line 469 "dmlyacc.yxx"
    {
              Expression* exp;
              parsedData->setFunctionType(TIMEDIFF);
              exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (6)].Expression), TIMEDIFF, (Expression *)(yyvsp[(5) - (6)].Expression));
            (yyval.Expression)=exp;
        }
    break;

  case 107:

/* Line 1464 of yacc.c  */
#line 476 "dmlyacc.yxx"
    {
             Expression* exp;
             parsedData->setFunctionType((*(FunctionType *)(yyvsp[(6) - (7)].FunctionType)));
             exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (7)].Expression), (*(FunctionType *)(yyvsp[(6) - (7)].FunctionType)), (Expression *)(yyvsp[(5) - (7)].Expression));
             (yyval.Expression)=exp;
        }
    break;

  case 108:

/* Line 1464 of yacc.c  */
#line 483 "dmlyacc.yxx"
    {
             Expression* exp;
             parsedData->setFunctionType((FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+3));
             exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (7)].Expression), (FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+3), (Expression *)(yyvsp[(5) - (7)].Expression));
             (yyval.Expression)=exp;
        }
    break;

  case 109:

/* Line 1464 of yacc.c  */
#line 490 "dmlyacc.yxx"
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

  case 110:

/* Line 1464 of yacc.c  */
#line 501 "dmlyacc.yxx"
    {
             Expression* exp;
             parsedData->setFunctionType((FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+12));
             exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (7)].Expression), (FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+12), (Expression *)(yyvsp[(5) - (7)].Expression));
             (yyval.Expression)=exp;
        }
    break;

  case 111:

/* Line 1464 of yacc.c  */
#line 508 "dmlyacc.yxx"
    {
             Expression* exp;
             parsedData->setFunctionType((FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+15));
             exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (7)].Expression), (FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+15), (Expression *)(yyvsp[(5) - (7)].Expression));
             (yyval.Expression)=exp;
        }
    break;

  case 112:

/* Line 1464 of yacc.c  */
#line 515 "dmlyacc.yxx"
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

  case 113:

/* Line 1464 of yacc.c  */
#line 527 "dmlyacc.yxx"
    {
            Expression* exp;
            parsedData->setFunctionType(DATEFROMTIMESTAMP);
            exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (4)].Expression), DATEFROMTIMESTAMP, NULL);
            (yyval.Expression)=exp;

        }
    break;

  case 114:

/* Line 1464 of yacc.c  */
#line 535 "dmlyacc.yxx"
    {
            Expression* exp;
            parsedData->setFunctionType(TIMEFROMTIMESTAMP);
            exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (4)].Expression), TIMEFROMTIMESTAMP, NULL);
            (yyval.Expression)=exp;
        }
    break;

  case 115:

/* Line 1464 of yacc.c  */
#line 543 "dmlyacc.yxx"
    {
           FunctionType val = *(FunctionType *)(yyvsp[(1) - (1)].FunctionType);
           (yyval.FunctionType) = &val;
        }
    break;

  case 116:

/* Line 1464 of yacc.c  */
#line 548 "dmlyacc.yxx"
    {
           FunctionType val = *(FunctionType *)(yyvsp[(1) - (1)].FunctionType);
           (yyval.FunctionType) = &val;
        }
    break;

  case 117:

/* Line 1464 of yacc.c  */
#line 554 "dmlyacc.yxx"
    { 
             FunctionType val = TIMEADDWITHHOUR;
             (yyval.FunctionType) = &val;
        }
    break;

  case 118:

/* Line 1464 of yacc.c  */
#line 559 "dmlyacc.yxx"
    {
             FunctionType val = TIMEADDWITHMIN;
             (yyval.FunctionType) = &val;
        }
    break;

  case 119:

/* Line 1464 of yacc.c  */
#line 564 "dmlyacc.yxx"
    {
             FunctionType val = TIMEADDWITHSEC;
             (yyval.FunctionType) = &val;
        }
    break;

  case 120:

/* Line 1464 of yacc.c  */
#line 570 "dmlyacc.yxx"
    {
	        FunctionType val = DATEADDWITHYEAR;
            (yyval.FunctionType) = &val;
	    }
    break;

  case 121:

/* Line 1464 of yacc.c  */
#line 575 "dmlyacc.yxx"
    {
	        FunctionType val = DATEADDWITHMON;
            (yyval.FunctionType) = &val;
        }
    break;

  case 122:

/* Line 1464 of yacc.c  */
#line 580 "dmlyacc.yxx"
    {
            FunctionType val = DATEADDWITHDAY;
            (yyval.FunctionType) = &val;
        }
    break;

  case 123:

/* Line 1464 of yacc.c  */
#line 586 "dmlyacc.yxx"
    {
            Expression* exp;
            exp=parsedData->insertExpression((char *)(yyvsp[(1) - (1)].stringval));
            free((yyvsp[(1) - (1)].stringval));
            (yyval.Expression)=exp;
        }
    break;

  case 124:

/* Line 1464 of yacc.c  */
#line 593 "dmlyacc.yxx"
    {
            Expression* exp;
            bool flag = false;
            exp=parsedData->insertExpression((char *)(yyvsp[(1) - (1)].stringval), flag);
            free((yyvsp[(1) - (1)].stringval));
            (yyval.Expression)=exp;
        }
    break;

  case 125:

/* Line 1464 of yacc.c  */
#line 601 "dmlyacc.yxx"
    {
            Expression* exp;
            exp=parsedData->insertExpression("NULL");
            free((yyvsp[(1) - (1)].stringval));
            (yyval.Expression)=exp;
        }
    break;

  case 126:

/* Line 1464 of yacc.c  */
#line 610 "dmlyacc.yxx"
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

  case 132:

/* Line 1464 of yacc.c  */
#line 631 "dmlyacc.yxx"
    {
            parsedData->setLimit(atoi((yyvsp[(2) - (2)].stringval)), 0);
        }
    break;

  case 133:

/* Line 1464 of yacc.c  */
#line 635 "dmlyacc.yxx"
    {
            parsedData->setLimit(atoi((yyvsp[(2) - (4)].stringval)), atoi((yyvsp[(4) - (4)].stringval)));
        }
    break;

  case 140:

/* Line 1464 of yacc.c  */
#line 649 "dmlyacc.yxx"
    {
            parsedData->insertGroupField((char*)(yyvsp[(1) - (1)].stringval));
            free( (yyvsp[(1) - (1)].stringval) );
        }
    break;

  case 144:

/* Line 1464 of yacc.c  */
#line 660 "dmlyacc.yxx"
    {
            parsedData->insertOrderByField((char*)(yyvsp[(1) - (1)].stringval));
            free( (yyvsp[(1) - (1)].stringval) );
        }
    break;

  case 145:

/* Line 1464 of yacc.c  */
#line 665 "dmlyacc.yxx"
    {
            parsedData->insertOrderByField((char*)(yyvsp[(1) - (2)].stringval));
            free( (yyvsp[(1) - (2)].stringval) );
        }
    break;

  case 146:

/* Line 1464 of yacc.c  */
#line 670 "dmlyacc.yxx"
    {
            parsedData->insertOrderByField((char*)(yyvsp[(1) - (2)].stringval), true);
            free( (yyvsp[(1) - (2)].stringval) );
        }
    break;

  case 147:

/* Line 1464 of yacc.c  */
#line 676 "dmlyacc.yxx"
    {
            Predicate *pred;
            pred = parsedData->insertPredicate((Predicate*) (yyvsp[(1) - (3)].predicate), OpOr, (Predicate*) (yyvsp[(3) - (3)].predicate));
            //parsedData->setCondition((Predicate*)pred);
            (yyval.predicate)= pred;

        }
    break;

  case 148:

/* Line 1464 of yacc.c  */
#line 684 "dmlyacc.yxx"
    {
            Predicate *pred;
            pred = parsedData->insertPredicate((Predicate*) (yyvsp[(1) - (3)].predicate), OpAnd, (Predicate*) (yyvsp[(3) - (3)].predicate));
            //parsedData->setCondition((Predicate*)pred);
            (yyval.predicate)= pred;
        }
    break;

  case 149:

/* Line 1464 of yacc.c  */
#line 690 "dmlyacc.yxx"
    { (yyval.predicate)=(yyvsp[(2) - (3)].predicate); }
    break;

  case 150:

/* Line 1464 of yacc.c  */
#line 692 "dmlyacc.yxx"
    {
            Predicate *pred;
            pred = parsedData->insertPredicate((Predicate*) (yyvsp[(3) - (4)].predicate), OpNot, NULL);
            //parsedData->setCondition((Predicate*)pred);
            (yyval.predicate)= pred;

        }
    break;

  case 151:

/* Line 1464 of yacc.c  */
#line 700 "dmlyacc.yxx"
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

  case 152:

/* Line 1464 of yacc.c  */
#line 716 "dmlyacc.yxx"
    {
            Predicate *pred;
            pred = parsedData->insertPredicate((Predicate*) (yyvsp[(1) - (3)].predicate), OpOr, (Predicate*) (yyvsp[(3) - (3)].predicate));
            parsedData->setHavingCondition((Predicate*)pred);
            (yyval.predicate)= pred;

        }
    break;

  case 153:

/* Line 1464 of yacc.c  */
#line 724 "dmlyacc.yxx"
    {
            Predicate *pred;
            pred = parsedData->insertPredicate((Predicate*) (yyvsp[(1) - (3)].predicate), OpAnd, (Predicate*) (yyvsp[(3) - (3)].predicate));
            parsedData->setHavingCondition((Predicate*)pred);
            (yyval.predicate)= pred;
        }
    break;

  case 154:

/* Line 1464 of yacc.c  */
#line 730 "dmlyacc.yxx"
    { (yyval.predicate)=(yyvsp[(2) - (3)].predicate); }
    break;

  case 155:

/* Line 1464 of yacc.c  */
#line 732 "dmlyacc.yxx"
    {
            Predicate *pred;
            pred = parsedData->insertPredicate((Predicate*) (yyvsp[(3) - (4)].predicate), OpNot, NULL);
            parsedData->setHavingCondition((Predicate*)pred);
            (yyval.predicate)= pred;

        }
    break;

  case 156:

/* Line 1464 of yacc.c  */
#line 740 "dmlyacc.yxx"
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

  case 157:

/* Line 1464 of yacc.c  */
#line 756 "dmlyacc.yxx"
    {
            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(5) - (6)].stringval));
            Predicate *pred;
            void **ptr = parsedData->insertCondValueAndGetPtr((char*)(yyvsp[(3) - (6)].stringval), (char*)(yyvsp[(6) - (6)].stringval), false, AGG_MIN, true);
            pred = parsedData->insertPredicate((char*) (yyvsp[(3) - (6)].stringval), op, ptr, AGG_MIN);
            free( (yyvsp[(1) - (6)].stringval) ); free ((yyvsp[(3) - (6)].stringval)); free ((yyvsp[(5) - (6)].stringval)); free ((yyvsp[(6) - (6)].stringval));
            (yyval.predicate)=pred;
        }
    break;

  case 158:

/* Line 1464 of yacc.c  */
#line 765 "dmlyacc.yxx"
    {
            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(5) - (6)].stringval));
            Predicate *pred;
            void **ptr = parsedData->insertCondValueAndGetPtr((char*)(yyvsp[(3) - (6)].stringval), (char*)(yyvsp[(6) - (6)].stringval), false, AGG_MAX, true);
            pred = parsedData->insertPredicate((char*) (yyvsp[(3) - (6)].stringval), op, ptr, AGG_MAX);
            free( (yyvsp[(1) - (6)].stringval) ); free ((yyvsp[(3) - (6)].stringval)); free ((yyvsp[(5) - (6)].stringval)); free ((yyvsp[(6) - (6)].stringval));
            (yyval.predicate)=pred;
        }
    break;

  case 159:

/* Line 1464 of yacc.c  */
#line 774 "dmlyacc.yxx"
    {
            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(5) - (6)].stringval));
            Predicate *pred;
            void **ptr = parsedData->insertCondValueAndGetPtr((char*)(yyvsp[(3) - (6)].stringval), (char*)(yyvsp[(6) - (6)].stringval), false, AGG_SUM, true);
            pred = parsedData->insertPredicate((char*) (yyvsp[(3) - (6)].stringval), op, ptr, AGG_SUM);
            free( (yyvsp[(1) - (6)].stringval) ); free ((yyvsp[(3) - (6)].stringval)); free ((yyvsp[(5) - (6)].stringval)); free ((yyvsp[(6) - (6)].stringval));
            (yyval.predicate)=pred;
        }
    break;

  case 160:

/* Line 1464 of yacc.c  */
#line 783 "dmlyacc.yxx"
    {
            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(5) - (6)].stringval));
            Predicate *pred;
            void **ptr = parsedData->insertCondValueAndGetPtr((char*)(yyvsp[(3) - (6)].stringval), (char*)(yyvsp[(6) - (6)].stringval), false, AGG_AVG, true);
            pred = parsedData->insertPredicate((char*) (yyvsp[(3) - (6)].stringval), op, ptr, AGG_AVG);
            free( (yyvsp[(1) - (6)].stringval) ); free ((yyvsp[(3) - (6)].stringval)); free ((yyvsp[(5) - (6)].stringval)); free ((yyvsp[(6) - (6)].stringval));
            (yyval.predicate)=pred;
        }
    break;

  case 161:

/* Line 1464 of yacc.c  */
#line 792 "dmlyacc.yxx"
    {
            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(5) - (6)].stringval));
            Predicate *pred;
            void **ptr = parsedData->insertCondValueAndGetPtr((char*)(yyvsp[(3) - (6)].stringval), (char*)(yyvsp[(6) - (6)].stringval), false, AGG_COUNT, true);
            pred = parsedData->insertPredicate((char*) (yyvsp[(3) - (6)].stringval), op, ptr, AGG_COUNT);
            free( (yyvsp[(1) - (6)].stringval) ); free ((yyvsp[(3) - (6)].stringval)); free ((yyvsp[(5) - (6)].stringval)); free ((yyvsp[(6) - (6)].stringval));
            (yyval.predicate)=pred;
        }
    break;

  case 162:

/* Line 1464 of yacc.c  */
#line 803 "dmlyacc.yxx"
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

  case 163:

/* Line 1464 of yacc.c  */
#line 814 "dmlyacc.yxx"
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

  case 164:

/* Line 1464 of yacc.c  */
#line 825 "dmlyacc.yxx"
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

  case 165:

/* Line 1464 of yacc.c  */
#line 841 "dmlyacc.yxx"
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

  case 166:

/* Line 1464 of yacc.c  */
#line 867 "dmlyacc.yxx"
    {
            Predicate *pred;
            parsedData->insertCondValue((char*) (yyvsp[(1) - (4)].stringval));
            pred = parsedData->insertNullPredicate((char*) (yyvsp[(1) - (4)].stringval), OpIsNull, false);
            free( (yyvsp[(1) - (4)].stringval) ); free((yyvsp[(2) - (4)].stringval)); free( (yyvsp[(3) - (4)].stringval) );
            (yyval.predicate)=pred;  
        }
    break;

  case 167:

/* Line 1464 of yacc.c  */
#line 875 "dmlyacc.yxx"
    {
            Predicate *pred;
            parsedData->insertCondValue((char*) (yyvsp[(1) - (3)].stringval));
            pred = parsedData->insertNullPredicate((char*) (yyvsp[(1) - (3)].stringval), OpIsNull, true);
            free( (yyvsp[(1) - (3)].stringval) ); free((yyvsp[(2) - (3)].stringval)); free( (yyvsp[(3) - (3)].stringval) );
            (yyval.predicate)=pred;  
        }
    break;

  case 168:

/* Line 1464 of yacc.c  */
#line 883 "dmlyacc.yxx"
    {
            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(2) - (3)].stringval));
            Predicate *pred;
            pred = parsedData->insertPredicate(((Expression*)(yyvsp[(1) - (3)].Expression)), op, ((Expression*)(yyvsp[(3) - (3)].Expression)));
            (yyval.predicate)=pred;
 
        }
    break;

  case 169:

/* Line 1464 of yacc.c  */
#line 891 "dmlyacc.yxx"
    {

            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(2) - (3)].stringval));
            parsedData->insertCondValue((char*) (yyvsp[(3) - (3)].stringval));
            Predicate *pred;
            pred = parsedData->insertPredicate(((Expression*)(yyvsp[(1) - (3)].Expression)), op, (char*) (yyvsp[(3) - (3)].stringval));
            (yyval.predicate)=pred;
            
        }
    break;

  case 170:

/* Line 1464 of yacc.c  */
#line 901 "dmlyacc.yxx"
    {
            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(2) - (3)].stringval));
            void **ptr = parsedData->insertCondValueAndGetPtr((char*)"dummy", (char*)(yyvsp[(3) - (3)].stringval), false, AGG_UNKNOWN, false, true);
            Predicate *pred;
            pred = parsedData->insertPredicate(((Expression*)(yyvsp[(1) - (3)].Expression)), op, ptr);
            (yyval.predicate)=pred;
        }
    break;

  case 171:

/* Line 1464 of yacc.c  */
#line 910 "dmlyacc.yxx"
    { (yyval.stringval)=(char*) 1;
	}
    break;

  case 172:

/* Line 1464 of yacc.c  */
#line 913 "dmlyacc.yxx"
    { (yyval.stringval)=(char*) 0; }
    break;

  case 173:

/* Line 1464 of yacc.c  */
#line 916 "dmlyacc.yxx"
    {
            parsedData->insertTableName((char*)(yyvsp[(1) - (1)].stringval));
            free( (yyvsp[(1) - (1)].stringval) );
        }
    break;

  case 174:

/* Line 1464 of yacc.c  */
#line 921 "dmlyacc.yxx"
    {
            parsedData->insertTableName((char*)(yyvsp[(1) - (3)].stringval), (char*)(yyvsp[(3) - (3)].stringval));
            free( (yyvsp[(1) - (3)].stringval) ); free((yyvsp[(3) - (3)].stringval));
        }
    break;

  case 175:

/* Line 1464 of yacc.c  */
#line 926 "dmlyacc.yxx"
    {
            parsedData->insertTableName((char*)(yyvsp[(1) - (2)].stringval), (char*)(yyvsp[(2) - (2)].stringval));
            free( (yyvsp[(1) - (2)].stringval) ); free((yyvsp[(2) - (2)].stringval));
        }
    break;

  case 176:

/* Line 1464 of yacc.c  */
#line 932 "dmlyacc.yxx"
    {
            parsedData->insertField((char*)(yyvsp[(1) - (1)].stringval));
            free( (yyvsp[(1) - (1)].stringval) );
            
        }
    break;

  case 177:

/* Line 1464 of yacc.c  */
#line 938 "dmlyacc.yxx"
    { 
            parsedData->insertField((char*)(yyvsp[(3) - (4)].stringval), AGG_MIN);
            free( (yyvsp[(1) - (4)].stringval) );
        }
    break;

  case 178:

/* Line 1464 of yacc.c  */
#line 943 "dmlyacc.yxx"
    { 
            parsedData->insertField((char*)(yyvsp[(3) - (4)].stringval), AGG_MAX);
            free( (yyvsp[(1) - (4)].stringval) );
        }
    break;

  case 179:

/* Line 1464 of yacc.c  */
#line 948 "dmlyacc.yxx"
    { 
            parsedData->insertField((char*)(yyvsp[(3) - (4)].stringval), AGG_SUM);
            free( (yyvsp[(1) - (4)].stringval) );
        }
    break;

  case 180:

/* Line 1464 of yacc.c  */
#line 953 "dmlyacc.yxx"
    { 
            parsedData->insertField((char*)(yyvsp[(3) - (4)].stringval), AGG_AVG);
            free( (yyvsp[(1) - (4)].stringval) );
        }
    break;

  case 181:

/* Line 1464 of yacc.c  */
#line 958 "dmlyacc.yxx"
    { 
            parsedData->insertField((char*)(yyvsp[(3) - (4)].stringval), AGG_COUNT);
            free( (yyvsp[(1) - (4)].stringval) );
        }
    break;

  case 182:

/* Line 1464 of yacc.c  */
#line 963 "dmlyacc.yxx"
    { 
            parsedData->insertField("*", AGG_COUNT);
            free( (yyvsp[(1) - (4)].stringval) );
        }
    break;

  case 183:

/* Line 1464 of yacc.c  */
#line 968 "dmlyacc.yxx"
    { 
            parsedData->insertField("*");
        }
    break;

  case 184:

/* Line 1464 of yacc.c  */
#line 972 "dmlyacc.yxx"
    {
            parsedData->insertField("*");
        }
    break;

  case 185:

/* Line 1464 of yacc.c  */
#line 976 "dmlyacc.yxx"
    { (yyval.stringval) = (yyvsp[(1) - (1)].stringval); }
    break;

  case 186:

/* Line 1464 of yacc.c  */
#line 977 "dmlyacc.yxx"
    { (yyval.stringval) = (yyvsp[(2) - (3)].stringval); }
    break;

  case 187:

/* Line 1464 of yacc.c  */
#line 979 "dmlyacc.yxx"
    { (yyval.stringval) = (yyvsp[(1) - (1)].stringval); }
    break;

  case 189:

/* Line 1464 of yacc.c  */
#line 981 "dmlyacc.yxx"
    { (yyval.stringval) = (yyvsp[(1) - (1)].stringval); }
    break;

  case 191:

/* Line 1464 of yacc.c  */
#line 983 "dmlyacc.yxx"
    { (yyval.stringval) = (yyvsp[(1) - (1)].stringval); }
    break;

  case 192:

/* Line 1464 of yacc.c  */
#line 984 "dmlyacc.yxx"
    { (yyval.stringval) = (char*) 0; }
    break;

  case 193:

/* Line 1464 of yacc.c  */
#line 986 "dmlyacc.yxx"
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

  case 194:

/* Line 1464 of yacc.c  */
#line 998 "dmlyacc.yxx"
    { (yyval.stringval) =  (yyvsp[(1) - (1)].stringval); }
    break;

  case 195:

/* Line 1464 of yacc.c  */
#line 1000 "dmlyacc.yxx"
    {
             char *n;
             n=(char*)malloc(30);
             strcpy(n,"-");
             strcat(n,(char*)(yyvsp[(2) - (2)].stringval));
             (yyval.stringval)=n;
             free((yyvsp[(2) - (2)].stringval));
        }
    break;

  case 196:

/* Line 1464 of yacc.c  */
#line 1008 "dmlyacc.yxx"
    { (yyval.stringval) =  (yyvsp[(2) - (2)].stringval); }
    break;

  case 197:

/* Line 1464 of yacc.c  */
#line 1010 "dmlyacc.yxx"
    { (yyval.stringval) = (yyvsp[(1) - (1)].stringval); }
    break;

  case 198:

/* Line 1464 of yacc.c  */
#line 1012 "dmlyacc.yxx"
    {
             char *d;
             d=(char*)malloc(30);
             strcpy(d,"-");
             strcat(d,(char*)(yyvsp[(2) - (2)].stringval));
             (yyval.stringval)=d;
             free((yyvsp[(2) - (2)].stringval));
        }
    break;

  case 199:

/* Line 1464 of yacc.c  */
#line 1020 "dmlyacc.yxx"
    { (yyval.stringval) = (yyvsp[(2) - (2)].stringval); }
    break;

  case 200:

/* Line 1464 of yacc.c  */
#line 1023 "dmlyacc.yxx"
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

  case 201:

/* Line 1464 of yacc.c  */
#line 1034 "dmlyacc.yxx"
    {
            parsedData->setStmtType(CacheTableStatement);
            parsedData->setUnCache(true);
            parsedData->setTableName((yyvsp[(3) - (4)].stringval)); 
        }
    break;

  case 204:

/* Line 1464 of yacc.c  */
#line 1044 "dmlyacc.yxx"
    {
            parsedData->setHCondFld(true);
            parsedData->setHCondition((char*)(yyvsp[(2) - (2)].stringval));
         }
    break;

  case 206:

/* Line 1464 of yacc.c  */
#line 1051 "dmlyacc.yxx"
    {
            parsedData->setVCondFld(true);
            parsedData->setVCondition((char*)(yyvsp[(2) - (2)].stringval));
            free((yyvsp[(2) - (2)].stringval));
         }
    break;

  case 208:

/* Line 1464 of yacc.c  */
#line 1059 "dmlyacc.yxx"
    {
            parsedData->setPkFld(true);
            parsedData->setIndexName((char*)(yyvsp[(2) - (2)].stringval));
            free((yyvsp[(2) - (2)].stringval));
         }
    break;

  case 210:

/* Line 1464 of yacc.c  */
#line 1067 "dmlyacc.yxx"
    {
            parsedData->setDirect(true);
         }
    break;

  case 212:

/* Line 1464 of yacc.c  */
#line 1073 "dmlyacc.yxx"
    {
             parsedData->setDSN(true);
             parsedData->setPKTableName((char*)(yyvsp[(2) - (2)].stringval));
             free((yyvsp[(2) - (2)].stringval));
         }
    break;

  case 214:

/* Line 1464 of yacc.c  */
#line 1080 "dmlyacc.yxx"
    {
             parsedData->setNoSchema(true);
         }
    break;

  case 215:

/* Line 1464 of yacc.c  */
#line 1085 "dmlyacc.yxx"
    {
            parsedData->setStmtType(CreateTableStatement);
            parsedData->setTableName((yyvsp[(3) - (7)].stringval)); 
            free((yyvsp[(3) - (7)].stringval));
        }
    break;

  case 216:

/* Line 1464 of yacc.c  */
#line 1091 "dmlyacc.yxx"
    {
            parsedData->setStmtType(CreateIndexStatement);
            parsedData->setIndexName((yyvsp[(3) - (12)].stringval)); 
            parsedData->setTableName((yyvsp[(5) - (12)].stringval)); 
            free((yyvsp[(3) - (12)].stringval));
            free((yyvsp[(5) - (12)].stringval));
        }
    break;

  case 217:

/* Line 1464 of yacc.c  */
#line 1099 "dmlyacc.yxx"
    {
            parsedData->setStmtType(DropTableStatement);
            parsedData->setTableName((yyvsp[(3) - (3)].stringval)); 
            free((yyvsp[(3) - (3)].stringval));
        }
    break;

  case 218:

/* Line 1464 of yacc.c  */
#line 1105 "dmlyacc.yxx"
    {
            parsedData->setStmtType(DropIndexStatement);
            parsedData->setIndexName((yyvsp[(3) - (3)].stringval)); 
            free((yyvsp[(3) - (3)].stringval));
        }
    break;

  case 219:

/* Line 1464 of yacc.c  */
#line 1111 "dmlyacc.yxx"
    {
            parsedData->setStmtType(TruncateStatement);
            parsedData->setTableName((yyvsp[(3) - (4)].stringval)); 
            free((yyvsp[(3) - (4)].stringval));
        }
    break;

  case 220:

/* Line 1464 of yacc.c  */
#line 1119 "dmlyacc.yxx"
    {
            parsedData->setIndexType(hashIndex);
        }
    break;

  case 221:

/* Line 1464 of yacc.c  */
#line 1123 "dmlyacc.yxx"
    {
            parsedData->setIndexType(treeIndex);
        }
    break;

  case 222:

/* Line 1464 of yacc.c  */
#line 1127 "dmlyacc.yxx"
    {
            parsedData->setIndexType(trieIndex);
        }
    break;

  case 223:

/* Line 1464 of yacc.c  */
#line 1131 "dmlyacc.yxx"
    {
            parsedData->setIndexType(hashIndex);
        }
    break;

  case 224:

/* Line 1464 of yacc.c  */
#line 1137 "dmlyacc.yxx"
    {
            parsedData->setUnique(true);
        }
    break;

  case 225:

/* Line 1464 of yacc.c  */
#line 1141 "dmlyacc.yxx"
    {
            parsedData->setUnique(true);
            parsedData->setPrimary(true);
        }
    break;

  case 226:

/* Line 1464 of yacc.c  */
#line 1146 "dmlyacc.yxx"
    {
            parsedData->setUnique(false);
            parsedData->setPrimary(false);
        }
    break;

  case 228:

/* Line 1464 of yacc.c  */
#line 1153 "dmlyacc.yxx"
    {
            parsedData->setBucketSize(atoi((yyvsp[(2) - (2)].stringval)));
            free((yyvsp[(2) - (2)].stringval));
        }
    break;

  case 234:

/* Line 1464 of yacc.c  */
#line 1169 "dmlyacc.yxx"
    {
            parsedData->insertFldDef();
        }
    break;

  case 236:

/* Line 1464 of yacc.c  */
#line 1178 "dmlyacc.yxx"
    {
            parsedData->setFldName((yyvsp[(1) - (1)].stringval));
            free((yyvsp[(1) - (1)].stringval));
        }
    break;

  case 238:

/* Line 1464 of yacc.c  */
#line 1184 "dmlyacc.yxx"
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

  case 240:

/* Line 1464 of yacc.c  */
#line 1197 "dmlyacc.yxx"
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

  case 242:

/* Line 1464 of yacc.c  */
#line 1210 "dmlyacc.yxx"
    {
            parsedData->setFldNotNull(true);
        }
    break;

  case 249:

/* Line 1464 of yacc.c  */
#line 1224 "dmlyacc.yxx"
    {
            parsedData->setForeign(true);
            parsedData->setPKTableName((char*)(yyvsp[(7) - (10)].stringval));
            parsedData->insertForeignKeyList();
        }
    break;

  case 253:

/* Line 1464 of yacc.c  */
#line 1236 "dmlyacc.yxx"
    {
           parsedData->insertFKField((char*)(yyvsp[(1) - (1)].stringval));
           free((yyvsp[(1) - (1)].stringval));
        }
    break;

  case 257:

/* Line 1464 of yacc.c  */
#line 1247 "dmlyacc.yxx"
    {
           parsedData->insertPKField((char*)(yyvsp[(1) - (1)].stringval));
           free((yyvsp[(1) - (1)].stringval));
        }
    break;

  case 258:

/* Line 1464 of yacc.c  */
#line 1254 "dmlyacc.yxx"
    {
           parsedData->setPrimary(true);
        }
    break;

  case 260:

/* Line 1464 of yacc.c  */
#line 1260 "dmlyacc.yxx"
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

  case 261:

/* Line 1464 of yacc.c  */
#line 1281 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeInt);
        }
    break;

  case 262:

/* Line 1464 of yacc.c  */
#line 1285 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeLong);
        }
    break;

  case 263:

/* Line 1464 of yacc.c  */
#line 1289 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeShort);
        }
    break;

  case 264:

/* Line 1464 of yacc.c  */
#line 1293 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeLongLong);
        }
    break;

  case 265:

/* Line 1464 of yacc.c  */
#line 1297 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeByteInt);
        }
    break;

  case 266:

/* Line 1464 of yacc.c  */
#line 1301 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeFloat);
        }
    break;

  case 267:

/* Line 1464 of yacc.c  */
#line 1305 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeDouble);
        }
    break;

  case 268:

/* Line 1464 of yacc.c  */
#line 1310 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeDate);
        }
    break;

  case 269:

/* Line 1464 of yacc.c  */
#line 1315 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeTime);
        }
    break;

  case 270:

/* Line 1464 of yacc.c  */
#line 1320 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeTimeStamp);
        }
    break;

  case 271:

/* Line 1464 of yacc.c  */
#line 1325 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeString);
            parsedData->setFldLength(2);
        }
    break;

  case 272:

/* Line 1464 of yacc.c  */
#line 1331 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeVarchar);
            parsedData->setFldLength(2);
        }
    break;

  case 273:

/* Line 1464 of yacc.c  */
#line 1337 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeBinary);
            parsedData->setFldLength(1);
        }
    break;



/* Line 1464 of yacc.c  */
#line 4315 "dmlyacc.cxx"
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
#line 1342 "dmlyacc.yxx"


extern int lexEof;
void yyerror(const char* Msg) { 
    if( lexEof == 0 )
        fprintf(stderr, "[Parser: %s] %s\n", Msg, yytext);

    return;
}

