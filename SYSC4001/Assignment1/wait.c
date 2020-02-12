#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	pid_t pid;
	char *message;
	int pidnum;
	char *process;
	int n;
	int exit_code;

	printf("Fork program starting \n");
	pid = fork();
	
	switch(pid){
		case -1:
			perror("fork failed");
			exit(1);
		case 0:
			message = "This is child";
			n = 5;
			exit_code = 37;
			break;
		default:
			message = "This is the parent";
			pidnum = getpid();
			printf("Parent has pid %d \n", pidnum);
			n = 3;
			exit_code = 0;
			break;
	}
	
	for(; n > 0; n--){
		puts(message);
		sleep(1);
	}

	//Waits for the child process to finish.
	if (pid!=0){
		int stat_val;
		pid_t child_pid;

		child_pid = wait(&stat_val);
	
		printf("Child has finished: PID = %d \n", child_pid);
		
		if (WIFEXITED(stat_val))
			printf("Child exited with code %d \n", WEXITSTATUS(stat_val));
		else
			printf("Child terminated abnormally \n");
	}
	exit(exit_code);
	//pid_t wait(int *stat_loc);
}




