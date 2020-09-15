#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(int argc, char *argv[]) {
const char *pat;
const char *file;
if(argc !=3) {
printf("Argument not correct \n");
return -7;
}
pat = argv[1];
if(chdir(pat)!=0){
printf("Error in locating dir \n");
return -1;
}
file = argv[2];
if(access(file, F_OK) ==0){
printf("File exist \n");
}
else{
printf("The requested file does not exist \n");
}
return 0;
}

