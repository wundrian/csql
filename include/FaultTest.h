
#ifndef FAULT_H
#define FAULT_H

extern void injectFault(char *testname, void *object);

#ifdef FAULTTEST
#define INJECT_FAULT injectFault
#else
#define INJECT_FAULT ;
#endif

#endif

