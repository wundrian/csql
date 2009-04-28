#define OR 257
#define AND 258
#define UMINUS 259
#define STRING 260
#define FIELD 261
#define NUMBER_STRING 262
#define BINARY_STRING 263
#define DOUBLE 264
#define OPERATOR 265
#define PARAMETER 266
#define SELECT 267
#define FROM 268
#define WHERE 269
#define BETWEEN 270
#define IN 271
#define NOT 272
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
#define SIZE 291
#define INT_TYPE 292
#define LONG_TYPE 293
#define SHORT_TYPE 294
#define DOUBLE_TYPE 295
#define TIMESTAMP_TYPE 296
#define DATE_TYPE 297
#define CHAR_TYPE 298
#define TIME_TYPE 299
#define BIGINT_TYPE 300
#define FLOAT_TYPE 301
#define TINYINT_TYPE 302
#define BINARY_TYPE 303
#define MIN 304
#define MAX 305
#define AVG 306
#define SUM 307
#define COUNT 308
#define GROUP 309
#define BY 310
typedef union
{
   char *stringval;
   void *predicate;
   void *Expression;
} YYSTYPE;
extern YYSTYPE yylval;
