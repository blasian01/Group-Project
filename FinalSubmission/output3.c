#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // Include limits.h for INT_MAX
#include "output3.h"

// Define a struct to represent job descriptions
struct jobDescription {
    char jobID[3];       // Job identifier (e.g., "P1")
    int timeArrival;     // Time at which the job arrives
    int timeExecution;   // Time required for the job to execute
};

// Function to evaluate job information and calculate metrics
void evaluateJobInfo(struct jobDescription jobs[], int jobCount);

void output3() {
    FILE *fp;

    fp = fopen("process_data.txt", "r");

    //char fn[] = "input.txt";     // Define the filename
    //FILE *inputFile = fopen(fn, "r");  // Open the file for reading
    
    // Check if the file can be opened
    if (fp == NULL) {
        printf("Error: Unable to open the file.\n");
        return 1;  // Return an error code
    }

    int jobCount;
    
    // Read the number of jobs from the file
    fscanf(fp, "%d", &jobCount);

    // Create an array to store job descriptions
    struct jobDescription jobs[jobCount];

    // Read job descriptions from the file and store them in the array
    for (int i = 0; i < jobCount; i++) {
        fscanf(fp, " %2s %d %d", jobs[i].jobID, &jobs[i].timeArrival, &jobs[i].timeExecution);
    }

    // Close the input file
    fclose(fp);

    // Call a function to evaluate job information and calculate metrics
    evaluateJobInfo(jobs, jobCount);

    return 0;
}

// Function to evaluate job information and calculate metrics
void evaluateJobInfo(struct jobDescription jobs[], int jobCount) {
    int timeRemaining[jobCount];       // Remaining execution time for each job
    int timeCompletion[jobCount];      // Completion time for each job
    int timeResponse[jobCount];        // Response time for each job
    int timeWaiting[jobCount];         // Waiting time for each job
    int tat[jobCount];      // Turnaround time for each job

    // Initialize arrays for each job
    int i = 0;
    do {
        timeRemaining[i] = jobs[i].timeExecution;
        timeCompletion[i] = 0;
        timeResponse[i] = -1;  // Initialize response time to -1 to identify when it's calculated
        timeWaiting[i] = 0;
        tat[i] = 0;
        i++;
    } while (i < jobCount);

    int currTime = 0;
    int jobsCompleted = 0;

    // Schedule and process jobs
    while (jobsCompleted < jobCount) {
        int sj = -1; // sj = shortestJob
        int max = INT_MAX; // Initialize max with the maximum integer value

        // Initialize minTimeRemaining with the value of max
        int minTimeRemaining = max;

        // Find the shortest job that is ready to execute
        i = 0;
        while (i < jobCount) {
            if (jobs[i].timeArrival <= currTime && timeRemaining[i] < minTimeRemaining && timeRemaining[i] > 0) {
                sj = i;
                minTimeRemaining = timeRemaining[i];
            }
            i++;
        }

        if (sj == -1) {
            currTime++;
        } else {
            // Calculate response time for the job if not already calculated
            if (timeResponse[sj] == -1) {
                timeResponse[sj] = currTime - jobs[sj].timeArrival;
            }
            timeRemaining[sj]--;

            // Check if the job has completed
            if (timeRemaining[sj] == 0) {
                jobsCompleted++;
                timeCompletion[sj] = currTime + 1;
                timeWaiting[sj] = timeCompletion[sj] - jobs[sj].timeExecution - jobs[sj].timeArrival;
                tat[sj] = timeWaiting[sj] + jobs[sj].timeExecution;
            }

            currTime++;
        }
    }

    // Calculate average metrics
    float avgtimeResponse = 0.0;
    float avgtimeWaiting = 0.0;
    float avgTAT = 0.0;

    i = 0;
    while (i < jobCount) {
        avgtimeResponse += timeResponse[i];
        avgtimeWaiting += timeWaiting[i];
        avgTAT += tat[i];
        i++;
    }

    avgtimeResponse /= jobCount;
    avgtimeWaiting /= jobCount;
    avgTAT /= jobCount;

    // Print the average metrics
    printf("Average Response Time: %.2f\n", avgtimeResponse);
    printf("Average Waiting Time: %.2f\n", avgtimeWaiting);
    printf("Average Turnaround Time: %.2f\n", avgTAT);
}
