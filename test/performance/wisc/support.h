
#ifndef __SUPPORT_H_
#define __SUPPORT_H_

void convert(int unique, char* buf);

int randNum(int seed, int limit, int generator, int prime);

int isQuery(int queryNum);

int setQueries(char* queryString);

#endif
