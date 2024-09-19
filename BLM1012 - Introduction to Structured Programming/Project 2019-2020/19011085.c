#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#define MAX 100
#define SONSUZ 999999


int main()
{
	clock_t surebas, surebit;
	long double sure[MAX], ortsure, toplamsure, l;
	int i, j, k, selection, count, n, baslangic, sayac ,sonrakidugum, dongu;
	long maliyet[MAX][MAX], uzaklik[MAX], minuzaklik, a[MAX][MAX];
	int ziyaret[MAX], oncekidugum[MAX];
	sayac = 0;
	k=0;
	
	//While d�ng�s� men� olu�umunu sa�l�yor
	
	while(selection != 3) {
		printf("\nMenu:\n(1)Progami Baslat\n(2)Programi Calistirdiktan Sonra Analizler\n(3)Cikis\n");
		scanf("%d", &selection);
		if(selection ==1){
			
			//En k�sa yolu hesaplamak i�in nokta say�s�n� ve uzakl�klar�n� kullan�c�dan al�yor
	
			printf("Dugum sayisini giriniz = ");
			scanf("%d", &n);
	
			for(i=1; i<=n; i++){
				for(j=1; j<=n; j++){
					if(i != j){
					printf("%d.dugumun %d.dugume uzakligini giriniz(Baglanti yoksa 0 giriniz) =", i, j);
					scanf("%ld", &a[i][j]);
					}
					else
						a[i][j]=0;
				}
			}	
		
			/*Dijkstra Algoritmas� tek kaynakl� bir shortest path algoritmas� oldu�u i�in
			hangi noktan�n �l��m�n� yapca��n� giriyor. */
			
		
			printf("Baslangic dugumunu giriniz = ");
			scanf("%d", &baslangic);
	
			surebas = clock();
			
			//Ortalama ve daha do�ru bir zaman almak i�in algoritmay� 1000 kere �al��t�r�yor.
			
			for(dongu=0;dongu<1000; dongu++){
				
				/*D���mler aras�ndaki uzakl�klar� matrise e�itliyor ve
				0 olan de�erlere sonsuz de�erini at�yor. */
	
				for(i=1; i<=n; i++){
					for(j=1; j<=n; j++){
						printf(" *");				//Y�ld�z burdaki karma��kl��� �l��yor.
						if(a[i][j] == 0)
							maliyet[i][j] = SONSUZ;
						else
							maliyet[i][j] = a[i][j];
					}
				}
				printf("\n");
	
				//Uzakl�k dizisine maliyet matrisindeki ba�lang�� d���m�n�n di�er d���mlere olan uzakl���n� at�yor.
				//�nceki d���m dizisinin b�t�n de�erlerine ba�lang�� d���m�n�n de�erini at�yor. Bu izlenilen yolu tutmam�z i�in yap�l�yor.
				//Ziyaret dizisinin b�t�n de�erlerine de 0 de�erini at�yor.Bu �u an i�in ziyaret edilen hi�bir noktan�n olmad��n� g�stermek i�in yap�l�yor
	
				for(i=1; i<=n; i++){
					printf(" *");
					uzaklik[i] = maliyet[baslangic][i];
					oncekidugum[i] = baslangic;
					ziyaret[i] = 0;
				}
	
				printf("\n");
	
				uzaklik[baslangic] = 0;		//Ba�lang�� d���m�n�n kendisine olan uzakl���n� 0 yap�yor1
				ziyaret[baslangic]=1;		//Ba�lang�� noktas�n�n ziyaret edildi�i bilgisini veriyor
	
				/*Burda while d�ng�s� b�t�n de�erlerin uzakl�klar�n�n �l��lmesi i�in yap�l�yor. 
				Normalden 1 de�er az d�n�yor ��nk� ilk de�erlerin atamalar� yap�ld�. */
	
				count = 1;					
				while(count < n){
					minuzaklik = SONSUZ;
					for(i=1; i<=n; i++){
						printf(" *");
						if(uzaklik[i] < minuzaklik && !ziyaret[i]){		//Uzakl�k de�erlerinin belirlenen minimum uzakl�ktan k���k olup olmad��� ve o noktan�n daha �nce ziyaret
							minuzaklik = uzaklik[i];					//edilip edilmedi�i kontrol ediliyor. E�er �artlar sa�lan�yorsa yeni minimum de�erimize bu uzakl�k ekleniyor.
							sonrakidugum = i;							
						}												//�artlar� sa�layan en optimum de�er bulunduktan sonra o noktan�n ziyaret edildi�i, diziye i�leniyor.
					} 
					printf("\n");										
					ziyaret[sonrakidugum] = 1;
		
					for(i=1; i<=n; i++){
						printf(" *");
						/*E�er ziyaret edilmeyen bir noktada; minimum uzakl�k ve belirledi�imiz sonraki d���m�n uzakl���n�n toplam�
						ba�lang�� d���m�m�z�n uzakl�klar�nndan k���kse, yeni uzakl�k de�erimiz bu iki de�erin toplam� olur.
						�nceki d���m dizimizde de bu de�er atan�r.  */
						if(ziyaret[i] == 0){										
							if(minuzaklik + maliyet[sonrakidugum][i] < uzaklik[i]){
								uzaklik[i] = minuzaklik + maliyet[sonrakidugum][i];
								oncekidugum[i] = sonrakidugum;
							}
						}
					}
		
					count++;
				}
				printf("\n \n");
			
		
			}
	
			//Bu d�ng�lerde ba�lang�� d���m�m�z�n di�er d���mlere en k�sa yolu ve ilerledikleri yol ekrana yazd�r�l�r.
	
			for(i=1; i<=n; i++){
				printf(" *");
				if(i != baslangic){
					printf("%d.dugume uzakligi = %ld\n",i, uzaklik[i]);
					printf("Gidilen yol : %d ", i);
			
					j = i;
					while(j != baslangic){
						printf(" *");
						j = oncekidugum[j];
						printf("<-- %d ", j);
					}
				}
		
				printf("\n");
			}	
			printf("\n \n");
			
			
			surebit = clock();
			
			printf("\n Algoritmanin calisma suresi(mikrosaniye) = %Lf \n \n", ((long double)(surebit-surebas)/(1000 * CLOCKS_PER_SEC)));
			
			/*B�t�n istedi�imiz de�erleri girdikten sonra kar��la�t�rma yapabilmek i�in 
			buldu�umuz s�releri bir diziye at�yor */
			
			sure[k] = (long double)(surebit-surebas)/ (1000 * CLOCKS_PER_SEC);
			k++;
			sayac++;
		}
		
		else if(selection == 2){
			if(sayac >= 1){
		
				//Tuttu�umuz b�t�n de�erler i�in bir bar diyagram� yap�yor.
				printf("Algoritmanin Calisma Suresinin Bar Diagrami\n");
				k=0;
				while(k<sayac){
					printf("%d.degerler  ", k+1);
					for(l=0; l<sure[k]/2; l = l  + 0.000001){
						printf("|");
					}
					printf("\n");
					k++;
				}
			
				//Elde etti�imiz zaman�n ortalamas�n� al�yor ve bunu �ekillendiriyor.
			
				toplamsure = 0;
				for(k=0; k<sayac; k++)
					toplamsure = toplamsure + sure[k];
	
				ortsure = toplamsure / sayac;
				printf("Ort. sure   ");
	
				for(l=0; l<ortsure/2; l = l + 0.000001)
					printf("|");
				
				//Y�ld�zlarla  hesaplad���m�z karma��kl��� veriyor.	
		
				printf("\n\nKarmasiklik  = O(N^2)\n");
			}
			
			else
				printf("Analizler Icin Programi Calistiriniz!!");
		
		}
	
		//Program� sonland�rma
		
		else if(selection==3){
			printf("Cikis Yapiliyor..\n");
		}
		
		//Men�deki de�erlerden farkl� bir de�er girme durumunda ekrana yaz�r�yor
		
		else
			printf("Yanlis deger! Yeniden deneyiniz\n");
	}
	
	return 0;
	
}


