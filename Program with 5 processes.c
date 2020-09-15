#include <stdio.h>

#include <stdlib.h>

#include <sys/types.h>

#include <unistd.h>

#include <sys/stat.h>

#include <fcntl.h>

#include <string.h>





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

char str[]= "ABCDEFGHIJKLMENOPQRSTUVWXYZ";

int wr,rd;
int sem[2];


void parent_init_process(void);

void child_process(void);

void pipe_handler(unsigned int size);

void semaphore_init ( int* sw,int init_num);

void semaphore_wait ( int * sw);

void semaphore_signal ( int * sw);



int main() 
{

pid_t pid1, pid2;

unsigned int pipedata=0;

unsigned int nlen=0;

char buffsource[BUFSIZ];

int i=0;
int value;



pipe_handler(NUM_PIPES);

parent_init_process();

semaphore_init(sem,4);



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
    
for(i=0;i<wr;i++)
{
        
semaphore_wait(sem);
        
write(fd[P1_WRITE],&str[i],1);       
        
printf("I have write the %c\n",str[i]);
    
}
    
   
wait(NULL);

break;

}

}


printf ("parent here final.\n");            

exit (EXIT_SUCCESS);

}


void parent_init_process(void)
{
    
    
printf (" How many times do you want to write ? ");
    
scanf ("%d",&wr);
    
printf (" How many times do you want to read ? ");
    
scanf ("%d",&rd);

}


void child_process(void)
{
    
int j=0;
int value;
    
char mybuffer[BUFSIZ];
    
unsigned int nbytes=0;
    
    
close(fd[P1_READ]);
    
close(fd[P1_WRITE]);
    
for(j=0;j<rd;j++)
{
        
nbytes = read(fd[P2_READ], mybuffer,1);
        
printf("I have read the %c\n",mybuffer[0]);
        
semaphore_signal(sem);
    
}

    
        
 
    
close(fd[P2_READ]);
    
close(fd[P2_WRITE]);


}



void pipe_handler(unsigned int size)
{ 
    
int i=0;
    
for (i=0; i<size; ++i)
    
{
        
if (pipe(fd+(i*2)) < 0)
        
{
            
perror("Failed to allocate pipes");
            
exit(EXIT_FAILURE);
        
}
    
}

}



void semaphore_init ( int* sw,int init_num) 
{
    
int i=0;
    
if ( pipe (sw) == -1) 
{

printf (" Error ");

exit ( -1);

}
    
for(i=0;i<init_num;i++)
{
        
semaphore_signal(sw);
    
}



}


void semaphore_wait ( int* sw) 
{

char buffer ;

if ( read (sw [0] ,& buffer ,1) != 1) 
{

printf (" Error ");

exit ( -1);

}

}


void semaphore_signal ( int * sw) 
{

if ( write (sw [1] ,"X" ,1) != 1) 
{

printf (" Error ");
exit ( -1);

}

}
