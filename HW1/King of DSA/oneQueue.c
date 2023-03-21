#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	int *items;
	int *index;
	int size;
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

	//create queue A
	Queue A;
	initQueue(&A, M);

	//input attack power and process
	int ap, val, ind, count, first, temp;
	val=-1;
	ind=-1;
	for(i=1;i<=N;i++){
		count=0;
		first=0;
		temp=0;

		scanf("%d", &ap);
		printf("Round %d: ", i);

		first=ind;
		//finding where the number is smaller than ap
		while(1){
			if(ind==-1) break;
			else if(ind==first && temp==0){
				temp++;
				enqueue_v(&A, val);
				enqueue_i(&A, ind);
				val=dequeue_v(&A);
				ind=dequeue_i(&A);
				continue;
			}
			
			if(val<ap){
				if(ind==first && temp==1){
					out[count]=ind;
					count++;
					break;
				}
				out[count]=ind;
                        	count++;
                        	val=dequeue_v(&A);
                        	ind=dequeue_i(&A);
			}
			else{
				if(ind==first && temp==1){
					enqueue_v(&A, val);
					enqueue_i(&A, ind);
					break;
				}
				enqueue_v(&A, val);
				enqueue_i(&A, ind);
				val=dequeue_v(&A);
				ind=dequeue_i(&A);
			}
		}

		//printf("\nnum:%d\n", A.size);

		//check whether the King will be killed
		if(!isQueueEmpty_i(&A) && isQueueFull(&A)){
			val=dequeue_v(&A);
			ind=dequeue_i(&A);
			out[count]=ind;
			count++;
		}

		val=ap;
		ind=i;

		if(count!=0){
			for(j=count-1;j>=0;j--){
				printf("%d", out[j]);
				if(j!=0) printf(" ");
			}
		}
		printf("\n");
	}
	enqueue_v(&A, val);
	enqueue_i(&A, ind);
	printf("Final: ");
	val=dequeue_v(&A);
	ind=dequeue_i(&A);
	count=0;
	while(ind!=-1){
		out[count]=ind;
		count++;
		val=dequeue_v(&A);
		ind=dequeue_i(&A);
	}
	if(count!=0){
        	for(j=count-1;j>=0;j--){
                	printf("%d", out[j]);
                	if(j!=0) printf(" ");
        	}
	}

	free(A.items);
	free(A.index);
	free(out);
}

void initQueue(Queue* q, int max_size){
        q->front_v=0;
        q->rear_v=-1;
        q->front_i=0;
        q->rear_i=-1;
	q->size=0;
	q->max_size=max_size;
        q->items=(int*)malloc(max_size*sizeof(int));
        q->index=(int*)malloc(max_size*sizeof(int));
}

int isQueueEmpty_v(Queue* q){
	return q->size==0;
}

int isQueueEmpty_i(Queue* q){
        return q->size==0;
}

int isQueueFull(Queue* q){
        return q->size==q->max_size;
}

void enqueue_v(Queue* q, int val){
	q->rear_v=(q->rear_v+1)%(q->max_size);
	q->items[q->rear_v]=val;
}

void enqueue_i(Queue* q, int ind){
	q->size=q->size+1;
        q->rear_i=(q->rear_i+1)%(q->max_size);
        q->index[q->rear_i]=ind;
}

int dequeue_v(Queue* q){
	int val;
	if(isQueueEmpty_v(q)) return -1;
	else{
		val=q->items[q->front_v];
		q->front_v=(q->front_v+1)%(q->max_size);
		return val;
	}
}

int dequeue_i(Queue* q){
        int ind;
	if(isQueueEmpty_i(q)) return -1;
	else{
		ind=q->index[q->front_i];
        	q->front_i=(q->front_i+1)%(q->max_size);
		q->size=q->size-1;
        	return ind;
	}
}
