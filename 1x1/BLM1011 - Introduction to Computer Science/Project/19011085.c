#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#define SIZE 100

int main(){
	
	srand(time(NULL));
	int selection,tmp,door,controlMemory;
	int table[SIZE][SIZE],easyMemory[6],mediumMemory[18],hardMemory[48];
	int i,j,n;
	int value=1,sira=1,count=0,userMove=0,userPoint=0,control=0,computerMove=0,computerPoint=0;
	int guessrow1, guessrow2, guesscolumn1,guesscolumn2;
	
	printf("Menu(Oyun Zorlugunu Seciniz)\n1.Kolay Mod\n2.Orta Mod\n3.Zor Mod\nSeciminiz:");
	scanf("%d",&selection);
	
	 
	
		
		if(selection==1){
			n=4;
			for(i=0;i<n;i++){
				for(j=0;j<=n-2;j=j+2){
					table[i][j]=value;
					table[i][j+1]=value++;
				}
			}
		
		
			for(i=0;i<50;i++){
				guessrow1 = rand() % n;
				guessrow2 = rand() % n;
				guesscolumn1 = rand() % n;
				guesscolumn2 = rand() % n;
				
				tmp = table[guessrow1][guesscolumn1];
				table[guessrow1][guesscolumn1] = table[guessrow2][guesscolumn2];
				table[guessrow2][guesscolumn2] = tmp;
			}
			
			for(i=0;i<6;i++){
				easyMemory[i] = 100; 
			}
				
				
			printf("\nKoordinatlar\n\t\t");
			for(i=0;i<n;i++)
				printf("%d.sutun\t",i+1);
			for(i=0;i<n;i++){
				printf("\n%d.satir\t\t",i+1);
				for(j=0;j<n;j++){
					printf("%d\t",table[i][j]);
				}
				printf("\n");
			}
			
			printf("\nOyun Basliyor!!\n");
			printf("\nKoordinatlar\n\t\t");
			for(i=0;i<n;i++)
				printf("%d.sutun\t",i+1);
			for(i=0;i<n;i++){
				printf("\n%d.satir\t\t",i+1);
				for(j=0;j<n;j++){
					printf("*\t");
				}
				printf("\n");
			}
			
			while(control != n*n){
				while(sira == 1 && control != n*n){
					do{
					printf("1.tahmininiz icin satir ve sutun numarasini giriniz:");
					scanf("%d %d",&guessrow1,&guesscolumn1);
					printf("%d,%d = %d\n",guessrow1,guesscolumn1,table[guessrow1-1][guesscolumn1-1]);					
					printf("2.tahmininiz icin satir ve sutun numarasini giriniz:");
					scanf("%d %d",&guessrow2,&guesscolumn2);
					printf("%d,%d = %d\n",guessrow2,guesscolumn2,table[guessrow2-1][guesscolumn2-1]);
						if(table[guessrow1-1][guesscolumn1-1]==0 || table[guessrow2-1][guesscolumn2-1]==0)
							printf("Hatali deger girdiniz! Lutfen yeni deger giriniz!\n");
					}while(table[guessrow1-1][guesscolumn1-1]==0 || table[guessrow2-1][guesscolumn2-1]==0);


					
					if(table[guessrow1-1][guesscolumn1-1]==table[guessrow2-1][guesscolumn2-1]){
						table[guessrow1-1][guesscolumn1-1] = 0;
						table[guessrow2-1][guesscolumn2-1] = 0;
						control = control + 2;
						userPoint++;
						printf("\nKoordinatlar\n\t\t");
						for(i=0;i<n;i++)
							printf("%d.sutun\t",i+1);
						for(i=0;i<n;i++){
							printf("\n%d.satir\t\t",i+1);
							for(j=0;j<n;j++){
								if(table[i][j]!=0)
									printf("*\t");
								else
									printf("-\t");	
							}
							printf("\n");
							if(userPoint==5)
								control = n*n;
						}
					}
					else{
						sira = 0;
						printf("\nSira Bilgisayarda!\n\n");
						easyMemory[count++] = guessrow1;
						easyMemory[count++] = guesscolumn1;
						easyMemory[count++] = table[guessrow1-1][guesscolumn1-1];
						easyMemory[count++] = guessrow2;
						easyMemory[count++] = guesscolumn2;
						easyMemory[count++] = table[guessrow2-1][guesscolumn2-1];
						count = 0;
					}
						
					userMove++;	
				}
				
				while(sira == 0 && control != n*n){
					
					printf("Bilgisayar tahmini icin ilk koordinati girer:\n");
					do{
						guessrow1 = 1 + rand() % n;
						guesscolumn1 =1 + rand() % n;
						for(i=0;i<=3;i=i+3){
							while(guessrow1 == easyMemory[i] && guesscolumn1 == easyMemory[i+1]){
								guessrow1 = 1 + rand() % n;
								guesscolumn1 = 1 + rand() % n;
								i=0;
							}
						}
					}while(table[guessrow1-1][guesscolumn1-1] == 0);
					
					printf("%d,%d = %d\n",guessrow1,guesscolumn1,table[guessrow1-1][guesscolumn1-1]);
					
					door = 0;
					for(i=2;i<=5;i=i+3){
						if(table[guessrow1-1][guesscolumn1-1]==easyMemory[i]){
							printf("\nBilgisayar hafizasindaki degeri girer:\n%d,%d = %d",easyMemory[i-2],easyMemory[i-1],easyMemory[i]);
							table[guessrow1-1][guesscolumn1-1] = 0;
							table[easyMemory[i-2]-1][easyMemory[i-1]-1] = 0;
							control = control+2;
							computerPoint++;
							door = 1;
							printf("\nKoordinatlar\n\t\t");
							for(i=0;i<n;i++)
								printf("%d.sutun\t",i+1);
							for(i=0;i<n;i++){
								printf("\n%d.satir\t\t",i+1);
								for(j=0;j<n;j++){
									if(table[i][j]!=0)
										printf("*\t");
									else
										printf("-\t");	
								}
								printf("\n");
							}
							if(computerPoint==5)
								control = n*n;
						}
					}
					
					if(door!=1){
						
						printf("Bilgisayar tahmini icin ikinci koordinati girer\n");
						do{
							guessrow2 = 1 + rand() % n;
							guesscolumn2 =1 + rand() % n;
						}while(table[guessrow2-1][guesscolumn2-1] == 0 || (guessrow2 == guessrow1 && guesscolumn2 == guesscolumn1));
						printf("%d,%d = %d\n",guessrow2,guesscolumn2, table[guessrow2-1][guesscolumn2-1]);
						if(table[guessrow1-1][guesscolumn1-1] == table[guessrow2-1][guesscolumn2-1]){
							table[guessrow1-1][guesscolumn1-1] = 0;
							table[guessrow2-1][guesscolumn2-1] = 0;
							control = control+2;
							computerPoint++;
							printf("\nKoordinatlar\n\t\t");
							for(i=0;i<n;i++)
								printf("%d.sutun\t",i+1);
							for(i=0;i<n;i++){
								printf("\n%d.satir\t\t",i+1);
								for(j=0;j<n;j++){
									if(table[i][j]!=0)
										printf("*\t");
									else
										printf("-\t");	
								}
								printf("\n");
							}
							if(computerPoint==5)
								control = n*n;
						}
						else{
							sira = 1;
							printf("\nSira Oyuncuda!\n\n");
						}
							
					}
					computerMove++;		
				}
				
				
			}
			
			if(userPoint>computerPoint)
				printf("Kazanan oyuncu!\n");
			else if(userPoint<computerPoint)
				printf("Kazanan bilgisayar!\n");
			else
				printf("Berabere!!\n");	
			printf("Oyuncunun Hamle Sayisi : %d\nBilgisayarin Hamle Sayisi : %d\nOyuncunun Puani : %d\nBilgisayarin Puani : %d\n",userMove,computerMove,userPoint,computerPoint);
			
		}
		
		else if(selection==2){
			n=6;
			for(i=0;i<n;i++){
				for(j=0;j<=n-2;j=j+2){
					table[i][j]=value;
					table[i][j+1]=value++;
				}
			}
		
		
			for(i=0;i<50;i++){
				guessrow1 = rand() % n;
				guessrow2 = rand() % n;
				guesscolumn1 = rand() % n;
				guesscolumn2 = rand() % n;
				
				tmp = table[guessrow1][guesscolumn1];
				table[guessrow1][guesscolumn1] = table[guessrow2][guesscolumn2];
				table[guessrow2][guesscolumn2] = tmp;
			}
		
			for(i=0;i<18;i++){
				mediumMemory[i] = 100;
			}
				
				
			printf("\nKoordinatlar\n\t\t");
			for(i=0;i<n;i++)
				printf("%d.sutun\t",i+1);
			for(i=0;i<n;i++){
				printf("\n%d.satir\t\t",i+1);
				for(j=0;j<n;j++){
					printf("%d\t",table[i][j]);
				}
				printf("\n");
			}
		
			printf("\nOyun Basliyor!!\n");
			printf("\nKoordinatlar\n\t\t");
			for(i=0;i<n;i++)
				printf("%d.sutun\t",i+1);
			for(i=0;i<n;i++){
				printf("\n%d.satir\t\t",i+1);
				for(j=0;j<n;j++){
					printf("*\t");
				}
				printf("\n");
			}
			
			while(control != n*n){
				while(sira == 1 && control != n*n){
					do{
					printf("1.tahmininiz icin satir ve sutun numarasini giriniz:");
					scanf("%d %d",&guessrow1,&guesscolumn1);
					printf("%d,%d = %d\n",guessrow1,guesscolumn1,table[guessrow1-1][guesscolumn1-1]);					
					printf("2.tahmininiz icin satir ve sutun numarasini giriniz:");
					scanf("%d %d",&guessrow2,&guesscolumn2);
					printf("%d,%d = %d\n",guessrow2,guesscolumn2,table[guessrow2-1][guesscolumn2-1]);	
						if(table[guessrow1-1][guesscolumn1-1]==0 || table[guessrow2-1][guesscolumn2-1]==0)
							printf("Hatali deger girdiniz! Lutfen yeni deger giriniz!\n");
					}while(table[guessrow1-1][guesscolumn1-1]==0 || table[guessrow2-1][guesscolumn2-1]==0);


					if(table[guessrow1-1][guesscolumn1-1]==table[guessrow2-1][guesscolumn2-1]){
						table[guessrow1-1][guesscolumn1-1] = 0;
						table[guessrow2-1][guesscolumn2-1] = 0;
						control = control + 2;
						userPoint++;
						printf("\nKoordinatlar\n\t\t");
						for(i=0;i<n;i++)
							printf("%d.sutun\t",i+1);
						for(i=0;i<n;i++){
							printf("\n%d.satir\t\t",i+1);
							for(j=0;j<n;j++){
								if(table[i][j]!=0)
									printf("*\t");
								else
									printf("-\t");	
							}
							printf("\n");
						}
						if(userPoint==10)
							control = n*n;
					}
					else{
						sira = 0;
						printf("\nSira Bilgisayarda!\n\n");
						if(count > 17)
							count = 0;
						controlMemory=0;
						for(i=2;i<=17;i=i+3){
							if(mediumMemory[i]==table[guessrow1-1][guesscolumn1-1])
								controlMemory=1;
						}
						if(controlMemory==0){
							mediumMemory[count++] = guessrow1;
							mediumMemory[count++] = guesscolumn1;
							mediumMemory[count++] = table[guessrow1-1][guesscolumn1-1];
						}
						if(count > 17)
							count = 0;
						controlMemory=0;
						for(i=2;i<=17;i=i+3){
							if(mediumMemory[i]==table[guessrow2-1][guesscolumn2-1])
								controlMemory=1;
						}
						if(controlMemory==0){
							mediumMemory[count++] = guessrow2;
							mediumMemory[count++] = guesscolumn2;
							mediumMemory[count++] = table[guessrow2-1][guesscolumn2-1];
						}
					}
						
					userMove++;	
				}
				
				while(sira == 0 && control != n*n){
					
					printf("Bilgisayar tahmini icin ilk koordinati girer:\n");
					do{
						guessrow1 = 1 + rand() % n;
						guesscolumn1 =1 + rand() % n;
						for(i=0;i<=15;i=i+3){
							while(guessrow1 == mediumMemory[i] && guesscolumn1 == mediumMemory[i+1]){
								guessrow1 = 1 + rand() % n;
								guesscolumn1 = 1 + rand() % n;
								i=0;
							}
						}
					}while(table[guessrow1-1][guesscolumn1-1] == 0);
					
					printf("%d,%d = %d\n",guessrow1,guesscolumn1,table[guessrow1-1][guesscolumn1-1]);
					
					door = 0;
					for(i=2;i<=17;i=i+3){
						if(table[guessrow1-1][guesscolumn1-1]==mediumMemory[i]){
							printf("\nBilgisayar hafizasindaki degeri girer:\n%d,%d = %d",mediumMemory[i-2],mediumMemory[i-1],mediumMemory[i]);
							table[guessrow1-1][guesscolumn1-1] = 0;
							table[mediumMemory[i-2]-1][mediumMemory[i-1]-1] = 0;
							control = control+2;
							computerPoint++;
							door = 1;
							printf("\nKoordinatlar\n\t\t");
							for(i=0;i<n;i++)
								printf("%d.sutun\t",i+1);
							for(i=0;i<n;i++){
								printf("\n%d.satir\t\t",i+1);
								for(j=0;j<n;j++){
									if(table[i][j]!=0)
										printf("*\t");
									else
										printf("-\t");	
								}
								printf("\n");
							}
							if(computerPoint==10)
								control = n*n;
						}
					}
					
					if(door!=1){
						
						printf("Bilgisayar tahmini icin ikinci koordinati girer\n");
						do{
							guessrow2 = 1 + rand() % n;
							guesscolumn2 =1 + rand() % n;
						}while(table[guessrow2-1][guesscolumn2-1] == 0 || (guessrow2 == guessrow1 && guesscolumn2 == guesscolumn1));
						printf("%d,%d = %d\n",guessrow2,guesscolumn2, table[guessrow2-1][guesscolumn2-1]);
						if(table[guessrow1-1][guesscolumn1-1] == table[guessrow2-1][guesscolumn2-1]){
							table[guessrow1-1][guesscolumn1-1] = 0;
							table[guessrow2-1][guesscolumn2-1] = 0;
							control = control+2;
							computerPoint++;
							printf("\nKoordinatlar\n\t\t");
							for(i=0;i<n;i++)
								printf("%d.sutun\t",i+1);
							for(i=0;i<n;i++){
								printf("\n%d.satir\t\t",i+1);
								for(j=0;j<n;j++){
									if(table[i][j]!=0)
										printf("*\t");
									else
										printf("-\t");	
								}
								printf("\n");
							}
							if(computerPoint==5)
								control = n*n;
						}
						else{
							sira = 1;
							if(count > 17)
								count = 0;
							controlMemory=0;
							for(i=2;i<=17;i=i+3){
								if(mediumMemory[i]==table[guessrow1-1][guesscolumn1-1])
									controlMemory=1;
							}
							if(controlMemory==0){
								mediumMemory[count++] = guessrow1;
								mediumMemory[count++] = guesscolumn1;
								mediumMemory[count++] = table[guessrow1-1][guesscolumn1-1];
							}
						
							if(count > 17)
								count = 0;
							controlMemory=0;
							for(i=2;i<=17;i=i+3){
								if(mediumMemory[i]==table[guessrow2-1][guesscolumn2-1])
									controlMemory=1;
							}
							if(controlMemory==0){
								mediumMemory[count++] = guessrow2;
								mediumMemory[count++] = guesscolumn2;
								mediumMemory[count++] = table[guessrow2-1][guesscolumn2-1];
							}

							printf("\nSira Oyuncuda!\n\n");
						}
							
					}
					computerMove++;		
				}
				
				
			}
			
			if(userPoint>computerPoint)
				printf("Kazanan oyuncu!\n");
			else if(userPoint<computerPoint)
				printf("Kazanan bilgisayar!\n");
			else
				printf("Berabere!!\n");	
			printf("Oyuncunun Hamle Sayisi : %d\nBilgisayarin Hamle Sayisi : %d\nOyuncunun Puani : %d\nBilgisayarin Puani : %d\n",userMove,computerMove,userPoint,computerPoint);			
		}
	
	
		else if(selection==3){
			n=8;
			for(i=0;i<n;i++){
				for(j=0;j<=n-2;j=j+2){
					table[i][j]=value;
					table[i][j+1]=value++;
				}
			}
		
		
			for(i=0;i<50;i++){
				guessrow1 = rand() % n;
				guessrow2 = rand() % n;
				guesscolumn1 = rand() % n;
				guesscolumn2 = rand() % n;
				
				tmp = table[guessrow1][guesscolumn1];
				table[guessrow1][guesscolumn1] = table[guessrow2][guesscolumn2];
				table[guessrow2][guesscolumn2] = tmp;
			}
		
			for(i=0;i<18;i++){
				hardMemory[i] = 100;
			}
				
				
			printf("\nKoordinatlar\n\t\t");
			for(i=0;i<n;i++)
				printf("%d.sutun\t",i+1);
			for(i=0;i<n;i++){
				printf("\n%d.satir\t\t",i+1);
				for(j=0;j<n;j++){
					printf("%d\t",table[i][j]);
				}
				printf("\n");
			}
		
			printf("\nOyun Basliyor!!\n");
			printf("\nKoordinatlar\n\t\t");
			for(i=0;i<n;i++)
				printf("%d.sutun\t",i+1);
			for(i=0;i<n;i++){
				printf("\n%d.satir\t\t",i+1);
				for(j=0;j<n;j++){
					printf("*\t");
				}
				printf("\n");
			}
			
			while(control != n*n){
				while(sira == 1 && control != n*n){
					do{
					printf("1.tahmininiz icin satir ve sutun numarasini giriniz:");
					scanf("%d %d",&guessrow1,&guesscolumn1);
					printf("%d,%d = %d\n",guessrow1,guesscolumn1,table[guessrow1-1][guesscolumn1-1]);					
					printf("2.tahmininiz icin satir ve sutun numarasini giriniz:");
					scanf("%d %d",&guessrow2,&guesscolumn2);
					printf("%d,%d = %d\n",guessrow2,guesscolumn2,table[guessrow2-1][guesscolumn2-1]);
						if(table[guessrow1-1][guesscolumn1-1]==0 || table[guessrow2-1][guesscolumn2-1]==0)
							printf("Hatali deger girdiniz! Lutfen yeni deger giriniz!\n");
					}while(table[guessrow1-1][guesscolumn1-1]==0 || table[guessrow2-1][guesscolumn2-1]==0);

						
						
					if(table[guessrow1-1][guesscolumn1-1]==table[guessrow2-1][guesscolumn2-1]){
						table[guessrow1-1][guesscolumn1-1] = 0;
						table[guessrow2-1][guesscolumn2-1] = 0;
						control = control + 2;
						userPoint++;
						printf("\nKoordinatlar\n\t\t");
						for(i=0;i<n;i++)
							printf("%d.sutun\t",i+1);
						for(i=0;i<n;i++){
							printf("\n%d.satir\t\t",i+1);
							for(j=0;j<n;j++){
								if(table[i][j]!=0)
									printf("*\t");
								else
									printf("-\t");	
							}
							printf("\n");
						}
						if(userPoint==17)
								control = n*n;
					}
					else{
						sira = 0;
						printf("\nSira Bilgisayarda!\n\n");
						if(count > 47)
							count = 0;
						for(i=2;i<=47;i=i+3){
							if(hardMemory[i]==table[guessrow1-1][guesscolumn1-1])
								controlMemory=1;
						}
						if(controlMemory==0){
							hardMemory[count++] = guessrow1;
							hardMemory[count++] = guesscolumn1;
							hardMemory[count++] = table[guessrow1-1][guesscolumn1-1];
						}
						if(count > 47)
							count = 0;
						controlMemory=0;
						for(i=2;i<=47;i=i+3){
							if(hardMemory[i]==table[guessrow2-1][guesscolumn2-1])
								controlMemory=1;
						}
						if(controlMemory==0){
							hardMemory[count++] = guessrow2;
							hardMemory[count++] = guesscolumn2;
							hardMemory[count++] = table[guessrow2-1][guesscolumn2-1];
						}
					}
						
					userMove++;	
				}
				
				while(sira == 0 && control != n*n){
					
					printf("Bilgisayar tahmini icin ilk koordinati girer:\n");
					do{
						guessrow1 = 1 + rand() % n;
						guesscolumn1 =1 + rand() % n;
						for(i=0;i<=45;i=i+3){
							while(guessrow1 == hardMemory[i] && guesscolumn1 == hardMemory[i+1]){
								guessrow1 = 1 + rand() % n;
								guesscolumn1 = 1 + rand() % n;
								i=0;
							}
						}
					}while(table[guessrow1-1][guesscolumn1-1] == 0);
					
					printf("%d,%d = %d\n",guessrow1,guesscolumn1,table[guessrow1-1][guesscolumn1-1]);
					
					door = 0;
					for(i=2;i<=47;i=i+3){
						if(table[guessrow1-1][guesscolumn1-1]==hardMemory[i]){
							printf("\nBilgisayar hafizasindaki degeri girer:\n%d,%d = %d",hardMemory[i-2],hardMemory[i-1],hardMemory[i]);
							table[guessrow1-1][guesscolumn1-1] = 0;
							table[hardMemory[i-2]-1][hardMemory[i-1]-1] = 0;
							control = control+2;
							computerPoint++;
							door = 1;
							printf("\nKoordinatlar\n\t\t");
							for(i=0;i<n;i++)
								printf("%d.sutun\t",i+1);
							for(i=0;i<n;i++){
								printf("\n%d.satir\t\t",i+1);
								for(j=0;j<n;j++){
									if(table[i][j]!=0)
										printf("*\t");
									else
										printf("-\t");	
								}
								printf("\n");
							}
							if(computerPoint==17)
								control = n*n;
							break;
						}
					}
					
					if(door!=1){
						
						printf("Bilgisayar tahmini icin ikinci koordinati girer\n");
						do{
							guessrow2 = 1 + rand() % n;
							guesscolumn2 =1 + rand() % n;
						}while(table[guessrow2-1][guesscolumn2-1] == 0 || (guessrow2 == guessrow1 && guesscolumn2 == guesscolumn1));
						printf("%d,%d = %d\n",guessrow2,guesscolumn2, table[guessrow2-1][guesscolumn2-1]);
						if(table[guessrow1-1][guesscolumn1-1] == table[guessrow2-1][guesscolumn2-1]){
							table[guessrow1-1][guesscolumn1-1] = 0;
							table[guessrow2-1][guesscolumn2-1] = 0;
							control = control+2;
							computerPoint++;
							printf("\nKoordinatlar\n\t\t");
							for(i=0;i<n;i++)
								printf("%d.sutun\t",i+1);
							for(i=0;i<n;i++){
								printf("\n%d.satir\t\t",i+1);
								for(j=0;j<n;j++){
									if(table[i][j]!=0)
										printf("*\t");
									else
										printf("-\t");	
								}
								printf("\n");
							}
							if(computerPoint==17)
								control = n*n;
						}
						else{
							sira = 1;
							if(count > 47)
								count = 0;
							controlMemory=0;
							for(i=2;i<=47;i=i+3){
								if(hardMemory[i]==table[guessrow1-1][guesscolumn1-1])
									controlMemory=1;
							}
							if(controlMemory==0){
								hardMemory[count++] = guessrow1;
								hardMemory[count++] = guesscolumn1;
								hardMemory[count++] = table[guessrow1-1][guesscolumn1-1];
							}
						
							if(count > 47)
								count = 0;
							controlMemory=0;
							for(i=2;i<=47;i=i+3){
								if(hardMemory[i]==table[guessrow2-1][guesscolumn2-1])
									controlMemory=1;
							}
							if(controlMemory==0){
								hardMemory[count++] = guessrow2;
								hardMemory[count++] = guesscolumn2;
								hardMemory[count++] = table[guessrow2-1][guesscolumn2-1];
							}
						

							printf("\nSira Oyuncuda!\n\n");
						}
							
					}
					computerMove++;		
				}
				
				
			}
			
			if(userPoint>computerPoint)
				printf("Kazanan oyuncu!\n");
			else if(userPoint<computerPoint)
				printf("Kazanan bilgisayar!\n");
			else
				printf("Berabere!!\n");	
			printf("Oyuncunun Hamle Sayisi : %d\nBilgisayarin Hamle Sayisi : %d\nOyuncunun Puani : %d\nBilgisayarin Puani : %d\n",userMove,computerMove,userPoint,computerPoint);				
		}	
		
		else
			printf("Hatali Tuslama Yaptiniz!Lutfen Programi Yeniden Baslatiniz!!!!");
	
	return 1;
	
}
