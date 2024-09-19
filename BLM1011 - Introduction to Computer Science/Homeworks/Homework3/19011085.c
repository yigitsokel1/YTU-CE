#include<stdio.h>
#include<stdlib.h>
#define MAX 5000

int main(){
	FILE *fp;
	char text[MAX], duzen[MAX];
	int i=0, j=0, count=1;
	
	if((fp = fopen ("soru.txt", "r")) == NULL){
		printf("Dosya acma hatasi!");
		return -1;
	}
	
	fgets(text, MAX-1, fp);
	printf("%s\n", text);
	

	
	while(text[i] != '\0'){
		if((text[i] == 32) && (text[i+1] == 32)){
			i++;
		}
		else if((text[i] == 32) && (text[i+1] == '\0')){
			i++;
		}
	
		else{
			duzen[j] = text[i];
			i++;
			j++;
		}
	}
	
	i=0;
	while(duzen[i] != '\0'){
		if(duzen[i] == 32 && ((97 <= duzen[i+1]) && (122 >= duzen[i+1]))){
			count++;
		}
		i++;
	}
	printf("\nKelime sayisi = %d\n", count);
	printf("%s\n", duzen);
	
}


