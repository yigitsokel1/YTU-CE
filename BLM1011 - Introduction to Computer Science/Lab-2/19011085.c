#include<stdio.h>
#include<stdlib.h>
#define MAX 5000

int main(){
	char text[MAX];
	int i=0;
	
	
	printf("Input: ");
	gets(text);
	
	
	
	if(((97 <= text[i]) && (122 >= text[i]))){
			text[i] = text[i] - 32;
		}
	else if(text[i]==32 && ((97 <= text[i]) && (122 >= text[i]))){
		text[i+1] = text[i+1] - 32;
	}

	
	while(text[i] != '\0'){
	
		if(text[i] == 46 && ((97 <= text[i+1]) && (122 >= text[i+1]))){
			text[i+1] = text[i+1] - 32;
		}
		
		else if(text[i] == 46 && text[i+1] == 32){
			if(((97 <= text[i+2]) && (122 >= text[i+2]))){
				text[i+2] = text[i+2] - 32;
			}
		}
		i++;
	}
	
	printf("Output: %s\n", text);

	
}


