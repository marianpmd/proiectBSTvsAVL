#include<stdio.h>
#include<stdlib.h>

#define noOfValues 100000


int main(int argc,char**argv){
    
    FILE *input = fopen("/dev/urandom","rb");
    int noOfFiles = atoi(argv[1]);
    
    printf("Number of files : %d",noOfFiles);
    FILE *output[noOfFiles] ;
    
    unsigned int value;
   
    for(int j = 0 ; j<noOfFiles;j++){
        char filename[20];
        sprintf(filename,"INPUT%d.txt",j);
        output[j] = fopen(filename,"w");
          
        unsigned int i = 0;
        while(i<noOfValues){
          fread(&value, sizeof(unsigned int),1,input);
          fprintf(output[j],"%u\n",value);
          //printf("Am generat : %u\n",value);
          i++;
         }
    }
    
    
   
   
    /*FILE *files[numfiles];
for (int i = 0; i < numfiles; i++)
{
    char filename[20];
    sprintf(filename, "results%d.dat", i);
    files[i] = fopen(filename, "w");
}*/
    
  /*  unsigned int i =0;
    while(i<noOfValues){
        fread(&value, sizeof(unsigned int),1,input);
        fprintf(output,"%u\n",value);
       // printf("Am generat : %u\n",value);
        i++;
    }*/


}
