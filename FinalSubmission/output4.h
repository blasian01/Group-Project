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


#endif