#ifndef _LINUX_SORT_H
#define _LINUX_SORT_H

#if 0	/* To replace with __FreeBSD_version */
#include <linux/types.h>

void sort(void *base, size_t num, size_t size,
	  int (*cmp)(const void *, const void *),
	  void (*swap)(void *, void *, int));
#else
#include_next <linux/sort.h>
#endif

#endif
