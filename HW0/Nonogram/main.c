#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool recur(int **board, int** token, int N, int M, int row, int col);
bool check_row(int **board, int** token, int row, int M);
bool check_col(int **board, int** token, int col, int N);
bool check_val(int **board, int row, int col);
bool check_row_temp(int **board, int** token, int row, int M);
bool check_col_temp(int **board, int** token, int col, int N);

int main(){
	int i, j;

	//input the frame
	int N, M; //N = the # of row; M = the # of col
	scanf("%d %d", &N, &M);

	//board
	int **board=calloc(N, sizeof(int*));
	for(i=0;i<N;i++) board[i]=calloc(M, sizeof(int));

	//input row and col
	int lar;
	if(N>M) lar=N;
	else lar=M;
	int **token=calloc(N+M, sizeof(int*));
	/*
	for(i=0;i<N+M;i++){
		token[i]=calloc(lar, sizeof(int*));

		c=0;
		char str[lar];
		setbuf(stdin, NULL);

		scanf("%[^\n]", str);
		//printf("%s\n", str);
		
		char *p=strtok(str, " ");

		while(p!=NULL){
			//printf("%s\n", p);
			token[i][c]=atoi(p);
			p=strtok(NULL, " ");
			//token[i][c]=atoi(p);
			c++;
		}
	}*/

	//revised ver. input row and col
	for(i=0;i<N+M;i++){
		token[i]=calloc(lar, sizeof(int*));
		scanf("%d", &token[i][0]);
		for(j=1;j<=token[i][0];j++) scanf("%d", &token[i][j]);
	}
	
	/*
	//testing
	//printf("%d", c);
	for(i=0;i<N+M;i++){
		for(j=0;j<=token[i][0];j++) printf("%d", token[i][j]);
		printf("\n");
	}
	*/
	///////////////////////////////////////////////////////////
	
	//solver
	if(recur(board, token, N, M, 0,0)){
	//print
		for(i=0;i<N;i++){
			for(j=0;j<M;j++){
				
				if(board[i][j]==1) printf("%c", 'o');
				else printf("%c", '_');
				
				//printf("%d", board[i][j]);
			}
			printf("\n");
			//else continue;
		}
	}
	else printf("%s", "sorry");
	
	for(i=0;i<N;i++){
		free(board[i]);
		free(token[i]);
	}
	free(board);
	for(i=N;i<M;i++) free(token[i]);
	free(token);
}

//recursive
bool recur(int **board, int** token, int N, int M, int row, int col){
	//int row_o=row;
	//int col_o=col;
		
	//check the whole board
	if(check_val(board, N, M)){
		/*
		//testing
		for(int i=0;i<N;i++){
			for(int j=0;j<M;j++) printf("%d", board[i][j]);
			printf("\n");
		}
		printf("\n");
		*/

		for(int i=0;i<N;i++){
			for(int j=0;j<M;j++){
				if(!check_row(board, token, i, M)) return false;
				if(!check_col(board, token, j, N)) return false;
			}
		}
		return true;
	}
	else{
		/*
		//testing
		for(int i=0;i<N;i++){
			for(int j=0;j<M;j++) printf("%d", board[i][j]);
			printf("\n");
		}
		printf("\n");
		*/
		if(!check_row_temp(board, token, row, M)) return false;
		if(!check_col_temp(board, token, col, N)) return false;

		//paint black
		board[row][col]=1;
		if(row+1==N && col+1==M){
			if(recur(board, token, N, M, row, col)) return true;
		}
		else if(row+1<N){
			if(recur(board, token, N, M, row+1, col)) return true;
		}
		else if(col+1<M){
			if(recur(board, token, N, M, 0, col+1)) return true;
		}
		
		//paint white
		board[row][col]=-1;
		if(row+1==N && col+1==M){
			if(recur(board, token, N, M, row, col)) return true;
		}
		else if(row+1<N){
			if(recur(board, token, N, M, row+1, col)) return true;
		}
		else if(col+1<M){
			if(recur(board, token, N, M, 0, col+1)) return true;
		}
		

		/*
		//testing
		for(int i=0;i<N;i++){
                        for(int j=0;j<M;j++) printf("%d", board[i][j]);
                        printf("\n");
                }
                printf("\n");
		*/

		//empty
		//row=row_o;
		//col=col_o;
		board[row][col]=0;
		return false;
	}
}

//check row-th row
bool check_row(int **board, int** token, int row, int M){
	//printf("%c", 'r');
	int bla=0; //# of black cell
	int sum=0; //clue
	int count=0; //count # of black cell
	int temp=1; //which clue it is
	for(int i=0;i<M;i++){
		if(board[row][i]==1){
			count++;
			bla++;
		}
		else if(board[row][i]==-1 && count!=0) return false;

		if(temp-1==token[row][0]){
			if(bla>sum) return false;
			else continue;
		}
		else if(token[row][temp]==count){
			sum+=count;
			temp++;
			count=0;
			if(i!=M-1 && board[row][i+1]==1) return false;
		}
		else if(token[row][temp]>count) continue;
		//else return false;
	}
	//printf("%c", 'r');
	if(temp-1<token[row][0]) return false;
	else return true;
}

//check col-th column/(N+col)-th token
bool check_col(int **board, int** token, int col, int N){
	//printf("%c", 'l');
        int bla=0; //# of black cell
        int sum=0; //clue
        int count=0; //count # of black cell
        int temp=1; //which clue it is
        for(int i=0;i<N;i++){
                if(board[i][col]==1){
                        count++;
                        bla++;
                }
		else if(board[i][col]==-1 && count!=0) return false;

                if(temp-1==token[col+N][0]){
                        if(bla>sum) return false;
                        else continue;
                }
                else if(token[col+N][temp]==count){
                        sum+=count;
                        temp++;
                        count=0;
                        if(i!=N-1 && board[i+1][col]==1) return false;
                }
                else if(token[col+N][temp]>count) continue;
                // else return false;
        }
	//printf("%c", 'l');
	if(temp-1<token[col+N][0]) return false;
	else return true;
}

//check the validity of the board (whether it is completely filled)
bool check_val(int **board, int N, int M){
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			if(board[i][j]==0) return false;
			else continue;
		}
	}
	return true;
}

//check row-th row so far
bool check_row_temp(int **board, int** token, int row, int M){
        //printf("%c", 'r');
        int bla=0; //# of black cell
        int sum=0; //clue
        int count=0; //count # of black cell
        int temp=1; //which clue it is
        for(int i=0;i<M;i++){
                if(board[row][i]==1){
                        count++;
                        bla++;
                }
                else if(board[row][i]==-1 && count!=0) return false;

                if(temp-1==token[row][0]){
                        if(bla>sum) return false;
                        else continue;
                }
                else if(token[row][temp]==count){
                        sum+=count;
                        temp++;
                        count=0;
                        if(i!=M-1 && board[row][i+1]==1) return false;
                }
                else if(token[row][temp]>count) continue;
                //else return false;
        }
        //printf("%c", 'r');
        return true;
}

//check col-th column/(N+col)-th token do far
bool check_col_temp(int **board, int** token, int col, int N){
        //printf("%c", 'l');
        int bla=0; //# of black cell
        int sum=0; //clue
        int count=0; //count # of black cell
        int temp=1; //which clue it is
        for(int i=0;i<N;i++){
                if(board[i][col]==1){
                        count++;
                        bla++;
                }
                else if(board[i][col]==-1 && count!=0) return false;

                if(temp-1==token[col+N][0]){
                        if(bla>sum) return false;
                        else continue;
                }
                else if(token[col+N][temp]==count){
                        sum+=count;
                        temp++;
                        count=0;
                        if(i!=N-1 && board[i+1][col]==1) return false;
                }
                else if(token[col+N][temp]>count) continue;
                // else return false;
        }
        //printf("%c", 'l');
        return true;
}
