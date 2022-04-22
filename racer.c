//
// File: racer.c
// racer.c is an implementation of racer.h
//
// @author Ming Creekmore mec5765
//
// @date 4/21/2022
//
// // // // // // // // // // // // // // // // // // // //

#define _DEFAULT_SOURCE
#include <curses.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <unistd.h>
#include "racer.h"

static long delay_limit;
static int finish_line;
pthread_mutext_t sharedLock;

//initialize all racers before the start of the race
void init_racers(long milliseconds, int length) {
    delay_limit = milliseconds;
    finish_line = length - MAX_CAR_LEN - 2;
    srand(30);
    int rc = pthread_mutex_init(&sharedLock, NULL);
    if(rc) {
        fprintf(stderr, "ERROR; pthread_mutex_init() returned %d\n", rc);
        exit(1);
    }
}

//makes a new racer given the name of the racer and the row num
Racer * make_racer(char *name, int row) {
    Racer * new_racer = (Racer *) malloc(sizeof(Racer));
    new_racer->row = row;
    new_racer->distance = 0;
    new_racer->graphic = (char *) malloc(MAX_CAR_LEN);
    new_racer->graphic = "~0=-------o>";
    for(int i = 0; i < strlen(name); i++) {
        new_racer->graphic[i+3] = name[i];
    }
    return new_racer;
}

//destroys a racer instance
void destroy_racer(Racer *racer) {
    free(racer->graphic);
    free(racer);
}

//main method for a thread instance to "run" a car on a racetrack
void* run(void *racer) {
    assert(racer != NULL);
    //this sleep randomizes the thread operation order
    usleep(1000L);
    int lockResult = pthread_mutex_lock(&sharedLock);
    if(lockResult) {
        perror("entering run() function");
        return lockResult;
    }

    Racer new_racer = (Racer *) racer;
    bool flat = 0;

    //keep racing until finish line or flat tire
    while(racer->distance < finish_line || flat) {
        long speed = rand()/delay_limit;
        
        //get a flat tire
        if(speed < 4) {
            new_racer->graphic[1] = 'X';
            flat = 1;
        }
        
        usleep(speed);
        racer->distance++;

        //print out car
        move(0, 0);
        for(int i = 0; i < new_racer->distance; i++) {
            printw(" ");
        }
        for(int i = 0; i <MAX_CAR_LEN; i++) {
            printw("%c", new_racer->graphic[i]);
        }
        
        lockResult = pthread_mutex_unlock(&sharedLock);
        if(lockResult) {
            perror("exiting run() function");
            exit(errno);
        }
    }
    
    return NULL;
}
