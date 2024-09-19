#include<stdio.h>

int main(){
	int selection;
	while(selection!=3){
		printf("\nMenu:\n(1) Seyrek Matristen Sikistirilmis Matrise\n(2) Sikistirilimis Matristen Seyrek Matrise\n(3) Cikis\nSelection : ");
		scanf("%d",&selection);
		if(selection==1){
			printf("\nMatrisin Boyutlarini Girin (Satir Sutun):");
			int satir, sutun;
			scanf("%d %d",&satir,&sutun);
			int i,j,sifirsayac=0;
			int seyrek[satir][sutun];
			printf("\nMatrisin Elemanlarini Giriniz\n");
			for(i=0;i<satir;i++){
				for(j=0;j<sutun;j++){
					printf("[%d][%d]: ",i,j);
					scanf("%d",&seyrek[i][j]);
				}
			}
			for(i=0;i<satir;i++){
				for(j=0;j<sutun;j++){
					if(seyrek[i][j]!=0){
						sifirsayac++;
					}
				}
			}
			int sikistirilmis[sifirsayac][3];
			int counter=0;
			for(i=0;i<satir;i++){
				for(j=0;j<sutun;j++){
					if(seyrek[i][j]!=0){
						sikistirilmis[counter][0]=i;
						sikistirilmis[counter][1]=j;
						sikistirilmis[counter][2]=seyrek[i][j];
						counter++;
					}
				}
			}
			
			printf("\nSikistirilmis Matris\n");
			for(i=0;i<sifirsayac;i++){
				printf("\n%d\t%d\t%d",sikistirilmis[i][0],sikistirilmis[i][1],sikistirilmis[i][2]);
			}
			printf("\n");
		}
		else if(selection==2){
			printf("Matriste Kac Tane Sifirdan Farkli Eleman Var (Sikistirilmis Matriste Satir Sayisi) : ");
			int satir;
			scanf("%d",&satir);
			int i,j;
			int sikistirilmis[satir][3];
			for(i=0;i<satir;i++){
				printf("%d. Eleman Icin Satir, Sutun ve Degeri Girin\n",i+1);
				scanf("%d %d %d",&sikistirilmis[i][0],&sikistirilmis[i][1],&sikistirilmis[i][2]);
			}
			int max=1;
			printf("\nSikistirilmis Matris\n");
			for(i=0;i<satir;i++){
				printf("\n%d\t%d\t%d",sikistirilmis[i][0],sikistirilmis[i][1],sikistirilmis[i][2]);
				if(sikistirilmis[i][0]>max){
					max=sikistirilmis[i][0];
				}
				else if(sikistirilmis[i][1]>max){
					max=sikistirilmis[i][1];
				}
			}
			int seyrek[max+1][max+1];
			for(i=0;i<max+1;i++){
				for(j=0;j<max+1;j++){
					seyrek[i][j]=0;
				}
			}
			
			for(i=0;i<satir;i++){
				seyrek[sikistirilmis[i][0]][sikistirilmis[i][1]]=sikistirilmis[i][2];
			}
			
			printf("\n\nSeyrek Matris: \n\n");
			for(i=0;i<max+1;i++){
				for(j=0;j<max+1;j++){
					printf("%d ",seyrek[i][j]);
				}
				printf("\n");
			}
			printf("\n");
		}
		else if(selection==3){
			printf("Cikis Yapiliyor..\n");
		}
		else{
			printf("Yanlis Deger! Yeniden Deneyin\n");
		}
		
		
	}
}
