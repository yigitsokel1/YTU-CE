#include<stdio.h>
#include<stdlib.h>
#define SIZE 100

int main(){
	
	int i, j;
	int n,m, control, count=0;;
	int matris[SIZE][SIZE];
	int bos[SIZE];
	
	printf("Matrisin once satir sonra sutun sayisini giriniz:");
	scanf("%d %d",&n,&m);
	
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			printf("Matris[%d][%d](0 veya 1 giriniz)=",i+1,j+1);
			scanf("%d",&matris[i][j]);
		}
	}
	
	printf("\nGirdi N=%d M=%d\n",n,m);
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			printf("%d\t",matris[i][j]);
		}
		printf("\n");
	}
	
	i=0;
	while(i<n){
		control = 0;
		for(j=0;j<m;j++){
			if(matris[i][j]==1){
				control = 1;
			}
		}
		if(control == 0)
			bos[count++] = i+1;
		i++;	
	}
	
	printf("\nCikti:");
	for(i=0;i<count-1;i++){
		printf("%d,",bos[i]);
	}
	printf("%d",bos[i]);
	
}
