/* 
 * File:   ParserDataTypes.h
 * Author: mabi
 *
 * Created on April 24, 2012, 10:58 PM
 */

#ifndef PARSERDATATYPES_H
#define PARSERDATATYPES_H

#include <list>
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

    /**
     * Calculate total size in bytes of this structure, including all things it is pointing to.
     * This does NOT include stuff pointed to by this.value, as it may be
     * reconstructed using this.parsedString
     * @return size_t
     */
    size_t sizeTotal() const { return sizeof(ConditionValue) + (sizeof(char) * (strlen(parsedString) + 1 /* for '\0' */)); }
};
typedef std::multimap<std::string, ConditionValue> FieldConditionValMap;
typedef std::map<void const * const *, ConditionValue> ConditionValMap;

enum DclType
{
    REVOKEACCESS=0, /* can't name them REVOKE, GRANT as this conflicts with parser tokens */
    GRANTACCESS
};

enum PrivilegeType
{
    PRIV_NONE = 0,
    PRIV_SELECT = 1,
    PRIV_INSERT = 2,
    PRIV_UPDATE = 4,
    PRIV_DELETE = 8,
    PRIV_DROP   = 16
};

/**
 * Represents an argument container for Privilege Descriptor related information
 */
struct DclInfoNode
{
    DclInfoNode(DclType type, std::string userName, unsigned char privs, bool withGrantOpt)
    : type(type), privs(privs), userName(userName), withGrantOpt(withGrantOpt) {}
    
    DclType type;
    /* The name of the user to grant privileges to */
    std::string userName;
    /* The list of privileges to grant (must be a bitmask of PrivilegeType) */
    unsigned char privs;
    /* indicates whether grantee can grant the privilege himself */
    bool withGrantOpt;
};

#endif  /* PARSERDATATYPES_H */
