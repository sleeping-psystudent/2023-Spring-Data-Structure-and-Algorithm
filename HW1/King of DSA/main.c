#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    int index;
};

struct deque {
    int count;
    int front;
    int rear;
    struct node *arr;
};

void init_deque(struct deque *dq, int size);
void insertion(struct deque *dq, int val, int ind, int M);
void deletion(struct deque *dq, int val, int M);

int main(){
    int i;

    //input N and M. N is the number of rounds and M is the arena's max capacity
    int N, M;
    scanf("%d %d", &N, &M);

    //initialize
    struct deque dq;
    init_deque(&dq, M);

    //process
    for(i=1;i<=N;i++){
        int ap;
        scanf("%d", &ap);
        printf("Round %d: ", i);

        if(dq.count==0) insertion(&dq, ap, i, M);
        else{
            deletion(&dq, ap, M);
            if(dq.count==M){
                printf("%d ", dq.arr[dq.front].index);
                dq.front=(dq.front+1)%M;
                dq.count--;
            }
            insertion(&dq, ap, i, M);
        }
        printf("\n");
    }
    printf("Final: ");
    while(dq.count>0){
        printf("%d ", dq.arr[dq.rear].index);
        dq.rear=(dq.rear-1+M)%M;
        dq.count--;
    }
    printf("\n");
    free(dq.arr);
}

//initialize
void init_deque(struct deque *dq, int size) {
    dq->arr = (struct node*)malloc(sizeof(struct node)*size);
    dq->count = 0;
    dq->front = 0;
    dq->rear = -1;
}

//rear insertion
void insertion(struct deque *dq, int val, int ind, int M) {
    dq->rear = (dq->rear+1)%M;
    dq->arr[dq->rear].data = val;
    dq->arr[dq->rear].index = ind;
    dq->count++;
}

//rear deletion
void deletion(struct deque *dq, int val, int M){
    while(dq->count>0 && dq->arr[dq->rear].data<val){
        printf("%d ", dq->arr[dq->rear].index);
        dq->rear=(dq->rear-1+M)%M;
        dq->count--;
    }
}

