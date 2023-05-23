#include <stdio.h>
#include <stdlib.h>

typedef struct point{
	struct node* idx; //pointer to the knight with specific index
}hash;

typedef struct node{
	int index;
        long long health;
        long long attack;
	int attN;
	struct node* parent; //for heap structure
        struct node* left; //for heap structure
        struct node* right; //for heap structure
        struct info* plate; //for compression
}knight;

typedef struct info{
        long long total_actA; //total knight attack
        long long total_pasA; //total be attacked
        int size; //number of set member
        int attack_time; //number of attacking time
	struct node* root; //point to the heap root
}plate;

void Heapify(knight* K_t);
void HealthCheck(knight* root, int* ans);
void extractMin(knight* root);
void Union(knight* small, knight* large);
void Insert(knight* root, knight* new);
void recurHeapify(knight* K_t);
//for testing
void printHeap(knight* root);

int main(){
	int i, j;

	int N, M; //N is the number of knight; M is the number of round
	scanf("%d %d", &N, &M);

	//knight data input and pointers construct
	hash* H[N]; //point to the knight with index i
	knight* K[N]; //the knight
	plate* P[N]; //the door plate of the set
	for(i=0;i<N;i++){
		H[i]=malloc(sizeof(hash));
		K[i]=malloc(sizeof(knight));
		P[i]=malloc(sizeof(plate));
		//for hash initialzing
		H[i]->idx=K[i];
		//for knight initializing
		K[i]->index=i;
		scanf("%lld", &K[i]->health);
		K[i]->attN=0;
		K[i]->parent=NULL;
		K[i]->left=NULL;
		K[i]->right=NULL;
		K[i]->plate=P[i];
		//for plate initializing
		P[i]->size=1;
		P[i]->attack_time=0;
		P[i]->root=K[i];
	}
	for(i=0;i<N;i++){
	       	scanf("%lld", &K[i]->attack);
		//plate attack
		P[i]->total_actA=K[i]->attack;
	}
	/*
	//testing
	printf("hash testing\n");
	for(i=0;i<N;i++) printf("%d:%d %d\n", i, H[i]->idx->health, H[i]->idx->attack);
	printf("knight testing\n");
	for(i=0;i<N;i++) printf("%d:%d %d\n", i, K[i]->health, K[i]->attack);
	printf("plate testing\n");
	for(i=0;i<N;i++) printf("%d:%d %d %d %d\n", i, K[i]->root->total_actA, K[i]->root->total_pasA, K[i]->root->size, K[i]->root->attack_time);
	*/
//////////////////////////////////////////////////////////////////////////////////////

	//M rounds
	int K_a, K_s; //index of attack knight and defense knight
	plate* att;
	plate* def;
	int ans[N]; //attack times output
	for(i=0;i<M;i++){
		scanf("%d %d", &K_a, &K_s);
		//check whether Ka and Ks alive
		if(H[K_a-1]->idx->health==1000000001 || H[K_s-1]->idx->health==1000000001) continue;
		else if(H[K_a-1]->idx->plate==H[K_s-1]->idx->plate) continue;
		else{
			//fight -> change information on the doorplate
			att=H[K_a-1]->idx->plate;
			att->attack_time+=1;
			def=H[K_s-1]->idx->plate;
			def->total_pasA+=att->total_actA;
			//check health <= 0
			HealthCheck(def->root, ans);
			//union
			if(att->size>def->size) Union(def->root, att->root);
			else Union(att->root, def->root);
		}
		/*
		//testing
	        printf("hash testing: health, attack\n");
       		for(i=0;i<N;i++) printf("%d:%lld %lld\n", i, H[i]->idx->health, H[i]->idx->attack);
      	  	printf("knight testing: attack time\n");
	       	for(i=0;i<N;i++) printf("%d:%d\n", i, K[i]->attN);
		printf("plate testing: total_actA, total_pasA, size, attack_time\n");
		for(i=0;i<N;i++) printf("%d:%lld %lld %d %d\n", i, K[i]->plate->total_actA, K[i]->plate->total_pasA, K[i]->plate->size, K[i]->plate->attack_time);
		*/
	}
///////////////////////////////////////////////////////////////////////////////////////
	
	//output
	for(i=0;i<N;i++){
		if(H[i]->idx->health!=1000000001) printf("%d ", H[i]->idx->attN+(H[i]->idx->plate->attack_time));
		else printf("%d ", ans[i]);
	}
	/*
	//testing
	printf("\n");
	for(i=0;i<N;i++){
		if(H[i]->idx->health!=1000000001) printf("%c ", 'd');
		else printf("%c ", 'a');
	}*/
}

//parent pointer increased, dead node ignore
void Heapify(knight* K_t){
	knight* smallest=K_t;
	knight* Kleft=K_t->left;
	knight* Kright=K_t->right;
	if(Kleft!=NULL && Kleft->health<smallest->health) smallest=Kleft;
	if(Kright!=NULL && Kright->health<smallest->health) smallest=Kright;
/*
	printf("root:%d ", K_t->index);
	if(K_t->left!=NULL) printf("left:%d ", K_t->left->index);
        else printf("left:%c ", 'N');
        if(K_t->right!=NULL) printf("right:%d\n", K_t->right->index);
	else printf("right:%c\n", 'N');
*/
	if(smallest!=K_t){
		if(K_t==K_t->plate->root) K_t->plate->root=smallest; //update the root of the heap
		knight* temp;
		if(smallest==Kleft){
			//switch parents
			smallest->parent=K_t->parent;
			K_t->parent=smallest;
			if(smallest->parent!=NULL){
				if(smallest->parent->left==K_t) smallest->parent->left=smallest;
				else smallest->parent->right=smallest;
			}
			//switch smallest and K_t
			K_t->left=smallest->left;
			smallest->left=K_t;
			if(smallest->left!=NULL) smallest->left->parent=smallest;
			if(K_t->left!=NULL) K_t->left->parent=K_t;
			//switch rightChild
			temp=K_t->right;
                	K_t->right=smallest->right;
                	smallest->right=temp;
			if(smallest->right!=NULL) smallest->right->parent=smallest;
			if(K_t->right!=NULL) K_t->right->parent=K_t;
		}
		else{
			//switch parents
                        smallest->parent=K_t->parent;
                        K_t->parent=smallest;
                        if(smallest->parent!=NULL){
                                if(smallest->parent->left==K_t) smallest->parent->left=smallest;
                                else smallest->parent->right=smallest;
                        }
                        //switch leftChild
                        temp=K_t->left;
                        K_t->left=smallest->left;
                        smallest->left=temp;
			if(smallest->left!=NULL) smallest->left->parent=smallest;
			if(K_t->left!=NULL) K_t->left->parent=K_t;
                        //switch smallest and K_t
			K_t->right=smallest->right;
			smallest->right=K_t;
			if(smallest->right!=NULL) smallest->right->parent=smallest;
			if(K_t->right!=NULL) K_t->right->parent=K_t;
		}
                //recursion
                Heapify(K_t);
	}
}

void HealthCheck(knight* root, int* ans){
	if(root==NULL) return;

	if(root->health-(root->plate->total_pasA)<=0){
		//printf("dead:%d\n", root->index);
		//printHeap(root);
		//printf(" heap\n");
		root->health=1000000001;
		root->plate->total_actA=(root->plate->total_actA)-(root->attack);
		ans[root->index]=root->attN+root->plate->attack_time;
		extractMin(root);
		//printHeap(root->plate->root);
		//printf(" ex\n");
		root->plate->size=(root->plate->size)-1;
		Heapify(root->plate->root);
		HealthCheck(root->plate->root, ans);
	}
	else return;
}

//extract-min
void extractMin(knight* root){
        int decimal=root->plate->size;
        int binary[18];
        int i=0;

        while(decimal>0){
                binary[i]=decimal%2;
                decimal=decimal/2;
                i++;
        }

        knight* now=root;
        for(int j=i-1;j>=0;j--){
                if(j==i-1) continue;
                if(binary[j]==0)now=now->left;
                else now=now->right;
        }
	//printf("exmin:%d %d\n", root->index, now->index);
	knight* temp;
	if(root->left==now){
		//left
		root->left=NULL;
		now->left=NULL;
		//switch right child
                temp=root->right;
                root->right=now->right;
                now->right=temp;
                if(now->right!=NULL) now->right->parent=now;
	}
	else if(root->right==now){
		//switch left child
                temp=root->left;
                root->left=now->left;
                now->left=temp;
                if(now->left!=NULL) now->left->parent=now;
		//right
		root->right=NULL;
		now->right=NULL;
	}
	else{
        	//switch left child
		temp=root->left;
		root->left=now->left;
		now->left=temp;
		if(now->left!=NULL) now->left->parent=now;
		//switch right child
        	temp=root->right;
        	root->right=now->right;
        	now->right=temp;
		if(now->right!=NULL) now->right->parent=now;
	}
	//switch parent
	if(now->parent!=NULL){
		if(now->parent->left==now) now->parent->left=NULL;
		else now->parent->right=NULL;
	}
	now->parent=NULL;
	now->plate->root=now;
}

void Union(knight* small, knight* large){
	if(small==NULL) return;
	else{
		if(small->health!=1000000001){
			//info update
			small->health=small->health-(small->plate->total_pasA)+(large->plate->total_pasA);
			small->attN=small->attN+(small->plate->attack_time)-(large->plate->attack_time);
			large->plate->total_actA+=small->attack;
			//transfer from small heap to big heap
			small->plate=large->plate; //small element becomes part of larger heap
			large->plate->size+=1;
			Insert(large, small);
			knight* tempL=small->left;
			knight* tempR=small->right;
			small->left=NULL;
			small->right=NULL;
			recurHeapify(small);
			//printf("actA:%lld pasA:%lld size:%d\n", large->plate->total_actA, large->plate->total_pasA, large->plate->size);
			//printHeap(large->plate->root);
			//printf("\n\n");
			Union(tempL, large->plate->root);
			Union(tempR, large->plate->root);
		}
		else return;
	}
}

void Insert(knight* root, knight* new) {
        int decimal=root->plate->size;
	int binary[18];
	int i=0;

	while(decimal>0){
		binary[i]=decimal%2;
		decimal=decimal/2;
		i++;
	}

	knight* now=root;
	for(int j=i-1;j>0;j--){
		if(j==i-1) continue;
		if(binary[j]==0)now=now->left;
		else now=now->right;
	}
	if(binary[0]==0){
		now->left=new;
		new->parent=now;
	}
	else{
		now->right=new;
		new->parent=now;
	}
}


void recurHeapify(knight* K_t){
	knight* parent=K_t->parent;
	if(K_t==NULL||parent==NULL) return;
	if(K_t->health < parent->health){
		if(parent==K_t->plate->root) K_t->plate->root=K_t; //update the root of the heap
		knight* temp;
		if(parent->left==K_t){
			//switch parent and K_t
			parent->left=K_t->left;
			K_t->left=parent;
			if(parent->left!=NULL) parent->left->parent=parent;
			//switch rightChild
			temp=K_t->right;
                	K_t->right=parent->right;
                	parent->right=temp;
			if(K_t->right!=NULL) K_t->right->parent=K_t;
			if(parent->right!=NULL) parent->right->parent=parent;
		}
		else{
                        //switch leftChild
                        temp=K_t->left;
                        K_t->left=parent->left;
                        parent->left=temp;
			if(K_t->left!=NULL) K_t->left->parent=K_t;
			if(parent->left!=NULL) parent->left->parent=parent;
                        //switch parent and K_t
			parent->right=K_t->right;
			K_t->right=parent;
			if(parent->right!=NULL) parent->right->parent=parent;
		}
		//switch parent
		K_t->parent=parent->parent;
		parent->parent=K_t;
		if(K_t->parent!=NULL){
			if(K_t->parent->left==parent) K_t->parent->left=K_t;
			else if(K_t->parent->right==parent) K_t->parent->right=K_t;
		}
                //recursion
                recurHeapify(K_t);
	}
}

void printHeap(knight* root){
	if(root==NULL) return;
	printHeap(root->left);
	printf("(%d,%lld,%lld", root->index, root->attack, root->health);
	if(root->parent!=NULL) printf(",%d", root->parent->index);
	else printf(",N");
	if(root->left!=NULL) printf(",%d", root->left->index);
        else printf(",N");
	if(root->right!=NULL) printf(",%d) ", root->right->index);
        else printf(",N) ");
	printHeap(root->right);
}
