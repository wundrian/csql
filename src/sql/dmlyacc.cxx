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
     MIN = 368,
     MAX = 369,
     AVG = 370,
     SUM = 371,
     COUNT = 372,
     GROUP = 373,
     BY = 374,
     HAVING = 375,
     ORDER = 376,
     ASC = 377,
     DESC = 378,
     DISTINCT = 379
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
#define MIN 368
#define MAX 369
#define AVG 370
#define SUM 371
#define COUNT 372
#define GROUP 373
#define BY 374
#define HAVING 375
#define ORDER 376
#define ASC 377
#define DESC 378
#define DISTINCT 379




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
#line 378 "dmlyacc.cxx"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 390 "dmlyacc.cxx"

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
#define YYLAST   799

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  135
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  100
/* YYNRULES -- Number of rules.  */
#define YYNRULES  272
/* YYNRULES -- Number of states.  */
#define YYNSTATES  613

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   379

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     9,     2,     2,
     132,   133,     7,     5,   131,     6,     2,     8,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,   130,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,   134,     2,     2,     2,
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
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    11,    13,    15,    17,
      19,    21,    23,    25,    27,    29,    38,    46,    55,    62,
      72,    80,    84,    91,    96,   104,   107,   109,   112,   114,
     116,   118,   120,   123,   125,   128,   130,   139,   155,   171,
     175,   177,   180,   184,   187,   189,   191,   193,   196,   199,
     212,   215,   216,   218,   219,   222,   224,   227,   229,   233,
     236,   238,   241,   248,   256,   261,   262,   263,   265,   266,
     268,   271,   281,   282,   286,   289,   291,   294,   297,   299,
     302,   308,   315,   317,   318,   321,   323,   326,   330,   334,
     338,   342,   346,   350,   354,   358,   362,   365,   368,   370,
     372,   379,   387,   395,   402,   410,   418,   427,   435,   443,
     450,   455,   460,   462,   464,   466,   468,   470,   472,   474,
     476,   478,   480,   482,   485,   486,   490,   491,   495,   496,
     499,   504,   505,   508,   509,   512,   514,   517,   519,   522,
     524,   527,   529,   532,   535,   539,   543,   547,   552,   555,
     559,   563,   567,   572,   575,   582,   589,   596,   603,   610,
     614,   618,   625,   632,   637,   641,   645,   649,   653,   655,
     656,   658,   662,   665,   667,   672,   677,   682,   687,   692,
     697,   699,   702,   704,   708,   710,   712,   714,   716,   718,
     720,   724,   726,   729,   732,   734,   737,   740,   746,   751,
     758,   759,   762,   763,   766,   767,   770,   771,   773,   774,
     777,   778,   780,   788,   801,   805,   809,   814,   815,   818,
     821,   824,   825,   826,   828,   830,   831,   832,   835,   837,
     841,   844,   846,   849,   851,   858,   860,   861,   865,   866,
     869,   870,   873,   875,   877,   881,   884,   886,   889,   900,
     903,   905,   908,   910,   913,   915,   918,   920,   927,   928,
     930,   932,   934,   936,   938,   940,   942,   944,   946,   948,
     950,   952,   954
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     136,     0,    -1,   150,    -1,   161,    -1,   167,    -1,   168,
      -1,   209,    -1,   148,    -1,   201,    -1,   147,    -1,   139,
      -1,   146,    -1,   138,    -1,   137,    -1,   149,    -1,   109,
      52,   197,   111,   132,   213,   133,   169,    -1,   109,    52,
     197,    62,   112,   197,   169,    -1,   109,    52,   197,   113,
     132,   216,   133,   169,    -1,   114,    52,   197,   115,   197,
     169,    -1,   109,    52,   197,   114,   112,   197,   115,   197,
     169,    -1,   109,    56,   197,   114,   115,   197,   169,    -1,
     110,    68,   169,    -1,    51,   107,   197,   108,    11,   169,
      -1,    62,   107,   197,   169,    -1,   109,   107,   197,    49,
     108,    11,   169,    -1,   140,   141,    -1,   142,    -1,   131,
     142,    -1,    27,    -1,    42,    -1,    48,    -1,    47,    -1,
     143,   144,    -1,   145,    -1,   131,   145,    -1,   197,    -1,
     116,   140,    57,   197,   115,   143,   179,   169,    -1,    51,
      52,   197,    33,    27,   152,   153,    28,   156,   179,   180,
     183,   181,   182,   169,    -1,    42,    43,   197,    33,    27,
     152,   153,    28,   156,   179,   180,   183,   181,   182,   169,
      -1,    66,    52,   197,    -1,    18,    -1,    19,   195,    -1,
      19,    56,   195,    -1,    20,   195,    -1,    22,    -1,    24,
      -1,    23,    -1,    25,   195,    -1,    26,   195,    -1,   151,
      27,   152,   153,    28,   156,   179,   180,   183,   181,   182,
     169,    -1,    45,    46,    -1,    -1,   129,    -1,    -1,   153,
     154,    -1,   155,    -1,   131,   155,    -1,   196,    -1,   196,
      33,   197,    -1,   156,   160,    -1,   195,    -1,   195,   157,
      -1,    36,   159,   195,    57,   190,   157,    -1,    40,   158,
     159,   195,    57,   190,   157,    -1,    38,   159,   195,   157,
      -1,    -1,    -1,    37,    -1,    -1,    39,    -1,   131,   195,
      -1,    42,    43,   197,   162,    44,   132,   163,   133,   169,
      -1,    -1,   132,   153,   133,    -1,   163,   164,    -1,   198,
      -1,   131,   198,    -1,   165,   166,    -1,   198,    -1,   131,
     198,    -1,    47,    28,   197,   179,   169,    -1,    48,   197,
      49,   170,   179,   169,    -1,   130,    -1,    -1,   170,   171,
      -1,   172,    -1,   131,   172,    -1,   197,    16,   173,    -1,
     197,    16,   198,    -1,   197,    16,    50,    -1,   173,     8,
     173,    -1,   173,     9,   173,    -1,   173,     7,   173,    -1,
     173,     5,   173,    -1,   173,     6,   173,    -1,   132,   173,
     133,    -1,     6,   173,    -1,     5,   173,    -1,   174,    -1,
     178,    -1,    89,   132,   178,   131,   178,   133,    -1,    90,
     132,   178,    98,   178,   177,   133,    -1,    91,   132,   178,
      98,   178,   177,   133,    -1,    99,   132,   178,   131,   178,
     133,    -1,   100,   132,   178,    98,   178,   176,   133,    -1,
     101,   132,   178,    98,   178,   176,   133,    -1,   102,   132,
     175,   131,   178,   131,   178,   133,    -1,   103,   132,   178,
      98,   178,   175,   133,    -1,   104,   132,   178,    98,   178,
     175,   133,    -1,   105,   132,   175,    28,   178,   133,    -1,
      81,   132,   178,   133,    -1,    83,   132,   178,   133,    -1,
     176,    -1,   177,    -1,    92,    -1,    93,    -1,    94,    -1,
      95,    -1,    96,    -1,    97,    -1,   197,    -1,   198,    -1,
      50,    -1,    29,   190,    -1,    -1,   123,   124,   184,    -1,
      -1,   126,   124,   187,    -1,    -1,    34,    13,    -1,    34,
      13,    35,    13,    -1,    -1,   125,   191,    -1,    -1,   184,
     185,    -1,   186,    -1,   131,   186,    -1,   197,    -1,   187,
     188,    -1,   189,    -1,   131,   189,    -1,   197,    -1,   197,
     127,    -1,   197,   128,    -1,   190,     3,   190,    -1,   190,
       4,   190,    -1,   132,   190,   133,    -1,    32,   132,   190,
     133,    -1,   194,   193,    -1,   191,     3,   191,    -1,   191,
       4,   191,    -1,   132,   191,   133,    -1,    32,   132,   191,
     133,    -1,   194,   192,    -1,   118,   132,   197,   133,    16,
     198,    -1,   119,   132,   197,   133,    16,   198,    -1,   121,
     132,   197,   133,    16,   198,    -1,   120,   132,   197,   133,
      16,   198,    -1,   122,   132,   197,   133,    16,   198,    -1,
     197,    16,   198,    -1,   197,    16,   197,    -1,   197,   194,
      30,   198,     4,   198,    -1,   197,   194,    31,   132,   165,
     133,    -1,   197,    41,    32,    50,    -1,   197,    41,    50,
      -1,   174,    16,   174,    -1,   174,    16,   197,    -1,   174,
      16,   198,    -1,    32,    -1,    -1,   197,    -1,   197,    33,
     197,    -1,   197,   197,    -1,   197,    -1,   118,   132,   197,
     133,    -1,   119,   132,   197,   133,    -1,   121,   132,   197,
     133,    -1,   120,   132,   197,   133,    -1,   122,   132,   197,
     133,    -1,   122,   132,     7,   133,    -1,     7,    -1,   197,
       7,    -1,    12,    -1,   134,    12,   134,    -1,    11,    -1,
     199,    -1,    14,    -1,   200,    -1,    17,    -1,    50,    -1,
     106,   132,   133,    -1,    13,    -1,     6,    13,    -1,     5,
      13,    -1,    15,    -1,     6,    15,    -1,     5,    15,    -1,
      68,    52,   197,   202,   169,    -1,    74,    52,   197,   169,
      -1,   203,   204,   205,   206,   207,   208,    -1,    -1,    69,
     198,    -1,    -1,    70,   198,    -1,    -1,    71,   197,    -1,
      -1,    72,    -1,    -1,    73,   198,    -1,    -1,    75,    -1,
      51,    52,   197,   132,   213,   133,   169,    -1,    51,    56,
     197,    57,   197,   132,   153,   133,   211,   210,   212,   169,
      -1,    62,    52,   197,    -1,    62,    56,   197,    -1,    67,
      52,   197,   169,    -1,    -1,    58,   211,    -1,    59,   211,
      -1,    60,   211,    -1,    -1,    -1,    61,    -1,    53,    -1,
      -1,    -1,    63,    13,    -1,   214,    -1,   214,   131,   222,
      -1,   214,   215,    -1,   216,    -1,   131,   216,    -1,   217,
      -1,   218,   234,   219,   221,   220,   233,    -1,   197,    -1,
      -1,   132,    13,   133,    -1,    -1,    55,   198,    -1,    -1,
      32,    50,    -1,   232,    -1,   223,    -1,   232,   131,   223,
      -1,   223,   224,    -1,   225,    -1,   131,   225,    -1,    64,
      54,   132,   226,   133,    65,   197,   132,   229,   133,    -1,
     226,   227,    -1,   228,    -1,   131,   228,    -1,   197,    -1,
     229,   230,    -1,   231,    -1,   131,   231,    -1,   197,    -1,
      53,    54,   132,   153,   133,   212,    -1,    -1,    21,    -1,
      76,    -1,    77,    -1,    78,    -1,    84,    -1,    86,    -1,
      85,    -1,    79,    -1,    81,    -1,    83,    -1,    80,    -1,
      82,    -1,    88,    -1,    87,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    44,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    58,    65,    73,    79,    88,
      97,   106,   111,   118,   124,   132,   133,   135,   138,   139,
     140,   141,   143,   144,   146,   148,   149,   163,   170,   177,
     184,   189,   194,   200,   205,   210,   215,   220,   225,   231,
     237,   241,   243,   247,   249,   250,   252,   254,   255,   261,
     262,   263,   265,   279,   292,   296,   298,   299,   301,   302,
     304,   310,   318,   319,   322,   323,   329,   336,   337,   343,
     350,   358,   366,   367,   370,   371,   374,   376,   381,   386,
     392,   398,   404,   410,   416,   422,   426,   430,   434,   435,
     437,   444,   451,   459,   466,   473,   480,   491,   498,   505,
     517,   525,   533,   538,   544,   549,   554,   560,   565,   570,
     576,   583,   591,   600,   613,   615,   616,   618,   619,   621,
     625,   629,   631,   632,   634,   635,   637,   639,   645,   646,
     648,   650,   655,   660,   666,   674,   681,   682,   690,   706,
     714,   721,   722,   730,   746,   755,   764,   773,   782,   793,
     804,   815,   831,   857,   865,   873,   881,   891,   900,   904,
     906,   911,   916,   922,   928,   933,   938,   943,   948,   953,
     958,   962,   967,   968,   970,   971,   972,   973,   974,   975,
     976,   989,   990,   999,  1001,  1002,  1011,  1013,  1024,  1031,
    1033,  1034,  1040,  1041,  1048,  1049,  1056,  1057,  1062,  1063,
    1069,  1070,  1075,  1081,  1089,  1095,  1101,  1108,  1109,  1113,
    1117,  1122,  1126,  1127,  1131,  1137,  1142,  1143,  1149,  1150,
    1152,  1153,  1156,  1159,  1165,  1168,  1173,  1174,  1186,  1187,
    1199,  1200,  1205,  1206,  1207,  1209,  1210,  1212,  1214,  1221,
    1222,  1224,  1226,  1232,  1233,  1235,  1237,  1244,  1249,  1250,
    1271,  1275,  1279,  1283,  1287,  1291,  1295,  1300,  1305,  1310,
    1315,  1321,  1327
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
  "REVOKE", "MIN", "MAX", "AVG", "SUM", "COUNT", "GROUP", "BY", "HAVING",
  "ORDER", "ASC", "DESC", "DISTINCT", "';'", "','", "'('", "')'", "'`'",
  "$accept", "command", "alter_statement", "management_statement",
  "user_manager_statement", "privilege_list", "privilege_list_L",
  "privilege", "grantee_list", "grantee_list_L", "grantee",
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
      59,    44,    40,    41,    96
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   135,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   137,   137,   137,   137,   137,
     137,   138,   139,   139,   139,   140,   140,   141,   142,   142,
     142,   142,   143,   143,   144,   145,   146,   147,   147,   148,
     149,   149,   149,   149,   149,   149,   149,   149,   149,   150,
     151,   151,   152,   152,   153,   153,   154,   155,   155,   156,
     156,   156,   157,   157,   157,   157,   158,   158,   159,   159,
     160,   161,   162,   162,   163,   163,   164,   165,   165,   166,
     167,   168,   169,   169,   170,   170,   171,   172,   172,   172,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   173,
     174,   174,   174,   174,   174,   174,   174,   174,   174,   174,
     174,   174,   175,   175,   176,   176,   176,   177,   177,   177,
     178,   178,   178,   179,   179,   180,   180,   181,   181,   182,
     182,   182,   183,   183,   184,   184,   185,   186,   187,   187,
     188,   189,   189,   189,   190,   190,   190,   190,   190,   191,
     191,   191,   191,   191,   192,   192,   192,   192,   192,   193,
     193,   193,   193,   193,   193,   193,   193,   193,   194,   194,
     195,   195,   195,   196,   196,   196,   196,   196,   196,   196,
     196,   196,   197,   197,   198,   198,   198,   198,   198,   198,
     198,   199,   199,   199,   200,   200,   200,   201,   201,   202,
     203,   203,   204,   204,   205,   205,   206,   206,   207,   207,
     208,   208,   209,   209,   209,   209,   209,   210,   210,   210,
     210,   210,   211,   211,   211,   211,   212,   212,   213,   213,
     214,   214,   215,   216,   217,   218,   219,   219,   220,   220,
     221,   221,   222,   222,   222,   223,   223,   224,   225,   226,
     226,   227,   228,   229,   229,   230,   231,   232,   233,   233,
     234,   234,   234,   234,   234,   234,   234,   234,   234,   234,
     234,   234,   234
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     8,     7,     8,     6,     9,
       7,     3,     6,     4,     7,     2,     1,     2,     1,     1,
       1,     1,     2,     1,     2,     1,     8,    15,    15,     3,
       1,     2,     3,     2,     1,     1,     1,     2,     2,    12,
       2,     0,     1,     0,     2,     1,     2,     1,     3,     2,
       1,     2,     6,     7,     4,     0,     0,     1,     0,     1,
       2,     9,     0,     3,     2,     1,     2,     2,     1,     2,
       5,     6,     1,     0,     2,     1,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     2,     1,     1,
       6,     7,     7,     6,     7,     7,     8,     7,     7,     6,
       4,     4,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     0,     3,     0,     3,     0,     2,
       4,     0,     2,     0,     2,     1,     2,     1,     2,     1,
       2,     1,     2,     2,     3,     3,     3,     4,     2,     3,
       3,     3,     4,     2,     6,     6,     6,     6,     6,     3,
       3,     6,     6,     4,     3,     3,     3,     3,     1,     0,
       1,     3,     2,     1,     4,     4,     4,     4,     4,     4,
       1,     2,     1,     3,     1,     1,     1,     1,     1,     1,
       3,     1,     2,     2,     1,     2,     2,     5,     4,     6,
       0,     2,     0,     2,     0,     2,     0,     1,     0,     2,
       0,     1,     7,    12,     3,     3,     4,     0,     2,     2,
       2,     0,     0,     1,     1,     0,     0,     2,     1,     3,
       2,     1,     2,     1,     6,     1,     0,     3,     0,     2,
       0,     2,     1,     1,     3,     2,     1,     2,    10,     2,
       1,     2,     1,     2,     1,     2,     1,     6,     0,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
      51,    40,     0,     0,    44,    46,    45,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    13,    12,    10,    11,     9,     7,
      14,     2,     0,     3,     4,     5,     8,     6,   182,     0,
       0,    41,   170,    43,    47,    48,     0,    50,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    83,     0,    28,    29,    31,    30,     0,
      26,     1,    53,    42,     0,     0,   172,    72,   124,     0,
       0,     0,     0,   214,   215,    83,    39,    83,   200,    83,
       0,     0,     0,    82,    21,     0,     0,     0,    25,    52,
       0,   183,   171,     0,     0,     0,   169,    83,   124,    85,
       0,     0,     0,     0,     0,    23,   216,     0,    83,   202,
     198,     0,     0,     0,     0,     0,     0,     0,     0,    27,
     180,     0,     0,     0,     0,     0,     0,    55,    57,   173,
      53,     0,     0,   168,   169,   123,     0,    80,     0,    84,
      83,     0,    53,   235,     0,   228,   231,   233,     0,     0,
      83,     0,     0,   184,   191,   186,   194,   188,   189,     0,
     201,   185,   187,   197,     0,   204,     0,     0,     0,     0,
       0,     0,    83,     0,     0,     0,     0,     0,     0,     0,
       0,    54,     0,   181,     0,    73,     0,   169,     0,   169,
     169,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   148,   169,    86,    81,     0,     0,
     122,     0,    87,    98,    99,   120,   121,     0,    83,     0,
     230,   260,   261,   262,   266,   269,   267,   270,   268,   263,
     265,   264,   272,   271,   236,     0,    22,   193,   196,   192,
     195,     0,   203,     0,   206,    83,     0,     0,     0,    83,
      83,    18,   124,    33,    35,     0,     0,     0,     0,     0,
       0,   124,    60,    56,    58,     0,     0,    75,     0,   146,
     144,   145,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   168,     0,     0,   191,
     194,   122,    97,   121,   191,   194,    96,     0,     0,     0,
       0,     0,     0,     0,   212,     0,     0,   232,   229,   243,
     246,   242,     0,   240,     0,   190,   205,   207,   208,    16,
      83,    83,     0,    20,    24,     0,    32,    83,   174,   175,
     177,   176,   179,   178,     0,    59,   126,    68,    68,    66,
      61,     0,     0,    83,    74,   147,     0,     0,     0,     0,
       0,     0,     0,     0,   114,   115,   116,   117,   118,   119,
       0,   112,   113,     0,     0,     0,   165,   166,   167,   160,
     159,     0,   164,     0,     0,    95,    93,    94,    92,    90,
      91,     0,     0,     0,     0,   245,     0,     0,     0,   238,
     222,     0,   210,    15,    17,    83,    34,    36,    70,     0,
     133,    69,     0,     0,    67,    68,   124,    76,    71,   110,
     111,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   163,     0,     0,   124,     0,     0,   247,   244,   237,
     241,     0,   258,   224,   223,   217,   209,   211,   199,    19,
       0,   169,   128,     0,    65,     0,   126,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    78,
     126,     0,   252,     0,   250,   239,   259,   234,   222,   222,
     222,   226,   125,   135,   137,   168,   169,   132,     0,     0,
     131,   169,    64,     0,   133,   100,     0,     0,   103,     0,
       0,     0,     0,     0,   109,   161,     0,   162,    77,   133,
     226,     0,     0,   249,   218,   219,   220,     0,    83,     0,
     134,   169,     0,   169,   169,     0,     0,     0,     0,     0,
     153,     0,     0,    83,    65,   169,   128,   101,   102,   104,
     105,     0,   107,   108,    79,   128,   257,   251,     0,   227,
     213,   136,     0,   151,   149,   150,     0,     0,     0,     0,
       0,   127,   139,   141,   129,    49,    62,    65,   131,   106,
     131,     0,   152,     0,     0,     0,     0,     0,     0,   138,
     142,   143,     0,    63,    83,    83,     0,     0,     0,     0,
       0,     0,   140,   130,    38,    37,   256,     0,   254,     0,
       0,     0,     0,     0,     0,   248,   253,   154,   155,   157,
     156,   158,   255
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    23,    24,    25,    26,    69,    98,    70,   262,   336,
     263,    27,    28,    29,    30,    31,    32,   100,   136,   191,
     137,   271,   350,   415,   412,   345,    33,   105,   276,   354,
     468,   508,    34,    35,    94,   108,   149,   109,   222,   223,
     370,   371,   372,   224,   107,   410,   490,   533,   452,   482,
     520,   483,   561,   579,   562,   145,   487,   530,   214,   146,
     272,   138,   225,   303,   171,   172,    36,   118,   119,   175,
     254,   328,   402,   448,    37,   481,   445,   518,   154,   155,
     230,   156,   157,   158,   323,   442,   399,   318,   319,   395,
     320,   473,   513,   474,   597,   606,   598,   321,   477,   244
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -435
static const yytype_int16 yypact[] =
{
     683,  -435,    22,    21,  -435,  -435,  -435,    21,    21,    86,
      77,   126,    21,    84,   161,   121,   151,   183,   187,   162,
     192,   225,   279,   283,  -435,  -435,  -435,  -435,  -435,  -435,
    -435,  -435,   263,  -435,  -435,  -435,  -435,  -435,  -435,    21,
     282,  -435,     3,  -435,  -435,  -435,    21,  -435,    21,   249,
      21,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,   181,    21,  -435,  -435,  -435,  -435,     4,
    -435,  -435,   203,  -435,   204,    21,  -435,    70,   316,    21,
      80,   295,   289,  -435,  -435,   181,  -435,   181,   290,   181,
     131,   284,   328,  -435,  -435,   292,    21,   279,  -435,  -435,
     182,  -435,  -435,   382,   182,   374,    69,   181,    16,  -435,
     401,   404,    21,    21,   421,  -435,  -435,   430,   181,   367,
    -435,   326,   307,   308,   330,   331,   341,    21,   335,  -435,
    -435,   319,   320,   329,   338,   339,   -12,  -435,   424,   451,
     203,    93,   365,   366,    69,   154,   325,  -435,    21,  -435,
     181,   267,   203,  -435,   327,   368,  -435,  -435,   405,   376,
     181,   251,   261,  -435,  -435,  -435,  -435,  -435,  -435,   378,
    -435,  -435,  -435,  -435,   430,   447,    21,    21,    21,    21,
      21,   508,   181,    21,    21,    21,    21,    21,     7,    21,
     182,  -435,    21,  -435,   182,  -435,   430,    69,    39,    69,
      69,   388,   389,   390,   391,   392,   393,   394,   395,   396,
     398,   399,   400,   517,  -435,    90,  -435,  -435,   373,   489,
      12,   536,   356,  -435,  -435,  -435,    18,   182,   181,    81,
    -435,  -435,  -435,  -435,  -435,  -435,  -435,  -435,  -435,  -435,
    -435,  -435,  -435,  -435,   402,   182,  -435,  -435,  -435,  -435,
    -435,   407,  -435,    21,   463,   181,   410,   411,   422,   181,
     181,  -435,    66,  -435,  -435,   412,   419,   426,   427,   428,
     431,    68,   221,  -435,  -435,    -7,   174,  -435,    67,  -435,
     534,  -435,   217,   217,   217,   217,   217,   217,   217,   217,
     299,   217,   217,   299,   593,   241,  -435,    76,    53,  -435,
    -435,  -435,  -435,  -435,  -435,  -435,  -435,    83,   536,   536,
     536,   536,   536,    48,  -435,   511,   512,  -435,  -435,   436,
    -435,   437,   556,   539,   191,  -435,  -435,  -435,   500,  -435,
     181,   181,    21,  -435,  -435,    21,  -435,   181,  -435,  -435,
    -435,  -435,  -435,  -435,    21,  -435,   452,   535,   535,   540,
    -435,    21,   430,   181,  -435,  -435,   448,   449,   454,   485,
     498,   456,   499,   502,  -435,  -435,  -435,  -435,  -435,  -435,
     470,  -435,  -435,   505,   513,   581,  -435,  -435,  -435,  -435,
    -435,   562,  -435,   430,   481,  -435,   144,   144,  -435,  -435,
    -435,    21,   482,   483,   552,  -435,   552,   487,   568,   567,
      54,   430,   549,  -435,  -435,   181,  -435,  -435,  -435,   504,
     506,  -435,    21,    21,  -435,   535,    68,  -435,  -435,  -435,
    -435,   217,   217,   217,   217,   217,   217,   217,   217,   217,
     217,  -435,   625,   430,    68,   182,    21,  -435,   436,  -435,
    -435,   430,   609,  -435,  -435,   260,  -435,  -435,  -435,  -435,
      21,    73,   507,   575,   221,    21,   452,   501,   124,   124,
     514,   242,   242,   515,   299,   299,   516,   430,   208,  -435,
     452,   222,  -435,   243,  -435,  -435,  -435,  -435,    54,    54,
      54,   582,   519,  -435,  -435,   520,    73,   246,   347,   524,
     610,    69,  -435,   594,   506,  -435,   521,   522,  -435,   523,
     525,   217,   526,   527,  -435,  -435,   430,  -435,  -435,   506,
     582,    21,   588,  -435,  -435,  -435,  -435,   644,   181,    21,
    -435,    73,    71,    73,    73,   529,   530,   531,   532,   533,
    -435,    21,   653,   181,   259,    69,   507,  -435,  -435,  -435,
    -435,   538,  -435,  -435,  -435,   507,  -435,  -435,    21,  -435,
    -435,  -435,    78,  -435,   663,  -435,    21,    21,    21,    21,
      21,   541,  -435,   143,   634,  -435,  -435,   259,   610,  -435,
     610,   543,  -435,   544,   545,   546,   547,   548,    21,  -435,
    -435,  -435,   660,  -435,   181,   181,    21,   669,   670,   671,
     672,   673,  -435,  -435,  -435,  -435,  -435,   269,  -435,   430,
     430,   430,   430,   430,    21,  -435,  -435,  -435,  -435,  -435,
    -435,  -435,  -435
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -435,  -435,  -435,  -435,  -435,  -435,  -435,   603,  -435,  -435,
     355,  -435,  -435,  -435,  -435,  -435,  -435,    96,   -95,  -435,
     528,  -271,  -434,  -435,  -276,  -435,  -435,  -435,  -435,  -435,
    -435,  -435,  -435,  -435,   -22,  -435,  -435,   563,   -23,  -135,
    -255,  -133,   -77,  -260,   -91,  -352,  -415,  -165,  -382,  -435,
    -435,   172,  -435,  -435,   132,  -131,  -407,  -435,  -435,  -211,
       0,  -435,    -2,   -87,  -435,  -435,  -435,  -435,  -435,  -435,
    -435,  -435,  -435,  -435,  -435,  -435,   -58,   194,   537,  -435,
    -435,  -143,  -435,  -435,  -435,  -435,  -435,  -435,   317,  -435,
     318,  -435,  -435,   205,  -435,  -435,   111,  -435,  -435,  -435
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -90
static const yytype_int16 yytable[] =
{
      42,    42,    41,    43,   298,    42,    42,    44,    45,   141,
      49,   213,   -89,   198,   269,    38,   189,   150,   -88,    38,
     492,   351,   356,   357,   358,   359,   360,   361,   362,   363,
     170,   373,   374,    38,    38,   257,    75,    42,   375,    73,
      76,   -89,   199,   200,    77,   106,    78,   -88,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    96,    95,   115,   226,   116,   278,   120,   280,   281,
     199,   200,   413,   102,   523,   524,   391,   110,    39,   522,
     416,   523,   524,   383,   384,   147,   317,   252,   308,   309,
     310,   311,   312,    38,   128,   106,   173,   106,   139,   275,
     566,   143,   139,   103,   494,   485,   295,   443,   381,   277,
     153,   159,   536,   111,   552,   444,   554,   555,   509,   190,
     434,   568,   296,    47,   190,   182,   382,   545,   217,    46,
     570,   297,   313,   583,   315,    97,    50,    40,   246,   455,
      51,    40,   -89,   -89,   215,   316,   110,   148,   -88,   -88,
     324,   310,   311,   312,    48,    40,    40,   199,   200,   376,
     261,   457,   458,   459,   460,   461,   462,   463,   464,   465,
     466,   337,   279,    56,   255,   153,   153,   258,   259,   190,
     346,   264,   265,   266,   267,   268,   270,    42,   139,   130,
     274,    52,   139,   121,    38,   302,   306,   335,   307,   344,
     355,   144,   104,    57,   553,   486,   314,   378,   380,   502,
     503,   572,   112,    53,    60,    40,   385,    54,    61,   367,
     368,   369,   161,   162,   190,   139,   195,   153,   163,    38,
     164,   165,   166,   329,   167,    58,   194,   333,   334,    59,
     488,   541,   122,   139,   123,   124,   161,   162,   227,   523,
     524,   326,   163,    38,   164,   165,   166,   347,   167,   348,
      63,   349,   199,   200,   247,   417,   248,   301,    55,    62,
     580,   581,   218,   219,   249,   488,   250,    64,   163,    38,
     164,   165,   166,    71,   167,   386,   387,   388,   389,   390,
      72,   168,   377,   379,    74,   347,   432,   348,    79,   349,
     131,   132,   133,   134,   135,   352,    65,   353,   403,   404,
     488,    93,   488,   488,   446,   407,    40,   220,   478,   479,
     480,    66,   190,   169,   400,   456,    67,    68,   499,   500,
     405,   418,    99,   264,   364,   365,   366,    38,   101,   506,
     471,   507,    42,   470,   408,   106,   469,   169,   201,    42,
     202,    40,   113,   190,   475,   510,   203,   204,   205,   117,
     534,   308,   309,   310,   311,   312,   206,   207,   208,   209,
     210,   211,   212,   169,   511,    40,   512,   126,   218,   219,
     505,   496,   497,   449,   163,    38,   299,   165,   300,    42,
     167,   364,   365,   366,   367,   368,   369,   114,   125,   221,
     604,    40,   605,   584,   567,   585,   201,   127,   202,   140,
      42,    42,   453,   454,   203,   204,   205,   151,   142,   544,
     514,   515,   516,   301,   206,   207,   208,   209,   210,   211,
     212,   152,   160,   139,   472,   161,   162,   174,   176,   177,
     178,   163,   179,   164,   165,   166,   180,   167,   484,   181,
     183,   184,   185,    42,   201,   493,   202,   192,   193,    40,
     228,   186,   203,   204,   205,   525,   526,   527,   528,   529,
     187,   188,   206,   207,   208,   209,   210,   211,   212,   169,
     168,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   218,   219,   550,   196,   197,   229,
     163,    38,   304,   165,   305,   221,   167,    40,   245,   472,
     251,   565,   607,   608,   609,   610,   611,   484,   253,   260,
     282,   283,   284,   285,   286,   287,   288,   289,   290,   563,
     291,   292,   293,   294,   322,   327,   169,   332,   200,   301,
     325,   218,   219,   330,   331,   338,   571,   163,    38,   164,
     165,   166,   339,   167,   573,   574,   575,   576,   577,   340,
     341,   342,   594,   595,   343,   392,   393,   394,   396,   397,
     201,   398,   202,   401,   411,   409,   563,   414,   203,   204,
     205,   419,   420,   422,   596,   421,   301,   424,   206,   207,
     208,   209,   210,   211,   212,   169,   423,   425,   161,   162,
     426,   427,   596,   428,   163,    38,   164,   165,   166,   430,
     167,   429,   431,   433,   435,   436,   316,   201,   440,   202,
     439,   221,   441,    40,   447,   203,   204,   205,   450,   467,
     476,   451,   491,   489,   495,   206,   207,   208,   209,   210,
     211,   212,   169,   168,   532,   517,   501,   498,   531,   504,
     519,   535,   521,   548,   537,   538,   539,   549,   540,   542,
     543,   556,   557,   558,   559,   560,   564,   524,   221,   582,
      40,   569,   578,   593,   201,   586,   202,   587,   588,   589,
     590,   591,   203,   204,   205,   599,   600,   601,   602,   603,
     406,   551,   206,   207,   208,   209,   210,   211,   212,   169,
     129,     1,     2,     3,   546,     4,     5,     6,     7,     8,
     592,   216,   437,   438,   256,   612,   547,     0,   273,     0,
       0,     0,     0,     0,     0,     9,     0,    40,    10,     0,
      11,    12,     0,     0,    13,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    14,     0,     0,     0,    15,
      16,    17,     0,     0,     0,     0,     0,    18,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    19,    20,     0,     0,     0,    21,     0,    22
};

static const yytype_int16 yycheck[] =
{
       2,     3,     2,     3,   215,     7,     8,     7,     8,   104,
      12,   146,     0,   144,     7,    12,    28,   108,     0,    12,
     454,    28,   282,   283,   284,   285,   286,   287,   288,   289,
     117,   291,   292,    12,    12,   178,    33,    39,   293,    39,
      42,    29,     3,     4,    46,    29,    48,    29,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    57,    64,    85,   151,    87,   197,    89,   199,   200,
       3,     4,   348,    75,     3,     4,    28,    79,    56,   486,
     351,     3,     4,    30,    31,   107,   229,   174,     5,     6,
       7,     8,     9,    12,    96,    29,   118,    29,   100,   194,
     534,    32,   104,    33,   456,    32,    16,    53,    32,   196,
     112,   113,   494,    33,   521,    61,   523,   524,   470,   131,
     391,   536,    32,    46,   131,   127,    50,   509,   150,    43,
     545,    41,   227,   567,    53,   131,    52,   134,   160,   415,
      56,   134,   130,   131,   146,    64,   148,   131,   130,   131,
     245,     7,     8,     9,    28,   134,   134,     3,     4,   294,
     182,   421,   422,   423,   424,   425,   426,   427,   428,   429,
     430,   262,   133,    52,   176,   177,   178,   179,   180,   131,
     271,   183,   184,   185,   186,   187,   188,   189,   190,     7,
     192,   107,   194,    62,    12,   218,   219,   131,   221,   131,
     133,   132,   132,    52,   133,   132,   228,   294,   295,   464,
     465,   133,   132,    52,    52,   134,   133,    56,    56,    95,
      96,    97,     5,     6,   131,   227,   133,   229,    11,    12,
      13,    14,    15,   255,    17,    52,   140,   259,   260,    52,
     451,   501,   111,   245,   113,   114,     5,     6,   152,     3,
       4,   253,    11,    12,    13,    14,    15,    36,    17,    38,
      68,    40,     3,     4,    13,   352,    15,    50,   107,   107,
     127,   128,     5,     6,    13,   486,    15,    52,    11,    12,
      13,    14,    15,     0,    17,   308,   309,   310,   311,   312,
      27,    50,   294,   295,    12,    36,   383,    38,    49,    40,
     118,   119,   120,   121,   122,   131,    27,   133,   330,   331,
     521,   130,   523,   524,   401,   337,   134,    50,    58,    59,
      60,    42,   131,   106,   133,   416,    47,    48,   461,   462,
     332,   353,   129,   335,    92,    93,    94,    12,   134,   131,
     435,   133,   344,   434,   344,    29,   433,   106,    81,   351,
      83,   134,    57,   131,   441,   133,    89,    90,    91,    69,
     491,     5,     6,     7,     8,     9,    99,   100,   101,   102,
     103,   104,   105,   106,   131,   134,   133,    49,     5,     6,
     467,   458,   459,   405,    11,    12,    13,    14,    15,   391,
      17,    92,    93,    94,    95,    96,    97,   108,   114,   132,
     131,   134,   133,   568,   535,   570,    81,   115,    83,    27,
     412,   413,   412,   413,    89,    90,    91,    16,    44,   506,
     478,   479,   480,    50,    99,   100,   101,   102,   103,   104,
     105,    27,    11,   435,   436,     5,     6,    70,   112,   132,
     132,    11,   112,    13,    14,    15,   115,    17,   450,   108,
     115,   132,   132,   455,    81,   455,    83,    33,     7,   134,
     133,   132,    89,    90,    91,   118,   119,   120,   121,   122,
     132,   132,    99,   100,   101,   102,   103,   104,   105,   106,
      50,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,     5,     6,   518,   132,   132,   131,
      11,    12,    13,    14,    15,   132,    17,   134,   132,   511,
     132,   533,   599,   600,   601,   602,   603,   519,    71,    11,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   531,
     132,   132,   132,    16,   132,    72,   106,   115,     4,    50,
     133,     5,     6,   133,   133,   133,   548,    11,    12,    13,
      14,    15,   133,    17,   556,   557,   558,   559,   560,   133,
     133,   133,   584,   585,   133,    54,    54,   131,   131,    13,
      81,    32,    83,    73,    39,   123,   578,    37,    89,    90,
      91,   133,   133,    98,   586,   131,    50,   131,    99,   100,
     101,   102,   103,   104,   105,   106,    98,    98,     5,     6,
      98,   131,   604,    98,    11,    12,    13,    14,    15,    28,
      17,    98,    50,   132,   132,   132,    64,    81,    50,    83,
     133,   132,    55,   134,    75,    89,    90,    91,   124,     4,
      21,   125,    57,   126,   133,    99,   100,   101,   102,   103,
     104,   105,   106,    50,    34,    63,   131,   133,   124,   133,
     131,    57,   132,    65,   133,   133,   133,    13,   133,   133,
     133,   132,   132,   132,   132,   132,    13,     4,   132,    35,
     134,   133,   131,    13,    81,   132,    83,   133,   133,   133,
     133,   133,    89,    90,    91,    16,    16,    16,    16,    16,
     335,   519,    99,   100,   101,   102,   103,   104,   105,   106,
      97,    18,    19,    20,   510,    22,    23,    24,    25,    26,
     578,   148,   394,   396,   177,   604,   511,    -1,   190,    -1,
      -1,    -1,    -1,    -1,    -1,    42,    -1,   134,    45,    -1,
      47,    48,    -1,    -1,    51,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    62,    -1,    -1,    -1,    66,
      67,    68,    -1,    -1,    -1,    -1,    -1,    74,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   109,   110,    -1,    -1,    -1,   114,    -1,   116
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    18,    19,    20,    22,    23,    24,    25,    26,    42,
      45,    47,    48,    51,    62,    66,    67,    68,    74,   109,
     110,   114,   116,   136,   137,   138,   139,   146,   147,   148,
     149,   150,   151,   161,   167,   168,   201,   209,    12,    56,
     134,   195,   197,   195,   195,   195,    43,    46,    28,   197,
      52,    56,   107,    52,    56,   107,    52,    52,    52,    52,
      52,    56,   107,    68,    52,    27,    42,    47,    48,   140,
     142,     0,    27,   195,    12,    33,   197,   197,   197,    49,
     197,   197,   197,   197,   197,   197,   197,   197,   197,   197,
     197,   197,   197,   130,   169,   197,    57,   131,   141,   129,
     152,   134,   197,    33,   132,   162,    29,   179,   170,   172,
     197,    33,   132,    57,   108,   169,   169,    69,   202,   203,
     169,    62,   111,   113,   114,   114,    49,   115,   197,   142,
       7,   118,   119,   120,   121,   122,   153,   155,   196,   197,
      27,   153,    44,    32,   132,   190,   194,   169,   131,   171,
     179,    16,    27,   197,   213,   214,   216,   217,   218,   197,
      11,     5,     6,    11,    13,    14,    15,    17,    50,   106,
     198,   199,   200,   169,    70,   204,   112,   132,   132,   112,
     115,   108,   197,   115,   132,   132,   132,   132,   132,    28,
     131,   154,    33,     7,   152,   133,   132,   132,   190,     3,
       4,    81,    83,    89,    90,    91,    99,   100,   101,   102,
     103,   104,   105,   174,   193,   197,   172,   169,     5,     6,
      50,   132,   173,   174,   178,   197,   198,   152,   133,   131,
     215,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,   234,   132,   169,    13,    15,    13,
      15,   132,   198,    71,   205,   197,   213,   216,   197,   197,
      11,   169,   143,   145,   197,   197,   197,   197,   197,     7,
     197,   156,   195,   155,   197,   153,   163,   198,   190,   133,
     190,   190,   132,   132,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   132,    16,    16,    32,    41,   194,    13,
      15,    50,   173,   198,    13,    15,   173,   173,     5,     6,
       7,     8,     9,   153,   169,    53,    64,   216,   222,   223,
     225,   232,   132,   219,   153,   133,   197,    72,   206,   169,
     133,   133,   115,   169,   169,   131,   144,   179,   133,   133,
     133,   133,   133,   133,   131,   160,   179,    36,    38,    40,
     157,    28,   131,   133,   164,   133,   178,   178,   178,   178,
     178,   178,   178,   178,    92,    93,    94,    95,    96,    97,
     175,   176,   177,   178,   178,   175,   174,   197,   198,   197,
     198,    32,    50,    30,    31,   133,   173,   173,   173,   173,
     173,    28,    54,    54,   131,   224,   131,    13,    32,   221,
     133,    73,   207,   169,   169,   197,   145,   169,   195,   123,
     180,    39,   159,   159,    37,   158,   156,   198,   169,   133,
     133,   131,    98,    98,   131,    98,    98,   131,    98,    98,
      28,    50,   198,   132,   156,   132,   132,   225,   223,   133,
      50,    55,   220,    53,    61,   211,   198,    75,   208,   169,
     124,   125,   183,   195,   195,   159,   179,   178,   178,   178,
     178,   178,   178,   178,   178,   178,   178,     4,   165,   198,
     179,   153,   197,   226,   228,   198,    21,   233,    58,    59,
      60,   210,   184,   186,   197,    32,   132,   191,   194,   126,
     181,    57,   157,   195,   180,   133,   177,   177,   133,   176,
     176,   131,   175,   175,   133,   198,   131,   133,   166,   180,
     133,   131,   133,   227,   211,   211,   211,    63,   212,   131,
     185,   132,   191,     3,     4,   118,   119,   120,   121,   122,
     192,   124,    34,   182,   190,    57,   183,   133,   133,   133,
     133,   178,   133,   133,   198,   183,   212,   228,    65,    13,
     169,   186,   191,   133,   191,   191,   132,   132,   132,   132,
     132,   187,   189,   197,    13,   169,   157,   190,   181,   133,
     181,   197,   133,   197,   197,   197,   197,   197,   131,   188,
     127,   128,    35,   157,   182,   182,   132,   133,   133,   133,
     133,   133,   189,    13,   169,   169,   197,   229,   231,    16,
      16,    16,    16,    16,   131,   133,   230,   198,   198,   198,
     198,   198,   231
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

  case 28:

/* Line 1464 of yacc.c  */
#line 138 "dmlyacc.yxx"
    { parsedData->insertPrivilege(PRIV_SELECT); }
    break;

  case 29:

/* Line 1464 of yacc.c  */
#line 139 "dmlyacc.yxx"
    { parsedData->insertPrivilege(PRIV_INSERT); }
    break;

  case 30:

/* Line 1464 of yacc.c  */
#line 140 "dmlyacc.yxx"
    { parsedData->insertPrivilege(PRIV_UPDATE); }
    break;

  case 31:

/* Line 1464 of yacc.c  */
#line 141 "dmlyacc.yxx"
    { parsedData->insertPrivilege(PRIV_DELETE); }
    break;

  case 35:

/* Line 1464 of yacc.c  */
#line 148 "dmlyacc.yxx"
    { parsedData->insertGrantee((yyvsp[(1) - (1)].stringval)); }
    break;

  case 36:

/* Line 1464 of yacc.c  */
#line 150 "dmlyacc.yxx"
    {
            parsedData->setStmtType(DclStatement);
            parsedData->setTableName((yyvsp[(4) - (8)].stringval));
            parsedData->constructDclNodes(GRANTACCESS);
    }
    break;

  case 37:

/* Line 1464 of yacc.c  */
#line 164 "dmlyacc.yxx"
    {
            parsedData->setStmtType(CopyTableStatement);
            parsedData->setPKTableName((yyvsp[(3) - (15)].stringval));
            parsedData->setCreateTbl();
            free((yyvsp[(3) - (15)].stringval));
        }
    break;

  case 38:

/* Line 1464 of yacc.c  */
#line 171 "dmlyacc.yxx"
    {
            parsedData->setStmtType(CopyTableStatement);
            parsedData->setPKTableName((yyvsp[(3) - (15)].stringval));
            free((yyvsp[(3) - (15)].stringval));
        }
    break;

  case 39:

/* Line 1464 of yacc.c  */
#line 178 "dmlyacc.yxx"
    {
            parsedData->setStmtType(CompactTableStatement);
            parsedData->setTableName((yyvsp[(3) - (3)].stringval));
            free((yyvsp[(3) - (3)].stringval));
        }
    break;

  case 40:

/* Line 1464 of yacc.c  */
#line 185 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetTables);
	}
    break;

  case 41:

/* Line 1464 of yacc.c  */
#line 190 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetColumns);
        }
    break;

  case 42:

/* Line 1464 of yacc.c  */
#line 195 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetIndexes);
                   
        }
    break;

  case 43:

/* Line 1464 of yacc.c  */
#line 201 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetPriIndex);
        }
    break;

  case 44:

/* Line 1464 of yacc.c  */
#line 206 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetCatalogs);
        }
    break;

  case 45:

/* Line 1464 of yacc.c  */
#line 211 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetTableType);
        }
    break;

  case 46:

/* Line 1464 of yacc.c  */
#line 216 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetDataType);
        }
    break;

  case 47:

/* Line 1464 of yacc.c  */
#line 221 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetImportKey);
        }
    break;

  case 48:

/* Line 1464 of yacc.c  */
#line 226 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetExportKey);
        }
    break;

  case 49:

/* Line 1464 of yacc.c  */
#line 232 "dmlyacc.yxx"
    {
            parsedData->setStmtType(SelectStatement);
            parsedData->setCacheWorthy(true);
        }
    break;

  case 50:

/* Line 1464 of yacc.c  */
#line 238 "dmlyacc.yxx"
    {
           parsedData->setExplain();
	}
    break;

  case 52:

/* Line 1464 of yacc.c  */
#line 244 "dmlyacc.yxx"
    { 
            parsedData->setDistinct();
        }
    break;

  case 58:

/* Line 1464 of yacc.c  */
#line 256 "dmlyacc.yxx"
    {
            parsedData->insertFieldAlias((char*)(yyvsp[(3) - (3)].stringval));
            free((char*)(yyvsp[(3) - (3)].stringval));
        }
    break;

  case 62:

/* Line 1464 of yacc.c  */
#line 266 "dmlyacc.yxx"
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

  case 63:

/* Line 1464 of yacc.c  */
#line 280 "dmlyacc.yxx"
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

  case 64:

/* Line 1464 of yacc.c  */
#line 293 "dmlyacc.yxx"
    {
            parsedData->insertJoinType(INNER_JOIN);
        }
    break;

  case 70:

/* Line 1464 of yacc.c  */
#line 305 "dmlyacc.yxx"
    {
            parsedData->insertJoinType(INNER_JOIN);
        }
    break;

  case 71:

/* Line 1464 of yacc.c  */
#line 311 "dmlyacc.yxx"
    {
            parsedData->setStmtType(InsertStatement);
            parsedData->setTableName((yyvsp[(3) - (9)].stringval)); 
            free((yyvsp[(3) - (9)].stringval));
        }
    break;

  case 75:

/* Line 1464 of yacc.c  */
#line 324 "dmlyacc.yxx"
    {
            parsedData->insertValue((char*)(yyvsp[(1) - (1)].stringval));
            free((yyvsp[(1) - (1)].stringval));
        }
    break;

  case 76:

/* Line 1464 of yacc.c  */
#line 330 "dmlyacc.yxx"
    {
            parsedData->insertValue((char*)(yyvsp[(2) - (2)].stringval));
            free((yyvsp[(2) - (2)].stringval));
        }
    break;

  case 78:

/* Line 1464 of yacc.c  */
#line 338 "dmlyacc.yxx"
    {
            parsedData->insertInValue((char*)(yyvsp[(1) - (1)].stringval));
            free((yyvsp[(1) - (1)].stringval));
        }
    break;

  case 79:

/* Line 1464 of yacc.c  */
#line 344 "dmlyacc.yxx"
    {
            parsedData->insertInValue((char*)(yyvsp[(2) - (2)].stringval));
            free((yyvsp[(2) - (2)].stringval));
        }
    break;

  case 80:

/* Line 1464 of yacc.c  */
#line 351 "dmlyacc.yxx"
    {
            parsedData->setStmtType(DeleteStatement);
            parsedData->setTableName((yyvsp[(3) - (5)].stringval)); 
            free((yyvsp[(3) - (5)].stringval));
	}
    break;

  case 81:

/* Line 1464 of yacc.c  */
#line 359 "dmlyacc.yxx"
    {
            parsedData->setStmtType(UpdateStatement);
            parsedData->setTableName((yyvsp[(2) - (6)].stringval)); 
            free( (yyvsp[(2) - (6)].stringval) );
	}
    break;

  case 87:

/* Line 1464 of yacc.c  */
#line 377 "dmlyacc.yxx"
    {
           parsedData->insertUpdateExpression( (char*) (yyvsp[(1) - (3)].stringval), (Expression* ) (yyvsp[(3) - (3)].Expression));
           free( (yyvsp[(1) - (3)].stringval) ); free((yyvsp[(2) - (3)].stringval));
        }
    break;

  case 88:

/* Line 1464 of yacc.c  */
#line 382 "dmlyacc.yxx"
    { 
            parsedData->insertUpdateValue( (char*) (yyvsp[(1) - (3)].stringval), (char*) (yyvsp[(3) - (3)].stringval));
            free( (yyvsp[(1) - (3)].stringval) ); free((yyvsp[(2) - (3)].stringval));free( (yyvsp[(3) - (3)].stringval) ); 
        }
    break;

  case 89:

/* Line 1464 of yacc.c  */
#line 387 "dmlyacc.yxx"
    {
            parsedData->insertUpdateValue( (char*) (yyvsp[(1) - (3)].stringval), (char*) (yyvsp[(3) - (3)].stringval));
            free( (yyvsp[(1) - (3)].stringval) ); free((yyvsp[(2) - (3)].stringval));free( (yyvsp[(3) - (3)].stringval) );
        }
    break;

  case 90:

/* Line 1464 of yacc.c  */
#line 393 "dmlyacc.yxx"
    {
            Expression* exp;
            exp=parsedData->insertExpression((Expression *)(yyvsp[(1) - (3)].Expression), division, (Expression *)(yyvsp[(3) - (3)].Expression));
            (yyval.Expression)=exp;
        }
    break;

  case 91:

/* Line 1464 of yacc.c  */
#line 399 "dmlyacc.yxx"
    {
            Expression* exp;
            exp=parsedData->insertExpression((Expression *)(yyvsp[(1) - (3)].Expression), modulus, (Expression *)(yyvsp[(3) - (3)].Expression));
            (yyval.Expression)=exp;
        }
    break;

  case 92:

/* Line 1464 of yacc.c  */
#line 405 "dmlyacc.yxx"
    {
            Expression* exp;
            exp=parsedData->insertExpression((Expression *)(yyvsp[(1) - (3)].Expression), multiplication, (Expression *)(yyvsp[(3) - (3)].Expression));
            (yyval.Expression)=exp;
        }
    break;

  case 93:

/* Line 1464 of yacc.c  */
#line 411 "dmlyacc.yxx"
    {
            Expression* exp;
            exp=parsedData->insertExpression((Expression *)(yyvsp[(1) - (3)].Expression), addition, (Expression *)(yyvsp[(3) - (3)].Expression));
            (yyval.Expression)=exp;
        }
    break;

  case 94:

/* Line 1464 of yacc.c  */
#line 417 "dmlyacc.yxx"
    {
            Expression* exp;
            exp=parsedData->insertExpression((Expression *)(yyvsp[(1) - (3)].Expression), subtraction, (Expression *)(yyvsp[(3) - (3)].Expression));
            (yyval.Expression)=exp;
        }
    break;

  case 95:

/* Line 1464 of yacc.c  */
#line 423 "dmlyacc.yxx"
    {
            (yyval.Expression)=(yyvsp[(2) - (3)].Expression);
        }
    break;

  case 96:

/* Line 1464 of yacc.c  */
#line 427 "dmlyacc.yxx"
    {
            (yyval.Expression) = (yyvsp[(2) - (2)].Expression);
        }
    break;

  case 97:

/* Line 1464 of yacc.c  */
#line 431 "dmlyacc.yxx"
    {
            (yyval.Expression) = (yyvsp[(2) - (2)].Expression);
        }
    break;

  case 100:

/* Line 1464 of yacc.c  */
#line 438 "dmlyacc.yxx"
    {
              Expression* exp;
              parsedData->setFunctionType(DATEDIFF);
              exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (6)].Expression), DATEDIFF, (Expression *)(yyvsp[(5) - (6)].Expression));
            (yyval.Expression)=exp;
        }
    break;

  case 101:

/* Line 1464 of yacc.c  */
#line 445 "dmlyacc.yxx"
    {
	         Expression* exp;
             parsedData->setFunctionType((*(FunctionType *)(yyvsp[(6) - (7)].FunctionType)));
             exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (7)].Expression), (*(FunctionType *)(yyvsp[(6) - (7)].FunctionType)), (Expression *)(yyvsp[(5) - (7)].Expression));
             (yyval.Expression)=exp;
	    }
    break;

  case 102:

/* Line 1464 of yacc.c  */
#line 452 "dmlyacc.yxx"
    {
             Expression* exp;
             //parsedData->setFunctionType((*(FunctionType *)$6));
             parsedData->setFunctionType((FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+3));
             exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (7)].Expression), (FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+3), (Expression *)(yyvsp[(5) - (7)].Expression));
             (yyval.Expression)=exp;
        }
    break;

  case 103:

/* Line 1464 of yacc.c  */
#line 460 "dmlyacc.yxx"
    {
              Expression* exp;
              parsedData->setFunctionType(TIMEDIFF);
              exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (6)].Expression), TIMEDIFF, (Expression *)(yyvsp[(5) - (6)].Expression));
            (yyval.Expression)=exp;
        }
    break;

  case 104:

/* Line 1464 of yacc.c  */
#line 467 "dmlyacc.yxx"
    {
             Expression* exp;
             parsedData->setFunctionType((*(FunctionType *)(yyvsp[(6) - (7)].FunctionType)));
             exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (7)].Expression), (*(FunctionType *)(yyvsp[(6) - (7)].FunctionType)), (Expression *)(yyvsp[(5) - (7)].Expression));
             (yyval.Expression)=exp;
        }
    break;

  case 105:

/* Line 1464 of yacc.c  */
#line 474 "dmlyacc.yxx"
    {
             Expression* exp;
             parsedData->setFunctionType((FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+3));
             exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (7)].Expression), (FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+3), (Expression *)(yyvsp[(5) - (7)].Expression));
             (yyval.Expression)=exp;
        }
    break;

  case 106:

/* Line 1464 of yacc.c  */
#line 481 "dmlyacc.yxx"
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

  case 107:

/* Line 1464 of yacc.c  */
#line 492 "dmlyacc.yxx"
    {
             Expression* exp;
             parsedData->setFunctionType((FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+12));
             exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (7)].Expression), (FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+12), (Expression *)(yyvsp[(5) - (7)].Expression));
             (yyval.Expression)=exp;
        }
    break;

  case 108:

/* Line 1464 of yacc.c  */
#line 499 "dmlyacc.yxx"
    {
             Expression* exp;
             parsedData->setFunctionType((FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+15));
             exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (7)].Expression), (FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+15), (Expression *)(yyvsp[(5) - (7)].Expression));
             (yyval.Expression)=exp;
        }
    break;

  case 109:

/* Line 1464 of yacc.c  */
#line 506 "dmlyacc.yxx"
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

  case 110:

/* Line 1464 of yacc.c  */
#line 518 "dmlyacc.yxx"
    {
            Expression* exp;
            parsedData->setFunctionType(DATEFROMTIMESTAMP);
            exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (4)].Expression), DATEFROMTIMESTAMP, NULL);
            (yyval.Expression)=exp;

        }
    break;

  case 111:

/* Line 1464 of yacc.c  */
#line 526 "dmlyacc.yxx"
    {
            Expression* exp;
            parsedData->setFunctionType(TIMEFROMTIMESTAMP);
            exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (4)].Expression), TIMEFROMTIMESTAMP, NULL);
            (yyval.Expression)=exp;
        }
    break;

  case 112:

/* Line 1464 of yacc.c  */
#line 534 "dmlyacc.yxx"
    {
           FunctionType val = *(FunctionType *)(yyvsp[(1) - (1)].FunctionType);
           (yyval.FunctionType) = &val;
        }
    break;

  case 113:

/* Line 1464 of yacc.c  */
#line 539 "dmlyacc.yxx"
    {
           FunctionType val = *(FunctionType *)(yyvsp[(1) - (1)].FunctionType);
           (yyval.FunctionType) = &val;
        }
    break;

  case 114:

/* Line 1464 of yacc.c  */
#line 545 "dmlyacc.yxx"
    { 
             FunctionType val = TIMEADDWITHHOUR;
             (yyval.FunctionType) = &val;
        }
    break;

  case 115:

/* Line 1464 of yacc.c  */
#line 550 "dmlyacc.yxx"
    {
             FunctionType val = TIMEADDWITHMIN;
             (yyval.FunctionType) = &val;
        }
    break;

  case 116:

/* Line 1464 of yacc.c  */
#line 555 "dmlyacc.yxx"
    {
             FunctionType val = TIMEADDWITHSEC;
             (yyval.FunctionType) = &val;
        }
    break;

  case 117:

/* Line 1464 of yacc.c  */
#line 561 "dmlyacc.yxx"
    {
	        FunctionType val = DATEADDWITHYEAR;
            (yyval.FunctionType) = &val;
	    }
    break;

  case 118:

/* Line 1464 of yacc.c  */
#line 566 "dmlyacc.yxx"
    {
	        FunctionType val = DATEADDWITHMON;
            (yyval.FunctionType) = &val;
        }
    break;

  case 119:

/* Line 1464 of yacc.c  */
#line 571 "dmlyacc.yxx"
    {
            FunctionType val = DATEADDWITHDAY;
            (yyval.FunctionType) = &val;
        }
    break;

  case 120:

/* Line 1464 of yacc.c  */
#line 577 "dmlyacc.yxx"
    {
            Expression* exp;
            exp=parsedData->insertExpression((char *)(yyvsp[(1) - (1)].stringval));
            free((yyvsp[(1) - (1)].stringval));
            (yyval.Expression)=exp;
        }
    break;

  case 121:

/* Line 1464 of yacc.c  */
#line 584 "dmlyacc.yxx"
    {
            Expression* exp;
            bool flag = false;
            exp=parsedData->insertExpression((char *)(yyvsp[(1) - (1)].stringval), flag);
            free((yyvsp[(1) - (1)].stringval));
            (yyval.Expression)=exp;
        }
    break;

  case 122:

/* Line 1464 of yacc.c  */
#line 592 "dmlyacc.yxx"
    {
            Expression* exp;
            exp=parsedData->insertExpression("NULL");
            free((yyvsp[(1) - (1)].stringval));
            (yyval.Expression)=exp;
        }
    break;

  case 123:

/* Line 1464 of yacc.c  */
#line 601 "dmlyacc.yxx"
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

  case 129:

/* Line 1464 of yacc.c  */
#line 622 "dmlyacc.yxx"
    {
            parsedData->setLimit(atoi((yyvsp[(2) - (2)].stringval)), 0);
        }
    break;

  case 130:

/* Line 1464 of yacc.c  */
#line 626 "dmlyacc.yxx"
    {
            parsedData->setLimit(atoi((yyvsp[(2) - (4)].stringval)), atoi((yyvsp[(4) - (4)].stringval)));
        }
    break;

  case 137:

/* Line 1464 of yacc.c  */
#line 640 "dmlyacc.yxx"
    {
            parsedData->insertGroupField((char*)(yyvsp[(1) - (1)].stringval));
            free( (yyvsp[(1) - (1)].stringval) );
        }
    break;

  case 141:

/* Line 1464 of yacc.c  */
#line 651 "dmlyacc.yxx"
    {
            parsedData->insertOrderByField((char*)(yyvsp[(1) - (1)].stringval));
            free( (yyvsp[(1) - (1)].stringval) );
        }
    break;

  case 142:

/* Line 1464 of yacc.c  */
#line 656 "dmlyacc.yxx"
    {
            parsedData->insertOrderByField((char*)(yyvsp[(1) - (2)].stringval));
            free( (yyvsp[(1) - (2)].stringval) );
        }
    break;

  case 143:

/* Line 1464 of yacc.c  */
#line 661 "dmlyacc.yxx"
    {
            parsedData->insertOrderByField((char*)(yyvsp[(1) - (2)].stringval), true);
            free( (yyvsp[(1) - (2)].stringval) );
        }
    break;

  case 144:

/* Line 1464 of yacc.c  */
#line 667 "dmlyacc.yxx"
    {
            Predicate *pred;
            pred = parsedData->insertPredicate((Predicate*) (yyvsp[(1) - (3)].predicate), OpOr, (Predicate*) (yyvsp[(3) - (3)].predicate));
            //parsedData->setCondition((Predicate*)pred);
            (yyval.predicate)= pred;

        }
    break;

  case 145:

/* Line 1464 of yacc.c  */
#line 675 "dmlyacc.yxx"
    {
            Predicate *pred;
            pred = parsedData->insertPredicate((Predicate*) (yyvsp[(1) - (3)].predicate), OpAnd, (Predicate*) (yyvsp[(3) - (3)].predicate));
            //parsedData->setCondition((Predicate*)pred);
            (yyval.predicate)= pred;
        }
    break;

  case 146:

/* Line 1464 of yacc.c  */
#line 681 "dmlyacc.yxx"
    { (yyval.predicate)=(yyvsp[(2) - (3)].predicate); }
    break;

  case 147:

/* Line 1464 of yacc.c  */
#line 683 "dmlyacc.yxx"
    {
            Predicate *pred;
            pred = parsedData->insertPredicate((Predicate*) (yyvsp[(3) - (4)].predicate), OpNot, NULL);
            //parsedData->setCondition((Predicate*)pred);
            (yyval.predicate)= pred;

        }
    break;

  case 148:

/* Line 1464 of yacc.c  */
#line 691 "dmlyacc.yxx"
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

  case 149:

/* Line 1464 of yacc.c  */
#line 707 "dmlyacc.yxx"
    {
            Predicate *pred;
            pred = parsedData->insertPredicate((Predicate*) (yyvsp[(1) - (3)].predicate), OpOr, (Predicate*) (yyvsp[(3) - (3)].predicate));
            parsedData->setHavingCondition((Predicate*)pred);
            (yyval.predicate)= pred;

        }
    break;

  case 150:

/* Line 1464 of yacc.c  */
#line 715 "dmlyacc.yxx"
    {
            Predicate *pred;
            pred = parsedData->insertPredicate((Predicate*) (yyvsp[(1) - (3)].predicate), OpAnd, (Predicate*) (yyvsp[(3) - (3)].predicate));
            parsedData->setHavingCondition((Predicate*)pred);
            (yyval.predicate)= pred;
        }
    break;

  case 151:

/* Line 1464 of yacc.c  */
#line 721 "dmlyacc.yxx"
    { (yyval.predicate)=(yyvsp[(2) - (3)].predicate); }
    break;

  case 152:

/* Line 1464 of yacc.c  */
#line 723 "dmlyacc.yxx"
    {
            Predicate *pred;
            pred = parsedData->insertPredicate((Predicate*) (yyvsp[(3) - (4)].predicate), OpNot, NULL);
            parsedData->setHavingCondition((Predicate*)pred);
            (yyval.predicate)= pred;

        }
    break;

  case 153:

/* Line 1464 of yacc.c  */
#line 731 "dmlyacc.yxx"
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

  case 154:

/* Line 1464 of yacc.c  */
#line 747 "dmlyacc.yxx"
    {
            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(5) - (6)].stringval));
            Predicate *pred;
            void **ptr = parsedData->insertCondValueAndGetPtr((char*)(yyvsp[(3) - (6)].stringval), (char*)(yyvsp[(6) - (6)].stringval), false, AGG_MIN, true);
            pred = parsedData->insertPredicate((char*) (yyvsp[(3) - (6)].stringval), op, ptr, AGG_MIN);
            free( (yyvsp[(1) - (6)].stringval) ); free ((yyvsp[(3) - (6)].stringval)); free ((yyvsp[(5) - (6)].stringval)); free ((yyvsp[(6) - (6)].stringval));
            (yyval.predicate)=pred;
        }
    break;

  case 155:

/* Line 1464 of yacc.c  */
#line 756 "dmlyacc.yxx"
    {
            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(5) - (6)].stringval));
            Predicate *pred;
            void **ptr = parsedData->insertCondValueAndGetPtr((char*)(yyvsp[(3) - (6)].stringval), (char*)(yyvsp[(6) - (6)].stringval), false, AGG_MAX, true);
            pred = parsedData->insertPredicate((char*) (yyvsp[(3) - (6)].stringval), op, ptr, AGG_MAX);
            free( (yyvsp[(1) - (6)].stringval) ); free ((yyvsp[(3) - (6)].stringval)); free ((yyvsp[(5) - (6)].stringval)); free ((yyvsp[(6) - (6)].stringval));
            (yyval.predicate)=pred;
        }
    break;

  case 156:

/* Line 1464 of yacc.c  */
#line 765 "dmlyacc.yxx"
    {
            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(5) - (6)].stringval));
            Predicate *pred;
            void **ptr = parsedData->insertCondValueAndGetPtr((char*)(yyvsp[(3) - (6)].stringval), (char*)(yyvsp[(6) - (6)].stringval), false, AGG_SUM, true);
            pred = parsedData->insertPredicate((char*) (yyvsp[(3) - (6)].stringval), op, ptr, AGG_SUM);
            free( (yyvsp[(1) - (6)].stringval) ); free ((yyvsp[(3) - (6)].stringval)); free ((yyvsp[(5) - (6)].stringval)); free ((yyvsp[(6) - (6)].stringval));
            (yyval.predicate)=pred;
        }
    break;

  case 157:

/* Line 1464 of yacc.c  */
#line 774 "dmlyacc.yxx"
    {
            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(5) - (6)].stringval));
            Predicate *pred;
            void **ptr = parsedData->insertCondValueAndGetPtr((char*)(yyvsp[(3) - (6)].stringval), (char*)(yyvsp[(6) - (6)].stringval), false, AGG_AVG, true);
            pred = parsedData->insertPredicate((char*) (yyvsp[(3) - (6)].stringval), op, ptr, AGG_AVG);
            free( (yyvsp[(1) - (6)].stringval) ); free ((yyvsp[(3) - (6)].stringval)); free ((yyvsp[(5) - (6)].stringval)); free ((yyvsp[(6) - (6)].stringval));
            (yyval.predicate)=pred;
        }
    break;

  case 158:

/* Line 1464 of yacc.c  */
#line 783 "dmlyacc.yxx"
    {
            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(5) - (6)].stringval));
            Predicate *pred;
            void **ptr = parsedData->insertCondValueAndGetPtr((char*)(yyvsp[(3) - (6)].stringval), (char*)(yyvsp[(6) - (6)].stringval), false, AGG_COUNT, true);
            pred = parsedData->insertPredicate((char*) (yyvsp[(3) - (6)].stringval), op, ptr, AGG_COUNT);
            free( (yyvsp[(1) - (6)].stringval) ); free ((yyvsp[(3) - (6)].stringval)); free ((yyvsp[(5) - (6)].stringval)); free ((yyvsp[(6) - (6)].stringval));
            (yyval.predicate)=pred;
        }
    break;

  case 159:

/* Line 1464 of yacc.c  */
#line 794 "dmlyacc.yxx"
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

  case 160:

/* Line 1464 of yacc.c  */
#line 805 "dmlyacc.yxx"
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

  case 161:

/* Line 1464 of yacc.c  */
#line 816 "dmlyacc.yxx"
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

  case 162:

/* Line 1464 of yacc.c  */
#line 832 "dmlyacc.yxx"
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

  case 163:

/* Line 1464 of yacc.c  */
#line 858 "dmlyacc.yxx"
    {
            Predicate *pred;
            parsedData->insertCondValue((char*) (yyvsp[(1) - (4)].stringval));
            pred = parsedData->insertNullPredicate((char*) (yyvsp[(1) - (4)].stringval), OpIsNull, false);
            free( (yyvsp[(1) - (4)].stringval) ); free((yyvsp[(2) - (4)].stringval)); free( (yyvsp[(3) - (4)].stringval) );
            (yyval.predicate)=pred;  
        }
    break;

  case 164:

/* Line 1464 of yacc.c  */
#line 866 "dmlyacc.yxx"
    {
            Predicate *pred;
            parsedData->insertCondValue((char*) (yyvsp[(1) - (3)].stringval));
            pred = parsedData->insertNullPredicate((char*) (yyvsp[(1) - (3)].stringval), OpIsNull, true);
            free( (yyvsp[(1) - (3)].stringval) ); free((yyvsp[(2) - (3)].stringval)); free( (yyvsp[(3) - (3)].stringval) );
            (yyval.predicate)=pred;  
        }
    break;

  case 165:

/* Line 1464 of yacc.c  */
#line 874 "dmlyacc.yxx"
    {
            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(2) - (3)].stringval));
            Predicate *pred;
            pred = parsedData->insertPredicate(((Expression*)(yyvsp[(1) - (3)].Expression)), op, ((Expression*)(yyvsp[(3) - (3)].Expression)));
            (yyval.predicate)=pred;
 
        }
    break;

  case 166:

/* Line 1464 of yacc.c  */
#line 882 "dmlyacc.yxx"
    {

            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(2) - (3)].stringval));
            parsedData->insertCondValue((char*) (yyvsp[(3) - (3)].stringval));
            Predicate *pred;
            pred = parsedData->insertPredicate(((Expression*)(yyvsp[(1) - (3)].Expression)), op, (char*) (yyvsp[(3) - (3)].stringval));
            (yyval.predicate)=pred;
            
        }
    break;

  case 167:

/* Line 1464 of yacc.c  */
#line 892 "dmlyacc.yxx"
    {
            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(2) - (3)].stringval));
            void **ptr = parsedData->insertCondValueAndGetPtr((char*)"dummy", (char*)(yyvsp[(3) - (3)].stringval), false, AGG_UNKNOWN, false, true);
            Predicate *pred;
            pred = parsedData->insertPredicate(((Expression*)(yyvsp[(1) - (3)].Expression)), op, ptr);
            (yyval.predicate)=pred;
        }
    break;

  case 168:

/* Line 1464 of yacc.c  */
#line 901 "dmlyacc.yxx"
    { (yyval.stringval)=(char*) 1;
	}
    break;

  case 169:

/* Line 1464 of yacc.c  */
#line 904 "dmlyacc.yxx"
    { (yyval.stringval)=(char*) 0; }
    break;

  case 170:

/* Line 1464 of yacc.c  */
#line 907 "dmlyacc.yxx"
    {
            parsedData->insertTableName((char*)(yyvsp[(1) - (1)].stringval));
            free( (yyvsp[(1) - (1)].stringval) );
        }
    break;

  case 171:

/* Line 1464 of yacc.c  */
#line 912 "dmlyacc.yxx"
    {
            parsedData->insertTableName((char*)(yyvsp[(1) - (3)].stringval), (char*)(yyvsp[(3) - (3)].stringval));
            free( (yyvsp[(1) - (3)].stringval) ); free((yyvsp[(3) - (3)].stringval));
        }
    break;

  case 172:

/* Line 1464 of yacc.c  */
#line 917 "dmlyacc.yxx"
    {
            parsedData->insertTableName((char*)(yyvsp[(1) - (2)].stringval), (char*)(yyvsp[(2) - (2)].stringval));
            free( (yyvsp[(1) - (2)].stringval) ); free((yyvsp[(2) - (2)].stringval));
        }
    break;

  case 173:

/* Line 1464 of yacc.c  */
#line 923 "dmlyacc.yxx"
    {
            parsedData->insertField((char*)(yyvsp[(1) - (1)].stringval));
            free( (yyvsp[(1) - (1)].stringval) );
            
        }
    break;

  case 174:

/* Line 1464 of yacc.c  */
#line 929 "dmlyacc.yxx"
    { 
            parsedData->insertField((char*)(yyvsp[(3) - (4)].stringval), AGG_MIN);
            free( (yyvsp[(1) - (4)].stringval) );
        }
    break;

  case 175:

/* Line 1464 of yacc.c  */
#line 934 "dmlyacc.yxx"
    { 
            parsedData->insertField((char*)(yyvsp[(3) - (4)].stringval), AGG_MAX);
            free( (yyvsp[(1) - (4)].stringval) );
        }
    break;

  case 176:

/* Line 1464 of yacc.c  */
#line 939 "dmlyacc.yxx"
    { 
            parsedData->insertField((char*)(yyvsp[(3) - (4)].stringval), AGG_SUM);
            free( (yyvsp[(1) - (4)].stringval) );
        }
    break;

  case 177:

/* Line 1464 of yacc.c  */
#line 944 "dmlyacc.yxx"
    { 
            parsedData->insertField((char*)(yyvsp[(3) - (4)].stringval), AGG_AVG);
            free( (yyvsp[(1) - (4)].stringval) );
        }
    break;

  case 178:

/* Line 1464 of yacc.c  */
#line 949 "dmlyacc.yxx"
    { 
            parsedData->insertField((char*)(yyvsp[(3) - (4)].stringval), AGG_COUNT);
            free( (yyvsp[(1) - (4)].stringval) );
        }
    break;

  case 179:

/* Line 1464 of yacc.c  */
#line 954 "dmlyacc.yxx"
    { 
            parsedData->insertField("*", AGG_COUNT);
            free( (yyvsp[(1) - (4)].stringval) );
        }
    break;

  case 180:

/* Line 1464 of yacc.c  */
#line 959 "dmlyacc.yxx"
    { 
            parsedData->insertField("*");
        }
    break;

  case 181:

/* Line 1464 of yacc.c  */
#line 963 "dmlyacc.yxx"
    {
            parsedData->insertField("*");
        }
    break;

  case 182:

/* Line 1464 of yacc.c  */
#line 967 "dmlyacc.yxx"
    { (yyval.stringval) = (yyvsp[(1) - (1)].stringval); }
    break;

  case 183:

/* Line 1464 of yacc.c  */
#line 968 "dmlyacc.yxx"
    { (yyval.stringval) = (yyvsp[(2) - (3)].stringval); }
    break;

  case 184:

/* Line 1464 of yacc.c  */
#line 970 "dmlyacc.yxx"
    { (yyval.stringval) = (yyvsp[(1) - (1)].stringval); }
    break;

  case 186:

/* Line 1464 of yacc.c  */
#line 972 "dmlyacc.yxx"
    { (yyval.stringval) = (yyvsp[(1) - (1)].stringval); }
    break;

  case 188:

/* Line 1464 of yacc.c  */
#line 974 "dmlyacc.yxx"
    { (yyval.stringval) = (yyvsp[(1) - (1)].stringval); }
    break;

  case 189:

/* Line 1464 of yacc.c  */
#line 975 "dmlyacc.yxx"
    { (yyval.stringval) = (char*) 0; }
    break;

  case 190:

/* Line 1464 of yacc.c  */
#line 977 "dmlyacc.yxx"
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

  case 191:

/* Line 1464 of yacc.c  */
#line 989 "dmlyacc.yxx"
    { (yyval.stringval) =  (yyvsp[(1) - (1)].stringval); }
    break;

  case 192:

/* Line 1464 of yacc.c  */
#line 991 "dmlyacc.yxx"
    {
             char *n;
             n=(char*)malloc(30);
             strcpy(n,"-");
             strcat(n,(char*)(yyvsp[(2) - (2)].stringval));
             (yyval.stringval)=n;
             free((yyvsp[(2) - (2)].stringval));
        }
    break;

  case 193:

/* Line 1464 of yacc.c  */
#line 999 "dmlyacc.yxx"
    { (yyval.stringval) =  (yyvsp[(2) - (2)].stringval); }
    break;

  case 194:

/* Line 1464 of yacc.c  */
#line 1001 "dmlyacc.yxx"
    { (yyval.stringval) = (yyvsp[(1) - (1)].stringval); }
    break;

  case 195:

/* Line 1464 of yacc.c  */
#line 1003 "dmlyacc.yxx"
    {
             char *d;
             d=(char*)malloc(30);
             strcpy(d,"-");
             strcat(d,(char*)(yyvsp[(2) - (2)].stringval));
             (yyval.stringval)=d;
             free((yyvsp[(2) - (2)].stringval));
        }
    break;

  case 196:

/* Line 1464 of yacc.c  */
#line 1011 "dmlyacc.yxx"
    { (yyval.stringval) = (yyvsp[(2) - (2)].stringval); }
    break;

  case 197:

/* Line 1464 of yacc.c  */
#line 1014 "dmlyacc.yxx"
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

  case 198:

/* Line 1464 of yacc.c  */
#line 1025 "dmlyacc.yxx"
    {
            parsedData->setStmtType(CacheTableStatement);
            parsedData->setUnCache(true);
            parsedData->setTableName((yyvsp[(3) - (4)].stringval)); 
        }
    break;

  case 201:

/* Line 1464 of yacc.c  */
#line 1035 "dmlyacc.yxx"
    {
            parsedData->setHCondFld(true);
            parsedData->setHCondition((char*)(yyvsp[(2) - (2)].stringval));
         }
    break;

  case 203:

/* Line 1464 of yacc.c  */
#line 1042 "dmlyacc.yxx"
    {
            parsedData->setVCondFld(true);
            parsedData->setVCondition((char*)(yyvsp[(2) - (2)].stringval));
            free((yyvsp[(2) - (2)].stringval));
         }
    break;

  case 205:

/* Line 1464 of yacc.c  */
#line 1050 "dmlyacc.yxx"
    {
            parsedData->setPkFld(true);
            parsedData->setIndexName((char*)(yyvsp[(2) - (2)].stringval));
            free((yyvsp[(2) - (2)].stringval));
         }
    break;

  case 207:

/* Line 1464 of yacc.c  */
#line 1058 "dmlyacc.yxx"
    {
            parsedData->setDirect(true);
         }
    break;

  case 209:

/* Line 1464 of yacc.c  */
#line 1064 "dmlyacc.yxx"
    {
             parsedData->setDSN(true);
             parsedData->setPKTableName((char*)(yyvsp[(2) - (2)].stringval));
             free((yyvsp[(2) - (2)].stringval));
         }
    break;

  case 211:

/* Line 1464 of yacc.c  */
#line 1071 "dmlyacc.yxx"
    {
             parsedData->setNoSchema(true);
         }
    break;

  case 212:

/* Line 1464 of yacc.c  */
#line 1076 "dmlyacc.yxx"
    {
            parsedData->setStmtType(CreateTableStatement);
            parsedData->setTableName((yyvsp[(3) - (7)].stringval)); 
            free((yyvsp[(3) - (7)].stringval));
        }
    break;

  case 213:

/* Line 1464 of yacc.c  */
#line 1082 "dmlyacc.yxx"
    {
            parsedData->setStmtType(CreateIndexStatement);
            parsedData->setIndexName((yyvsp[(3) - (12)].stringval)); 
            parsedData->setTableName((yyvsp[(5) - (12)].stringval)); 
            free((yyvsp[(3) - (12)].stringval));
            free((yyvsp[(5) - (12)].stringval));
        }
    break;

  case 214:

/* Line 1464 of yacc.c  */
#line 1090 "dmlyacc.yxx"
    {
            parsedData->setStmtType(DropTableStatement);
            parsedData->setTableName((yyvsp[(3) - (3)].stringval)); 
            free((yyvsp[(3) - (3)].stringval));
        }
    break;

  case 215:

/* Line 1464 of yacc.c  */
#line 1096 "dmlyacc.yxx"
    {
            parsedData->setStmtType(DropIndexStatement);
            parsedData->setIndexName((yyvsp[(3) - (3)].stringval)); 
            free((yyvsp[(3) - (3)].stringval));
        }
    break;

  case 216:

/* Line 1464 of yacc.c  */
#line 1102 "dmlyacc.yxx"
    {
            parsedData->setStmtType(TruncateStatement);
            parsedData->setTableName((yyvsp[(3) - (4)].stringval)); 
            free((yyvsp[(3) - (4)].stringval));
        }
    break;

  case 218:

/* Line 1464 of yacc.c  */
#line 1110 "dmlyacc.yxx"
    {
            parsedData->setIndexType(hashIndex);
        }
    break;

  case 219:

/* Line 1464 of yacc.c  */
#line 1114 "dmlyacc.yxx"
    {
            parsedData->setIndexType(treeIndex);
        }
    break;

  case 220:

/* Line 1464 of yacc.c  */
#line 1118 "dmlyacc.yxx"
    {
            parsedData->setIndexType(trieIndex);
        }
    break;

  case 221:

/* Line 1464 of yacc.c  */
#line 1122 "dmlyacc.yxx"
    {
            parsedData->setIndexType(hashIndex);
        }
    break;

  case 223:

/* Line 1464 of yacc.c  */
#line 1128 "dmlyacc.yxx"
    {
            parsedData->setUnique(true);
        }
    break;

  case 224:

/* Line 1464 of yacc.c  */
#line 1132 "dmlyacc.yxx"
    {
            parsedData->setUnique(true);
            parsedData->setPrimary(true);
        }
    break;

  case 225:

/* Line 1464 of yacc.c  */
#line 1137 "dmlyacc.yxx"
    {
            parsedData->setUnique(false);
            parsedData->setPrimary(false);
        }
    break;

  case 227:

/* Line 1464 of yacc.c  */
#line 1144 "dmlyacc.yxx"
    {
            parsedData->setBucketSize(atoi((yyvsp[(2) - (2)].stringval)));
            free((yyvsp[(2) - (2)].stringval));
        }
    break;

  case 233:

/* Line 1464 of yacc.c  */
#line 1160 "dmlyacc.yxx"
    {
            parsedData->insertFldDef();
        }
    break;

  case 235:

/* Line 1464 of yacc.c  */
#line 1169 "dmlyacc.yxx"
    {
            parsedData->setFldName((yyvsp[(1) - (1)].stringval));
            free((yyvsp[(1) - (1)].stringval));
        }
    break;

  case 237:

/* Line 1464 of yacc.c  */
#line 1175 "dmlyacc.yxx"
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

  case 239:

/* Line 1464 of yacc.c  */
#line 1188 "dmlyacc.yxx"
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

  case 241:

/* Line 1464 of yacc.c  */
#line 1201 "dmlyacc.yxx"
    {
            parsedData->setFldNotNull(true);
        }
    break;

  case 248:

/* Line 1464 of yacc.c  */
#line 1215 "dmlyacc.yxx"
    {
            parsedData->setForeign(true);
            parsedData->setPKTableName((char*)(yyvsp[(7) - (10)].stringval));
            parsedData->insertForeignKeyList();
        }
    break;

  case 252:

/* Line 1464 of yacc.c  */
#line 1227 "dmlyacc.yxx"
    {
           parsedData->insertFKField((char*)(yyvsp[(1) - (1)].stringval));
           free((yyvsp[(1) - (1)].stringval));
        }
    break;

  case 256:

/* Line 1464 of yacc.c  */
#line 1238 "dmlyacc.yxx"
    {
           parsedData->insertPKField((char*)(yyvsp[(1) - (1)].stringval));
           free((yyvsp[(1) - (1)].stringval));
        }
    break;

  case 257:

/* Line 1464 of yacc.c  */
#line 1245 "dmlyacc.yxx"
    {
           parsedData->setPrimary(true);
        }
    break;

  case 259:

/* Line 1464 of yacc.c  */
#line 1251 "dmlyacc.yxx"
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

  case 260:

/* Line 1464 of yacc.c  */
#line 1272 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeInt);
        }
    break;

  case 261:

/* Line 1464 of yacc.c  */
#line 1276 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeLong);
        }
    break;

  case 262:

/* Line 1464 of yacc.c  */
#line 1280 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeShort);
        }
    break;

  case 263:

/* Line 1464 of yacc.c  */
#line 1284 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeLongLong);
        }
    break;

  case 264:

/* Line 1464 of yacc.c  */
#line 1288 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeByteInt);
        }
    break;

  case 265:

/* Line 1464 of yacc.c  */
#line 1292 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeFloat);
        }
    break;

  case 266:

/* Line 1464 of yacc.c  */
#line 1296 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeDouble);
        }
    break;

  case 267:

/* Line 1464 of yacc.c  */
#line 1301 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeDate);
        }
    break;

  case 268:

/* Line 1464 of yacc.c  */
#line 1306 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeTime);
        }
    break;

  case 269:

/* Line 1464 of yacc.c  */
#line 1311 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeTimeStamp);
        }
    break;

  case 270:

/* Line 1464 of yacc.c  */
#line 1316 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeString);
            parsedData->setFldLength(2);
        }
    break;

  case 271:

/* Line 1464 of yacc.c  */
#line 1322 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeVarchar);
            parsedData->setFldLength(2);
        }
    break;

  case 272:

/* Line 1464 of yacc.c  */
#line 1328 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeBinary);
            parsedData->setFldLength(1);
        }
    break;



/* Line 1464 of yacc.c  */
#line 4276 "dmlyacc.cxx"
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
#line 1333 "dmlyacc.yxx"


extern int lexEof;
void yyerror(const char* Msg) { 
    if( lexEof == 0 )
        fprintf(stderr, "[Parser: %s] %s\n", Msg, yytext);

    return;
}

