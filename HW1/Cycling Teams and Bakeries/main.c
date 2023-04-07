#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int y;
	int x;
	int uij;
	int tij;
	struct node* up;
	struct node* down;
	struct node* left;
	struct node* right;
	struct node* up_s;
	struct node* down_s;
	struct node* left_s;
	struct node* right_s;
}Node;

int train(int N, int M, Node* map1[N][M], Node* map2[N][M], Node* index1[N*M], Node* index2[N*M], int rank, int len, int size, int Npain[N*M], int num);
void race(int N, int M, Node* begin, Node* map1[N][M], Node* map2[N][M], Node* index1[N*M], Node* index2[N*M], int rank, int len);
void output(int N, int M, Node* begin, Node* map1[N][M], Node* map2[N][M], Node* boun1[2*N+2*M], Node* boun2[2*N+2*M]);

int main(){
	int i, j, temp;

	//input N, M
	int N, M;
	scanf("%d %d", &N, &M);
	Node* map1[N][M];
	Node* map2[N][M];
	Node* index1[N*M];
	Node* index2[N*M];
	Node* boun1[2*N+2*M];
	Node* boun2[2*N+2*M];
	int Npain[N*M];
	int num=0;

	//uij, the rank of bij
	for(i=0;i<N;i++){
		for(j=0;j<M;j++){
			map1[i][j]=malloc(sizeof(Node));
            map2[N-i-1][M-j-1]=malloc(sizeof(Node));

            map1[i][j]->y=i;
			map1[i][j]->x=j;
			map2[N-i-1][M-j-1]->y=N-i-1;
			map2[N-i-1][M-j-1]->x=M-j-1;

			scanf("%d", &temp);
            map1[i][j]->uij=temp;
            map2[N-i-1][M-j-1]->uij=temp;
            index1[temp-1]=map1[i][j];
	    index2[temp-1]=map2[N-i-1][M-j-1];
		}
	}
	for(i=0;i<N;i++){
		for(j=0;j<M;j++){
			if(i>0){
				map1[i][j]->up = map1[i-1][j];
				map1[i][j]->up_s = map1[i][j]->up;
				map2[N-i-1][M-j-1]->down = map2[N-i][M-j-1];
                map2[N-i-1][M-j-1]->down_s = map2[N-i-1][M-j-1]->down;
			}
			else{
				boun1[j] = malloc(sizeof(Node));
				boun2[j] = malloc(sizeof(Node));
				map1[i][j]->up = boun1[j];
				map1[i][j]->up_s = boun1[j];
				boun1[j]->down = map1[i][j];
				boun1[j]->down_s = map1[i][j];
				boun1[j]->uij = 0;
				map2[N-i-1][M-j-1]->down = boun2[j];
                map2[N-i-1][M-j-1]->down_s = boun2[j];
				boun2[j]->up = map2[N-i-1][M-j-1];
				boun2[j]->up_s = map2[N-i-1][M-j-1];
				boun2[j]->uij = 0;
			}
			if(i<N-1){
				map1[i][j]->down = map1[i+1][j];
				map1[i][j]->down_s = map1[i][j]->down;
				map2[N-i-1][M-j-1]->up = map2[N-i-2][M-j-1];
                map2[N-i-1][M-j-1]->up_s = map2[N-i-1][M-j-1]->up;
			}
            else{
		    boun1[M+j] = malloc(sizeof(Node));
                boun2[M+j] = malloc(sizeof(Node));
				map1[i][j]->down = boun1[M+j];
				map1[i][j]->down_s = boun1[M+j];
				boun1[M+j]->up = map1[i][j];
				boun1[M+j]->up_s = map1[i][j];
				boun1[M+j]->uij = 0;
				map2[N-i-1][M-j-1]->up = boun2[M+j];
                map2[N-i-1][M-j-1]->up_s = boun2[M+j];
				boun2[M+j]->down = map2[N-i-1][M-j-1];
				boun2[M+j]->down_s = map2[N-i-1][M-j-1];
				boun2[M+j]->uij = 0;
			}
            if(j>0){
				map1[i][j]->left = map1[i][j-1];
				map1[i][j]->left_s = map1[i][j]->left;
				map2[N-i-1][M-j-1]->right = map2[N-i-1][M-j];
                map2[N-i-1][M-j-1]->right_s = map2[N-i-1][M-j-1]->right;
			}
            else{
		    boun1[2*M+i] = malloc(sizeof(Node));
                boun2[2*M+i] = malloc(sizeof(Node));
				map1[i][j]->left = boun1[2*M+i];
				map1[i][j]->left_s = boun1[2*M+i];
				boun1[2*M+i]->right = map1[i][j];
				boun1[2*M+i]->right_s = map1[i][j];
				boun1[2*M+i]->uij = 0;
				map2[N-i-1][M-j-1]->right = boun2[2*M+i];
                map2[N-i-1][M-j-1]->right_s = boun2[2*M+i];
				boun2[2*M+i]->left = map2[N-i-1][M-j-1];
				boun2[2*M+i]->left_s = map2[N-i-1][M-j-1];
				boun2[2*M+i]->uij = 0;
			}
            if(j<M-1){
				map1[i][j]->right = map1[i][j+1];
				map1[i][j]->right_s = map1[i][j]->right;
				map2[N-i-1][M-j-1]->left = map2[N-i-1][M-j-2];
                map2[N-i-1][M-j-1]->left_s = map2[N-i-1][M-j-1]->left;
			}
            else{
		    boun1[2*M+N+i] = malloc(sizeof(Node));
                boun2[2*M+N+i] = malloc(sizeof(Node));
				map1[i][j]->right = boun1[2*M+N+i];
				map1[i][j]->right_s = boun1[2*M+N+i];
				boun1[2*M+N+i]->left = map1[i][j];
				boun1[2*M+N+i]->left_s = map1[i][j];
				boun1[2*M+N+i]->uij = 0;
				map2[N-i-1][M-j-1]->left = boun2[2*M+N+i];
                map2[N-i-1][M-j-1]->left_s = boun2[2*M+N+i];
				boun2[2*M+N+i]->right = map2[N-i-1][M-j-1];
				boun2[2*M+N+i]->right_s = map2[N-i-1][M-j-1];
				boun2[2*M+N+i]->uij = 0;
			}
		}
	}
/*	
	//check the boundaries
	for(i=0;i<(2*N+2*M);i++){
		if(0<=i && i<M) printf("U|%d ", boun1[i]->down->uij);
		else if(M<=i && i<2*M) printf("D|%d ", boun1[i]->up->uij);
		else if(2*M<=i && i<2*M+N) printf("L|%d ", boun1[i]->right->uij);
		else if(2*M+N<=i && i<2*M+2*N) printf("R|%d ", boun1[i]->left->uij);
	}
	printf("\n\n");
*/
	//tij, the initial # of toasts of bij
	for(i=0;i<N;i++){
		for(j=0;j<M;j++){
			scanf("%d", &temp);
			map1[i][j]->tij=temp;
			map2[N-i-1][M-j-1]->tij=temp;
		}
	}

	Node* begin=boun1[0];

	//T1, R, T2
	int T1, R, T2, rank, len, size;
	scanf("%d %d %d", &T1, &R, &T2);

	//first training
	for(i=0;i<T1;i++){
		scanf("%d %d %d", &rank, &len, &size);
		num = train(N, M, map1, map2, index1, index2, rank, len, size, Npain, num);
	}
	
	//racing
	for(i=0;i<R;i++){
		scanf("%d %d", &rank, &len);
		//printf("\nDay %d\n", i+1);
		race(N, M, begin, map1, map2, index1, index2, rank, len);
	}

	//restore
	if(R!=0 && T1!=0){
		Node* Down1=boun1[0]->down;
		Node* Right1=Down1;
		Node* Up2=boun2[0]->up;
		Node* Left2=Up2;
		for(i=0;i<N;i++){
			for(j=0;j<M;j++){
				Right1->up_s=Right1->up;
				Right1->down_s=Right1->down;
				Right1->left_s=Right1->left;
				Right1->right_s=Right1->right;

				Right1->up_s->down_s=Right1;
				Right1->down_s->up_s=Right1;
				Right1->left_s->right_s=Right1;
				Right1->right_s->left_s=Right1;

				Right1->y=i;
				Right1->x=j;
				Right1=Right1->right;

				Left2->up_s=Left2->up;
				Left2->down_s=Left2->down;
				Left2->left_s=Left2->left;
				Left2->right_s=Left2->right;

				Left2->up_s->down_s=Left2;
				Left2->down_s->up_s=Left2;
				Left2->left_s->right_s=Left2;
				Left2->right_s->left_s=Left2;
				Left2->y=N-i-1;
				Left2->x=M-j-1;
				Left2=Left2->left;
			}
			Down1=Down1->down;
			Right1=Down1;
			Up2=Up2->up;
			Left2=Up2;
		}
		//no pain
		int k=0;
		while(k<num){
			index1[Npain[k]-1]->up_s->down_s=index1[Npain[k]-1]->down_s;
			index1[Npain[k]-1]->down_s->up_s=index1[Npain[k]-1]->up_s;
			index1[Npain[k]-1]->left_s->right_s=index1[Npain[k]-1]->right_s;
			index1[Npain[k]-1]->right_s->left_s=index1[Npain[k]-1]->left_s;

			index2[Npain[k]-1]->up_s->down_s=index2[Npain[k]-1]->down_s;
			index2[Npain[k]-1]->down_s->up_s=index2[Npain[k]-1]->up_s;
			index2[Npain[k]-1]->left_s->right_s=index2[Npain[k]-1]->right_s;
			index2[Npain[k]-1]->right_s->left_s=index2[Npain[k]-1]->left_s;	
			k++;
		}
}

/*	
	//check the boundaries
	for(i=0;i<(2*N+2*M);i++){
		if(0<=i && i<M) printf("U|%d ", boun1[i]->down->uij);
		else if(M<=i && i<2*M) printf("D|%d ", boun1[i]->up->uij);
		else if(2*M<=i && i<2*M+N) printf("L|%d ", boun1[i]->right->uij);
		else if(2*M+N<=i && i<2*M+2*N) printf("R|%d ", boun1[i]->left->uij);
	}
	printf("\n\n");
*/

	//second training
	for(i=0;i<T2;i++){
		scanf("%d %d %d", &rank, &len, &size);
		num = train(N, M, map1, map2, index1, index2, rank, len, size, Npain, num);
	}

	//output map
	output(N, M, begin, map1, map2, boun1, boun2);
}

int train(int N, int M, Node* map1[N][M], Node* map2[N][M], Node* index1[N*M], Node* index2[N*M], int rank, int len, int size, int* Npain, int num){
	int i=1;
	int count=num;
	Node* index_s[len+1];
	index_s[0]=index1[rank-1];
	Node* u=index1[rank-1]->up_s;
	Node* d=index1[rank-1]->down_s;
	Node* l=index1[rank-1]->left_s;
	Node* r=index1[rank-1]->right_s;

	index1[rank-1]->up_s->down_s=index1[rank-1]->down_s;
    index1[rank-1]->down_s->up_s=index1[rank-1]->up_s;
	index1[rank-1]->left_s->right_s=index1[rank-1]->right_s;
	index1[rank-1]->right_s->left_s=index1[rank-1]->left_s;

	Node* minN=NULL;
	Node* center=index1[rank-1];
	int min=1000001;
	int dis=1000001;
	int dis_u, dis_d, dis_l, dis_r;

	while(i<=len){
		if(u->uij==0 && d->uij==0 && l->uij==0 && r->uij==0) break;

		if(u->uij!=0 && u->tij>0){
			dis_u=abs(center->y-u->y);
			if(dis_u<dis || (dis_u==dis && u->uij<min)){
				minN=u;
				min=u->uij;
				dis=dis_u;
			}
		}

		if(d->uij!=0 && d->tij>0){
			dis_d=abs(d->y-center->y);
			if(dis_d<dis || (dis_d==dis && d->uij<min)){
                minN=d;
                min=d->uij;
				dis=dis_d;
			}
              	}

		if(l->uij!=0 && l->tij>0){
			dis_l=abs(center->x-l->x);
			if(dis_l<dis || (dis_l==dis && l->uij<min)){
                minN=l;
                min=l->uij;
				dis=dis_l;
			}
                }

		if(r->uij!=0 && r->tij>0){
			dis_r=abs(r->x-center->x);
			if(dis_r<dis || (dis_r==dis && r->uij<min)){
                minN=r;
                min=r->uij;
				dis=dis_r;
			}
                }

		index_s[i]=minN;
		center=minN;
		
		//pain
		int temp=(minN->tij)-size;
		if(temp<=0) temp=0;
		index1[minN->uij-1]->tij=temp;
		index2[minN->uij-1]->tij=temp;

		//cut branch
		index1[minN->uij-1]->up_s->down_s=index1[minN->uij-1]->down_s;
		index1[minN->uij-1]->down_s->up_s=index1[minN->uij-1]->up_s;
		index1[minN->uij-1]->left_s->right_s=index1[minN->uij-1]->right_s;
		index1[minN->uij-1]->right_s->left_s=index1[minN->uij-1]->left_s;
		
		index2[minN->uij-1]->up_s->down_s=index2[minN->uij-1]->down_s;
		index2[minN->uij-1]->down_s->up_s=index2[minN->uij-1]->up_s;
		index2[minN->uij-1]->left_s->right_s=index2[minN->uij-1]->right_s;
		index2[minN->uij-1]->right_s->left_s=index2[minN->uij-1]->left_s;

		//next itr
		u=minN->up_s;
		d=minN->down_s;
		l=minN->left_s;
		r=minN->right_s;
/*
		printf("%d %d %d %d\n", i, minN->uij, minN->tij, index1[minN->uij-1]->tij, index2[minN->uij-1]->tij);
		if(u!=NULL) printf("U: %d\n", u->uij);
		if(d!=NULL) printf("D: %d\n", d->uij);
		if(l!=NULL) printf("L: %d\n", l->uij);
		if(r!=NULL) printf("R: %d\n", r->uij);
		//output(N, M, map1[0][0], map1, map2, index);
		Node* Down=map1[0][0];
		Node* Right=Down;
		for(int k=0;k<N;k++){
			for(int j=0;j<M;j++){
				printf("%d ", Right->uij);
				Right=Right->right;
		}
		printf("\n");
		Down=Down->down;
		Right=Down;
	}
		printf("\n");
*/
		min=1000001;
		dis=1000001;
		i++;
	}

	//restore
	for(int j=0;j<i;j++){
		if(index_s[j]->tij!=0){
			index1[index_s[j]->uij-1]->up_s->down_s=index1[index_s[j]->uij-1];
			index1[index_s[j]->uij-1]->down_s->up_s=index1[index_s[j]->uij-1];
			index1[index_s[j]->uij-1]->right_s->left_s=index1[index_s[j]->uij-1];
			index1[index_s[j]->uij-1]->left_s->right_s=index1[index_s[j]->uij-1];
			
			index2[index_s[j]->uij-1]->up_s->down_s=index2[index_s[j]->uij-1];
			index2[index_s[j]->uij-1]->down_s->up_s=index2[index_s[j]->uij-1];
			index2[index_s[j]->uij-1]->right_s->left_s=index2[index_s[j]->uij-1];
			index2[index_s[j]->uij-1]->left_s->right_s=index2[index_s[j]->uij-1];
		}
		else{
			index1[index_s[j]->uij-1]->up_s->down_s=index1[index_s[j]->uij-1]->down_s;
			index1[index_s[j]->uij-1]->down_s->up_s=index1[index_s[j]->uij-1]->up_s;
			index1[index_s[j]->uij-1]->left_s->right_s=index1[index_s[j]->uij-1]->right_s;
			index1[index_s[j]->uij-1]->right_s->left_s=index1[index_s[j]->uij-1]->left_s;
			
			index2[index_s[j]->uij-1]->up_s->down_s=index2[index_s[j]->uij-1]->down_s;
			index2[index_s[j]->uij-1]->down_s->up_s=index2[index_s[j]->uij-1]->up_s;
			index2[index_s[j]->uij-1]->left_s->right_s=index2[index_s[j]->uij-1]->right_s;
			index2[index_s[j]->uij-1]->right_s->left_s=index2[index_s[j]->uij-1]->left_s;
			Npain[count]=index_s[j]->uij;
			count++;
		}
	}
	return count;
}


void race(int N, int M, Node* begin, Node* map1[N][M], Node* map2[N][M], Node* index1[N*M], Node* index2[N*M], int rank, int len){
	int i;
	int l = (len-1)/2;
	Node* MUp1=index1[rank-1];
	Node* MDown1=index1[rank-1];
	Node* MLeft1=index1[rank-1];
	Node* MRight1=index1[rank-1];
	Node* MUp2=index2[rank-1];
    Node* MDown2=index2[rank-1];
    Node* MLeft2=index2[rank-1];
    Node* MRight2=index2[rank-1];
	Node* temp=NULL;
	//find the points
	i=0;
	while(i<l){
		MUp1=MUp1->up;
		MDown1=MDown1->down;
		MLeft1=MLeft1->left;
		MRight1=MRight1->right;
		MUp2=MUp2->up;
                MDown2=MDown2->down;
                MLeft2=MLeft2->left;
                MRight2=MRight2->right;
		i++;
	}

	//Middle to corners
	for(i=0;i<=l;i++){
		//Middle up
		temp=MUp1->up;
		MUp1->up=MUp2->up;
		MUp2->up=temp;
		MUp1->up->down=MUp1;
		MUp2->up->down=MUp2;
		if(i!=l){
			MUp1=MUp1->left;
			MUp2=MUp2->left;
		}

		//Middle Down
        temp=MDown1->down;
        MDown1->down=MDown2->down;
        MDown2->down=temp;
        MDown1->down->up=MDown1;
        MDown2->down->up=MDown2;
		if(i!=l){
			MDown1=MDown1->right;
			MDown2=MDown2->right;
		}

		//Middle left
        temp=MLeft1->left;
        MLeft1->left=MLeft2->left;
        MLeft2->left=temp;
        MLeft1->left->right=MLeft1;
        MLeft2->left->right=MLeft2;
		if(i!=l){
			MLeft1=MLeft1->down;
			MLeft2=MLeft2->down;
		}

		//Middle right
        temp=MRight1->right;
        MRight1->right=MRight2->right;
        MRight2->right=temp;
        MRight1->right->left=MRight1;
        MRight2->right->left=MRight2;
		if(i!=l){
			MRight1=MRight1->up;
			MRight2=MRight2->up;
		}
	}

	//corners to middle
	for(i=0;i<l;i++){
		//printf("%d %d %d %d\n", MUp1->uij, MDown1->uij, MLeft1->uij, MRight1->uij);
		//printf("%d %d %d %d\n", MUp2->uij, MDown2->uij, MLeft2->uij, MRight2->uij);
		//printf("\n");
        //up-left
        temp=MUp1->left;
        MUp1->left=MUp2->left;
        MUp2->left=temp;
        MUp1->left->right=MUp1;
        MUp2->left->right=MUp2;
        MUp1=MUp1->down;
        MUp2=MUp2->down;

        //down-right
        temp=MDown1->right;
        MDown1->right=MDown2->right;
        MDown2->right=temp;
        MDown1->right->left=MDown1;
        MDown2->right->left=MDown2;
        MDown1=MDown1->up;
        MDown2=MDown2->up;

        //left-down
        temp=MLeft1->down;
        MLeft1->down=MLeft2->down;
        MLeft2->down=temp;
        MLeft1->down->up=MLeft1;
        MLeft2->down->up=MLeft2;
        MLeft1=MLeft1->right;
        MLeft2=MLeft2->right;

        //right-up
        temp=MRight1->up;
        MRight1->up=MRight2->up;
        MRight2->up=temp;
        MRight1->up->down=MRight1;
        MRight2->up->down=MRight2;
        MRight1=MRight1->left;
        MRight2=MRight2->left;
	}
}

void output(int N, int M, Node* begin, Node* map1[N][M], Node* map2[N][M], Node* boun1[2*N+2*M], Node* boun2[2*N+2*M]){
	int i, j;
	Node* Down=begin->down;
	Node* Right=Down;
	for(i=0;i<N;i++){
		for(j=0;j<M;j++){
			printf("%d ", Right->tij);
			Right=Right->right;
		}
		printf("\n");
		Down=Down->down;
		Right=Down;
	}
	for(i=0;i<N;i++){
		for(j=0;j<M;j++){
			free(map1[i][j]);
            free(map2[N-i-1][M-j-1]);
		}
	}
	for(i=0;i<2*N+2*M;i++){
		free(boun1[i]);
		free(boun2[i]);
	}
}
