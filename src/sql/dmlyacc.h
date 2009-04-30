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
#define AUTO_INCREMENT 267
#define SELECT 268
#define FROM 269
#define WHERE 270
#define BETWEEN 271
#define IN 272
#define NOT 273
#define INSERT 274
#define INTO 275
#define VALUES 276
#define DELETE 277
#define UPDATE 278
#define SET 279
#define NULL_VALUE 280
#define CREATE 281
#define TABLE 282
#define PRIMARY 283
#define KEY 284
#define DEFAULT 285
#define INDEX 286
#define ON 287
#define HASH 288
#define TREE 289
#define UNIQUE 290
#define DROP 291
#define SIZE 292
#define INT_TYPE 293
#define LONG_TYPE 294
#define SHORT_TYPE 295
#define DOUBLE_TYPE 296
#define TIMESTAMP_TYPE 297
#define DATE_TYPE 298
#define CHAR_TYPE 299
#define TIME_TYPE 300
#define BIGINT_TYPE 301
#define FLOAT_TYPE 302
#define TINYINT_TYPE 303
#define BINARY_TYPE 304
#define MIN 305
#define MAX 306
#define AVG 307
#define SUM 308
#define COUNT 309
#define GROUP 310
#define BY 311
typedef union
{
   char *stringval;
   void *predicate;
   void *Expression;
} YYSTYPE;
extern YYSTYPE yylval;
