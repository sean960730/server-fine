#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;



int main(){
	int R,C,M;
	scanf("%d %d %d",&R,&C,&M);
	int array[R][C];
	for(int a = 0;a<R;a++){
		char input[C*2-1]  = {'\0'};
		scanf("%s",input);
		for(int b= 0;b<C;b++){
				array[a][b] = input[b]-48;
		}
	}
	for(int c= 0;c<R;c++){
		for(int d = 0;d<C;d++){
			printf("%d ",array[c][d]);
		}
		printf("\n");
	}
	int modify[M] = {0};
	printf("%d\n",M);
	for(int g = 0;g<M;g++){
		printf("%d\n",g);
		scanf("%d",&modify[g]);
	}
	int i,j;
	for(int t = 0;t<M;t++){
		switch(modify[t]){
			case 0:
				for(i =0;i<R;i++){
					if (R-1-i==i){
						break;
					}
					int temp[C] = {0};
					for(j = 0;j<C;j++){
						temp[j] = array[i][j];
						array[i][j] = array[R-1-i][j];
						array[R-1-i][j] = temp[j] ;
					}
				}
				break;
			case 1:
				printf("Break one\n");
				int T = R;
				R=C;
				C=T;
				int array2[R][C] = {0};
				for (i = 0;i<R;i++){
					for(j=0;j<C;j++){
						array2[i][j] = array[C-1-j][i];
						//printf("%d\n",array2[i][j]); 
					}
				}
				int array[R][C] = {0};
				for(int f = 0;f<R;f++){
					for(int k =0;k<C;k++){
						//printf("%d\n",array2[f][k]);
						array[f][k] =array2[f][k];
						printf("%d,%d\n",array[f][k],array2[f][k]);
					}
				}
				break;
		}
	}
	printf("%d %d\n",R,C);
	for(int d = 0;d<R;d++){
		for(int e = 0;e<C;e++){
			if (e==C-1){
				printf("%d",array[d][e]);
				break;
			}
			printf("%d ",array[d][e]);
		}
		printf("\n");
	}
	return 0;
}
