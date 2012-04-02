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
     MIN = 366,
     MAX = 367,
     AVG = 368,
     SUM = 369,
     COUNT = 370,
     GROUP = 371,
     BY = 372,
     HAVING = 373,
     ORDER = 374,
     ASC = 375,
     DESC = 376,
     DISTINCT = 377
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
#define MIN 366
#define MAX 367
#define AVG 368
#define SUM 369
#define COUNT 370
#define GROUP 371
#define BY 372
#define HAVING 373
#define ORDER 374
#define ASC 375
#define DESC 376
#define DISTINCT 377




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
#line 374 "dmlyacc.cxx"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 386 "dmlyacc.cxx"

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
#define YYFINAL  63
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   805

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  133
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  93
/* YYNRULES -- Number of rules.  */
#define YYNRULES  259
/* YYNRULES -- Number of states.  */
#define YYNSTATES  591

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   377

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     9,     2,     2,
     130,   131,     7,     5,   129,     6,     2,     8,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,   128,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,   132,     2,     2,     2,
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
     120,   121,   122,   123,   124,   125,   126,   127
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    11,    13,    15,    17,
      19,    21,    23,    25,    27,    36,    44,    53,    60,    70,
      78,    82,    89,    94,   102,   118,   134,   138,   140,   143,
     147,   150,   152,   154,   156,   159,   162,   175,   178,   179,
     181,   182,   185,   187,   190,   192,   196,   199,   201,   204,
     211,   219,   224,   225,   226,   228,   229,   231,   234,   244,
     245,   249,   252,   254,   257,   260,   262,   265,   271,   278,
     280,   281,   284,   286,   289,   293,   297,   301,   305,   309,
     313,   317,   321,   325,   328,   331,   333,   335,   342,   350,
     358,   365,   373,   381,   390,   398,   406,   413,   418,   423,
     425,   427,   429,   431,   433,   435,   437,   439,   441,   443,
     445,   448,   449,   453,   454,   458,   459,   462,   467,   468,
     471,   472,   475,   477,   480,   482,   485,   487,   490,   492,
     495,   498,   502,   506,   510,   515,   518,   522,   526,   530,
     535,   538,   545,   552,   559,   566,   573,   577,   581,   588,
     595,   600,   604,   608,   612,   616,   618,   619,   621,   625,
     628,   630,   635,   640,   645,   650,   655,   660,   662,   665,
     667,   671,   673,   675,   677,   679,   681,   683,   687,   689,
     692,   695,   697,   700,   703,   709,   714,   721,   722,   725,
     726,   729,   730,   733,   734,   736,   737,   740,   741,   743,
     751,   764,   768,   772,   777,   778,   781,   784,   787,   788,
     789,   791,   793,   794,   795,   798,   800,   804,   807,   809,
     812,   814,   821,   823,   824,   828,   829,   832,   833,   836,
     838,   840,   844,   847,   849,   852,   863,   866,   868,   871,
     873,   876,   878,   881,   883,   890,   891,   893,   895,   897,
     899,   901,   903,   905,   907,   909,   911,   913,   915,   917
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     134,     0,    -1,   141,    -1,   152,    -1,   158,    -1,   159,
      -1,   200,    -1,   139,    -1,   192,    -1,   138,    -1,   137,
      -1,   136,    -1,   135,    -1,   140,    -1,   109,    52,   188,
     111,   130,   204,   131,   160,    -1,   109,    52,   188,    62,
     112,   188,   160,    -1,   109,    52,   188,   113,   130,   207,
     131,   160,    -1,   114,    52,   188,   115,   188,   160,    -1,
     109,    52,   188,   114,   112,   188,   115,   188,   160,    -1,
     109,    56,   188,   114,   115,   188,   160,    -1,   110,    68,
     160,    -1,    51,   107,   188,   108,    11,   160,    -1,    62,
     107,   188,   160,    -1,   109,   107,   188,    49,   108,    11,
     160,    -1,    51,    52,   188,    33,    27,   143,   144,    28,
     147,   170,   171,   174,   172,   173,   160,    -1,    42,    43,
     188,    33,    27,   143,   144,    28,   147,   170,   171,   174,
     172,   173,   160,    -1,    66,    52,   188,    -1,    18,    -1,
      19,   186,    -1,    19,    56,   186,    -1,    20,   186,    -1,
      22,    -1,    24,    -1,    23,    -1,    25,   186,    -1,    26,
     186,    -1,   142,    27,   143,   144,    28,   147,   170,   171,
     174,   172,   173,   160,    -1,    45,    46,    -1,    -1,   127,
      -1,    -1,   144,   145,    -1,   146,    -1,   129,   146,    -1,
     187,    -1,   187,    33,   188,    -1,   147,   151,    -1,   186,
      -1,   186,   148,    -1,    36,   150,   186,    57,   181,   148,
      -1,    40,   149,   150,   186,    57,   181,   148,    -1,    38,
     150,   186,   148,    -1,    -1,    -1,    37,    -1,    -1,    39,
      -1,   129,   186,    -1,    42,    43,   188,   153,    44,   130,
     154,   131,   160,    -1,    -1,   130,   144,   131,    -1,   154,
     155,    -1,   189,    -1,   129,   189,    -1,   156,   157,    -1,
     189,    -1,   129,   189,    -1,    47,    28,   188,   170,   160,
      -1,    48,   188,    49,   161,   170,   160,    -1,   128,    -1,
      -1,   161,   162,    -1,   163,    -1,   129,   163,    -1,   188,
      16,   164,    -1,   188,    16,   189,    -1,   188,    16,    50,
      -1,   164,     8,   164,    -1,   164,     9,   164,    -1,   164,
       7,   164,    -1,   164,     5,   164,    -1,   164,     6,   164,
      -1,   130,   164,   131,    -1,     6,   164,    -1,     5,   164,
      -1,   165,    -1,   169,    -1,    89,   130,   169,   129,   169,
     131,    -1,    90,   130,   169,    98,   169,   168,   131,    -1,
      91,   130,   169,    98,   169,   168,   131,    -1,    99,   130,
     169,   129,   169,   131,    -1,   100,   130,   169,    98,   169,
     167,   131,    -1,   101,   130,   169,    98,   169,   167,   131,
      -1,   102,   130,   166,   129,   169,   129,   169,   131,    -1,
     103,   130,   169,    98,   169,   166,   131,    -1,   104,   130,
     169,    98,   169,   166,   131,    -1,   105,   130,   166,    28,
     169,   131,    -1,    81,   130,   169,   131,    -1,    83,   130,
     169,   131,    -1,   167,    -1,   168,    -1,    92,    -1,    93,
      -1,    94,    -1,    95,    -1,    96,    -1,    97,    -1,   188,
      -1,   189,    -1,    50,    -1,    29,   181,    -1,    -1,   121,
     122,   175,    -1,    -1,   124,   122,   178,    -1,    -1,    34,
      13,    -1,    34,    13,    35,    13,    -1,    -1,   123,   182,
      -1,    -1,   175,   176,    -1,   177,    -1,   129,   177,    -1,
     188,    -1,   178,   179,    -1,   180,    -1,   129,   180,    -1,
     188,    -1,   188,   125,    -1,   188,   126,    -1,   181,     3,
     181,    -1,   181,     4,   181,    -1,   130,   181,   131,    -1,
      32,   130,   181,   131,    -1,   185,   184,    -1,   182,     3,
     182,    -1,   182,     4,   182,    -1,   130,   182,   131,    -1,
      32,   130,   182,   131,    -1,   185,   183,    -1,   116,   130,
     188,   131,    16,   189,    -1,   117,   130,   188,   131,    16,
     189,    -1,   119,   130,   188,   131,    16,   189,    -1,   118,
     130,   188,   131,    16,   189,    -1,   120,   130,   188,   131,
      16,   189,    -1,   188,    16,   189,    -1,   188,    16,   188,
      -1,   188,   185,    30,   189,     4,   189,    -1,   188,   185,
      31,   130,   156,   131,    -1,   188,    41,    32,    50,    -1,
     188,    41,    50,    -1,   165,    16,   165,    -1,   165,    16,
     188,    -1,   165,    16,   189,    -1,    32,    -1,    -1,   188,
      -1,   188,    33,   188,    -1,   188,   188,    -1,   188,    -1,
     116,   130,   188,   131,    -1,   117,   130,   188,   131,    -1,
     119,   130,   188,   131,    -1,   118,   130,   188,   131,    -1,
     120,   130,   188,   131,    -1,   120,   130,     7,   131,    -1,
       7,    -1,   188,     7,    -1,    12,    -1,   132,    12,   132,
      -1,    11,    -1,   190,    -1,    14,    -1,   191,    -1,    17,
      -1,    50,    -1,   106,   130,   131,    -1,    13,    -1,     6,
      13,    -1,     5,    13,    -1,    15,    -1,     6,    15,    -1,
       5,    15,    -1,    68,    52,   188,   193,   160,    -1,    74,
      52,   188,   160,    -1,   194,   195,   196,   197,   198,   199,
      -1,    -1,    69,   189,    -1,    -1,    70,   189,    -1,    -1,
      71,   188,    -1,    -1,    72,    -1,    -1,    73,   189,    -1,
      -1,    75,    -1,    51,    52,   188,   130,   204,   131,   160,
      -1,    51,    56,   188,    57,   188,   130,   144,   131,   202,
     201,   203,   160,    -1,    62,    52,   188,    -1,    62,    56,
     188,    -1,    67,    52,   188,   160,    -1,    -1,    58,   202,
      -1,    59,   202,    -1,    60,   202,    -1,    -1,    -1,    61,
      -1,    53,    -1,    -1,    -1,    63,    13,    -1,   205,    -1,
     205,   129,   213,    -1,   205,   206,    -1,   207,    -1,   129,
     207,    -1,   208,    -1,   209,   225,   210,   212,   211,   224,
      -1,   188,    -1,    -1,   130,    13,   131,    -1,    -1,    55,
     189,    -1,    -1,    32,    50,    -1,   223,    -1,   214,    -1,
     223,   129,   214,    -1,   214,   215,    -1,   216,    -1,   129,
     216,    -1,    64,    54,   130,   217,   131,    65,   188,   130,
     220,   131,    -1,   217,   218,    -1,   219,    -1,   129,   219,
      -1,   188,    -1,   220,   221,    -1,   222,    -1,   129,   222,
      -1,   188,    -1,    53,    54,   130,   144,   131,   203,    -1,
      -1,    21,    -1,    76,    -1,    77,    -1,    78,    -1,    84,
      -1,    86,    -1,    85,    -1,    79,    -1,    81,    -1,    83,
      -1,    80,    -1,    82,    -1,    88,    -1,    87,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    44,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    57,    64,    72,    78,    87,    96,
     105,   110,   117,   123,   131,   138,   145,   152,   157,   162,
     168,   173,   178,   183,   188,   193,   199,   205,   209,   211,
     215,   217,   218,   220,   222,   223,   229,   230,   231,   233,
     247,   260,   264,   266,   267,   269,   270,   272,   278,   286,
     287,   290,   291,   297,   304,   305,   311,   318,   326,   334,
     335,   338,   339,   342,   344,   349,   354,   360,   366,   372,
     378,   384,   390,   394,   398,   402,   403,   405,   412,   419,
     427,   434,   441,   448,   459,   466,   473,   485,   493,   501,
     506,   512,   517,   522,   528,   533,   538,   544,   551,   559,
     568,   581,   583,   584,   586,   587,   589,   593,   597,   599,
     600,   602,   603,   605,   607,   613,   614,   616,   618,   623,
     628,   634,   642,   649,   650,   658,   674,   682,   689,   690,
     698,   714,   723,   732,   741,   750,   761,   772,   783,   799,
     825,   833,   841,   849,   859,   868,   872,   874,   879,   884,
     890,   896,   901,   906,   911,   916,   921,   926,   930,   935,
     936,   938,   939,   940,   941,   942,   943,   944,   957,   958,
     967,   969,   970,   979,   981,   992,   999,  1001,  1002,  1008,
    1009,  1016,  1017,  1024,  1025,  1030,  1031,  1037,  1038,  1043,
    1049,  1057,  1063,  1069,  1076,  1077,  1081,  1085,  1090,  1094,
    1095,  1099,  1105,  1110,  1111,  1117,  1118,  1120,  1121,  1124,
    1127,  1133,  1136,  1141,  1142,  1154,  1155,  1167,  1168,  1173,
    1174,  1175,  1177,  1178,  1180,  1182,  1189,  1190,  1192,  1194,
    1200,  1201,  1203,  1205,  1212,  1217,  1218,  1239,  1243,  1247,
    1251,  1255,  1259,  1263,  1268,  1273,  1278,  1283,  1289,  1295
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
  "ALTER", "FLUSH", "ADD", "COLUMN", "MODIFY", "RENAME", "TO", "MIN",
  "MAX", "AVG", "SUM", "COUNT", "GROUP", "BY", "HAVING", "ORDER", "ASC",
  "DESC", "DISTINCT", "';'", "','", "'('", "')'", "'`'", "$accept",
  "command", "alter_statement", "management_statement",
  "user_manager_statement", "copy_table_statement", "internal_statement",
  "other", "select_statement", "opt_explain", "opt_distinct", "field_list",
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
     370,   371,   372,   373,   374,   375,   376,   377,    59,    44,
      40,    41,    96
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   133,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   135,   135,   135,   135,   135,   135,
     136,   137,   137,   137,   138,   138,   139,   140,   140,   140,
     140,   140,   140,   140,   140,   140,   141,   142,   142,   143,
     143,   144,   144,   145,   146,   146,   147,   147,   147,   148,
     148,   148,   148,   149,   149,   150,   150,   151,   152,   153,
     153,   154,   154,   155,   156,   156,   157,   158,   159,   160,
     160,   161,   161,   162,   163,   163,   163,   164,   164,   164,
     164,   164,   164,   164,   164,   164,   164,   165,   165,   165,
     165,   165,   165,   165,   165,   165,   165,   165,   165,   166,
     166,   167,   167,   167,   168,   168,   168,   169,   169,   169,
     170,   170,   171,   171,   172,   172,   173,   173,   173,   174,
     174,   175,   175,   176,   177,   178,   178,   179,   180,   180,
     180,   181,   181,   181,   181,   181,   182,   182,   182,   182,
     182,   183,   183,   183,   183,   183,   184,   184,   184,   184,
     184,   184,   184,   184,   184,   185,   185,   186,   186,   186,
     187,   187,   187,   187,   187,   187,   187,   187,   187,   188,
     188,   189,   189,   189,   189,   189,   189,   189,   190,   190,
     190,   191,   191,   191,   192,   192,   193,   194,   194,   195,
     195,   196,   196,   197,   197,   198,   198,   199,   199,   200,
     200,   200,   200,   200,   201,   201,   201,   201,   201,   202,
     202,   202,   202,   203,   203,   204,   204,   205,   205,   206,
     207,   208,   209,   210,   210,   211,   211,   212,   212,   213,
     213,   213,   214,   214,   215,   216,   217,   217,   218,   219,
     220,   220,   221,   222,   223,   224,   224,   225,   225,   225,
     225,   225,   225,   225,   225,   225,   225,   225,   225,   225
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     8,     7,     8,     6,     9,     7,
       3,     6,     4,     7,    15,    15,     3,     1,     2,     3,
       2,     1,     1,     1,     2,     2,    12,     2,     0,     1,
       0,     2,     1,     2,     1,     3,     2,     1,     2,     6,
       7,     4,     0,     0,     1,     0,     1,     2,     9,     0,
       3,     2,     1,     2,     2,     1,     2,     5,     6,     1,
       0,     2,     1,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     1,     1,     6,     7,     7,
       6,     7,     7,     8,     7,     7,     6,     4,     4,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     0,     3,     0,     3,     0,     2,     4,     0,     2,
       0,     2,     1,     2,     1,     2,     1,     2,     1,     2,
       2,     3,     3,     3,     4,     2,     3,     3,     3,     4,
       2,     6,     6,     6,     6,     6,     3,     3,     6,     6,
       4,     3,     3,     3,     3,     1,     0,     1,     3,     2,
       1,     4,     4,     4,     4,     4,     4,     1,     2,     1,
       3,     1,     1,     1,     1,     1,     1,     3,     1,     2,
       2,     1,     2,     2,     5,     4,     6,     0,     2,     0,
       2,     0,     2,     0,     1,     0,     2,     0,     1,     7,
      12,     3,     3,     4,     0,     2,     2,     2,     0,     0,
       1,     1,     0,     0,     2,     1,     3,     2,     1,     2,
       1,     6,     1,     0,     3,     0,     2,     0,     2,     1,
       1,     3,     2,     1,     2,    10,     2,     1,     2,     1,
       2,     1,     2,     1,     6,     0,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
      38,    27,     0,     0,    31,    33,    32,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    12,    11,    10,     9,     7,    13,     2,
       0,     3,     4,     5,     8,     6,   169,     0,     0,    28,
     157,    30,    34,    35,     0,    37,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    70,     0,     1,    40,    29,     0,     0,   159,    59,
     111,     0,     0,     0,     0,   201,   202,    70,    26,    70,
     187,    70,     0,     0,     0,    69,    20,     0,    39,     0,
     170,   158,     0,     0,     0,   156,    70,   111,    72,     0,
       0,     0,     0,     0,    22,   203,     0,    70,   189,   185,
       0,     0,     0,     0,     0,     0,     0,   167,     0,     0,
       0,     0,     0,     0,    42,    44,   160,    40,     0,     0,
     155,   156,   110,     0,    67,     0,    71,    70,     0,    40,
     222,     0,   215,   218,   220,     0,     0,    70,     0,     0,
     171,   178,   173,   181,   175,   176,     0,   188,   172,   174,
     184,     0,   191,     0,     0,     0,     0,     0,     0,    70,
       0,     0,     0,     0,     0,     0,     0,    41,     0,   168,
       0,    60,     0,   156,     0,   156,   156,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     135,   156,    73,    68,     0,     0,   109,     0,    74,    85,
      86,   107,   108,     0,    70,     0,   217,   247,   248,   249,
     253,   256,   254,   257,   255,   250,   252,   251,   259,   258,
     223,     0,    21,   180,   183,   179,   182,     0,   190,     0,
     193,    70,     0,     0,     0,    70,    70,    17,     0,     0,
       0,     0,     0,     0,   111,    47,    43,    45,     0,     0,
      62,     0,   133,   131,   132,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   155,
       0,     0,   178,   181,   109,    84,   108,   178,   181,    83,
       0,     0,     0,     0,     0,     0,     0,   199,     0,     0,
     219,   216,   230,   233,   229,     0,   227,     0,   177,   192,
     194,   195,    15,    70,    70,     0,    19,    23,   161,   162,
     164,   163,   166,   165,     0,    46,   113,    55,    55,    53,
      48,     0,     0,    70,    61,   134,     0,     0,     0,     0,
       0,     0,     0,     0,   101,   102,   103,   104,   105,   106,
       0,    99,   100,     0,     0,     0,   152,   153,   154,   147,
     146,     0,   151,     0,     0,    82,    80,    81,    79,    77,
      78,     0,     0,     0,     0,   232,     0,     0,     0,   225,
     209,     0,   197,    14,    16,    70,    57,     0,   120,    56,
       0,     0,    54,    55,   111,    63,    58,    97,    98,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   150,
       0,     0,   111,     0,     0,   234,   231,   224,   228,     0,
     245,   211,   210,   204,   196,   198,   186,    18,     0,   156,
     115,     0,    52,     0,   113,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    65,   113,     0,
     239,     0,   237,   226,   246,   221,   209,   209,   209,   213,
     112,   122,   124,   155,   156,   119,     0,     0,   118,   156,
      51,     0,   120,    87,     0,     0,    90,     0,     0,     0,
       0,     0,    96,   148,     0,   149,    64,   120,   213,     0,
       0,   236,   205,   206,   207,     0,    70,     0,   121,   156,
       0,   156,   156,     0,     0,     0,     0,     0,   140,     0,
       0,    70,    52,   156,   115,    88,    89,    91,    92,     0,
      94,    95,    66,   115,   244,   238,     0,   214,   200,   123,
       0,   138,   136,   137,     0,     0,     0,     0,     0,   114,
     126,   128,   116,    36,    49,    52,   118,    93,   118,     0,
     139,     0,     0,     0,     0,     0,     0,   125,   129,   130,
       0,    50,    70,    70,     0,     0,     0,     0,     0,     0,
     127,   117,    25,    24,   243,     0,   241,     0,     0,     0,
       0,     0,     0,   235,   240,   141,   142,   144,   143,   145,
     242
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      89,   123,   177,   124,   254,   330,   393,   390,   325,    31,
      94,   259,   334,   446,   486,    32,    33,    86,    97,   136,
      98,   208,   209,   350,   351,   352,   210,    96,   388,   468,
     511,   430,   460,   498,   461,   539,   557,   540,   132,   465,
     508,   200,   133,   255,   125,   211,   286,   158,   159,    34,
     107,   108,   162,   240,   311,   382,   426,    35,   459,   423,
     496,   141,   142,   216,   143,   144,   145,   306,   420,   379,
     301,   302,   375,   303,   451,   491,   452,   575,   584,   576,
     304,   455,   230
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -388
static const yytype_int16 yypact[] =
{
     691,  -388,    82,    11,  -388,  -388,  -388,    11,    11,   -23,
      -6,    58,    11,    45,    50,    41,    44,    57,    70,   137,
      61,    80,   147,  -388,  -388,  -388,  -388,  -388,  -388,  -388,
     163,  -388,  -388,  -388,  -388,  -388,  -388,    11,   214,  -388,
      -8,  -388,  -388,  -388,    11,  -388,    11,   158,    11,    11,
      11,    11,    11,    11,    11,    11,    11,    11,    11,    11,
      11,   102,    11,  -388,   109,  -388,   122,    11,  -388,    37,
     241,    11,    47,   263,   224,  -388,  -388,   102,  -388,   102,
     234,   102,   132,   252,   318,  -388,  -388,   271,  -388,   133,
    -388,  -388,   351,   133,   343,    30,   102,    -1,  -388,   380,
     379,    11,    11,   397,  -388,  -388,   330,   102,   340,  -388,
     301,   289,   290,   309,   307,   315,    11,  -388,   294,   295,
     297,   298,   299,     5,  -388,   401,   428,   109,   202,   308,
     311,    30,   236,   546,  -388,    11,  -388,   102,   359,   109,
    -388,   312,   310,  -388,  -388,   577,   314,   102,   325,   333,
    -388,  -388,  -388,  -388,  -388,  -388,   316,  -388,  -388,  -388,
    -388,   330,   376,    11,    11,    11,    11,    11,   440,   102,
      11,    11,    11,    11,    78,    11,   133,  -388,    11,  -388,
     133,  -388,   330,    30,    15,    30,    30,   322,   323,   324,
     326,   327,   336,   337,   338,   339,   344,   345,   346,   439,
    -388,    66,  -388,  -388,   466,   500,    59,   602,   293,  -388,
    -388,  -388,    63,   133,   102,    77,  -388,  -388,  -388,  -388,
    -388,  -388,  -388,  -388,  -388,  -388,  -388,  -388,  -388,  -388,
     352,   133,  -388,  -388,  -388,  -388,  -388,   342,  -388,    11,
     398,   102,   353,   354,   371,   102,   102,  -388,   357,   361,
     363,   367,   368,   377,     7,   233,  -388,  -388,     6,   220,
    -388,    18,  -388,   486,  -388,   106,   106,   106,   106,   106,
     106,   106,   106,   164,   106,   106,   164,   191,   387,  -388,
      94,   232,  -388,  -388,  -388,  -388,  -388,  -388,  -388,  -388,
      67,   602,   602,   602,   602,   602,    55,  -388,   455,   456,
    -388,  -388,   389,  -388,   391,   508,   490,   246,  -388,  -388,
    -388,   450,  -388,   102,   102,    11,  -388,  -388,  -388,  -388,
    -388,  -388,  -388,  -388,    11,  -388,   404,   487,   487,   491,
    -388,    11,   330,   102,  -388,  -388,   396,   399,   400,   433,
     441,   408,   442,   443,  -388,  -388,  -388,  -388,  -388,  -388,
     409,  -388,  -388,   444,   445,   516,  -388,  -388,  -388,  -388,
    -388,   495,  -388,   330,   416,  -388,   208,   208,  -388,  -388,
    -388,    11,   418,   421,   488,  -388,   488,   422,   509,   505,
      89,   330,   489,  -388,  -388,   102,  -388,   451,   438,  -388,
      11,    11,  -388,   487,     7,  -388,  -388,  -388,  -388,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   106,  -388,
     559,   330,     7,   133,    11,  -388,   389,  -388,  -388,   330,
     553,  -388,  -388,   175,  -388,  -388,  -388,  -388,    11,    36,
     452,   518,   233,    11,   404,   446,   188,   188,   447,   195,
     195,   453,   164,   164,   448,   330,   250,  -388,   404,   253,
    -388,   254,  -388,  -388,  -388,  -388,    89,    89,    89,   521,
     457,  -388,  -388,   458,    36,   275,   189,   463,   558,    30,
    -388,   530,   438,  -388,   462,   464,  -388,   478,   479,   106,
     480,   481,  -388,  -388,   330,  -388,  -388,   438,   521,    11,
     529,  -388,  -388,  -388,  -388,   584,   102,    11,  -388,    36,
      23,    36,    36,   492,   493,   494,   496,   498,  -388,    11,
     605,   102,   228,    30,   452,  -388,  -388,  -388,  -388,   502,
    -388,  -388,  -388,   452,  -388,  -388,    11,  -388,  -388,  -388,
      28,  -388,   616,  -388,    11,    11,    11,    11,    11,   510,
    -388,   185,   586,  -388,  -388,   228,   558,  -388,   558,   501,
    -388,   503,   507,   511,   512,   513,    11,  -388,  -388,  -388,
     612,  -388,   102,   102,    11,   624,   625,   650,   651,   652,
    -388,  -388,  -388,  -388,  -388,   266,  -388,   330,   330,   330,
     330,   330,    11,  -388,  -388,  -388,  -388,  -388,  -388,  -388,
    -388
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -388,  -388,  -388,  -388,  -388,  -388,  -388,  -388,  -388,  -388,
      12,   -76,  -388,   497,  -292,  -387,  -388,  -285,  -388,  -388,
    -388,  -388,  -388,  -388,  -388,  -388,  -388,   -66,  -388,  -388,
     534,   123,  -124,  -260,  -114,   -74,   -47,   -73,  -249,  -328,
    -143,  -377,  -388,  -388,   173,  -388,  -388,   115,  -119,  -386,
    -388,  -388,  -187,     0,  -388,    -2,   -77,  -388,  -388,  -388,
    -388,  -388,  -388,  -388,  -388,  -388,  -388,  -388,  -388,  -140,
     184,   515,  -388,  -388,   -88,  -388,  -388,  -388,  -388,  -388,
    -388,   300,  -388,   303,  -388,  -388,   186,  -388,  -388,    92,
    -388,  -388,  -388
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -77
static const yytype_int16 yytable[] =
{
      40,    40,    39,    41,    36,    40,    40,    42,    43,   199,
      47,   104,   184,   105,   281,   109,   355,   128,   185,   186,
      44,   185,   186,    36,   137,    67,   501,   502,    95,   157,
     134,   501,   502,   175,   331,    40,    95,    65,    68,   394,
      45,   160,    69,   391,    70,   470,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,   -76,
      87,   212,   130,   -75,   261,    91,   263,   264,   463,    99,
      92,   203,   291,   292,   293,   294,   295,   243,   500,   412,
     100,   232,   278,   371,   238,   252,    46,   126,   -76,    36,
      36,   126,   -75,    54,    36,   514,    55,    48,   279,   140,
     146,    49,    51,   247,   258,   260,    52,   280,   433,    56,
     523,   148,   149,   530,   169,   532,   533,   150,    36,   151,
     152,   153,    57,   154,    38,   544,   361,   300,   135,    61,
     298,   201,    62,    99,   176,   176,   324,   296,    37,   180,
     117,   299,   421,    38,   362,    36,   262,    63,   297,   335,
     422,   213,    50,   356,   531,   307,   284,    53,   561,   550,
     131,   241,   140,   140,   244,   245,   464,    93,   248,   249,
     250,   251,   253,    40,   126,   312,   257,   101,   126,   316,
     317,   326,   480,   481,   176,   472,   546,   -76,   -76,    58,
      64,   -75,   -75,    59,   110,   548,   148,   149,   365,   487,
     358,   360,   150,    36,   151,   152,   153,    71,   154,    38,
      38,   126,   156,   140,    38,   293,   294,   295,   336,   337,
     338,   339,   340,   341,   342,   343,    66,   353,   354,   126,
      85,   185,   186,   456,   457,   458,    88,   309,    38,   185,
     186,   155,   466,   111,    60,   112,   113,   383,   384,   118,
     119,   120,   121,   122,    90,   395,   344,   345,   346,   347,
     348,   349,   363,   364,   327,    38,   328,   396,   329,   327,
      95,   328,   187,   329,   188,   357,   359,   466,   501,   502,
     189,   190,   191,   347,   348,   349,   410,   344,   345,   346,
     192,   193,   194,   195,   196,   197,   198,   156,   291,   292,
     293,   294,   295,   106,   424,   503,   504,   505,   506,   507,
     558,   559,   466,   385,   466,   466,   492,   493,   494,   427,
     102,   434,    40,    38,   386,   477,   478,   285,   289,    40,
     290,   176,   103,   181,   447,   148,   149,   449,   233,   448,
     234,   150,   453,   151,   152,   153,   235,   154,   236,   332,
     512,   333,   435,   436,   437,   438,   439,   440,   441,   442,
     443,   444,   474,   475,   204,   205,   114,   115,   483,    40,
     150,    36,   151,   152,   153,   176,   154,   380,   127,   484,
     155,   485,   176,   489,   488,   490,   116,   129,    40,    40,
     431,   432,   148,   149,   545,   582,   138,   583,   150,    36,
     151,   152,   153,   562,   154,   563,   139,   522,   147,   206,
     161,   126,   450,   163,   366,   367,   368,   369,   370,   164,
     165,   166,   167,   168,   170,   171,   462,   172,   173,   174,
     528,    40,   519,   471,   178,   179,   156,   155,   182,   215,
     187,   183,   188,   214,   231,   543,   237,   239,   189,   190,
     191,   246,   265,   266,   267,   277,   268,   269,   192,   193,
     194,   195,   196,   197,   198,   156,   270,   271,   272,   273,
     310,   204,   205,   308,   274,   275,   276,   150,    36,   282,
     152,   283,   305,   154,   313,   314,   315,   450,   318,   207,
     186,    38,   319,   156,   320,   462,   572,   573,   321,   322,
     585,   586,   587,   588,   589,   204,   205,   541,   323,   372,
     373,   150,    36,   287,   152,   288,   284,   154,   374,    38,
     376,   377,   378,   381,   549,   387,   389,   397,   392,   399,
     398,   400,   551,   552,   553,   554,   555,   402,   405,   401,
     403,   404,   406,   407,   408,   409,   411,   187,   413,   188,
     284,   414,   299,   417,   541,   189,   190,   191,    36,   418,
     419,   429,   574,   445,   425,   192,   193,   194,   195,   196,
     197,   198,   156,   428,   454,   469,   467,   473,   476,   482,
     574,   187,   479,   188,   495,   509,   497,   513,   499,   189,
     190,   191,   510,   515,   526,   516,   207,   527,    38,   192,
     193,   194,   195,   196,   197,   198,   156,   204,   205,   517,
     518,   520,   521,   150,    36,   151,   152,   153,   542,   154,
     502,   560,   534,   535,   536,   571,   537,   187,   538,   188,
     207,   564,    38,   547,   565,   189,   190,   191,   566,   556,
     577,   578,   567,   568,   569,   192,   193,   194,   195,   196,
     197,   198,   284,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   579,   580,   581,   202,
     529,   570,   524,   256,   590,   525,   416,   415,    38,   242,
       0,     0,     0,   187,     0,   188,     0,     0,     0,     0,
       0,   189,   190,   191,     0,     0,     0,     0,     0,     0,
       0,   192,   193,   194,   195,   196,   197,   198,   156,     1,
       2,     3,     0,     4,     5,     6,     7,     8,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   207,     9,    38,     0,    10,     0,    11,    12,
       0,     0,    13,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    14,     0,     0,     0,    15,    16,    17,
       0,     0,     0,     0,     0,    18,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      19,    20,     0,     0,     0,    21
};

static const yytype_int16 yycheck[] =
{
       2,     3,     2,     3,    12,     7,     8,     7,     8,   133,
      12,    77,   131,    79,   201,    81,   276,    93,     3,     4,
      43,     3,     4,    12,    97,    33,     3,     4,    29,   106,
      96,     3,     4,    28,    28,    37,    29,    37,    40,   331,
      46,   107,    44,   328,    46,   432,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,     0,
      62,   138,    32,     0,   183,    67,   185,   186,    32,    71,
      33,   137,     5,     6,     7,     8,     9,   165,   464,   371,
      33,   147,    16,    28,   161,     7,    28,    89,    29,    12,
      12,    93,    29,    52,    12,   472,    52,    52,    32,   101,
     102,    56,    52,   169,   180,   182,    56,    41,   393,    52,
     487,     5,     6,   499,   116,   501,   502,    11,    12,    13,
      14,    15,    52,    17,   132,   512,    32,   215,   129,    68,
      53,   133,    52,   135,   129,   129,   129,   213,    56,   127,
       7,    64,    53,   132,    50,    12,   131,     0,   214,   131,
      61,   139,   107,   277,   131,   231,    50,   107,   545,   131,
     130,   163,   164,   165,   166,   167,   130,   130,   170,   171,
     172,   173,   174,   175,   176,   241,   178,   130,   180,   245,
     246,   254,   442,   443,   129,   434,   514,   128,   129,    52,
      27,   128,   129,    56,    62,   523,     5,     6,   131,   448,
     277,   278,    11,    12,    13,    14,    15,    49,    17,   132,
     132,   213,   106,   215,   132,     7,     8,     9,   265,   266,
     267,   268,   269,   270,   271,   272,    12,   274,   275,   231,
     128,     3,     4,    58,    59,    60,   127,   239,   132,     3,
       4,    50,   429,   111,   107,   113,   114,   313,   314,   116,
     117,   118,   119,   120,   132,   332,    92,    93,    94,    95,
      96,    97,    30,    31,    36,   132,    38,   333,    40,    36,
      29,    38,    81,    40,    83,   277,   278,   464,     3,     4,
      89,    90,    91,    95,    96,    97,   363,    92,    93,    94,
      99,   100,   101,   102,   103,   104,   105,   106,     5,     6,
       7,     8,     9,    69,   381,   116,   117,   118,   119,   120,
     125,   126,   499,   315,   501,   502,   456,   457,   458,   385,
      57,   394,   324,   132,   324,   439,   440,   204,   205,   331,
     207,   129,   108,   131,   411,     5,     6,   413,    13,   412,
      15,    11,   419,    13,    14,    15,    13,    17,    15,   129,
     469,   131,   399,   400,   401,   402,   403,   404,   405,   406,
     407,   408,   436,   437,     5,     6,   114,    49,   445,   371,
      11,    12,    13,    14,    15,   129,    17,   131,    27,   129,
      50,   131,   129,   129,   131,   131,   115,    44,   390,   391,
     390,   391,     5,     6,   513,   129,    16,   131,    11,    12,
      13,    14,    15,   546,    17,   548,    27,   484,    11,    50,
      70,   413,   414,   112,   291,   292,   293,   294,   295,   130,
     130,   112,   115,   108,   130,   130,   428,   130,   130,   130,
     496,   433,   479,   433,    33,     7,   106,    50,   130,   129,
      81,   130,    83,   131,   130,   511,   130,    71,    89,    90,
      91,    11,   130,   130,   130,    16,   130,   130,    99,   100,
     101,   102,   103,   104,   105,   106,   130,   130,   130,   130,
      72,     5,     6,   131,   130,   130,   130,    11,    12,    13,
      14,    15,   130,    17,   131,   131,   115,   489,   131,   130,
       4,   132,   131,   106,   131,   497,   562,   563,   131,   131,
     577,   578,   579,   580,   581,     5,     6,   509,   131,    54,
      54,    11,    12,    13,    14,    15,    50,    17,   129,   132,
     129,    13,    32,    73,   526,   121,    39,   131,    37,   129,
     131,    98,   534,   535,   536,   537,   538,   129,   129,    98,
      98,    98,    98,    98,    28,    50,   130,    81,   130,    83,
      50,   130,    64,   131,   556,    89,    90,    91,    12,    50,
      55,   123,   564,     4,    75,    99,   100,   101,   102,   103,
     104,   105,   106,   122,    21,    57,   124,   131,   131,   131,
     582,    81,   129,    83,    63,   122,   129,    57,   130,    89,
      90,    91,    34,   131,    65,   131,   130,    13,   132,    99,
     100,   101,   102,   103,   104,   105,   106,     5,     6,   131,
     131,   131,   131,    11,    12,    13,    14,    15,    13,    17,
       4,    35,   130,   130,   130,    13,   130,    81,   130,    83,
     130,   130,   132,   131,   131,    89,    90,    91,   131,   129,
      16,    16,   131,   131,   131,    99,   100,   101,   102,   103,
     104,   105,    50,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    16,    16,    16,   135,
     497,   556,   488,   176,   582,   489,   376,   374,   132,   164,
      -1,    -1,    -1,    81,    -1,    83,    -1,    -1,    -1,    -1,
      -1,    89,    90,    91,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    99,   100,   101,   102,   103,   104,   105,   106,    18,
      19,    20,    -1,    22,    23,    24,    25,    26,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   130,    42,   132,    -1,    45,    -1,    47,    48,
      -1,    -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    62,    -1,    -1,    -1,    66,    67,    68,
      -1,    -1,    -1,    -1,    -1,    74,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     109,   110,    -1,    -1,    -1,   114
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    18,    19,    20,    22,    23,    24,    25,    26,    42,
      45,    47,    48,    51,    62,    66,    67,    68,    74,   109,
     110,   114,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   152,   158,   159,   192,   200,    12,    56,   132,   186,
     188,   186,   186,   186,    43,    46,    28,   188,    52,    56,
     107,    52,    56,   107,    52,    52,    52,    52,    52,    56,
     107,    68,    52,     0,    27,   186,    12,    33,   188,   188,
     188,    49,   188,   188,   188,   188,   188,   188,   188,   188,
     188,   188,   188,   188,   188,   128,   160,   188,   127,   143,
     132,   188,    33,   130,   153,    29,   170,   161,   163,   188,
      33,   130,    57,   108,   160,   160,    69,   193,   194,   160,
      62,   111,   113,   114,   114,    49,   115,     7,   116,   117,
     118,   119,   120,   144,   146,   187,   188,    27,   144,    44,
      32,   130,   181,   185,   160,   129,   162,   170,    16,    27,
     188,   204,   205,   207,   208,   209,   188,    11,     5,     6,
      11,    13,    14,    15,    17,    50,   106,   189,   190,   191,
     160,    70,   195,   112,   130,   130,   112,   115,   108,   188,
     130,   130,   130,   130,   130,    28,   129,   145,    33,     7,
     143,   131,   130,   130,   181,     3,     4,    81,    83,    89,
      90,    91,    99,   100,   101,   102,   103,   104,   105,   165,
     184,   188,   163,   160,     5,     6,    50,   130,   164,   165,
     169,   188,   189,   143,   131,   129,   206,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
     225,   130,   160,    13,    15,    13,    15,   130,   189,    71,
     196,   188,   204,   207,   188,   188,    11,   160,   188,   188,
     188,   188,     7,   188,   147,   186,   146,   188,   144,   154,
     189,   181,   131,   181,   181,   130,   130,   130,   130,   130,
     130,   130,   130,   130,   130,   130,   130,    16,    16,    32,
      41,   185,    13,    15,    50,   164,   189,    13,    15,   164,
     164,     5,     6,     7,     8,     9,   144,   160,    53,    64,
     207,   213,   214,   216,   223,   130,   210,   144,   131,   188,
      72,   197,   160,   131,   131,   115,   160,   160,   131,   131,
     131,   131,   131,   131,   129,   151,   170,    36,    38,    40,
     148,    28,   129,   131,   155,   131,   169,   169,   169,   169,
     169,   169,   169,   169,    92,    93,    94,    95,    96,    97,
     166,   167,   168,   169,   169,   166,   165,   188,   189,   188,
     189,    32,    50,    30,    31,   131,   164,   164,   164,   164,
     164,    28,    54,    54,   129,   215,   129,    13,    32,   212,
     131,    73,   198,   160,   160,   188,   186,   121,   171,    39,
     150,   150,    37,   149,   147,   189,   160,   131,   131,   129,
      98,    98,   129,    98,    98,   129,    98,    98,    28,    50,
     189,   130,   147,   130,   130,   216,   214,   131,    50,    55,
     211,    53,    61,   202,   189,    75,   199,   160,   122,   123,
     174,   186,   186,   150,   170,   169,   169,   169,   169,   169,
     169,   169,   169,   169,   169,     4,   156,   189,   170,   144,
     188,   217,   219,   189,    21,   224,    58,    59,    60,   201,
     175,   177,   188,    32,   130,   182,   185,   124,   172,    57,
     148,   186,   171,   131,   168,   168,   131,   167,   167,   129,
     166,   166,   131,   189,   129,   131,   157,   171,   131,   129,
     131,   218,   202,   202,   202,    63,   203,   129,   176,   130,
     182,     3,     4,   116,   117,   118,   119,   120,   183,   122,
      34,   173,   181,    57,   174,   131,   131,   131,   131,   169,
     131,   131,   189,   174,   203,   219,    65,    13,   160,   177,
     182,   131,   182,   182,   130,   130,   130,   130,   130,   178,
     180,   188,    13,   160,   148,   181,   172,   131,   172,   188,
     131,   188,   188,   188,   188,   188,   129,   179,   125,   126,
      35,   148,   173,   173,   130,   131,   131,   131,   131,   131,
     180,    13,   160,   160,   188,   220,   222,    16,    16,    16,
      16,    16,   129,   131,   221,   189,   189,   189,   189,   189,
     222
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
    {YYACCEPT;}
    break;

  case 14:

/* Line 1464 of yacc.c  */
#line 58 "dmlyacc.yxx"
    {
            parsedData->setStmtType(AlterStatement);
            parsedData->setAlterType(ALTERADD);
            parsedData->setTableName((yyvsp[(3) - (8)].stringval));
            free((yyvsp[(3) - (8)].stringval)); 
	}
    break;

  case 15:

/* Line 1464 of yacc.c  */
#line 65 "dmlyacc.yxx"
    {
            parsedData->setStmtType(AlterStatement);
            parsedData->setAlterType(ALTERDROP);
            parsedData->setTableName((yyvsp[(3) - (7)].stringval));
            parsedData->setIndexName((yyvsp[(6) - (7)].stringval)); 
            free((yyvsp[(3) - (7)].stringval));
	}
    break;

  case 16:

/* Line 1464 of yacc.c  */
#line 73 "dmlyacc.yxx"
    {
            printf(" Not Implemented\n");
            free((yyvsp[(3) - (8)].stringval));
            YYABORT;
	}
    break;

  case 17:

/* Line 1464 of yacc.c  */
#line 79 "dmlyacc.yxx"
    {
            parsedData->setStmtType(AlterStatement);
            parsedData->setAlterType(ALTERTABLERENAME);
            parsedData->setTableName((yyvsp[(3) - (6)].stringval));
            parsedData->setIndexName((yyvsp[(5) - (6)].stringval)); 
            free((yyvsp[(3) - (6)].stringval)); free((yyvsp[(5) - (6)].stringval));

	}
    break;

  case 18:

/* Line 1464 of yacc.c  */
#line 88 "dmlyacc.yxx"
    {
            parsedData->setStmtType(AlterStatement);
            parsedData->setAlterType(ALTERFIELDRENAME);
            parsedData->setTableName((yyvsp[(3) - (9)].stringval));
            parsedData->setIndexName((yyvsp[(6) - (9)].stringval));
            parsedData->setPKTableName((yyvsp[(8) - (9)].stringval));
            free((yyvsp[(3) - (9)].stringval)); free((yyvsp[(5) - (9)].stringval)); free((yyvsp[(8) - (9)].stringval));
        }
    break;

  case 19:

/* Line 1464 of yacc.c  */
#line 97 "dmlyacc.yxx"
    {
            parsedData->setStmtType(AlterStatement);
            parsedData->setAlterType(ALTERINDEXRENAME);
            parsedData->setTableName((yyvsp[(3) - (7)].stringval));
            parsedData->setIndexName((yyvsp[(6) - (7)].stringval)); 
            free((yyvsp[(3) - (7)].stringval)); free((yyvsp[(5) - (7)].stringval));
        }
    break;

  case 20:

/* Line 1464 of yacc.c  */
#line 106 "dmlyacc.yxx"
    {
           parsedData->setStmtType(MgmtStatement);
	}
    break;

  case 21:

/* Line 1464 of yacc.c  */
#line 111 "dmlyacc.yxx"
    {
            parsedData->setStmtType(UserStatement);
            parsedData->createUserNode((char*)(yyvsp[(3) - (6)].stringval),(char*)(yyvsp[(5) - (6)].stringval));
            free((yyvsp[(3) - (6)].stringval));
            free((yyvsp[(5) - (6)].stringval));
	}
    break;

  case 22:

/* Line 1464 of yacc.c  */
#line 118 "dmlyacc.yxx"
    {
            parsedData->setStmtType(UserStatement);
            parsedData->dropUserNode((char*)(yyvsp[(3) - (4)].stringval));
            free((yyvsp[(3) - (4)].stringval));
        }
    break;

  case 23:

/* Line 1464 of yacc.c  */
#line 124 "dmlyacc.yxx"
    {
            parsedData->setStmtType(UserStatement);
            parsedData->alterUserNode((char*)(yyvsp[(3) - (7)].stringval),(char*)(yyvsp[(6) - (7)].stringval));
            free((yyvsp[(3) - (7)].stringval));
            free((yyvsp[(6) - (7)].stringval));
	}
    break;

  case 24:

/* Line 1464 of yacc.c  */
#line 132 "dmlyacc.yxx"
    {
            parsedData->setStmtType(CopyTableStatement);
            parsedData->setPKTableName((yyvsp[(3) - (15)].stringval));
            parsedData->setCreateTbl();
            free((yyvsp[(3) - (15)].stringval));
        }
    break;

  case 25:

/* Line 1464 of yacc.c  */
#line 139 "dmlyacc.yxx"
    {
            parsedData->setStmtType(CopyTableStatement);
            parsedData->setPKTableName((yyvsp[(3) - (15)].stringval));
            free((yyvsp[(3) - (15)].stringval));
        }
    break;

  case 26:

/* Line 1464 of yacc.c  */
#line 146 "dmlyacc.yxx"
    {
            parsedData->setStmtType(CompactTableStatement);
            parsedData->setTableName((yyvsp[(3) - (3)].stringval));
            free((yyvsp[(3) - (3)].stringval));
        }
    break;

  case 27:

/* Line 1464 of yacc.c  */
#line 153 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetTables);
	}
    break;

  case 28:

/* Line 1464 of yacc.c  */
#line 158 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetColumns);
        }
    break;

  case 29:

/* Line 1464 of yacc.c  */
#line 163 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetIndexes);
                   
        }
    break;

  case 30:

/* Line 1464 of yacc.c  */
#line 169 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetPriIndex);
        }
    break;

  case 31:

/* Line 1464 of yacc.c  */
#line 174 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetCatalogs);
        }
    break;

  case 32:

/* Line 1464 of yacc.c  */
#line 179 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetTableType);
        }
    break;

  case 33:

/* Line 1464 of yacc.c  */
#line 184 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetDataType);
        }
    break;

  case 34:

/* Line 1464 of yacc.c  */
#line 189 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetImportKey);
        }
    break;

  case 35:

/* Line 1464 of yacc.c  */
#line 194 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetExportKey);
        }
    break;

  case 36:

/* Line 1464 of yacc.c  */
#line 200 "dmlyacc.yxx"
    {
            parsedData->setStmtType(SelectStatement);
            parsedData->setCacheWorthy(true);
        }
    break;

  case 37:

/* Line 1464 of yacc.c  */
#line 206 "dmlyacc.yxx"
    {
           parsedData->setExplain();
	}
    break;

  case 39:

/* Line 1464 of yacc.c  */
#line 212 "dmlyacc.yxx"
    { 
            parsedData->setDistinct();
        }
    break;

  case 45:

/* Line 1464 of yacc.c  */
#line 224 "dmlyacc.yxx"
    {
            parsedData->insertFieldAlias((char*)(yyvsp[(3) - (3)].stringval));
            free((char*)(yyvsp[(3) - (3)].stringval));
        }
    break;

  case 49:

/* Line 1464 of yacc.c  */
#line 234 "dmlyacc.yxx"
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

  case 50:

/* Line 1464 of yacc.c  */
#line 248 "dmlyacc.yxx"
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

  case 51:

/* Line 1464 of yacc.c  */
#line 261 "dmlyacc.yxx"
    {
            parsedData->insertJoinType(INNER_JOIN);
        }
    break;

  case 57:

/* Line 1464 of yacc.c  */
#line 273 "dmlyacc.yxx"
    {
            parsedData->insertJoinType(INNER_JOIN);
        }
    break;

  case 58:

/* Line 1464 of yacc.c  */
#line 279 "dmlyacc.yxx"
    {
            parsedData->setStmtType(InsertStatement);
            parsedData->setTableName((yyvsp[(3) - (9)].stringval)); 
            free((yyvsp[(3) - (9)].stringval));
        }
    break;

  case 62:

/* Line 1464 of yacc.c  */
#line 292 "dmlyacc.yxx"
    {
            parsedData->insertValue((char*)(yyvsp[(1) - (1)].stringval));
            free((yyvsp[(1) - (1)].stringval));
        }
    break;

  case 63:

/* Line 1464 of yacc.c  */
#line 298 "dmlyacc.yxx"
    {
            parsedData->insertValue((char*)(yyvsp[(2) - (2)].stringval));
            free((yyvsp[(2) - (2)].stringval));
        }
    break;

  case 65:

/* Line 1464 of yacc.c  */
#line 306 "dmlyacc.yxx"
    {
            parsedData->insertInValue((char*)(yyvsp[(1) - (1)].stringval));
            free((yyvsp[(1) - (1)].stringval));
        }
    break;

  case 66:

/* Line 1464 of yacc.c  */
#line 312 "dmlyacc.yxx"
    {
            parsedData->insertInValue((char*)(yyvsp[(2) - (2)].stringval));
            free((yyvsp[(2) - (2)].stringval));
        }
    break;

  case 67:

/* Line 1464 of yacc.c  */
#line 319 "dmlyacc.yxx"
    {
            parsedData->setStmtType(DeleteStatement);
            parsedData->setTableName((yyvsp[(3) - (5)].stringval)); 
            free((yyvsp[(3) - (5)].stringval));
	}
    break;

  case 68:

/* Line 1464 of yacc.c  */
#line 327 "dmlyacc.yxx"
    {
            parsedData->setStmtType(UpdateStatement);
            parsedData->setTableName((yyvsp[(2) - (6)].stringval)); 
            free( (yyvsp[(2) - (6)].stringval) );
	}
    break;

  case 74:

/* Line 1464 of yacc.c  */
#line 345 "dmlyacc.yxx"
    {
           parsedData->insertUpdateExpression( (char*) (yyvsp[(1) - (3)].stringval), (Expression* ) (yyvsp[(3) - (3)].Expression));
           free( (yyvsp[(1) - (3)].stringval) ); free((yyvsp[(2) - (3)].stringval));
        }
    break;

  case 75:

/* Line 1464 of yacc.c  */
#line 350 "dmlyacc.yxx"
    { 
            parsedData->insertUpdateValue( (char*) (yyvsp[(1) - (3)].stringval), (char*) (yyvsp[(3) - (3)].stringval));
            free( (yyvsp[(1) - (3)].stringval) ); free((yyvsp[(2) - (3)].stringval));free( (yyvsp[(3) - (3)].stringval) ); 
        }
    break;

  case 76:

/* Line 1464 of yacc.c  */
#line 355 "dmlyacc.yxx"
    {
            parsedData->insertUpdateValue( (char*) (yyvsp[(1) - (3)].stringval), (char*) (yyvsp[(3) - (3)].stringval));
            free( (yyvsp[(1) - (3)].stringval) ); free((yyvsp[(2) - (3)].stringval));free( (yyvsp[(3) - (3)].stringval) );
        }
    break;

  case 77:

/* Line 1464 of yacc.c  */
#line 361 "dmlyacc.yxx"
    {
            Expression* exp;
            exp=parsedData->insertExpression((Expression *)(yyvsp[(1) - (3)].Expression), division, (Expression *)(yyvsp[(3) - (3)].Expression));
            (yyval.Expression)=exp;
        }
    break;

  case 78:

/* Line 1464 of yacc.c  */
#line 367 "dmlyacc.yxx"
    {
            Expression* exp;
            exp=parsedData->insertExpression((Expression *)(yyvsp[(1) - (3)].Expression), modulus, (Expression *)(yyvsp[(3) - (3)].Expression));
            (yyval.Expression)=exp;
        }
    break;

  case 79:

/* Line 1464 of yacc.c  */
#line 373 "dmlyacc.yxx"
    {
            Expression* exp;
            exp=parsedData->insertExpression((Expression *)(yyvsp[(1) - (3)].Expression), multiplication, (Expression *)(yyvsp[(3) - (3)].Expression));
            (yyval.Expression)=exp;
        }
    break;

  case 80:

/* Line 1464 of yacc.c  */
#line 379 "dmlyacc.yxx"
    {
            Expression* exp;
            exp=parsedData->insertExpression((Expression *)(yyvsp[(1) - (3)].Expression), addition, (Expression *)(yyvsp[(3) - (3)].Expression));
            (yyval.Expression)=exp;
        }
    break;

  case 81:

/* Line 1464 of yacc.c  */
#line 385 "dmlyacc.yxx"
    {
            Expression* exp;
            exp=parsedData->insertExpression((Expression *)(yyvsp[(1) - (3)].Expression), subtraction, (Expression *)(yyvsp[(3) - (3)].Expression));
            (yyval.Expression)=exp;
        }
    break;

  case 82:

/* Line 1464 of yacc.c  */
#line 391 "dmlyacc.yxx"
    {
            (yyval.Expression)=(yyvsp[(2) - (3)].Expression);
        }
    break;

  case 83:

/* Line 1464 of yacc.c  */
#line 395 "dmlyacc.yxx"
    {
            (yyval.Expression) = (yyvsp[(2) - (2)].Expression);
        }
    break;

  case 84:

/* Line 1464 of yacc.c  */
#line 399 "dmlyacc.yxx"
    {
            (yyval.Expression) = (yyvsp[(2) - (2)].Expression);
        }
    break;

  case 87:

/* Line 1464 of yacc.c  */
#line 406 "dmlyacc.yxx"
    {
              Expression* exp;
              parsedData->setFunctionType(DATEDIFF);
              exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (6)].Expression), DATEDIFF, (Expression *)(yyvsp[(5) - (6)].Expression));
            (yyval.Expression)=exp;
        }
    break;

  case 88:

/* Line 1464 of yacc.c  */
#line 413 "dmlyacc.yxx"
    {
	         Expression* exp;
             parsedData->setFunctionType((*(FunctionType *)(yyvsp[(6) - (7)].FunctionType)));
             exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (7)].Expression), (*(FunctionType *)(yyvsp[(6) - (7)].FunctionType)), (Expression *)(yyvsp[(5) - (7)].Expression));
             (yyval.Expression)=exp;
	    }
    break;

  case 89:

/* Line 1464 of yacc.c  */
#line 420 "dmlyacc.yxx"
    {
             Expression* exp;
             //parsedData->setFunctionType((*(FunctionType *)$6));
             parsedData->setFunctionType((FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+3));
             exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (7)].Expression), (FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+3), (Expression *)(yyvsp[(5) - (7)].Expression));
             (yyval.Expression)=exp;
        }
    break;

  case 90:

/* Line 1464 of yacc.c  */
#line 428 "dmlyacc.yxx"
    {
              Expression* exp;
              parsedData->setFunctionType(TIMEDIFF);
              exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (6)].Expression), TIMEDIFF, (Expression *)(yyvsp[(5) - (6)].Expression));
            (yyval.Expression)=exp;
        }
    break;

  case 91:

/* Line 1464 of yacc.c  */
#line 435 "dmlyacc.yxx"
    {
             Expression* exp;
             parsedData->setFunctionType((*(FunctionType *)(yyvsp[(6) - (7)].FunctionType)));
             exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (7)].Expression), (*(FunctionType *)(yyvsp[(6) - (7)].FunctionType)), (Expression *)(yyvsp[(5) - (7)].Expression));
             (yyval.Expression)=exp;
        }
    break;

  case 92:

/* Line 1464 of yacc.c  */
#line 442 "dmlyacc.yxx"
    {
             Expression* exp;
             parsedData->setFunctionType((FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+3));
             exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (7)].Expression), (FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+3), (Expression *)(yyvsp[(5) - (7)].Expression));
             (yyval.Expression)=exp;
        }
    break;

  case 93:

/* Line 1464 of yacc.c  */
#line 449 "dmlyacc.yxx"
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

  case 94:

/* Line 1464 of yacc.c  */
#line 460 "dmlyacc.yxx"
    {
             Expression* exp;
             parsedData->setFunctionType((FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+12));
             exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (7)].Expression), (FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+12), (Expression *)(yyvsp[(5) - (7)].Expression));
             (yyval.Expression)=exp;
        }
    break;

  case 95:

/* Line 1464 of yacc.c  */
#line 467 "dmlyacc.yxx"
    {
             Expression* exp;
             parsedData->setFunctionType((FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+15));
             exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (7)].Expression), (FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+15), (Expression *)(yyvsp[(5) - (7)].Expression));
             (yyval.Expression)=exp;
        }
    break;

  case 96:

/* Line 1464 of yacc.c  */
#line 474 "dmlyacc.yxx"
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

  case 97:

/* Line 1464 of yacc.c  */
#line 486 "dmlyacc.yxx"
    {
            Expression* exp;
            parsedData->setFunctionType(DATEFROMTIMESTAMP);
            exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (4)].Expression), DATEFROMTIMESTAMP, NULL);
            (yyval.Expression)=exp;

        }
    break;

  case 98:

/* Line 1464 of yacc.c  */
#line 494 "dmlyacc.yxx"
    {
            Expression* exp;
            parsedData->setFunctionType(TIMEFROMTIMESTAMP);
            exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (4)].Expression), TIMEFROMTIMESTAMP, NULL);
            (yyval.Expression)=exp;
        }
    break;

  case 99:

/* Line 1464 of yacc.c  */
#line 502 "dmlyacc.yxx"
    {
           FunctionType val = *(FunctionType *)(yyvsp[(1) - (1)].FunctionType);
           (yyval.FunctionType) = &val;
        }
    break;

  case 100:

/* Line 1464 of yacc.c  */
#line 507 "dmlyacc.yxx"
    {
           FunctionType val = *(FunctionType *)(yyvsp[(1) - (1)].FunctionType);
           (yyval.FunctionType) = &val;
        }
    break;

  case 101:

/* Line 1464 of yacc.c  */
#line 513 "dmlyacc.yxx"
    { 
             FunctionType val = TIMEADDWITHHOUR;
             (yyval.FunctionType) = &val;
        }
    break;

  case 102:

/* Line 1464 of yacc.c  */
#line 518 "dmlyacc.yxx"
    {
             FunctionType val = TIMEADDWITHMIN;
             (yyval.FunctionType) = &val;
        }
    break;

  case 103:

/* Line 1464 of yacc.c  */
#line 523 "dmlyacc.yxx"
    {
             FunctionType val = TIMEADDWITHSEC;
             (yyval.FunctionType) = &val;
        }
    break;

  case 104:

/* Line 1464 of yacc.c  */
#line 529 "dmlyacc.yxx"
    {
	        FunctionType val = DATEADDWITHYEAR;
            (yyval.FunctionType) = &val;
	    }
    break;

  case 105:

/* Line 1464 of yacc.c  */
#line 534 "dmlyacc.yxx"
    {
	        FunctionType val = DATEADDWITHMON;
            (yyval.FunctionType) = &val;
        }
    break;

  case 106:

/* Line 1464 of yacc.c  */
#line 539 "dmlyacc.yxx"
    {
            FunctionType val = DATEADDWITHDAY;
            (yyval.FunctionType) = &val;
        }
    break;

  case 107:

/* Line 1464 of yacc.c  */
#line 545 "dmlyacc.yxx"
    {
            Expression* exp;
            exp=parsedData->insertExpression((char *)(yyvsp[(1) - (1)].stringval));
            free((yyvsp[(1) - (1)].stringval));
            (yyval.Expression)=exp;
        }
    break;

  case 108:

/* Line 1464 of yacc.c  */
#line 552 "dmlyacc.yxx"
    {
            Expression* exp;
            bool flag = false;
            exp=parsedData->insertExpression((char *)(yyvsp[(1) - (1)].stringval), flag);
            free((yyvsp[(1) - (1)].stringval));
            (yyval.Expression)=exp;
        }
    break;

  case 109:

/* Line 1464 of yacc.c  */
#line 560 "dmlyacc.yxx"
    {
            Expression* exp;
            exp=parsedData->insertExpression("NULL");
            free((yyvsp[(1) - (1)].stringval));
            (yyval.Expression)=exp;
        }
    break;

  case 110:

/* Line 1464 of yacc.c  */
#line 569 "dmlyacc.yxx"
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

  case 116:

/* Line 1464 of yacc.c  */
#line 590 "dmlyacc.yxx"
    {
            parsedData->setLimit(atoi((yyvsp[(2) - (2)].stringval)), 0);
        }
    break;

  case 117:

/* Line 1464 of yacc.c  */
#line 594 "dmlyacc.yxx"
    {
            parsedData->setLimit(atoi((yyvsp[(2) - (4)].stringval)), atoi((yyvsp[(4) - (4)].stringval)));
        }
    break;

  case 124:

/* Line 1464 of yacc.c  */
#line 608 "dmlyacc.yxx"
    {
            parsedData->insertGroupField((char*)(yyvsp[(1) - (1)].stringval));
            free( (yyvsp[(1) - (1)].stringval) );
        }
    break;

  case 128:

/* Line 1464 of yacc.c  */
#line 619 "dmlyacc.yxx"
    {
            parsedData->insertOrderByField((char*)(yyvsp[(1) - (1)].stringval));
            free( (yyvsp[(1) - (1)].stringval) );
        }
    break;

  case 129:

/* Line 1464 of yacc.c  */
#line 624 "dmlyacc.yxx"
    {
            parsedData->insertOrderByField((char*)(yyvsp[(1) - (2)].stringval));
            free( (yyvsp[(1) - (2)].stringval) );
        }
    break;

  case 130:

/* Line 1464 of yacc.c  */
#line 629 "dmlyacc.yxx"
    {
            parsedData->insertOrderByField((char*)(yyvsp[(1) - (2)].stringval), true);
            free( (yyvsp[(1) - (2)].stringval) );
        }
    break;

  case 131:

/* Line 1464 of yacc.c  */
#line 635 "dmlyacc.yxx"
    {
            Predicate *pred;
            pred = parsedData->insertPredicate((Predicate*) (yyvsp[(1) - (3)].predicate), OpOr, (Predicate*) (yyvsp[(3) - (3)].predicate));
            //parsedData->setCondition((Predicate*)pred);
            (yyval.predicate)= pred;

        }
    break;

  case 132:

/* Line 1464 of yacc.c  */
#line 643 "dmlyacc.yxx"
    {
            Predicate *pred;
            pred = parsedData->insertPredicate((Predicate*) (yyvsp[(1) - (3)].predicate), OpAnd, (Predicate*) (yyvsp[(3) - (3)].predicate));
            //parsedData->setCondition((Predicate*)pred);
            (yyval.predicate)= pred;
        }
    break;

  case 133:

/* Line 1464 of yacc.c  */
#line 649 "dmlyacc.yxx"
    { (yyval.predicate)=(yyvsp[(2) - (3)].predicate); }
    break;

  case 134:

/* Line 1464 of yacc.c  */
#line 651 "dmlyacc.yxx"
    {
            Predicate *pred;
            pred = parsedData->insertPredicate((Predicate*) (yyvsp[(3) - (4)].predicate), OpNot, NULL);
            //parsedData->setCondition((Predicate*)pred);
            (yyval.predicate)= pred;

        }
    break;

  case 135:

/* Line 1464 of yacc.c  */
#line 659 "dmlyacc.yxx"
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

  case 136:

/* Line 1464 of yacc.c  */
#line 675 "dmlyacc.yxx"
    {
            Predicate *pred;
            pred = parsedData->insertPredicate((Predicate*) (yyvsp[(1) - (3)].predicate), OpOr, (Predicate*) (yyvsp[(3) - (3)].predicate));
            parsedData->setHavingCondition((Predicate*)pred);
            (yyval.predicate)= pred;

        }
    break;

  case 137:

/* Line 1464 of yacc.c  */
#line 683 "dmlyacc.yxx"
    {
            Predicate *pred;
            pred = parsedData->insertPredicate((Predicate*) (yyvsp[(1) - (3)].predicate), OpAnd, (Predicate*) (yyvsp[(3) - (3)].predicate));
            parsedData->setHavingCondition((Predicate*)pred);
            (yyval.predicate)= pred;
        }
    break;

  case 138:

/* Line 1464 of yacc.c  */
#line 689 "dmlyacc.yxx"
    { (yyval.predicate)=(yyvsp[(2) - (3)].predicate); }
    break;

  case 139:

/* Line 1464 of yacc.c  */
#line 691 "dmlyacc.yxx"
    {
            Predicate *pred;
            pred = parsedData->insertPredicate((Predicate*) (yyvsp[(3) - (4)].predicate), OpNot, NULL);
            parsedData->setHavingCondition((Predicate*)pred);
            (yyval.predicate)= pred;

        }
    break;

  case 140:

/* Line 1464 of yacc.c  */
#line 699 "dmlyacc.yxx"
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

  case 141:

/* Line 1464 of yacc.c  */
#line 715 "dmlyacc.yxx"
    {
            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(5) - (6)].stringval));
            Predicate *pred;
            void **ptr = parsedData->insertCondValueAndGetPtr((char*)(yyvsp[(3) - (6)].stringval), (char*)(yyvsp[(6) - (6)].stringval), false, AGG_MIN, true);
            pred = parsedData->insertPredicate((char*) (yyvsp[(3) - (6)].stringval), op, ptr, AGG_MIN);
            free( (yyvsp[(1) - (6)].stringval) ); free ((yyvsp[(3) - (6)].stringval)); free ((yyvsp[(5) - (6)].stringval)); free ((yyvsp[(6) - (6)].stringval));
            (yyval.predicate)=pred;
        }
    break;

  case 142:

/* Line 1464 of yacc.c  */
#line 724 "dmlyacc.yxx"
    {
            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(5) - (6)].stringval));
            Predicate *pred;
            void **ptr = parsedData->insertCondValueAndGetPtr((char*)(yyvsp[(3) - (6)].stringval), (char*)(yyvsp[(6) - (6)].stringval), false, AGG_MAX, true);
            pred = parsedData->insertPredicate((char*) (yyvsp[(3) - (6)].stringval), op, ptr, AGG_MAX);
            free( (yyvsp[(1) - (6)].stringval) ); free ((yyvsp[(3) - (6)].stringval)); free ((yyvsp[(5) - (6)].stringval)); free ((yyvsp[(6) - (6)].stringval));
            (yyval.predicate)=pred;
        }
    break;

  case 143:

/* Line 1464 of yacc.c  */
#line 733 "dmlyacc.yxx"
    {
            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(5) - (6)].stringval));
            Predicate *pred;
            void **ptr = parsedData->insertCondValueAndGetPtr((char*)(yyvsp[(3) - (6)].stringval), (char*)(yyvsp[(6) - (6)].stringval), false, AGG_SUM, true);
            pred = parsedData->insertPredicate((char*) (yyvsp[(3) - (6)].stringval), op, ptr, AGG_SUM);
            free( (yyvsp[(1) - (6)].stringval) ); free ((yyvsp[(3) - (6)].stringval)); free ((yyvsp[(5) - (6)].stringval)); free ((yyvsp[(6) - (6)].stringval));
            (yyval.predicate)=pred;
        }
    break;

  case 144:

/* Line 1464 of yacc.c  */
#line 742 "dmlyacc.yxx"
    {
            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(5) - (6)].stringval));
            Predicate *pred;
            void **ptr = parsedData->insertCondValueAndGetPtr((char*)(yyvsp[(3) - (6)].stringval), (char*)(yyvsp[(6) - (6)].stringval), false, AGG_AVG, true);
            pred = parsedData->insertPredicate((char*) (yyvsp[(3) - (6)].stringval), op, ptr, AGG_AVG);
            free( (yyvsp[(1) - (6)].stringval) ); free ((yyvsp[(3) - (6)].stringval)); free ((yyvsp[(5) - (6)].stringval)); free ((yyvsp[(6) - (6)].stringval));
            (yyval.predicate)=pred;
        }
    break;

  case 145:

/* Line 1464 of yacc.c  */
#line 751 "dmlyacc.yxx"
    {
            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(5) - (6)].stringval));
            Predicate *pred;
            void **ptr = parsedData->insertCondValueAndGetPtr((char*)(yyvsp[(3) - (6)].stringval), (char*)(yyvsp[(6) - (6)].stringval), false, AGG_COUNT, true);
            pred = parsedData->insertPredicate((char*) (yyvsp[(3) - (6)].stringval), op, ptr, AGG_COUNT);
            free( (yyvsp[(1) - (6)].stringval) ); free ((yyvsp[(3) - (6)].stringval)); free ((yyvsp[(5) - (6)].stringval)); free ((yyvsp[(6) - (6)].stringval));
            (yyval.predicate)=pred;
        }
    break;

  case 146:

/* Line 1464 of yacc.c  */
#line 762 "dmlyacc.yxx"
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

  case 147:

/* Line 1464 of yacc.c  */
#line 773 "dmlyacc.yxx"
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

  case 148:

/* Line 1464 of yacc.c  */
#line 784 "dmlyacc.yxx"
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

  case 149:

/* Line 1464 of yacc.c  */
#line 800 "dmlyacc.yxx"
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

  case 150:

/* Line 1464 of yacc.c  */
#line 826 "dmlyacc.yxx"
    {
            Predicate *pred;
            parsedData->insertCondValue((char*) (yyvsp[(1) - (4)].stringval));
            pred = parsedData->insertNullPredicate((char*) (yyvsp[(1) - (4)].stringval), OpIsNull, false);
            free( (yyvsp[(1) - (4)].stringval) ); free((yyvsp[(2) - (4)].stringval)); free( (yyvsp[(3) - (4)].stringval) );
            (yyval.predicate)=pred;  
        }
    break;

  case 151:

/* Line 1464 of yacc.c  */
#line 834 "dmlyacc.yxx"
    {
            Predicate *pred;
            parsedData->insertCondValue((char*) (yyvsp[(1) - (3)].stringval));
            pred = parsedData->insertNullPredicate((char*) (yyvsp[(1) - (3)].stringval), OpIsNull, true);
            free( (yyvsp[(1) - (3)].stringval) ); free((yyvsp[(2) - (3)].stringval)); free( (yyvsp[(3) - (3)].stringval) );
            (yyval.predicate)=pred;  
        }
    break;

  case 152:

/* Line 1464 of yacc.c  */
#line 842 "dmlyacc.yxx"
    {
            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(2) - (3)].stringval));
            Predicate *pred;
            pred = parsedData->insertPredicate(((Expression*)(yyvsp[(1) - (3)].Expression)), op, ((Expression*)(yyvsp[(3) - (3)].Expression)));
            (yyval.predicate)=pred;
 
        }
    break;

  case 153:

/* Line 1464 of yacc.c  */
#line 850 "dmlyacc.yxx"
    {

            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(2) - (3)].stringval));
            parsedData->insertCondValue((char*) (yyvsp[(3) - (3)].stringval));
            Predicate *pred;
            pred = parsedData->insertPredicate(((Expression*)(yyvsp[(1) - (3)].Expression)), op, (char*) (yyvsp[(3) - (3)].stringval));
            (yyval.predicate)=pred;
            
        }
    break;

  case 154:

/* Line 1464 of yacc.c  */
#line 860 "dmlyacc.yxx"
    {
            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(2) - (3)].stringval));
            void **ptr = parsedData->insertCondValueAndGetPtr((char*)"dummy", (char*)(yyvsp[(3) - (3)].stringval), false, AGG_UNKNOWN, false, true);
            Predicate *pred;
            pred = parsedData->insertPredicate(((Expression*)(yyvsp[(1) - (3)].Expression)), op, ptr);
            (yyval.predicate)=pred;
        }
    break;

  case 155:

/* Line 1464 of yacc.c  */
#line 869 "dmlyacc.yxx"
    { (yyval.stringval)=(char*) 1;
	}
    break;

  case 156:

/* Line 1464 of yacc.c  */
#line 872 "dmlyacc.yxx"
    { (yyval.stringval)=(char*) 0; }
    break;

  case 157:

/* Line 1464 of yacc.c  */
#line 875 "dmlyacc.yxx"
    {
            parsedData->insertTableName((char*)(yyvsp[(1) - (1)].stringval));
            free( (yyvsp[(1) - (1)].stringval) );
        }
    break;

  case 158:

/* Line 1464 of yacc.c  */
#line 880 "dmlyacc.yxx"
    {
            parsedData->insertTableName((char*)(yyvsp[(1) - (3)].stringval), (char*)(yyvsp[(3) - (3)].stringval));
            free( (yyvsp[(1) - (3)].stringval) ); free((yyvsp[(3) - (3)].stringval));
        }
    break;

  case 159:

/* Line 1464 of yacc.c  */
#line 885 "dmlyacc.yxx"
    {
            parsedData->insertTableName((char*)(yyvsp[(1) - (2)].stringval), (char*)(yyvsp[(2) - (2)].stringval));
            free( (yyvsp[(1) - (2)].stringval) ); free((yyvsp[(2) - (2)].stringval));
        }
    break;

  case 160:

/* Line 1464 of yacc.c  */
#line 891 "dmlyacc.yxx"
    {
            parsedData->insertField((char*)(yyvsp[(1) - (1)].stringval));
            free( (yyvsp[(1) - (1)].stringval) );
            
        }
    break;

  case 161:

/* Line 1464 of yacc.c  */
#line 897 "dmlyacc.yxx"
    { 
            parsedData->insertField((char*)(yyvsp[(3) - (4)].stringval), AGG_MIN);
            free( (yyvsp[(1) - (4)].stringval) );
        }
    break;

  case 162:

/* Line 1464 of yacc.c  */
#line 902 "dmlyacc.yxx"
    { 
            parsedData->insertField((char*)(yyvsp[(3) - (4)].stringval), AGG_MAX);
            free( (yyvsp[(1) - (4)].stringval) );
        }
    break;

  case 163:

/* Line 1464 of yacc.c  */
#line 907 "dmlyacc.yxx"
    { 
            parsedData->insertField((char*)(yyvsp[(3) - (4)].stringval), AGG_SUM);
            free( (yyvsp[(1) - (4)].stringval) );
        }
    break;

  case 164:

/* Line 1464 of yacc.c  */
#line 912 "dmlyacc.yxx"
    { 
            parsedData->insertField((char*)(yyvsp[(3) - (4)].stringval), AGG_AVG);
            free( (yyvsp[(1) - (4)].stringval) );
        }
    break;

  case 165:

/* Line 1464 of yacc.c  */
#line 917 "dmlyacc.yxx"
    { 
            parsedData->insertField((char*)(yyvsp[(3) - (4)].stringval), AGG_COUNT);
            free( (yyvsp[(1) - (4)].stringval) );
        }
    break;

  case 166:

/* Line 1464 of yacc.c  */
#line 922 "dmlyacc.yxx"
    { 
            parsedData->insertField("*", AGG_COUNT);
            free( (yyvsp[(1) - (4)].stringval) );
        }
    break;

  case 167:

/* Line 1464 of yacc.c  */
#line 927 "dmlyacc.yxx"
    { 
            parsedData->insertField("*");
        }
    break;

  case 168:

/* Line 1464 of yacc.c  */
#line 931 "dmlyacc.yxx"
    {
            parsedData->insertField("*");
        }
    break;

  case 169:

/* Line 1464 of yacc.c  */
#line 935 "dmlyacc.yxx"
    { (yyval.stringval) = (yyvsp[(1) - (1)].stringval); }
    break;

  case 170:

/* Line 1464 of yacc.c  */
#line 936 "dmlyacc.yxx"
    { (yyval.stringval) = (yyvsp[(2) - (3)].stringval); }
    break;

  case 171:

/* Line 1464 of yacc.c  */
#line 938 "dmlyacc.yxx"
    { (yyval.stringval) = (yyvsp[(1) - (1)].stringval); }
    break;

  case 173:

/* Line 1464 of yacc.c  */
#line 940 "dmlyacc.yxx"
    { (yyval.stringval) = (yyvsp[(1) - (1)].stringval); }
    break;

  case 175:

/* Line 1464 of yacc.c  */
#line 942 "dmlyacc.yxx"
    { (yyval.stringval) = (yyvsp[(1) - (1)].stringval); }
    break;

  case 176:

/* Line 1464 of yacc.c  */
#line 943 "dmlyacc.yxx"
    { (yyval.stringval) = (char*) 0; }
    break;

  case 177:

/* Line 1464 of yacc.c  */
#line 945 "dmlyacc.yxx"
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

  case 178:

/* Line 1464 of yacc.c  */
#line 957 "dmlyacc.yxx"
    { (yyval.stringval) =  (yyvsp[(1) - (1)].stringval); }
    break;

  case 179:

/* Line 1464 of yacc.c  */
#line 959 "dmlyacc.yxx"
    {
             char *n;
             n=(char*)malloc(30);
             strcpy(n,"-");
             strcat(n,(char*)(yyvsp[(2) - (2)].stringval));
             (yyval.stringval)=n;
             free((yyvsp[(2) - (2)].stringval));
        }
    break;

  case 180:

/* Line 1464 of yacc.c  */
#line 967 "dmlyacc.yxx"
    { (yyval.stringval) =  (yyvsp[(2) - (2)].stringval); }
    break;

  case 181:

/* Line 1464 of yacc.c  */
#line 969 "dmlyacc.yxx"
    { (yyval.stringval) = (yyvsp[(1) - (1)].stringval); }
    break;

  case 182:

/* Line 1464 of yacc.c  */
#line 971 "dmlyacc.yxx"
    {
             char *d;
             d=(char*)malloc(30);
             strcpy(d,"-");
             strcat(d,(char*)(yyvsp[(2) - (2)].stringval));
             (yyval.stringval)=d;
             free((yyvsp[(2) - (2)].stringval));
        }
    break;

  case 183:

/* Line 1464 of yacc.c  */
#line 979 "dmlyacc.yxx"
    { (yyval.stringval) = (yyvsp[(2) - (2)].stringval); }
    break;

  case 184:

/* Line 1464 of yacc.c  */
#line 982 "dmlyacc.yxx"
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

  case 185:

/* Line 1464 of yacc.c  */
#line 993 "dmlyacc.yxx"
    {
            parsedData->setStmtType(CacheTableStatement);
            parsedData->setUnCache(true);
            parsedData->setTableName((yyvsp[(3) - (4)].stringval)); 
        }
    break;

  case 188:

/* Line 1464 of yacc.c  */
#line 1003 "dmlyacc.yxx"
    {
            parsedData->setHCondFld(true);
            parsedData->setHCondition((char*)(yyvsp[(2) - (2)].stringval));
         }
    break;

  case 190:

/* Line 1464 of yacc.c  */
#line 1010 "dmlyacc.yxx"
    {
            parsedData->setVCondFld(true);
            parsedData->setVCondition((char*)(yyvsp[(2) - (2)].stringval));
            free((yyvsp[(2) - (2)].stringval));
         }
    break;

  case 192:

/* Line 1464 of yacc.c  */
#line 1018 "dmlyacc.yxx"
    {
            parsedData->setPkFld(true);
            parsedData->setIndexName((char*)(yyvsp[(2) - (2)].stringval));
            free((yyvsp[(2) - (2)].stringval));
         }
    break;

  case 194:

/* Line 1464 of yacc.c  */
#line 1026 "dmlyacc.yxx"
    {
            parsedData->setDirect(true);
         }
    break;

  case 196:

/* Line 1464 of yacc.c  */
#line 1032 "dmlyacc.yxx"
    {
             parsedData->setDSN(true);
             parsedData->setPKTableName((char*)(yyvsp[(2) - (2)].stringval));
             free((yyvsp[(2) - (2)].stringval));
         }
    break;

  case 198:

/* Line 1464 of yacc.c  */
#line 1039 "dmlyacc.yxx"
    {
             parsedData->setNoSchema(true);
         }
    break;

  case 199:

/* Line 1464 of yacc.c  */
#line 1044 "dmlyacc.yxx"
    {
            parsedData->setStmtType(CreateTableStatement);
            parsedData->setTableName((yyvsp[(3) - (7)].stringval)); 
            free((yyvsp[(3) - (7)].stringval));
        }
    break;

  case 200:

/* Line 1464 of yacc.c  */
#line 1050 "dmlyacc.yxx"
    {
            parsedData->setStmtType(CreateIndexStatement);
            parsedData->setIndexName((yyvsp[(3) - (12)].stringval)); 
            parsedData->setTableName((yyvsp[(5) - (12)].stringval)); 
            free((yyvsp[(3) - (12)].stringval));
            free((yyvsp[(5) - (12)].stringval));
        }
    break;

  case 201:

/* Line 1464 of yacc.c  */
#line 1058 "dmlyacc.yxx"
    {
            parsedData->setStmtType(DropTableStatement);
            parsedData->setTableName((yyvsp[(3) - (3)].stringval)); 
            free((yyvsp[(3) - (3)].stringval));
        }
    break;

  case 202:

/* Line 1464 of yacc.c  */
#line 1064 "dmlyacc.yxx"
    {
            parsedData->setStmtType(DropIndexStatement);
            parsedData->setIndexName((yyvsp[(3) - (3)].stringval)); 
            free((yyvsp[(3) - (3)].stringval));
        }
    break;

  case 203:

/* Line 1464 of yacc.c  */
#line 1070 "dmlyacc.yxx"
    {
            parsedData->setStmtType(TruncateStatement);
            parsedData->setTableName((yyvsp[(3) - (4)].stringval)); 
            free((yyvsp[(3) - (4)].stringval));
        }
    break;

  case 205:

/* Line 1464 of yacc.c  */
#line 1078 "dmlyacc.yxx"
    {
            parsedData->setIndexType(hashIndex);
        }
    break;

  case 206:

/* Line 1464 of yacc.c  */
#line 1082 "dmlyacc.yxx"
    {
            parsedData->setIndexType(treeIndex);
        }
    break;

  case 207:

/* Line 1464 of yacc.c  */
#line 1086 "dmlyacc.yxx"
    {
            parsedData->setIndexType(trieIndex);
        }
    break;

  case 208:

/* Line 1464 of yacc.c  */
#line 1090 "dmlyacc.yxx"
    {
            parsedData->setIndexType(hashIndex);
        }
    break;

  case 210:

/* Line 1464 of yacc.c  */
#line 1096 "dmlyacc.yxx"
    {
            parsedData->setUnique(true);
        }
    break;

  case 211:

/* Line 1464 of yacc.c  */
#line 1100 "dmlyacc.yxx"
    {
            parsedData->setUnique(true);
            parsedData->setPrimary(true);
        }
    break;

  case 212:

/* Line 1464 of yacc.c  */
#line 1105 "dmlyacc.yxx"
    {
            parsedData->setUnique(false);
            parsedData->setPrimary(false);
        }
    break;

  case 214:

/* Line 1464 of yacc.c  */
#line 1112 "dmlyacc.yxx"
    {
            parsedData->setBucketSize(atoi((yyvsp[(2) - (2)].stringval)));
            free((yyvsp[(2) - (2)].stringval));
        }
    break;

  case 220:

/* Line 1464 of yacc.c  */
#line 1128 "dmlyacc.yxx"
    {
            parsedData->insertFldDef();
        }
    break;

  case 222:

/* Line 1464 of yacc.c  */
#line 1137 "dmlyacc.yxx"
    {
            parsedData->setFldName((yyvsp[(1) - (1)].stringval));
            free((yyvsp[(1) - (1)].stringval));
        }
    break;

  case 224:

/* Line 1464 of yacc.c  */
#line 1143 "dmlyacc.yxx"
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

  case 226:

/* Line 1464 of yacc.c  */
#line 1156 "dmlyacc.yxx"
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

  case 228:

/* Line 1464 of yacc.c  */
#line 1169 "dmlyacc.yxx"
    {
            parsedData->setFldNotNull(true);
        }
    break;

  case 235:

/* Line 1464 of yacc.c  */
#line 1183 "dmlyacc.yxx"
    {
            parsedData->setForeign(true);
            parsedData->setPKTableName((char*)(yyvsp[(7) - (10)].stringval));
            parsedData->insertForeignKeyList();
        }
    break;

  case 239:

/* Line 1464 of yacc.c  */
#line 1195 "dmlyacc.yxx"
    {
           parsedData->insertFKField((char*)(yyvsp[(1) - (1)].stringval));
           free((yyvsp[(1) - (1)].stringval));
        }
    break;

  case 243:

/* Line 1464 of yacc.c  */
#line 1206 "dmlyacc.yxx"
    {
           parsedData->insertPKField((char*)(yyvsp[(1) - (1)].stringval));
           free((yyvsp[(1) - (1)].stringval));
        }
    break;

  case 244:

/* Line 1464 of yacc.c  */
#line 1213 "dmlyacc.yxx"
    {
           parsedData->setPrimary(true);
        }
    break;

  case 246:

/* Line 1464 of yacc.c  */
#line 1219 "dmlyacc.yxx"
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

  case 247:

/* Line 1464 of yacc.c  */
#line 1240 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeInt);
        }
    break;

  case 248:

/* Line 1464 of yacc.c  */
#line 1244 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeLong);
        }
    break;

  case 249:

/* Line 1464 of yacc.c  */
#line 1248 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeShort);
        }
    break;

  case 250:

/* Line 1464 of yacc.c  */
#line 1252 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeLongLong);
        }
    break;

  case 251:

/* Line 1464 of yacc.c  */
#line 1256 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeByteInt);
        }
    break;

  case 252:

/* Line 1464 of yacc.c  */
#line 1260 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeFloat);
        }
    break;

  case 253:

/* Line 1464 of yacc.c  */
#line 1264 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeDouble);
        }
    break;

  case 254:

/* Line 1464 of yacc.c  */
#line 1269 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeDate);
        }
    break;

  case 255:

/* Line 1464 of yacc.c  */
#line 1274 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeTime);
        }
    break;

  case 256:

/* Line 1464 of yacc.c  */
#line 1279 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeTimeStamp);
        }
    break;

  case 257:

/* Line 1464 of yacc.c  */
#line 1284 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeString);
            parsedData->setFldLength(2);
        }
    break;

  case 258:

/* Line 1464 of yacc.c  */
#line 1290 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeVarchar);
            parsedData->setFldLength(2);
        }
    break;

  case 259:

/* Line 1464 of yacc.c  */
#line 1296 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeBinary);
            parsedData->setFldLength(1);
        }
    break;



/* Line 1464 of yacc.c  */
#line 4201 "dmlyacc.cxx"
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
#line 1301 "dmlyacc.yxx"


extern int lexEof;
void yyerror(const char* Msg) { 
    if( lexEof == 0 )
        fprintf(stderr, "[Parser: %s] %s\n", Msg, yytext);

    return;
}

