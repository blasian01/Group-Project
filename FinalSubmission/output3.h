#ifndef _OUTPUT_3_
#define _OUTPUT_3_


// Define a struct to represent job descriptions
struct jobDescription {
    char jobID[3];       // Job identifier (e.g., "P1")
    int timeArrival;     // Time at which the job arrives
    int timeExecution;   // Time required for the job to execute
};


// Function to evaluate job information and calculate metrics
void evaluateJobInfo(struct jobDescription jobs[], int jobCount);

void output3(char *argv);


#endif
