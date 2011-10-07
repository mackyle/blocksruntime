#undef __APPLE_CC__
#define __APPLE_CC__ 5627
#include <stdlib.h>
#include <stdio.h>
#ifdef _WIN32
#define random() rand()
#else /* !_WIN32 */
#include <unistd.h>
#include <sys/wait.h>
#endif /* !_WIN32 */
