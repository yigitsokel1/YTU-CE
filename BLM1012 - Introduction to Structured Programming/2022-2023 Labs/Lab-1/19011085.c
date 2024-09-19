#include<stdio.h>
#define STR_SIZE 100


int main(){
	
	
	char input[STR_SIZE];
	char selection = 'e';
	int i, j, step, control;
		
	do{
		printf("Enter the word : ");
		scanf("%s", input);
		
		control = 1;
		step = 0;
		do{
			step++;
			printf("%d.adim : ", step);
			if(input[step] == '\0'){
				control = 0;
				step = 0;
			}
			
				
			i = step;
			do{
				printf("%c", input[i]);
				i++;
			}while(input[i] != '\0');
			
			j=0;
			do{
				if(control)
					printf("%c", input[j]);
				j++;	
			}while(j < step);
			printf("\n");
		}while(step != 0);
		
		
		printf("\nPress 'e' or 'E' to restart the program : ");
		scanf(" %c", &selection);
	}while(selection == 'e' || selection == 'E');
	
	printf("\nProgram terminated...");
	return 0;
	
}
