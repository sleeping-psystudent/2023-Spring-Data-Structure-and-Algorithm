#include<stdio.h>
#include<stdlib.h>

//#define q1 62011379
//#define q2 58082989
//#define q3 12345653

#define q1 12345653
#define q2 999907
#define q3 400009

#define Nmax 1000001

typedef struct node{
	int m1;
	int m2;
	int m3;
	int size;
}hash;

int main(){
	int i, j, temp;

	int N, Q; //the # of strings inside S; the number of operations
	scanf("%d %d", &N, &Q);

	//hash table and initial
	hash* record[q1];

	//t_i input
	char *t = malloc(Nmax*sizeof(char));
	char tempC;
	long long h1=1;
	long long h2=1;
	long long h3=1;
	long long t1, t2, t3;
	long long min1, min2, min3;
	int d=26;
	int len=0;
	int pair;
	long long count=0;
	int P;
	long long pos;
	for(i=0;i<N;i++){
		t1=0;
		t2=0;
		t3=0;
		if(i==0){
			getchar();
			while(scanf("%c", &tempC)==1){
				if(tempC=='\n') break;
				if(len!=0){
					h1=(h1*d)%q1;
					h2=(h2*d)%q2;
					h3=(h3*d)%q3;
				}
				t[len]=tempC;
				t1=(d*t1+(t[len]-96))%q1;
				t2=(d*t2+(t[len]-96))%q2;
				t3=(d*t3+(t[len]-96))%q3;
				len++;
			}
		}
		else{
			if(i!=1) getchar();
			for(j=0;j<len;j++){
				scanf("%c", &t[j]);
				t1=(d*t1+(t[j]-96))%q1;
                                t2=(d*t2+(t[j]-96))%q2;
				t3=(d*t3+(t[j]-96))%q3;
			}
		}
		//printf("ori:%lld %lld %lld\n", t1, t2, t3);

		//check hash table and make rotation
		pair=0;
		min1=t1;
		min2=t2;
		min3=t3;
		for(j=0;j<len-1;j++){
			temp=t[j]-96;
			t1=(d*(t1-h1*temp)+temp)%q1;
			if(t1<0) t1=t1+q1;
			if(t1<min1) min1=t1;
			t2=(d*(t2-h2*temp)+temp)%q2;
			if(t2<0) t2=t2+q2;
			if(t2<min2) min2=t2;
			t3=(d*(t3-h3*temp)+temp)%q3;
                        if(t3<0) t3=t3+q3;
			if(t3<min3) min3=t3;
			//printf("rot:%lld %lld %lld\n", t1, t2, t3);	
		}
		//printf("min:%lld %lld %lld\n", min1, min2, min3);

		if(record[min1]!=NULL && record[min1]->m1==min1 && record[min1]->m2==min2 && record[min1]->m3==min3){
			pair+=record[min1]->size;
			record[min1]->size+=1;
		}
		else if(record[min2]!=NULL && record[min2]->m1==min1 && record[min2]->m2==min2 && record[min2]->m3==min3){
			pair+=record[min2]->size;
			record[min2]->size+=1;
		}
		else if(record[min3]!=NULL && record[min3]->m1==min1 && record[min3]->m2==min2 && record[min3]->m3==min3){
			pair+=record[min3]->size;
			record[min3]->size+=1;
		}
		else{
			if(record[min1]==NULL){
				record[min1]=malloc(sizeof(hash));
				record[min1]->m1=min1;
				record[min1]->m2=min2;
				record[min1]->m3=min3;
				record[min1]->size=1;
			}
			else if(record[min2]==NULL){
				record[min2]=malloc(sizeof(hash));
				record[min2]->m1=min1;
				record[min2]->m2=min2;
				record[min2]->m3=min3;
				record[min2]->size=1;
			}
			else if(record[min3]==NULL){
				record[min3]=malloc(sizeof(hash));
				record[min3]->m1=min1;
				record[min3]->m2=min2;
				record[min3]->m3=min3;
				record[min3]->size=1;
			}
		}
		//printf("pair:%d\n", pair);
		count+=pair;
	}
	printf("%lld\n", count);

	//P and t_j input
	for(i=0;i<Q;i++){
		getchar();
		scanf("%d", &P);
		getchar();
		t1=0;
		t2=0;
		t3=0;
		for(j=0;j<len;j++){
			scanf("%c", &t[j]);
                        t1=(d*t1+(t[j]-96))%q1;
                        t2=(d*t2+(t[j]-96))%q2;
                        t3=(d*t3+(t[j]-96))%q3;
                }
		//rotation
                min1=t1;
                min2=t2;
                min3=t3;
                for(j=0;j<len-1;j++){
                        temp=t[j]-96;
                        t1=(d*(t1-h1*temp)+temp)%q1;
                        if(t1<0) t1=t1+q1;
                        if(t1<min1) min1=t1;
                        t2=(d*(t2-h2*temp)+temp)%q2;
                        if(t2<0) t2=t2+q2;
                        if(t2<min2) min2=t2;
                        t3=(d*(t3-h3*temp)+temp)%q3;
                        if(t3<0) t3=t3+q3;
                        if(t3<min3) min3=t3;
                }

		pos=-1;
		if(record[min1]!=NULL && record[min1]->m1==min1 && record[min1]->m2==min2 && record[min1]->m3==min3) pos=min1;
                else if(record[min2]!=NULL && record[min2]->m1==min1 && record[min2]->m2==min2 && record[min2]->m3==min3) pos=min2;
                else if(record[min3]!=NULL && record[min3]->m1==min1 && record[min3]->m2==min2 && record[min3]->m3==min3) pos=min3;
		if(P==1){
			if(pos!=-1){
				count+=record[pos]->size;
				record[pos]->size+=1;
			}
			else{
				if(record[min1]==NULL){
					record[min1]=malloc(sizeof(hash));
					record[min1]->m1=min1;
					record[min1]->m2=min2;
					record[min1]->m3=min3;
					record[min1]->size=1;
				}
				else if(record[min2]==NULL){
					record[min2]=malloc(sizeof(hash));
					record[min2]->m1=min1;
                                        record[min2]->m2=min2;
                                        record[min2]->m3=min3;
                                        record[min2]->size=1;
				}
				else if(record[min3]==NULL){
					record[min3]=malloc(sizeof(hash));
					record[min3]->m1=min1;
                                        record[min3]->m2=min2;
                                        record[min3]->m3=min3;
					record[min3]->size=1;
				}
			}
		}
		else if(P==2){
			if(pos!=-1){
                                if(record[pos]->size!=0){
				       	record[pos]->size-=1;
					count-=record[pos]->size;
				}
                        }
		}
		printf("%lld\n", count);
	}
}
