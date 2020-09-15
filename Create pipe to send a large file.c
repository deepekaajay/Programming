#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define MAX 4+1 /* 4 is the number of bytes for an integer */

//float compute_average();

int main()
{
	pid_t pid, pid1, pid2, pid3;	
	int fd, N, n, i, status;
	char *buf = malloc(sizeof(int)+1), t = ' ', *cmd[] = {"average", (char *)0};

	pid = fork();
	if(pid < -1){
		printf("Fork failure\n");
		exit(1);
	}else if(pid == 0){
		/* Child process */
		//printf("integer = %ld bytes\n", sizeof(int));
		srand(time(NULL));
		N = rand()%20;
		fd = open("random.txt",O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR);
		if(fd == -1){
			printf("ERROR, failure in opening the file\n");
			exit(1);
		}
		//printf("N = %d\n", N);
		for(i=0;i<N;i++){
			n = rand()%100;
			//printf("%d ", n);
			/* In order to convert the string into an integer number, instead of using the function itoa(), which is not a standard function, I use snprintf(). This function belongs to stdio.h library and prints the integer on a string */
			snprintf(buf,sizeof(n),"%d",n);
			write(fd,buf,strlen(buf));
			write(fd,&t,sizeof(char));
		}
		free(buf);
	}else{
		/* Parent process, which is the main process */
		/* The parent process waits for its child to be ended because he needs 'random.txt' file */
		wait(&status);
		
		/* 1st sub-process */
		if((pid1 = fork()) == 0){
			execlp("wc", "wc", "-m", "random.txt", NULL);
			printf("Failed exec\n");
			exit(-1);
		}else if(pid1 == -1){
			printf("Fork failure\n");
			exit(1);
		}
		/* 2nd sub-process */
		if((pid2 = fork()) == 0){
			execlp("wc", "wc", "-w", "random.txt", NULL);
			printf("Failed exec\n");
			exit(-1);
		}else if(pid2 == -1){
			printf("Fork failure\n");
			exit(1);
		}
		/* 3rd sub-process */
		if((pid3 = fork()) == 0){
			execv("average", cmd);
			printf("Exec failure\n");
			exit(1);
		}else if(pid3 == -1){
			printf("Fork failure\n");
			exit(1);
		}
	}

	exit(0);
}

/*float compute_average()
{
	int fd, i = -1, bytes_read, n, cnt = 0;
	float avg;
	char buf[MAX], t;

	fd = open("random.txt",O_RDONLY,S_IRUSR);
	if(fd == -1){
		printf("ERROR, failure in opening the file\n");
		exit(1);
	}
	
	do{
		i++;
		bytes_read = read(fd,&t,1);
		buf[i] = t;
		if((t == ' ') && (bytes_read != 0)){ 
			buf[i] = '\0';
			n = atoi(buf);
			//printf("n = %d\n", n);
			avg += n;
			cnt++;
			i = -1;
		}
	}while(bytes_read != 0);
	//printf("I read %d numbers\n", cnt);
	
	return ((float) (avg/cnt));
}*/
