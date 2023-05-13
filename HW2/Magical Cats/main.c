#include<stdio.h>
#include<stdlib.h>

typedef struct node1{
	int appetite;
	int color;
	int index;
	struct node1* larger;
	struct node1* smaller;
	struct node2* idx_pos;
}CAT;

typedef struct node2{
	int appetite;
	struct node1* cat_pos;
}IDX;

typedef struct node3{
	int head;
	int tail;
	int len;
	int color;
	int** cats; //appetite
}MENU;

int cmp_d2d(const void* a, const void* b);
int cmp_2d(const void* a, const void* b);
int cmp_ll(const void* a, const void* b);

int main(){
	int i, j;

	int N, M; //the # of cats, the # of steps
	scanf("%d %d",  &N, &M);

	//appetite
	IDX* idx_app[N];
	CAT* cat_sorted[N];
	for(i=0;i<N;i++){
		cat_sorted[i]=malloc(sizeof(CAT));
		idx_app[i]=malloc(sizeof(IDX));
		scanf("%d", &cat_sorted[i]->appetite);
		cat_sorted[i]->index=i;
		idx_app[i]->appetite=cat_sorted[i]->appetite;
		cat_sorted[i]->idx_pos=idx_app[i];
	}
	
	//the color of the ith cat
	int color_sorted[N][2]; //index, color
	for(i=0;i<N;i++){
		color_sorted[i][0]=i;
		scanf("%d", &color_sorted[i][1]);
	}
	//sorted
	qsort(color_sorted, N, sizeof(color_sorted[0]), cmp_2d);
/*
	//testing
	for(i=0;i<N;i++){
		printf("index: %d, appetite: %d\n", cat_sorted[i]->index, cat_sorted[i]->appetite);
	}
	for(i=0;i<N;i++){
		printf("index: %d, color: %d\n", color_sorted[i][0], color_sorted[i][1]);
	}
*/	
	/////////////////////////////////////////////////////////////////////////////////COLOR
	//count how many colors
	int count=1;
	for(i=1;i<N;i++){
		if(color_sorted[i-1][1]!=color_sorted[i][1]) count++;
	}
	//color discretization
	int temp=0;
	MENU* MC[count];
	MC[0]=malloc(sizeof(MENU));
	MC[0]->head=0;
	MC[0]->head++;
	cat_sorted[color_sorted[0][0]]->color=temp;
	for(i=1;i<N;i++){
		if(color_sorted[i-1][1]!=color_sorted[i][1]){
			MC[temp]->cats=(int**)malloc(MC[temp]->head*sizeof(int*));
			for(j=0;j<MC[temp]->head;j++) MC[temp]->cats[j]=(int*)malloc(2*sizeof(int));
			MC[temp]->len=MC[temp]->head;
			MC[temp]->tail=MC[temp]->head-1;
			MC[temp]->color=color_sorted[i-1][1];
			temp++;
			MC[temp]=malloc(sizeof(MENU));
			MC[temp]->head=0;
			MC[temp]->head++;
			cat_sorted[color_sorted[i][0]]->color=temp;
		}
		else{
			MC[temp]->head++;
			cat_sorted[color_sorted[i][0]]->color=temp;
		}
	}
	MC[temp]->cats=(int**)malloc(MC[temp]->head*sizeof(int*));
	for(j=0;j<MC[temp]->head;j++) MC[temp]->cats[j]=(int*)malloc(2*sizeof(int));
	MC[temp]->len=MC[temp]->head;
	MC[temp]->tail=MC[temp]->head-1;
	MC[temp]->color=color_sorted[N-1][1];
	//cats appetite
	temp=0;
	MC[0]->cats[MC[0]->head-1][1]=cat_sorted[color_sorted[0][0]]->appetite;
	MC[0]->cats[MC[0]->head-1][0]=cat_sorted[color_sorted[0][0]]->index;
	MC[0]->head--;
	for(i=1;i<N;i++){
		if(color_sorted[i-1][1]!=color_sorted[i][1]){
			qsort(MC[temp]->cats, MC[temp]->len, sizeof(MC[temp]->cats[0]), cmp_d2d);
			temp++;
			MC[temp]->cats[MC[temp]->head-1][1]=cat_sorted[color_sorted[i][0]]->appetite;
			MC[temp]->cats[MC[temp]->head-1][0]=cat_sorted[color_sorted[i][0]]->index;
			MC[temp]->head--;
		}
		else{
			MC[temp]->cats[MC[temp]->head-1][1]=cat_sorted[color_sorted[i][0]]->appetite;
			MC[temp]->cats[MC[temp]->head-1][0]=cat_sorted[color_sorted[i][0]]->index;
			MC[temp]->head--;
		}
	}
	qsort(MC[temp]->cats, MC[temp]->len, sizeof(MC[temp]->cats[0]), cmp_d2d);
	/*
	//testing
	for(i=0;i<count;i++){
		printf("%d: len: %d\n", i, MC[i]->len);
		for(j=0;j<MC[i]->len;j++) printf("index: %d, appetite: %d\n", MC[i]->cats[j][0], MC[i]->cats[j][1]);
		printf("\n");
	}*/
	////////////////////////////////////////////////////////////////////////////////CAT
	//appetite sort
	qsort(cat_sorted, N, sizeof(cat_sorted[0]), cmp_ll);
	for(i=0;i<N;i++) cat_sorted[i]->idx_pos->cat_pos=cat_sorted[i];
/*
	//testing
	printf("cat_sorted\n");
	for(i=0;i<N;i++) printf("index: %d, appetite: %d\n", cat_sorted[i]->index, cat_sorted[i]->appetite);
	printf("idx_app\n");
	for(i=0;i<N;i++) printf("index: %d, appetite: %d\n", i, idx_app[i]->appetite);
	printf("idx->cat\n");
	for(i=0;i<N;i++) printf("index: %d, appetite: %d\n", idx_app[i]->cat_pos->index, idx_app[i]->cat_pos->appetite);
	printf("cat->idx\n");
	for(i=0;i<N;i++) printf("index: %d, appetite: %d\n", cat_sorted[i]->index, cat_sorted[i]->idx_pos->appetite);
*/
	//larger and smaller, circular array
	CAT* head=cat_sorted[0];
	CAT* tail=cat_sorted[N-1];
	for(i=0;i<N;i++){
		if(i==N-1){
			cat_sorted[i]->larger=cat_sorted[0];
			cat_sorted[i]->smaller=cat_sorted[i-1];
		}
		else if(i==0){
			cat_sorted[i]->larger=cat_sorted[i+1];
			cat_sorted[i]->smaller=cat_sorted[N-1];
		}
		else{
			cat_sorted[i]->larger=cat_sorted[i+1];
			cat_sorted[i]->smaller=cat_sorted[i-1];
		}
	}
/*
	//testing
      	printf("\n///////////////////////////////////////////////\n");
        printf("cat_sorted\napp, head: %d, tail: %d\nidx, head: %d, tail: %d\n", head->appetite, tail->appetite, head->index, tail->index);
        printf("MC\n");
        for(j=0;j<count;j++){
		printf("color: %d, head: %d, tail: %d\nindex\n", MC[j]->color, MC[j]->head, MC[j]->tail);
                for(int g=0;g<MC[j]->len;g++) printf("%d ", MC[j]->cats[g][0]);
                printf("\nappetite\n");
               	for(int g=0;g<MC[j]->len;g++) printf("%d ", MC[j]->cats[g][1]);
                printf("\n");
         }
	printf("idx_app\n");
        for(j=0;j<N;j++) printf("%d ", idx_app[j]->cat_pos->appetite);
	printf("\n///////////////////////////////////////////////\n\n");
*/
	////////////////////////////////////////////////////////////////////////////////STEPS
	//steps
	int step, c, l, r, k, s, t;
	int left, right, mid;
	int lb, rb, mb, mb_r; //count cats in step one and two
	int lidx, ridx; //for step one
	CAT* greedy; //for step two, greedy cat
	CAT* poor; //for step two, poor cat
	int newapp; //for step three, max+1 or min-1
	CAT* temp_cat; //for step three
	CAT* small_cat; //new small cat for temp_cat
	CAT* large_cat; //new large cat for temp_cat
	for(i=0;i<M;i++){
		scanf("%d", &step);

		//a questioning step
		if(step==1){
			scanf("%d %d %d", &c, &l, &r); //the color, the lower bound, the upper bound
			//binary search, find the color
			left=0;
			right=count-1;
			while(left<=right){
				mid=(left+right)/2;
				if(c==MC[mid]->color) break;
				else if(c>MC[mid]->color) left=mid+1;
				else right=mid-1;
			}
			if(MC[mid]->color==c){
				//lower bound, bs
				if(l<=MC[mid]->cats[MC[mid]->head][1]) lidx=0;
				else{
					lb=0;
					rb=MC[mid]->len-1;
					while(lb<=rb){
						mb=(lb+rb)/2;
						//revise to the correct pos
                               	       		if(mb+MC[mid]->head>=MC[mid]->len) mb_r=mb-MC[mid]->len+MC[mid]->head;
                               	      		else mb_r=mb+MC[mid]->head;
						//search
						if(l==MC[mid]->cats[mb_r][1]){
							lidx=mb;
							break;
						}
						else if(l>MC[mid]->cats[mb_r][1]) lb=mb+1;
						else rb=mb-1;
					}
					if(lb>rb) lidx=lb;
				}
				//upper bound, bs
				if(r>=MC[mid]->cats[MC[mid]->tail][1]) ridx=MC[mid]->len-1;
				else{
					lb=0;
					rb=MC[mid]->len-1;
					while(lb<=rb){
						mb=(lb+rb)/2;
						//revise to the correct pos
						if(mb+MC[mid]->head>=MC[mid]->len) mb_r=mb-MC[mid]->len+MC[mid]->head;
						else mb_r=mb+MC[mid]->head;
						//search
						if(r==MC[mid]->cats[mb_r][1]){
							ridx=mb;
							break;
						}
						else if(r>MC[mid]->cats[mb_r][1]) lb=mb+1;
						else rb=mb-1;
					}
					if(lb>rb) ridx=rb;
				}
				printf("%d\n", ridx-lidx+1);
			}
			else printf("%d\n", 0);
		}

		//a swapping step
		else if(step==2){
			scanf("%d", &k); //the index of greedy cat
			greedy=idx_app[k]->cat_pos;
			poor=greedy->larger;
			//swap appetite and ca_pos in idx
			idx_app[k]->appetite=poor->appetite;
			idx_app[k]->cat_pos=poor;
			poor->idx_pos=idx_app[k];
			idx_app[poor->index]->appetite=greedy->appetite;
			idx_app[poor->index]->cat_pos=greedy;
			greedy->idx_pos=idx_app[poor->index];
			//swap index in cat_sorted
			temp=greedy->index;
			greedy->index=poor->index;
			poor->index=temp;
			//swap appetite in MENU and color
			//diff color
			if(greedy->color!=poor->color){
				//bs for greedy cat in its original color
				lb=0;
				rb=MC[greedy->color]->len-1;
                                while(lb<=rb){
					mb=(lb+rb)/2;
                                        //revise to the correct pos
                                        if(mb+MC[greedy->color]->head>=MC[greedy->color]->len) mb_r=mb-MC[greedy->color]->len+MC[greedy->color]->head;
                                        else mb_r=mb+MC[greedy->color]->head;
                                        //search
                                        if(greedy->appetite==MC[greedy->color]->cats[mb_r][1]) break;
                                        else if(greedy->appetite>MC[greedy->color]->cats[mb_r][1]) lb=mb+1;
                                        else rb=mb-1;
                                }
				//change greedy cat's appetite
				MC[greedy->color]->cats[mb_r][1]=poor->appetite;
				//bs for poor cat in its original color
                                lb=0;
                                rb=MC[poor->color]->len-1;
                                while(lb<=rb){
                                        mb=(lb+rb)/2;
                                        //revise to the correct pos
                                        if(mb+MC[poor->color]->head>=MC[poor->color]->len) mb_r=mb-MC[poor->color]->len+MC[poor->color]->head;
                                        else mb_r=mb+MC[poor->color]->head;
                                        //search
                                        if(poor->appetite==MC[poor->color]->cats[mb_r][1]) break;
                                        else if(poor->appetite>MC[poor->color]->cats[mb_r][1]) lb=mb+1;
                                        else rb=mb-1;
                                }
                                //change poor cat's index and appetite
                                MC[poor->color]->cats[mb_r][1]=greedy->appetite;
				//swap color
				temp=greedy->color;
                                greedy->color=poor->color;
                                poor->color=temp;
			}
			//same color
			else{
				//bs for greedy cat in its original color
				lb=0;
				rb=MC[greedy->color]->len-1;
                                while(lb<=rb){
					mb=(lb+rb)/2;
                                        //revise to the correct pos
                                        if(mb+MC[greedy->color]->head>=MC[greedy->color]->len) mb_r=mb-MC[greedy->color]->len+MC[greedy->color]->head;
                                        else mb_r=mb+MC[greedy->color]->head;
                                        //search
                                        if(greedy->appetite==MC[greedy->color]->cats[mb_r][1]) break;
                                        else if(greedy->appetite>MC[greedy->color]->cats[mb_r][1]) lb=mb+1;
                                        else rb=mb-1;
                                }
				//change greedy cat's index
				MC[greedy->color]->cats[mb_r][0]=greedy->index;
				MC[greedy->color]->cats[(mb_r+1)%MC[greedy->color]->len][0]=poor->index;
			}
			/*
			//testing
			for(i=0;i<N;i++) printf("%d: %d\n", cat_sorted[i]->index, cat_sorted[i]->appetite);
			for(i=0;i<count;i++){
				printf("%d: ", i);
				for(int j=0;j<MC[i]->len;j++) printf("%d ", MC[i]->cats[j]);
				printf("\n");
			}*/
			
		}

		//a magic step
		else if(step==3){
			scanf("%d %d %d", &c, &s, &t); //the color, the direction of the magic, success/failure
			//binary search, find the color
			left=0;
			right=count-1;
			while(left<=right){
				mid=(left+right)/2;
				if(c==MC[mid]->color) break;
				else if(c>MC[mid]->color) left=mid+1;
				else right=mid-1;
			}
			//success, max+1
			if(t==1){
				//lowest(head)
				newapp=tail->appetite+1;
				if(s==0){
					//MENU, min becomes max
					MC[mid]->cats[MC[mid]->head][1]=newapp;
					//idx appetite
                                        idx_app[MC[mid]->cats[MC[mid]->head][0]]->appetite=newapp;
					//cat_sorted appetite, larger and smaller, head and tail
					temp_cat=idx_app[MC[mid]->cats[MC[mid]->head][0]]->cat_pos;
					temp_cat->appetite=newapp;
					if(head->index==temp_cat->index){
						head=temp_cat->larger;
						tail=temp_cat;
					}
					else if(tail->index!=temp_cat->index){
						temp_cat->smaller->larger=temp_cat->larger;
                                       	 	temp_cat->larger->smaller=temp_cat->smaller;
						//new small cat and large cat
						small_cat=tail;
						large_cat=tail->larger;
						small_cat->larger=temp_cat;
						temp_cat->smaller=small_cat;
						large_cat->smaller=temp_cat;
						temp_cat->larger=large_cat;
						//cat_sorted tail
						tail=temp_cat;
					}
					//MENU head and tail
					MC[mid]->tail=MC[mid]->head;
					MC[mid]->head=(MC[mid]->head+1)%MC[mid]->len;
				}
				//highest(tail)
				else{
                                        //MENU
                                        MC[mid]->cats[MC[mid]->tail][1]=newapp;
                                        //idx appetite
                                        idx_app[MC[mid]->cats[MC[mid]->tail][0]]->appetite=newapp;
                                        //cat_sorted appetite, larger and smaller, head and tail
                                        temp_cat=idx_app[MC[mid]->cats[MC[mid]->tail][0]]->cat_pos;
					temp_cat->appetite=newapp;
                                        if(head->index==temp_cat->index){
                                                head=temp_cat->larger;
                                                tail=temp_cat;
                                        }
                                        else if(tail->index!=temp_cat->index){
                                                temp_cat->smaller->larger=temp_cat->larger;
                                                temp_cat->larger->smaller=temp_cat->smaller;
                                                //new small cat and large cat
                                                small_cat=tail;
                                                large_cat=tail->larger;
                                                small_cat->larger=temp_cat;
                                                temp_cat->smaller=small_cat;
                                                large_cat->smaller=temp_cat;
                                                temp_cat->larger=large_cat;
                                                //cat_sorted tail
                                                tail=temp_cat;
                                        }

				}
			}
			//failure, min-1;
			else{
				newapp=head->appetite-1;
				//lowest(head)
				if(s==0){
					//MENU
					MC[mid]->cats[MC[mid]->head][1]=newapp;
					//idx appetite
                                        idx_app[MC[mid]->cats[MC[mid]->head][0]]->appetite=newapp;
					//cat_sorted appetite, larger and smaller, head and tail
					temp_cat=idx_app[MC[mid]->cats[MC[mid]->head][0]]->cat_pos;
					temp_cat->appetite=newapp;
					if(tail->index==temp_cat->index){
						tail=temp_cat->smaller;
						head=temp_cat;
					}
					else if(head->index!=temp_cat->index){
						temp_cat->smaller->larger=temp_cat->larger;
                                       	 	temp_cat->larger->smaller=temp_cat->smaller;
						//new small cat and large cat
						small_cat=head->smaller;
						large_cat=head;
						small_cat->larger=temp_cat;
						temp_cat->smaller=small_cat;
						large_cat->smaller=temp_cat;
						temp_cat->larger=large_cat;
						//cat_sorted tail
						head=temp_cat;
					}
				}
				//highest(tail)
				else{
                                        //MENU
                                        MC[mid]->cats[MC[mid]->tail][1]=newapp;
                                        //idx appetite
                                        idx_app[MC[mid]->cats[MC[mid]->tail][0]]->appetite=newapp;
                                        //cat_sorted appetite, larger and smaller, head and tail
                                        temp_cat=idx_app[MC[mid]->cats[MC[mid]->tail][0]]->cat_pos;
					temp_cat->appetite=newapp;
                                        if(tail->index==temp_cat->index){
                                                tail=temp_cat->smaller;
                                                head=temp_cat;
                                        }
                                        else if(head->index!=temp_cat->index){
                                                temp_cat->smaller->larger=temp_cat->larger;
                                                temp_cat->larger->smaller=temp_cat->smaller;
                                                //new small cat and large cat
                                                small_cat=head->smaller;
                                                large_cat=head;
                                                small_cat->larger=temp_cat;
                                                temp_cat->smaller=small_cat;
                                                large_cat->smaller=temp_cat;
                                                temp_cat->larger=large_cat;
                                                //cat_sorted tail
                                                head=temp_cat;
                                        }
					//MENU head and tail
                                        MC[mid]->head=MC[mid]->tail;
					if(MC[mid]->tail-1<0) MC[mid]->tail=MC[mid]->len-1;
					else MC[mid]->tail=MC[mid]->tail-1;


				}
			}
		}
		/*
		//testing
		printf("\n///////////////////////////////////////////////\nnumber: %d\n", i);
		if(step==1) printf("1: %d %d %d\n", c, l, r);
		else if(step==2) printf("2: %d\n", k);
		else printf("3: %d %d %d\n", c, s, t);
		printf("cat_sorted\napp, head: %d, tail: %d\nidx, head: %d, tail: %d\n", head->appetite, tail->appetite, head->index, tail->index);
		printf("MC\n");
		for(j=0;j<count;j++){
				printf("color: %d, head: %d, tail: %d\nindex\n", MC[j]->color, MC[j]->head, MC[j]->tail);
				for(int g=0;g<MC[j]->len;g++) printf("%d ", MC[j]->cats[g][0]);
				printf("\nappetite\n");
				for(int g=0;g<MC[j]->len;g++) printf("%d ", MC[j]->cats[g][1]);
				printf("\n");
		}
		printf("idx_app\n");
		for(j=0;j<N;j++) printf("%d ", idx_app[j]->cat_pos->appetite);
		printf("\n///////////////////////////////////////////////\n\n");
		*/
	}
}

int cmp_d2d(const void* a, const void* b){
	int* arr1=*(int**)a;
	int* arr2=*(int**)b;
	return arr1[1]-arr2[1];
}

int cmp_2d(const void*a, const void* b){
	return ((int *)a)[1]-((int *)b)[1];
}

int cmp_ll(const void*a, const void* b){
    const CAT** ptr_a = (const CAT**)a;
    const CAT** ptr_b = (const CAT**)b;
    return (*ptr_a)->appetite - (*ptr_b)->appetite;
}
