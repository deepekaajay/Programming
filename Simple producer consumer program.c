#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

int main(int argc, char **argv)
{
	int N, i, power, sum = 0;
	int file_pipes[2];
	pid_t pid;

	if(argc != 2){
		printf("ERROR, wrong number of arguments\n");
		exit(1);
	}
	N = atoi(argv[1]);
	if(N > 5) N = 5;
	
	if(pipe(file_pipes) == 0){
		for(i=0;i<=N;i++){
			pid = fork();

			if(pid == -1){
				printf("Fork failure\n");
				exit(1);
			}else if(pid == 0){
				power = pow(2,i);
				//printf("2^%d = %d\n", i, power);
				/* I close the channel for reading from the pipe */
				close(file_pipes[0]);
				write(file_pipes[1],&power,sizeof(power));
				exit(0); /* Exit successfully */
			}
		}
	}

	for(i=0;i<=N;i++){
		/* I close the channel for writing on the pipe */
		close(file_pipes[1]);
		read(file_pipes[0],&power,sizeof(power));
		sum += power;
	}

	printf("The summation of powers of 2 from 0 to %d is %d\n", N, sum);
	
	exit(0);
}
