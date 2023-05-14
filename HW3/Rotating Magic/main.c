#include<stdio.h>
#include<stdlib.h>

#define q1 62011379
#define q2 58082989
#define q3 12345653

int main(){
	int i, temp;

	//input N and M
	int N, M; //first line, second line
	scanf("%d %d", &N, &M);

	int chr[26];
	for(i=0;i<26;i++) chr[i]=0;
	//first line
	char fL[N];
	getchar();
	for(i=0;i<N;i++){
		scanf("%c", &fL[i]);
		temp=fL[i]-65;
		chr[temp]=1;
	}
	//second line
	char sL[M];
	getchar();
	for(i=0;i<M;i++){
		scanf("%c", &sL[i]);
		temp=sL[i]-65;
		chr[temp]=1;
	}
	/*
	//testing
	for(i=0;i<N;i++) printf("%c", fL[i]);
	printf("\n");
	for(i=0;i<M;i++) printf("%d %c\n", i, sL[i]);
	printf("\n");
	*/
	//find d
	int d=0;
	for(i=0;i<26;i++) if(chr[i]!=0) d+=1;

	///////////////////////////////////////////hash
	int hash1[q1]={0};
	int hash2[q2]={0};
	int hash3[q3]={0};
	int h1=1; //d^(M-1)%q1
	int h2=1; //d^(M-1)%q2
	int h3=1; //d^(M-1)%q3
	//original
	long long ori1=0;
	long long firstL1=0; //first line segment (%q1)
	long long ori2=0;
        long long firstL2=0; //first line segment (%q2)
        long long ori3=0;
        long long firstL3=0; //first line segment (%q3)
	for(i=0;i<M;i++){
		ori1=(ori1*d+(sL[i]-64))%q1;
		firstL1=(firstL1*d+(fL[i]-64))%q1;
		if(i<M-1) h1=(h1*d)%q1;
                ori2=(ori2*d+(sL[i]-64))%q2;
                firstL2=(firstL2*d+(fL[i]-64))%q2;
                if(i<M-1) h2=(h2*d)%q2;
                ori3=(ori3*d+(sL[i]-64))%q3;
                firstL3=(firstL3*d+(fL[i]-64))%q3;
                if(i<M-1) h3=(h3*d)%q3;
	}
	//printf("h: %d\n", h);
	hash1[ori1]+=1;
	hash2[ori2]+=1;
	hash3[ori3]+=1;
	//rotation
	long long rot1=ori1;
	long long rot2=ori2;
	long long rot3=ori3;
	for(i=0;i<M-1;i++){ //only M-1 rotation
		temp=sL[i]-64;
		rot1=(d*(rot1-h1*temp)+temp)%q1;
		if(rot1<0) rot1=rot1+q1;
		hash1[rot1]+=1;
                rot2=(d*(rot2-h2*temp)+temp)%q2;
		if(rot2<0) rot2=rot2+q2;
                hash2[rot2]+=1;
                rot3=(d*(rot3-h3*temp)+temp)%q3;
                if(rot3<0) rot3=rot3+q3;
                hash3[rot3]+=1;
	}
	/*
	//testing
	for(i=0;i<q;i++) if(hash[i]!=0) printf("%d %d\n", i, hash[i]);
	*/

	///////////////////////////////////////////matching
	int count=0;
	int head, tail;
	for(i=0;i<N-M+1;i++){
		//printf("%d\n", firstL);
		if(hash1[firstL1]!=0 && hash2[firstL2]!=0 && hash3[firstL3]!=0) count++;
		if(i<N-M){
			head=fL[i]-64;
			tail=fL[i+M]-64;
			firstL1=(d*(firstL1-h1*head)+tail)%q1;
			if(firstL1<0) firstL1=firstL1+q1;
			firstL2=(d*(firstL2-h2*head)+tail)%q2;
			if(firstL2<0) firstL2=firstL2+q2;
                        firstL3=(d*(firstL3-h3*head)+tail)%q3;
                        if(firstL3<0) firstL3=firstL3+q3;
		}
	}
	printf("%d", count);
}
