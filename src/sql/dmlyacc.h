#ifndef YYERRCODE
#define YYERRCODE 256
#endif

#define STRING 257
#define FIELD 258
#define NUMBER_STRING 259
#define BINARY_STRING 260
#define DOUBLE 261
#define OPERATOR 262
#define PARAMETER 263
#define SELECT 264
#define FROM 265
#define WHERE 266
#define BETWEEN 267
#define IN 268
#define AND 269
#define OR 270
#define NOT 271
#define STAR 272
#define INSERT 273
#define INTO 274
#define VALUES 275
#define DELETE 276
#define UPDATE 277
#define SET 278
#define NULL_VALUE 279
#define CREATE 280
#define TABLE 281
#define PRIMARY 282
#define KEY 283
#define DEFAULT 284
#define INDEX 285
#define ON 286
#define HASH 287
#define TREE 288
#define UNIQUE 289
#define DROP 290
#define INT_TYPE 291
#define LONG_TYPE 292
#define SHORT_TYPE 293
#define DOUBLE_TYPE 294
#define TIMESTAMP_TYPE 295
#define DATE_TYPE 296
#define CHAR_TYPE 297
#define TIME_TYPE 298
#define BIGINT_TYPE 299
#define FLOAT_TYPE 300
#define TINYINT_TYPE 301
typedef union
{
   char *stringval;
   void *predicate;
} YYSTYPE;
extern YYSTYPE yylval;
