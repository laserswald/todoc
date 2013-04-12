#ifndef DEBUG_H
#define DEBUG_H


/// Debugprint definition.
// dbprintf(...) is a special version of printf that prints the line and file 
// and an explaination of the current status of the program in question
// to either stderr or to stdout, depending on whether or not debugging is activated.
//
#ifdef NDEBUG
#define dbprintf(M, ...) fprintf(stderr, "Debug: %s %d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#else 
#define dbprintf(M, ...) printf("Debug: %s %d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#endif

#endif
