// Speedunit.h
//
#include <stdio.h>

#define sp_pfail(message) printf("%s: %d: fail: %s\n", __FILE__, __LINE__, message)
#define sp_assert(test, message) do { if (!(test)) sp_pfail(message); } while (0)

