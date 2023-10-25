//Author: Chris Settle
//Reads input of file and prepares it to send to each indivdual c file for output.

#include <stdio.h>
#include <stdlib.h>
#include "output1.h"
#include "output2.h"
#include "output3.h"
#include "output4.h"

struct Process { //Creates a struct for the information required of the Processes.

int ID;
int arrivalTime;
int burstTime; int remainingTime;
int startTime; int endTime;

};

//Takes an array of Procceses as input and then performs the pre-emptive shortest job first algorithim.
//iterates and finds the shortest remaining time.
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
            output1(processes[shortestIndex].ID); //Outputs for Gantt chart

            // If the process is completed, increment counter
            if (processes[shortestIndex].remainingTime <= 0) {
                numCompleted++;
                processes[shortestIndex].endTime = currentTime;
            }
        }
    }
    
}

//Requires commandline argument for the input file.
int main(int argc, char *argv[]) {
    FILE *fp;

    fp = fopen(argv[1], "r"); //Opens the input file.
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
    for(int i = 0; i < n; i++) //Set process array values to the input values.
        {
            processes[i].ID = processID[i];
            processes[i].arrivalTime = processArrivalTime[i];
            processes[i].burstTime = processBurstTime[i];
	    processes[i].remainingTime = processBurstTime[i];	
        }


	printf("Gantt Chart:\n");
    SJFAlgorithim(n, processes);

    //TODO Include 4 outputs here.
    //output 1 printing to console

    // output2 printing to the console 
	printf("|\n\nDisplay Table\n"); //Displays a table of the different statisitcs of each process.
    output2(argv[1]);
printf("\n\nAverages:\n");

    output3(argv[1]); // Computes average of each statistic.
printf("\n\nProcesses Dropped:\n");

    output4(argv[1]); //Displays how many processes are dropped.

    return 0;
}
