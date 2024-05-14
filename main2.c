#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define CYLINDERS 5000
#define REQUESTS 1000
#define INITIAL_HEAD_POSITION 2500 // position of the most inner 

// function declares
int fcfs(int requests[], int head);
int scan(int requests[], int head);
int cscan(int requests[], int head);
int compare_distance_from_head(const void *a, const void *b); // for sorting requests efficiently

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s initial_head_position requests_file\n", argv[0]);
        return 1;
    }

    int initial_head = atoi(argv[1]); // to retrieve initial pos of disk head, set when running file arguement
    char *file_path = argv[2]; // to  retrive the text file, also set when running file arguement

    FILE *file = fopen(file_path, "r"); // open the text file in read mode ("r")

    // if file does not exist
    if (file == NULL) {
        fprintf(stderr, "Error: Could not open file %s\n", file_path);
        return 1;
    }


    int requests[REQUESTS]; // declare array "requests"
    for (int i = 0; i < REQUESTS; i++) { //iterate i for "request" amount of times
        fscanf(file, "%d", &requests[i]);
    }
    fclose(file);

    // scheduling algorithm (optimized request ordering)
    int total_fcfs = fcfs(requests, initial_head);
    int total_scan = scan(requests, initial_head);
    int total_cscan = cscan(requests, initial_head);
    
    // print results
    printf("FCFS total head movements: %d\n", total_fcfs);
    printf("SCAN total head movements: %d\n", total_scan);
    printf("C-SCAN total head movements: %d\n", total_cscan);

    return 0;
}

// FCFS, re arranging the list of requests does no use for anything here 
int fcfs(int requests[], int head) {
    int total_movements = 0;
    for (int i = 0; i < REQUESTS; i++) {
        total_movements += abs(requests[i] - head);
        head = requests[i];
    }
    return total_movements;
}



// helper function to compare distances from head (used for qsort)
int compare_distance_from_head(const void *a, const void *b) {
    int distance_a = abs(*(const int *)a - INITIAL_HEAD_POSITION);
    int distance_b = abs(*(const int *)b - INITIAL_HEAD_POSITION);
    return distance_a - distance_b;
}




// SCAN  with request reordering
int scan(int requests[], int head) {
    int total_movements = 0;
    int direction = 1; // move towards higher cylinder numbers

    // sort requests based on distance from initial head position
    qsort(requests, REQUESTS, sizeof(int), compare_distance_from_head);

    // serve requests in sorted order
    for (int i = 0; i < REQUESTS; i++) {
        total_movements += abs(head - requests[i]);
        head = requests[i];
    }

    return total_movements;
}

// C-SCAN  with request reordering
int cscan(int requests[], int head) {
    int total_movements = 0;
    int direction = 1; // move to higher cylinder numbers

    // sort requests based on distance from the initial head position
    qsort(requests, REQUESTS, sizeof(int), compare_distance_from_head);

    // serve requests in the sorted order
    for (int i = 0; i < REQUESTS; i++) {
        total_movements += abs(head - requests[i]);
        head = requests[i];
    }

    return total_movements;
}


