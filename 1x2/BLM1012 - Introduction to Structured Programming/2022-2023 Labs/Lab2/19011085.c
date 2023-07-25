#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>


int main(){
	
	int n;
	int count=0;
	int aysePoint, betulPoint, point;
	int i, j;
	char selection;
	
	
	do{
		aysePoint = 0;
		betulPoint = 0;
		count = 0;
		srand(time(NULL));
		do{
			printf("Enter the size of the matrix : ");
			scanf("%d", &n);
			if(n<4)
				printf("Please enter a value greater than 3!!\n");
		}while(n<3);
		
		int board[n][n];
		int tmp[n][n];	
		
		for(i=0;i<n;i++){
			for(j=0;j<n;j++)
				board[i][j] = 1 + rand() % (n * n);
		}
		
		printf("Matrix\n");
		for(i=0;i<n;i++){
			for(j=0;j<n;j++)
				printf("%d\t", board[i][j]);
			printf("\n");
		}
		
		while(count<6){
			printf("\n90° rotated\n");
			for(i=0;i<n;i++){
				for(j=0;j<n;j++){
					tmp[j][n-i-1] = board[i][j];
				}
			}
			for(i=0;i<n;i++){
				for(j=0;j<n;j++){
					board[i][j] = tmp[i][j];
					printf("%d\t", board[i][j]);
				}
				printf("\n");
			}
			count++;
			point = 0;
			for(i=0;i<n;i++)
				point += board[n-1][i];
			if(count % 2 != 0)
				betulPoint += point;
			else
				aysePoint += point;
			printf("Betul:%d\tAyse:%d\n",betulPoint,aysePoint);
		}
		
		if(aysePoint > betulPoint)
			printf("\nAyse Win!!\n\n\n");
		else if(aysePoint == betulPoint)
			printf("\nDraw!!\n\n\n");
		else
			printf("\nBetul Win!!\n\n\n");
		
		printf("\nPress 'e' or 'E' to restart the program : ");
		scanf(" %c", &selection);
		
	}while(selection == 'e' || selection == 'E');
	
	printf("\nProgram terminated...");
	return 0;
	
}

