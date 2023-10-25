#ifndef _OUTPUT_4_
#define _OUTPUT_4_

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
struct Node* newNode(int pid);

// Function to create an empty queue
struct Queue* createQueue();

// Function to add a process to queue
void enQueue(struct Queue* q, int pid);

// Function to remove a process from queue
void deQueue(struct Queue* q);

// Function to check if queue is full
int isQueueFull(struct Queue* q, int max_size);

void output4(char *argv);


#endif
