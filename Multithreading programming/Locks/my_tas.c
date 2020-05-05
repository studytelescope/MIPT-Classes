#include "lock.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct lock
{
	uint8_t volatile state;
};

lock_t *lock_alloc(long unsigned n_threads)
{
	lock_t *lk = (lock_t*)calloc(1, sizeof(lock_t));
	lk->state = 0;

	return lk;
}

int lock_acquire(lock_t* lk)
{
	uint8_t volatile * ptr = &lk->state;
	while (!__atomic_compare_exchange(ptr, &(uint8_t volatile){0}, &(uint8_t volatile){1},
			0, __ATOMIC_ACQUIRE, __ATOMIC_ACQUIRE));

	return 0;
}

int lock_release(lock_t* lk)
{
	uint8_t volatile * ptr = &lk->state;
	__atomic_store(ptr, &(uint8_t volatile){0}, __ATOMIC_RELEASE);
	return 0;
}

int lock_free(lock_t* lk)
{
	if (lk->state != 0)
	{
		printf("lock is not free!\n");
		return -1;
	}

	free(lk);
	return 0;
}
