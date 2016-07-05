// Copyright (c) rAthena Project (www.rathena.org) - Licensed under GNU GPL
// For more information, see LICENCE in the main folder  

#ifndef _rA_MUTEX_H_
#define _rA_MUTEX_H_

#include "cbasetypes.h"

#ifdef WIN32
#include "winapi.h"
#else
#include <pthread.h>
#endif

#ifdef	__cplusplus
extern "C" {
#endif
    
typedef struct ramutex* pramutex; // Mutex
typedef struct racond* pracond; // Condition Var

struct racond{
#ifdef WIN32
	HANDLE events[2];
	ra_align(8) volatile LONG nWaiters;
	CRITICAL_SECTION waiters_lock;

#define EVENT_COND_SIGNAL 0
#define EVENT_COND_BROADCAST 1

#else
	pthread_cond_t hCond;
#endif
};

/**
 * Creates a Mutex 
 *
 * @return not NULL
 */
pramutex ramutex_create();

/** 
 * Destroys a Mutex
 * 
 * @param m - the mutex to destroy
 */
void ramutex_destroy( pramutex m );

/** 
 * Gets a lock
 *
 * @param m - the mutex to lock
 */
void ramutex_lock( pramutex m);

/** 
 * Trys to get the Lock
 * 
 * @param m - the mutex try to lock
 * 
 * @return boolean (true = got the lock)
 */
bool ramutex_trylock( pramutex m );

/** 
 * Unlocks a mutex
 *
 * @param m - the mutex to unlock
 */
void ramutex_unlock( pramutex m);


/** 
 * Creates a Condition variable
 *
 * @return not NULL
 */
pracond racond_create();

/** 
 * Destroy a Condition variable
 *
 * @param c - the condition varaible to destroy
 */
void racond_destroy( pracond c );

/**
 * Waits Until state is signalled
 * 
 * @param c - the condition var to wait for signalled state 
 * @param m - the mutex used for syncronization
 * @param timeout_ticks - timeout in ticks ( -1 = INFINITE )
 */
void racond_wait( pracond c,  pramutex m,  sysint timeout_ticks);

/** 
 * Sets the given condition var to signalled state
 *
 * @param c - condition var to set in signalled state.
 *
 * @note:
 *  Only one waiter gets notified.
 */
void racond_signal( pracond c );

/** 
 * Sets notifys all waiting threads thats signalled.
 * @param c - condition var to set in signalled state
 * 
 * @note:
 *  All Waiters getting notified.
 */ 
void racond_broadcast( pracond c );

#ifdef	__cplusplus
}
#endif
    
#endif
