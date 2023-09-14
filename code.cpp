#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cstring>
#include <fstream>
double max(double data[],int len){
    double max = data[0];
    for(int i = 0;i<len;i++){
        if (data[i] > max){
            max = data[i];
        }
    }
    return max;
}

double range(double max,double min){
    double range = max-min;
    return range;
}
void amount_counter(double data[],int len){
    double list[1024] = {0};
    list[0]  = data[0];
    int counter[1024] = {0};
    int i = 0;
    for(int f = 0;f<len;f++){
        if(data[f] != list[i]){
            list[i+1] = data[f];
            counter[i+1]++;
            i++;
        }else{
            counter[i]++;
        }

    }
    int index[1024];
    for(int b = 0;b<1024;b++){
        index[b] = -1;
    }
    int max = counter[0];
    int p =0;
    for(int l = 0;l<=i;l++){
        if (counter[l] == max){
            index[p] = l;
            p++;
        }else if(counter[l] > max){
            max = counter[l];
            for(int c = 0;c<=p;c++){
                index[c] = -1;
            }
            p = 1;
            index[0] = l;
        }
    }
    for(int h = 0;h<1024;h++){
        if (index[h] == -1){
            break;
        }else{
            printf("Mo: %f\n",list[index[h]]);
        }
    }
    printf("Amount: %d\n",max);
}
double iqr(double data[],int len,int p,int h){
    if((float)len*p/h-(int)len*p/h>0){
        return data[(int)len*p/h];
    }else if((float)len*p/h-(int)len*p/h==0){
        if ((float)len*p/h - len ==0){
            return data[len*p/h-1];
        }
        return(data[len*p/h-1] + data[len*p/h])/2;
    }else if(len==1){
	return data[0];
    }
    else{
        return -1;
    }
    
}
double min(double data[],int len,int data_index){
    double min = data[0];
    for(int i = 0;i<len;i++){
        if(i >data_index-1){
            break;
        }
        if(data[i] < min){
            min = data[i];
        }
    }
    return min;
}
double sum(double data[],int len){
    double s = 0;
    for(int i = 0;i<len;i++){
        s+= data[i];
    }
    return s;
}
int main(){
    system("clear");
    printf("Usage: key in the one dimentional data set,to stop it just type \'b\'.\n");
    printf("Press enter to continue");
    char t;
    scanf("%c",&t);
    system("clear");
    int data_index = 0;
    char num[30];
    double data[1024] = {0};
    int floating = 0;
    int inter_len = 0;
    int length[1024] = {21};
    int max_pointer = 0;
    int times = -1;
    int ind = 0;
    memset(num,0,sizeof(num));
    while (1){
        printf("Data(%d)",data_index+1);
        scanf("%s",num);
        if(num[0] == 'b'){
            break;
        }
        for(int i = 0;i<=30;i++){
            if(num[i] == '*'){
              printf("Times : ");
              scanf("%d",&times);
              num[i] = '\0';  
            }
        }
        inter_len = 0; 
        floating=0;
        int stop;
	    int neg = 0;
        for(int f = 0;f<sizeof(num);f++){
            if(f == 29){
                break;
            }
            if(num[f] == '\0'){
                if(floating == 0){
                    max_pointer = f-1;
                    break;
                }
            }
	    if (num[f] == '-'){
		    neg = 1;
		for(int ab = 0;ab<sizeof(num);ab++){
			if(f==29){
			   break;
			}	
			num[ab] = num[ab+1];
			num[ab+1] = 0;
		}
	    }
            if(num[f] == '.'){
                inter_len = f;
                max_pointer = f-1;
                floating = 1;
            }
            if(floating == 1){
                num[f] = num[f+1];
                num[f+1] = 0;
            } 
        }
        double n = 0;
        for(int x = 0;x<sizeof(num)/sizeof(num[0]);x++){
            if(num[x] == '\0'){
                break;
            }
	    if(neg==1){
		n+= -1*((int)num[x]-48)*pow((double)10,(double)max_pointer-x);
	    }else{	
            	n+= ((int)num[x]-48)*pow((double)10,(double)max_pointer-x);
	    }
        }
        if(times != -1){
            for(int u = 0;u<times;u++){
                data[data_index] = n;
                length[data_index] = inter_len;
                data_index++;
            }
            continue;
        }
        data[data_index] = n;
        memset(num,0,sizeof(num));
        length[data_index] = inter_len;
        data_index++;
    }
    for(int l = 0;l<data_index-1;l++){
        for(int q = 0;q<data_index-1-l;q++){
            if(data[q]> data[q+1]){
                double temp = data[q+1];
                data[q+1] = data[q];
                data[q] = temp;
            }
        }
    }
    for (int i = 0;i<data_index;i++){
        double c = data[i];
        int space = 15-length[i];
        if(i%8 == 0){
            printf("\n");
        }
        printf("%f",c);
        for(int v = 0;v<space;v++){
            printf(" ");
        }
        printf("|");
        
    }
    double max_ = max(data,data_index);
    printf("\nMax: %f\n",max_);
    double min_ = min(data,1024,data_index);
    printf("Min: %f\n",min_);
    double r = range(max_,min_);
    printf("R: %f\n",r);
    double iqrn[3] = {0};
    for(int i = 0;i<3;i++){
        iqrn[i] = iqr(data,data_index,i+1,4);
        printf("Q%d: %f \n",i+1,iqrn[i]); 
    }
    printf("I.Q.R.: %f\n",iqrn[2]-iqrn[0]);
    double Me = iqr(data,data_index,2,4);
    printf("Me: %f\n",Me);
    amount_counter(data,data_index);
    double m =0;
    for(int k = 0;k<data_index;k++){
        double K = data[k];
        double a = K*K;
        m+= a;

    }
    double average = sum(data,1024)/data_index;
    double sd = sqrt((double)((m/(data_index))-average*average));
    printf("Average : %f\n",average);
    printf("Sandard deviation: %f\n",sd);
    int pr;
    while (1){
	printf("Type p Number: ");
        scanf("%d",&pr);
        if(pr == -1){
            break;
        }
        double e = iqr(data,data_index,pr,100);
        printf("P %d %%: %f\n",pr,e);
    }
    return 0;
}
