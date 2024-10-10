#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<conio.h>


char** readMaze(char* fileName, int *r, int *c, int *startRow, int *startCol){
	
	FILE* fp = fopen(fileName, "r");
	char** maze;
	int i, j;
	int row, col;
	
	if(fp == NULL){
		printf("Dosya mevcut degil!!!\n");
	}
	fscanf(fp,"%d,%d",&row,&col);
	maze = (char**)malloc(row * sizeof(char*));
	for(i=0;i<row;i++){
		maze[i] = (char*)malloc(col * sizeof(char));
	}
	for(i=0;i<row;i++){
		for(j=0;j<col;j++){
			fscanf(fp,"%c",&maze[i][j]);
			if(maze[i][j] == '\n')
				fscanf(fp,"%c",&maze[i][j]);
			if(maze[i][j] == 'b'){
				*startRow = i;
				*startCol = j;
			}
		}
	}
	
	*r = row;
	*c = col;
	fclose(fp);
	return maze;
}
 
 void sleep(){
 	int i, j, k;
 	for(i=0;i<2000000;i++){
 		for(j=0; j<25; j++){
 			k=0;
		 }
	 }
 }

void printMaze(char** matrix, int **visited, int row, int col, int point){
	int i,j;
	for(i=0; i<row; i++){
		for(j=0; j<col; j++){
			if(visited[i][j]==1){
				printf("%c", -78);				
			}else{
				printf("%c ",matrix[i][j]);
			}
		}
		printf("\n");
	}
	printf("Total Point : %d", point);	
	
	//getch();
	sleep();
	system("cls");
}

 int** configureVisited(char** maze, int row, int col){
 	
 	int **visited;
 	int i,j;
 	
	visited = (int**) malloc(row*sizeof(int*));
	for(i=0;i<row;i++){
		visited[i] = (int*)malloc(col*sizeof(int));
	}
	
	for(i=0; i<row; i++){
		for(j=0; j<col; j++){
			if((maze[i][j] == '+' || maze[i][j] == '-') || maze[i][j] == '|')
				visited[i][j] = 2; //2'ler duvar
			else if(maze[i][j] == 'O')
				visited[i][j] = 3;//3 elma
			else if(maze[i][j] == 'c')
				visited[i][j] = 4;//4 bitiþ 
			else
				visited[i][j] = 0;//0'lar boþ
		}
	}
 	
 	return visited;
 }

 
 int isImpasse(int** visited, int tempRow, int tempCol){
 	
 	int count =0;
 	
 	if(visited[tempRow+1][tempCol] == 2){
 		count++;
	 }
	if(visited[tempRow][tempCol+1] == 2){
 		count++;
	 }
	if(visited[tempRow-1][tempCol] == 2){
 		count++;
	 }
	if(visited[tempRow][tempCol-1] == 2){
 		count++;
	 }
	 return count;
 }
 
 
 int dfSearch(char** maze, int** visited, int row, int col,int tempRow,int tempCol, int* point){
 	
 	int control;
 	int *tempElement = &visited[tempRow][tempCol];
 	
 	if(*tempElement == 4)
 		return 1;
 	if(*tempElement == 3){
 		*point += 10;
 		printf("You find apple! You earn 10 points!\n");
	 }
	
	if(*tempElement == 0 || *tempElement == 3){
		*tempElement = 1;
		printMaze(maze,visited,row, col, *point);
		
	
		maze[tempRow][tempCol] = ' ';
		visited[tempRow][tempCol] = 1;//1 gezdigin yerler
		if(dfSearch(maze,visited,row,col,tempRow+1,tempCol,point)){
			*tempElement = 1;
			return 1;
		}	
		else if(dfSearch(maze,visited,row,col,tempRow,tempCol-1,point)){
			*tempElement= 1;
			return 1;
		}
		else if(dfSearch(maze,visited,row,col,tempRow-1,tempCol,point)){
			*tempElement = 1;
			return 1;
		}
		else if(dfSearch(maze,visited,row,col,tempRow,tempCol+1,point)){
			*tempElement = 1;
		 	return 1;
		}
	
		
		
		control = isImpasse(visited,tempRow,tempCol);
		visited[tempRow][tempCol] = 0;//Yoksa visitedý boþ yer yapýyor tekrardan
		if(control==3){
			*point -=5;
			printf("\nYou hit the wall! You lost 5 points!\n");
		}
	
		printMaze(maze,visited,row, col, *point);
		
	}
 	
	 
 	return 0;
 	
 	
 }
 
 char** insertApple(char** maze, int row, int col){
 	
 	int i, j;
 	int temp, count = 0;;
 	
 	srand(time(NULL));
 	temp = row*col/100;
 	
 	while(count < temp){
 		i = rand()%row;
 		j = rand()%col;
 		if(maze[i][j] == ' '){
 			maze[i][j] = 'O';
 			count++;
		 }
	 }
	 return maze;
 
 }

int main(){
	
	int row, col, startRow, startCol;
	char **maze;
	int **visited;
	int point=0;
	int control;
	
	maze = readMaze("maze2.txt",&row,&col,&startRow,&startCol);
	maze = insertApple(maze,row,col);
	visited = configureVisited(maze,row,col);
	control = dfSearch(maze,visited,row,col, startRow,startCol,&point);
	if(control){
		printf("Congrulations!! Point : %d",point);
	}else{
		printf("You Lose!!!");
	}
	return 0;
}



