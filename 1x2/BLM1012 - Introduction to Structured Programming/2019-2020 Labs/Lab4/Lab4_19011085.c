#include <stdio.h>

int toplam(int a[], int n, int sum, int i, int j, int k)
{
	int control = 0;
	
  	if(sum == a[i] + a[j] + a[k])
		return 1;
	else if(i == n-3 && j == n-2 && k == n-1)
		return 0;
	else{
		if(k == n-1){
			if(j == n-2){
				i++;
				j = i+1;
				k = i+2;
			}
			else{
				j++;
				k = j+1;
			}
		}
		else
			k++;
		toplam(a,n,sum,i,j,k);
	}
}

int main()
{
    int i,j,k,n,sum,result;
    int a[50];
    do{
    	printf("Kac buton oldugunu giriniz = ");
    	scanf("%d", &n);
    	if(n<3)
    		printf("En az 3 buton giriniz!\n");
	}while(n<3);
    

    for(i=0; i<n; i++)
    {
        printf("%d.butonun degerini giriniz = ",i+1);
        scanf("%d",&a[i]);
    }

    printf("Ampulun calismasi icin gereken enerji = ");
    scanf("%d", &sum);

    i=0;
    j=1;
    k=2;
	result = toplam(a, n, sum, i, j, k);
    
    if(result)
    	printf("Ampul yanar!");
    else
    	printf("Ampul yanmaz!");
    
    return 0;
}
