#include <stdio.h>

int main(){
        int a;
        int b;
        scanf("%d %d", &a, &b);

        int n;
        int m;
        if(a>b){
                m=a;
                n=b;
        }
        else{
                m=b;
                n=a;
        }
        int ans=1;

        while(n!=0 && m!=0){
                if(n%2==0 && m%2==0){
                        ans=ans*2;
                        n=n/2;
                        m=m/2;
                }
                else if(n%2==0) n=n/2;
                else if(m%2==0) m=m/2;

                if(n>m){
                        int temp=n;
                        n=m;
                        m=temp;
                }
                m=m-n;
        }
        printf("%d", n*ans);
}
