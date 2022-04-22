//
// File: racer.c
// racer.c is an implementation of racer.h
//
// @author Ming Creekmore mec5765
//
// @date 4/21/2022
//
// // // // // // // // // // // // // // // // // // // //

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
    new_racer->graphic = (char *) malloc(MAX_CAR_LEN + 1);
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

void* run(void *racer) {

}
