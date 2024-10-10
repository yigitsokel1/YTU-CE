#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>


typedef struct sumAndIndex{
	int start;
	int end;
	int sum;
}RESULT;

void bruteForce(int n, int *arr);
RESULT maxSubArray(int *arr, int l, int h);

int main(){
	
	srand(time(NULL));
	int *coal;
	int n;
	int i;
	RESULT gain;
	
	n = 10 + rand() % 10;
	coal = (int*)malloc(n*sizeof(int));
	
	for(i=0; i<n; i++)
		coal[i] = -50 + rand() % 100 ;
	
	printf("Brute-Force");
	bruteForce(n, coal);
	gain = maxSubArray(coal, 0, n-1);
	printf("\nDivide and Conquer");
	if(gain.sum > 0 && gain.start == gain.end){
		printf("\nEn yuksek kazanc : %d\nKazilmasi gereken tek blok: %d\n",gain.sum,gain.start);
	}else if(gain.sum > 0){
		printf("\nEn yuksek kazanc : %d\nKazilmasi gereken kesintisiz blok butunu: %d-%d\n",gain.sum,gain.start,gain.end);
	}else{
		printf("\nHerhangi bir bolum kazanc saglamaz!!\n");
	}
	printf("\nBlok:   ");
	for(i=0; i<n; i++)
	 	printf("%3d  ",i);
	printf("\nKazanc: ");
	for(i=0; i<n; i++)
	 	printf("%3d  ",coal[i]);
	 	
	return 0;
}

void bruteForce(int n, int *arr){
	
	int i, j;
	int maxGain, tempGain;
	int tempStart, tempEnd;
	
	maxGain = 0;
	for(i=0; i<n; i++){
		tempGain = 0;
		for(j=i;j<n;j++){
			tempGain += arr[j];
			if(tempGain > maxGain){
				maxGain = tempGain;
				tempStart = i;
				tempEnd = j;
			}
		}
	}
	
	if(maxGain > 0 && tempStart == tempEnd){
		printf("\nEn yuksek kazanc : %d\nKazilmasi gereken tek blok: %d\n",maxGain,tempStart);
	}else if(maxGain > 0){
		printf("\nEn yuksek kazanc : %d\nKazilmasi gereken kesintisiz blok butunu: %d-%d\n",maxGain,tempStart,tempEnd);
	}else{
		printf("\nHerhangi bir bolum kazanc saglamaz!!\n");
	}
	
}


RESULT maxSubArray(int *arr, int l, int h){
	
	int i;
	int sum, mid;
	RESULT left, right, general;
	left.sum = 0;
	right.sum = 0;
	
	if(l<h){				
		mid = (l+h)/2;
		sum=0;
		left.start = left.end = right.start = right.end = mid;	//�lk ko�ulda ba�lang�� de�erlerinin her zaman middle'a e�it oldu�unu bildi�imiz i�in set ediyoruz
		for(i=mid-1; i>=l; i--){					//Middle'�n hemen solundaki en y�ksek kazan�
			sum += arr[i];
			if(sum > left.sum && 0 < sum){
				left.sum = sum;
				left.start = i;
				left.end = mid;
			}
		}	
		
		sum=0;
		for(i=mid+1; i<=h; i++){					//Middle'�n hemen sa��ndaki en y�ksek kazan�
			sum += arr[i];
			if(sum > right.sum &&  0 < sum){
				right.sum = sum;
				right.start = mid + 1;
				right.end = i;
			}
		}
		
		RESULT dAnswer = {left.start, right.end, arr[mid]+left.sum+right.sum};//Middle'� i�eren en y�ksek kazan�
		RESULT bAnswer = maxSubArray(arr,l, mid == l ? l: mid-1);	 	//Mid l'ye e�itse azalt�ld��� taktirde yanl�� aral�k g�nderilmi� olur(l,l-1)
		RESULT cAnswer = maxSubArray(arr,mid+1,h);
		if(bAnswer.sum > cAnswer.sum)				//Middle'�n solundaki ve sa��ndaki en b�y�k kazanc� se�me
			general = bAnswer;
		else
			general = cAnswer;
						
		if(general.sum > dAnswer.sum)				//En b�y�k kazanca middle'�n dahil olup olmad���n� sorgulay�p ona g�re d�nd�rme
			return general;
		else
			return dAnswer;
		
	}else{
		RESULT last;								//Base Case Durumu
		last.sum = arr[l];
		last.start = l;
		last.end = l;
		return last;
	}
		
	
}
