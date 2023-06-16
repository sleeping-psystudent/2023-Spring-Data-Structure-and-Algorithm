#include <stdio.h>
#include <stdlib.h>

struct node{
	long long A;
	long long B;
	long long interval;
	long long odd;
	long long even;
	int n; //number, for testing parity
	int c; // 1-red, 0-black
	struct node* p; // parent
	struct node* r; // right-child
	struct node* l; // left child
};

struct store{
	struct node* priceNode;
};

struct node* root = NULL;


struct node* bst(struct node* trav, struct node* NIL, struct node* temp);
struct node* rightrotate(struct node* root, struct node* NIL, struct node* temp);
struct node* leftrotate(struct node* root, struct node* NIL, struct node* temp);
struct node* insertFixup(struct node* root, struct node* NIL, struct node* pt);
struct node* delete(struct node* root, struct node* NIL, struct node* node);
struct node* deleteFixup(struct node* root, struct node* NIL, struct node* pt);
struct node* transplant(struct node* root, struct node* NIL, struct node* u, struct node* v);
struct node* successor(struct node* NIL, struct node* node);

int main(){
	int i, j;
	long long low=0;
	long long P;

	// intput the # of types of the sd and the # of the days to make the purchases
	int N, M;
	scanf("%d %d", &N, &M);
	
	//NULL
	struct node* NIL=(struct node*)malloc(sizeof(struct node));
	NIL->A=0;
	NIL->B=0;
	NIL->interval=0;
	NIL->r=NIL;
	NIL->l=NIL;
	NIL->p=NIL;
	NIL->c=0;
	NIL->n=0;

	//construct the price tree
	long long a, b, in;
	struct store* poi[N];
	struct node* up;
	for (i=0;i<N;i++) {
		//input a and b
		scanf("%lld %lld", &a, &b);
		if(a>b){
			in=a-b;
			low+=b;
		}
		else{
			in=b-a;
			low+=a;
		}

		struct node* temp=(struct node*)malloc(sizeof(struct node));
		temp->A=a;
		temp->B=b;
		temp->interval=in;
		temp->odd=0;
		temp->even=0;
		temp->n=0;
		temp->r = NIL;
		temp->l = NIL;
		temp->p = NIL;
		temp->c = 1;
		poi[i]=malloc(sizeof(struct store));
		poi[i]->priceNode=temp;

		//building
		root=bst(root, NIL, temp);
		//update
		up=temp;
		while(up!=root){
			if(up!=NIL){
				if(up->l->n%2==1){
					up->odd=up->l->odd+up->r->odd;
					up->even=up->l->even+up->r->even+up->interval;
				}
				else if(up->l->n%2==0){
					up->odd=up->l->odd+up->r->even+up->interval;
					up->even=up->l->even+up->r->odd;
				}
			}
			up=up->p;
		}
		if(up!=NIL){
			if(up->l->n%2==1){
				up->odd=up->l->odd+up->r->odd;
				up->even=up->l->even+up->r->even+up->interval;
			}
			else if(up->l->n%2==0){
				up->odd=up->l->odd+up->r->even+up->interval;
				up->even=up->l->even+up->r->odd;
			}
		}
		root=insertFixup(root, NIL, temp);
		root->c=0;
	}
	//output
	if(N%2==0) P=low+root->odd;
	else P=low+root->even;
	printf("%lld\n", P);
	
	//testing
	/*for(i=0;i<N;i++){
		if(poi[i]->priceNode->p!=NIL) printf("p: %lld %lld\n", poi[i]->priceNode->p->A, poi[i]->priceNode->p->B);
		if(poi[i]->priceNode->l!=NIL) printf("l: %lld %lld\n", poi[i]->priceNode->l->A, poi[i]->priceNode->l->B);
		if(poi[i]->priceNode->r!=NIL) printf("r: %lld %lld\n", poi[i]->priceNode->r->A, poi[i]->priceNode->r->B);
		printf("%d, %lld %lld %d\n\n", i, poi[i]->priceNode->A, poi[i]->priceNode->B, poi[i]->priceNode->c);
	}
	printf("\n---------------------\n");*/

	int t;
	long long c, d, e, f;
	struct node* deal;
	for(i=0;i<M-1;i++){		
		//input t, c, d, e, f and update the prices
		scanf("%d %lld %lld %lld %lld", &t, &c, &d, &e, &f);
		deal=poi[t-1]->priceNode;
		if(deal->A>deal->B) low-=deal->B;
		else low-=deal->A;
		deal->A=(c*(P%1000000007)+d)%1000000007;
		deal->B=(e*(P%1000000007)+f)%1000000007;
		if(deal->A>deal->B){
			deal->interval=deal->A-deal->B;
			low+=deal->B;
		}
		else{
			deal->interval=deal->B-deal->A;
			low+=deal->A;
		}
		root=delete(root, NIL, deal);

		//reinsert
		root=bst(root, NIL, deal);
		//update
		up=deal;
		while(up!=root){
			if(up!=NIL){
				if(up->l->n%2==1){
					up->odd=up->l->odd+up->r->odd;
					up->even=up->l->even+up->r->even+up->interval;
				}
				else if(up->l->n%2==0){
					up->odd=up->l->odd+up->r->even+up->interval;
					up->even=up->l->even+up->r->odd;
				}
			}
			up=up->p;
		}
		if(up!=NIL){
			if(up->l->n%2==1){
				up->odd=up->l->odd+up->r->odd;
				up->even=up->l->even+up->r->even+up->interval;
			}
			else if(up->l->n%2==0){
				up->odd=up->l->odd+up->r->even+up->interval;
				up->even=up->l->even+up->r->odd;
			}
		}
		root=insertFixup(root, NIL, deal);
		root->c=0;
		
		//testing
		/*for(j=0;j<N;j++){
			if(poi[j]->priceNode->p!=NIL) printf("p: %lld %lld\n", poi[j]->priceNode->p->A, poi[j]->priceNode->p->B);
			if(poi[j]->priceNode->l!=NIL) printf("l: %lld %lld\n", poi[j]->priceNode->l->A, poi[j]->priceNode->l->B);
			if(poi[j]->priceNode->r!=NIL) printf("r: %lld %lld\n", poi[j]->priceNode->r->A, poi[j]->priceNode->r->B);
			printf("%d, %lld %lld %d\n\n", j, poi[j]->priceNode->A, poi[j]->priceNode->B, poi[j]->priceNode->c);
		}
		printf("\n---------------------\n");*/

    //output
		if(N%2==0) P=low+root->odd;
		else P=low+root->even;
		printf("%lld\n", P);
	}
}


struct node* bst(struct node* trav, struct node* NIL, struct node* temp){
	if (trav==NIL || trav==NULL){
		temp->c=1;
		temp->n++;
		return temp;
	}

	if(temp->interval<trav->interval){
		trav->l=bst(trav->l, NIL, temp);
		trav->l->p=trav;
		trav->n++;
	}
	else if(temp->interval>trav->interval){
		trav->r=bst(trav->r, NIL, temp);
		trav->r->p=trav;
		trav->n++;
	}
	else{
		long long minTE, minTR;
		if(temp->A>temp->B) minTE=temp->B;
		else minTE=temp->A;
		if(trav->A>trav->B) minTR=temp->B;
		else minTR=trav->A;

		if(minTE>minTR){
			trav->l=bst(trav->l, NIL, temp);
                	trav->l->p=trav;
			trav->n++;
		}
		else{
			trav->r=bst(trav->r,NIL, temp);
                	trav->r->p=trav;
			trav->n++;
		}
	}
	return trav;
}

struct node* rightrotate(struct node* root, struct node* NIL, struct node* temp){
	struct node* left = temp->l;
	temp->l=left->r;
	if(temp->l!=NIL) temp->l->p=temp;
	left->p=temp->p;
	if(temp->p==NIL) root=left;
	else if(temp==temp->p->l) temp->p->l=left;
	else temp->p->r=left;
	left->r=temp;
	temp->p=left;

	//root in case
	if(root==temp) root=left;

	//update
	if(temp!=NIL) temp->n=1+temp->l->n+temp->r->n;
	if(left!=NIL) left->n=1+left->l->n+left->r->n;
	
	if(temp!=NIL){
		if(temp->l->n%2==1){
			temp->odd=temp->l->odd+temp->r->odd;
			temp->even=temp->l->even+temp->r->even+temp->interval;
		}
		else if(temp->l->n%2==0){
			temp->odd=temp->l->odd+temp->r->even+temp->interval;
			temp->even=temp->l->even+temp->r->odd;
		}
	}
	if(left!=NIL){
		if(left->l->n%2==1){
			left->odd=left->l->odd+left->r->odd;
			left->even=left->l->even+left->r->even+left->interval;
		}
		else if(left->l->n%2==0){
			left->odd=left->l->odd+left->r->even+left->interval;
			left->even=left->l->even+left->r->odd;
		}
	}

	return root;
}

struct node* leftrotate(struct node* root, struct node* NIL, struct node* temp){
	struct node* right=temp->r;
	temp->r=right->l;
	if (temp->r!=NIL) temp->r->p=temp;
	right->p=temp->p;
	if (temp->p==NIL) root=right;
	else if (temp==temp->p->l) temp->p->l=right;
	else temp->p->r=right;
	right->l=temp;
	temp->p=right;

	//root in case
	if(root==temp) root=right;

	//update
	if(temp!=NIL) temp->n=1+temp->l->n+temp->r->n;
	if(right!=NIL) right->n=1+right->l->n+right->r->n;
	
	if(temp!=NIL){
		if(temp->l->n%2==1){
			temp->odd=temp->l->odd+temp->r->odd;
			temp->even=temp->l->even+temp->r->even+temp->interval;
		}
		else if(temp->l->n%2==0){
			temp->odd=temp->l->odd+temp->r->even+temp->interval;
			temp->even=temp->l->even+temp->r->odd;
		}
	}
	if(right!=NIL){
		if(right->l->n%2==1){
			right->odd=right->l->odd+right->r->odd;
			right->even=right->l->even+right->r->even+right->interval;
		}
		else if(right->l->n%2==0){
			right->odd=right->l->odd+right->r->even+right->interval;
			right->even=right->l->even+right->r->odd;
		}
	}

	return root;
}

struct node* insertFixup(struct node* root, struct node* NIL, struct node* pt){
	struct node* parent_pt = NIL;
	struct node* grand_parent_pt = NIL;

	while(pt!=root && pt->c==1 && pt->p->c==1){
		parent_pt=pt->p;
		grand_parent_pt=pt->p->p;

		if(parent_pt==grand_parent_pt->l){
			struct node* uncle_pt = grand_parent_pt->r;

			if(uncle_pt!=NIL && uncle_pt->c==1){
				grand_parent_pt->c=1;
				parent_pt->c=0;
				uncle_pt->c=0;
				pt=grand_parent_pt;
			}
			else{
				if(pt==parent_pt->r){
					root=leftrotate(root, NIL, parent_pt);
					pt=parent_pt;
					parent_pt=pt->p;
				}
				root=rightrotate(root, NIL, grand_parent_pt);
				int t=parent_pt->c;
				parent_pt->c=grand_parent_pt->c;
				grand_parent_pt->c=t;
				pt=parent_pt;
			}
		}
		else{
			struct node* uncle_pt=grand_parent_pt->l;

			if(uncle_pt!=NIL && uncle_pt->c==1){
				grand_parent_pt->c=1;
				parent_pt->c=0;
				uncle_pt->c=0;
				pt=grand_parent_pt;
			}
			else{
				if (pt==parent_pt->l){
					root=rightrotate(root, NIL, parent_pt);
					pt = parent_pt;
					parent_pt=pt->p;
				}
				root=leftrotate(root, NIL, grand_parent_pt);
				int t=parent_pt->c;
				parent_pt->c = grand_parent_pt->c;
				grand_parent_pt->c=t;
				pt=parent_pt;
			}
		}
	}
	return root;
}

struct node* delete(struct node* root, struct node* NIL, struct node* node){
	struct node* x;
	struct node* y=node;
	int yori=y->c;
	if(node->l==NIL){
		x=node->r;
		root=transplant(root, NIL, node, node->r);
	}
	else if(node->r==NIL){
		x=node->l;
		root=transplant(root, NIL, node, node->l);
	}
	else{
		y=successor(NIL, node->r);
		yori=y->c;
		x=y->r;
		if(y->p==node) x->p=y;
		else{
			root=transplant(root, NIL, y, y->r);
			y->r=node->r;
			y->r->p=y;
		}
		root=transplant(root, NIL, node, y);
		y->l=node->l;
		y->l->p=y;
		y->c=node->c;
	}
	
	//parity
	struct node* pass=x;
	while (pass!=root){
        	if(pass!=NIL) pass->n=1+pass->l->n+pass->r->n;
        	else pass->n=0;
        	pass=pass->p;
	}
	if(root!=NIL) root->n=1+root->l->n+root->r->n;
	
	struct node* temp=x;
	while(temp!=root){
		if(temp!=NIL){
			if(temp->l->n%2==1){
				temp->odd=temp->l->odd+temp->r->odd;
				temp->even=temp->l->even+temp->r->even+temp->interval;
			}
			else if(temp->l->n%2==0){
				temp->odd=temp->l->odd+temp->r->even+temp->interval;
				temp->even=temp->l->even+temp->r->odd;
			}
		}
		temp=temp->p;
	}
	if(yori==0) root=deleteFixup(root, NIL, x);
	NIL->p=NIL;
	NIL->l=NIL;
	NIL->r=NIL;
	node->p=NIL;
	node->l=NIL;
	node->r=NIL;
	node->n=0;
	return root;
}

struct node* deleteFixup(struct node* root, struct node* NIL, struct node* pt){
	struct node* sibling_pt=NIL;
	while(pt!=root && pt->c==0){
		if(pt==pt->p->l){
            		sibling_pt=pt->p->r;
			if(sibling_pt->c==1){
				sibling_pt->c=0;
				pt->p->c=1;
				root=leftrotate(root, NIL, pt->p);
				sibling_pt=pt->p->r;
			}
			if(sibling_pt->l->c==0 && sibling_pt->r->c==0){
				sibling_pt->c=1;
				pt=pt->p;
			}
			else{
				if(sibling_pt->r->c==0){
					sibling_pt->l->c=0;
					sibling_pt->c=1;
					root=rightrotate(root, NIL, sibling_pt);
					sibling_pt=pt->p->r;
				}
				sibling_pt->c=pt->p->c;
				pt->p->c=0;
				sibling_pt->r->c=0;
				root=leftrotate(root, NIL, pt->p);
				pt=root;
			}
		}
		else{
			sibling_pt=pt->p->l;
			if(sibling_pt->c==1){
				sibling_pt->c=0;
				pt->p->c=1;
				root=rightrotate(root, NIL, pt->p);
				sibling_pt=pt->p->l;
			}
			if(sibling_pt->r->c==0 && sibling_pt->l->c==0){
				sibling_pt->c=1;
				pt=pt->p;
			}
			else{
				if(sibling_pt->l->c==0){
					sibling_pt->r->c=0;
					sibling_pt->c=1;
					root=leftrotate(root, NIL, sibling_pt);
					sibling_pt=pt->p->l;
				}
				sibling_pt->c=pt->p->c;
				pt->p->c=0;
				sibling_pt->l->c=0;
				root=rightrotate(root, NIL, pt->p);
				pt=root;
			}
		}
	}
	pt->c=0;
	return root;
}

struct node* transplant(struct node* root, struct node* NIL, struct node* u, struct node* v){
	if(u->p==NIL) root=v;
	else if(u==u->p->l) u->p->l=v;
	else u->p->r=v;
	v->p=u->p;
	return root;
}

struct node* successor(struct node* NIL, struct node* node){
    struct node* current=node;
    while (current->l!=NIL) current=current->l;
    return current;
}
