#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#define MAX 100

typedef struct{
	int item[MAX];
	int top;
}STACK;


void initialize(STACK *s);
int isEmpty(STACK *s);
int isFull(STACK *s);
void push(STACK *s, int item);
int pop(STACK *s);
void compare(char* str, int i);

int main(){
	
	char bin[MAX];
	int number, number2;
	int tmp, item, count, counter, temp;
	int i, j, k;
	STACK s;
	initialize(&s);
	
	printf("Enter the number : ");
	scanf("%d",&number);
	number2 = number;
	
	if(number>=0){
		while(number!=0){
			tmp = number % 2;
			push(&s,tmp);
			number = number / 2;
			i++;
		}
		count = ((i-2) / 8 + 1) * 8;
		j=0;
		while(j<count-i+1){
			bin[j++] = '0';
		}
		for(k=0;k<i-1;k++){
			item = pop(&s);
			if(item == 1)
				bin[j++] = '1';
			else
				bin[j++] = '0';
		}
		bin[j] = '\0';
		printf("String Binary : %s\n",bin);
	}
	else{
		number = number * -1;
		while(number!=0){
			tmp = number % 2;
			push(&s,tmp);
			number = number / 2;
			i++;
		}
		count = ((i-2) / 8 + 1) * 8;
		j=0;
		while(j<count-i+1){
			bin[j++] = '1';
		}
		for(k=0;k<i-1;k++){
			item = pop(&s);
			if(item == 1 )
				bin[j++] = '1';
			else
				bin[j++] = '0';
		}
		j = count - 1;
		counter = 0;
		while(j>=count-i+1){
			if(bin[j] == '0' && counter == 0){
				j--;
			}
				
			else if(bin[j] == '1' && counter == 0){
				counter = 1;
				j--;
			}
			else if(bin[j] == '0' && counter == 1){
				bin[j] = '1';
				j--;
			}
			else if(bin[j] == '1' && counter == 1){
				bin[j] = '0';
				j--;
			}
			
		}
		bin[count] = '\0';
		printf("String Binary : %s\n",bin);
	}

	compare(bin,0);
	
}



void initialize(STACK *s){
	s->top=0;
}

int isEmpty(STACK *s){
	if(!s->top)
		return 1;
	else
		return 0;
}

int isFull(STACK *s){
	if(s->top == MAX)
		return 1;
	else 
		return 0;
}

void push(STACK *s, int item){
	
	if(isFull(s))
		printf("Stack is FULL!!!!");
	else{
		s->item[s->top] = item;
		(s->top)++;
	}
}

int pop(STACK *s){
	
	if(isEmpty(s))
		printf("Stack is Empty");
	else{
		(s->top)--;
		return s->item[s->top];
	}
	
}



void compare(char* str, int i){
	
	STACK s;
	s.top=0;
	
	if(str[i] == 48){
		while(str[i]!='\0'){
			if(str[i]==48)
				push(&s,str[i]);
			else{
				if(s.top == 0)
					return compare(str,i);
				pop(&s);
			}
			i++;	
		}
		if(s.top==0)
			printf("0 and 1 are equals.");
		else
			printf("0s are more. This need %d piece of 1.", s.top);
	}
	else{
		while(str[i]!='\0'){
			if(str[i]==49)
				push(&s,str[i]);
			else{
				if(s.top == 0)
					return compare(str,i);
			
				pop(&s);
			}
			i++;	
		}
		if(s.top==0)
			printf("0 and 1 are equal numbers.");
		else
			printf("1s are more.This need %d piece of 0.", s.top);
	}
	
	
}






