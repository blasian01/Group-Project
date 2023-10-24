//Author: Chris Settle
//Reads input of file and prepares it to send to each indivdual c file for output.

#include <stdio.h>
#include <stdlib.h>
#include "output1.h"

struct Process {

int ID;
int arrivalTime;
int burstTime; int remainingTime;
int startTime; int endTime;

};


void SJFAlgorithim(int n, struct Process processes[n]){

    int currentTime = 0;
    int numCompleted = 0;

    while (numCompleted < n) {
        // Find the process with the shortest remaining time
        int shortestIndex = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                if (shortestIndex == -1 || processes[i].remainingTime < processes[shortestIndex].remainingTime) {
                    shortestIndex = i;
                    if(processes[i].startTime == -1) { processes[i].startTime = currentTime; }
                }
            }
        }

        if (shortestIndex == -1) {
            // No eligible process to run at the current time, just increment time
            currentTime++;
        } else {
            // Execute the selected process for 1 time unit
            processes[shortestIndex].remainingTime--;
            currentTime++;
            output1(processes[shortestIndex].ID);

            // If the process is completed, increment counter
            if (processes[shortestIndex].remainingTime <= 0) {
                numCompleted++;
                processes[shortestIndex].endTime = currentTime;
            }
        }
    }
    
}




int main() {
    FILE *fp;

    fp = fopen("process_data.txt", "r");
    if (fp == NULL) {
        printf("Error: Couldn't open file.\n");
        return 1;
    }

    int n;
    fscanf(fp, "%d\n", &n);  // count number of processes

    int processID[n], processArrivalTime[n], processBurstTime[n];

    // Set arrays to 0
    for (int i = 0; i < n; i++) {
        processID[i] = 0;
        processArrivalTime[i] = 0;
        processBurstTime[i] = 0;
        
    }

    for (int i = 0; i < n; i++) {
        fscanf(fp, "P%d %d %d\n", &processID[i], &processArrivalTime[i], &processBurstTime[i]); //scan in information to arrays.
    }

    fclose(fp);

    struct Process processes[n];
    for(int i = 0; i < n; i++)
        {
            processes[i].ID = processID[i];
            processes[i].arrivalTime = processArrivalTime[i];
            processes[i].burstTime = processBurstTime[i];
	    processes[i].remainingTime = processBurstTime[i];	
        }

    SJFAlgorithim(n, processes);

    //TODO Include 4 outputs here.
    // output1();
    // output2();
    // output3();
    // output4();

    return 0;
}
