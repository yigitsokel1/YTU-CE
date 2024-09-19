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
	
	//While döngüsü menü oluþumunu saðlýyor
	
	while(selection != 3) {
		printf("\nMenu:\n(1)Progami Baslat\n(2)Programi Calistirdiktan Sonra Analizler\n(3)Cikis\n");
		scanf("%d", &selection);
		if(selection ==1){
			
			//En kýsa yolu hesaplamak için nokta sayýsýný ve uzaklýklarýný kullanýcýdan alýyor
	
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
		
			/*Dijkstra Algoritmasý tek kaynaklý bir shortest path algoritmasý olduðu için
			hangi noktanýn ölçümünü yapcaðýný giriyor. */
			
		
			printf("Baslangic dugumunu giriniz = ");
			scanf("%d", &baslangic);
	
			surebas = clock();
			
			//Ortalama ve daha doðru bir zaman almak için algoritmayý 1000 kere çalýþtýrýyor.
			
			for(dongu=0;dongu<1000; dongu++){
				
				/*Düðümler arasýndaki uzaklýklarý matrise eþitliyor ve
				0 olan deðerlere sonsuz deðerini atýyor. */
	
				for(i=1; i<=n; i++){
					for(j=1; j<=n; j++){
						printf(" *");				//Yýldýz burdaki karmaþýklýðý ölçüyor.
						if(a[i][j] == 0)
							maliyet[i][j] = SONSUZ;
						else
							maliyet[i][j] = a[i][j];
					}
				}
				printf("\n");
	
				//Uzaklýk dizisine maliyet matrisindeki baþlangýç düðümünün diðer düðümlere olan uzaklýðýný atýyor.
				//Önceki düðüm dizisinin bütün deðerlerine baþlangýç düðümünün deðerini atýyor. Bu izlenilen yolu tutmamýz için yapýlýyor.
				//Ziyaret dizisinin bütün deðerlerine de 0 deðerini atýyor.Bu þu an için ziyaret edilen hiçbir noktanýn olmadðýný göstermek için yapýlýyor
	
				for(i=1; i<=n; i++){
					printf(" *");
					uzaklik[i] = maliyet[baslangic][i];
					oncekidugum[i] = baslangic;
					ziyaret[i] = 0;
				}
	
				printf("\n");
	
				uzaklik[baslangic] = 0;		//Baþlangýç düðümünün kendisine olan uzaklýðýný 0 yapýyor1
				ziyaret[baslangic]=1;		//Baþlangýç noktasýnýn ziyaret edildiði bilgisini veriyor
	
				/*Burda while döngüsü bütün deðerlerin uzaklýklarýnýn ölçülmesi için yapýlýyor. 
				Normalden 1 deðer az dönüyor çünkü ilk deðerlerin atamalarý yapýldý. */
	
				count = 1;					
				while(count < n){
					minuzaklik = SONSUZ;
					for(i=1; i<=n; i++){
						printf(" *");
						if(uzaklik[i] < minuzaklik && !ziyaret[i]){		//Uzaklýk deðerlerinin belirlenen minimum uzaklýktan küçük olup olmadýðý ve o noktanýn daha önce ziyaret
							minuzaklik = uzaklik[i];					//edilip edilmediði kontrol ediliyor. Eðer þartlar saðlanýyorsa yeni minimum deðerimize bu uzaklýk ekleniyor.
							sonrakidugum = i;							
						}												//Þartlarý saðlayan en optimum deðer bulunduktan sonra o noktanýn ziyaret edildiði, diziye iþleniyor.
					} 
					printf("\n");										
					ziyaret[sonrakidugum] = 1;
		
					for(i=1; i<=n; i++){
						printf(" *");
						/*Eðer ziyaret edilmeyen bir noktada; minimum uzaklýk ve belirlediðimiz sonraki düðümün uzaklýðýnýn toplamý
						baþlangýç düðümümüzün uzaklýklarýnndan küçükse, yeni uzaklýk deðerimiz bu iki deðerin toplamý olur.
						Önceki düðüm dizimizde de bu deðer atanýr.  */
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
	
			//Bu döngülerde baþlangýç düðümümüzün diðer düðümlere en kýsa yolu ve ilerledikleri yol ekrana yazdýrýlýr.
	
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
			
			/*Bütün istediðimiz deðerleri girdikten sonra karþýlaþtýrma yapabilmek için 
			bulduðumuz süreleri bir diziye atýyor */
			
			sure[k] = (long double)(surebit-surebas)/ (1000 * CLOCKS_PER_SEC);
			k++;
			sayac++;
		}
		
		else if(selection == 2){
			if(sayac >= 1){
		
				//Tuttuðumuz bütün deðerler için bir bar diyagramý yapýyor.
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
			
				//Elde ettiðimiz zamanýn ortalamasýný alýyor ve bunu þekillendiriyor.
			
				toplamsure = 0;
				for(k=0; k<sayac; k++)
					toplamsure = toplamsure + sure[k];
	
				ortsure = toplamsure / sayac;
				printf("Ort. sure   ");
	
				for(l=0; l<ortsure/2; l = l + 0.000001)
					printf("|");
				
				//Yýldýzlarla  hesapladýðýmýz karmaþýklýðý veriyor.	
		
				printf("\n\nKarmasiklik  = O(N^2)\n");
			}
			
			else
				printf("Analizler Icin Programi Calistiriniz!!");
		
		}
	
		//Programý sonlandýrma
		
		else if(selection==3){
			printf("Cikis Yapiliyor..\n");
		}
		
		//Menüdeki deðerlerden farklý bir deðer girme durumunda ekrana yazýrýyor
		
		else
			printf("Yanlis deger! Yeniden deneyiniz\n");
	}
	
	return 0;
	
}


