#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include "shm_com.h"
#include <sys/wait.h>

int main(){
	int n = 4;
	int i, j, k;
	pid_t pid;
	int status = 0;

	void *shared_memory = (void *)0;
	struct shared_use_st *shared_stuff;

	int M[4][4] = {
	   {10, 20, 30, 40},
	   {5, 6, 7, 8} ,
	   {4, 3, 2, 1},
	   {8, 7, 6, 5}
	};
	int N[4][4] = {
	   {10, 30, 50, 70},
	   {2, 4, 6, 8} ,
	   {7, 3, 5, 7},
	   {8, 6, 4, 2}
	};

	int shared_matrix[4][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};

	//Q before multiplication.
	//Should be: Q = [0 0 0 0
	//		  0 0 0 0
	//		  0 0 0 0
	//		  0 0 0 0]
	printf("Matrix Q before multiplication:\n");
	for (int a = 0; a < n; a++){
		for (int b = 0; b < n; b++){
			printf("%d ", shared_matrix[a][b]);
		}
		printf("\n");
	}
	sleep(1);
	
	//Printing input matrix M
	printf("Matrix M:\n");
	for (int a = 0; a < n; a++){ 
		for (int b = 0; b < n; b++){
			printf("%d ", M[a][b]);
		}
		printf("\n");
	}
	sleep(1);
	printf("Matrix N:\n");
	//Printing input matrix N
	for (int a = 0; a < n; a++){ 
		for (int b = 0; b < n; b++){
			printf("%d ", N[a][b]);
		}
		printf("\n");
	}
	sleep(1);
	
	//Create shared memory
	int shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666 | IPC_CREAT);
	//Stop if the create failed
	if (shmid == -1){
		fprintf(stderr, "shmget failed\n");
		exit(EXIT_FAILURE);
	}

	//Enable access to the shared memory
	shared_memory = shmat(shmid, (void *)0, 0);
	//Stop if the enabling failed
	if (shared_memory == (void *)-1){
			fprintf(stderr, "shmat failed\n");
			exit(EXIT_FAILURE);
	}
	
	//Shared memory segment
	shared_stuff = (struct shared_use_st *) shared_memory;
	shared_stuff->shared_matrix;
	
	//Creatng child processes
	for (i = 0; i < n; ++i){
		//In child process
		printf("Child process (P%d) computing row %d...\n", i+1, i+1);
		sleep(1);

		if (fork() == 0){

			//Deals with one column of the row
			//eg Q[1][3] = P13
			for(k = 0; k < n; k++){

				//Deals with one term of the sum
				//eg j=2: (M[i][2] * N[2][k])
				for(j = 0; j < n; j++){
					shared_stuff->shared_matrix[i][k] += (M[i][j] * N[j][k]);
				}
			}
			printf("Row %d: ", i+1);
			for(int r = 0; r < n; r++){
				printf("%d ", shared_stuff->shared_matrix[i][r]);
			}
			printf("\n");
			sleep(1);
			break;
		}
	}

	//Make the parent process wait for the children to finish executing
	while((pid = waitpid(-1,&status,0)) != -1){
		printf("Process %d terminated.\n",pid);
		sleep(1);
	}

	//Printing Q afte multiplication
	//Should be: Q = [670 710 930 1150
	//		  175 243 353 463
	//		  68  144 232 320
	//		  176 316 492 668]
	if (i < n){} 
	else {
		printf("Matrix Q after multiplying:\n");
			for (int a = 0; a < n; a++){ 
				for (int b = 0; b < n; b++){
					printf("%d ", shared_stuff->shared_matrix[a][b]);
				}
				printf("\n");
			}
			sleep(1);
	}

	//Detatch shared memory
	if (shmdt(shared_memory) == -1){
		fprintf(stderr, "shmdt failed \n");
		exit(EXIT_FAILURE);
	}
	if (shmctl(shmid, IPC_RMID, 0) == -1){
		fprintf(stderr, "shmctl(IPC_RMID) failed\n");
		exit(EXIT_FAILURE);
	}
	
	//Finish program
	exit(EXIT_SUCCESS);
}
		  
