#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<conio.h>
#define MAX 15 


typedef struct user{
	char *username;
	double score;
	struct user *next;
}USER;

void drawBoard(int matrix[][MAX], int N);
int readFromFile(int matrix[][MAX], char *fileName);
void readRandomMatris(int n, int matrix[][MAX]);
USER* addUser(USER *head, char *name);
void configureVisited(int matrix[][MAX], int visited[][MAX], int n);
int isFullVisited(int visited[][MAX], int N);
int automaticGame(int matrix[][MAX], int visited[][MAX], int n, int startRow, int startCol, int tempRow, int tempCol, int dest, int isIncrease, double *score);
void gameMenu(int menuType);
void resetMatrix(int matrix[][MAX], int n);
USER* incrementScore(USER *head, char *name, int score);
void manualGame(int matrix[][MAX], int visited[][MAX], int n, double *score);
int isFreePath(int visited[][MAX], int n, int startRow, int startCol, int endRow, int endCol);
int min(int a, int b);
int max(int a, int b);


int main(){
	
    int i,j,matris[MAX][MAX]={{0}}, visited[MAX][MAX];
    int N; 
    char fileName[20];
    char *name;
	int selectionMain, selectionGame;
	USER *users = NULL;
	USER *current = (USER*)malloc(sizeof(USER));
	name = (char*)malloc(20*sizeof(char));
	int result;
	double score;
	char isAgree;
	float time;
	clock_t start, end;
	
	// Ana d�ng� ba�lang�c�
	do{
		gameMenu(1);
		scanf("%d", &selectionMain);
		// Oyun men�s� g�sterme
		if(selectionMain == 1){
			printf("Enter the file name : ");
  			scanf("%s",fileName);
  			N = readFromFile(matris, fileName);// Dosyadan okuma
  			if(N == -1)
  				selectionMain = 0;
  			if(selectionMain == 1){
  				printf("Enter the username : ");
  				scanf("%s", name);
				users = addUser(users, name);// Kullan�c� ekleme
				drawBoard(matris,N);
				configureVisited(matris, visited, N);//Visited matrisini tan�mlama	
				gameMenu(2);// Oyun modu se�me
				scanf("%d", &selectionGame);
				if(selectionGame == 1){
					score = 30000*N+50;
			  		start = clock();
					manualGame(matris, visited, N, &score);// Manuel oyun modu
					end = clock();
			  		time = (float)(end-start)/CLOCKS_PER_SEC;
			  		score -= time * 10;
			  		printf("Complete Time : %.1f\nGain Score : %.2lf\n\n",time, score);
		  			incrementScore(users, name, score);//Kullan�c� puan g�ncelleme
				}else if(selectionGame==2){
					if(N>7)
						printf("Solution is Loading!!\n");
		  			score = 30000*N+50;
			  		start = clock();
			  		result = automaticGame(matris, visited, N, 0, 0, 0, 0, 1, 1, &score);// Otomatik oyun modu
			  		end = clock();
			  		time = (float)(end-start)/CLOCKS_PER_SEC;
			  		score -= time * 10;
		  			if(result){
		  				printf("Complete Time : %.1f\nGain Score : %.2lf\n\n",time, score);
		  				incrementScore(users, name, score);//Kullan�c� puan g�ncelleme
					  }
		  			else{
		  				drawBoard(visited,N);
		  				printf("!!!!The Game Has No Solution!!!!\n\n");	
					  }
					  	
					resetMatrix(matris, N);
				}else if(selectionGame == 3){
					printf("\n\n");
				}else
					printf("Invalid Selection! Try Again!\n\n");
					
			}
		}else if(selectionMain == 2){
			printf("Enter the matrix size(N) = ");
			scanf("%d", &N);
			readRandomMatris(N, matris);// Rastgele matris olu�turma
			do{							//Kullan�c� yenisini olu�turdu�u s�rece yeni matrix olu�turma
				drawBoard(matris, N);
				printf("\nWould you like to use the matrix above[y|n]? :  ");
				scanf(" %c", &isAgree);
				
				if(isAgree != 'n' && isAgree != 'y')
					printf("Invalid Selection!! Try again!!\n\n");
				else if(isAgree == 'n'){
					resetMatrix(matris, N);
					readRandomMatris(N, matris);
				}
			}while(isAgree != 'y');
			
			printf("Enter the username : ");
  			scanf("%s", name);
			users = addUser(users, name);//Kullan�c� ekleme
			configureVisited(matris, visited, N);//Visited matrixini tan�mlama	
			gameMenu(2);
			scanf("%d", &selectionGame);
			if(selectionGame == 1){
				score = 30000*N+100;
			  	start = clock();
				manualGame(matris, visited, N, &score);//Manuel oyun modu
				end = clock();
			  	time = (float)(end-start)/CLOCKS_PER_SEC;
			  	score -= time * 10;
			  	printf("Complete Time : %.1f\nGain Score : %.2lf\n\n",time, score);
		  		incrementScore(users, name, score);
			}else if(selectionGame==2){
				if(N>7)
					printf("Solution is Loading!!\n");
		  		drawBoard(matris,N);
		  		score = 30000*N+100;
		  		start = clock();
		  		result = automaticGame(matris, visited, N, 0, 0, 0, 0, 1, 1, &score);//Otomatik oyun modu
		  		end = clock();
		  		time = (float)(end-start)/CLOCKS_PER_SEC;
		  		score -=  time * 10;
		  		if(result){
		  			printf("Complete Time : %.1f\nGain Score : %.2lf\n\n",time, score);
		  			incrementScore(users, name, score);
				}
		  		else{
		  			drawBoard(visited, N);//Matrix yazd�rma
		  			printf("!!!!The Game Has No Solution!!!!\n\n");	
				  }
				resetMatrix(matris, N);//Matrix s�f�rlama
			}else if(selectionGame == 3){
				printf("\n\n");
			}else
				printf("Invalid Selection! Try Again!\n\n");
				
		}else if(selectionMain == 3){
			printf("\nScore Table\n");
			printf("\tAuto Game Mode\n");
			printf("\t\tMatrix Size:\t\t+Size * 40000 Score\n\t\tRandom Game Mode:\t+100 Score\n\t\tRead File Mode:\t\t+50 Score\n\t\tUndo:\t\t\t-0.001 Score\n\t\tTime:\t\t\t-Second * 10 Score\n");
			printf("\tManual Game Mode\n");
			printf("\t\tMatrix Size:\t\t+Size * 40000 Score\n\t\tRandom Game Mode:\t+100 Score\n\t\tRead File Mode:\t\t+50 Score\n\t\tUndo:\t\t\t-2 Score\n\t\tTime:\t\t\t-Second * 10 Score\n\n");
			current = users;//Kullan�c� puanlar�n� yazd�rma
			while(current != NULL){
				printf("User %s:\t %.2lf Score\n",current->username, current->score);
				current = current->next;
			}
			printf("\n");
		}else if(selectionMain == 4)
			printf("Program Terminated!\n");
		else
			printf("Invalid Selection! Try Again!\n");
			
	}while(selectionMain != 4);
	
	
  return 0;
}


void manualGame(int matrix[][MAX], int visited[][MAX], int n, double *score){
	
	int i, j;
	int control = 0;
	int count = 1;
	int startRow, startCol, endRow, endCol;
	int sourceRow, sourceCol, destRow, destCol;
	int backMoves[MAX][5];// Geriye al�nabilen hamleleri tutan dizi
	int isFree;
	int backCount = 0;
	int isUndo;
	int rowOrCol, deletePoint1, deletePoint2, deletePoint3;	
	
	while(count  < n+1 || !control){//Oyun gereksinimlerini sa�lamad��� s�rece devam ediyor
		
		printf("Press any key to continue!\n");
		printf("Press 0 to undo!\n");
		printf("Selection : ");
		scanf("%d", &isUndo);
		
		if(isUndo != 0){
			
			do{																	//Tahtadan ilk adresi al�yor
				printf("Enter the source row: ");					
				scanf("%d", &sourceRow);
				
				if(sourceRow < 0 || sourceRow >= n)
					printf("Invalid Number! Enter a value suitable for the matrix dimensions!!\n");
				else{
					printf("Enter the source column: ");
					scanf("%d", &sourceCol);
					
					if(sourceCol < 0 || sourceCol >= n)
						printf("Invalid Number! Enter a value suitable for the matrix dimensions!!\n");
					else if(visited[sourceRow][sourceCol] == 0)
						printf("Source address is empty!!\n");
					else if(matrix[sourceRow][sourceCol] != 0){			//Ger�ek matrixte ba�lang�� yeri tutuyor
						startRow = sourceRow;
						startCol = sourceCol;
						for(i=0;i<n;i++){
							for(j=0;j<n;j++){
								if(matrix[i][j] == matrix[sourceRow][sourceCol] && !(i==startRow && j==startCol)) {
									endRow = i;
									endCol = j;							//Ger�ek matrixte biti� yeri tutuyor
								}
							}
						}
					}
						
				}
				
			}while((sourceRow < 0 || sourceRow >= n) || (sourceCol < 0 || sourceCol >= n) || (visited[sourceRow][sourceCol] == 0));
			
			
			do{
				printf("Enter the destination row(-1 to change source address): ");		//Tahtadan hedef adresi al�yor
				scanf("%d", &destRow);
				
				if(destRow == -1){
					do{
						printf("Enter the source row: ");
						scanf("%d", &sourceRow);
						
						if(sourceRow < 0 || sourceRow >= n)
							printf("Invalid Number! Enter a value suitable for the matrix dimensions!!\n");
						else{
							printf("Enter the source column: ");
							scanf("%d", &sourceCol);
							
							if(sourceCol < 0 || sourceCol >= n)
								printf("Invalid Number! Enter a value suitable for the matrix dimensions!!\n");
							else if(visited[sourceRow][sourceCol] == 0)
								printf("Source address is empty!!\n");
							else if(visited[sourceRow][sourceCol] != 0){
								startRow = sourceRow;
								startCol = sourceCol;		
								for(i=0;i<n;i++){
									for(j=0;j<n;j++){
										if(matrix[i][j] == matrix[sourceRow][sourceCol] && !(i==startRow && j==startCol)) {
											endRow = i;
											endCol = j;
										}
									}
								}
							}
								
						}
						
					}while((sourceRow < 0 || sourceRow >= n) || (sourceCol < 0 || sourceCol >= n) || (visited[sourceRow][sourceCol] == 0));
				}
				else if(destRow < 0 || destRow >= n)
					printf("Invalid Number! Enter a value suitable for the matrix dimensions!!\n");
				else{
					printf("Enter the destination column: ");				
					scanf("%d", &destCol);
					
					if(destCol < 0 || destCol >= n)
						printf("Invalid Number! Enter a value suitable for the matrix dimensions!!\n");
					else if(sourceRow == destRow && sourceCol == destCol)
						printf("Source address and destination adress is same!!!\n");
					else if(visited[destRow][destCol] != 0)
						printf("Destination address is full!!\n");
					else if(destRow != sourceRow && destCol != sourceCol)
						printf("Destination address and source address must be in the same direction!!\n");	
				}
				
			}while((destRow < 0 || destRow >= n) || (destCol < 0 || destCol >= n) || (visited[destRow][destCol] != 0) || (destRow != sourceRow && destCol != sourceCol));
			
			
			isFree = isFreePath(visited, n, sourceRow, sourceCol, destRow, destCol);//Al�nan adresler aras�ndaki yolun bo� olup olmad���n� kontrol ediyor
			
			if(isFree == 1){								//E�er yol m�saitse i�aretlemeleri yap�yor
				for(i=sourceCol+1; i<=destCol; i++)
					visited[sourceRow][i] = visited[sourceRow][sourceCol];
				backMoves[backCount][0] = 0;				//Yatay dikey oldu�unu tutuyor
				backMoves[backCount][1] = sourceRow;		//Yatay dikey s�ray� belirliyor
				backMoves[backCount][2] = sourceCol+1;		//De�i�tirilecek adresleri belirliyor
				backMoves[backCount][3] = destCol;
				backMoves[backCount++][4] = 0;				//E�le�me olup olmad���n� koyuyor
			}else if(isFree == 2){
				for(i=sourceCol-1; i>=destCol; i--)
					visited[sourceRow][i] = visited[sourceRow][sourceCol];
				backMoves[backCount][0] = 0;
				backMoves[backCount][1] = sourceRow;
				backMoves[backCount][2] = sourceCol-1;
				backMoves[backCount][3] = destCol;
				backMoves[backCount++][4] = 0;
			}else if(isFree == 3){
				for(i=sourceRow+1; i<=destRow; i++)
					visited[i][sourceCol] = visited[sourceRow][sourceCol];
				backMoves[backCount][0] = 1;
				backMoves[backCount][1] = sourceCol;
				backMoves[backCount][2] = sourceRow+1;
				backMoves[backCount][3] = destRow;
				backMoves[backCount++][4] = 0;
			}else if(isFree == 4){
				for(i=sourceRow-1; i>=destRow; i--)
					visited[i][sourceCol] = visited[sourceRow][sourceCol];
				backMoves[backCount][0] = 1;
				backMoves[backCount][1] = sourceCol;
				backMoves[backCount][2] = sourceRow-1;
				backMoves[backCount][3] = destRow;
				backMoves[backCount++][4] = 0;
			}else
				printf("Path is not available!!\n}n");
				
			
			if(destRow+1 < n && destRow+1 == endRow && destCol == endCol){
				count++;
				backMoves[backCount-1][4]=1;									//��aretler e�le�mi�, i�aret sayac� artt�r�l�yor
				if(isFullVisited(visited, n))
					control = 1;												//B�t�n tablonun dolu olup olmad��� kontrol ediliyor
			}else if(destRow-1 >= n && destRow-1 == endRow && destCol == endCol){
				count++;
				backMoves[backCount-1][4]=1;
				if(isFullVisited(visited, n))
					control = 1;
			}else if(destCol+1 < n && destRow == endRow && destCol+1 == endCol){
				count++;
				backMoves[backCount-1][4]=1;
				if(isFullVisited(visited, n))
					control = 1;
			}else if(destCol-1 >= 0 && destRow == endRow && destCol-1 == endCol){
				count++;
				backMoves[backCount-1][4]=1;
				if(isFullVisited(visited, n))
					control = 1;
				
			}
			system("cls");						//Ekran� temizliyor
			drawBoard(visited, n);				//Ekrana yazd�rma
			
		}else{
			if(backCount == 0)
				printf("No moves have been made before!!\n");
				
			else{
				backCount--;
				*score -= 2;
				rowOrCol = backMoves[backCount][0];			//Geri al�nmada yap�lcak hamleleri al�yor
				deletePoint1 = backMoves[backCount][1];
				deletePoint2 = backMoves[backCount][2];
				deletePoint3 = backMoves[backCount][3];
				
				
				
				if(!rowOrCol){								//Yatay olarak geri al�m i�lemini yap�yor
					count = count - backMoves[backCount][4];//E�er o hamlede e�le�me varsa kald�r�l�yor
					for(i=min(deletePoint2, deletePoint3); i<=max(deletePoint2, deletePoint3); i++){
						visited[deletePoint1][i] = 0;
					}
					
				}else{										//Dikey olarak geri al�m i�lemini yap�yor
					count = count - backMoves[backCount][4];
					for(i=min(deletePoint2, deletePoint3); i<=max(deletePoint2, deletePoint3); i++){
						visited[i][deletePoint1] = 0;
					}
				
				}
				system("cls");
				drawBoard(visited, n);		
				
			}
			
		}
		
	}
	
	
}


// Verilen ziyaret edilmi� matriste, ba�lang�� noktas�ndan hedef noktaya serbest bir yol olup olmad���n� kontrol eder.
int isFreePath(int visited[][MAX], int n, int startRow, int startCol, int endRow, int endCol){
	
	int control;
	int i;
	
	if(startRow == endRow){
		if(startCol < endCol){
			i = startCol+1;
			while(i<=endCol && visited[startRow][i] == 0)
				i++;
			if(i==endCol+1)
				return 1;// Yatay serbest yol
			else
				return 0;//De�il	
		}
		else{
			i = startCol-1;
			while(i>=endCol && visited[startRow][i] == 0)
				i--;
			if(i == endCol-1)
				return 2;// Ters Yatay serbest yol
			else
				return 0;
		}
	}else{
		if(startRow < endRow){
			i = startRow +1;
			while(i<=endRow && visited[i][startCol] ==0)
				i++;
			if(i == endRow+1)
				return 3;//Dikey serbest yol
			else
				return 0;
		}else{
			i = startRow-1;
			while(i>=endRow && visited[i][startCol] == 0)
				i--;
			if(i== endRow-1)
				return 4;//Ters dikey serbest yol
			else
				return 0;
		}
		
	}
} 


int min(int a, int b){//�ki say�dan k���k olan� d�nd�r�r
	
	if(a<b)
		return a;
	else
		return b;
		
}

int max(int a, int b){//�ki say�dan b�y�k olan� d�nd�r�r
	
	if(a<b)
		return b;
	else
		return a;
		
}


 void sleep(){//Program� yazd�r�rken anla��l�r olmas� i�in fonksiyoun
 	int i, j, k;
 	for(i=0;i<2000000;i++){
 		for(j=0; j<25; j++){
 			k=0;
		 }
	 }
 }


USER* incrementScore(USER *head, char *name, int score){//Kullan�c�n�n yap�s�nda skor g�ncelleme
	
	USER *current = head;
	
	while(strcmp(current->username, name) != 0)	//Kullan�c�y� bulma
		current = current->next;
	
	current->score += score;
	
}



void resetMatrix(int matrix[][MAX], int n){//G�nderilen matrixin i�ini 0 olacak �ekilde ayarl�yor
	
	int i, j;			
	
	for(i=0; i<n; i++){
		for(j=0; j<n; j++)
			matrix[i][j] = 0;
	}
	
}


void gameMenu(int menuType){
	
	if(menuType == 1)
		printf("Main Menu\n1.Read From File Mode\n2.Random Write Mode\n3.Show Scores of Users\n4.Exit\nSelection : ");
	else
		printf("\nGame Menu\n1.Play in Manual Mode\n2.Play in Auto Mode\n3.Back to Main Menu\nSelection : ");
	
	
}


void configureVisited(int matrix[][MAX], int visited[][MAX], int n){//Matrix �zerinde i�lemler yap�lmas� i�in ger�ek matrixi kopyal�yor
	
	int i, j;
	
	for(i=0; i<n; i++){
		for(j=0; j<n; j++)
			visited[i][j] = matrix[i][j];
	}
	
}


// Otomatik oyunun ger�ekle�tirildi�i fonksiyon.
// startRow, startCol: Ba�lang�� h�cresinin koordinatlar�
// tempRow, tempCol: Ge�ici h�crenin koordinatlar�
// dest: Hedef h�cre de�eri
// isIncrease: H�cre de�eri art�r�l�yor mu?
// score: Oyuncunun skorunu tutan de�i�ken
// Fonksiyon, recursive bir �ekilde oyunun otomatik olarak oynand��� algoritmay� uygular.
// Ba�lang�� h�cresinden ba�layarak, matristeki h�creleri ziyaret eder ve hedefe ula�maya �al���r.
// Ziyaret edilen h�creler visited matrisine i�aretlenir.
// E�er hedefe ula��l�rsa (visited matrisi tam dolu ise), fonksiyon 1 d�ner.
// E�er hedefe ula��lamazsa, fonksiyon 0 d�ner.
int automaticGame(int matrix[][MAX], int visited[][MAX], int n, int startRow, int startCol, int tempRow, int tempCol, int dest, int isIncrease,double *score){
	
	int i, j;
	int control = 0;
	
	if(dest == n+1){
		if(isFullVisited(visited, n)){
			drawBoard(visited, n);
			return 1;
		}
		else
			return 0;
	}
	
	
	if(isIncrease){
		// Hedef de�eri art�r�l�rken, ba�lang�� h�cresi belirlenir
		i=0;
		while(!control && i<n){
			j=0;
			while(!control && j<n){
				if(visited[i][j] == dest){
					control = 1;
					startRow = i;
					startCol = j;
					tempRow = i;
					tempCol = j;
				}
				j++;	
			}
			i++;
		}
	}
	
		
	
	if(matrix[tempRow][tempCol] == dest && !(tempRow == startRow && tempCol == startCol)){// Ge�ici h�cre hedef de�erine e�itse ve ba�lang�� h�cresi de�ilse, bir sonraki hedefe ge�ilir
		if(n<8){
			drawBoard(visited, n);
			sleep();
			system("cls");
		}
		return automaticGame(matrix, visited, n, 0, 0, 0, 0, dest+1, 1, score);
	}
	else if(visited[tempRow][tempCol] != 0 && !(tempRow == startRow && tempCol == startCol))// Ge�ici h�cre ziyaret edilmi�se ve ba�lang�� h�cresiyse, hedefe ula��lamaz
		return 0;
	
		
	
	else{
		if(!(tempRow == startRow && tempCol == startCol))//visited matrixine i�aretleme
			visited[tempRow][tempCol] = dest;				
		if(tempRow+1 < n && automaticGame(matrix, visited, n, startRow, startCol, tempRow+1, tempCol, dest, 0, score)){//A�a��ya hareket et
			return 1;
		}
		else if(tempCol+1 < n && automaticGame(matrix, visited, n, startRow, startCol, tempRow, tempCol+1, dest, 0, score)){//Sa�a hareket et
			return 1;
		}
		else if(tempCol-1 >= 0 && automaticGame(matrix, visited, n, startRow, startCol, tempRow, tempCol-1, dest, 0, score)){//Sola hareket et
			return 1;
		}
		else if(tempRow-1 >= 0 && automaticGame(matrix, visited, n, startRow, startCol, tempRow-1, tempCol, dest, 0, score)){//Yukar� hareket et
			return 1;
		}
		else{
			if(matrix[tempRow][tempCol] == 0){// Ge�ici h�crede do�ru de�ilse, ziyaret edilen h�creyi geri al ve skoru azalt
				visited[tempRow][tempCol] = 0;
				*score -= 0.001;
			}
				
			
			return 0;
		}
			
		
	}
	
	
}


int isFullVisited(int visited[][MAX], int N){//B�t�n matrixin dolu olup olmad��� kontrol ediliyor
	
	int i, j;
	
	i=0;
	while(i<N){
		j=0;
		while(j<N){				//Doluysa 0 d�nd�r�yor
			if(visited[i][j] == 0)
				return 0;
			j++;
		}
		i++;
	}
	return 1;
	
}


USER* addUser(USER *head, char *name){// Kullan�c� d���m�n� verilen kullan�c� ad�yla birlikte kullan�c� listesine ekler.
	
	USER *current;
	USER *prev;
	USER *newUser;
	
	if(head == NULL){
		// Liste bo� ise, head d���m� olu�turulur ve kullan�c� bilgileri eklenir
		head = (USER*)malloc(sizeof(USER));
		head->username = (char*)malloc(20*sizeof(char));
		strcpy(head->username, name);
		head->score = 0;
		head->next = NULL;
		return head;
	}else{
		current = head;
		while(current != NULL && strcmp(current->username, name) != 0){
			prev = current;
			current = current->next;
		}
		if(current == NULL){// Kullan�c� ad� listede yok ise, yeni kullan�c� d���m� olu�turulur ve listenin sonuna eklenir
			newUser = (USER*)malloc(sizeof(USER));
			newUser->username = (char*)malloc(20*sizeof(char));
			strcpy(newUser->username, name);
			newUser->score = 0;
			prev->next = newUser;
			newUser->next = NULL;
			return head;
		}
		else
			return head;
		
			
	}
	
}

void readRandomMatris(int n, int matrix[][MAX]){//Matrix boyutuna g�re de�erleri rastgele da��t�yor
	
	int i, j;
	int row, col;
	
	for(i=0; i<2; i++){
		for(j=1; j<=n; j++){
			srand(time(NULL));
			do{
				row = rand() % n;
				col = rand() % n;
			}while(matrix[row][col] != 0);
			matrix[row][col] = j;
		}
	}
	
}


int readFromFile(int matrix[][MAX], char *fileName){//Dosyadan Okuma
	int i,j, temp;
	int count;
	
	FILE *data = fopen(fileName,"r");
	if(!data){
        printf("File Failed to Open!\n\n");
		return -1;
    }
    while(!feof(data)){
        fscanf(data,"%d %d %d\n",&i,&j,&temp);  
		matrix[i][j]=temp; 
		count++;
    }  
  	fclose(data);
  	return count/2;
}



void drawBoard(int matrix[][MAX], int N){//Matrixi terminale yazd�rma
    int i,j,k;
    printf("\nBoard");
    for(i=0;i<N;i++){
        printf("\n");
        for (k=0;k<N;k++)
            printf("-------");
        printf("\n");
        for(j=0;j<N;j++)
            if (matrix[i][j]!=0)
                printf("  %d   |",matrix[i][j]);
            else
                 printf("      |",matrix[i][j]);
    }
    printf("\n\n");
    
}
