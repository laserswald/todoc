#ifndef DEBUG_H
#define DEBUG_H

#ifdef NDEBUG
#define debugprint(M, ...) 
#else 
#define debugprint(M, ...) printf("Debug: %s %d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#endif

#endif
