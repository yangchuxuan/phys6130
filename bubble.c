#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void){
  
  int array[10]={};
  srand((int)time(0));   
  for (int i=0;i<10;i++){
	array[i]=rand();
	printf("%d \n",array[i]);
  }
  int temp;
  for (int i=10;i>0;i--){
	for (int j=0;j<i-1;j++){
		if(array[j]>array[j+1]){
			temp=array[j+1];
			array[j+1]=array[j];
			array[j]=temp;
		}		
	}
  }
  printf("below is the sorted array \n");  
  for (int i=0;i<10;i++){
	
	printf("%d \n",array[i]);
  }
  return 0;
}
