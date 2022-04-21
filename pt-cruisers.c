//
// File: pt-cruisers.c
// pt-cruisers.c runs a racecar simulation
//
// @author Ming Creekmore mec5765
//
// @date 4/21/2022
//
// // // // // // // // // // // // // // // // // // //

#include <stdio.h>
#include "racer.h"

int main(int argc, char * argv[]) {
    //where to start reading names
    //default is 1
    int starting_arg = 1;

    //automatically exit if not at least 2 args not including program name
    if(argc < 3) {
        fprintf(stderr, "Usage: pt-cruisers [max-speed-delay] name1 name2 [name3...]\n");
        return EXIT_FAILURE;
    }

    int speed_delay = atoi(arv[1]);
    //if there are not at least 2 name args
    if(speed_delay != 0 && argc < 4) {
        fprintf(stderr, "Usage: pt-cruisers [max-speed-delay] name1 name2 [name3...]\n");
        return EXIT_FAILURE;
    }
    
    //changing how input is read based on speed_delay
    if(speed_delay != 0) {
        starting_arg = 2;
    }
    else {
        speed_delay = DEFAULT_WAIT;
    }
    
    int row = 0;
    //initialize racers
    for(int i = starting_arg; i < argc, i++) {
        //if a name exceeds the max length exit, otherwise make new racer
        if(strlen(argv[i]) > MAX_NAME_LEN) {
            fprintf(stderr, "Error: racer %s exceeds length limit of %d", argv[i], MAX_NAME_LEN);
            return EXIT_FAILURE;
        }
        make_racer(argv[i], row);
        row++;
    }

    //initialize curses
}
