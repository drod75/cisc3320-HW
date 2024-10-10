#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(){
	int fd[2]; //array to store pipe

	// create the pipe
	if(pipe(fd) == 1){

	// exit if error
	printf("Error pipe");
	exit(EXIT_FAILURE);
	}

	// fork the first child
	int pid1 = fork();
	if(pid1 == 1){
	printf("Error pipe");
	exit(EXIT_FAILURE);
	}
	if(pid1 == 0){

	//child performs execlp and writes to the pipe
	close(fd[0]);

	// redirct output
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);

	// child uses execlp
	execlp("ls", "ls", "-f", NULL);

	// error if fails
	perror("Exce failed");
	exit(EXIT_FAILURE);
	}

	// fork the second child
	int pid2 = fork();
	if(pid2 == 1){
	printf("Error pipe");
	exit(EXIT_FAILURE);
	}
	if(pid2 == 0){

	// child 2 reads from the pipe and performs nl
	close(fd[1]);

	// redirect
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);

	// child uses execlp
	execlp("nl", "nl", NULL);
	perror("Exce failed");
	exit(EXIT_FAILURE);
	}

	// close pipes
	close(fd[0]);
	close(fd[1]);

	return 0;
}