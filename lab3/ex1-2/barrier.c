/**
 * CS2106 AY 20/21 Semester 1 - Lab 3
 *
 * This file contains function definitions. Your implementation should go in
 * this file.
 */

#include "barrier.h"

// Initialise barrier here
void barrier_init ( barrier_t *barrier, int count ) {
    sem_t sem;
    sem_init(&sem, 0, 0);
    barrier->sem = sem;
    barrier->count = count;
}

void barrier_wait ( barrier_t *barrier ) {
    if (barrier->count == 1) {
        barrier->count--;
        sem_post(&(barrier->sem));
    } else {
        barrier->count--;
    }
}

// Perform cleanup here if you need to
void barrier_destroy ( barrier_t *barrier ) {
}