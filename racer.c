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
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <unistd.h>
#include "racer.h"

//initialize variables
static long delay_limit;
static int finish_line;
pthread_mutex_t sharedLock;
void * retval;

//initialize all racers before the start of the race
void init_racers(long milliseconds, int length) {
    delay_limit = milliseconds * 1000;
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
    new_racer->graphic = (char *) malloc(MAX_CAR_LEN + 1);
    char tmp[MAX_CAR_LEN + 1] = "";
    strcpy(tmp, "~0=-------o>");
    for(size_t i = 0; i < strlen(name); i++) {
        tmp[i+3] = name[i];
    }
    strcpy(new_racer->graphic, tmp);
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
    usleep(1000);
    int lockResult = pthread_mutex_lock(&sharedLock);
    if(lockResult) {
        perror("entering run() function");
        pthread_exit(retval);
    }

    Racer* new_racer = (Racer *) racer;
    bool flat = 0;

    //keep racing until finish line or flat tire
    while((new_racer->distance < finish_line) && (!flat)) {
        long speed = rand()%delay_limit;
        
        //get a flat tire
        if(speed < 4) {
            char tmp[MAX_CAR_LEN + 1] = "";
            strcpy(tmp, new_racer->graphic);
            tmp[1] = 'X';
            strcpy(new_racer->graphic, tmp);
            flat = 1;
        }
        
        usleep(speed);
        new_racer->distance++;

        //print out car
        move(new_racer->row, 0);
        for(int i = 0; i < new_racer->distance; i++) {
            printw(" ");
        }
        for(int i = 0; i <MAX_CAR_LEN; i++) {
            printw("%c", new_racer->graphic[i]);
        }
        refresh();

        //unlocking thread
        lockResult = pthread_mutex_unlock(&sharedLock);
        if(lockResult) {
            perror("exiting run() function");
            exit(errno);
        }
    }
    
    pthread_exit(retval);
}
