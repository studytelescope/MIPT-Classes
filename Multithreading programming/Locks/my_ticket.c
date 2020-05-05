#include "lock.h"

#include <stdlib.h>
#include <stdint.h>
#include <sched.h>

struct lock
{
	uint32_t volatile serving_ticket;
	uint32_t volatile next_ticket;
};

lock_t *lock_alloc(long unsigned n_threads)
{
	lock_t *lk = (lock_t*)calloc(1, sizeof(lock_t));

	lk->serving_ticket  = 0;
	lk->next_ticket = 0;

	return lk;
}

int lock_acquire(lock_t* lk)
{
	
	int attempts_counter = 0;
	uint32_t volatile client_id;
	client_id = __atomic_fetch_add(&lk->next_ticket, 1, __ATOMIC_RELAXED);

	while (__atomic_load_n(&lk->serving_ticket, __ATOMIC_ACQUIRE) != client_id)
	{
		__asm volatile("pause" ::: "memory");

		if(++attempts_counter == 100)
		{
			attempts_counter = 0;
			sched_yield();
		}
	}

	return 0;
}

int lock_release(lock_t* lk)
{
	uint32_t volatile current_id = __atomic_load_n(&lk->serving_ticket, __ATOMIC_RELAXED);
	__atomic_store_n(&lk->serving_ticket, current_id + 1, __ATOMIC_RELEASE);
	
	return 0;
}

int lock_free(lock_t* lk)
{
	free(lk);
	return 0;
}

/*
struct lock
{
	uint32_t volatile owner;
	uint32_t volatile ticket;
};

lock_t *lock_alloc(long unsigned n_threads)
{
	lock_t *lk;
	if (!(lk = aligned_alloc(sizeof(*lk), sizeof(*lk))))
		return NULL;
	lk->owner  = 0;
	lk->ticket = 0;
	return lk;
}

int lock_acquire(lock_t* lk)
{
	typeof(lk->owner) id;
	id = __atomic_fetch_add(&lk->ticket, 1, __ATOMIC_RELAXED);
#define MAX_SPINS 16
	int i = 0;
	while (__atomic_load_n(&lk->owner, __ATOMIC_ACQUIRE) != id)
	{
		__asm volatile("pause");

		if (i++ == MAX_SPINS)
		{
			i = 0;
			sched_yield();
		}

	}
	return 0;
}

int lock_release(lock_t* lk)
{
	typeof(lk->owner) tmp = __atomic_load_n(&lk->owner, __ATOMIC_RELAXED);
	__atomic_store_n(&lk->owner, tmp + 1, __ATOMIC_RELEASE);
	return 0;
}

int lock_free(lock_t* lk)
{
	free(lk);
	return 0;
}*/