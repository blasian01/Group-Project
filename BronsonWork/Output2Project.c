//Author: Bronson Woods

//Date: 10/13/23

/* Program Description: program reads process data from a text file, calculates waiting time, turnaround time, 
and response time for each process using First-Come-First-Served scheduling, and then displays the results in a tabular format */

#include <stdio.h>


// Function to pring out the information of processes
void displayTable(int n, int pid[], int arrival_time[], int burst_time[], int waiting_time[], int turnaround_time[], int response_time[]) {
    printf("PID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\tResponse Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", pid[i], arrival_time[i], burst_time[i], waiting_time[i], turnaround_time[i], response_time[i]);
    }
}

int main() {
    FILE *fp;

    fp = fopen("process_data.txt", "r");
    if (fp == NULL) {
        printf("Could not open file.\n");
        return 1;
    }

    int n;
    fscanf(fp, "%d\n", &n);  // Read the number of processes from the first line

    int pid[n], arrival_time[n], burst_time[n], waiting_time[n], turnaround_time[n], response_time[n];

    // Initialize all arrays to zero
    for (int i = 0; i < n; i++) {
        pid[i] = 0;
        arrival_time[i] = 0;
        burst_time[i] = 0;
        waiting_time[i] = 0;
        turnaround_time[i] = 0;
        response_time[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        fscanf(fp, "P%d %d %d\n", &pid[i], &arrival_time[i], &burst_time[i]);
    }
    fclose(fp);

    // Initialize the first process's waiting and response time to 0
    waiting_time[0] = 0;
    response_time[0] = 0;

    // Turnaround time for the first process
    turnaround_time[0] = arrival_time[0] + burst_time[0];

    for (int i = 1; i < n; i++) {
        // Calculate waiting time for each process
        waiting_time[i] = turnaround_time[i - 1] - arrival_time[i];

        // If waiting time is negative, set it to 0
        if (waiting_time[i] < 0) {
            waiting_time[i] = 0;
        }

        // Response time is the same as waiting time for scheduling
        response_time[i] = waiting_time[i];

        // Calculate turnaround time for each process
        turnaround_time[i] = waiting_time[i] + burst_time[i];
    }

    // Display the table
    displayTable(n, pid, arrival_time, burst_time, waiting_time, turnaround_time, response_time);

    return 0;
}
