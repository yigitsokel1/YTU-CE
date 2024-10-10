#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

void colors(int n);
int** getColor(int ** matrix, int N);
int* rotateRight(int *colorRow, int N);
void printMatrix(int **matrix, int N);
int backTracking(int **matrix, int N, int currentRow, int selection);

int main(){
	int selection;		
	int N;				
	int i, j;
	int **colorsMat;
	char tmp[10];
	int result;
	
	
	do{
		printf("1.Normal Mode\n2.Detail Mode\n3.Exit\nSelection : ");
		scanf("%d",&selection);
		
		switch(selection){
			case 1:
				do{
					printf("Enter the number of colors(between 3 and 8) : ");		//3 ve 8 aral���nda matris boyutu belirleniyor
					scanf("%d", &N);
					if(N<3 || N>8)
						printf("Enter a value between 3 and 8!\n");
				}while(N<3 || N>8);
				colorsMat = (int**)malloc(sizeof(int*)*N);							//Matris i�in yer a�ma
				for(i=0;i<N;i++)
					colorsMat[i] = (int*)malloc(sizeof(int)*N);
				colors(N);															//Se�ilebilecek renkleri ekrana yazd�rma
				colorsMat = getColor(colorsMat, N);									//Renkleri kullan�c�dan alma
				printMatrix(colorsMat,N);
				result  = backTracking(colorsMat, N, 0, selection);					//Recursive fonksiyon ile d�zeni olu�turma
				if(result == -1)
					printf("Not possibility! Not created! \n");						//D�zenin bulunmama durumunda uyar�
				else{
					printf("Result\n");												//Bulundu�u durumda ekrana yazd�r�yor
					printMatrix(colorsMat,N);
				}
				free(colorsMat);
				break;
			case 2:
				do{
					printf("Enter the number of colors(between 3 and 8) : ");
					scanf("%d", &N);
					if(N<3 || N>8)
						printf("Enter a value between 3 and 8!\n");
				}while(N<3 || N>8);
				colorsMat = (int**)malloc(sizeof(int*)*N);
				for(i=0;i<N;i++)
					colorsMat[i] = (int*)malloc(sizeof(int)*N);
				colors(N);
				colorsMat = getColor(colorsMat, N);
				printMatrix(colorsMat,N);
				result  = backTracking(colorsMat, N, 0, selection);
				if(result == -1)
					printf("Not possibility! Not created! \n");
				else{
					printf("Result\n");
					printMatrix(colorsMat,N);
				}
				free(colorsMat);
				break;
			case 3:																	//Program sonland�rma
				printf("Program terminated..\n");
				break;
			default:
				printf("Wrong value! Try Again\n");									//Yanl�� se�imde uyar� mesaj�
		}
	}while(selection != 3);
	
	
	
}


int backTracking(int **matrix, int N, int currentRow, int selection){
	int i=0,j;
	int countRotate=0;																		//Sat�r�n d�nd�r�lme say�s�n� tutuyor
	int result;
	int flag = 0;
	
	if(currentRow == N){																	//E�er b�t�n sat�rlar d�zene uyumlu ise 1 ile d�n�� yap�l�yor
		return 1;
	}else{
		if(currentRow == 0){																//�lk sat�r olma durumu kontrol ediliyor
			while(countRotate != N){														//B�t�n se�enekler denenmedi�i s�rece tekrar ediyor
				result = backTracking(matrix, N, currentRow+1,selection);					//Bir sonraki sat�r i�in fonksiyon �a��r�l�yor
				if(result == -1){															//E�er d�zen sa�lanamad��� geri d�n���n� al�rsa
					matrix[currentRow] = rotateRight(matrix[currentRow], N);				//�lk sat�r d�nd�r�l�yor
					if(selection == 2){														//Detail modda �al��t�r�ld���nda her ad�m ekrana yazd�r�l�yor
						printf("Step\n");							
						printMatrix(matrix,N);
					}
					countRotate++;															//D�nd�rme say�s� artt�r�l�yor
				}else if(result == 1)
					return 1;																//D�zen sa�land�ysa 1 ile d�n�yor
				if(countRotate == N){
					return -1;																//Sa�lanmad�ysa -1 ile d�n�yor
				}
			}
		}else{
			while(i<=N && countRotate != N){												//B�t�n d�nd�rmeler tamamlanmad��� s�rece devam ediyor
				if(flag){																	//E�er �st�ndeki sat�rlarla ayn� s�tunda ayn� renk varsa �al��an ko�ul
					matrix[currentRow] = rotateRight(matrix[currentRow], N);				//Sat�r dairesel olacak �ekilde sa�a kayd�r�l�yor
					if(selection == 2){
						printf("Step\n");
						printMatrix(matrix,N);
					}
					countRotate++;
					i=0;																	//D�nd�rme oldu�u i�in bir sonraki d�zenin de en ba�tan kontrol edilmesi gerekiyor. S�tun de�i�kenini s�f�rl�yor
				}
				flag = 0;																	//D�nd�rme olup olmayaca��n� tutan de�i�ken 
				j=0;																		//Her seferinde ilk sat�rdan kontrol etsin diye s�f�rlan�yor
				while(j<currentRow &&  !flag){												//Ayn� s�tunda ayn� renk bulunmas�n� kontrol ediyor. Varsa flag de�erini 1 yap�yor
					if(matrix[currentRow][i] == matrix[j][i]){
						flag = 1;
					}
					j++;																	//Sat�r de�i�kenini artt�rma
				}
				i++;																		//S�tun de�i�kenini artt�rma
				if(countRotate == N)														//B�t�n ihtimaller denenip olmam��sa -1 ile d�n�� yap�yor
					return -1;	
				else if(flag == 0 && i == N){												//E�er o sat�r�n d�zeni sa�lan�yorsa
					result = backTracking(matrix, N, currentRow+1, selection);				//Bir sonraki sat�r i�in fonksiyon �a��r�l�yor
					i=0;
					if(result == 1)															//Sonraki sat�rlar da d�zeni sa�lam�� ise 1 ile d�n�� yap�yor
						return 1;
					else{
						flag = 1;															//E�er sonraki sat�rlarda d�zen olmam�� ise bu sat�r�n di�er ihtimallerini denemek i�in flag de�i�keninini 1 yap�yor
					}
						
				}
					
			}
			
		}	
	}
}


int* rotateRight(int *colorRow, int N){			//Matriximizde g�nderilen sat�r�n sa�a kayd�r�lmas� i�in kullan�l�yor
	
	int i;
	int tmpRow[N];								//De�i�ken ile g�nderilen sat�rdaki renkler tutuluyor
	
	for(i=0;i<N;i++){
		tmpRow[i] = colorRow[i];			
	}
	for(i=0;i<N;i++){
		colorRow[(i+1)%N] = tmpRow[i];			//Dairesel bir �ekilde dizinin yeni sat�r� ayarlan�yor ve geri g�nderiliyor
	}
	return colorRow;
}


void colors(int n){								//Renk se�eneklerini ekrana yazd�r�yor
	
	printf("Red(r)\nOrange(o)\nBlue(b)\n");
	if(n>3)
		printf("Green(g)\n");
	if(n>4)
		printf("Pink(p)\n");
	if(n>5)
		printf("Brown(br)\n");
	if(n>6)
		printf("Yellow(y)\n");
	if(n>7)
		printf("White(w)\n");
	
}


void printMatrix(int **matrix, int N){		//Matrixlerde bulunan integer de�erlere g�re ekrana yazd�r�yor
	
	int i, j;
	
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			if(matrix[i][j] == 1)
				printf("r\t");
			else if(matrix[i][j] == 2)
				printf("o\t");
			else if(matrix[i][j] == 3)
				printf("b\t");
			else if(matrix[i][j] == 4)
				printf("g\t");
			else if(matrix[i][j] == 5)
				printf("p\t");
			else if(matrix[i][j] == 6)
				printf("br\t");
			else if(matrix[i][j] == 7)
				printf("y\t");
			else if(matrix[i][j] == 8)
				printf("w\t");
		}
		printf("\n");
	}
	
}


int** getColor(int **matrix, int N){				//Matrixin her bir eleman� i�in kullan�c�dan inputu al�yor. Yanl�� bir de�er ya da se�enekler aras�nda bir renk girildi�inde hata veriyor.
													//String ya da char olarak girilen renkleri integer olarak dizide tutuyor
	int i, j;
	int isWriteColor[N];
	char tmp[10];
	
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			do{
				printf("M[%d][%d] : ",i,j);				
				scanf("%s", &tmp);
				if(strcmp(tmp, "r") == 0)
					matrix[i][j] = 1;
				else if(strcmp(tmp, "o") == 0)
					matrix[i][j] = 2;
				else if(strcmp(tmp, "b") == 0)
					matrix[i][j] = 3;
				else if(strcmp(tmp, "g") == 0 && N > 3)
					matrix[i][j] = 4;
				else if(strcmp(tmp, "p") == 0 && N > 4)
					matrix[i][j] = 5;
				else if(strcmp(tmp, "br") == 0 && N > 5)
					matrix[i][j] = 6;
				else if(strcmp(tmp, "y") == 0 && N > 6)
					matrix[i][j] = 7;
				else if(strcmp(tmp, "w") == 0 && N > 7)
					matrix[i][j] = 8;
				else
					printf("Wrong color! Try again!\n");
			}while(!(strcmp(tmp, "r") == 0) && !(strcmp(tmp, "o") == 0) && !(strcmp(tmp, "b") == 0) && !(strcmp(tmp, "g") == 0 && N > 3) && !(strcmp(tmp, "p") == 0 && N > 4) && !(strcmp(tmp, "br") == 0 && N > 5) && !(strcmp(tmp, "y") == 0 && N > 6) && !(strcmp(tmp, "w") == 0 && N > 7));	
		}
	}
	return matrix;	
	
}
