#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>


typedef struct node{	//Her kullanýcýnýn numarasý, indegree sayýsý, ismi, soyismi ve takip ettiklerini tutmak için next node'u tutuluyor
	int vertex;			
	int indegree;
	char *name;
	char *surname;
	struct node *next;
}NODE;

typedef struct graph{	//Graf yapýsýnda node listesi ve node adeti tutuluyor
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
	countOfUser = findCountUser();							//Kaç adet kullanýcý olduðu hesaplanýyor			
	int countOfRoad[countOfUser];							//Dolaylý ya da doðrudan kaç düðümden ulaþýlabileceðini tutan dizi
	matrix = (int**)malloc(countOfUser*sizeof(int*));		//Hangi düðümler arasýnda doðrudan ya da dolaylý olup olmadýðýný tutan matris
	for(i=0;i<countOfUser;i++)								//1-->Yol var	0-->Yol yok
		matrix[i] = (int*)calloc(countOfUser,sizeof(int)); 
	 isDeleted = (int*)calloc(countOfUser,sizeof(int));		//Indegree sayýsý M'deðerinden düþük olanlarýn silindiðini tutan dizi
	GRAPH *graf = createGraph(countOfUser);					//Kullanýcý sayýsýna göre grafýn büyüklüðü belirleniyor
	GRAPH *newGraf = graf;									//Ýkinci bir graf oluþturuluyor, bilgiler kaybedilmesin diye
	fileToAdjList(graf);									//Kullanýcýnýn bilgilerini ve hangi kullanýcýlarý takip ettiðini dosyadan okuyor
	
	do{
		printf("1.Normal Mod\n2.Detayli Mod\n3.Cikis\nSecim:");		//Programýn çalýþtýrýlacak modu seçiyor
		scanf("%d",&selection);
		if(selection==1){
			printf("M : ");											//Kullanýcýdan M deðerini alýyor
			scanf("%d",&m);
			do{
				printf("X : ");										//Kullanýcýdan X>M olacak þekilde X deðerini alýyor
				scanf("%d",&x);
				if(x<=m)
					printf("M'den buyuk bir deger giriniz!\n");
			}while(x<=m);
			printf("Y : ");											//Kullanýcýdan Y deðerini alýyor
			scanf("%d",&y);
			eliminationNode(newGraf, m, isDeleted);					//Girilen M deðerine göre indegreesi düþük olanlarý eliyor
			for(i=0;i<countOfUser;i++){
				DFS(newGraf,i,isDeleted,matrix[i]);					//Kullanýcýlar arasýnda yol olup olmadýðýný DFS fonksiyonu ile buluyor
			}
			for(i=0;i<countOfUser;i++){								//Kaç yol olduðu bilgisini tutmak için baþta diziyi sýfýrlýyor
				countOfRoad[i] = 0;
			}
			for(i=0;i<countOfUser;i++){
				matrix[i][i] = 0;									//Matrixte kendine olan yolu sýfýrlýyor
				for(j=0;j<countOfUser;j++){
					countOfRoad[i] += matrix[j][i];					//Matrixte ilgili sütun hesaplanarak kaç yol olduðu bilgisi dizide tutuluyor
				}
			}
			printf("Influencer Bilgileri\n");
			for(i=0;i<countOfUser;i++){								//Her bir kullanýcý için indegree sayýsý X'ten büyükse ve toplam yol Y'den büyükse kullanýcýlarý ekrana yazdýrýyor
				if(newGraf->adjLists[i]->indegree >= x && countOfRoad[i] >= y){
					printf("%d-%s-%s\n",newGraf->adjLists[i]->vertex,newGraf->adjLists[i]->name,newGraf->adjLists[i]->surname);
				}
			}
		}else if(selection==2){
			printf("M : ");											//Kullanýcýdan M deðerini alýyor
			scanf("%d",&m);
			do{
				printf("X : ");										//Kullanýcýdan X>M olacak þekilde X deðerini alýyor
				scanf("%d",&x);
				if(x<=m)
					printf("M'den buyuk bir deger giriniz!\n");
			}while(x<=m);
			printf("Y : ");											//Kullanýcýdan Y deðerini alýyor
			scanf("%d",&y);
			printf("Baslangic In-Degree Degerleri\n");				//Hiçbir iþlem yapýlmadan bilgileri ekrana yazdýrýyor
			for(i=0;i<countOfUser;i++){
				printf("NODE : %d   In Degree : %d\t  -->",graf->adjLists[i]->vertex, graf->adjLists[i]->indegree);
				tmp = graf->adjLists[i]->next;
				while(tmp!=NULL){
					printf("%d  ",tmp->vertex);
					tmp = tmp->next;
				}
				printf("\n");
			}
			eliminationNode(newGraf, m, isDeleted);					//Limite göre indegreelere eleme iþlemi yapýyor
			printf("\n\nEleme Sonrasi In-Degree Degerleri\n");		//Eleme yapýldýktan sonra bilgileri ekrana yazdýrýyor
			for(i=0;i<countOfUser;i++){
				if(isDeleted[i] == 0)
					printf("%d-%s-%s--In Degree : %d\n",newGraf->adjLists[i]->vertex,newGraf->adjLists[i]->name,newGraf->adjLists[i]->surname, newGraf->adjLists[i]->indegree);
			}
			for(i=0;i<countOfUser;i++){								//Kullanýcýlar arasýnda yol olup olmadýðýný DFS fonksiyonu ile buluyor
				DFS(newGraf,i,isDeleted,matrix[i]);
			}
			for(i=0;i<countOfUser;i++){								//Kaç yol olduðu bilgisini tutmak için baþta diziyi sýfýrlýyor
				countOfRoad[i] = 0;
			}
			for(i=0;i<countOfUser;i++){
				matrix[i][i] = 0;									//Matrixte kendine olan yolu sýfýrlýyor
				for(j=0;j<countOfUser;j++){
					countOfRoad[i] += matrix[j][i];					//Matrixte ilgili sütun hesaplanarak kaç yol olduðu bilgisi dizide tutuluyor
				}
			}
			printf("\n\nInfluencer Bilgileri\n");					//Verilen þartlar saðlandýktan sonraki Influencer bilgilerini ekrana yazdýrýyor
			for(i=0;i<countOfUser;i++){
				if(newGraf->adjLists[i]->indegree >= x && countOfRoad[i] >= y){
					printf("%d-%s-%s-In-Degree : %d - Toplam Baglanti Sayisi : %d\n",newGraf->adjLists[i]->vertex,newGraf->adjLists[i]->name,newGraf->adjLists[i]->surname,newGraf->adjLists[i]->indegree, countOfRoad[i]);
				}
			}
		}else if(selection==3)
			printf("Program sonlandirildi...");
		else
			printf("Hatali secim. Tekrar Deneyiniz!\n");
	}while(selection != 3);											//Programdan çýkýþ yapýlmadýðý sürece programýn çalýþmasýnýn devam etmesini saðlýyor
	
	return 0;
}

GRAPH* createGraph(int vertices){									//Düðüm sayýsý bilgisi alýnýyor
	int i;
	GRAPH *graph = malloc(sizeof(GRAPH));							//GRAPH yapýsý kadar bellekte yer açýlýyor
	graph->numVertices = vertices;									//Kaç adet kullanýcýdan oluþcaðý bilgisi tutuluyor
	graph->adjLists = malloc(vertices*sizeof(NODE*));				//Kullanýcý sayýsýna göre o kadar düðüm için bellekte yer açýlýr
	for(i=0;i<vertices;i++)
		graph->adjLists[i] = NULL;									//Hepsi baþta NULL olarak atanýyor
	return graph;
}

NODE* createNode(int v, char *firstName, char *lastName){			//Her bir düðüm için hafýzadan yer ayrýlýyor
	NODE* newNode = malloc(sizeof(NODE));
	newNode->vertex = v;											//kaçýncý düðüm olduðu bilgisi, ismi ve soyismi düðüme atýlýyor
	newNode->indegree = 0;											//Indegree baþta 0 olacak þekilde ayarlanýyor
	newNode->name = (char*)malloc(sizeof(char)*strlen(firstName));
	strcpy(newNode->name,firstName);
	newNode->surname = (char*)malloc(sizeof(char)*strlen(lastName));
	strcpy(newNode->surname,lastName);
	newNode->next = NULL;											//Takip ettiði kullanýcýlar ilk olarak NULL belirleniyor
	return newNode;
}

void addEdge(GRAPH* graph,int src, int dest){						//Kullanýcýnýn takip ettiði kullanýcýlarý grafa ekliyor
																	//Kullanýcýnýn takip ettiði kullanýcý düðüm olarak oluþturuluyor
	NODE* newNode= createNode(graph->adjLists[dest]->vertex, graph->adjLists[dest]->name,graph->adjLists[dest]->surname);
	newNode->next = graph->adjLists[src]->next;						
	graph->adjLists[src]->next = newNode;
	(graph->adjLists[dest]->indegree)++;							//Takip ettiði kullanýcýnýn indegree sayýsýný arttýrýyor
	
}

int findCountUser(){												//Kullanýcý sayýsýný hesaplýyor
	
	FILE *fp;
	int count=0;													//Count baþta 0 olarak alýnýyor
	int maxLineLength = 255;
	char line[maxLineLength];
	
	fp = fopen("socialNet.txt","r");								//Okuayacaðýmýz dosyayý açýyoruz
	if(fp != NULL){
		while(fgets(line, maxLineLength, fp)){						//Her kullanýcý için 2 satýr bilgi olduðu için 2 satýr ayný anda okunuyor. Count arttýrýlýyor
			count++;
			fgets(line, maxLineLength, fp);
		}
	}else
		printf("File Open Error!\n");								//Dosya açýlmadýðýnda hata dönüyor
	
	fclose(fp);
	
	return count;								
}

void fileToAdjList(GRAPH *list){									//Dosyadaki bilgileri grafa aktarmak için fonksiyon
	
	FILE *fp;
	int i=0;
	int maxLineLength = 255;
	char line[maxLineLength];
	char *tmpName, *tmpSurname, *tmpVertexStr;
	int tmpVertex;
	NODE *tmp;
	
	fp = fopen("socialNet.txt","r");								//Dosyayý okumak için açýyor
	if(fp != NULL){
		while(fgets(line, maxLineLength, fp)){		
			tmpVertexStr = strtok(line, ",");						//Ýlk satýrý okuyup kullanýcýnýn kaçýncý kullanýcý olduðunu, ismini ve soyismini alýyor
			tmpVertex = atoi(tmpVertexStr);							
			tmpName = strtok(NULL, ",");							
			tmpSurname = strtok(NULL, "\n");						
			list->adjLists[i] = createNode(tmpVertex,tmpName,tmpSurname);//Alýnan bilgilere göre düðüm oluþturuluyor ve grafa yerleþtiriliyor
			fgets(line, maxLineLength, fp);
			i++;
		}
	}else
		printf("File Open Error!\n");								//Dosya açamama hatasý
	fclose(fp);
	
	i=0;
	fp = fopen("socialNet.txt","r");
	if(fp != NULL){
		while(fgets(line, maxLineLength, fp)){
			fgets(line, maxLineLength, fp);
			tmpVertexStr = strtok(line, ",");						//Takip ettiði kullanýcýlarý virgüle kadar ayýrýp kullanýcýlarýn takip ettiði kullanýcýlara düðüm þeklinde ekliyoruz grafa
			do{
				tmpVertex = atoi(tmpVertexStr);
				if(tmpVertex != 0){
					addEdge(list,i,tmpVertex-1);
				}
				tmpVertexStr = strtok(NULL, ",");
				
			}while(tmpVertexStr != NULL);							//Takip ettiði kullanýcýlar bitinceye kadar devam ediyor split yapmaya
			i++;
		}
	}else
		printf("File Open Error!\n");								//Dosya açamama hatasý
			
	fclose(fp);
	
}

void eliminationNode(GRAPH* list,int limit,int *deletedArray){		//Verilen limite göre o limitin altýndaki indegree'ye sahip kullanýcýlarý elemek için fonksiyon
	
	int flag = 1;
	int count;
	int i;
	NODE *tmp;
	while(flag){													//Elemeler sonrasýnda limitin altýna düþecek kullanýcýlarý da elemek için kontrol
		flag = 0;
		for(i=0;i<list->numVertices;i++){
			if(list->adjLists[i]->indegree<limit && deletedArray[i] == 0){//Limitin altýnda ise 
				flag = 1;
				tmp = list->adjLists[i]->next;
				while(tmp!=NULL){
					(list->adjLists[tmp->vertex-1]->indegree)--;		//O kullanýcýnýn takip ettiði kullanýcýlarýn indegree sayýsýný azaltýyor 
					tmp = tmp->next;
				}
				deletedArray[i] = 1;									//Limitin altýndaki kullanýcýnýn elendiði bilgisini dizide tutuyor
			}
		}	
	}	
	
}

void DFS(GRAPH *list, int dest, int *deletedArray, int *haveLink){	//Recursive DFS fonksiyonu
	
	NODE *tmp = list->adjLists[dest]->next;							//Parametrenin takip ettiði ilk düðüm geçici þekilde tmp'ye atanýyor
	if(deletedArray[dest] == 0){									//Eleme iþlemi yapýldýktan sonra hala iþlemde olup olmadýðý kontrol ediliyor
		haveLink[dest] = 1;											//Matrixin ilgili satýra oraya ulaþým olduðu bilgisini yazýyor. SET 1
		while(tmp != NULL){											//Takip ettiði kullanýcý bitinceye kadar ilerliyor
			if(haveLink[tmp->vertex-1] == 0){						//Eðer orasý ziyaret edilmemiþse DFS recursive bir þekilde baðlý olduðu kullanýcýnýn bilgisi ile çalýþýyor
				DFS(list,tmp->vertex-1,deletedArray,haveLink);
			}
			tmp = tmp->next;						
		}
	}
}


