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
#define YYFINAL  74
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   838

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  135
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  101
/* YYNRULES -- Number of rules.  */
#define YYNRULES  272
/* YYNRULES -- Number of states.  */
#define YYNSTATES  621

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
      19,    21,    23,    25,    27,    29,    31,    40,    48,    57,
      64,    74,    82,    86,    93,    98,   106,   109,   111,   114,
     116,   118,   120,   122,   125,   127,   130,   132,   141,   149,
     165,   181,   185,   187,   190,   194,   197,   199,   201,   203,
     206,   209,   222,   225,   226,   228,   229,   232,   234,   237,
     239,   243,   246,   248,   251,   258,   266,   271,   272,   273,
     275,   276,   278,   281,   291,   292,   296,   299,   301,   304,
     307,   309,   312,   318,   325,   327,   328,   331,   333,   336,
     340,   344,   348,   352,   356,   360,   364,   368,   372,   375,
     378,   380,   382,   389,   397,   405,   412,   420,   428,   437,
     445,   453,   460,   465,   470,   472,   474,   476,   478,   480,
     482,   484,   486,   488,   490,   492,   495,   496,   500,   501,
     505,   506,   509,   514,   515,   518,   519,   522,   524,   527,
     529,   532,   534,   537,   539,   542,   545,   549,   553,   557,
     562,   565,   569,   573,   577,   582,   585,   592,   599,   606,
     613,   620,   624,   628,   635,   642,   647,   651,   655,   659,
     663,   665,   666,   668,   672,   675,   677,   682,   687,   692,
     697,   702,   707,   709,   712,   714,   718,   720,   722,   724,
     726,   728,   730,   734,   736,   739,   742,   744,   747,   750,
     756,   761,   768,   769,   772,   773,   776,   777,   780,   781,
     783,   784,   787,   788,   790,   798,   811,   815,   819,   824,
     827,   830,   833,   834,   836,   838,   839,   840,   843,   845,
     849,   852,   854,   857,   859,   866,   868,   869,   873,   874,
     877,   878,   881,   883,   885,   889,   892,   894,   897,   908,
     911,   913,   916,   918,   921,   923,   926,   928,   935,   936,
     938,   940,   942,   944,   946,   948,   950,   952,   954,   956,
     958,   960,   962
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     136,     0,    -1,   151,    -1,   162,    -1,   168,    -1,   169,
      -1,   210,    -1,   149,    -1,   202,    -1,   148,    -1,   139,
      -1,   146,    -1,   147,    -1,   138,    -1,   137,    -1,   150,
      -1,   109,    52,   198,   111,   132,   214,   133,   170,    -1,
     109,    52,   198,    62,   112,   198,   170,    -1,   109,    52,
     198,   113,   132,   217,   133,   170,    -1,   114,    52,   198,
     115,   198,   170,    -1,   109,    52,   198,   114,   112,   198,
     115,   198,   170,    -1,   109,    56,   198,   114,   115,   198,
     170,    -1,   110,    68,   170,    -1,    51,   107,   198,   108,
      11,   170,    -1,    62,   107,   198,   170,    -1,   109,   107,
     198,    49,   108,    11,   170,    -1,   140,   141,    -1,   142,
      -1,   131,   142,    -1,    27,    -1,    42,    -1,    48,    -1,
      47,    -1,   143,   144,    -1,   145,    -1,   131,   145,    -1,
     198,    -1,   116,   140,    57,   198,   115,   143,   180,   170,
      -1,   117,   140,    57,   198,    28,   143,   170,    -1,    51,
      52,   198,    33,    27,   153,   154,    28,   157,   180,   181,
     184,   182,   183,   170,    -1,    42,    43,   198,    33,    27,
     153,   154,    28,   157,   180,   181,   184,   182,   183,   170,
      -1,    66,    52,   198,    -1,    18,    -1,    19,   196,    -1,
      19,    56,   196,    -1,    20,   196,    -1,    22,    -1,    24,
      -1,    23,    -1,    25,   196,    -1,    26,   196,    -1,   152,
      27,   153,   154,    28,   157,   180,   181,   184,   182,   183,
     170,    -1,    45,    46,    -1,    -1,   129,    -1,    -1,   154,
     155,    -1,   156,    -1,   131,   156,    -1,   197,    -1,   197,
      33,   198,    -1,   157,   161,    -1,   196,    -1,   196,   158,
      -1,    36,   160,   196,    57,   191,   158,    -1,    40,   159,
     160,   196,    57,   191,   158,    -1,    38,   160,   196,   158,
      -1,    -1,    -1,    37,    -1,    -1,    39,    -1,   131,   196,
      -1,    42,    43,   198,   163,    44,   132,   164,   133,   170,
      -1,    -1,   132,   154,   133,    -1,   164,   165,    -1,   199,
      -1,   131,   199,    -1,   166,   167,    -1,   199,    -1,   131,
     199,    -1,    47,    28,   198,   180,   170,    -1,    48,   198,
      49,   171,   180,   170,    -1,   130,    -1,    -1,   171,   172,
      -1,   173,    -1,   131,   173,    -1,   198,    16,   174,    -1,
     198,    16,   199,    -1,   198,    16,    50,    -1,   174,     8,
     174,    -1,   174,     9,   174,    -1,   174,     7,   174,    -1,
     174,     5,   174,    -1,   174,     6,   174,    -1,   132,   174,
     133,    -1,     6,   174,    -1,     5,   174,    -1,   175,    -1,
     179,    -1,    89,   132,   179,   131,   179,   133,    -1,    90,
     132,   179,    98,   179,   178,   133,    -1,    91,   132,   179,
      98,   179,   178,   133,    -1,    99,   132,   179,   131,   179,
     133,    -1,   100,   132,   179,    98,   179,   177,   133,    -1,
     101,   132,   179,    98,   179,   177,   133,    -1,   102,   132,
     176,   131,   179,   131,   179,   133,    -1,   103,   132,   179,
      98,   179,   176,   133,    -1,   104,   132,   179,    98,   179,
     176,   133,    -1,   105,   132,   176,    28,   179,   133,    -1,
      81,   132,   179,   133,    -1,    83,   132,   179,   133,    -1,
     177,    -1,   178,    -1,    92,    -1,    93,    -1,    94,    -1,
      95,    -1,    96,    -1,    97,    -1,   198,    -1,   199,    -1,
      50,    -1,    29,   191,    -1,    -1,   123,   124,   185,    -1,
      -1,   126,   124,   188,    -1,    -1,    34,    13,    -1,    34,
      13,    35,    13,    -1,    -1,   125,   192,    -1,    -1,   185,
     186,    -1,   187,    -1,   131,   187,    -1,   198,    -1,   188,
     189,    -1,   190,    -1,   131,   190,    -1,   198,    -1,   198,
     127,    -1,   198,   128,    -1,   191,     3,   191,    -1,   191,
       4,   191,    -1,   132,   191,   133,    -1,    32,   132,   191,
     133,    -1,   195,   194,    -1,   192,     3,   192,    -1,   192,
       4,   192,    -1,   132,   192,   133,    -1,    32,   132,   192,
     133,    -1,   195,   193,    -1,   118,   132,   198,   133,    16,
     199,    -1,   119,   132,   198,   133,    16,   199,    -1,   121,
     132,   198,   133,    16,   199,    -1,   120,   132,   198,   133,
      16,   199,    -1,   122,   132,   198,   133,    16,   199,    -1,
     198,    16,   199,    -1,   198,    16,   198,    -1,   198,   195,
      30,   199,     4,   199,    -1,   198,   195,    31,   132,   166,
     133,    -1,   198,    41,    32,    50,    -1,   198,    41,    50,
      -1,   175,    16,   175,    -1,   175,    16,   198,    -1,   175,
      16,   199,    -1,    32,    -1,    -1,   198,    -1,   198,    33,
     198,    -1,   198,   198,    -1,   198,    -1,   118,   132,   198,
     133,    -1,   119,   132,   198,   133,    -1,   121,   132,   198,
     133,    -1,   120,   132,   198,   133,    -1,   122,   132,   198,
     133,    -1,   122,   132,     7,   133,    -1,     7,    -1,   198,
       7,    -1,    12,    -1,   134,    12,   134,    -1,    11,    -1,
     200,    -1,    14,    -1,   201,    -1,    17,    -1,    50,    -1,
     106,   132,   133,    -1,    13,    -1,     6,    13,    -1,     5,
      13,    -1,    15,    -1,     6,    15,    -1,     5,    15,    -1,
      68,    52,   198,   203,   170,    -1,    74,    52,   198,   170,
      -1,   204,   205,   206,   207,   208,   209,    -1,    -1,    69,
     199,    -1,    -1,    70,   199,    -1,    -1,    71,   198,    -1,
      -1,    72,    -1,    -1,    73,   199,    -1,    -1,    75,    -1,
      51,    52,   198,   132,   214,   133,   170,    -1,    51,    56,
     198,    57,   198,   132,   154,   133,   212,   211,   213,   170,
      -1,    62,    52,   198,    -1,    62,    56,   198,    -1,    67,
      52,   198,   170,    -1,    58,   212,    -1,    59,   212,    -1,
      60,   212,    -1,    -1,    61,    -1,    53,    -1,    -1,    -1,
      63,    13,    -1,   215,    -1,   215,   131,   223,    -1,   215,
     216,    -1,   217,    -1,   131,   217,    -1,   218,    -1,   219,
     235,   220,   222,   221,   234,    -1,   198,    -1,    -1,   132,
      13,   133,    -1,    -1,    55,   199,    -1,    -1,    32,    50,
      -1,   233,    -1,   224,    -1,   233,   131,   224,    -1,   224,
     225,    -1,   226,    -1,   131,   226,    -1,    64,    54,   132,
     227,   133,    65,   198,   132,   230,   133,    -1,   227,   228,
      -1,   229,    -1,   131,   229,    -1,   198,    -1,   230,   231,
      -1,   232,    -1,   131,   232,    -1,   198,    -1,    53,    54,
     132,   154,   133,   213,    -1,    -1,    21,    -1,    76,    -1,
      77,    -1,    78,    -1,    84,    -1,    86,    -1,    85,    -1,
      79,    -1,    81,    -1,    83,    -1,    80,    -1,    82,    -1,
      88,    -1,    87,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    44,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    59,    66,    74,    80,
      89,    98,   107,   112,   119,   125,   133,   134,   136,   139,
     140,   141,   142,   144,   145,   147,   149,   151,   158,   165,
     172,   179,   186,   191,   196,   202,   207,   212,   217,   222,
     227,   233,   239,   243,   245,   249,   251,   252,   254,   256,
     257,   263,   264,   265,   267,   281,   294,   298,   300,   301,
     303,   304,   306,   312,   320,   321,   324,   325,   331,   338,
     339,   345,   352,   360,   368,   369,   372,   373,   376,   378,
     383,   388,   394,   400,   406,   412,   418,   424,   428,   432,
     436,   437,   439,   446,   453,   461,   468,   475,   482,   493,
     500,   507,   519,   527,   535,   540,   546,   551,   556,   562,
     567,   572,   578,   585,   593,   602,   615,   617,   618,   620,
     621,   623,   627,   631,   633,   634,   636,   637,   639,   641,
     647,   648,   650,   652,   657,   662,   668,   676,   683,   684,
     692,   708,   716,   723,   724,   732,   748,   757,   766,   775,
     784,   795,   806,   817,   833,   859,   867,   875,   883,   893,
     902,   906,   908,   913,   918,   924,   930,   935,   940,   945,
     950,   955,   960,   964,   969,   970,   972,   973,   974,   975,
     976,   977,   978,   991,   992,  1001,  1003,  1004,  1013,  1015,
    1026,  1033,  1035,  1036,  1042,  1043,  1050,  1051,  1058,  1059,
    1064,  1065,  1071,  1072,  1077,  1083,  1091,  1097,  1103,  1111,
    1115,  1119,  1124,  1129,  1133,  1139,  1144,  1145,  1151,  1152,
    1154,  1155,  1158,  1161,  1167,  1170,  1175,  1176,  1188,  1189,
    1201,  1202,  1207,  1208,  1209,  1211,  1212,  1214,  1216,  1223,
    1224,  1226,  1228,  1234,  1235,  1237,  1239,  1246,  1251,  1252,
    1273,  1277,  1281,  1285,  1289,  1293,  1297,  1302,  1307,  1312,
    1317,  1323,  1329
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
  "grant_statement", "revoke_statement", "copy_table_statement",
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
      59,    44,    40,    41,    96
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   135,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   137,   137,   137,   137,
     137,   137,   138,   139,   139,   139,   140,   140,   141,   142,
     142,   142,   142,   143,   143,   144,   145,   146,   147,   148,
     148,   149,   150,   150,   150,   150,   150,   150,   150,   150,
     150,   151,   152,   152,   153,   153,   154,   154,   155,   156,
     156,   157,   157,   157,   158,   158,   158,   158,   159,   159,
     160,   160,   161,   162,   163,   163,   164,   164,   165,   166,
     166,   167,   168,   169,   170,   170,   171,   171,   172,   173,
     173,   173,   174,   174,   174,   174,   174,   174,   174,   174,
     174,   174,   175,   175,   175,   175,   175,   175,   175,   175,
     175,   175,   175,   175,   176,   176,   177,   177,   177,   178,
     178,   178,   179,   179,   179,   180,   180,   181,   181,   182,
     182,   183,   183,   183,   184,   184,   185,   185,   186,   187,
     188,   188,   189,   190,   190,   190,   191,   191,   191,   191,
     191,   192,   192,   192,   192,   192,   193,   193,   193,   193,
     193,   194,   194,   194,   194,   194,   194,   194,   194,   194,
     195,   195,   196,   196,   196,   197,   197,   197,   197,   197,
     197,   197,   197,   197,   198,   198,   199,   199,   199,   199,
     199,   199,   199,   200,   200,   200,   201,   201,   201,   202,
     202,   203,   204,   204,   205,   205,   206,   206,   207,   207,
     208,   208,   209,   209,   210,   210,   210,   210,   210,   211,
     211,   211,   211,   212,   212,   212,   213,   213,   214,   214,
     215,   215,   216,   217,   218,   219,   220,   220,   221,   221,
     222,   222,   223,   223,   223,   224,   224,   225,   226,   227,
     227,   228,   229,   230,   230,   231,   232,   233,   234,   234,
     235,   235,   235,   235,   235,   235,   235,   235,   235,   235,
     235,   235,   235
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     8,     7,     8,     6,
       9,     7,     3,     6,     4,     7,     2,     1,     2,     1,
       1,     1,     1,     2,     1,     2,     1,     8,     7,    15,
      15,     3,     1,     2,     3,     2,     1,     1,     1,     2,
       2,    12,     2,     0,     1,     0,     2,     1,     2,     1,
       3,     2,     1,     2,     6,     7,     4,     0,     0,     1,
       0,     1,     2,     9,     0,     3,     2,     1,     2,     2,
       1,     2,     5,     6,     1,     0,     2,     1,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       1,     1,     6,     7,     7,     6,     7,     7,     8,     7,
       7,     6,     4,     4,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     0,     3,     0,     3,
       0,     2,     4,     0,     2,     0,     2,     1,     2,     1,
       2,     1,     2,     1,     2,     2,     3,     3,     3,     4,
       2,     3,     3,     3,     4,     2,     6,     6,     6,     6,
       6,     3,     3,     6,     6,     4,     3,     3,     3,     3,
       1,     0,     1,     3,     2,     1,     4,     4,     4,     4,
       4,     4,     1,     2,     1,     3,     1,     1,     1,     1,
       1,     1,     3,     1,     2,     2,     1,     2,     2,     5,
       4,     6,     0,     2,     0,     2,     0,     2,     0,     1,
       0,     2,     0,     1,     7,    12,     3,     3,     4,     2,
       2,     2,     0,     1,     1,     0,     0,     2,     1,     3,
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
      53,    42,     0,     0,    46,    48,    47,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    14,    13,    10,    11,    12,
       9,     7,    15,     2,     0,     3,     4,     5,     8,     6,
     184,     0,     0,    43,   172,    45,    49,    50,     0,    52,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    85,     0,    29,    30,    32,
      31,     0,    27,     0,     1,    55,    44,     0,     0,   174,
      74,   126,     0,     0,     0,     0,   216,   217,    85,    41,
      85,   202,    85,     0,     0,     0,    84,    22,     0,     0,
       0,    26,     0,    54,     0,   185,   173,     0,     0,     0,
     171,    85,   126,    87,     0,     0,     0,     0,     0,    24,
     218,     0,    85,   204,   200,     0,     0,     0,     0,     0,
       0,     0,     0,    28,     0,   182,     0,     0,     0,     0,
       0,     0,    57,    59,   175,    55,     0,     0,   170,   171,
     125,     0,    82,     0,    86,    85,     0,    55,   235,     0,
     228,   231,   233,     0,     0,    85,     0,     0,   186,   193,
     188,   196,   190,   191,     0,   203,   187,   189,   199,     0,
     206,     0,     0,     0,     0,     0,     0,    85,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    56,     0,   183,
       0,    75,     0,   171,     0,   171,   171,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     150,   171,    88,    83,     0,     0,   124,     0,    89,   100,
     101,   122,   123,     0,    85,     0,   230,   260,   261,   262,
     266,   269,   267,   270,   268,   263,   265,   264,   272,   271,
     236,     0,    23,   195,   198,   194,   197,     0,   205,     0,
     208,    85,     0,     0,     0,    85,    85,    19,   126,    34,
      36,    85,     0,     0,     0,     0,     0,     0,   126,    62,
      58,    60,     0,     0,    77,     0,   148,   146,   147,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   170,     0,     0,   193,   196,   124,    99,
     123,   193,   196,    98,     0,     0,     0,     0,     0,     0,
       0,   214,     0,     0,   232,   229,   243,   246,   242,     0,
     240,     0,   192,   207,   209,   210,    17,    85,    85,     0,
      21,    25,     0,    33,    85,    38,   176,   177,   179,   178,
     181,   180,     0,    61,   128,    70,    70,    68,    63,     0,
       0,    85,    76,   149,     0,     0,     0,     0,     0,     0,
       0,     0,   116,   117,   118,   119,   120,   121,     0,   114,
     115,     0,     0,     0,   167,   168,   169,   162,   161,     0,
     166,     0,     0,    97,    95,    96,    94,    92,    93,     0,
       0,     0,     0,   245,     0,     0,     0,   238,   225,     0,
     212,    16,    18,    85,    35,    37,    72,     0,   135,    71,
       0,     0,    69,    70,   126,    78,    73,   112,   113,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   165,
       0,     0,   126,     0,     0,   247,   244,   237,   241,     0,
     258,   224,   223,   222,   211,   213,   201,    20,     0,   171,
     130,     0,    67,     0,   128,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    80,   128,     0,
     252,     0,   250,   239,   259,   234,   225,   225,   225,   226,
     127,   137,   139,   170,   171,   134,     0,     0,   133,   171,
      66,     0,   135,   102,     0,     0,   105,     0,     0,     0,
       0,     0,   111,   163,     0,   164,    79,   135,   226,     0,
       0,   249,   219,   220,   221,     0,    85,     0,   136,   171,
       0,   171,   171,     0,     0,     0,     0,     0,   155,     0,
       0,    85,    67,   171,   130,   103,   104,   106,   107,     0,
     109,   110,    81,   130,   257,   251,     0,   227,   215,   138,
       0,   153,   151,   152,     0,     0,     0,     0,     0,   129,
     141,   143,   131,    51,    64,    67,   133,   108,   133,     0,
     154,     0,     0,     0,     0,     0,     0,   140,   144,   145,
       0,    65,    85,    85,     0,     0,     0,     0,     0,     0,
     142,   132,    40,    39,   256,     0,   254,     0,     0,     0,
       0,     0,     0,   248,   253,   156,   157,   159,   158,   160,
     255
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    24,    25,    26,    27,    71,   101,    72,   268,   343,
     269,    28,    29,    30,    31,    32,    33,    34,   104,   141,
     197,   142,   278,   358,   423,   420,   353,    35,   109,   283,
     362,   476,   516,    36,    37,    97,   112,   154,   113,   228,
     229,   378,   379,   380,   230,   111,   418,   498,   541,   460,
     490,   528,   491,   569,   587,   570,   150,   495,   538,   220,
     151,   279,   143,   231,   310,   176,   177,    38,   122,   123,
     180,   260,   335,   410,   456,    39,   489,   453,   526,   159,
     160,   236,   161,   162,   163,   330,   450,   407,   325,   326,
     403,   327,   481,   521,   482,   605,   614,   606,   328,   485,
     250
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -441
static const yytype_int16 yypact[] =
{
     406,  -441,    35,     4,  -441,  -441,  -441,     4,     4,     2,
      87,   115,     4,    64,   120,    88,   106,   170,   185,   162,
     188,   266,   256,   256,   275,  -441,  -441,  -441,  -441,  -441,
    -441,  -441,  -441,  -441,   239,  -441,  -441,  -441,  -441,  -441,
    -441,     4,   307,  -441,     1,  -441,  -441,  -441,     4,  -441,
       4,   278,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   202,     4,  -441,  -441,  -441,
    -441,   -38,  -441,    46,  -441,   207,  -441,   209,     4,  -441,
      16,   313,     4,    84,   290,   254,  -441,  -441,   202,  -441,
     202,   289,   202,   112,   245,   317,  -441,  -441,   261,     4,
     256,  -441,     4,  -441,    83,  -441,  -441,   351,    83,   342,
      41,   202,     6,  -441,   371,   361,     4,     4,   378,  -441,
    -441,   267,   202,   321,  -441,   281,   260,   263,   284,   294,
     302,     4,   296,  -441,   384,  -441,   283,   285,   291,   295,
     303,     5,  -441,   380,   409,   207,    77,   311,   312,    41,
     181,   280,  -441,     4,  -441,   202,   496,   207,  -441,   301,
     314,  -441,  -441,   405,   315,   202,   200,   320,  -441,  -441,
    -441,  -441,  -441,  -441,   318,  -441,  -441,  -441,  -441,   267,
     375,     4,     4,     4,     4,     4,   411,   202,     4,     4,
       4,     4,     4,     4,    31,     4,    83,  -441,     4,  -441,
      83,  -441,   267,    41,    14,    41,    41,   323,   326,   327,
     328,   330,   332,   333,   334,   335,   337,   338,   339,   433,
    -441,   214,  -441,  -441,   544,   601,    15,   647,   288,  -441,
    -441,  -441,    37,    83,   202,    10,  -441,  -441,  -441,  -441,
    -441,  -441,  -441,  -441,  -441,  -441,  -441,  -441,  -441,  -441,
     343,    83,  -441,  -441,  -441,  -441,  -441,   319,  -441,     4,
     404,   202,   344,   346,   385,   202,   202,  -441,    76,  -441,
    -441,    98,   372,   373,   379,   381,   386,   388,    78,   251,
    -441,  -441,     8,   208,  -441,    17,  -441,   500,  -441,    72,
      72,    72,    72,    72,    72,    72,    72,   402,    72,    72,
     402,   704,   113,  -441,    91,   210,  -441,  -441,  -441,  -441,
    -441,  -441,  -441,  -441,    23,   647,   647,   647,   647,   647,
      44,  -441,   470,   477,  -441,  -441,   401,  -441,   403,   520,
     503,   218,  -441,  -441,  -441,   463,  -441,   202,   202,     4,
    -441,  -441,     4,  -441,   202,  -441,  -441,  -441,  -441,  -441,
    -441,  -441,     4,  -441,   415,   501,   501,   502,  -441,     4,
     267,   202,  -441,  -441,   408,   410,   413,   444,   447,   416,
     450,   453,  -441,  -441,  -441,  -441,  -441,  -441,   421,  -441,
    -441,   455,   462,   539,  -441,  -441,  -441,  -441,  -441,   518,
    -441,   267,   439,  -441,   102,   102,  -441,  -441,  -441,     4,
     440,   441,   510,  -441,   510,   442,   526,   523,   171,   267,
     505,  -441,  -441,   202,  -441,  -441,  -441,   457,   458,  -441,
       4,     4,  -441,   501,    78,  -441,  -441,  -441,  -441,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,  -441,
     578,   267,    78,    83,     4,  -441,   401,  -441,  -441,   267,
     567,  -441,  -441,   176,  -441,  -441,  -441,  -441,     4,    80,
     464,   532,   251,     4,   415,   460,   216,   216,   471,   232,
     232,   472,   402,   402,   475,   267,   222,  -441,   415,   223,
    -441,   234,  -441,  -441,  -441,  -441,   171,   171,   171,   528,
     474,  -441,  -441,   479,    80,   248,   187,   485,   583,    41,
    -441,   562,   458,  -441,   487,   488,  -441,   489,   490,    72,
     491,   493,  -441,  -441,   267,  -441,  -441,   458,   528,     4,
     564,  -441,  -441,  -441,  -441,   618,   202,     4,  -441,    80,
      20,    80,    80,   504,   506,   507,   508,   509,  -441,     4,
     619,   202,   250,    41,   464,  -441,  -441,  -441,  -441,   521,
    -441,  -441,  -441,   464,  -441,  -441,     4,  -441,  -441,  -441,
      22,  -441,   633,  -441,     4,     4,     4,     4,     4,   511,
    -441,   117,   620,  -441,  -441,   250,   583,  -441,   583,   524,
    -441,   530,   533,   534,   535,   536,     4,  -441,  -441,  -441,
     644,  -441,   202,   202,     4,   649,   654,   655,   656,   657,
    -441,  -441,  -441,  -441,  -441,   241,  -441,   267,   267,   267,
     267,   267,     4,  -441,  -441,  -441,  -441,  -441,  -441,  -441,
    -441
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -441,  -441,  -441,  -441,  -441,   651,  -441,   575,   492,  -441,
     341,  -441,  -441,  -441,  -441,  -441,  -441,  -441,     9,   -99,
    -441,   481,  -202,  -380,  -441,  -264,  -441,  -441,  -441,  -441,
    -441,  -441,  -441,  -441,  -441,   -23,  -441,  -441,   527,   121,
    -140,  -273,  -199,  -165,   -31,  -108,  -370,  -440,  -201,  -421,
    -441,  -441,   152,  -441,  -441,    99,  -135,  -255,  -441,  -441,
    -209,     0,  -441,    -2,   -81,  -441,  -441,  -441,  -441,  -441,
    -441,  -441,  -441,  -441,  -441,  -441,  -441,  -157,   168,   512,
    -441,  -441,  -104,  -441,  -441,  -441,  -441,  -441,  -441,   292,
    -441,   286,  -441,  -441,   174,  -441,  -441,    75,  -441,  -441,
    -441
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -92
static const yytype_int16 yytable[] =
{
      44,    44,    43,    45,   155,    44,    44,    46,    47,   146,
      51,   219,   305,    40,   204,   -91,    40,   205,   206,    99,
     205,   206,    40,   531,   532,   531,   532,   383,   315,   316,
     317,   318,   319,   195,    78,   110,   359,   -90,   276,    44,
     175,    76,    79,    40,   -91,    48,    80,    40,    81,   107,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,   322,    98,   119,   -90,   120,   285,   124,
     287,   288,   399,   148,   323,   232,   106,   166,   167,   263,
     114,   544,   500,   168,    40,   169,   170,   171,   152,   172,
     135,    41,   421,   100,   502,    40,   553,   132,   258,   178,
     134,   282,   144,   102,   576,   110,   144,   110,   517,   317,
     318,   319,   493,   578,   158,   164,    52,   115,   166,   167,
      53,   284,   308,   389,   168,    40,   169,   170,   171,   187,
     172,   324,   223,    49,   320,    42,   196,   153,    42,   196,
      58,   390,   252,    50,    42,   -91,   -91,   286,   108,   221,
     363,   114,   331,   561,   200,   580,   393,   424,    59,   463,
     344,   384,   574,   173,   267,    42,   233,   -90,   -90,    42,
     354,    54,    55,   149,   125,   196,    56,   100,   174,   261,
     158,   158,   264,   265,   205,   206,   270,   270,   272,   273,
     274,   275,   277,    44,   144,   591,   281,   442,   144,   510,
     511,   136,   137,   138,   139,   140,    42,   342,   196,   352,
     201,   321,   494,   253,    62,   254,   116,    42,    63,   174,
     386,   388,    60,   126,   451,   127,   128,    57,    96,   342,
     302,   144,   452,   158,   486,   487,   488,    61,   336,   530,
     391,   392,   340,   341,   588,   589,   303,    42,   345,   144,
     496,   531,   532,   205,   206,   304,    65,   333,   364,   365,
     366,   367,   368,   369,   370,   371,    75,   381,   382,    64,
     507,   508,   166,   167,   560,    74,   562,   563,   168,   425,
     169,   170,   171,    67,   172,   496,   355,   355,   356,   356,
     357,   357,    40,   315,   316,   317,   318,   319,    68,   385,
     387,   504,   505,    69,    70,   533,   534,   535,   536,   537,
     440,   375,   376,   377,   411,   412,   464,   173,    66,    77,
     496,   415,   496,   496,   372,   373,   374,    82,   454,   522,
     523,   524,    96,   255,   478,   256,   103,   413,   426,   360,
     270,   361,   110,   105,   479,   309,   313,   117,   314,   196,
      44,   408,   416,   514,   196,   515,   518,    44,   121,   129,
     477,   207,   118,   208,   542,   519,   130,   520,   483,   209,
     210,   211,   612,   174,   613,   592,   131,   593,   145,   212,
     213,   214,   215,   216,   217,   218,   147,   156,   157,   165,
     457,   179,   182,   181,   513,   183,   184,    44,   465,   466,
     467,   468,   469,   470,   471,   472,   473,   474,   575,   185,
     186,   188,   189,   198,    42,   190,   199,   191,    44,    44,
     461,   462,   266,   192,     1,     2,     3,   193,     4,     5,
       6,     7,     8,   552,   234,   194,   394,   395,   396,   397,
     398,   144,   480,   202,   203,   235,   259,   251,     9,   301,
     257,    10,   332,    11,    12,   289,   492,    13,   290,   291,
     292,    44,   293,   501,   294,   295,   296,   297,    14,   298,
     299,   300,    15,    16,    17,   329,   334,   337,   549,   338,
      18,   237,   238,   239,   240,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   372,   373,   374,   375,   376,   377,
     339,   224,   225,   558,   206,   346,   347,   168,    40,   169,
     170,   171,   348,   172,   349,    19,    20,   480,   573,   350,
      21,   351,    22,    23,   400,   492,   615,   616,   617,   618,
     619,   401,   402,   405,   404,   406,   409,   571,   417,   422,
     419,   427,   430,   428,   429,   431,   226,   432,   433,   224,
     225,   434,   435,   436,   579,   168,    40,   306,   170,   307,
     437,   172,   581,   582,   583,   584,   585,   438,   439,   602,
     603,   441,   443,   444,   323,   447,   448,   207,   449,   208,
     455,   458,   475,   459,   571,   209,   210,   211,   484,   499,
     497,   525,   604,   503,   308,   212,   213,   214,   215,   216,
     217,   218,   174,   509,   506,   527,   224,   225,   512,   539,
     604,   529,   168,    40,   311,   170,   312,   540,   172,   543,
     545,   546,   547,   548,   550,   207,   551,   208,   227,   556,
      42,   557,   572,   209,   210,   211,   564,   532,   565,   566,
     567,   568,   586,   212,   213,   214,   215,   216,   217,   218,
     174,   308,   224,   225,   577,   590,   594,   601,   168,    40,
     169,   170,   171,   595,   172,   607,   596,   597,   598,   599,
     608,   609,   610,   611,    73,   133,   227,   280,    42,   559,
     222,   271,   207,   414,   208,   600,   554,   620,   445,     0,
     209,   210,   211,   555,   262,     0,   446,   308,     0,     0,
     212,   213,   214,   215,   216,   217,   218,   174,     0,   166,
     167,     0,     0,     0,     0,   168,    40,   169,   170,   171,
       0,   172,     0,     0,     0,     0,     0,     0,   207,     0,
     208,     0,     0,   227,     0,    42,   209,   210,   211,     0,
       0,     0,     0,     0,     0,     0,   212,   213,   214,   215,
     216,   217,   218,   174,   173,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   227,
       0,    42,     0,     0,     0,   207,     0,   208,     0,     0,
       0,     0,     0,   209,   210,   211,     0,     0,     0,     0,
       0,     0,     0,   212,   213,   214,   215,   216,   217,   218,
     174,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    42
};

static const yytype_int16 yycheck[] =
{
       2,     3,     2,     3,   112,     7,     8,     7,     8,   108,
      12,   151,   221,    12,   149,     0,    12,     3,     4,    57,
       3,     4,    12,     3,     4,     3,     4,   300,     5,     6,
       7,     8,     9,    28,    33,    29,    28,     0,     7,    41,
     121,    41,    44,    12,    29,    43,    48,    12,    50,    33,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    53,    66,    88,    29,    90,   203,    92,
     205,   206,    28,    32,    64,   156,    78,     5,     6,   183,
      82,   502,   462,    11,    12,    13,    14,    15,   111,    17,
       7,    56,   356,   131,   464,    12,   517,    99,   179,   122,
     102,   200,   104,    57,   544,    29,   108,    29,   478,     7,
       8,     9,    32,   553,   116,   117,    52,    33,     5,     6,
      56,   202,    50,    32,    11,    12,    13,    14,    15,   131,
      17,   235,   155,    46,   233,   134,   131,   131,   134,   131,
      52,    50,   165,    28,   134,   130,   131,   133,   132,   151,
     133,   153,   251,   133,   145,   133,   133,   359,    52,   423,
     268,   301,   542,    50,   187,   134,   157,   130,   131,   134,
     278,   107,    52,   132,    62,   131,    56,   131,   106,   181,
     182,   183,   184,   185,     3,     4,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   575,   198,   399,   200,   472,
     473,   118,   119,   120,   121,   122,   134,   131,   131,   131,
     133,   234,   132,    13,    52,    15,   132,   134,    56,   106,
     301,   302,    52,   111,    53,   113,   114,   107,   130,   131,
      16,   233,    61,   235,    58,    59,    60,    52,   261,   494,
      30,    31,   265,   266,   127,   128,    32,   134,   271,   251,
     459,     3,     4,     3,     4,    41,    68,   259,   289,   290,
     291,   292,   293,   294,   295,   296,    27,   298,   299,   107,
     469,   470,     5,     6,   529,     0,   531,   532,    11,   360,
      13,    14,    15,    27,    17,   494,    36,    36,    38,    38,
      40,    40,    12,     5,     6,     7,     8,     9,    42,   301,
     302,   466,   467,    47,    48,   118,   119,   120,   121,   122,
     391,    95,    96,    97,   337,   338,   424,    50,    52,    12,
     529,   344,   531,   532,    92,    93,    94,    49,   409,   486,
     487,   488,   130,    13,   442,    15,   129,   339,   361,   131,
     342,   133,    29,   134,   443,   224,   225,    57,   227,   131,
     352,   133,   352,   131,   131,   133,   133,   359,    69,   114,
     441,    81,   108,    83,   499,   131,    49,   133,   449,    89,
      90,    91,   131,   106,   133,   576,   115,   578,    27,    99,
     100,   101,   102,   103,   104,   105,    44,    16,    27,    11,
     413,    70,   132,   112,   475,   132,   112,   399,   429,   430,
     431,   432,   433,   434,   435,   436,   437,   438,   543,   115,
     108,   115,    28,    33,   134,   132,     7,   132,   420,   421,
     420,   421,    11,   132,    18,    19,    20,   132,    22,    23,
      24,    25,    26,   514,   133,   132,   315,   316,   317,   318,
     319,   443,   444,   132,   132,   131,    71,   132,    42,    16,
     132,    45,   133,    47,    48,   132,   458,    51,   132,   132,
     132,   463,   132,   463,   132,   132,   132,   132,    62,   132,
     132,   132,    66,    67,    68,   132,    72,   133,   509,   133,
      74,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    92,    93,    94,    95,    96,    97,
     115,     5,     6,   526,     4,   133,   133,    11,    12,    13,
      14,    15,   133,    17,   133,   109,   110,   519,   541,   133,
     114,   133,   116,   117,    54,   527,   607,   608,   609,   610,
     611,    54,   131,    13,   131,    32,    73,   539,   123,    37,
      39,   133,    98,   133,   131,    98,    50,   131,    98,     5,
       6,    98,   131,    98,   556,    11,    12,    13,    14,    15,
      98,    17,   564,   565,   566,   567,   568,    28,    50,   592,
     593,   132,   132,   132,    64,   133,    50,    81,    55,    83,
      75,   124,     4,   125,   586,    89,    90,    91,    21,    57,
     126,    63,   594,   133,    50,    99,   100,   101,   102,   103,
     104,   105,   106,   131,   133,   131,     5,     6,   133,   124,
     612,   132,    11,    12,    13,    14,    15,    34,    17,    57,
     133,   133,   133,   133,   133,    81,   133,    83,   132,    65,
     134,    13,    13,    89,    90,    91,   132,     4,   132,   132,
     132,   132,   131,    99,   100,   101,   102,   103,   104,   105,
     106,    50,     5,     6,   133,    35,   132,    13,    11,    12,
      13,    14,    15,   133,    17,    16,   133,   133,   133,   133,
      16,    16,    16,    16,    23,   100,   132,   196,   134,   527,
     153,   189,    81,   342,    83,   586,   518,   612,   402,    -1,
      89,    90,    91,   519,   182,    -1,   404,    50,    -1,    -1,
      99,   100,   101,   102,   103,   104,   105,   106,    -1,     5,
       6,    -1,    -1,    -1,    -1,    11,    12,    13,    14,    15,
      -1,    17,    -1,    -1,    -1,    -1,    -1,    -1,    81,    -1,
      83,    -1,    -1,   132,    -1,   134,    89,    90,    91,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    99,   100,   101,   102,
     103,   104,   105,   106,    50,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   132,
      -1,   134,    -1,    -1,    -1,    81,    -1,    83,    -1,    -1,
      -1,    -1,    -1,    89,    90,    91,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    99,   100,   101,   102,   103,   104,   105,
     106,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   134
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    18,    19,    20,    22,    23,    24,    25,    26,    42,
      45,    47,    48,    51,    62,    66,    67,    68,    74,   109,
     110,   114,   116,   117,   136,   137,   138,   139,   146,   147,
     148,   149,   150,   151,   152,   162,   168,   169,   202,   210,
      12,    56,   134,   196,   198,   196,   196,   196,    43,    46,
      28,   198,    52,    56,   107,    52,    56,   107,    52,    52,
      52,    52,    52,    56,   107,    68,    52,    27,    42,    47,
      48,   140,   142,   140,     0,    27,   196,    12,    33,   198,
     198,   198,    49,   198,   198,   198,   198,   198,   198,   198,
     198,   198,   198,   198,   198,   198,   130,   170,   198,    57,
     131,   141,    57,   129,   153,   134,   198,    33,   132,   163,
      29,   180,   171,   173,   198,    33,   132,    57,   108,   170,
     170,    69,   203,   204,   170,    62,   111,   113,   114,   114,
      49,   115,   198,   142,   198,     7,   118,   119,   120,   121,
     122,   154,   156,   197,   198,    27,   154,    44,    32,   132,
     191,   195,   170,   131,   172,   180,    16,    27,   198,   214,
     215,   217,   218,   219,   198,    11,     5,     6,    11,    13,
      14,    15,    17,    50,   106,   199,   200,   201,   170,    70,
     205,   112,   132,   132,   112,   115,   108,   198,   115,    28,
     132,   132,   132,   132,   132,    28,   131,   155,    33,     7,
     153,   133,   132,   132,   191,     3,     4,    81,    83,    89,
      90,    91,    99,   100,   101,   102,   103,   104,   105,   175,
     194,   198,   173,   170,     5,     6,    50,   132,   174,   175,
     179,   198,   199,   153,   133,   131,   216,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
     235,   132,   170,    13,    15,    13,    15,   132,   199,    71,
     206,   198,   214,   217,   198,   198,    11,   170,   143,   145,
     198,   143,   198,   198,   198,   198,     7,   198,   157,   196,
     156,   198,   154,   164,   199,   191,   133,   191,   191,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
     132,    16,    16,    32,    41,   195,    13,    15,    50,   174,
     199,    13,    15,   174,   174,     5,     6,     7,     8,     9,
     154,   170,    53,    64,   217,   223,   224,   226,   233,   132,
     220,   154,   133,   198,    72,   207,   170,   133,   133,   115,
     170,   170,   131,   144,   180,   170,   133,   133,   133,   133,
     133,   133,   131,   161,   180,    36,    38,    40,   158,    28,
     131,   133,   165,   133,   179,   179,   179,   179,   179,   179,
     179,   179,    92,    93,    94,    95,    96,    97,   176,   177,
     178,   179,   179,   176,   175,   198,   199,   198,   199,    32,
      50,    30,    31,   133,   174,   174,   174,   174,   174,    28,
      54,    54,   131,   225,   131,    13,    32,   222,   133,    73,
     208,   170,   170,   198,   145,   170,   196,   123,   181,    39,
     160,   160,    37,   159,   157,   199,   170,   133,   133,   131,
      98,    98,   131,    98,    98,   131,    98,    98,    28,    50,
     199,   132,   157,   132,   132,   226,   224,   133,    50,    55,
     221,    53,    61,   212,   199,    75,   209,   170,   124,   125,
     184,   196,   196,   160,   180,   179,   179,   179,   179,   179,
     179,   179,   179,   179,   179,     4,   166,   199,   180,   154,
     198,   227,   229,   199,    21,   234,    58,    59,    60,   211,
     185,   187,   198,    32,   132,   192,   195,   126,   182,    57,
     158,   196,   181,   133,   178,   178,   133,   177,   177,   131,
     176,   176,   133,   199,   131,   133,   167,   181,   133,   131,
     133,   228,   212,   212,   212,    63,   213,   131,   186,   132,
     192,     3,     4,   118,   119,   120,   121,   122,   193,   124,
      34,   183,   191,    57,   184,   133,   133,   133,   133,   179,
     133,   133,   199,   184,   213,   229,    65,    13,   170,   187,
     192,   133,   192,   192,   132,   132,   132,   132,   132,   188,
     190,   198,    13,   170,   158,   191,   182,   133,   182,   198,
     133,   198,   198,   198,   198,   198,   131,   189,   127,   128,
      35,   158,   183,   183,   132,   133,   133,   133,   133,   133,
     190,    13,   170,   170,   198,   230,   232,    16,    16,    16,
      16,    16,   131,   133,   231,   199,   199,   199,   199,   199,
     232
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

  case 36:

/* Line 1464 of yacc.c  */
#line 149 "dmlyacc.yxx"
    { parsedData->insertGrantee((yyvsp[(1) - (1)].stringval)); }
    break;

  case 37:

/* Line 1464 of yacc.c  */
#line 152 "dmlyacc.yxx"
    {
            parsedData->setStmtType(DclStatement);
            parsedData->setTableName((yyvsp[(4) - (8)].stringval));
            parsedData->constructDclNodes(GRANTACCESS);
    }
    break;

  case 38:

/* Line 1464 of yacc.c  */
#line 159 "dmlyacc.yxx"
    {
            parsedData->setStmtType(DclStatement);
            parsedData->setTableName((yyvsp[(4) - (7)].stringval));
            parsedData->constructDclNodes(REVOKEACCESS);
    }
    break;

  case 39:

/* Line 1464 of yacc.c  */
#line 166 "dmlyacc.yxx"
    {
            parsedData->setStmtType(CopyTableStatement);
            parsedData->setPKTableName((yyvsp[(3) - (15)].stringval));
            parsedData->setCreateTbl();
            free((yyvsp[(3) - (15)].stringval));
        }
    break;

  case 40:

/* Line 1464 of yacc.c  */
#line 173 "dmlyacc.yxx"
    {
            parsedData->setStmtType(CopyTableStatement);
            parsedData->setPKTableName((yyvsp[(3) - (15)].stringval));
            free((yyvsp[(3) - (15)].stringval));
        }
    break;

  case 41:

/* Line 1464 of yacc.c  */
#line 180 "dmlyacc.yxx"
    {
            parsedData->setStmtType(CompactTableStatement);
            parsedData->setTableName((yyvsp[(3) - (3)].stringval));
            free((yyvsp[(3) - (3)].stringval));
        }
    break;

  case 42:

/* Line 1464 of yacc.c  */
#line 187 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetTables);
	}
    break;

  case 43:

/* Line 1464 of yacc.c  */
#line 192 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetColumns);
        }
    break;

  case 44:

/* Line 1464 of yacc.c  */
#line 197 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetIndexes);
                   
        }
    break;

  case 45:

/* Line 1464 of yacc.c  */
#line 203 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetPriIndex);
        }
    break;

  case 46:

/* Line 1464 of yacc.c  */
#line 208 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetCatalogs);
        }
    break;

  case 47:

/* Line 1464 of yacc.c  */
#line 213 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetTableType);
        }
    break;

  case 48:

/* Line 1464 of yacc.c  */
#line 218 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetDataType);
        }
    break;

  case 49:

/* Line 1464 of yacc.c  */
#line 223 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetImportKey);
        }
    break;

  case 50:

/* Line 1464 of yacc.c  */
#line 228 "dmlyacc.yxx"
    {
            parsedData->setStmtType(MetaStatement);
            parsedData->setResultSetPlan(GetExportKey);
        }
    break;

  case 51:

/* Line 1464 of yacc.c  */
#line 234 "dmlyacc.yxx"
    {
            parsedData->setStmtType(SelectStatement);
            parsedData->setCacheWorthy(true);
        }
    break;

  case 52:

/* Line 1464 of yacc.c  */
#line 240 "dmlyacc.yxx"
    {
           parsedData->setExplain();
	}
    break;

  case 54:

/* Line 1464 of yacc.c  */
#line 246 "dmlyacc.yxx"
    { 
            parsedData->setDistinct();
        }
    break;

  case 60:

/* Line 1464 of yacc.c  */
#line 258 "dmlyacc.yxx"
    {
            parsedData->insertFieldAlias((char*)(yyvsp[(3) - (3)].stringval));
            free((char*)(yyvsp[(3) - (3)].stringval));
        }
    break;

  case 64:

/* Line 1464 of yacc.c  */
#line 268 "dmlyacc.yxx"
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

  case 65:

/* Line 1464 of yacc.c  */
#line 282 "dmlyacc.yxx"
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

  case 66:

/* Line 1464 of yacc.c  */
#line 295 "dmlyacc.yxx"
    {
            parsedData->insertJoinType(INNER_JOIN);
        }
    break;

  case 72:

/* Line 1464 of yacc.c  */
#line 307 "dmlyacc.yxx"
    {
            parsedData->insertJoinType(INNER_JOIN);
        }
    break;

  case 73:

/* Line 1464 of yacc.c  */
#line 313 "dmlyacc.yxx"
    {
            parsedData->setStmtType(InsertStatement);
            parsedData->setTableName((yyvsp[(3) - (9)].stringval)); 
            free((yyvsp[(3) - (9)].stringval));
        }
    break;

  case 77:

/* Line 1464 of yacc.c  */
#line 326 "dmlyacc.yxx"
    {
            parsedData->insertValue((char*)(yyvsp[(1) - (1)].stringval));
            free((yyvsp[(1) - (1)].stringval));
        }
    break;

  case 78:

/* Line 1464 of yacc.c  */
#line 332 "dmlyacc.yxx"
    {
            parsedData->insertValue((char*)(yyvsp[(2) - (2)].stringval));
            free((yyvsp[(2) - (2)].stringval));
        }
    break;

  case 80:

/* Line 1464 of yacc.c  */
#line 340 "dmlyacc.yxx"
    {
            parsedData->insertInValue((char*)(yyvsp[(1) - (1)].stringval));
            free((yyvsp[(1) - (1)].stringval));
        }
    break;

  case 81:

/* Line 1464 of yacc.c  */
#line 346 "dmlyacc.yxx"
    {
            parsedData->insertInValue((char*)(yyvsp[(2) - (2)].stringval));
            free((yyvsp[(2) - (2)].stringval));
        }
    break;

  case 82:

/* Line 1464 of yacc.c  */
#line 353 "dmlyacc.yxx"
    {
            parsedData->setStmtType(DeleteStatement);
            parsedData->setTableName((yyvsp[(3) - (5)].stringval)); 
            free((yyvsp[(3) - (5)].stringval));
	}
    break;

  case 83:

/* Line 1464 of yacc.c  */
#line 361 "dmlyacc.yxx"
    {
            parsedData->setStmtType(UpdateStatement);
            parsedData->setTableName((yyvsp[(2) - (6)].stringval)); 
            free( (yyvsp[(2) - (6)].stringval) );
	}
    break;

  case 89:

/* Line 1464 of yacc.c  */
#line 379 "dmlyacc.yxx"
    {
           parsedData->insertUpdateExpression( (char*) (yyvsp[(1) - (3)].stringval), (Expression* ) (yyvsp[(3) - (3)].Expression));
           free( (yyvsp[(1) - (3)].stringval) ); free((yyvsp[(2) - (3)].stringval));
        }
    break;

  case 90:

/* Line 1464 of yacc.c  */
#line 384 "dmlyacc.yxx"
    { 
            parsedData->insertUpdateValue( (char*) (yyvsp[(1) - (3)].stringval), (char*) (yyvsp[(3) - (3)].stringval));
            free( (yyvsp[(1) - (3)].stringval) ); free((yyvsp[(2) - (3)].stringval));free( (yyvsp[(3) - (3)].stringval) ); 
        }
    break;

  case 91:

/* Line 1464 of yacc.c  */
#line 389 "dmlyacc.yxx"
    {
            parsedData->insertUpdateValue( (char*) (yyvsp[(1) - (3)].stringval), (char*) (yyvsp[(3) - (3)].stringval));
            free( (yyvsp[(1) - (3)].stringval) ); free((yyvsp[(2) - (3)].stringval));free( (yyvsp[(3) - (3)].stringval) );
        }
    break;

  case 92:

/* Line 1464 of yacc.c  */
#line 395 "dmlyacc.yxx"
    {
            Expression* exp;
            exp=parsedData->insertExpression((Expression *)(yyvsp[(1) - (3)].Expression), division, (Expression *)(yyvsp[(3) - (3)].Expression));
            (yyval.Expression)=exp;
        }
    break;

  case 93:

/* Line 1464 of yacc.c  */
#line 401 "dmlyacc.yxx"
    {
            Expression* exp;
            exp=parsedData->insertExpression((Expression *)(yyvsp[(1) - (3)].Expression), modulus, (Expression *)(yyvsp[(3) - (3)].Expression));
            (yyval.Expression)=exp;
        }
    break;

  case 94:

/* Line 1464 of yacc.c  */
#line 407 "dmlyacc.yxx"
    {
            Expression* exp;
            exp=parsedData->insertExpression((Expression *)(yyvsp[(1) - (3)].Expression), multiplication, (Expression *)(yyvsp[(3) - (3)].Expression));
            (yyval.Expression)=exp;
        }
    break;

  case 95:

/* Line 1464 of yacc.c  */
#line 413 "dmlyacc.yxx"
    {
            Expression* exp;
            exp=parsedData->insertExpression((Expression *)(yyvsp[(1) - (3)].Expression), addition, (Expression *)(yyvsp[(3) - (3)].Expression));
            (yyval.Expression)=exp;
        }
    break;

  case 96:

/* Line 1464 of yacc.c  */
#line 419 "dmlyacc.yxx"
    {
            Expression* exp;
            exp=parsedData->insertExpression((Expression *)(yyvsp[(1) - (3)].Expression), subtraction, (Expression *)(yyvsp[(3) - (3)].Expression));
            (yyval.Expression)=exp;
        }
    break;

  case 97:

/* Line 1464 of yacc.c  */
#line 425 "dmlyacc.yxx"
    {
            (yyval.Expression)=(yyvsp[(2) - (3)].Expression);
        }
    break;

  case 98:

/* Line 1464 of yacc.c  */
#line 429 "dmlyacc.yxx"
    {
            (yyval.Expression) = (yyvsp[(2) - (2)].Expression);
        }
    break;

  case 99:

/* Line 1464 of yacc.c  */
#line 433 "dmlyacc.yxx"
    {
            (yyval.Expression) = (yyvsp[(2) - (2)].Expression);
        }
    break;

  case 102:

/* Line 1464 of yacc.c  */
#line 440 "dmlyacc.yxx"
    {
              Expression* exp;
              parsedData->setFunctionType(DATEDIFF);
              exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (6)].Expression), DATEDIFF, (Expression *)(yyvsp[(5) - (6)].Expression));
            (yyval.Expression)=exp;
        }
    break;

  case 103:

/* Line 1464 of yacc.c  */
#line 447 "dmlyacc.yxx"
    {
	         Expression* exp;
             parsedData->setFunctionType((*(FunctionType *)(yyvsp[(6) - (7)].FunctionType)));
             exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (7)].Expression), (*(FunctionType *)(yyvsp[(6) - (7)].FunctionType)), (Expression *)(yyvsp[(5) - (7)].Expression));
             (yyval.Expression)=exp;
	    }
    break;

  case 104:

/* Line 1464 of yacc.c  */
#line 454 "dmlyacc.yxx"
    {
             Expression* exp;
             //parsedData->setFunctionType((*(FunctionType *)$6));
             parsedData->setFunctionType((FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+3));
             exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (7)].Expression), (FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+3), (Expression *)(yyvsp[(5) - (7)].Expression));
             (yyval.Expression)=exp;
        }
    break;

  case 105:

/* Line 1464 of yacc.c  */
#line 462 "dmlyacc.yxx"
    {
              Expression* exp;
              parsedData->setFunctionType(TIMEDIFF);
              exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (6)].Expression), TIMEDIFF, (Expression *)(yyvsp[(5) - (6)].Expression));
            (yyval.Expression)=exp;
        }
    break;

  case 106:

/* Line 1464 of yacc.c  */
#line 469 "dmlyacc.yxx"
    {
             Expression* exp;
             parsedData->setFunctionType((*(FunctionType *)(yyvsp[(6) - (7)].FunctionType)));
             exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (7)].Expression), (*(FunctionType *)(yyvsp[(6) - (7)].FunctionType)), (Expression *)(yyvsp[(5) - (7)].Expression));
             (yyval.Expression)=exp;
        }
    break;

  case 107:

/* Line 1464 of yacc.c  */
#line 476 "dmlyacc.yxx"
    {
             Expression* exp;
             parsedData->setFunctionType((FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+3));
             exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (7)].Expression), (FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+3), (Expression *)(yyvsp[(5) - (7)].Expression));
             (yyval.Expression)=exp;
        }
    break;

  case 108:

/* Line 1464 of yacc.c  */
#line 483 "dmlyacc.yxx"
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

  case 109:

/* Line 1464 of yacc.c  */
#line 494 "dmlyacc.yxx"
    {
             Expression* exp;
             parsedData->setFunctionType((FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+12));
             exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (7)].Expression), (FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+12), (Expression *)(yyvsp[(5) - (7)].Expression));
             (yyval.Expression)=exp;
        }
    break;

  case 110:

/* Line 1464 of yacc.c  */
#line 501 "dmlyacc.yxx"
    {
             Expression* exp;
             parsedData->setFunctionType((FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+15));
             exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (7)].Expression), (FunctionType)((int)(*(FunctionType *)(yyvsp[(6) - (7)].FunctionType))+15), (Expression *)(yyvsp[(5) - (7)].Expression));
             (yyval.Expression)=exp;
        }
    break;

  case 111:

/* Line 1464 of yacc.c  */
#line 508 "dmlyacc.yxx"
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

  case 112:

/* Line 1464 of yacc.c  */
#line 520 "dmlyacc.yxx"
    {
            Expression* exp;
            parsedData->setFunctionType(DATEFROMTIMESTAMP);
            exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (4)].Expression), DATEFROMTIMESTAMP, NULL);
            (yyval.Expression)=exp;

        }
    break;

  case 113:

/* Line 1464 of yacc.c  */
#line 528 "dmlyacc.yxx"
    {
            Expression* exp;
            parsedData->setFunctionType(TIMEFROMTIMESTAMP);
            exp=parsedData->insertExpression((Expression *)(yyvsp[(3) - (4)].Expression), TIMEFROMTIMESTAMP, NULL);
            (yyval.Expression)=exp;
        }
    break;

  case 114:

/* Line 1464 of yacc.c  */
#line 536 "dmlyacc.yxx"
    {
           FunctionType val = *(FunctionType *)(yyvsp[(1) - (1)].FunctionType);
           (yyval.FunctionType) = &val;
        }
    break;

  case 115:

/* Line 1464 of yacc.c  */
#line 541 "dmlyacc.yxx"
    {
           FunctionType val = *(FunctionType *)(yyvsp[(1) - (1)].FunctionType);
           (yyval.FunctionType) = &val;
        }
    break;

  case 116:

/* Line 1464 of yacc.c  */
#line 547 "dmlyacc.yxx"
    { 
             FunctionType val = TIMEADDWITHHOUR;
             (yyval.FunctionType) = &val;
        }
    break;

  case 117:

/* Line 1464 of yacc.c  */
#line 552 "dmlyacc.yxx"
    {
             FunctionType val = TIMEADDWITHMIN;
             (yyval.FunctionType) = &val;
        }
    break;

  case 118:

/* Line 1464 of yacc.c  */
#line 557 "dmlyacc.yxx"
    {
             FunctionType val = TIMEADDWITHSEC;
             (yyval.FunctionType) = &val;
        }
    break;

  case 119:

/* Line 1464 of yacc.c  */
#line 563 "dmlyacc.yxx"
    {
	        FunctionType val = DATEADDWITHYEAR;
            (yyval.FunctionType) = &val;
	    }
    break;

  case 120:

/* Line 1464 of yacc.c  */
#line 568 "dmlyacc.yxx"
    {
	        FunctionType val = DATEADDWITHMON;
            (yyval.FunctionType) = &val;
        }
    break;

  case 121:

/* Line 1464 of yacc.c  */
#line 573 "dmlyacc.yxx"
    {
            FunctionType val = DATEADDWITHDAY;
            (yyval.FunctionType) = &val;
        }
    break;

  case 122:

/* Line 1464 of yacc.c  */
#line 579 "dmlyacc.yxx"
    {
            Expression* exp;
            exp=parsedData->insertExpression((char *)(yyvsp[(1) - (1)].stringval));
            free((yyvsp[(1) - (1)].stringval));
            (yyval.Expression)=exp;
        }
    break;

  case 123:

/* Line 1464 of yacc.c  */
#line 586 "dmlyacc.yxx"
    {
            Expression* exp;
            bool flag = false;
            exp=parsedData->insertExpression((char *)(yyvsp[(1) - (1)].stringval), flag);
            free((yyvsp[(1) - (1)].stringval));
            (yyval.Expression)=exp;
        }
    break;

  case 124:

/* Line 1464 of yacc.c  */
#line 594 "dmlyacc.yxx"
    {
            Expression* exp;
            exp=parsedData->insertExpression("NULL");
            free((yyvsp[(1) - (1)].stringval));
            (yyval.Expression)=exp;
        }
    break;

  case 125:

/* Line 1464 of yacc.c  */
#line 603 "dmlyacc.yxx"
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

  case 131:

/* Line 1464 of yacc.c  */
#line 624 "dmlyacc.yxx"
    {
            parsedData->setLimit(atoi((yyvsp[(2) - (2)].stringval)), 0);
        }
    break;

  case 132:

/* Line 1464 of yacc.c  */
#line 628 "dmlyacc.yxx"
    {
            parsedData->setLimit(atoi((yyvsp[(2) - (4)].stringval)), atoi((yyvsp[(4) - (4)].stringval)));
        }
    break;

  case 139:

/* Line 1464 of yacc.c  */
#line 642 "dmlyacc.yxx"
    {
            parsedData->insertGroupField((char*)(yyvsp[(1) - (1)].stringval));
            free( (yyvsp[(1) - (1)].stringval) );
        }
    break;

  case 143:

/* Line 1464 of yacc.c  */
#line 653 "dmlyacc.yxx"
    {
            parsedData->insertOrderByField((char*)(yyvsp[(1) - (1)].stringval));
            free( (yyvsp[(1) - (1)].stringval) );
        }
    break;

  case 144:

/* Line 1464 of yacc.c  */
#line 658 "dmlyacc.yxx"
    {
            parsedData->insertOrderByField((char*)(yyvsp[(1) - (2)].stringval));
            free( (yyvsp[(1) - (2)].stringval) );
        }
    break;

  case 145:

/* Line 1464 of yacc.c  */
#line 663 "dmlyacc.yxx"
    {
            parsedData->insertOrderByField((char*)(yyvsp[(1) - (2)].stringval), true);
            free( (yyvsp[(1) - (2)].stringval) );
        }
    break;

  case 146:

/* Line 1464 of yacc.c  */
#line 669 "dmlyacc.yxx"
    {
            Predicate *pred;
            pred = parsedData->insertPredicate((Predicate*) (yyvsp[(1) - (3)].predicate), OpOr, (Predicate*) (yyvsp[(3) - (3)].predicate));
            //parsedData->setCondition((Predicate*)pred);
            (yyval.predicate)= pred;

        }
    break;

  case 147:

/* Line 1464 of yacc.c  */
#line 677 "dmlyacc.yxx"
    {
            Predicate *pred;
            pred = parsedData->insertPredicate((Predicate*) (yyvsp[(1) - (3)].predicate), OpAnd, (Predicate*) (yyvsp[(3) - (3)].predicate));
            //parsedData->setCondition((Predicate*)pred);
            (yyval.predicate)= pred;
        }
    break;

  case 148:

/* Line 1464 of yacc.c  */
#line 683 "dmlyacc.yxx"
    { (yyval.predicate)=(yyvsp[(2) - (3)].predicate); }
    break;

  case 149:

/* Line 1464 of yacc.c  */
#line 685 "dmlyacc.yxx"
    {
            Predicate *pred;
            pred = parsedData->insertPredicate((Predicate*) (yyvsp[(3) - (4)].predicate), OpNot, NULL);
            //parsedData->setCondition((Predicate*)pred);
            (yyval.predicate)= pred;

        }
    break;

  case 150:

/* Line 1464 of yacc.c  */
#line 693 "dmlyacc.yxx"
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

  case 151:

/* Line 1464 of yacc.c  */
#line 709 "dmlyacc.yxx"
    {
            Predicate *pred;
            pred = parsedData->insertPredicate((Predicate*) (yyvsp[(1) - (3)].predicate), OpOr, (Predicate*) (yyvsp[(3) - (3)].predicate));
            parsedData->setHavingCondition((Predicate*)pred);
            (yyval.predicate)= pred;

        }
    break;

  case 152:

/* Line 1464 of yacc.c  */
#line 717 "dmlyacc.yxx"
    {
            Predicate *pred;
            pred = parsedData->insertPredicate((Predicate*) (yyvsp[(1) - (3)].predicate), OpAnd, (Predicate*) (yyvsp[(3) - (3)].predicate));
            parsedData->setHavingCondition((Predicate*)pred);
            (yyval.predicate)= pred;
        }
    break;

  case 153:

/* Line 1464 of yacc.c  */
#line 723 "dmlyacc.yxx"
    { (yyval.predicate)=(yyvsp[(2) - (3)].predicate); }
    break;

  case 154:

/* Line 1464 of yacc.c  */
#line 725 "dmlyacc.yxx"
    {
            Predicate *pred;
            pred = parsedData->insertPredicate((Predicate*) (yyvsp[(3) - (4)].predicate), OpNot, NULL);
            parsedData->setHavingCondition((Predicate*)pred);
            (yyval.predicate)= pred;

        }
    break;

  case 155:

/* Line 1464 of yacc.c  */
#line 733 "dmlyacc.yxx"
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

  case 156:

/* Line 1464 of yacc.c  */
#line 749 "dmlyacc.yxx"
    {
            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(5) - (6)].stringval));
            Predicate *pred;
            void **ptr = parsedData->insertCondValueAndGetPtr((char*)(yyvsp[(3) - (6)].stringval), (char*)(yyvsp[(6) - (6)].stringval), false, AGG_MIN, true);
            pred = parsedData->insertPredicate((char*) (yyvsp[(3) - (6)].stringval), op, ptr, AGG_MIN);
            free( (yyvsp[(1) - (6)].stringval) ); free ((yyvsp[(3) - (6)].stringval)); free ((yyvsp[(5) - (6)].stringval)); free ((yyvsp[(6) - (6)].stringval));
            (yyval.predicate)=pred;
        }
    break;

  case 157:

/* Line 1464 of yacc.c  */
#line 758 "dmlyacc.yxx"
    {
            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(5) - (6)].stringval));
            Predicate *pred;
            void **ptr = parsedData->insertCondValueAndGetPtr((char*)(yyvsp[(3) - (6)].stringval), (char*)(yyvsp[(6) - (6)].stringval), false, AGG_MAX, true);
            pred = parsedData->insertPredicate((char*) (yyvsp[(3) - (6)].stringval), op, ptr, AGG_MAX);
            free( (yyvsp[(1) - (6)].stringval) ); free ((yyvsp[(3) - (6)].stringval)); free ((yyvsp[(5) - (6)].stringval)); free ((yyvsp[(6) - (6)].stringval));
            (yyval.predicate)=pred;
        }
    break;

  case 158:

/* Line 1464 of yacc.c  */
#line 767 "dmlyacc.yxx"
    {
            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(5) - (6)].stringval));
            Predicate *pred;
            void **ptr = parsedData->insertCondValueAndGetPtr((char*)(yyvsp[(3) - (6)].stringval), (char*)(yyvsp[(6) - (6)].stringval), false, AGG_SUM, true);
            pred = parsedData->insertPredicate((char*) (yyvsp[(3) - (6)].stringval), op, ptr, AGG_SUM);
            free( (yyvsp[(1) - (6)].stringval) ); free ((yyvsp[(3) - (6)].stringval)); free ((yyvsp[(5) - (6)].stringval)); free ((yyvsp[(6) - (6)].stringval));
            (yyval.predicate)=pred;
        }
    break;

  case 159:

/* Line 1464 of yacc.c  */
#line 776 "dmlyacc.yxx"
    {
            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(5) - (6)].stringval));
            Predicate *pred;
            void **ptr = parsedData->insertCondValueAndGetPtr((char*)(yyvsp[(3) - (6)].stringval), (char*)(yyvsp[(6) - (6)].stringval), false, AGG_AVG, true);
            pred = parsedData->insertPredicate((char*) (yyvsp[(3) - (6)].stringval), op, ptr, AGG_AVG);
            free( (yyvsp[(1) - (6)].stringval) ); free ((yyvsp[(3) - (6)].stringval)); free ((yyvsp[(5) - (6)].stringval)); free ((yyvsp[(6) - (6)].stringval));
            (yyval.predicate)=pred;
        }
    break;

  case 160:

/* Line 1464 of yacc.c  */
#line 785 "dmlyacc.yxx"
    {
            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(5) - (6)].stringval));
            Predicate *pred;
            void **ptr = parsedData->insertCondValueAndGetPtr((char*)(yyvsp[(3) - (6)].stringval), (char*)(yyvsp[(6) - (6)].stringval), false, AGG_COUNT, true);
            pred = parsedData->insertPredicate((char*) (yyvsp[(3) - (6)].stringval), op, ptr, AGG_COUNT);
            free( (yyvsp[(1) - (6)].stringval) ); free ((yyvsp[(3) - (6)].stringval)); free ((yyvsp[(5) - (6)].stringval)); free ((yyvsp[(6) - (6)].stringval));
            (yyval.predicate)=pred;
        }
    break;

  case 161:

/* Line 1464 of yacc.c  */
#line 796 "dmlyacc.yxx"
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

  case 162:

/* Line 1464 of yacc.c  */
#line 807 "dmlyacc.yxx"
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

  case 163:

/* Line 1464 of yacc.c  */
#line 818 "dmlyacc.yxx"
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

  case 164:

/* Line 1464 of yacc.c  */
#line 834 "dmlyacc.yxx"
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

  case 165:

/* Line 1464 of yacc.c  */
#line 860 "dmlyacc.yxx"
    {
            Predicate *pred;
            parsedData->insertCondValue((char*) (yyvsp[(1) - (4)].stringval));
            pred = parsedData->insertNullPredicate((char*) (yyvsp[(1) - (4)].stringval), OpIsNull, false);
            free( (yyvsp[(1) - (4)].stringval) ); free((yyvsp[(2) - (4)].stringval)); free( (yyvsp[(3) - (4)].stringval) );
            (yyval.predicate)=pred;  
        }
    break;

  case 166:

/* Line 1464 of yacc.c  */
#line 868 "dmlyacc.yxx"
    {
            Predicate *pred;
            parsedData->insertCondValue((char*) (yyvsp[(1) - (3)].stringval));
            pred = parsedData->insertNullPredicate((char*) (yyvsp[(1) - (3)].stringval), OpIsNull, true);
            free( (yyvsp[(1) - (3)].stringval) ); free((yyvsp[(2) - (3)].stringval)); free( (yyvsp[(3) - (3)].stringval) );
            (yyval.predicate)=pred;  
        }
    break;

  case 167:

/* Line 1464 of yacc.c  */
#line 876 "dmlyacc.yxx"
    {
            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(2) - (3)].stringval));
            Predicate *pred;
            pred = parsedData->insertPredicate(((Expression*)(yyvsp[(1) - (3)].Expression)), op, ((Expression*)(yyvsp[(3) - (3)].Expression)));
            (yyval.predicate)=pred;
 
        }
    break;

  case 168:

/* Line 1464 of yacc.c  */
#line 884 "dmlyacc.yxx"
    {

            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(2) - (3)].stringval));
            parsedData->insertCondValue((char*) (yyvsp[(3) - (3)].stringval));
            Predicate *pred;
            pred = parsedData->insertPredicate(((Expression*)(yyvsp[(1) - (3)].Expression)), op, (char*) (yyvsp[(3) - (3)].stringval));
            (yyval.predicate)=pred;
            
        }
    break;

  case 169:

/* Line 1464 of yacc.c  */
#line 894 "dmlyacc.yxx"
    {
            ComparisionOp  op = AllDataType::getComparisionOperator((char*)(yyvsp[(2) - (3)].stringval));
            void **ptr = parsedData->insertCondValueAndGetPtr((char*)"dummy", (char*)(yyvsp[(3) - (3)].stringval), false, AGG_UNKNOWN, false, true);
            Predicate *pred;
            pred = parsedData->insertPredicate(((Expression*)(yyvsp[(1) - (3)].Expression)), op, ptr);
            (yyval.predicate)=pred;
        }
    break;

  case 170:

/* Line 1464 of yacc.c  */
#line 903 "dmlyacc.yxx"
    { (yyval.stringval)=(char*) 1;
	}
    break;

  case 171:

/* Line 1464 of yacc.c  */
#line 906 "dmlyacc.yxx"
    { (yyval.stringval)=(char*) 0; }
    break;

  case 172:

/* Line 1464 of yacc.c  */
#line 909 "dmlyacc.yxx"
    {
            parsedData->insertTableName((char*)(yyvsp[(1) - (1)].stringval));
            free( (yyvsp[(1) - (1)].stringval) );
        }
    break;

  case 173:

/* Line 1464 of yacc.c  */
#line 914 "dmlyacc.yxx"
    {
            parsedData->insertTableName((char*)(yyvsp[(1) - (3)].stringval), (char*)(yyvsp[(3) - (3)].stringval));
            free( (yyvsp[(1) - (3)].stringval) ); free((yyvsp[(3) - (3)].stringval));
        }
    break;

  case 174:

/* Line 1464 of yacc.c  */
#line 919 "dmlyacc.yxx"
    {
            parsedData->insertTableName((char*)(yyvsp[(1) - (2)].stringval), (char*)(yyvsp[(2) - (2)].stringval));
            free( (yyvsp[(1) - (2)].stringval) ); free((yyvsp[(2) - (2)].stringval));
        }
    break;

  case 175:

/* Line 1464 of yacc.c  */
#line 925 "dmlyacc.yxx"
    {
            parsedData->insertField((char*)(yyvsp[(1) - (1)].stringval));
            free( (yyvsp[(1) - (1)].stringval) );
            
        }
    break;

  case 176:

/* Line 1464 of yacc.c  */
#line 931 "dmlyacc.yxx"
    { 
            parsedData->insertField((char*)(yyvsp[(3) - (4)].stringval), AGG_MIN);
            free( (yyvsp[(1) - (4)].stringval) );
        }
    break;

  case 177:

/* Line 1464 of yacc.c  */
#line 936 "dmlyacc.yxx"
    { 
            parsedData->insertField((char*)(yyvsp[(3) - (4)].stringval), AGG_MAX);
            free( (yyvsp[(1) - (4)].stringval) );
        }
    break;

  case 178:

/* Line 1464 of yacc.c  */
#line 941 "dmlyacc.yxx"
    { 
            parsedData->insertField((char*)(yyvsp[(3) - (4)].stringval), AGG_SUM);
            free( (yyvsp[(1) - (4)].stringval) );
        }
    break;

  case 179:

/* Line 1464 of yacc.c  */
#line 946 "dmlyacc.yxx"
    { 
            parsedData->insertField((char*)(yyvsp[(3) - (4)].stringval), AGG_AVG);
            free( (yyvsp[(1) - (4)].stringval) );
        }
    break;

  case 180:

/* Line 1464 of yacc.c  */
#line 951 "dmlyacc.yxx"
    { 
            parsedData->insertField((char*)(yyvsp[(3) - (4)].stringval), AGG_COUNT);
            free( (yyvsp[(1) - (4)].stringval) );
        }
    break;

  case 181:

/* Line 1464 of yacc.c  */
#line 956 "dmlyacc.yxx"
    { 
            parsedData->insertField("*", AGG_COUNT);
            free( (yyvsp[(1) - (4)].stringval) );
        }
    break;

  case 182:

/* Line 1464 of yacc.c  */
#line 961 "dmlyacc.yxx"
    { 
            parsedData->insertField("*");
        }
    break;

  case 183:

/* Line 1464 of yacc.c  */
#line 965 "dmlyacc.yxx"
    {
            parsedData->insertField("*");
        }
    break;

  case 184:

/* Line 1464 of yacc.c  */
#line 969 "dmlyacc.yxx"
    { (yyval.stringval) = (yyvsp[(1) - (1)].stringval); }
    break;

  case 185:

/* Line 1464 of yacc.c  */
#line 970 "dmlyacc.yxx"
    { (yyval.stringval) = (yyvsp[(2) - (3)].stringval); }
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

  case 190:

/* Line 1464 of yacc.c  */
#line 976 "dmlyacc.yxx"
    { (yyval.stringval) = (yyvsp[(1) - (1)].stringval); }
    break;

  case 191:

/* Line 1464 of yacc.c  */
#line 977 "dmlyacc.yxx"
    { (yyval.stringval) = (char*) 0; }
    break;

  case 192:

/* Line 1464 of yacc.c  */
#line 979 "dmlyacc.yxx"
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

  case 193:

/* Line 1464 of yacc.c  */
#line 991 "dmlyacc.yxx"
    { (yyval.stringval) =  (yyvsp[(1) - (1)].stringval); }
    break;

  case 194:

/* Line 1464 of yacc.c  */
#line 993 "dmlyacc.yxx"
    {
             char *n;
             n=(char*)malloc(30);
             strcpy(n,"-");
             strcat(n,(char*)(yyvsp[(2) - (2)].stringval));
             (yyval.stringval)=n;
             free((yyvsp[(2) - (2)].stringval));
        }
    break;

  case 195:

/* Line 1464 of yacc.c  */
#line 1001 "dmlyacc.yxx"
    { (yyval.stringval) =  (yyvsp[(2) - (2)].stringval); }
    break;

  case 196:

/* Line 1464 of yacc.c  */
#line 1003 "dmlyacc.yxx"
    { (yyval.stringval) = (yyvsp[(1) - (1)].stringval); }
    break;

  case 197:

/* Line 1464 of yacc.c  */
#line 1005 "dmlyacc.yxx"
    {
             char *d;
             d=(char*)malloc(30);
             strcpy(d,"-");
             strcat(d,(char*)(yyvsp[(2) - (2)].stringval));
             (yyval.stringval)=d;
             free((yyvsp[(2) - (2)].stringval));
        }
    break;

  case 198:

/* Line 1464 of yacc.c  */
#line 1013 "dmlyacc.yxx"
    { (yyval.stringval) = (yyvsp[(2) - (2)].stringval); }
    break;

  case 199:

/* Line 1464 of yacc.c  */
#line 1016 "dmlyacc.yxx"
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

  case 200:

/* Line 1464 of yacc.c  */
#line 1027 "dmlyacc.yxx"
    {
            parsedData->setStmtType(CacheTableStatement);
            parsedData->setUnCache(true);
            parsedData->setTableName((yyvsp[(3) - (4)].stringval)); 
        }
    break;

  case 203:

/* Line 1464 of yacc.c  */
#line 1037 "dmlyacc.yxx"
    {
            parsedData->setHCondFld(true);
            parsedData->setHCondition((char*)(yyvsp[(2) - (2)].stringval));
         }
    break;

  case 205:

/* Line 1464 of yacc.c  */
#line 1044 "dmlyacc.yxx"
    {
            parsedData->setVCondFld(true);
            parsedData->setVCondition((char*)(yyvsp[(2) - (2)].stringval));
            free((yyvsp[(2) - (2)].stringval));
         }
    break;

  case 207:

/* Line 1464 of yacc.c  */
#line 1052 "dmlyacc.yxx"
    {
            parsedData->setPkFld(true);
            parsedData->setIndexName((char*)(yyvsp[(2) - (2)].stringval));
            free((yyvsp[(2) - (2)].stringval));
         }
    break;

  case 209:

/* Line 1464 of yacc.c  */
#line 1060 "dmlyacc.yxx"
    {
            parsedData->setDirect(true);
         }
    break;

  case 211:

/* Line 1464 of yacc.c  */
#line 1066 "dmlyacc.yxx"
    {
             parsedData->setDSN(true);
             parsedData->setPKTableName((char*)(yyvsp[(2) - (2)].stringval));
             free((yyvsp[(2) - (2)].stringval));
         }
    break;

  case 213:

/* Line 1464 of yacc.c  */
#line 1073 "dmlyacc.yxx"
    {
             parsedData->setNoSchema(true);
         }
    break;

  case 214:

/* Line 1464 of yacc.c  */
#line 1078 "dmlyacc.yxx"
    {
            parsedData->setStmtType(CreateTableStatement);
            parsedData->setTableName((yyvsp[(3) - (7)].stringval)); 
            free((yyvsp[(3) - (7)].stringval));
        }
    break;

  case 215:

/* Line 1464 of yacc.c  */
#line 1084 "dmlyacc.yxx"
    {
            parsedData->setStmtType(CreateIndexStatement);
            parsedData->setIndexName((yyvsp[(3) - (12)].stringval)); 
            parsedData->setTableName((yyvsp[(5) - (12)].stringval)); 
            free((yyvsp[(3) - (12)].stringval));
            free((yyvsp[(5) - (12)].stringval));
        }
    break;

  case 216:

/* Line 1464 of yacc.c  */
#line 1092 "dmlyacc.yxx"
    {
            parsedData->setStmtType(DropTableStatement);
            parsedData->setTableName((yyvsp[(3) - (3)].stringval)); 
            free((yyvsp[(3) - (3)].stringval));
        }
    break;

  case 217:

/* Line 1464 of yacc.c  */
#line 1098 "dmlyacc.yxx"
    {
            parsedData->setStmtType(DropIndexStatement);
            parsedData->setIndexName((yyvsp[(3) - (3)].stringval)); 
            free((yyvsp[(3) - (3)].stringval));
        }
    break;

  case 218:

/* Line 1464 of yacc.c  */
#line 1104 "dmlyacc.yxx"
    {
            parsedData->setStmtType(TruncateStatement);
            parsedData->setTableName((yyvsp[(3) - (4)].stringval)); 
            free((yyvsp[(3) - (4)].stringval));
        }
    break;

  case 219:

/* Line 1464 of yacc.c  */
#line 1112 "dmlyacc.yxx"
    {
            parsedData->setIndexType(hashIndex);
        }
    break;

  case 220:

/* Line 1464 of yacc.c  */
#line 1116 "dmlyacc.yxx"
    {
            parsedData->setIndexType(treeIndex);
        }
    break;

  case 221:

/* Line 1464 of yacc.c  */
#line 1120 "dmlyacc.yxx"
    {
            parsedData->setIndexType(trieIndex);
        }
    break;

  case 222:

/* Line 1464 of yacc.c  */
#line 1124 "dmlyacc.yxx"
    {
            parsedData->setIndexType(hashIndex);
        }
    break;

  case 223:

/* Line 1464 of yacc.c  */
#line 1130 "dmlyacc.yxx"
    {
            parsedData->setUnique(true);
        }
    break;

  case 224:

/* Line 1464 of yacc.c  */
#line 1134 "dmlyacc.yxx"
    {
            parsedData->setUnique(true);
            parsedData->setPrimary(true);
        }
    break;

  case 225:

/* Line 1464 of yacc.c  */
#line 1139 "dmlyacc.yxx"
    {
            parsedData->setUnique(false);
            parsedData->setPrimary(false);
        }
    break;

  case 227:

/* Line 1464 of yacc.c  */
#line 1146 "dmlyacc.yxx"
    {
            parsedData->setBucketSize(atoi((yyvsp[(2) - (2)].stringval)));
            free((yyvsp[(2) - (2)].stringval));
        }
    break;

  case 233:

/* Line 1464 of yacc.c  */
#line 1162 "dmlyacc.yxx"
    {
            parsedData->insertFldDef();
        }
    break;

  case 235:

/* Line 1464 of yacc.c  */
#line 1171 "dmlyacc.yxx"
    {
            parsedData->setFldName((yyvsp[(1) - (1)].stringval));
            free((yyvsp[(1) - (1)].stringval));
        }
    break;

  case 237:

/* Line 1464 of yacc.c  */
#line 1177 "dmlyacc.yxx"
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
#line 1190 "dmlyacc.yxx"
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
#line 1203 "dmlyacc.yxx"
    {
            parsedData->setFldNotNull(true);
        }
    break;

  case 248:

/* Line 1464 of yacc.c  */
#line 1217 "dmlyacc.yxx"
    {
            parsedData->setForeign(true);
            parsedData->setPKTableName((char*)(yyvsp[(7) - (10)].stringval));
            parsedData->insertForeignKeyList();
        }
    break;

  case 252:

/* Line 1464 of yacc.c  */
#line 1229 "dmlyacc.yxx"
    {
           parsedData->insertFKField((char*)(yyvsp[(1) - (1)].stringval));
           free((yyvsp[(1) - (1)].stringval));
        }
    break;

  case 256:

/* Line 1464 of yacc.c  */
#line 1240 "dmlyacc.yxx"
    {
           parsedData->insertPKField((char*)(yyvsp[(1) - (1)].stringval));
           free((yyvsp[(1) - (1)].stringval));
        }
    break;

  case 257:

/* Line 1464 of yacc.c  */
#line 1247 "dmlyacc.yxx"
    {
           parsedData->setPrimary(true);
        }
    break;

  case 259:

/* Line 1464 of yacc.c  */
#line 1253 "dmlyacc.yxx"
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
#line 1274 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeInt);
        }
    break;

  case 261:

/* Line 1464 of yacc.c  */
#line 1278 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeLong);
        }
    break;

  case 262:

/* Line 1464 of yacc.c  */
#line 1282 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeShort);
        }
    break;

  case 263:

/* Line 1464 of yacc.c  */
#line 1286 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeLongLong);
        }
    break;

  case 264:

/* Line 1464 of yacc.c  */
#line 1290 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeByteInt);
        }
    break;

  case 265:

/* Line 1464 of yacc.c  */
#line 1294 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeFloat);
        }
    break;

  case 266:

/* Line 1464 of yacc.c  */
#line 1298 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeDouble);
        }
    break;

  case 267:

/* Line 1464 of yacc.c  */
#line 1303 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeDate);
        }
    break;

  case 268:

/* Line 1464 of yacc.c  */
#line 1308 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeTime);
        }
    break;

  case 269:

/* Line 1464 of yacc.c  */
#line 1313 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeTimeStamp);
        }
    break;

  case 270:

/* Line 1464 of yacc.c  */
#line 1318 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeString);
            parsedData->setFldLength(2);
        }
    break;

  case 271:

/* Line 1464 of yacc.c  */
#line 1324 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeVarchar);
            parsedData->setFldLength(2);
        }
    break;

  case 272:

/* Line 1464 of yacc.c  */
#line 1330 "dmlyacc.yxx"
    {
            parsedData->setFldType(typeBinary);
            parsedData->setFldLength(1);
        }
    break;



/* Line 1464 of yacc.c  */
#line 4308 "dmlyacc.cxx"
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
#line 1335 "dmlyacc.yxx"


extern int lexEof;
void yyerror(const char* Msg) { 
    if( lexEof == 0 )
        fprintf(stderr, "[Parser: %s] %s\n", Msg, yytext);

    return;
}

