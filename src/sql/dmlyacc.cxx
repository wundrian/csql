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
     FOR = 370,
     OPTION = 371,
     WITH = 372,
     RESTRICT = 373,
     CASCADE = 374,
     MIN = 375,
     MAX = 376,
     AVG = 377,
     SUM = 378,
     COUNT = 379,
     GROUP = 380,
     BY = 381,
     HAVING = 382,
     ORDER = 383,
     ASC = 384,
     DESC = 385,
     DISTINCT = 386
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
#define FOR 370
#define OPTION 371
#define WITH 372
#define RESTRICT 373
#define CASCADE 374
#define MIN 375
#define MAX 376
#define AVG 377
#define SUM 378
#define COUNT 379
#define GROUP 380
#define BY 381
#define HAVING 382
#define ORDER 383
#define ASC 384
#define DESC 385
#define DISTINCT 386




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
#line 392 "dmlyacc.cxx"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 404 "dmlyacc.cxx"

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
#define YYLAST   847

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  142
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  102
/* YYNRULES -- Number of rules.  */
#define YYNRULES  275
/* YYNRULES -- Number of states.  */
#define YYNSTATES  627

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   386

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     9,     2,     2,
     139,   140,     7,     5,   138,     6,     2,     8,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,   137,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,   141,     2,     2,     2,
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
     130,   131,   132,   133,   134,   135,   136
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    11,    13,    15,    17,
      19,    21,    23,    25,    27,    29,    31,    40,    48,    57,
      64,    74,    82,    86,    93,    98,   106,   109,   111,   114,
     116,   118,   120,   122,   125,   128,   130,   133,   135,   136,
     140,   150,   158,   174,   190,   194,   196,   199,   203,   206,
     208,   210,   212,   215,   218,   231,   234,   235,   237,   238,
     241,   243,   246,   248,   252,   255,   257,   260,   267,   275,
     280,   281,   282,   284,   285,   287,   290,   300,   301,   305,
     308,   310,   313,   316,   318,   321,   327,   334,   336,   337,
     340,   342,   345,   349,   353,   357,   361,   365,   369,   373,
     377,   381,   384,   387,   389,   391,   398,   406,   414,   421,
     429,   437,   446,   454,   462,   469,   474,   479,   481,   483,
     485,   487,   489,   491,   493,   495,   497,   499,   501,   504,
     505,   509,   510,   514,   515,   518,   523,   524,   527,   528,
     531,   533,   536,   538,   541,   543,   546,   548,   551,   554,
     558,   562,   566,   571,   574,   578,   582,   586,   591,   594,
     601,   608,   615,   622,   629,   633,   637,   644,   651,   656,
     660,   664,   668,   672,   674,   675,   677,   681,   684,   686,
     691,   696,   701,   706,   711,   716,   718,   721,   723,   727,
     729,   731,   733,   735,   737,   739,   743,   745,   748,   751,
     753,   756,   759,   765,   770,   777,   778,   781,   782,   785,
     786,   789,   790,   792,   793,   796,   797,   799,   807,   820,
     824,   828,   833,   836,   839,   842,   843,   845,   847,   848,
     849,   852,   854,   858,   861,   863,   866,   868,   875,   877,
     878,   882,   883,   886,   887,   890,   892,   894,   898,   901,
     903,   906,   917,   920,   922,   925,   927,   930,   932,   935,
     937,   944,   945,   947,   949,   951,   953,   955,   957,   959,
     961,   963,   965,   967,   969,   971
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     143,     0,    -1,   159,    -1,   170,    -1,   176,    -1,   177,
      -1,   218,    -1,   157,    -1,   210,    -1,   156,    -1,   146,
      -1,   154,    -1,   155,    -1,   145,    -1,   144,    -1,   158,
      -1,   109,    52,   206,   111,   139,   222,   140,   178,    -1,
     109,    52,   206,    62,   112,   206,   178,    -1,   109,    52,
     206,   113,   139,   225,   140,   178,    -1,   114,    52,   206,
     115,   206,   178,    -1,   109,    52,   206,   114,   112,   206,
     115,   206,   178,    -1,   109,    56,   206,   114,   115,   206,
     178,    -1,   110,    68,   178,    -1,    51,   107,   206,   108,
      11,   178,    -1,    62,   107,   206,   178,    -1,   109,   107,
     206,    49,   108,    11,   178,    -1,   147,   148,    -1,   149,
      -1,   138,   149,    -1,    27,    -1,    42,    -1,    48,    -1,
      47,    -1,   118,   119,    -1,   150,   151,    -1,   152,    -1,
     138,   152,    -1,   206,    -1,    -1,   122,   116,   121,    -1,
     116,   147,    57,   206,   115,   150,   188,   153,   178,    -1,
     117,   147,    57,   206,    28,   150,   178,    -1,    51,    52,
     206,    33,    27,   161,   162,    28,   165,   188,   189,   192,
     190,   191,   178,    -1,    42,    43,   206,    33,    27,   161,
     162,    28,   165,   188,   189,   192,   190,   191,   178,    -1,
      66,    52,   206,    -1,    18,    -1,    19,   204,    -1,    19,
      56,   204,    -1,    20,   204,    -1,    22,    -1,    24,    -1,
      23,    -1,    25,   204,    -1,    26,   204,    -1,   160,    27,
     161,   162,    28,   165,   188,   189,   192,   190,   191,   178,
      -1,    45,    46,    -1,    -1,   136,    -1,    -1,   162,   163,
      -1,   164,    -1,   138,   164,    -1,   205,    -1,   205,    33,
     206,    -1,   165,   169,    -1,   204,    -1,   204,   166,    -1,
      36,   168,   204,    57,   199,   166,    -1,    40,   167,   168,
     204,    57,   199,   166,    -1,    38,   168,   204,   166,    -1,
      -1,    -1,    37,    -1,    -1,    39,    -1,   138,   204,    -1,
      42,    43,   206,   171,    44,   139,   172,   140,   178,    -1,
      -1,   139,   162,   140,    -1,   172,   173,    -1,   207,    -1,
     138,   207,    -1,   174,   175,    -1,   207,    -1,   138,   207,
      -1,    47,    28,   206,   188,   178,    -1,    48,   206,    49,
     179,   188,   178,    -1,   137,    -1,    -1,   179,   180,    -1,
     181,    -1,   138,   181,    -1,   206,    16,   182,    -1,   206,
      16,   207,    -1,   206,    16,    50,    -1,   182,     8,   182,
      -1,   182,     9,   182,    -1,   182,     7,   182,    -1,   182,
       5,   182,    -1,   182,     6,   182,    -1,   139,   182,   140,
      -1,     6,   182,    -1,     5,   182,    -1,   183,    -1,   187,
      -1,    89,   139,   187,   138,   187,   140,    -1,    90,   139,
     187,    98,   187,   186,   140,    -1,    91,   139,   187,    98,
     187,   186,   140,    -1,    99,   139,   187,   138,   187,   140,
      -1,   100,   139,   187,    98,   187,   185,   140,    -1,   101,
     139,   187,    98,   187,   185,   140,    -1,   102,   139,   184,
     138,   187,   138,   187,   140,    -1,   103,   139,   187,    98,
     187,   184,   140,    -1,   104,   139,   187,    98,   187,   184,
     140,    -1,   105,   139,   184,    28,   187,   140,    -1,    81,
     139,   187,   140,    -1,    83,   139,   187,   140,    -1,   185,
      -1,   186,    -1,    92,    -1,    93,    -1,    94,    -1,    95,
      -1,    96,    -1,    97,    -1,   206,    -1,   207,    -1,    50,
      -1,    29,   199,    -1,    -1,   130,   131,   193,    -1,    -1,
     133,   131,   196,    -1,    -1,    34,    13,    -1,    34,    13,
      35,    13,    -1,    -1,   132,   200,    -1,    -1,   193,   194,
      -1,   195,    -1,   138,   195,    -1,   206,    -1,   196,   197,
      -1,   198,    -1,   138,   198,    -1,   206,    -1,   206,   134,
      -1,   206,   135,    -1,   199,     3,   199,    -1,   199,     4,
     199,    -1,   139,   199,   140,    -1,    32,   139,   199,   140,
      -1,   203,   202,    -1,   200,     3,   200,    -1,   200,     4,
     200,    -1,   139,   200,   140,    -1,    32,   139,   200,   140,
      -1,   203,   201,    -1,   125,   139,   206,   140,    16,   207,
      -1,   126,   139,   206,   140,    16,   207,    -1,   128,   139,
     206,   140,    16,   207,    -1,   127,   139,   206,   140,    16,
     207,    -1,   129,   139,   206,   140,    16,   207,    -1,   206,
      16,   207,    -1,   206,    16,   206,    -1,   206,   203,    30,
     207,     4,   207,    -1,   206,   203,    31,   139,   174,   140,
      -1,   206,    41,    32,    50,    -1,   206,    41,    50,    -1,
     183,    16,   183,    -1,   183,    16,   206,    -1,   183,    16,
     207,    -1,    32,    -1,    -1,   206,    -1,   206,    33,   206,
      -1,   206,   206,    -1,   206,    -1,   125,   139,   206,   140,
      -1,   126,   139,   206,   140,    -1,   128,   139,   206,   140,
      -1,   127,   139,   206,   140,    -1,   129,   139,   206,   140,
      -1,   129,   139,     7,   140,    -1,     7,    -1,   206,     7,
      -1,    12,    -1,   141,    12,   141,    -1,    11,    -1,   208,
      -1,    14,    -1,   209,    -1,    17,    -1,    50,    -1,   106,
     139,   140,    -1,    13,    -1,     6,    13,    -1,     5,    13,
      -1,    15,    -1,     6,    15,    -1,     5,    15,    -1,    68,
      52,   206,   211,   178,    -1,    74,    52,   206,   178,    -1,
     212,   213,   214,   215,   216,   217,    -1,    -1,    69,   207,
      -1,    -1,    70,   207,    -1,    -1,    71,   206,    -1,    -1,
      72,    -1,    -1,    73,   207,    -1,    -1,    75,    -1,    51,
      52,   206,   139,   222,   140,   178,    -1,    51,    56,   206,
      57,   206,   139,   162,   140,   220,   219,   221,   178,    -1,
      62,    52,   206,    -1,    62,    56,   206,    -1,    67,    52,
     206,   178,    -1,    58,   220,    -1,    59,   220,    -1,    60,
     220,    -1,    -1,    61,    -1,    53,    -1,    -1,    -1,    63,
      13,    -1,   223,    -1,   223,   138,   231,    -1,   223,   224,
      -1,   225,    -1,   138,   225,    -1,   226,    -1,   227,   243,
     228,   230,   229,   242,    -1,   206,    -1,    -1,   139,    13,
     140,    -1,    -1,    55,   207,    -1,    -1,    32,    50,    -1,
     241,    -1,   232,    -1,   241,   138,   232,    -1,   232,   233,
      -1,   234,    -1,   138,   234,    -1,    64,    54,   139,   235,
     140,    65,   206,   139,   238,   140,    -1,   235,   236,    -1,
     237,    -1,   138,   237,    -1,   206,    -1,   238,   239,    -1,
     240,    -1,   138,   240,    -1,   206,    -1,    53,    54,   139,
     162,   140,   221,    -1,    -1,    21,    -1,    76,    -1,    77,
      -1,    78,    -1,    84,    -1,    86,    -1,    85,    -1,    79,
      -1,    81,    -1,    83,    -1,    80,    -1,    82,    -1,    88,
      -1,    87,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    44,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    59,    66,    74,    80,
      89,    98,   107,   112,   119,   125,   133,   134,   136,   139,
     140,   141,   142,   143,   151,   152,   154,   156,   158,   159,
     161,   169,   176,   183,   190,   197,   202,   207,   213,   218,
     223,   228,   233,   238,   244,   250,   254,   256,   260,   262,
     263,   265,   267,   268,   274,   275,   276,   278,   292,   305,
     309,   311,   312,   314,   315,   317,   323,   331,   332,   335,
     336,   342,   349,   350,   356,   363,   371,   379,   380,   383,
     384,   387,   389,   394,   399,   405,   411,   417,   423,   429,
     435,   439,   443,   447,   448,   450,   457,   464,   472,   479,
     486,   493,   504,   511,   518,   530,   538,   546,   551,   557,
     562,   567,   573,   578,   583,   589,   596,   604,   613,   626,
     628,   629,   631,   632,   634,   638,   642,   644,   645,   647,
     648,   650,   652,   658,   659,   661,   663,   668,   673,   679,
     687,   694,   695,   703,   719,   727,   734,   735,   743,   759,
     768,   777,   786,   795,   806,   817,   828,   844,   870,   878,
     886,   894,   904,   913,   917,   919,   924,   929,   935,   941,
     946,   951,   956,   961,   966,   971,   975,   980,   981,   983,
     984,   985,   986,   987,   988,   989,  1002,  1003,  1012,  1014,
    1015,  1024,  1026,  1037,  1044,  1046,  1047,  1053,  1054,  1061,
    1062,  1069,  1070,  1075,  1076,  1082,  1083,  1088,  1094,  1102,
    1108,  1114,  1122,  1126,  1130,  1135,  1140,  1144,  1150,  1155,
    1156,  1162,  1163,  1165,  1166,  1169,  1172,  1178,  1181,  1186,
    1187,  1199,  1200,  1212,  1213,  1218,  1219,  1220,  1222,  1223,
    1225,  1227,  1234,  1235,  1237,  1239,  1245,  1246,  1248,  1250,
    1257,  1262,  1263,  1284,  1288,  1292,  1296,  1300,  1304,  1308,
    1313,  1318,  1323,  1328,  1334,  1340
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
  "REVOKE", "ALL", "PRIVILEGES", "FOR", "OPTION", "WITH", "RESTRICT",
  "CASCADE", "MIN", "MAX", "AVG", "SUM", "COUNT", "GROUP", "BY", "HAVING",
  "ORDER", "ASC", "DESC", "DISTINCT", "';'", "','", "'('", "')'", "'`'",
  "$accept", "command", "alter_statement", "management_statement",
  "user_manager_statement", "privilege_list", "privilege_list_L",
  "privilege", "grantee_list", "grantee_list_L", "grantee",
  "with_grant_opt", "grant_statement", "revoke_statement",
  "copy_table_statement", "internal_statement", "other",
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
     380,   381,   382,   383,   384,   385,   386,    59,    44,    40,
      41,    96
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   142,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   144,   144,   144,   144,
     144,   144,   145,   146,   146,   146,   147,   147,   148,   149,
     149,   149,   149,   149,   150,   150,   151,   152,   153,   153,
     154,   155,   156,   156,   157,   158,   158,   158,   158,   158,
     158,   158,   158,   158,   159,   160,   160,   161,   161,   162,
     162,   163,   164,   164,   165,   165,   165,   166,   166,   166,
     166,   167,   167,   168,   168,   169,   170,   171,   171,   172,
     172,   173,   174,   174,   175,   176,   177,   178,   178,   179,
     179,   180,   181,   181,   181,   182,   182,   182,   182,   182,
     182,   182,   182,   182,   182,   183,   183,   183,   183,   183,
     183,   183,   183,   183,   183,   183,   183,   184,   184,   185,
     185,   185,   186,   186,   186,   187,   187,   187,   188,   188,
     189,   189,   190,   190,   191,   191,   191,   192,   192,   193,
     193,   194,   195,   196,   196,   197,   198,   198,   198,   199,
     199,   199,   199,   199,   200,   200,   200,   200,   200,   201,
     201,   201,   201,   201,   202,   202,   202,   202,   202,   202,
     202,   202,   202,   203,   203,   204,   204,   204,   205,   205,
     205,   205,   205,   205,   205,   205,   205,   206,   206,   207,
     207,   207,   207,   207,   207,   207,   208,   208,   208,   209,
     209,   209,   210,   210,   211,   212,   212,   213,   213,   214,
     214,   215,   215,   216,   216,   217,   217,   218,   218,   218,
     218,   218,   219,   219,   219,   219,   220,   220,   220,   221,
     221,   222,   222,   223,   223,   224,   225,   226,   227,   228,
     228,   229,   229,   230,   230,   231,   231,   231,   232,   232,
     233,   234,   235,   235,   236,   237,   238,   238,   239,   240,
     241,   242,   242,   243,   243,   243,   243,   243,   243,   243,
     243,   243,   243,   243,   243,   243
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     8,     7,     8,     6,
       9,     7,     3,     6,     4,     7,     2,     1,     2,     1,
       1,     1,     1,     2,     2,     1,     2,     1,     0,     3,
       9,     7,    15,    15,     3,     1,     2,     3,     2,     1,
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
       3,     4,     2,     2,     2,     0,     1,     1,     0,     0,
       2,     1,     3,     2,     1,     2,     1,     6,     1,     0,
       3,     0,     2,     0,     2,     1,     1,     3,     2,     1,
       2,    10,     2,     1,     2,     1,     2,     1,     2,     1,
       6,     0,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
      56,    45,     0,     0,    49,    51,    50,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    14,    13,    10,    11,    12,
       9,     7,    15,     2,     0,     3,     4,     5,     8,     6,
     187,     0,     0,    46,   175,    48,    52,    53,     0,    55,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    88,     0,    29,    30,    32,
      31,     0,     0,    27,     0,     1,    58,    47,     0,     0,
     177,    77,   129,     0,     0,     0,     0,   219,   220,    88,
      44,    88,   205,    88,     0,     0,     0,    87,    22,     0,
      33,     0,     0,    26,     0,    57,     0,   188,   176,     0,
       0,     0,   174,    88,   129,    90,     0,     0,     0,     0,
       0,    24,   221,     0,    88,   207,   203,     0,     0,     0,
       0,     0,     0,     0,     0,    28,     0,   185,     0,     0,
       0,     0,     0,     0,    60,    62,   178,    58,     0,     0,
     173,   174,   128,     0,    85,     0,    89,    88,     0,    58,
     238,     0,   231,   234,   236,     0,     0,    88,     0,     0,
     189,   196,   191,   199,   193,   194,     0,   206,   190,   192,
     202,     0,   209,     0,     0,     0,     0,     0,     0,    88,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    59,
       0,   186,     0,    78,     0,   174,     0,   174,   174,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   153,   174,    91,    86,     0,     0,   127,     0,
      92,   103,   104,   125,   126,     0,    88,     0,   233,   263,
     264,   265,   269,   272,   270,   273,   271,   266,   268,   267,
     275,   274,   239,     0,    23,   198,   201,   197,   200,     0,
     208,     0,   211,    88,     0,     0,     0,    88,    88,    19,
     129,    35,    37,    88,     0,     0,     0,     0,     0,     0,
     129,    65,    61,    63,     0,     0,    80,     0,   151,   149,
     150,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   173,     0,     0,   196,   199,
     127,   102,   126,   196,   199,   101,     0,     0,     0,     0,
       0,     0,     0,   217,     0,     0,   235,   232,   246,   249,
     245,     0,   243,     0,   195,   210,   212,   213,    17,    88,
      88,     0,    21,    25,     0,    34,    38,    41,   179,   180,
     182,   181,   184,   183,     0,    64,   131,    73,    73,    71,
      66,     0,     0,    88,    79,   152,     0,     0,     0,     0,
       0,     0,     0,     0,   119,   120,   121,   122,   123,   124,
       0,   117,   118,     0,     0,     0,   170,   171,   172,   165,
     164,     0,   169,     0,     0,   100,    98,    99,    97,    95,
      96,     0,     0,     0,     0,   248,     0,     0,     0,   241,
     228,     0,   215,    16,    18,    88,    36,     0,    88,    75,
       0,   138,    74,     0,     0,    72,    73,   129,    81,    76,
     115,   116,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   168,     0,     0,   129,     0,     0,   250,   247,
     240,   244,     0,   261,   227,   226,   225,   214,   216,   204,
      20,     0,    40,     0,   174,   133,     0,    70,     0,   131,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    83,   131,     0,   255,     0,   253,   242,   262,
     237,   228,   228,   228,   229,    39,   130,   140,   142,   173,
     174,   137,     0,     0,   136,   174,    69,     0,   138,   105,
       0,     0,   108,     0,     0,     0,     0,     0,   114,   166,
       0,   167,    82,   138,   229,     0,     0,   252,   222,   223,
     224,     0,    88,     0,   139,   174,     0,   174,   174,     0,
       0,     0,     0,     0,   158,     0,     0,    88,    70,   174,
     133,   106,   107,   109,   110,     0,   112,   113,    84,   133,
     260,   254,     0,   230,   218,   141,     0,   156,   154,   155,
       0,     0,     0,     0,     0,   132,   144,   146,   134,    54,
      67,    70,   136,   111,   136,     0,   157,     0,     0,     0,
       0,     0,     0,   143,   147,   148,     0,    68,    88,    88,
       0,     0,     0,     0,     0,     0,   145,   135,    43,    42,
     259,     0,   257,     0,     0,     0,     0,     0,     0,   251,
     256,   159,   160,   162,   161,   163,   258
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    24,    25,    26,    27,    72,   103,    73,   270,   345,
     271,   418,    28,    29,    30,    31,    32,    33,    34,   106,
     143,   199,   144,   280,   360,   426,   423,   355,    35,   111,
     285,   364,   481,   522,    36,    37,    98,   114,   156,   115,
     230,   231,   380,   381,   382,   232,   113,   421,   504,   547,
     465,   496,   534,   497,   575,   593,   576,   152,   501,   544,
     222,   153,   281,   145,   233,   312,   178,   179,    38,   124,
     125,   182,   262,   337,   412,   459,    39,   494,   456,   532,
     161,   162,   238,   163,   164,   165,   332,   453,   409,   327,
     328,   405,   329,   486,   527,   487,   611,   620,   612,   330,
     490,   252
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -449
static const yytype_int16 yypact[] =
{
     730,  -449,    19,    35,  -449,  -449,  -449,    35,    35,    46,
      79,    86,    35,    55,    67,    77,    83,    95,   100,    68,
     118,   153,   205,   205,   238,  -449,  -449,  -449,  -449,  -449,
    -449,  -449,  -449,  -449,   215,  -449,  -449,  -449,  -449,  -449,
    -449,    35,   234,  -449,    32,  -449,  -449,  -449,    35,  -449,
      35,   212,    35,    35,    35,    35,    35,    35,    35,    35,
      35,    35,    35,    35,    35,   117,    35,  -449,  -449,  -449,
    -449,   138,    17,  -449,    26,  -449,   134,  -449,   133,    35,
    -449,    30,   261,    35,    58,   270,   216,  -449,  -449,   117,
    -449,   117,   262,   117,   162,   227,   295,  -449,  -449,   242,
    -449,    35,   205,  -449,    35,  -449,    81,  -449,  -449,   323,
      81,   324,    -9,   117,     8,  -449,   356,   354,    35,    35,
     383,  -449,  -449,   482,   117,   326,  -449,   289,   275,   279,
     307,   305,   317,    35,   311,  -449,   399,  -449,   290,   293,
     296,   297,   298,    -6,  -449,   395,   423,   134,   -53,   299,
     304,    -9,   139,   572,  -449,    35,  -449,   117,   206,   134,
    -449,   294,   308,  -449,  -449,   548,   309,   117,   267,   273,
    -449,  -449,  -449,  -449,  -449,  -449,   318,  -449,  -449,  -449,
    -449,   482,   376,    35,    35,    35,    35,    35,   447,   117,
      35,    35,    35,    35,    35,    35,     9,    35,    81,  -449,
      35,  -449,    81,  -449,   482,    -9,    14,    -9,    -9,   320,
     321,   325,   328,   330,   331,   333,   336,   337,   338,   339,
     345,   446,  -449,    80,  -449,  -449,   350,   502,    11,   606,
     313,  -449,  -449,  -449,    20,    81,   117,    31,  -449,  -449,
    -449,  -449,  -449,  -449,  -449,  -449,  -449,  -449,  -449,  -449,
    -449,  -449,   351,    81,  -449,  -449,  -449,  -449,  -449,   352,
    -449,    35,   391,   117,   358,   360,   379,   117,   117,  -449,
      49,  -449,  -449,    33,   361,   362,   363,   364,   370,   371,
      63,   203,  -449,  -449,     2,   120,  -449,    21,  -449,   461,
    -449,   365,   365,   365,   365,   365,   365,   365,   365,   291,
     365,   365,   291,   633,   468,  -449,    47,   283,  -449,  -449,
    -449,  -449,  -449,  -449,  -449,  -449,    27,   606,   606,   606,
     606,   606,    39,  -449,   451,   458,  -449,  -449,   382,  -449,
     384,   508,   493,   192,  -449,  -449,  -449,   453,  -449,   117,
     117,    35,  -449,  -449,    35,  -449,   405,  -449,  -449,  -449,
    -449,  -449,  -449,  -449,    35,  -449,   398,   490,   490,   496,
    -449,    35,   482,   117,  -449,  -449,   390,   394,   402,   443,
     444,   406,   448,   449,  -449,  -449,  -449,  -449,  -449,  -449,
     407,  -449,  -449,   450,   452,   521,  -449,  -449,  -449,  -449,
    -449,   501,  -449,   482,   414,  -449,   195,   195,  -449,  -449,
    -449,    35,   415,   416,   492,  -449,   492,   417,   509,   503,
      57,   482,   486,  -449,  -449,   117,  -449,   457,   117,  -449,
     431,   432,  -449,    35,    35,  -449,   490,    63,  -449,  -449,
    -449,  -449,   365,   365,   365,   365,   365,   365,   365,   365,
     365,   365,  -449,   559,   482,    63,    81,    35,  -449,   382,
    -449,  -449,   482,   544,  -449,  -449,   156,  -449,  -449,  -449,
    -449,   445,  -449,    35,     6,   434,   520,   203,    35,   398,
     438,   182,   182,   439,   200,   200,   442,   291,   291,   441,
     482,   208,  -449,   398,   213,  -449,   220,  -449,  -449,  -449,
    -449,    57,    57,    57,   519,  -449,   456,  -449,  -449,   460,
       6,   300,   209,   455,   553,    -9,  -449,   532,   432,  -449,
     470,   473,  -449,   474,   475,   365,   497,   500,  -449,  -449,
     482,  -449,  -449,   432,   519,    35,   530,  -449,  -449,  -449,
    -449,   583,   117,    35,  -449,     6,    23,     6,     6,   483,
     510,   512,   513,   515,  -449,    35,   584,   117,   245,    -9,
     434,  -449,  -449,  -449,  -449,   517,  -449,  -449,  -449,   434,
    -449,  -449,    35,  -449,  -449,  -449,    25,  -449,   596,  -449,
      35,    35,    35,    35,    35,   504,  -449,   255,   623,  -449,
    -449,   245,   553,  -449,   553,   525,  -449,   526,   527,   528,
     529,   538,    35,  -449,  -449,  -449,   646,  -449,   117,   117,
      35,   644,   649,   654,   663,   664,  -449,  -449,  -449,  -449,
    -449,   235,  -449,   482,   482,   482,   482,   482,    35,  -449,
    -449,  -449,  -449,  -449,  -449,  -449,  -449
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -449,  -449,  -449,  -449,  -449,   658,  -449,   580,   494,  -449,
     340,  -449,  -449,  -449,  -449,  -449,  -449,  -449,  -449,   -61,
     -97,  -449,   488,  -279,  -448,  -449,  -285,  -449,  -449,  -449,
    -449,  -449,  -449,  -449,  -449,  -449,   -23,  -449,  -449,   533,
     -90,  -144,  -298,   -77,   -55,   -29,  -102,  -356,  -444,  -191,
    -414,  -449,  -449,   157,  -449,  -449,    99,  -136,  -301,  -449,
    -449,  -209,     0,  -449,    -2,   -78,  -449,  -449,  -449,  -449,
    -449,  -449,  -449,  -449,  -449,  -449,  -449,  -449,  -193,   168,
     514,  -449,  -449,  -109,  -449,  -449,  -449,  -449,  -449,  -449,
     287,  -449,   314,  -449,  -449,   169,  -449,  -449,    82,  -449,
    -449,  -449
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -95
static const yytype_int16 yytable[] =
{
      44,    44,    43,    45,   385,    44,    44,    46,    47,   221,
      51,   -94,   157,   148,   307,   206,   278,   207,   208,   506,
     -93,    40,   197,   150,   207,   208,   537,   538,   537,   538,
     361,    40,   317,   318,   319,   320,   321,   112,   499,    44,
     -94,    77,    80,    40,    40,   177,    81,    40,    82,   -93,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,   109,    99,    79,   121,   401,   122,   287,
     126,   289,   290,   424,   101,    41,   265,   108,   112,   391,
     234,   116,   427,   104,   324,   198,   202,   203,   137,    48,
     154,   117,   112,    40,   550,   325,   304,   392,   235,   134,
     580,   180,   136,   260,   146,   284,   582,    52,   146,   559,
     454,    53,   305,   508,    50,   584,   160,   166,   455,    55,
      62,   306,   445,    56,    63,    49,   286,   523,   326,    58,
     151,   189,   198,   597,   225,    59,   311,   315,   322,   316,
     198,   468,   207,   208,   254,   500,   155,    60,   -94,   -94,
      42,   223,    61,   116,   288,   102,   333,   -93,   -93,   386,
      42,   365,    54,   567,   102,   586,   269,   395,   346,   110,
      97,   344,    42,    42,    57,    64,    42,   198,   356,   516,
     517,   263,   160,   160,   266,   267,    65,   344,   272,   272,
     274,   275,   276,   277,   279,    44,   146,   118,   283,   536,
     146,   354,   319,   320,   321,    66,   138,   139,   140,   141,
     142,   226,   227,   323,   491,   492,   493,   170,    40,   171,
     172,   173,    42,   174,   127,   388,   390,   396,   397,   398,
     399,   400,    67,   146,   566,   160,   568,   569,    75,   357,
     338,   358,    76,   359,   342,   343,    78,    68,   207,   208,
     347,   146,    69,    70,    97,   502,   228,   100,   362,   335,
     363,    83,   366,   367,   368,   369,   370,   371,   372,   373,
     105,   383,   384,   128,   107,   129,   130,   377,   378,   379,
     255,   357,   256,   358,   428,   359,   257,   209,   258,   210,
     112,   502,   374,   375,   376,   211,   212,   213,   528,   529,
     530,   387,   389,   537,   538,   214,   215,   216,   217,   218,
     219,   220,   176,   393,   394,   443,   413,   414,   317,   318,
     319,   320,   321,    71,   120,   469,   502,   119,   502,   502,
     198,   123,   410,   457,   539,   540,   541,   542,   543,   415,
     429,   131,   272,   483,   132,   229,   520,    42,   521,   484,
     147,   198,    44,   524,   419,   226,   227,   133,   525,    44,
     526,   170,    40,   308,   172,   309,   482,   174,   149,   548,
     168,   169,   158,   618,   488,   619,   170,    40,   171,   172,
     173,   159,   174,   374,   375,   376,   377,   378,   379,   594,
     595,   598,   460,   599,   167,   462,   181,   513,   514,    44,
     310,   183,   519,   470,   471,   472,   473,   474,   475,   476,
     477,   478,   479,   581,   184,   310,   510,   511,   185,   186,
     187,    44,    44,   466,   467,   188,   190,   191,   200,   192,
     201,   209,   193,   210,   236,   194,   195,   196,   204,   211,
     212,   213,   558,   205,   146,   485,   237,   261,   253,   214,
     215,   216,   217,   218,   219,   220,   176,   259,   268,   291,
     292,   498,   303,   336,   293,   208,    44,   294,   507,   295,
     296,   176,   297,   168,   169,   298,   299,   300,   301,   170,
      40,   171,   172,   173,   302,   174,   555,   168,   169,   229,
     331,    42,   334,   170,   341,   171,   172,   173,   339,   174,
     340,   348,   349,   350,   351,   402,    42,   226,   227,   564,
     352,   353,   403,   170,    40,   313,   172,   314,   175,   174,
     404,   407,   406,   485,   579,   408,   411,   417,   420,   422,
     430,   498,   175,   425,   431,   621,   622,   623,   624,   625,
     432,   433,   434,   577,   435,   438,   436,   437,   439,   441,
     440,   442,   310,   444,   446,   447,   325,   450,   452,   451,
     585,   458,   463,   480,   464,   489,   495,   503,   587,   588,
     589,   590,   591,   461,   176,   608,   609,   505,   509,   512,
     515,   518,   531,   209,    40,   210,   545,   546,   176,   549,
     577,   211,   212,   213,   533,   562,   563,   578,   610,   535,
     538,   214,   215,   216,   217,   218,   219,   220,   176,    42,
     551,   226,   227,   552,   553,   554,   610,   170,    40,   171,
     172,   173,   570,   174,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   556,   168,   169,
     557,   229,   592,    42,   170,    40,   171,   172,   173,   571,
     174,   572,   573,   209,   574,   210,   310,   583,   596,   607,
     613,   211,   212,   213,   600,   614,   601,   602,   603,   604,
     615,   214,   215,   216,   217,   218,   219,   220,   605,   616,
     617,    74,   135,   175,   416,   273,   282,   209,   224,   210,
     565,   606,   560,   449,   561,   211,   212,   213,   264,     0,
     626,     0,     0,     0,     0,   214,   215,   216,   217,   218,
     219,   220,   176,    42,   209,     0,   210,     0,   448,     0,
       0,     0,   211,   212,   213,     0,     0,     0,     0,     0,
       0,     0,   214,   215,   216,   217,   218,   219,   220,   176,
       0,     0,     0,     0,     0,   229,     0,    42,     1,     2,
       3,     0,     4,     5,     6,     7,     8,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     9,     0,    42,    10,     0,    11,    12,     0,
       0,    13,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    14,     0,     0,     0,    15,    16,    17,     0,
       0,     0,     0,     0,    18,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    19,
      20,     0,     0,     0,    21,     0,    22,    23
};

static const yytype_int16 yycheck[] =
{
       2,     3,     2,     3,   302,     7,     8,     7,     8,   153,
      12,     0,   114,   110,   223,   151,     7,     3,     4,   467,
       0,    12,    28,    32,     3,     4,     3,     4,     3,     4,
      28,    12,     5,     6,     7,     8,     9,    29,    32,    41,
      29,    41,    44,    12,    12,   123,    48,    12,    50,    29,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    33,    66,    33,    89,    28,    91,   205,
      93,   207,   208,   358,    57,    56,   185,    79,    29,    32,
     158,    83,   361,    57,    53,   138,   147,   140,     7,    43,
     113,    33,    29,    12,   508,    64,    16,    50,   159,   101,
     548,   124,   104,   181,   106,   202,   550,    52,   110,   523,
      53,    56,    32,   469,    28,   559,   118,   119,    61,    52,
      52,    41,   401,    56,    56,    46,   204,   483,   237,    52,
     139,   133,   138,   581,   157,    52,   226,   227,   235,   229,
     138,   426,     3,     4,   167,   139,   138,    52,   137,   138,
     141,   153,    52,   155,   140,   138,   253,   137,   138,   303,
     141,   140,   107,   140,   138,   140,   189,   140,   270,   139,
     137,   138,   141,   141,   107,   107,   141,   138,   280,   477,
     478,   183,   184,   185,   186,   187,    68,   138,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   139,   200,   500,
     202,   138,     7,     8,     9,    52,   125,   126,   127,   128,
     129,     5,     6,   236,    58,    59,    60,    11,    12,    13,
      14,    15,   141,    17,    62,   303,   304,   317,   318,   319,
     320,   321,    27,   235,   535,   237,   537,   538,     0,    36,
     263,    38,    27,    40,   267,   268,    12,    42,     3,     4,
     273,   253,    47,    48,   137,   464,    50,   119,   138,   261,
     140,    49,   291,   292,   293,   294,   295,   296,   297,   298,
     136,   300,   301,   111,   141,   113,   114,    95,    96,    97,
      13,    36,    15,    38,   362,    40,    13,    81,    15,    83,
      29,   500,    92,    93,    94,    89,    90,    91,   491,   492,
     493,   303,   304,     3,     4,    99,   100,   101,   102,   103,
     104,   105,   106,    30,    31,   393,   339,   340,     5,     6,
       7,     8,     9,   118,   108,   427,   535,    57,   537,   538,
     138,    69,   140,   411,   125,   126,   127,   128,   129,   341,
     363,   114,   344,   445,    49,   139,   138,   141,   140,   446,
      27,   138,   354,   140,   354,     5,     6,   115,   138,   361,
     140,    11,    12,    13,    14,    15,   444,    17,    44,   505,
       5,     6,    16,   138,   452,   140,    11,    12,    13,    14,
      15,    27,    17,    92,    93,    94,    95,    96,    97,   134,
     135,   582,   415,   584,    11,   418,    70,   474,   475,   401,
      50,   112,   480,   432,   433,   434,   435,   436,   437,   438,
     439,   440,   441,   549,   139,    50,   471,   472,   139,   112,
     115,   423,   424,   423,   424,   108,   115,    28,    33,   139,
       7,    81,   139,    83,   140,   139,   139,   139,   139,    89,
      90,    91,   520,   139,   446,   447,   138,    71,   139,    99,
     100,   101,   102,   103,   104,   105,   106,   139,    11,   139,
     139,   463,    16,    72,   139,     4,   468,   139,   468,   139,
     139,   106,   139,     5,     6,   139,   139,   139,   139,    11,
      12,    13,    14,    15,   139,    17,   515,     5,     6,   139,
     139,   141,   140,    11,   115,    13,    14,    15,   140,    17,
     140,   140,   140,   140,   140,    54,   141,     5,     6,   532,
     140,   140,    54,    11,    12,    13,    14,    15,    50,    17,
     138,    13,   138,   525,   547,    32,    73,   122,   130,    39,
     140,   533,    50,    37,   140,   613,   614,   615,   616,   617,
     138,    98,    98,   545,   138,   138,    98,    98,    98,    28,
      98,    50,    50,   139,   139,   139,    64,   140,    55,    50,
     562,    75,   131,     4,   132,    21,   121,   133,   570,   571,
     572,   573,   574,   116,   106,   598,   599,    57,   140,   140,
     138,   140,    63,    81,    12,    83,   131,    34,   106,    57,
     592,    89,    90,    91,   138,    65,    13,    13,   600,   139,
       4,    99,   100,   101,   102,   103,   104,   105,   106,   141,
     140,     5,     6,   140,   140,   140,   618,    11,    12,    13,
      14,    15,   139,    17,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,   140,     5,     6,
     140,   139,   138,   141,    11,    12,    13,    14,    15,   139,
      17,   139,   139,    81,   139,    83,    50,   140,    35,    13,
      16,    89,    90,    91,   139,    16,   140,   140,   140,   140,
      16,    99,   100,   101,   102,   103,   104,   105,   140,    16,
      16,    23,   102,    50,   344,   191,   198,    81,   155,    83,
     533,   592,   524,   406,   525,    89,    90,    91,   184,    -1,
     618,    -1,    -1,    -1,    -1,    99,   100,   101,   102,   103,
     104,   105,   106,   141,    81,    -1,    83,    -1,   404,    -1,
      -1,    -1,    89,    90,    91,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    99,   100,   101,   102,   103,   104,   105,   106,
      -1,    -1,    -1,    -1,    -1,   139,    -1,   141,    18,    19,
      20,    -1,    22,    23,    24,    25,    26,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    42,    -1,   141,    45,    -1,    47,    48,    -1,
      -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    62,    -1,    -1,    -1,    66,    67,    68,    -1,
      -1,    -1,    -1,    -1,    74,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   109,
     110,    -1,    -1,    -1,   114,    -1,   116,   117
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    18,    19,    20,    22,    23,    24,    25,    26,    42,
      45,    47,    48,    51,    62,    66,    67,    68,    74,   109,
     110,   114,   116,   117,   143,   144,   145,   146,   154,   155,
     156,   157,   158,   159,   160,   170,   176,   177,   210,   218,
      12,    56,   141,   204,   206,   204,   204,   204,    43,    46,
      28,   206,    52,    56,   107,    52,    56,   107,    52,    52,
      52,    52,    52,    56,   107,    68,    52,    27,    42,    47,
      48,   118,   147,   149,   147,     0,    27,   204,    12,    33,
     206,   206,   206,    49,   206,   206,   206,   206,   206,   206,
     206,   206,   206,   206,   206,   206,   206,   137,   178,   206,
     119,    57,   138,   148,    57,   136,   161,   141,   206,    33,
     139,   171,    29,   188,   179,   181,   206,    33,   139,    57,
     108,   178,   178,    69,   211,   212,   178,    62,   111,   113,
     114,   114,    49,   115,   206,   149,   206,     7,   125,   126,
     127,   128,   129,   162,   164,   205,   206,    27,   162,    44,
      32,   139,   199,   203,   178,   138,   180,   188,    16,    27,
     206,   222,   223,   225,   226,   227,   206,    11,     5,     6,
      11,    13,    14,    15,    17,    50,   106,   207,   208,   209,
     178,    70,   213,   112,   139,   139,   112,   115,   108,   206,
     115,    28,   139,   139,   139,   139,   139,    28,   138,   163,
      33,     7,   161,   140,   139,   139,   199,     3,     4,    81,
      83,    89,    90,    91,    99,   100,   101,   102,   103,   104,
     105,   183,   202,   206,   181,   178,     5,     6,    50,   139,
     182,   183,   187,   206,   207,   161,   140,   138,   224,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,   243,   139,   178,    13,    15,    13,    15,   139,
     207,    71,   214,   206,   222,   225,   206,   206,    11,   178,
     150,   152,   206,   150,   206,   206,   206,   206,     7,   206,
     165,   204,   164,   206,   162,   172,   207,   199,   140,   199,
     199,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,    16,    16,    32,    41,   203,    13,    15,
      50,   182,   207,    13,    15,   182,   182,     5,     6,     7,
       8,     9,   162,   178,    53,    64,   225,   231,   232,   234,
     241,   139,   228,   162,   140,   206,    72,   215,   178,   140,
     140,   115,   178,   178,   138,   151,   188,   178,   140,   140,
     140,   140,   140,   140,   138,   169,   188,    36,    38,    40,
     166,    28,   138,   140,   173,   140,   187,   187,   187,   187,
     187,   187,   187,   187,    92,    93,    94,    95,    96,    97,
     184,   185,   186,   187,   187,   184,   183,   206,   207,   206,
     207,    32,    50,    30,    31,   140,   182,   182,   182,   182,
     182,    28,    54,    54,   138,   233,   138,    13,    32,   230,
     140,    73,   216,   178,   178,   206,   152,   122,   153,   204,
     130,   189,    39,   168,   168,    37,   167,   165,   207,   178,
     140,   140,   138,    98,    98,   138,    98,    98,   138,    98,
      98,    28,    50,   207,   139,   165,   139,   139,   234,   232,
     140,    50,    55,   229,    53,    61,   220,   207,    75,   217,
     178,   116,   178,   131,   132,   192,   204,   204,   168,   188,
     187,   187,   187,   187,   187,   187,   187,   187,   187,   187,
       4,   174,   207,   188,   162,   206,   235,   237,   207,    21,
     242,    58,    59,    60,   219,   121,   193,   195,   206,    32,
     139,   200,   203,   133,   190,    57,   166,   204,   189,   140,
     186,   186,   140,   185,   185,   138,   184,   184,   140,   207,
     138,   140,   175,   189,   140,   138,   140,   236,   220,   220,
     220,    63,   221,   138,   194,   139,   200,     3,     4,   125,
     126,   127,   128,   129,   201,   131,    34,   191,   199,    57,
     192,   140,   140,   140,   140,   187,   140,   140,   207,   192,
     221,   237,    65,    13,   178,   195,   200,   140,   200,   200,
     139,   139,   139,   139,   139,   196,   198,   206,    13,   178,
     166,   199,   190,   140,   190,   206,   140,   206,   206,   206,
     206,   206,   138,   197,   134,   135,    35,   166,   191,   191,
     139,   140,   140,   140,   140,   140,   198,    13,   178,   178,
     206,   238,   240,    16,    16,    16,    16,    16,   138,   140,
     239,   207,   207,   207,   207,   207,   240
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
    { parsedData->insertGrantee((yyvsp[(1) - (1)].stringval)); free((yyvsp[(1) - (1)].stringval)); }
    break;

  case 39:

/* Line 1464 of yacc.c  */
#line 159 "dmlyacc.yxx"
    { parsedData->withGrantOption(); }
    break;

  case 40:

/* Line 1464 of yacc.c  */
#line 162 "dmlyacc.yxx"
    {
            parsedData->setStmtType(DclStatement);
            parsedData->setTableName((yyvsp[(4) - (9)].stringval));
            parsedData->constructDclNodes(GRANTACCESS);
			free((yyvsp[(4) - (9)].stringval));
    }
    break;

  case 41:

/* Line 1464 of yacc.c  */
#line 170 "dmlyacc.yxx"
    {
            parsedData->setStmtType(DclStatement);
            parsedData->setTableName((yyvsp[(4) - (7)].stringval));
            parsedData->constructDclNodes(REVOKEACCESS);
    }
    break;

  case 42:

/* Line 1464 of yacc.c  */
#line 177 "dmlyacc.yxx"
    {
            parsedData->setStmtType(CopyTableStatement);
            parsedData->setPKTableName((yyvsp[(3) - (15)].stringval));
            parsedData->setCreateTbl();
            free((yyvsp[(3) - (15)].stringval));
        }
    break;

  case 43:

/* Line 1464 of yacc.c  */
#line 184 "dmlyacc.yxx"
    {
            parsedData->setStmtType(CopyTableStatement);
            parsedData->setPKTableName((yyvsp[(3) - (15)].stringval));
            free((yyvsp[(3) - (15)].stringval));
        }
    break;

  case 44:

/* Line 1464 of yacc.c  */
#line 191 "dmlyacc.yxx"
    {
            parsedData->setStmtType(CompactTableStatement);
            parsedData->setTableName((yyvsp[(3) - (3)].stringval));
            free((yyvsp[(3) - (3)].stringval));
        }
    break;

  case 45:

/* Line 1464 of yacc.c  */
#line 198 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetTables);
	}
    break;

  case 46:

/* Line 1464 of yacc.c  */
#line 203 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetColumns);
        }
    break;

  case 47:

/* Line 1464 of yacc.c  */
#line 208 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetIndexes);
                   
        }
    break;

  case 48:

/* Line 1464 of yacc.c  */
#line 214 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetPriIndex);
        }
    break;

  case 49:

/* Line 1464 of yacc.c  */
#line 219 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetCatalogs);
        }
    break;

  case 50:

/* Line 1464 of yacc.c  */
#line 224 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetTableType);
        }
    break;

  case 51:

/* Line 1464 of yacc.c  */
#line 229 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetDataType);
        }
    break;

  case 52:

/* Line 1464 of yacc.c  */
#line 234 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetImportKey);
        }
    break;

  case 53:

/* Line 1464 of yacc.c  */
#line 239 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetExportKey);
        }
    break;

  case 54:

/* Line 1464 of yacc.c  */
#line 245 "dmlyacc.yxx"
    {
            parsedData->setStmtType(SelectStatement);
            parsedData->setCacheWorthy(true);
        }
    break;

  case 55:

/* Line 1464 of yacc.c  */
#line 251 "dmlyacc.yxx"
    {
           parsedData->setExplain();
	}
    break;

  case 57:

/* Line 1464 of yacc.c  */
#line 257 "dmlyacc.yxx"
    { 
            parsedData->setDistinct();
        }
    break;

  case 63:

/* Line 1464 of yacc.c  */
#line 269 "dmlyacc.yxx"
    {
            parsedData->insertFieldAlias((char*)(yyvsp[(3) - (3)].stringval));
            free((char*)(yyvsp[(3) - (3)].stringval));
        }
    break;

  case 67:

/* Line 1464 of yacc.c  */
#line 279 "dmlyacc.yxx"
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

  case 68:

/* Line 1464 of yacc.c  */
#line 293 "dmlyacc.yxx"
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

  case 69:

/* Line 1464 of yacc.c  */
#line 306 "dmlyacc.yxx"
    {
            parsedData->insertJoinType(INNER_JOIN);
        }
    break;

  case 75:

/* Line 1464 of yacc.c  */
#line 318 "dmlyacc.yxx"
    {
            parsedData->insertJoinType(INNER_JOIN);
        }
    break;

  case 76:

/* Line 1464 of yacc.c  */
#line 324 "dmlyacc.yxx"
    {
            parsedData->setStmtType(InsertStatement);
            parsedData->setTableName((yyvsp[(3) - (9)].stringval)); 
            free((yyvsp[(3) - (9)].stringval));
        }
    break;

  case 80:

/* Line 1464 of yacc.c  */
#line 337 "dmlyacc.yxx"
    {
            parsedData->insertValue((char*)(yyvsp[(1) - (1)].stringval));
            free((yyvsp[(1) - (1)].stringval));
        }
    break;

  case 81:

/* Line 1464 of yacc.c  */
#line 343 "dmlyacc.yxx"
    {
            parsedData->insertValue((char*)(yyvsp[(2) - (2)].stringval));
            free((yyvsp[(2) - (2)].stringval));
        }
    break;

  case 83:

/* Line 1464 of yacc.c  */
#line 351 "dmlyacc.yxx"
    {
            parsedData->insertInValue((char*)(yyvsp[(1) - (1)].stringval));
            free((yyvsp[(1) - (1)].stringval));
        }
    break;

  case 84:

/* Line 1464 of yacc.c  */
#line 357 "dmlyacc.yxx"
    {
            parsedData->insertInValue((char*)(yyvsp[(2) - (2)].stringval));
            free((yyvsp[(2) - (2)].stringval));
        }
    break;

  case 85:

/* Line 1464 of yacc.c  */
#line 364 "dmlyacc.yxx"
    {
            parsedData->setStmtType(DeleteStatement);
            parsedData->setTableName((yyvsp[(3) - (5)].stringval)); 
            free((yyvsp[(3) - (5)].stringval));
	}
    break;

  case 86:

/* Line 1464 of yacc.c  */
#line 372 "dmlyacc.yxx"
    {
            parsedData->setStmtType(UpdateStatement);
            parsedData->setTableName((yyvsp[(2) - (6)].stringval)); 
            free( (yyvsp[(2) - (6)].stringval) );
	}
    break;

  case 92:

/* Line 1464 of yacc.c  */
#line 390 "dmlyacc.yxx"
    {
           parsedData->insertUpdateExpression( (char*) (yyvsp[(1) - (3)].stringval), (Expression* ) (yyvsp[(3) - (3)].Expression));
           free( (yyvsp[(1) - (3)].stringval) ); free((yyvsp[(2) - (3)].stringval));
        }
    break;

  case 93:

/* Line 1464 of yacc.c  */
#line 395 "dmlyacc.yxx"
    { 
            parsedData->insertUpdateValue( (char*) (yyvsp[(1) - (3)].stringval), (char*) (yyvsp[(3) - (3)].stringval));
            free( (yyvsp[(1) - (3)].stringval) ); free((yyvsp[(2) - (3)].stringval));free( (yyvsp[(3) - (3)].stringval) ); 
        }
    break;

  case 94:

/* Line 1464 of yacc.c  */
#line 400 "dmlyacc.yxx"
    {
            parsedData->insertUpdateValue( (char*) (yyvsp[(1) - (3)].stringval), (char*) (yyvsp[(3) - (3)].stringval));
            free( (yyvsp[(1) - (3)].stringval) ); free((yyvsp[(2) - (3)].stringval));free( (yyvsp[(3) - (3)].stringval) );
        }
    break;

  case 95:

/* Line 1464 of yacc.c  */
#line 406 "dmlyacc.yxx"
    {
            Expression* exp;
            exp=parsedData->insertExpression((Expression *)(yyvsp[(1) - (3)].Expression), division, (Expression *)(yyvsp[(3) - (3)].Expression));
            (yyval.Expression)=exp;
        }
    break;

  case 96:

/* Line 1464 of yacc.c  */
#line 412 "dmlyacc.yxx"
    {
            Expression* exp;
            exp=parsedData->insertExpression((Expression *)(yyvsp[(1) - (3)].Expression), modulus, (Expression *)(yyvsp[(3) - (3)].Expression));
            (yyval.Expression)=exp;
        }
    break;

  case 97:

/* Line 1464 of yacc.c  */
#line 418 "dmlyacc.yxx"
    {
            Expression* exp;
            exp=parsedData->insertExpression((Expression *)(yyvsp[(1) - (3)].Expression), multiplication, (Expression *)(yyvsp[(3) - (3)].Expression));
            (yyval.Expression)=exp;
        }
    break;

  case 98:

/* Line 1464 of yacc.c  */
#line 424 "dmlyacc.yxx"
    {
            Expression* exp;
            exp=parsedData->insertExpression((Expression *)(yyvsp[(1) - (3)].Expression), addition, (Expression *)(yyvsp[(3) - (3)].Expression));
            (yyval.Expression)=exp;
        }
    break;

  case 99:

/* Line 1464 of yacc.c  */
#line 430 "dmlyacc.yxx"
    {
            Expression* exp;
            exp=parsedData->insertExpression((Expression *)(yyvsp[(1) - (3)].Expression), subtraction, (Expression *)(yyvsp[(3) - (3)].Expression));
            (yyval.Expression)=exp;
        }
    break;

  case 100:

/* Line 1464 of yacc.c  */
#line 436 "dmlyacc.yxx"
    {
            (yyval.Expression)=(yyvsp[(2) - (3)].Expression);
        }
    break;

  case 101:

/* Line 1464 of yacc.c  */
#line 440 "dmlyacc.yxx"
    {
            (yyval.Expression) = (yyvsp[(2) - (2)].Expression);
        }
    break;

  case 102:

/* Line 1464 of yacc.c  */
#line 444 "dmlyacc.yxx"
    {
            (yyval.Expression) = (yyvsp[(2) - (2)].Expression);
        }
    break;

  case 105:

/* Line 1464 of yacc.c  */
#line 451 "dmlyacc.yxx"
    {
              Expression* exp;
              parsedData->setFunctionType(DATEDIFF);
              exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (6)].Expression), DATEDIFF, (Expression *)(yyvsp[(5) - (6)].Expression));
            (yyval.Expression)=exp;
        }
    break;

  case 106:

/* Line 1464 of yacc.c  */
#line 458 "dmlyacc.yxx"
    {
	         Expression* exp;
             parsedData->setFunctionType((*(FunctionType *)(yyvsp[(6) - (7)].FunctionType)));
             exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (7)].Expression), (*(FunctionType *)(yyvsp[(6) - (7)].FunctionType)), (Expression *)(yyvsp[(5) - (7)].Expression));
             (yyval.Expression)=exp;
	    }
    break;

  case 107:

/* Line 1464 of yacc.c  */
#line 465 "dmlyacc.yxx"
    {
             Expression* exp;
             //parsedData->setFunctionType((*(FunctionType *)$6));
             parsedData->setFunctionType((FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+3));
             exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (7)].Expression), (FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+3), (Expression *)(yyvsp[(5) - (7)].Expression));
             (yyval.Expression)=exp;
        }
    break;

  case 108:

/* Line 1464 of yacc.c  */
#line 473 "dmlyacc.yxx"
    {
              Expression* exp;
              parsedData->setFunctionType(TIMEDIFF);
              exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (6)].Expression), TIMEDIFF, (Expression *)(yyvsp[(5) - (6)].Expression));
            (yyval.Expression)=exp;
        }
    break;

  case 109:

/* Line 1464 of yacc.c  */
#line 480 "dmlyacc.yxx"
    {
             Expression* exp;
             parsedData->setFunctionType((*(FunctionType *)(yyvsp[(6) - (7)].FunctionType)));
             exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (7)].Expression), (*(FunctionType *)(yyvsp[(6) - (7)].FunctionType)), (Expression *)(yyvsp[(5) - (7)].Expression));
             (yyval.Expression)=exp;
        }
    break;

  case 110:

/* Line 1464 of yacc.c  */
#line 487 "dmlyacc.yxx"
    {
             Expression* exp;
             parsedData->setFunctionType((FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+3));
             exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (7)].Expression), (FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+3), (Expression *)(yyvsp[(5) - (7)].Expression));
             (yyval.Expression)=exp;
        }
    break;

  case 111:

/* Line 1464 of yacc.c  */
#line 494 "dmlyacc.yxx"
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

  case 112:

/* Line 1464 of yacc.c  */
#line 505 "dmlyacc.yxx"
    {
             Expression* exp;
             parsedData->setFunctionType((FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+12));
             exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (7)].Expression), (FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+12), (Expression *)(yyvsp[(5) - (7)].Expression));
             (yyval.Expression)=exp;
        }
    break;

  case 113:

/* Line 1464 of yacc.c  */
#line 512 "dmlyacc.yxx"
    {
             Expression* exp;
             parsedData->setFunctionType((FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+15));
             exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (7)].Expression), (FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+15), (Expression *)(yyvsp[(5) - (7)].Expression));
             (yyval.Expression)=exp;
        }
    break;

  case 114:

/* Line 1464 of yacc.c  */
#line 519 "dmlyacc.yxx"
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

  case 115:

/* Line 1464 of yacc.c  */
#line 531 "dmlyacc.yxx"
    {
            Expression* exp;
            parsedData->setFunctionType(DATEFROMTIMESTAMP);
            exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (4)].Expression), DATEFROMTIMESTAMP, NULL);
            (yyval.Expression)=exp;

        }
    break;

  case 116:

/* Line 1464 of yacc.c  */
#line 539 "dmlyacc.yxx"
    {
            Expression* exp;
            parsedData->setFunctionType(TIMEFROMTIMESTAMP);
            exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (4)].Expression), TIMEFROMTIMESTAMP, NULL);
            (yyval.Expression)=exp;
        }
    break;

  case 117:

/* Line 1464 of yacc.c  */
#line 547 "dmlyacc.yxx"
    {
           FunctionType val = *(FunctionType *)(yyvsp[(1) - (1)].FunctionType);
           (yyval.FunctionType) = &val;
        }
    break;

  case 118:

/* Line 1464 of yacc.c  */
#line 552 "dmlyacc.yxx"
    {
           FunctionType val = *(FunctionType *)(yyvsp[(1) - (1)].FunctionType);
           (yyval.FunctionType) = &val;
        }
    break;

  case 119:

/* Line 1464 of yacc.c  */
#line 558 "dmlyacc.yxx"
    { 
             FunctionType val = TIMEADDWITHHOUR;
             (yyval.FunctionType) = &val;
        }
    break;

  case 120:

/* Line 1464 of yacc.c  */
#line 563 "dmlyacc.yxx"
    {
             FunctionType val = TIMEADDWITHMIN;
             (yyval.FunctionType) = &val;
        }
    break;

  case 121:

/* Line 1464 of yacc.c  */
#line 568 "dmlyacc.yxx"
    {
             FunctionType val = TIMEADDWITHSEC;
             (yyval.FunctionType) = &val;
        }
    break;

  case 122:

/* Line 1464 of yacc.c  */
#line 574 "dmlyacc.yxx"
    {
	        FunctionType val = DATEADDWITHYEAR;
            (yyval.FunctionType) = &val;
	    }
    break;

  case 123:

/* Line 1464 of yacc.c  */
#line 579 "dmlyacc.yxx"
    {
	        FunctionType val = DATEADDWITHMON;
            (yyval.FunctionType) = &val;
        }
    break;

  case 124:

/* Line 1464 of yacc.c  */
#line 584 "dmlyacc.yxx"
    {
            FunctionType val = DATEADDWITHDAY;
            (yyval.FunctionType) = &val;
        }
    break;

  case 125:

/* Line 1464 of yacc.c  */
#line 590 "dmlyacc.yxx"
    {
            Expression* exp;
            exp=parsedData->insertExpression((char *)(yyvsp[(1) - (1)].stringval));
            free((yyvsp[(1) - (1)].stringval));
            (yyval.Expression)=exp;
        }
    break;

  case 126:

/* Line 1464 of yacc.c  */
#line 597 "dmlyacc.yxx"
    {
            Expression* exp;
            bool flag = false;
            exp=parsedData->insertExpression((char *)(yyvsp[(1) - (1)].stringval), flag);
            free((yyvsp[(1) - (1)].stringval));
            (yyval.Expression)=exp;
        }
    break;

  case 127:

/* Line 1464 of yacc.c  */
#line 605 "dmlyacc.yxx"
    {
            Expression* exp;
            exp=parsedData->insertExpression("NULL");
            free((yyvsp[(1) - (1)].stringval));
            (yyval.Expression)=exp;
        }
    break;

  case 128:

/* Line 1464 of yacc.c  */
#line 614 "dmlyacc.yxx"
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

  case 134:

/* Line 1464 of yacc.c  */
#line 635 "dmlyacc.yxx"
    {
            parsedData->setLimit(atoi((yyvsp[(2) - (2)].stringval)), 0);
        }
    break;

  case 135:

/* Line 1464 of yacc.c  */
#line 639 "dmlyacc.yxx"
    {
            parsedData->setLimit(atoi((yyvsp[(2) - (4)].stringval)), atoi((yyvsp[(4) - (4)].stringval)));
        }
    break;

  case 142:

/* Line 1464 of yacc.c  */
#line 653 "dmlyacc.yxx"
    {
            parsedData->insertGroupField((char*)(yyvsp[(1) - (1)].stringval));
            free( (yyvsp[(1) - (1)].stringval) );
        }
    break;

  case 146:

/* Line 1464 of yacc.c  */
#line 664 "dmlyacc.yxx"
    {
            parsedData->insertOrderByField((char*)(yyvsp[(1) - (1)].stringval));
            free( (yyvsp[(1) - (1)].stringval) );
        }
    break;

  case 147:

/* Line 1464 of yacc.c  */
#line 669 "dmlyacc.yxx"
    {
            parsedData->insertOrderByField((char*)(yyvsp[(1) - (2)].stringval));
            free( (yyvsp[(1) - (2)].stringval) );
        }
    break;

  case 148:

/* Line 1464 of yacc.c  */
#line 674 "dmlyacc.yxx"
    {
            parsedData->insertOrderByField((char*)(yyvsp[(1) - (2)].stringval), true);
            free( (yyvsp[(1) - (2)].stringval) );
        }
    break;

  case 149:

/* Line 1464 of yacc.c  */
#line 680 "dmlyacc.yxx"
    {
            Predicate *pred;
            pred = parsedData->insertPredicate((Predicate*) (yyvsp[(1) - (3)].predicate), OpOr, (Predicate*) (yyvsp[(3) - (3)].predicate));
            //parsedData->setCondition((Predicate*)pred);
            (yyval.predicate)= pred;

        }
    break;

  case 150:

/* Line 1464 of yacc.c  */
#line 688 "dmlyacc.yxx"
    {
            Predicate *pred;
            pred = parsedData->insertPredicate((Predicate*) (yyvsp[(1) - (3)].predicate), OpAnd, (Predicate*) (yyvsp[(3) - (3)].predicate));
            //parsedData->setCondition((Predicate*)pred);
            (yyval.predicate)= pred;
        }
    break;

  case 151:

/* Line 1464 of yacc.c  */
#line 694 "dmlyacc.yxx"
    { (yyval.predicate)=(yyvsp[(2) - (3)].predicate); }
    break;

  case 152:

/* Line 1464 of yacc.c  */
#line 696 "dmlyacc.yxx"
    {
            Predicate *pred;
            pred = parsedData->insertPredicate((Predicate*) (yyvsp[(3) - (4)].predicate), OpNot, NULL);
            //parsedData->setCondition((Predicate*)pred);
            (yyval.predicate)= pred;

        }
    break;

  case 153:

/* Line 1464 of yacc.c  */
#line 704 "dmlyacc.yxx"
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

  case 154:

/* Line 1464 of yacc.c  */
#line 720 "dmlyacc.yxx"
    {
            Predicate *pred;
            pred = parsedData->insertPredicate((Predicate*) (yyvsp[(1) - (3)].predicate), OpOr, (Predicate*) (yyvsp[(3) - (3)].predicate));
            parsedData->setHavingCondition((Predicate*)pred);
            (yyval.predicate)= pred;

        }
    break;

  case 155:

/* Line 1464 of yacc.c  */
#line 728 "dmlyacc.yxx"
    {
            Predicate *pred;
            pred = parsedData->insertPredicate((Predicate*) (yyvsp[(1) - (3)].predicate), OpAnd, (Predicate*) (yyvsp[(3) - (3)].predicate));
            parsedData->setHavingCondition((Predicate*)pred);
            (yyval.predicate)= pred;
        }
    break;

  case 156:

/* Line 1464 of yacc.c  */
#line 734 "dmlyacc.yxx"
    { (yyval.predicate)=(yyvsp[(2) - (3)].predicate); }
    break;

  case 157:

/* Line 1464 of yacc.c  */
#line 736 "dmlyacc.yxx"
    {
            Predicate *pred;
            pred = parsedData->insertPredicate((Predicate*) (yyvsp[(3) - (4)].predicate), OpNot, NULL);
            parsedData->setHavingCondition((Predicate*)pred);
            (yyval.predicate)= pred;

        }
    break;

  case 158:

/* Line 1464 of yacc.c  */
#line 744 "dmlyacc.yxx"
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

  case 159:

/* Line 1464 of yacc.c  */
#line 760 "dmlyacc.yxx"
    {
            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(5) - (6)].stringval));
            Predicate *pred;
            void **ptr = parsedData->insertCondValueAndGetPtr((char*)(yyvsp[(3) - (6)].stringval), (char*)(yyvsp[(6) - (6)].stringval), false, AGG_MIN, true);
            pred = parsedData->insertPredicate((char*) (yyvsp[(3) - (6)].stringval), op, ptr, AGG_MIN);
            free( (yyvsp[(1) - (6)].stringval) ); free ((yyvsp[(3) - (6)].stringval)); free ((yyvsp[(5) - (6)].stringval)); free ((yyvsp[(6) - (6)].stringval));
            (yyval.predicate)=pred;
        }
    break;

  case 160:

/* Line 1464 of yacc.c  */
#line 769 "dmlyacc.yxx"
    {
            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(5) - (6)].stringval));
            Predicate *pred;
            void **ptr = parsedData->insertCondValueAndGetPtr((char*)(yyvsp[(3) - (6)].stringval), (char*)(yyvsp[(6) - (6)].stringval), false, AGG_MAX, true);
            pred = parsedData->insertPredicate((char*) (yyvsp[(3) - (6)].stringval), op, ptr, AGG_MAX);
            free( (yyvsp[(1) - (6)].stringval) ); free ((yyvsp[(3) - (6)].stringval)); free ((yyvsp[(5) - (6)].stringval)); free ((yyvsp[(6) - (6)].stringval));
            (yyval.predicate)=pred;
        }
    break;

  case 161:

/* Line 1464 of yacc.c  */
#line 778 "dmlyacc.yxx"
    {
            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(5) - (6)].stringval));
            Predicate *pred;
            void **ptr = parsedData->insertCondValueAndGetPtr((char*)(yyvsp[(3) - (6)].stringval), (char*)(yyvsp[(6) - (6)].stringval), false, AGG_SUM, true);
            pred = parsedData->insertPredicate((char*) (yyvsp[(3) - (6)].stringval), op, ptr, AGG_SUM);
            free( (yyvsp[(1) - (6)].stringval) ); free ((yyvsp[(3) - (6)].stringval)); free ((yyvsp[(5) - (6)].stringval)); free ((yyvsp[(6) - (6)].stringval));
            (yyval.predicate)=pred;
        }
    break;

  case 162:

/* Line 1464 of yacc.c  */
#line 787 "dmlyacc.yxx"
    {
            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(5) - (6)].stringval));
            Predicate *pred;
            void **ptr = parsedData->insertCondValueAndGetPtr((char*)(yyvsp[(3) - (6)].stringval), (char*)(yyvsp[(6) - (6)].stringval), false, AGG_AVG, true);
            pred = parsedData->insertPredicate((char*) (yyvsp[(3) - (6)].stringval), op, ptr, AGG_AVG);
            free( (yyvsp[(1) - (6)].stringval) ); free ((yyvsp[(3) - (6)].stringval)); free ((yyvsp[(5) - (6)].stringval)); free ((yyvsp[(6) - (6)].stringval));
            (yyval.predicate)=pred;
        }
    break;

  case 163:

/* Line 1464 of yacc.c  */
#line 796 "dmlyacc.yxx"
    {
            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(5) - (6)].stringval));
            Predicate *pred;
            void **ptr = parsedData->insertCondValueAndGetPtr((char*)(yyvsp[(3) - (6)].stringval), (char*)(yyvsp[(6) - (6)].stringval), false, AGG_COUNT, true);
            pred = parsedData->insertPredicate((char*) (yyvsp[(3) - (6)].stringval), op, ptr, AGG_COUNT);
            free( (yyvsp[(1) - (6)].stringval) ); free ((yyvsp[(3) - (6)].stringval)); free ((yyvsp[(5) - (6)].stringval)); free ((yyvsp[(6) - (6)].stringval));
            (yyval.predicate)=pred;
        }
    break;

  case 164:

/* Line 1464 of yacc.c  */
#line 807 "dmlyacc.yxx"
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

  case 165:

/* Line 1464 of yacc.c  */
#line 818 "dmlyacc.yxx"
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

  case 166:

/* Line 1464 of yacc.c  */
#line 829 "dmlyacc.yxx"
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

  case 167:

/* Line 1464 of yacc.c  */
#line 845 "dmlyacc.yxx"
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

  case 168:

/* Line 1464 of yacc.c  */
#line 871 "dmlyacc.yxx"
    {
            Predicate *pred;
            parsedData->insertCondValue((char*) (yyvsp[(1) - (4)].stringval));
            pred = parsedData->insertNullPredicate((char*) (yyvsp[(1) - (4)].stringval), OpIsNull, false);
            free( (yyvsp[(1) - (4)].stringval) ); free((yyvsp[(2) - (4)].stringval)); free( (yyvsp[(3) - (4)].stringval) );
            (yyval.predicate)=pred;  
        }
    break;

  case 169:

/* Line 1464 of yacc.c  */
#line 879 "dmlyacc.yxx"
    {
            Predicate *pred;
            parsedData->insertCondValue((char*) (yyvsp[(1) - (3)].stringval));
            pred = parsedData->insertNullPredicate((char*) (yyvsp[(1) - (3)].stringval), OpIsNull, true);
            free( (yyvsp[(1) - (3)].stringval) ); free((yyvsp[(2) - (3)].stringval)); free( (yyvsp[(3) - (3)].stringval) );
            (yyval.predicate)=pred;  
        }
    break;

  case 170:

/* Line 1464 of yacc.c  */
#line 887 "dmlyacc.yxx"
    {
            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(2) - (3)].stringval));
            Predicate *pred;
            pred = parsedData->insertPredicate(((Expression*)(yyvsp[(1) - (3)].Expression)), op, ((Expression*)(yyvsp[(3) - (3)].Expression)));
            (yyval.predicate)=pred;
 
        }
    break;

  case 171:

/* Line 1464 of yacc.c  */
#line 895 "dmlyacc.yxx"
    {

            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(2) - (3)].stringval));
            parsedData->insertCondValue((char*) (yyvsp[(3) - (3)].stringval));
            Predicate *pred;
            pred = parsedData->insertPredicate(((Expression*)(yyvsp[(1) - (3)].Expression)), op, (char*) (yyvsp[(3) - (3)].stringval));
            (yyval.predicate)=pred;
            
        }
    break;

  case 172:

/* Line 1464 of yacc.c  */
#line 905 "dmlyacc.yxx"
    {
            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(2) - (3)].stringval));
            void **ptr = parsedData->insertCondValueAndGetPtr((char*)"dummy", (char*)(yyvsp[(3) - (3)].stringval), false, AGG_UNKNOWN, false, true);
            Predicate *pred;
            pred = parsedData->insertPredicate(((Expression*)(yyvsp[(1) - (3)].Expression)), op, ptr);
            (yyval.predicate)=pred;
        }
    break;

  case 173:

/* Line 1464 of yacc.c  */
#line 914 "dmlyacc.yxx"
    { (yyval.stringval)=(char*) 1;
	}
    break;

  case 174:

/* Line 1464 of yacc.c  */
#line 917 "dmlyacc.yxx"
    { (yyval.stringval)=(char*) 0; }
    break;

  case 175:

/* Line 1464 of yacc.c  */
#line 920 "dmlyacc.yxx"
    {
            parsedData->insertTableName((char*)(yyvsp[(1) - (1)].stringval));
            free( (yyvsp[(1) - (1)].stringval) );
        }
    break;

  case 176:

/* Line 1464 of yacc.c  */
#line 925 "dmlyacc.yxx"
    {
            parsedData->insertTableName((char*)(yyvsp[(1) - (3)].stringval), (char*)(yyvsp[(3) - (3)].stringval));
            free( (yyvsp[(1) - (3)].stringval) ); free((yyvsp[(3) - (3)].stringval));
        }
    break;

  case 177:

/* Line 1464 of yacc.c  */
#line 930 "dmlyacc.yxx"
    {
            parsedData->insertTableName((char*)(yyvsp[(1) - (2)].stringval), (char*)(yyvsp[(2) - (2)].stringval));
            free( (yyvsp[(1) - (2)].stringval) ); free((yyvsp[(2) - (2)].stringval));
        }
    break;

  case 178:

/* Line 1464 of yacc.c  */
#line 936 "dmlyacc.yxx"
    {
            parsedData->insertField((char*)(yyvsp[(1) - (1)].stringval));
            free( (yyvsp[(1) - (1)].stringval) );
            
        }
    break;

  case 179:

/* Line 1464 of yacc.c  */
#line 942 "dmlyacc.yxx"
    { 
            parsedData->insertField((char*)(yyvsp[(3) - (4)].stringval), AGG_MIN);
            free( (yyvsp[(1) - (4)].stringval) );
        }
    break;

  case 180:

/* Line 1464 of yacc.c  */
#line 947 "dmlyacc.yxx"
    { 
            parsedData->insertField((char*)(yyvsp[(3) - (4)].stringval), AGG_MAX);
            free( (yyvsp[(1) - (4)].stringval) );
        }
    break;

  case 181:

/* Line 1464 of yacc.c  */
#line 952 "dmlyacc.yxx"
    { 
            parsedData->insertField((char*)(yyvsp[(3) - (4)].stringval), AGG_SUM);
            free( (yyvsp[(1) - (4)].stringval) );
        }
    break;

  case 182:

/* Line 1464 of yacc.c  */
#line 957 "dmlyacc.yxx"
    { 
            parsedData->insertField((char*)(yyvsp[(3) - (4)].stringval), AGG_AVG);
            free( (yyvsp[(1) - (4)].stringval) );
        }
    break;

  case 183:

/* Line 1464 of yacc.c  */
#line 962 "dmlyacc.yxx"
    { 
            parsedData->insertField((char*)(yyvsp[(3) - (4)].stringval), AGG_COUNT);
            free( (yyvsp[(1) - (4)].stringval) );
        }
    break;

  case 184:

/* Line 1464 of yacc.c  */
#line 967 "dmlyacc.yxx"
    { 
            parsedData->insertField("*", AGG_COUNT);
            free( (yyvsp[(1) - (4)].stringval) );
        }
    break;

  case 185:

/* Line 1464 of yacc.c  */
#line 972 "dmlyacc.yxx"
    { 
            parsedData->insertField("*");
        }
    break;

  case 186:

/* Line 1464 of yacc.c  */
#line 976 "dmlyacc.yxx"
    {
            parsedData->insertField("*");
        }
    break;

  case 187:

/* Line 1464 of yacc.c  */
#line 980 "dmlyacc.yxx"
    { (yyval.stringval) = (yyvsp[(1) - (1)].stringval); }
    break;

  case 188:

/* Line 1464 of yacc.c  */
#line 981 "dmlyacc.yxx"
    { (yyval.stringval) = (yyvsp[(2) - (3)].stringval); }
    break;

  case 189:

/* Line 1464 of yacc.c  */
#line 983 "dmlyacc.yxx"
    { (yyval.stringval) = (yyvsp[(1) - (1)].stringval); }
    break;

  case 191:

/* Line 1464 of yacc.c  */
#line 985 "dmlyacc.yxx"
    { (yyval.stringval) = (yyvsp[(1) - (1)].stringval); }
    break;

  case 193:

/* Line 1464 of yacc.c  */
#line 987 "dmlyacc.yxx"
    { (yyval.stringval) = (yyvsp[(1) - (1)].stringval); }
    break;

  case 194:

/* Line 1464 of yacc.c  */
#line 988 "dmlyacc.yxx"
    { (yyval.stringval) = (char*) 0; }
    break;

  case 195:

/* Line 1464 of yacc.c  */
#line 990 "dmlyacc.yxx"
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

  case 196:

/* Line 1464 of yacc.c  */
#line 1002 "dmlyacc.yxx"
    { (yyval.stringval) =  (yyvsp[(1) - (1)].stringval); }
    break;

  case 197:

/* Line 1464 of yacc.c  */
#line 1004 "dmlyacc.yxx"
    {
             char *n;
             n=(char*)malloc(30);
             strcpy(n,"-");
             strcat(n,(char*)(yyvsp[(2) - (2)].stringval));
             (yyval.stringval)=n;
             free((yyvsp[(2) - (2)].stringval));
        }
    break;

  case 198:

/* Line 1464 of yacc.c  */
#line 1012 "dmlyacc.yxx"
    { (yyval.stringval) =  (yyvsp[(2) - (2)].stringval); }
    break;

  case 199:

/* Line 1464 of yacc.c  */
#line 1014 "dmlyacc.yxx"
    { (yyval.stringval) = (yyvsp[(1) - (1)].stringval); }
    break;

  case 200:

/* Line 1464 of yacc.c  */
#line 1016 "dmlyacc.yxx"
    {
             char *d;
             d=(char*)malloc(30);
             strcpy(d,"-");
             strcat(d,(char*)(yyvsp[(2) - (2)].stringval));
             (yyval.stringval)=d;
             free((yyvsp[(2) - (2)].stringval));
        }
    break;

  case 201:

/* Line 1464 of yacc.c  */
#line 1024 "dmlyacc.yxx"
    { (yyval.stringval) = (yyvsp[(2) - (2)].stringval); }
    break;

  case 202:

/* Line 1464 of yacc.c  */
#line 1027 "dmlyacc.yxx"
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

  case 203:

/* Line 1464 of yacc.c  */
#line 1038 "dmlyacc.yxx"
    {
            parsedData->setStmtType(CacheTableStatement);
            parsedData->setUnCache(true);
            parsedData->setTableName((yyvsp[(3) - (4)].stringval)); 
        }
    break;

  case 206:

/* Line 1464 of yacc.c  */
#line 1048 "dmlyacc.yxx"
    {
            parsedData->setHCondFld(true);
            parsedData->setHCondition((char*)(yyvsp[(2) - (2)].stringval));
         }
    break;

  case 208:

/* Line 1464 of yacc.c  */
#line 1055 "dmlyacc.yxx"
    {
            parsedData->setVCondFld(true);
            parsedData->setVCondition((char*)(yyvsp[(2) - (2)].stringval));
            free((yyvsp[(2) - (2)].stringval));
         }
    break;

  case 210:

/* Line 1464 of yacc.c  */
#line 1063 "dmlyacc.yxx"
    {
            parsedData->setPkFld(true);
            parsedData->setIndexName((char*)(yyvsp[(2) - (2)].stringval));
            free((yyvsp[(2) - (2)].stringval));
         }
    break;

  case 212:

/* Line 1464 of yacc.c  */
#line 1071 "dmlyacc.yxx"
    {
            parsedData->setDirect(true);
         }
    break;

  case 214:

/* Line 1464 of yacc.c  */
#line 1077 "dmlyacc.yxx"
    {
             parsedData->setDSN(true);
             parsedData->setPKTableName((char*)(yyvsp[(2) - (2)].stringval));
             free((yyvsp[(2) - (2)].stringval));
         }
    break;

  case 216:

/* Line 1464 of yacc.c  */
#line 1084 "dmlyacc.yxx"
    {
             parsedData->setNoSchema(true);
         }
    break;

  case 217:

/* Line 1464 of yacc.c  */
#line 1089 "dmlyacc.yxx"
    {
            parsedData->setStmtType(CreateTableStatement);
            parsedData->setTableName((yyvsp[(3) - (7)].stringval)); 
            free((yyvsp[(3) - (7)].stringval));
        }
    break;

  case 218:

/* Line 1464 of yacc.c  */
#line 1095 "dmlyacc.yxx"
    {
            parsedData->setStmtType(CreateIndexStatement);
            parsedData->setIndexName((yyvsp[(3) - (12)].stringval)); 
            parsedData->setTableName((yyvsp[(5) - (12)].stringval)); 
            free((yyvsp[(3) - (12)].stringval));
            free((yyvsp[(5) - (12)].stringval));
        }
    break;

  case 219:

/* Line 1464 of yacc.c  */
#line 1103 "dmlyacc.yxx"
    {
            parsedData->setStmtType(DropTableStatement);
            parsedData->setTableName((yyvsp[(3) - (3)].stringval)); 
            free((yyvsp[(3) - (3)].stringval));
        }
    break;

  case 220:

/* Line 1464 of yacc.c  */
#line 1109 "dmlyacc.yxx"
    {
            parsedData->setStmtType(DropIndexStatement);
            parsedData->setIndexName((yyvsp[(3) - (3)].stringval)); 
            free((yyvsp[(3) - (3)].stringval));
        }
    break;

  case 221:

/* Line 1464 of yacc.c  */
#line 1115 "dmlyacc.yxx"
    {
            parsedData->setStmtType(TruncateStatement);
            parsedData->setTableName((yyvsp[(3) - (4)].stringval)); 
            free((yyvsp[(3) - (4)].stringval));
        }
    break;

  case 222:

/* Line 1464 of yacc.c  */
#line 1123 "dmlyacc.yxx"
    {
            parsedData->setIndexType(hashIndex);
        }
    break;

  case 223:

/* Line 1464 of yacc.c  */
#line 1127 "dmlyacc.yxx"
    {
            parsedData->setIndexType(treeIndex);
        }
    break;

  case 224:

/* Line 1464 of yacc.c  */
#line 1131 "dmlyacc.yxx"
    {
            parsedData->setIndexType(trieIndex);
        }
    break;

  case 225:

/* Line 1464 of yacc.c  */
#line 1135 "dmlyacc.yxx"
    {
            parsedData->setIndexType(hashIndex);
        }
    break;

  case 226:

/* Line 1464 of yacc.c  */
#line 1141 "dmlyacc.yxx"
    {
            parsedData->setUnique(true);
        }
    break;

  case 227:

/* Line 1464 of yacc.c  */
#line 1145 "dmlyacc.yxx"
    {
            parsedData->setUnique(true);
            parsedData->setPrimary(true);
        }
    break;

  case 228:

/* Line 1464 of yacc.c  */
#line 1150 "dmlyacc.yxx"
    {
            parsedData->setUnique(false);
            parsedData->setPrimary(false);
        }
    break;

  case 230:

/* Line 1464 of yacc.c  */
#line 1157 "dmlyacc.yxx"
    {
            parsedData->setBucketSize(atoi((yyvsp[(2) - (2)].stringval)));
            free((yyvsp[(2) - (2)].stringval));
        }
    break;

  case 236:

/* Line 1464 of yacc.c  */
#line 1173 "dmlyacc.yxx"
    {
            parsedData->insertFldDef();
        }
    break;

  case 238:

/* Line 1464 of yacc.c  */
#line 1182 "dmlyacc.yxx"
    {
            parsedData->setFldName((yyvsp[(1) - (1)].stringval));
            free((yyvsp[(1) - (1)].stringval));
        }
    break;

  case 240:

/* Line 1464 of yacc.c  */
#line 1188 "dmlyacc.yxx"
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

  case 242:

/* Line 1464 of yacc.c  */
#line 1201 "dmlyacc.yxx"
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

  case 244:

/* Line 1464 of yacc.c  */
#line 1214 "dmlyacc.yxx"
    {
            parsedData->setFldNotNull(true);
        }
    break;

  case 251:

/* Line 1464 of yacc.c  */
#line 1228 "dmlyacc.yxx"
    {
            parsedData->setForeign(true);
            parsedData->setPKTableName((char*)(yyvsp[(7) - (10)].stringval));
            parsedData->insertForeignKeyList();
        }
    break;

  case 255:

/* Line 1464 of yacc.c  */
#line 1240 "dmlyacc.yxx"
    {
           parsedData->insertFKField((char*)(yyvsp[(1) - (1)].stringval));
           free((yyvsp[(1) - (1)].stringval));
        }
    break;

  case 259:

/* Line 1464 of yacc.c  */
#line 1251 "dmlyacc.yxx"
    {
           parsedData->insertPKField((char*)(yyvsp[(1) - (1)].stringval));
           free((yyvsp[(1) - (1)].stringval));
        }
    break;

  case 260:

/* Line 1464 of yacc.c  */
#line 1258 "dmlyacc.yxx"
    {
           parsedData->setPrimary(true);
        }
    break;

  case 262:

/* Line 1464 of yacc.c  */
#line 1264 "dmlyacc.yxx"
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

  case 263:

/* Line 1464 of yacc.c  */
#line 1285 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeInt);
        }
    break;

  case 264:

/* Line 1464 of yacc.c  */
#line 1289 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeLong);
        }
    break;

  case 265:

/* Line 1464 of yacc.c  */
#line 1293 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeShort);
        }
    break;

  case 266:

/* Line 1464 of yacc.c  */
#line 1297 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeLongLong);
        }
    break;

  case 267:

/* Line 1464 of yacc.c  */
#line 1301 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeByteInt);
        }
    break;

  case 268:

/* Line 1464 of yacc.c  */
#line 1305 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeFloat);
        }
    break;

  case 269:

/* Line 1464 of yacc.c  */
#line 1309 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeDouble);
        }
    break;

  case 270:

/* Line 1464 of yacc.c  */
#line 1314 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeDate);
        }
    break;

  case 271:

/* Line 1464 of yacc.c  */
#line 1319 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeTime);
        }
    break;

  case 272:

/* Line 1464 of yacc.c  */
#line 1324 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeTimeStamp);
        }
    break;

  case 273:

/* Line 1464 of yacc.c  */
#line 1329 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeString);
            parsedData->setFldLength(2);
        }
    break;

  case 274:

/* Line 1464 of yacc.c  */
#line 1335 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeVarchar);
            parsedData->setFldLength(2);
        }
    break;

  case 275:

/* Line 1464 of yacc.c  */
#line 1341 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeBinary);
            parsedData->setFldLength(1);
        }
    break;



/* Line 1464 of yacc.c  */
#line 4349 "dmlyacc.cxx"
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
#line 1346 "dmlyacc.yxx"


extern int lexEof;
void yyerror(const char* Msg) { 
    if( lexEof == 0 )
        fprintf(stderr, "[Parser: %s] %s\n", Msg, yytext);

    return;
}

