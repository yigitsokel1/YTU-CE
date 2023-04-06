#include <stdio.h>
#define SIZE 10000

int main(int argc, char** argv) {
  	
        int A[SIZE];
        int i, n, tmp;
		int control = 0;   
        
        do{
        	printf("Dizinin eleman sayisini giriniz = ");
    		scanf("%d", &n);
    		
    		if(n<2)
    			printf("2 veya daha buyuk sayi giriniz!\n");
		}while(n < 2);
		
        printf("Elemanlari sirali giriniz!\n");               
        for(i = 0; i < n; i++){
        printf("Dizinin %d. elemanini giriniz = ", i+1);
                scanf("%d", &A[i]);
	    }
	    
		tmp=1;
	    
		while(tmp < n){
			if(A[tmp] - A[tmp-1] != 1){
				if(!control)
					printf("\nKayip Eleman(lar)\n");
				control = 1;
				for(i=A[tmp-1]+1; i<A[tmp]; i++)
					printf("%d\n",i);
			}
			tmp++;	
		}
			
		if(!control)
			printf("\nDizide kayip eleman yok!");
	            
        
	return 0;

}
  	
