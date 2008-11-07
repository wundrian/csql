
#include <stdio.h>
#include <string.h>
#include "support.h"

void
convert(int unique, char* buf)
{
    int i;
    int rem;

    for (i=0; i<7; i++) buf[i] = 'A';

    i = 6;
    while ( unique > 0 ) {
        rem = unique % 26;
        buf[i] = 'A' + rem;
        unique = unique / 26;
        i--;
    }
}

int
randNum(int seed, int limit, int generator, int prime)
{
    do {
        seed = (generator * seed) % prime;
    } while (seed>limit);

    return seed;
}

static unsigned long initSelection  = 0xFFFFFFFFL;
static unsigned long querySelection = 0xFFFFFFFFL;

int
isQuery(int queryNum)
{
    /* Check the (queryNum-1)th bit of the querySpec */

    if ((1 << (queryNum - 1)) & querySelection)
        return 1;
    else
        return 0;
}

#define MAX_TOKENS 40

int
setQueries(char* queryString)
{
    /* If never called then querySelection = all,
       if called, set query to none. and start processing
    */
    if (querySelection == initSelection)
        querySelection = 0;

    /* Parse the string into comma separated tokens */

    char*   tokens[MAX_TOKENS];
    int     numTokens;
    int     tokenPtr = 0;
    char*   dash;
    int     start;
    int     end;
    int     i;
    int     tokenValue;

    numTokens = 0;
    tokens[numTokens] = strtok(queryString, ",");
    while (tokens[numTokens] != NULL) {
        if (numTokens < MAX_TOKENS) {
            tokens[++numTokens] = strtok(NULL, ",");
        }
        else {
            fprintf (stderr, "Too many queries specified.\n");
            return -1;
        }
    }

    /* Check to see if you got any tokens (return if not) */

    if (numTokens == 0) {
        return 0;
    }

    /* Process each token, expanding ranges if present,
     * and adding the query numbers to the return value */

    for (tokenPtr = 0; tokenPtr < numTokens; tokenPtr++) {

        /* Check for a range '-' of tokens */

        dash = strchr(tokens[tokenPtr], '-');

        if (dash) {
            /* Get the start and end range specifiers (set the dash to null) */
            *dash = 0;
            if (sscanf(tokens[tokenPtr], "%d", &start) == -1 ||
                sscanf(dash+1, "%d", &end) == -1) {
                fprintf (stderr, "Invalid query range specified (%s-%s).\n",
                        tokens[tokenPtr], dash+1);
                return -1;
            }

            /* Make sure that the start and end values are in range
             * (return -1 to signal error in caller) */
            if ((start < 1) || (start > 32) || (end < 1) || (end > 32) || (start >= end)) {
                fprintf (stderr, "Invalid query range specified (%d-%d).\n", start, end);
                return -1;
            }

            /* From start to end, set the bit in the querySpec */
            for (i = start; i < (end+1); i++) {
                querySelection = querySelection | (1 << (i - 1));
            }
        }
        else {
            /* Set  the (tokenPtr) bit in the querySpec */
            if (sscanf(tokens[tokenPtr], "%d", &tokenValue) == -1) {
                fprintf (stderr, "Invalid query specified (%s).\n", tokens[tokenPtr]);
                return -1;
            }
            if (tokenValue < 1 || tokenValue > 32) {
                fprintf (stderr, "Invalid query specified (%d).\n", tokenValue);
                return -1;
            }
            querySelection = querySelection | (1 << (tokenValue - 1));
        }
    }
    return 0;
}
