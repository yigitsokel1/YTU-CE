#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#define MAX 1000

int** newConnect(int **matrix, int row, int col, int cost, int size, int capacity);
int** sparseOrderMatrix(int **matrix, int size);

int main(){
	int numNode;
	int control = 0;
	int i, j, tmp = 1;
	int selection = 0;
	int dest, src, length;
	printf("Dugum sayisini giriniz : " );
	scanf("%d", &numNode);
	int nodeList[numNode];
	int **matrix;
	int **regMatrix;
	matrix = (int**)malloc(numNode*sizeof(int*));
	for(i=0;i<numNode;i++){
		matrix[i] = (int*)malloc(numNode*sizeof(int));
	}
	
	for(i=0;i<numNode;i++){
		for(j=0;j<numNode;j++){
			matrix[i][j]=0;
		}
	}
	
	for(i = 0; i< numNode; i++)
		nodeList[i] = 0;
	i=0;
	printf("MST'ye gore kucukten buyuge gore giriniz!\n");
	while(control != numNode){
		control = 0;
		printf("Hangi dugumler arasinda oldugunu ve uzakligi giriniz : ");
		scanf("%d %d %d", &dest, &src, &length);
		matrix[dest][src] = length;
		matrix[src][dest] = length;
		if(nodeList[dest] == 0 && nodeList[src] == 0){
			nodeList[dest] = tmp;
			nodeList[src] = tmp++;
		}
		else if((nodeList[dest] == 0) || (nodeList[src] == 0)){
			if(nodeList[dest] == 0)
				nodeList[dest] = nodeList[src];
			else
				nodeList[src] = nodeList[dest];
		}
		else if(nodeList[dest] != nodeList[src]){
			for(j = 0; j< numNode; j++){
				if((nodeList[j] != nodeList[src]) && (nodeList[j] != 0))
					nodeList[j] = nodeList[src];
			}
		}
	
		for(j=0;j<numNode;j++)
			printf("%d.Node\t",j);
		printf("\n");
		for(j=0;j<numNode;j++){
			printf("%d\t", nodeList[j]);
			if(nodeList[0] == nodeList[j])
				control++;
		}
		printf("\n");
		i++;
	}
	
	regMatrix = (int**)malloc(i*sizeof(int*));
	for(j=0;j<i;j++)
		regMatrix[i] = (int*)malloc(3*sizeof(int));
	regMatrix = sparseOrderMatrix(matrix, numNode);
	
	while(selection != 3){
		printf("Menu\n1.Yeni baglanti ekle\n2.MST'yi goruntule\n3.Exit\nSelection : ");
		scanf("%d", &selection);
		switch(selection){
			case 1:
				printf("Hangi dugumler arasinda oldugunu ve uzakligi giriniz : ");
				scanf("%d %d %d", &dest, &src, &length);
				matrix = newConnect(matrix,dest,src,length, numNode, i);
				break;
			case 2:
				printf("\nMST\n");
				regMatrix = sparseOrderMatrix(matrix, numNode);
				for(j=0;j<i;j++){
					printf("%d-%d -> %d\n", regMatrix[j][0],regMatrix[j][1],regMatrix[j][2]);
				}
				break;
			case 3:
				printf("Program bitti!!\n");
				break;
			default:
				printf("Yanlis secim! Tekrar deneyiniz!!\n");
				break;
		}		
		
	}

	
}


int** sparseOrderMatrix(int **matrix, int size){
	
	int **newMatrix;
	int i, j, tmp=0;
	int temp;

	for(i=0;i<size;i++){
		for(j=i;j<size;j++){
			if(matrix[i][j] != 0)
				tmp++;
		}
	}
	newMatrix = (int**)malloc(tmp*sizeof(int*));
	for(i=0;i<tmp;i++){
		newMatrix[i] = (int*)malloc(3*sizeof(int));
	}
	
	tmp = 0;
	for(i=0;i<size;i++){
		for(j=i;j<size;j++){
			if(matrix[i][j] != 0){
				newMatrix[tmp][0] = i;
				newMatrix[tmp][1] = j;
				newMatrix[tmp][2] = matrix[i][j];
				tmp++;
			}
		}
	}

	for(i=0;i<tmp-1;i++){
		for(j=0;j<tmp-i-1;j++){
			if(newMatrix[j][2] > newMatrix[j+1][2]){
				temp = newMatrix[j][0];
				newMatrix[j][0] = newMatrix[j+1][0];
				newMatrix[j+1][0] = temp;
				temp = newMatrix[j][1];
				newMatrix[j][1] = newMatrix[j+1][1];
				newMatrix[j+1][1] = temp;
				temp = newMatrix[j][2];
				newMatrix[j][2] = newMatrix[j+1][2];
				newMatrix[j+1][2] = temp;
			}
		}
	}
	
	return newMatrix;
	
}

int** newConnect(int **matrix,int row, int col, int cost, int size, int capacity){
	
	int i, j;
	int max=0;
	int min;
	int **newMatrix;
	int tmp = 1;
	int control = 0;
	int nodeList[size];
	
	for(i=0;i<size;i++)
		nodeList[i] = 0;

	newMatrix = (int**)malloc((capacity+1)*sizeof(int*));
	for(i=0;i<capacity+1;i++){
		newMatrix[i] = (int*)malloc(3*sizeof(int));
	}
	
	
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			if(matrix[i][j] > max)
				max = matrix[i][j];
		}
	}
	min = max;
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			if(matrix[i][j] < min && matrix[i][j] > 0)
				min = matrix[i][j];
		}
	}
	
	
	if(matrix[row][col] != 0){
		if(cost >= matrix[row][col])
			return matrix;
		else{
			matrix[row][col] = cost;
			matrix[col][row] = cost;
			return matrix;
		}	
	}
	else{
		if(cost >= max)
			return matrix;
		else{
			matrix[row][col] = cost;
			matrix[col][row] = cost;
			newMatrix = sparseOrderMatrix(matrix,size);
			i = 0;
			while(control != size){
				control = 0;
				if(nodeList[newMatrix[i][0]] == 0 && nodeList[newMatrix[i][1]] == 0){
					nodeList[newMatrix[i][0]] = tmp;
					nodeList[newMatrix[i][1]] = tmp++;
				}
				else if(nodeList[newMatrix[i][0]] == 0 || nodeList[newMatrix[i][1]] == 0){
					if(nodeList[newMatrix[i][0]] == 0)
						nodeList[newMatrix[i][0]] = nodeList[newMatrix[i][1]];
					else
						nodeList[newMatrix[i][1]] = nodeList[newMatrix[i][0]];
				}
				else if(nodeList[newMatrix[i][0]] != nodeList[newMatrix[i][1]]){
					for(j = 0; j< size; j++){
						if((nodeList[j] != nodeList[newMatrix[i][1]]) && (nodeList[j] != 0))
							nodeList[j] = nodeList[newMatrix[i][1]];
					}
				}
				else if(nodeList[newMatrix[i][0]] == nodeList[newMatrix[i][1]]){
					newMatrix[i][0] = 0;
					newMatrix[i][1] = 0;
					newMatrix[i][2] = 0;
					
				}
				i++;
				for(j=0;j<size;j++){
					if(nodeList[0] == nodeList[j])
						control++;
				}
			}
			for(i=0;i<size;i++){
				for(j=0;j<size;j++)
					matrix[i][j] = 0;
			}
			
			for(j=0;j<capacity+1;j++){
				if(newMatrix[j][2] != 0){
					matrix[newMatrix[j][0]][newMatrix[j][1]] = newMatrix[j][2];
					matrix[newMatrix[j][1]][newMatrix[j][0]] = newMatrix[j][2];
				}
			}
			return matrix;
		}
	}
	
}
