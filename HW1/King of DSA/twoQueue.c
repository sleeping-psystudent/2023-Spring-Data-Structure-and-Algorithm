#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
       int *items;
       int *index;
       int front_v, rear_v;
       int front_i, rear_i;
       int max_size;
} Queue;

void initQueue(Queue* q, int max_size);
int isQueueEmpty_v(Queue* q);
int isQueueEmpty_i(Queue* q);
int isQueueFull(Queue* q);
void enqueue_v(Queue* q, int val);
void enqueue_i(Queue* q, int ind);
int dequeue_v(Queue* q);
int dequeue_i(Queue* q);

int main(){
       int i, j;

       //input N and M. N is the number of rounds and M is the arena's max capacity
       int N, M;
       scanf("%d %d", &N, &M);

       //temp output
       int* out=(int*)malloc(M*sizeof(int));

       //create queue A and queue B
       Queue A;
       Queue B;
       initQueue(&A, M);
       initQueue(&B, M);

       //input attack power and process
       int ap, val, ind, count;
       for(i=1;i<=N;i++){
               count=0;

               scanf("%d", &ap);
               printf("Round %d: ", i);

               val=dequeue_v(&A);
               ind=dequeue_i(&A);
               //finding where the number is smaller than ap
               while(val!=-1){
                       if(val<ap) break;
                       else{
                               enqueue_v(&B, val);
                               enqueue_i(&B, ind);
                               val=dequeue_v(&A);
                               ind=dequeue_i(&A);
                       }
               }

               //print losers
               while(val!=-1){
                       //printf("%d ", ind);
                       out[count]=ind;
                       count++;
                       val=dequeue_v(&A);
                       ind=dequeue_i(&A);
               }

               //check whether the King will be killed
               if(isQueueFull(&B)){
                       val=dequeue_v(&B);
                       ind=dequeue_i(&B);
                       //printf("%d ", ind);
                       out[count]=ind;
                       count++;
               }

               //put data back into queue A
               val=dequeue_v(&B);
               ind=dequeue_i(&B);
               while(val!=-1){
                       enqueue_v(&A, val);
                       enqueue_i(&A, ind);
                       val=dequeue_v(&B);
                       ind=dequeue_i(&B);
               }
               enqueue_v(&A, ap);
               enqueue_i(&A, i);

               for(j=count-1;j>=0;j--){
                       printf("%d", out[j]);
                       if(j!=0) printf(" ");
               }
               printf("\n");
       }
       printf("Final: ");
       val=dequeue_v(&A);
       ind=dequeue_i(&A);
       count=0;
       while(val!=-1){
               //printf("%d ", ind);
               out[count]=ind;
               count++;
               val=dequeue_v(&A);
               ind=dequeue_i(&A);
       }
        for(j=count-1;j>=0;j--){
                printf("%d", out[j]);
                if(j!=0) printf(" ");
        }

       free(A.items);
       free(A.index);
       free(B.items);
       free(B.index);
       free(out);
}

void initQueue(Queue* q, int max_size){
        q->front_v=-1;
        q->rear_v=-1;
        q->front_i=-1;
        q->rear_i=-1;
       q->max_size=max_size;
        q->items=(int*)malloc(max_size*sizeof(int));
        q->index=(int*)malloc(max_size*sizeof(int));
}

int isQueueEmpty_v(Queue* q){
       return q->front_v==-1;
}

int isQueueEmpty_i(Queue* q){
        return q->front_i==-1;
}

int isQueueFull(Queue* q){
        return q->rear_i==q->max_size-1;
}

void enqueue_v(Queue* q, int val){
       if(isQueueEmpty_v(q)) q->front_v=0;
       q->rear_v++;
       q->items[q->rear_v]=val;
}

void enqueue_i(Queue* q, int ind){
        if(isQueueEmpty_i(q)) q->front_i=0;
        q->rear_i++;
        q->index[q->rear_i]=ind;
}

int dequeue_v(Queue* q){
       int val;
       if(isQueueEmpty_v(q)) return -1;
       else{
               val=q->items[q->front_v];
               if(q->front_v>=q->rear_v){
                       q->front_v=-1;
                       q->rear_v=-1;
               }
               else q->front_v++;
               return val;
       }
}

int dequeue_i(Queue* q){
        int ind;
       if(isQueueEmpty_i(q)) return -1;
       else{
               ind=q->index[q->front_i];
               if(q->front_i>=q->rear_i){
                       q->front_i=-1;
                       q->rear_i=-1;
               }
               else q->front_i++;
               return ind;
       }
}
