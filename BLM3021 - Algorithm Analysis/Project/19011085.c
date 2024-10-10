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
					printf("Enter the number of colors(between 3 and 8) : ");		//3 ve 8 aralýðýnda matris boyutu belirleniyor
					scanf("%d", &N);
					if(N<3 || N>8)
						printf("Enter a value between 3 and 8!\n");
				}while(N<3 || N>8);
				colorsMat = (int**)malloc(sizeof(int*)*N);							//Matris için yer açma
				for(i=0;i<N;i++)
					colorsMat[i] = (int*)malloc(sizeof(int)*N);
				colors(N);															//Seçilebilecek renkleri ekrana yazdýrma
				colorsMat = getColor(colorsMat, N);									//Renkleri kullanýcýdan alma
				printMatrix(colorsMat,N);
				result  = backTracking(colorsMat, N, 0, selection);					//Recursive fonksiyon ile düzeni oluþturma
				if(result == -1)
					printf("Not possibility! Not created! \n");						//Düzenin bulunmama durumunda uyarý
				else{
					printf("Result\n");												//Bulunduðu durumda ekrana yazdýrýyor
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
			case 3:																	//Program sonlandýrma
				printf("Program terminated..\n");
				break;
			default:
				printf("Wrong value! Try Again\n");									//Yanlýþ seçimde uyarý mesajý
		}
	}while(selection != 3);
	
	
	
}


int backTracking(int **matrix, int N, int currentRow, int selection){
	int i=0,j;
	int countRotate=0;																		//Satýrýn döndürülme sayýsýný tutuyor
	int result;
	int flag = 0;
	
	if(currentRow == N){																	//Eðer bütün satýrlar düzene uyumlu ise 1 ile dönüþ yapýlýyor
		return 1;
	}else{
		if(currentRow == 0){																//Ýlk satýr olma durumu kontrol ediliyor
			while(countRotate != N){														//Bütün seçenekler denenmediði sürece tekrar ediyor
				result = backTracking(matrix, N, currentRow+1,selection);					//Bir sonraki satýr için fonksiyon çaðýrýlýyor
				if(result == -1){															//Eðer düzen saðlanamadýðý geri dönüþünü alýrsa
					matrix[currentRow] = rotateRight(matrix[currentRow], N);				//Ýlk satýr döndürülüyor
					if(selection == 2){														//Detail modda çalýþtýrýldýðýnda her adým ekrana yazdýrýlýyor
						printf("Step\n");							
						printMatrix(matrix,N);
					}
					countRotate++;															//Döndürme sayýsý arttýrýlýyor
				}else if(result == 1)
					return 1;																//Düzen saðlandýysa 1 ile dönüyor
				if(countRotate == N){
					return -1;																//Saðlanmadýysa -1 ile dönüyor
				}
			}
		}else{
			while(i<=N && countRotate != N){												//Bütün döndürmeler tamamlanmadýðý sürece devam ediyor
				if(flag){																	//Eðer üstündeki satýrlarla ayný sütunda ayný renk varsa çalýþan koþul
					matrix[currentRow] = rotateRight(matrix[currentRow], N);				//Satýr dairesel olacak þekilde saða kaydýrýlýyor
					if(selection == 2){
						printf("Step\n");
						printMatrix(matrix,N);
					}
					countRotate++;
					i=0;																	//Döndürme olduðu için bir sonraki düzenin de en baþtan kontrol edilmesi gerekiyor. Sütun deðiþkenini sýfýrlýyor
				}
				flag = 0;																	//Döndürme olup olmayacaðýný tutan deðiþken 
				j=0;																		//Her seferinde ilk satýrdan kontrol etsin diye sýfýrlanýyor
				while(j<currentRow &&  !flag){												//Ayný sütunda ayný renk bulunmasýný kontrol ediyor. Varsa flag deðerini 1 yapýyor
					if(matrix[currentRow][i] == matrix[j][i]){
						flag = 1;
					}
					j++;																	//Satýr deðiþkenini arttýrma
				}
				i++;																		//Sütun deðiþkenini arttýrma
				if(countRotate == N)														//Bütün ihtimaller denenip olmamýþsa -1 ile dönüþ yapýyor
					return -1;	
				else if(flag == 0 && i == N){												//Eðer o satýrýn düzeni saðlanýyorsa
					result = backTracking(matrix, N, currentRow+1, selection);				//Bir sonraki satýr için fonksiyon çaðýrýlýyor
					i=0;
					if(result == 1)															//Sonraki satýrlar da düzeni saðlamýþ ise 1 ile dönüþ yapýyor
						return 1;
					else{
						flag = 1;															//Eðer sonraki satýrlarda düzen olmamýþ ise bu satýrýn diðer ihtimallerini denemek için flag deðiþkeninini 1 yapýyor
					}
						
				}
					
			}
			
		}	
	}
}


int* rotateRight(int *colorRow, int N){			//Matriximizde gönderilen satýrýn saða kaydýrýlmasý için kullanýlýyor
	
	int i;
	int tmpRow[N];								//Deðiþken ile gönderilen satýrdaki renkler tutuluyor
	
	for(i=0;i<N;i++){
		tmpRow[i] = colorRow[i];			
	}
	for(i=0;i<N;i++){
		colorRow[(i+1)%N] = tmpRow[i];			//Dairesel bir þekilde dizinin yeni satýrý ayarlanýyor ve geri gönderiliyor
	}
	return colorRow;
}


void colors(int n){								//Renk seçeneklerini ekrana yazdýrýyor
	
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


void printMatrix(int **matrix, int N){		//Matrixlerde bulunan integer deðerlere göre ekrana yazdýrýyor
	
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


int** getColor(int **matrix, int N){				//Matrixin her bir elemaný için kullanýcýdan inputu alýyor. Yanlýþ bir deðer ya da seçenekler arasýnda bir renk girildiðinde hata veriyor.
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
