#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

int main(int argc,char *argv[]){
    srand(time(NULL));
    int n, i, j, toplam, adres1, adres2, count;
    int x1,y1,x2,y2;
    printf("Lutfen board icin 'n' degeri giriniz : ");
    scanf("%d",&n);
    int board[n][n];
	do{
		count = 0;
		for(i=0; i<n; i++){
        	for(j=0; j<n; j++){
            	board[i][j] = 10 * (rand() % n);
				if(board[i][j] == 0)
					count++; 
        	}
    	} 
	}while(count<2)   ; 
      
    printf("Board(Evler 0 olarak gosterilmektedir!)\n");    
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            printf("%3d ", board[i][j]);  
        }
        printf("\n");
    }
        printf("\n");

    printf("Baslangic noktasi icin bir ev koordinati giriniz(0-%d araliginda olmalidir.)(x y): ",n-1);
    scanf("%d %d",&x1,&y1);
    printf("Varis noktasi icin bir ev koordinati giriniz...(0-%d araliginda olmalidir.)(x y): ",n-1);
    scanf("%d %d",&x2,&y2);
    if(board[x1][y1] != 0){
        printf("Hatali koordinat girdiniz.");
    }
    if(board[x2][y2] != 0){
        printf("Hatali koordinat girdiniz.");
    }
    
    printf("\n1-Saga \n2-Sola\n3-Yukari\n4-Asagi\nHareketi temsil etmektedir.\n");
    adres1 = x2-x1;
    adres2 = y2-y1;
    toplam=0;

    printf("Current Place : %d %d\tBoard Value : %d \t Current Total : %d\n", x1, y1, board[x1][y1], toplam);
    while(x1 != x2 || y1 != y2){
    	if(adres1 > 0 && adres2 > 0){
    		if(min(board[x1][y1+1], board[x1+1][y1]) == board[x1+1][y1]){
    			x1++;
    			printf("Next Move: 4\n");
			}
    		else{
    			y1++;
    			printf("Next Move: 1\n");
			}
		}else if(adres1 > 0 && adres2 < 0){
    		if(min(board[x1+1][y1], board[x1][y1-1]) == board[x1+1][y1]){
    			x1++;
    			printf("Next Move: 4\n");
			}
    		else{
    			y1--;
    			printf("Next Move: 2\n");
			}
		}else if(adres1 < 0 && adres2 > 0){
    		if(min(board[x1-1][y1], board[x1][y1+1]) == board[x1-1][y1]){
    			x1--;
    			printf("Next Move: 3\n");
			}
    		else{
    			y1++;
    			printf("Next Move: 1\n");
			}
		}else if(adres1 < 0 && adres2 < 0){
    		if(min(board[x1][y1-1], board[x1-1][y1]) == board[x1-1][y1]){
    			x1--;
    			printf("Next Move: 3\n");
			}
    		else{
    			y1--;
    			printf("Next Move: 2\n");
			}
		}else if(adres1 > 0 && adres2 == 0){
			x1++;
			printf("Next Move: 4\n");
		}else if(adres1 < 0 && adres2 == 0){
			x1--;
			printf("Next Move: 3\n");
		}else if(adres1 == 0 && adres2 > 0){
			y1++;
			printf("Next Move: 1\n");
		}else if(adres1 == 0 && adres2 < 0){
			y1--;
			printf("Next Move: 1\n");
		}
    	adres1 = x2-x1;
    	adres2 = y2-y1;
    	toplam += board[x1][y1]; 
    	printf("Current Place : %d %d\tBoard Value : %d \t Current Total : %d\n", x1, y1, board[x1][y1], toplam);
	}

    
    return 0;
}

int min(int a, int b){
	if(a<b)
		return a;
	else
		return b;
}

