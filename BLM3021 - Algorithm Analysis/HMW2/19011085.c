#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>


typedef struct node{	//Her kullan�c�n�n numaras�, indegree say�s�, ismi, soyismi ve takip ettiklerini tutmak i�in next node'u tutuluyor
	int vertex;			
	int indegree;
	char *name;
	char *surname;
	struct node *next;
}NODE;

typedef struct graph{	//Graf yap�s�nda node listesi ve node adeti tutuluyor
	int numVertices;
	struct node **adjLists;
}GRAPH;

void fileToAdjList(GRAPH *list);
int findCountUser();
void addEdge(GRAPH* graph,int src, int dest);
GRAPH* createGraph(int vertices);
NODE* createNode(int v, char *firstName, char *lastName);
void eliminationNode(GRAPH* list, int limit, int *deletedArray);
void DFS(GRAPH *list, int dest, int *deletedArray, int *haveLink);

int main(){
	
	int selection;
	int countOfUser;
	int *isDeleted;
	int i,j;
	int **matrix;
	int m,x,y;
	NODE *tmp;
	countOfUser = findCountUser();							//Ka� adet kullan�c� oldu�u hesaplan�yor			
	int countOfRoad[countOfUser];							//Dolayl� ya da do�rudan ka� d���mden ula��labilece�ini tutan dizi
	matrix = (int**)malloc(countOfUser*sizeof(int*));		//Hangi d���mler aras�nda do�rudan ya da dolayl� olup olmad���n� tutan matris
	for(i=0;i<countOfUser;i++)								//1-->Yol var	0-->Yol yok
		matrix[i] = (int*)calloc(countOfUser,sizeof(int)); 
	 isDeleted = (int*)calloc(countOfUser,sizeof(int));		//Indegree say�s� M'de�erinden d���k olanlar�n silindi�ini tutan dizi
	GRAPH *graf = createGraph(countOfUser);					//Kullan�c� say�s�na g�re graf�n b�y�kl��� belirleniyor
	GRAPH *newGraf = graf;									//�kinci bir graf olu�turuluyor, bilgiler kaybedilmesin diye
	fileToAdjList(graf);									//Kullan�c�n�n bilgilerini ve hangi kullan�c�lar� takip etti�ini dosyadan okuyor
	
	do{
		printf("1.Normal Mod\n2.Detayli Mod\n3.Cikis\nSecim:");		//Program�n �al��t�r�lacak modu se�iyor
		scanf("%d",&selection);
		if(selection==1){
			printf("M : ");											//Kullan�c�dan M de�erini al�yor
			scanf("%d",&m);
			do{
				printf("X : ");										//Kullan�c�dan X>M olacak �ekilde X de�erini al�yor
				scanf("%d",&x);
				if(x<=m)
					printf("M'den buyuk bir deger giriniz!\n");
			}while(x<=m);
			printf("Y : ");											//Kullan�c�dan Y de�erini al�yor
			scanf("%d",&y);
			eliminationNode(newGraf, m, isDeleted);					//Girilen M de�erine g�re indegreesi d���k olanlar� eliyor
			for(i=0;i<countOfUser;i++){
				DFS(newGraf,i,isDeleted,matrix[i]);					//Kullan�c�lar aras�nda yol olup olmad���n� DFS fonksiyonu ile buluyor
			}
			for(i=0;i<countOfUser;i++){								//Ka� yol oldu�u bilgisini tutmak i�in ba�ta diziyi s�f�rl�yor
				countOfRoad[i] = 0;
			}
			for(i=0;i<countOfUser;i++){
				matrix[i][i] = 0;									//Matrixte kendine olan yolu s�f�rl�yor
				for(j=0;j<countOfUser;j++){
					countOfRoad[i] += matrix[j][i];					//Matrixte ilgili s�tun hesaplanarak ka� yol oldu�u bilgisi dizide tutuluyor
				}
			}
			printf("Influencer Bilgileri\n");
			for(i=0;i<countOfUser;i++){								//Her bir kullan�c� i�in indegree say�s� X'ten b�y�kse ve toplam yol Y'den b�y�kse kullan�c�lar� ekrana yazd�r�yor
				if(newGraf->adjLists[i]->indegree >= x && countOfRoad[i] >= y){
					printf("%d-%s-%s\n",newGraf->adjLists[i]->vertex,newGraf->adjLists[i]->name,newGraf->adjLists[i]->surname);
				}
			}
		}else if(selection==2){
			printf("M : ");											//Kullan�c�dan M de�erini al�yor
			scanf("%d",&m);
			do{
				printf("X : ");										//Kullan�c�dan X>M olacak �ekilde X de�erini al�yor
				scanf("%d",&x);
				if(x<=m)
					printf("M'den buyuk bir deger giriniz!\n");
			}while(x<=m);
			printf("Y : ");											//Kullan�c�dan Y de�erini al�yor
			scanf("%d",&y);
			printf("Baslangic In-Degree Degerleri\n");				//Hi�bir i�lem yap�lmadan bilgileri ekrana yazd�r�yor
			for(i=0;i<countOfUser;i++){
				printf("NODE : %d   In Degree : %d\t  -->",graf->adjLists[i]->vertex, graf->adjLists[i]->indegree);
				tmp = graf->adjLists[i]->next;
				while(tmp!=NULL){
					printf("%d  ",tmp->vertex);
					tmp = tmp->next;
				}
				printf("\n");
			}
			eliminationNode(newGraf, m, isDeleted);					//Limite g�re indegreelere eleme i�lemi yap�yor
			printf("\n\nEleme Sonrasi In-Degree Degerleri\n");		//Eleme yap�ld�ktan sonra bilgileri ekrana yazd�r�yor
			for(i=0;i<countOfUser;i++){
				if(isDeleted[i] == 0)
					printf("%d-%s-%s--In Degree : %d\n",newGraf->adjLists[i]->vertex,newGraf->adjLists[i]->name,newGraf->adjLists[i]->surname, newGraf->adjLists[i]->indegree);
			}
			for(i=0;i<countOfUser;i++){								//Kullan�c�lar aras�nda yol olup olmad���n� DFS fonksiyonu ile buluyor
				DFS(newGraf,i,isDeleted,matrix[i]);
			}
			for(i=0;i<countOfUser;i++){								//Ka� yol oldu�u bilgisini tutmak i�in ba�ta diziyi s�f�rl�yor
				countOfRoad[i] = 0;
			}
			for(i=0;i<countOfUser;i++){
				matrix[i][i] = 0;									//Matrixte kendine olan yolu s�f�rl�yor
				for(j=0;j<countOfUser;j++){
					countOfRoad[i] += matrix[j][i];					//Matrixte ilgili s�tun hesaplanarak ka� yol oldu�u bilgisi dizide tutuluyor
				}
			}
			printf("\n\nInfluencer Bilgileri\n");					//Verilen �artlar sa�land�ktan sonraki Influencer bilgilerini ekrana yazd�r�yor
			for(i=0;i<countOfUser;i++){
				if(newGraf->adjLists[i]->indegree >= x && countOfRoad[i] >= y){
					printf("%d-%s-%s-In-Degree : %d - Toplam Baglanti Sayisi : %d\n",newGraf->adjLists[i]->vertex,newGraf->adjLists[i]->name,newGraf->adjLists[i]->surname,newGraf->adjLists[i]->indegree, countOfRoad[i]);
				}
			}
		}else if(selection==3)
			printf("Program sonlandirildi...");
		else
			printf("Hatali secim. Tekrar Deneyiniz!\n");
	}while(selection != 3);											//Programdan ��k�� yap�lmad��� s�rece program�n �al��mas�n�n devam etmesini sa�l�yor
	
	return 0;
}

GRAPH* createGraph(int vertices){									//D���m say�s� bilgisi al�n�yor
	int i;
	GRAPH *graph = malloc(sizeof(GRAPH));							//GRAPH yap�s� kadar bellekte yer a��l�yor
	graph->numVertices = vertices;									//Ka� adet kullan�c�dan olu�ca�� bilgisi tutuluyor
	graph->adjLists = malloc(vertices*sizeof(NODE*));				//Kullan�c� say�s�na g�re o kadar d���m i�in bellekte yer a��l�r
	for(i=0;i<vertices;i++)
		graph->adjLists[i] = NULL;									//Hepsi ba�ta NULL olarak atan�yor
	return graph;
}

NODE* createNode(int v, char *firstName, char *lastName){			//Her bir d���m i�in haf�zadan yer ayr�l�yor
	NODE* newNode = malloc(sizeof(NODE));
	newNode->vertex = v;											//ka��nc� d���m oldu�u bilgisi, ismi ve soyismi d���me at�l�yor
	newNode->indegree = 0;											//Indegree ba�ta 0 olacak �ekilde ayarlan�yor
	newNode->name = (char*)malloc(sizeof(char)*strlen(firstName));
	strcpy(newNode->name,firstName);
	newNode->surname = (char*)malloc(sizeof(char)*strlen(lastName));
	strcpy(newNode->surname,lastName);
	newNode->next = NULL;											//Takip etti�i kullan�c�lar ilk olarak NULL belirleniyor
	return newNode;
}

void addEdge(GRAPH* graph,int src, int dest){						//Kullan�c�n�n takip etti�i kullan�c�lar� grafa ekliyor
																	//Kullan�c�n�n takip etti�i kullan�c� d���m olarak olu�turuluyor
	NODE* newNode= createNode(graph->adjLists[dest]->vertex, graph->adjLists[dest]->name,graph->adjLists[dest]->surname);
	newNode->next = graph->adjLists[src]->next;						
	graph->adjLists[src]->next = newNode;
	(graph->adjLists[dest]->indegree)++;							//Takip etti�i kullan�c�n�n indegree say�s�n� artt�r�yor
	
}

int findCountUser(){												//Kullan�c� say�s�n� hesapl�yor
	
	FILE *fp;
	int count=0;													//Count ba�ta 0 olarak al�n�yor
	int maxLineLength = 255;
	char line[maxLineLength];
	
	fp = fopen("socialNet.txt","r");								//Okuayaca��m�z dosyay� a��yoruz
	if(fp != NULL){
		while(fgets(line, maxLineLength, fp)){						//Her kullan�c� i�in 2 sat�r bilgi oldu�u i�in 2 sat�r ayn� anda okunuyor. Count artt�r�l�yor
			count++;
			fgets(line, maxLineLength, fp);
		}
	}else
		printf("File Open Error!\n");								//Dosya a��lmad���nda hata d�n�yor
	
	fclose(fp);
	
	return count;								
}

void fileToAdjList(GRAPH *list){									//Dosyadaki bilgileri grafa aktarmak i�in fonksiyon
	
	FILE *fp;
	int i=0;
	int maxLineLength = 255;
	char line[maxLineLength];
	char *tmpName, *tmpSurname, *tmpVertexStr;
	int tmpVertex;
	NODE *tmp;
	
	fp = fopen("socialNet.txt","r");								//Dosyay� okumak i�in a��yor
	if(fp != NULL){
		while(fgets(line, maxLineLength, fp)){		
			tmpVertexStr = strtok(line, ",");						//�lk sat�r� okuyup kullan�c�n�n ka��nc� kullan�c� oldu�unu, ismini ve soyismini al�yor
			tmpVertex = atoi(tmpVertexStr);							
			tmpName = strtok(NULL, ",");							
			tmpSurname = strtok(NULL, "\n");						
			list->adjLists[i] = createNode(tmpVertex,tmpName,tmpSurname);//Al�nan bilgilere g�re d���m olu�turuluyor ve grafa yerle�tiriliyor
			fgets(line, maxLineLength, fp);
			i++;
		}
	}else
		printf("File Open Error!\n");								//Dosya a�amama hatas�
	fclose(fp);
	
	i=0;
	fp = fopen("socialNet.txt","r");
	if(fp != NULL){
		while(fgets(line, maxLineLength, fp)){
			fgets(line, maxLineLength, fp);
			tmpVertexStr = strtok(line, ",");						//Takip etti�i kullan�c�lar� virg�le kadar ay�r�p kullan�c�lar�n takip etti�i kullan�c�lara d���m �eklinde ekliyoruz grafa
			do{
				tmpVertex = atoi(tmpVertexStr);
				if(tmpVertex != 0){
					addEdge(list,i,tmpVertex-1);
				}
				tmpVertexStr = strtok(NULL, ",");
				
			}while(tmpVertexStr != NULL);							//Takip etti�i kullan�c�lar bitinceye kadar devam ediyor split yapmaya
			i++;
		}
	}else
		printf("File Open Error!\n");								//Dosya a�amama hatas�
			
	fclose(fp);
	
}

void eliminationNode(GRAPH* list,int limit,int *deletedArray){		//Verilen limite g�re o limitin alt�ndaki indegree'ye sahip kullan�c�lar� elemek i�in fonksiyon
	
	int flag = 1;
	int count;
	int i;
	NODE *tmp;
	while(flag){													//Elemeler sonras�nda limitin alt�na d��ecek kullan�c�lar� da elemek i�in kontrol
		flag = 0;
		for(i=0;i<list->numVertices;i++){
			if(list->adjLists[i]->indegree<limit && deletedArray[i] == 0){//Limitin alt�nda ise 
				flag = 1;
				tmp = list->adjLists[i]->next;
				while(tmp!=NULL){
					(list->adjLists[tmp->vertex-1]->indegree)--;		//O kullan�c�n�n takip etti�i kullan�c�lar�n indegree say�s�n� azalt�yor 
					tmp = tmp->next;
				}
				deletedArray[i] = 1;									//Limitin alt�ndaki kullan�c�n�n elendi�i bilgisini dizide tutuyor
			}
		}	
	}	
	
}

void DFS(GRAPH *list, int dest, int *deletedArray, int *haveLink){	//Recursive DFS fonksiyonu
	
	NODE *tmp = list->adjLists[dest]->next;							//Parametrenin takip etti�i ilk d���m ge�ici �ekilde tmp'ye atan�yor
	if(deletedArray[dest] == 0){									//Eleme i�lemi yap�ld�ktan sonra hala i�lemde olup olmad��� kontrol ediliyor
		haveLink[dest] = 1;											//Matrixin ilgili sat�ra oraya ula��m oldu�u bilgisini yaz�yor. SET 1
		while(tmp != NULL){											//Takip etti�i kullan�c� bitinceye kadar ilerliyor
			if(haveLink[tmp->vertex-1] == 0){						//E�er oras� ziyaret edilmemi�se DFS recursive bir �ekilde ba�l� oldu�u kullan�c�n�n bilgisi ile �al���yor
				DFS(list,tmp->vertex-1,deletedArray,haveLink);
			}
			tmp = tmp->next;						
		}
	}
}


