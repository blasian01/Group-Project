//Author: Chris Settle
//Reads input of file and prepares it to send to each indivdual c file for output.

#include <stdio.h>
#include <stdlib.h>

struct Process {

int ID, arrivalTime, burstTime;

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
        fscanf(fp, "P%d %d %d\n", &pid[i], &arrival_time[i], &burst_time[i]); //scan in information to arrays.
    }

    fclose(fp);

    //TODO Include 4 outputs here.
    // output1();
    // output2();
    // output3();
    // output4();

    return 0;
}
