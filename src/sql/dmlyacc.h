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
#define AND 268
#define OR 269
#define NOT 270
#define STAR 271
#define INSERT 272
#define INTO 273
#define VALUES 274
#define DELETE 275
#define UPDATE 276
#define SET 277
#define NULL_VALUE 278
#define CREATE 279
#define TABLE 280
#define PRIMARY 281
#define KEY 282
#define DEFAULT 283
#define INDEX 284
#define ON 285
#define HASH 286
#define TREE 287
#define UNIQUE 288
#define DROP 289
#define INT_TYPE 290
#define LONG_TYPE 291
#define SHORT_TYPE 292
#define DOUBLE_TYPE 293
#define TIMESTAMP_TYPE 294
#define DATE_TYPE 295
#define CHAR_TYPE 296
#define TIME_TYPE 297
typedef union
{
   char *stringval;
   void *predicate;
} YYSTYPE;
extern YYSTYPE yylval;
