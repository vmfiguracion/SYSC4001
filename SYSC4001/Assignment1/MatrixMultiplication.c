#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include "shm_com.h"
#include <sys/wait.h>

//Q[i][k] = sum(M[i][j]*N[j][k])
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
	printf("Matrix before Multiplication:\n");
	for (int a = 0; a < n; a++){
		for (int b = 0; b < n; b++){
			printf("%d ", shared_matrix[a][b]);
		}
		printf("\n");
	}
	
	
//Making Shared Memory
	//1) Create shared memory
	int shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666 | IPC_CREAT);
	//Stop if the create failed
	if (shmid == -1){
		fprintf(stderr, "shmget failed\n");
		exit(EXIT_FAILURE);
	}

	//2) Enable access to the shared memory
	shared_memory = shmat(shmid, (void *)0, 0);
	//Stop if the enabling failed
	if (shared_memory == (void *)-1){
			fprintf(stderr, "shmat failed\n");
			exit(EXIT_FAILURE);
	}
	printf("Memory attached at %X\n", (int *)shared_memory);

	//3) Shared memory segment
	shared_stuff = (struct shared_use_st *) shared_memory;
	shared_stuff->shared_matrix;

//CREATING CHILD PROCESSES
	for (i = 0; i < n; ++i){
		//In child process
		sleep(1);
		printf("Child process (P%d) computing row %d...\n", i+1, i+1);
		sleep(3);

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
			sleep(3);
			break;
		}
	}



//MAKE THE PARENT PROCESS WAIT FOR THE CHILDREN TO FINISH EXECUTION
	while((pid=waitpid(-1,&status,0))!=-1){
		sleep(2);
		printf("Process %d terminated\n",pid);
	}

	//Q after multiplication.
	//Should be: Q = [670 710 930 1150
	//		  175 243 353 463
	//		  68  144 232 320
	//		  176 316 492 668]
	for (int a = 0; a < n; a++){
		for (int b = 0; b < n; b++){
			printf("%d ", shared_stuff->shared_matrix[a][b]);
		}
		printf("\n");
	}


//DETATCH SHARED MEMORY
	if (shmdt(shared_memory) == -1){
		fprintf(stderr, "shmdt failed \n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);

}
		  
