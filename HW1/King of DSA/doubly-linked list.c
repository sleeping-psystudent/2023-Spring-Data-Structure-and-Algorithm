#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    int data;
    int index;
    struct node *prev;
    struct node *next;
};

struct list {
    int count; 
    struct node *head;
    struct node *tail;
};

void init_list(struct list *lst);
void insert_node(struct list *lst, int val, int ind);
void delete_node_tail(struct list *lst, int val);
void delete_node_head(struct list *lst);

int main(){
	int i, j;

	//input N and M. N is the number of rounds and M is the arena's max capacity
	int N, M;
	scanf("%d %d", &N, &M);

	//initialize
	struct list lst;
	init_list(&lst);

	//process
	for(i=1;i<=N;i++){
		int ap;
		scanf("%d", &ap);
		printf("Round %d: ", i);

		//process
		if(lst.count==0) insert_node(&lst, ap, i);
		else{
			delete_node_tail(&lst, ap);
			//printf("\ncount: %d\n", lst.count);
			if(lst.count==M) delete_node_head(&lst);
			insert_node(&lst, ap, i);
		}
		printf("\n");
	}
	printf("Final: ");
	while(lst.count>0){
		struct node *temp=lst.tail;
		printf("%d ", temp->index);
		lst.tail=lst.tail->prev;
		if(lst.tail!=NULL) lst.tail->next=NULL;
		lst.count--;
		free(temp);
	}
}

//initialize
void init_list(struct list *lst) {
    lst->head = NULL;
    lst->tail = NULL;
    lst->count = 0;
}

//insertion
void insert_node(struct list *lst, int val, int ind) {
    struct node *new_node = (struct node*) malloc(sizeof(struct node));
    new_node->data = val;
    new_node->index = ind;
    new_node->prev = NULL;
    new_node->next = NULL;

    if (lst->head == NULL){
        lst->head = new_node;
        lst->tail = new_node;
	lst->count++;
    }
    else{
        new_node->prev = lst->tail;
        lst->tail->next = new_node;
        lst->tail = new_node;
	lst->count++;
    }
}

//tail deletion
void delete_node_tail(struct list *lst, int val){
	struct node *temp=lst->tail;
	while (temp != NULL && temp->data<val){

		struct node *del=temp;
		temp=temp->prev;

		if(del->prev != NULL) del->prev->next = del->next;
		else lst->tail = del->next;
		
		if(del->next != NULL) del->next->prev = del->prev;
		else lst->head = del->prev;

		lst->count--;
		printf("%d ", del->index);
		free(del);

		if(temp!=NULL) lst->tail=temp;
	}
}

//head deletion
void delete_node_head(struct list *lst){
	struct node *temp = lst->head;
	printf("%d", temp->index);
	lst->count--;
	lst->head = lst->head->next;
	if(lst->head != NULL) lst->head->prev = NULL;
	free(temp);
}
