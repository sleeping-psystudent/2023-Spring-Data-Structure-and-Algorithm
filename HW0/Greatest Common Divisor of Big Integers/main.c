#include <stdio.h>
#include <stdlib.h>

void binA(int*, int*, int*, int*);
void comp(int*, int*);

int main(){

        //input a string and divide them into arrays
        int *arr1;
        arr1=(int*)calloc(1000, sizeof(int));
        int *arr2;
        arr2=(int*)calloc(1000, sizeof(int));
        int ch;
        int alen1=0;
        int alen2=0;
        int note=0;

        while((ch=getchar())!='\n'){
                if(alen1!=0 && ch==' ') note=1;
                else if(note==0){
                        arr1[alen1]=ch-48;
                        //printf("%d %d\n", note, arr1[alen1]);
                        alen1=alen1+1;
                }
                else if(note==1){
                        arr2[alen2]=ch-48;
                        //printf("%d %d\n", note, arr2[alen2]);
                        alen2=alen2+1;
                }
        }

        //testing the arrays
        /*
        printf("%d\n%d\n", alen1, alen2);
        for(int i=0;i<alen1;i++){
                printf("%d", arr1[i]);
        }
        printf("\n");
        for(int j=0;j<alen2;j++){
                printf("%d", arr2[j]);
        }
        */
        /////////////////////////////////////////////////////////////////

        //reverse the arrays
        int temp;
        for(int i=0;i<alen1/2;i++){
                temp=arr1[i];
                arr1[i]=arr1[alen1-i-1];
                arr1[alen1-i-1]=temp;
        }
        for(int i=0;i<alen2/2;i++){
                temp=arr2[i];
                arr2[i]=arr2[alen2-i-1];
                arr2[alen2-i-1]=temp;
        }

        //testing the arrays
        /*
        for(int i=0;i<alen1;i++){
                printf("%d", arr1[i]);
        }
        */
        ///////////////////////////////////////////////////////////////

        /*
        //subtract
        if(alen1>alen2){
                while(alen1!=alen2){
                        sub(arr1, arr2, alen1, alen2);

                        int count=alen1;
                        for(int i=alen1-1;i>=alen2;i--){
                                if(arr1[i]>0) break;
                                else count=count-1;
                        }
                        if(count==alen2) alen1=count;
                        //printf("%d %d\n", alen1, alen2);
                }
        }
        else if(alen2>alen1){
                while(alen2!=alen1){
                        sub(arr2, arr1, alen2, alen1);

                        int count=alen2;
                        for(int i=alen2-1;i>=alen1;i--){
                                if(arr2[i]>0) break;
                                else count=count-1;
                        }
                        if(count==alen1) alen2=count;
                }
        }

        //testing the arrays
        for(int i=alen2-1;i>=0;i--){
                printf("%d", arr2[i]);
        }
        */

        //////////////////////////////////////////////////////////////

        int *ans;
        ans=(int*)calloc(1000, sizeof(int));

        int *rem;
        rem=(int*)calloc(1000, sizeof(int));
        rem[0]=1;

        //binary Alg
        comp(arr1, arr2);
        binA(arr1, arr2, rem, ans);

        /*
        //testing the arrays
        printf("\n");
        for(int i=4;i>=0;i--){
                printf("%d", arr1[i]);
        }
        printf("\n");
        for(int i=4;i>=0;i--){
                printf("%d", arr2[i]);
        }
        printf("\n");
        */

        //print the answer
        int len;
        int c;
        if(alen1>alen2) len=alen2;
        else len=alen1;
        for(c=len;c>=0;c--){
                if(ans[c]!=0) break;
        }
        while(c>=0){
                printf("%d", ans[c]);
                c--;
        }

        free(arr1);
        free(arr2);
        free(ans);
}

//binary Alg details
void binA(int* arr1, int* arr2, int* rem, int* ans){
       int len=257;
       int itemp;
       int i;

       while(1){
               /*
               //teasting
               printf("\n%d%c\t", 1, ':');
               for(i=len-1;i>=0;i--) printf("%d", arr1[i]);
               printf("\n%d%c\t", 2, ':');
               for(i=len-1;i>=0;i--) printf("%d", arr2[i]);
               printf("\n%c%c\t", 'a', ':');
               for(i=len-1;i>=0;i--) printf("%d", ans[i]);
               printf("\n");
               */

                if(arr2[0]%2==0 && arr1[0]%2==0){
                        //ansX2
                        for(i=0;i<len;i++){
                                rem[i]=rem[i]*2;
                        }
                        for(i=0;i<len;i++){
                                rem[i+1]=rem[i+1]+(rem[i]/10);
                                rem[i]=rem[i]%10;
                        }

                        //n/2
                        itemp=0;
                        for(i=len-1;i>=0;i--){
                                itemp=itemp*10+arr2[i];
                                arr2[i]=itemp/2;
                                itemp%=2;
                        }

                        //m/2
                        itemp=0;
                        for(i=len-1;i>=0;i--){
                                itemp=itemp*10+arr1[i];
                                arr1[i]=itemp/2;
                                itemp%=2;
                        }
                }
                else if(arr2[0]%2==0){
                        itemp=0;
                        for(i=len-1;i>=0;i--){
                                itemp=itemp*10+arr2[i];
                                arr2[i]=itemp/2;
                                itemp%=2;
                        }
                }
                else if(arr1[0]%2==0){
                        itemp=0;
                        for(i=len-1;i>=0;i--){
                                itemp=itemp*10+arr1[i];
                                arr1[i]=itemp/2;
                                itemp%=2;
                        }
                }


                comp(arr1, arr2);
                int count=0;
                for(i=0;i<len;i++){
                        arr1[i]=arr1[i]-arr2[i];
                        if(arr1[i]<0){
                                arr1[i+1]--;
                                arr1[i]+=10;
                        }
                        else if(arr1[i]==0) count++;
                }
                //check the content
                if(count==len) break;
        }

       //nXans
       for(i=0;i<len;i++){
               for(int j=0;j<len;j++){
                       ans[i+j]+=arr2[i]*rem[j];
                       //printf("%d %d %d\n", arr2[i], rem[j], ans[i+j]);
               }
        }
        for(i=0;i<len;i++){
                ans[i+1]+=ans[i]/10;
                ans[i]%=10;
        }
}

//comparison
void comp(int* arr1, int* arr2){
        for(int i=257;i>=0;i--){
                if(arr1[i]>arr2[i]) break;
                else if(arr2[i]>arr1[i]){
                        int temp;
                        for(int j=i;j>=0;j--){
                                temp=arr1[j];
                                arr1[j]=arr2[j];
                                arr2[j]=temp;
                        }
                        break;
                }
        }
}
