#include<stdio.h>
#include<stdlib.h>
#include <time.h>

int main(){


	int randomnumber, basamak, i=4, poz, neg, j;
	int sayi = 0, random[5], sayibas[5];
	
	srand(time(NULL));
	randomnumber = 3000 + rand() % 1000;
	basamak = randomnumber;
	
	while(i  > 0){
		random[i] = basamak % 10;
		basamak = basamak - random[i];
		basamak = basamak / 10;
		i--;
	}
	
	printf("%d\n", randomnumber);
	for(i=1;i<5;i++){
		printf("%d     ", random[i]);
	}
		
	
	
	
	while(sayi != randomnumber){
		poz = 0;
		neg = 0;
		printf("Lutfen tahminini giriniz = ");
		scanf("%d",&sayi);
		basamak = sayi;
		i = 4;
		while(i > 0){
		sayibas[i] = basamak % 10;
		basamak = basamak / 10;
		i--;
		}
		
		for(i = 1; i<5; i++){
			for(j = 1; j<5; j++){
				if(random[i]==sayibas[j]){
					if(i == j)
						poz++;
					else
						neg++;
				}
			}
		}
		
		printf("+%d -- -%d\n", poz, neg);
	}
	
	 
	
	printf("Dogru sonuca ulastiniz!!\n");


}
