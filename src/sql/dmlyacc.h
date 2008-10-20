#define OR 257
#define AND 258
#define STRING 259
#define FIELD 260
#define NUMBER_STRING 261
#define BINARY_STRING 262
#define DOUBLE 263
#define OPERATOR 264
#define PARAMETER 265
#define SELECT 266
#define FROM 267
#define WHERE 268
#define BETWEEN 269
#define IN 270
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
#define BINARY_TYPE 302
#define MIN 303
#define MAX 304
#define AVG 305
#define SUM 306
#define COUNT 307
#define GROUP 308
#define BY 309
typedef union
{
   char *stringval;
   void *predicate;
} YYSTYPE;
extern YYSTYPE yylval;
