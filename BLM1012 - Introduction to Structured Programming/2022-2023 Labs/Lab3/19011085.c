#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>

int** getValueOfMatrix(int n, int **matrix);

int main(){
	
	int n;
	int **rooms;
	int i,j;
	int control;
	int totalPath;
	
	printf("Enter the matrix size : ");
	scanf("%d", &n);
	
	rooms = getValueOfMatrix(n, rooms);
	
	printf("Matrix\n");
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			printf("%d  ", rooms[i][j]);
		}
		printf("\n");
	}
	
	
	control = getPath(n, rooms, 0, 0, 0);
	printf("Total Path = %d", control);
	
	return 0;
	
}

int getPath(int n, int **matrix, int row, int col, int sum){
	
	int control;
	
	if(matrix[row][col] == 0)
		return sum;
	else if(row == n-1 && col == n-1){
		printf("(%d,%d)\n",n-1,n-1);
		sum++;
		return sum;
	}else{
		if(row+1<n){
			if(matrix[row+1][col] != 0)
				printf("(%d, %d)",row, col);
			sum = getPath(n,matrix,row+1,col, sum);
		}
		if(col+1<n){
			if(matrix[row][col+1] != 0)
				printf("(%d, %d)",row, col);
			sum = getPath(n, matrix, row, col+1, sum);
		}
		
	}
	return sum;
	
}



int** getValueOfMatrix(int n, int **matrix){
	
	int i, j;
	
	matrix = (int**)malloc(n*sizeof(int*));
	for(i=0; i<n; i++)
		matrix[i] = (int*)malloc(n*sizeof(int));
	
	
	for(i=0;i<n;i++){
		for(j=0; j<n; j++){
			if((i==0 && j==0) ||(i==n-1 && j==n-1))
				matrix[i][j] = 1;
			else{
				do{
					printf("Matrix[%d][%d] = ", i, j);
					scanf("%d", &matrix[i][j]);
					
					if(!(matrix[i][j] == 1 || matrix[i][j]==0))
						printf("Please enter 0 or 1!!\n");
				}while(!(matrix[i][j] == 1 || matrix[i][j]==0));
				
			}
		}
	}
	
	return matrix;
		
}
