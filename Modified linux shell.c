#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

#define MAX 2048

int main(int argc, char **argv)
{
	int file_pipes[2], data_processed = 0, fd;
	pid_t pid;
	char buf[MAX];

	if(argc < 2){
		printf("Error parameters\n");
		exit(1);
	}

	if(pipe(file_pipes) == -1)
		exit(1);

	pid = fork();
	if(pid < 0){
		printf("Fork failure\n");
		exit(1);
	}else if(pid == 0){
		/* The child read from the pipe, so I close the file descriptor for the writing and I close the stdin */
		close(0);
		close(file_pipes[1]);
		
		read(file_pipes[0],buf,MAX);
			
		//printf("Read %d bytes\n", data_processed);
	}else{
		/* The parent writes on the pipe, so I close the file descriptor for reading */
		close(1);
		close(file_pipes[0]);

		fd = open(argv[1],O_RDONLY,S_IRUSR|S_IWUSR);
		if(fd == -1){
			printf("Impossible to open the file\n");
			exit(1);
		}
		/* The parent process read from the input file and writes its content on the pipe */
		while(read(fd,buf,MAX) != 0){
			write(file_pipes[1],buf,MAX);
		}
		
		close(fd);
	}

	exit(0);
}
