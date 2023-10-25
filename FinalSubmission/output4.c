#include <stdio.h>
#include <stdlib.h>

// Struct for a queue node
struct Node {
    int pid;
    struct Node* next;
};

// Queue with front and rear
struct Queue {
    struct Node *front, *rear;
    int size;  // Size of the queue
};

// Function to create a new node
struct Node* newNode(int pid) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->pid = pid;
    temp->next = NULL;
    return temp;
}

// Function to create an empty queue
struct Queue* createQueue() {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    q->size = 0;
    return q;
}

// Function to add a process to queue
void enQueue(struct Queue* q, int pid) {
    struct Node* temp = newNode(pid);
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        q->size++;
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
    q->size++;
}

// Function to remove a process from queue
void deQueue(struct Queue* q) {
    if (q->front == NULL) return;
    struct Node* temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    free(temp);
    q->size--;
}

// Function to check if queue is full
int isQueueFull(struct Queue* q, int max_size) {
    return q->size == max_size;
}

int main() {
    FILE *fp;
    fp = fopen("input1.txt", "r");
    if (fp == NULL) {
        printf("Could not open file.\n");
        return 1;
    }

    int queue_max_size;
    fscanf(fp, "%d\n", &queue_max_size);

    int n = 0; // Initialize n to zero
    int capacity = 10; // Initial capacity
    int *pid = malloc(capacity * sizeof(int));
    int *arrival_time = malloc(capacity * sizeof(int));
    int *burst_time = malloc(capacity * sizeof(int));

    struct Queue* q = createQueue();

    while (fscanf(fp, "P%d %d %d\n", &pid[n], &arrival_time[n], &burst_time[n]) != EOF) {
        n++;
        if (n == capacity) {
            capacity *= 2; // Double the capacity
            pid = realloc(pid, capacity * sizeof(int));
            arrival_time = realloc(arrival_time, capacity * sizeof(int));
            burst_time = realloc(burst_time, capacity * sizeof(int));
        }
    }
    fclose(fp);

    int time = 0, served = 0, dropped = 0;
    int i = 0;  // Index to keep track of processes

    while (i < n || q->front != NULL) {
        // Enqueue arriving processes
        while (i < n && arrival_time[i] <= time) {
            if (!isQueueFull(q, queue_max_size)) {
                enQueue(q, i);
            } else {
                dropped++;
            }
            i++;
        }

        // Serve the process at the front of the queue
        if (q->front != NULL) {
            int front_pid = q->front->pid;
            time += burst_time[front_pid];
            deQueue(q);
            served++;
        } else {
            // If the queue is empty, simply increment the time
            time++;
        }
    }

    // Results printed to terminal
    printf("Total Processes Served: %d\n", served);
    printf("Total Processes Dropped: %d\n", dropped);

    //freeing memory to prevent memory leaks
    free(pid);
    free(arrival_time);
    free(burst_time);


    return 0;
}