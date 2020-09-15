#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<time.h>

int main(int argc, char *argv[]){
time_t t;
srand((unsigned) time(&t)); 
int r;
int c;
int i;
int j;
int matrix[r][c];
const char *file;
FILE *fp;
file = "/home/deepeka/lab/test.txt";
if( (fp= fopen(file, "r+")) == NULL){
printf("Cannot open file");
exit(1);
}
printf("enter the no of rows");
scanf("%i", &r);
printf("enter the no of columns");
scanf("%i", &c);

for(i=0;i<r;i++){
for(j=0;j<c;j++){
matrix[i][j]= (rand()%100);
printf("%i",matrix[i][j]);

fprintf(fp,"%d",matrix[i][j]);
}
printf("\n");
fprintf(fp,"\n");
}
int test[]= {10 , 12 , 13};
fclose(fp);
return 0;
}
