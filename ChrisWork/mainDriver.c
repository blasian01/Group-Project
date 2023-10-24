//Author: Chris Settle
//Reads input of file and prepares it to send to each indivdual c file for output.

#include <stdio.h>
#include <stdlib.h>
#include <output1.h>

void SJFAlgorithim(int n, Process processes[]){

    int currentTime = 0;
    int numCompleted = 0;

    while (numCompleted < n) {
        // Find the process with the shortest remaining time
        int shortestIndex = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= current_time && processes[i].remainingTime > 0) {
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
            output(processes[shortestIndex].ID);

            // If the process is completed, increment counter
            if (processes[shortestIndex].remainingTime == 0) {
                numCompleted++;
                processes[i].endTime = currentTime;
            }
        }
    }
    
}

struct Process {

int ID = -1;
int arrivalTime = -1;
int burstTime = -1; int remainingTime = -1;
int startTime = -1; int endTime = -1;

};

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

    Process processes[n];
    for(int i = 0; i < n; i++)
        {
            processes[i].ID = processID[i];
            process[i].arrivalTime = processArrivalTime[i];
            process[i].burstTime = processBurstTime[i];
        }

    SJFAlgorithim(n, &processes);

    //TODO Include 4 outputs here.
    // output1();
    // output2();
    // output3();
    // output4();

    return 0;
}
