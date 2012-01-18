#ifndef _CONFIG_H_
#define _CONFIG_H_

#ifdef __APPLE__

#define HAVE_AVAILABILITY_MACROS_H 1
#define HAVE_TARGET_CONDITIONALS_H 1
#define HAVE_OSATOMIC_COMPARE_AND_SWAP_INT 1
#define HAVE_OSATOMIC_COMPARE_AND_SWAP_LONG 1
#define HAVE_LIBKERN_OSATOMIC_H

/* Be sneaky and turn OSAtomicCompareAndSwapInt into OSAtomicCompareAndSwap32
 * and OSAtomicCompareAndSwapLong into either OSAtomicCompareAndSwap32
 * or OSAtomicCompareAndSwap64 (depending on __LP64__) so that the library
 * is Tiger compatible!
 */
#include <libkern/OSAtomic.h>
#define OSAtomicCompareAndSwapInt OSAtomicCompareAndSwap32
#ifdef __LP64__
#define OSAtomicCompareAndSwapLong OSAtomicCompareAndSwap64
#else
#define OSAtomicCompareAndSwapLong OSAtomicCompareAndSwap32
#endif

#else /* !__APPLE__ */

#ifdef __GNUC__

#if !defined(__WIN32__) && !defined(_WIN32)

#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 1) /* GCC >= 4.1 */

/* runtime.c ignores these if __WIN32__ or _WIN32 is defined */
#define HAVE_SYNC_BOOL_COMPARE_AND_SWAP_INT 1
#define HAVE_SYNC_BOOL_COMPARE_AND_SWAP_LONG 1

#else /* GCC earlier than version 4.1 */

#error GCC version 4.1 (or compatible) or later is required on non-apple, non-w32 targets

#endif /* GCC earlier than version 4.1 */

#endif /* !defined(__WIN32__) && !defined(_WIN32) */

#endif /* __GNUC__ */

#endif /* !__APPLE__ */

#endif /* _CONFIG_H_ */
