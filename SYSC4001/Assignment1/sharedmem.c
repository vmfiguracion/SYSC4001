#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include "shm_com.h"

int main(){
	pid_t pid;
	char *message;
	int pidnum;
	char *process;
	int n;
	int exit_code;

	void *shared_memory = (void *)0;
	struct shared_use_st *shared_stuff;
	int shmid;
	
	printf("This is not done :(");


	//Creating child and parent processes
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

	//Create shared memeory
	srand((unsigned int)getpid());

	shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666 | IPC_CREAT);

	if (shmid == -1){
		fprintf(stderr, "shmget failed\n");
		exit(EXIT_FAILURE);
	}
	
	//Shared memory is accessible to the program
	shared_memory = shmat(shmid, (void *)0, 0);
	if (shared_memory == (void *)-1){
		fprintf(stderr, "shmat failed\n");
		exit(EXIT_FAILURE);
	}

	//printf("Memory attached at %X\n", (int *)shared_memory);
