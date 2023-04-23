#include<stdio.h>
#include<stdlib.h>

typedef struct tree{
	int HeapLen;
	int Num;
	long long int HeapPrice;
	long long int TreePrice;
	int childNum;
	int *children;
	int subtreeSize;
}Tree;

typedef struct heap{
	long long int price;
	int length;
}Heap;

void heapify(int N, int M, int ID, int day, int num, Heap* event[N][M]);
long long int TreeREC(int N, int root, Tree* company[N], int* size, int C);
int TreeREC_childNum(int N, int root, Tree* company[N]);

int main(){
    int i, j, temp;

    //input the # of companies, the len of sales events, and his daily pockey money
    int N, M, C;
    scanf("%d %d %d", &N, &M, &C);

    //tree
    Tree* company[N];
    
    //initialize
    for(i=0;i<N;i++){
		company[i]=malloc(sizeof(Tree));
		company[i]->HeapLen=0;
		company[i]->Num=0;
		company[i]->HeapPrice=0;
		company[i]->TreePrice=0;
		company[i]->childNum=0;
		company[i]->subtreeSize=1;
    }
    //input parents of each node
    int arr[N-1];
    for(i=2;i<=N;i++){
        scanf("%d", &temp);
        arr[i-2]=temp-1;
	company[temp-1]->childNum++;
    }
    for(i=0;i<N;i++){
	    company[i]->children=(int*)malloc(company[i]->childNum*sizeof(int));
    }
    for(i=2;i<=N;i++){
	company[arr[i-2]]->children[company[arr[i-2]]->Num]=i-1; //company index starts from 0
	company[arr[i-2]]->Num++;
    }
    TreeREC_childNum(N, 0, company);
/*
    //testing
    for(i=0;i<N;i++){
	    printf("%d: ", i+1);
	    for(j=0;j<company[i]->childNum;j++){
		    printf("%d ", company[i]->children[j]);
	    }
	    printf("\n");
    }
*/
	//heap: company, day, price+sales
int size, cursor, smaller;
long long int tempC;
Heap* event[N][M];
for(i=0;i<M;i++){
	for(j=0;j<N;j++){
			event[j][i]=malloc(sizeof(Heap));
			//INSERT
			scanf("%lld %d", &event[j][company[j]->HeapLen]->price, &temp);
			event[j][company[j]->HeapLen]->length=i+temp;
			company[j]->HeapLen++;
			cursor=company[j]->HeapLen-1;
			while(1){
				if(cursor==0) break;

				if(event[j][cursor]->price<event[j][(cursor-1)/2]->price) smaller=cursor;
				else smaller=(cursor-1)/2;

				if(smaller==(cursor-1)/2) break;
				else{
					tempC=event[j][cursor]->price;
        				event[j][cursor]->price=event[j][(cursor-1)/2]->price;
        				event[j][(cursor-1)/2]->price=tempC;
					temp=event[j][cursor]->length;
        				event[j][cursor]->length=event[j][(cursor-1)/2]->length;
        				event[j][(cursor-1)/2]->length=temp;
					cursor=(cursor-1)/2;
				}
			}

			//check the sales
			while(event[j][0]->length<i){
				event[j][0]->price=1000000001;
				//swap
				tempC=event[j][company[j]->HeapLen-1]->price;
        			event[j][company[j]->HeapLen-1]->price=event[j][0]->price;
        			event[j][0]->price=tempC;
				temp=event[j][company[j]->HeapLen-1]->length;
        			event[j][company[j]->HeapLen-1]->length=event[j][0]->length;
        			event[j][0]->length=temp;
        			company[j]->HeapLen--;
				heapify(N, M, j, company[j]->HeapLen, 0, event);
			}

			//get the minimum
			company[j]->HeapPrice=event[j][0]->price;
			//testing the price
			//printf("%d day, %d comp: %d\n", i+1, j+1, company[j]->HeapPrice);
	    }
		//restore subtree price
		size=0;
		TreeREC(N, 0, company, &size, C);
		printf("%d\n", size);
    }

}

void heapify(int N, int M, int ID, int len, int num, Heap* event[N][M]){
    int left = 2*num+1;
    int right = 2*num+2;
    int smallest=num;

    if(left<len && event[ID][left]->price<event[ID][smallest]->price) smallest = left;
    if(right<len && event[ID][right]->price<event[ID][smallest]->price) smallest = right;

    long long int tempC;
    int temp;
    if (smallest!=num) {
        //swap
        tempC=event[ID][num]->price;
        event[ID][num]->price=event[ID][smallest]->price;
        event[ID][smallest]->price=tempC;
	temp=event[ID][num]->length;
        event[ID][num]->length=event[ID][smallest]->length;
        event[ID][smallest]->length=temp;
        //heapify subtree
        heapify(N, M, ID, len, smallest, event);
    }
}


long long int TreeREC(int N, int root, Tree* company[N], int* size, int C){
	long long int priceSum=company[root]->HeapPrice;
	int subtreeNum=company[root]->subtreeSize;
	for(int i=0;i<company[root]->childNum;i++){
		priceSum+=TreeREC(N, company[root]->children[i], company, size, C);
	}
	company[root]->TreePrice=priceSum;
	company[root]->subtreeSize=subtreeNum;

	if(subtreeNum>*size && priceSum<=C) *size=subtreeNum;
	return priceSum;
}

int TreeREC_childNum(int N, int root, Tree* company[N]){
	for(int i=0;i<company[root]->childNum;i++){
		company[root]->subtreeSize+=TreeREC_childNum(N, company[root]->children[i], company);
	}
	//testing
	return company[root]->subtreeSize;
}
