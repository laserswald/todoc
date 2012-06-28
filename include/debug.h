#ifndef DEBUG_H
#define DEBUG_H

#ifdef DEBUG
#define debugprint(M, ...) printf("Debug: %s %d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#else 
#define debugprint()
#endif
