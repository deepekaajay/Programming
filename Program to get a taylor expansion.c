#include <stdio.h>

#include <stdlib.h>

#include <sys/types.h>

#include <unistd.h>

#include <sys/stat.h>

#include <fcntl.h>

#include <string.h>

#include <dirent.h>


#define P1_READ     0

#define P2_WRITE    1

#define P2_READ     2

#define P1_WRITE    3

#define NUM_PIPES   2
int fd[2*NUM_PIPES];


unsigned int N=0;

unsigned int global_i=0;
char readbuffer[BUFSIZ];
char global_str[50];

int fd_global_src,fd_global_des;
char sourcefile[50],destfolder[50];


void parent_init_process(void);

void child_process(void);

void pipe_handler(unsigned int size);

void directoryvis(char *directory);

void filevis(char *address);



int main() 
{

pid_t pid1, pid2;

unsigned int pipedata=0;

unsigned int nlen=0;

char buffsource[BUFSIZ];

int i=0;


pipe_handler(NUM_PIPES);

parent_init_process();




for(global_i=0;global_i<=N;global_i++)
{

pid1=fork();


switch (pid1)
{

case -1:
    
printf("Fork error.");
    
exit(EXIT_FAILURE);

break;
    

case 0:
    
child_process();
    
exit(EXIT_SUCCESS);

break;


default:
    
close(fd[P2_READ]);
    
close(fd[P2_WRITE]);
    

    
while(1)
{
    
nlen=read(fd_global_src,buffsource,sizeof(buffsource));
    
if (nlen==0)
        
break;
    
write(fd[P1_WRITE],buffsource,nlen);
    }
    
close(fd_global_src);
    
wait(NULL);
    


break;

}

}


printf ("parent here final.\n");            

exit (EXIT_SUCCESS);

}


void parent_init_process(void)
{
    
    
printf("Please enter the file you want to copy:");
    
scanf("%s",sourcefile);
    
filevis(sourcefile);
    
    
printf("Please enter the address you want to paste to:");
    
scanf("%s",destfolder);
    
directoryvis(destfolder);


}


void child_process(void)
{
    
int j=0;
    
char mybuffer[BUFSIZ];
    
unsigned int nbytes=0;
    
    
strcat(destfolder,"/copy.txt");
    
fd_global_des=open (destfolder,O_CREAT | O_WRONLY,S_IRUSR | S_IWUSR | S_IXUSR );
    
close(fd[P1_READ]);
    
close(fd[P1_WRITE]);
    
do
{
        
nbytes = read(fd[P2_READ], mybuffer, sizeof(mybuffer));
        
write(fd_global_des,mybuffer,nbytes);
    
}
while(nbytes==BUFSIZ);
 
    
close(fd[P2_READ]);
    close(fd[P2_WRITE]);
    
close(fd_global_des);

}



void pipe_handler(unsigned int size)
{ 

    
for (i=0; i<size; ++i)
    {
        
if (pipe(fd+(i*2)) < 0)
        {
            
perror("Failed to allocate pipes");
            
exit(EXIT_FAILURE);
        
}

    
}

}


void directoryvis(char *directory)
{
    
    
DIR *dp;
    
struct dirent *dire;
    
dp=opendir(directory);
    
if(dp==NULL)
{
        
printf("No such a directory!\n");
        
exit(EXIT_FAILURE);
    }
    
printf("This directory contains:\n");
    
dire=readdir(dp);
    
while(dire!=NULL)
{
        
printf("%s\n",dire->d_name);
        
dire=readdir(dp);
    
}
    
closedir(dp);


}



void filevis(char *address)
{
   
    
if(access(address,F_OK)==0)
{
        
fd_global_src=open(address,O_RDONLY , S_IRUSR | S_IWUSR | S_IXUSR );
    
}
else
{
        
printf("No such a file!\n");
        
exit(EXIT_FAILURE);
    
}
    

}
