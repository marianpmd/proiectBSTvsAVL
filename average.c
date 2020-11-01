#include<stdio.h>
#include<stdlib.h>

int noOfValues = 0;

double max(double values[]){
    double maxv = values[0];
    for(int i = 1 ; i<noOfValues ; i++){
        if(values[i]>maxv){
            maxv = values[i];
        }
    }
    return maxv;

}

double min(double values[]){
    double minv = values[0];
    for(int i = 1 ; i<noOfValues ; i++){
        if(values[i]<minv){
            minv = values[i];
        }
    }
    return minv;

}


double avg(double values[]){
    double sum = 0;
    int i = 0;
    for( i = 0 ; i<noOfValues ; i++){
        sum+=values[i];
    }
    return sum/i;
}



int main(void){
    FILE* input = fopen("results","r");
    double values[100];
    double val;
    int i=0;
    while(!feof(input)){
        fscanf(input,"%lf",&val);
        values[i] = val;
        i++;
    }
    
    noOfValues = 75;    
    
    printf("Number of values : %d\n",noOfValues);
    printf("Largest value is : %lf\n",max(values));
    printf("Smallest value is : %lf\n",min(values));
    printf("Average value is : %lf\n",avg(values));
    
    
    
    return 0;

}
