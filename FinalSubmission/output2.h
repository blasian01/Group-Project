#ifndef _OUTPUT_2_
#define _OUTPUT_2_

// Function to pring out the information of processes
void displayTable(int n, int pid[], int arrival_time[], int burst_time[], int waiting_time[], int turnaround_time[], int response_time[]) {
    printf("PID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\tResponse Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", pid[i], arrival_time[i], burst_time[i], waiting_time[i], turnaround_time[i], response_time[i]);
    }
}


#endif