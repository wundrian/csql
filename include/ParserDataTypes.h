/* 
 * File:   ParserDataTypes.h
 * Author: mabi
 *
 * Created on April 24, 2012, 10:58 PM
 */

#ifndef PARSERDATATYPES_H
#define	PARSERDATATYPES_H

#include <map>
#include <string>
#include <DataType.h>

#ifndef AGGTYPE
enum AggType
{
    AGG_MIN = 1,
    AGG_MAX,
    AGG_SUM,
    AGG_AVG,
    AGG_COUNT,
    AGG_UNKNOWN
};
#define AGGTYPE
#endif

struct ConditionValue
{
    char *parsedString;
    void *value;
    int paramNo; // 0 ->not a param. It stores the param position
    DataType type;
    AggType aType;
    int length;
    bool opLike;
    bool isNullable;
    char fName[IDENTIFIER_LENGTH];
    bool isFunctionInvolve;
};
typedef std::multimap<std::string, ConditionValue> FieldConditionValMap;

#endif	/* PARSERDATATYPES_H */
