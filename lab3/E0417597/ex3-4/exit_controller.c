/**
 * CS2106 AY 20/21 Semester 1 - Lab 3
 *
 * This file contains declarations. You should only modify the fifo_sem_t struct,
 * as the method signatures will be needed to compile with the runner.
 */
#include "exit_controller.h"
#include <stdlib.h> 
#include <stdio.h>


void exit_controller_init(exit_controller_t *exit_controller, int no_of_priorities) {
    sem_init(&(exit_controller->exitSem), 1, 1);
    sem_init(&(exit_controller->queue), 1, 1);
    exit_controller->first = 0;
    exit_controller->firstEnd = 0;
    exit_controller->last = 0;
    exit_controller->lastEnd = 0;
    exit_controller->atom = 1;

    for(int i = 0; i < MAX_PRIORITIES; i++) {
        sem_init(&exit_controller->arrH[i], 1, 0);
        sem_init(&exit_controller->arrL[i], 1, 0);
    }
}

void exit_controller_wait(exit_controller_t *exit_controller, int priority) {
    sem_wait(&exit_controller->queue); // Queue CS
    sem_t* node = enqueueX(exit_controller, priority);
    if (exit_controller->atom > 0) {
        dequeueX(exit_controller);
        exit_controller->atom--;
    } 
    sem_post(&exit_controller->queue); // Queue CS
    sem_trywait(node);
    sem_wait(&exit_controller->exitSem);
}

void exit_controller_post(exit_controller_t *exit_controller, int priority) {
    sem_wait(&exit_controller->queue); // Queue CS
    dequeueX(exit_controller);
    sem_post(&exit_controller->queue); // Queue CS
    sem_post(&exit_controller->exitSem);
}

void exit_controller_destroy(exit_controller_t *exit_controller){
    for (int i = 0; i < (MAX_PRIORITIES * 2); i++) {
        sem_destroy(&exit_controller->arrH[i]);
        sem_destroy(&exit_controller->arrL[i]);
    }
}

sem_t* enqueueX(exit_controller_t *exit_controller, int priority) {
    sem_t* node;
    if (priority == 0) {
        node = &exit_controller->arrH[exit_controller->firstEnd];
        exit_controller->firstEnd++;
    } else {
        node = &exit_controller->arrL[exit_controller->lastEnd];
        exit_controller->lastEnd++;
    }
    return node;
}

void dequeueX(exit_controller_t *exit_controller) {
    sem_t *node;
    if(exit_controller->firstEnd - exit_controller->first != 0) {
        node = &exit_controller->arrH[exit_controller->first];
        exit_controller->first++;
    } else {
        node = &exit_controller->arrL[exit_controller->last];
        exit_controller->last++;
    }
    sem_post(node);
}