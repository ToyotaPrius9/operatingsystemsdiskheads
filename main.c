#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define CYLINDERS 5000
#define REQUESTS 1000

// declare functions
int fcfs(int requests[], int head);
int scan(int requests[], int head);
int cscan(int requests[], int head);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s initial_head_position requests_file\n", argv[0]);
        return 1;
    }

    int initial_head = atoi(argv[1]);
    char *file_path = argv[2];

    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not open file %s\n", file_path);
        return 1;
    }

    int requests[REQUESTS];
    for (int i = 0; i < REQUESTS; i++) {
        fscanf(file, "%d", &requests[i]);
    }
    fclose(file);

    // call algos
    int total_fcfs = fcfs(requests, initial_head);
    int total_scan = scan(requests, initial_head);
    int total_cscan = cscan(requests, initial_head);
    
    // prints
    printf("FCFS total head movements: %d\n", total_fcfs);
    printf("SCAN total head movements: %d\n", total_scan);
    printf("C-SCAN total head movements: %d\n", total_cscan);

    return 0;
}

// FCFS disk scheduling
int fcfs(int requests[], int head) {
    int total_movements = 0;
    for (int i = 0; i < REQUESTS; i++) {
        total_movements += abs(requests[i] - head);
        head = requests[i];
    }
    return total_movements;
}

// SCAN disk scheduling
int scan(int requests[], int head) {
    int total_movements = 0;
    int direction = 1; // Moving to higher cylinder numbers

    while (1) {
        int serviced = 0;

        // serve requests in current direction
        for (int i = 0; i < REQUESTS; i++) {
            if ((requests[i] >= head && direction == 1) || (requests[i] <= head && direction == -1)) {
                total_movements += abs(head - requests[i]);
                head = requests[i];
                serviced++;
            }
        }

        // reverse direction if no requests were serviced
        if (serviced == 0) {
            direction = -direction; // reverse direction
        } else {
            // continue in the same direction
            break;
        }
    }

    return total_movements;
}

// C-SCAN disk scheduling
int cscan(int requests[], int head) {
    int total_movements = 0;
    int direction = 1; // Moving to higher cylinder numbers

    // move to the first request
    total_movements += abs(head - requests[0]);
    head = requests[0];

    // serve requests in the current direction
    for (int i = 0; i < REQUESTS; i++) {
        if ((requests[i] >= head && direction == 1) || (requests[i] <= head && direction == -1)) {
            total_movements += abs(head - requests[i]);
            head = requests[i];
        }
    }

    // wrap around to the beginning of the cylinder range
    total_movements += abs(head - CYLINDERS); // move to the end
    head = 0; // wrap around to the beginning

    // continue serving requests in the same direction
    for (int i = 0; i < REQUESTS; i++) {
        if ((requests[i] >= head && direction == 1) || (requests[i] <= head && direction == -1)) {
            total_movements += abs(head - requests[i]);
            head = requests[i];
        }
    }

    return total_movements;
}




// gcc -o disk_scheduler main.c -lm
// ./disk_scheduler 5000 textfile