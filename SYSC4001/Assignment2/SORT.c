#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <sys/types.h>

#include "semun.h"
#include "shm_com.h"

/*
 * SYSC 4001 - Assignment 2
 * Valerie Figuracion 100965536
 * March 6, 2020
 */

static int set_semvalue();
static void del_semvalue();
static int semaphore_p();
static int semaphore_v();
static void swap(int n);
static void destroy_shared_mem(int shmid);
static void make_semaphore(int argc);
static int make_shared_mem();
static int list_of_integers();
static int debug_mode();

int sem_id;
int sorted = 0;
char debug;
int db;

void *shared_memory = (void *)0;
struct shared_use_st *shared_stuff;

int main(int argc){
	int n = 4;
	pid_t pid;
	int status = 0;

	//Ask for debug mode
	db = debug_mode();
	//If the char is not Y, y, N, or n it exits the program
	if(db == -1) exit(EXIT_FAILURE);

	//Make shared memory
	int shared_mem_id = make_shared_mem();
	//Make semaphore
	make_semaphore(argc);

	//Get the array. If list_of_integers() is 0 it exits the program.
	if(!list_of_integers()) exit(EXIT_FAILURE);

	//Swapping logic
	swap(n);

	//Make the parent process wait for the children to finish executing
	while((pid = waitpid(-1,&status,0)) != -1){
		sleep(5);
		del_semvalue();
		//Printout of the sorted matrix
		for(int i = 0; i < 5; i++) printf("%d ", shared_stuff->shared_matrix[i]);
		printf("\n");
	}
	sleep(2);
	//Destroy the shared memory
	destroy_shared_mem(shared_mem_id);

	//Finish program
	exit(EXIT_SUCCESS);
}

/**
 * Initialize semaphore using SETVAL
 */
static int set_semvalue(void){
	union semun sem_union;

	sem_union.val = 1;
	if (semctl (sem_id, 0, SETVAL, sem_union) == -1) return(0);
	return (1);
}

/**
 * Delete semaphore using IPC_RMID
 */
static void del_semvalue(void){
	union semun sem_union;

	if (semctl(sem_id, 0, IPC_RMID, sem_union) == -1){
		exit(EXIT_FAILURE);
	}
}

/**
 * Waiting semaphore
 **/
static int semaphore_p(){
	struct sembuf sem_b;

	sem_b.sem_num = 0;
	sem_b.sem_op = -1;
	sem_b.sem_flg = SEM_UNDO;

	//If the semaphore failed
	if(semop(sem_id, &sem_b, 1) == -1){
		return(0);
	}
	return(1);
}

/**
 * Releasing semaphore
 */
static int semaphore_v(){
	struct sembuf sem_b;

	sem_b.sem_num = 0;
	sem_b.sem_op = 1;
	sem_b.sem_flg = SEM_UNDO;

	//If the semaphore failed
	if(semop(sem_id, &sem_b, 1) == -1){
		return(0);
	}
	return(1);
}

/**
 *Sorting logic
 */
static void swap(int n){
	//While the array is not sorted
	while(!sorted){

		//For each process
		for (int i = 0; i < n; i++){
			//If it's a child process
			if (fork() == 0){
				//If semaphore failed
				if (!semaphore_p()) exit(EXIT_FAILURE);

				//Switch numbers if the ith number is less than the i+1 th number
				if (shared_stuff->shared_matrix[i] < shared_stuff->shared_matrix[i+1]){
					int temp = shared_stuff->shared_matrix[i];
					shared_stuff->shared_matrix[i] = shared_stuff->shared_matrix[i+1];
					shared_stuff->shared_matrix[i+1] = temp;

					//If it is in debug mode print extra statements
					if (db){
						printf("Process P%d performed swapping\n", i+1);
					}
					printf("Process P%d switched %d and %d\n", i+1, i+1, i+2);
					fflush(stdout);
					sleep(2);
				}else{
					//If it is in debug mode print extra statements
					//(for the process that is not swapping
					if (db){
						printf("Process P%d: No swapping.\n", i+1);
						sleep(2);
					}
				}
				//Is semaphore failed
				if (!semaphore_v()) exit(EXIT_FAILURE);
				sleep(1);
				break;
			}
		}

		int count = 0;
		for (int i = 0; i <= sizeof(*shared_stuff->shared_matrix); i++){
			//If the ith number is greater than i+1th number
			if (shared_stuff->shared_matrix[i] > shared_stuff->shared_matrix[i+1]){
				count++;
			}
		}
		if (count == 5) sorted = 1;
	}
}

/**
 * Debug mode
 */
static int debug_mode(){
	printf("Debug mode? (Y/N): ");
	scanf("%c", &debug);

	if (debug == 'Y' | debug == 'y' ){
		printf("Debug mode\n");
		return 1;
	}
	if (debug == 'N' | debug == 'n' ){
		printf("Regular mode\n");
		return 0;
	}
	return -1;
}

/**
 * Asks for an array of 5 integers
 **/
static int list_of_integers(){
	printf("Please provide an array of 5 numbers. Please use spaces instead of commas.\n");

	//Scans for 5 numbers
	for (int i = 0; i < 5; i++) scanf("%d", &shared_stuff->shared_matrix[i]);

	//Compares the first 5 numbers entered to see if there is a duplicate
	for (int i = 0; i < 5; i++){
		for (int j = 0; j < 5; j++){
			//Will not compare shared_matrix[i] and shared_matrix[j] if i = j
			if (i != j){
				if (shared_stuff->shared_matrix[i] == shared_stuff->shared_matrix[j]){
					printf("Please provide an array with 5 distinct values.\n");
					return(0);
				}
			}
		}
	}

	//Prints out the array before it is being sorted
	printf("Provided array is: ");
	for(int i = 0; i < 5; i++) { printf("%d ", shared_stuff->shared_matrix[i]); }
	printf("\n");
	return(1);
}

/**
 * Create semaphore
 */
static void make_semaphore(int argc){
//Create semaphore
	sem_id = semget((key_t)1234, 1, 0666 | IPC_CREAT);

	if (argc > 0){
		//Stop if semaphore can't be initialized
		if (!set_semvalue()){
			fprintf(stderr, "Failed to initialize semaphore\n");
			exit(EXIT_FAILURE);
		}
	}
}

/**
 * Create shared memory
 * returns the shared memory id
 */
static int make_shared_mem(){
	//Create shared memory
	int shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666 | IPC_CREAT);
	//Stop if the create failed
	if (shmid == -1){
		fprintf(stderr, "Creating shared memory failed\n");
		exit(EXIT_FAILURE);
	}

	//Enable access to the shared memory
	shared_memory = shmat(shmid, (void *)0, 0);
	//Stop if the enabling failed
	if (shared_memory == (void *)-1){
		fprintf(stderr, "Enabling access to shared memory has failed\n");
		exit(EXIT_FAILURE);
	}

	//Shared memory segment
	shared_stuff = (struct shared_use_st *) shared_memory;
	shared_stuff->shared_matrix;

	return shmid;
}

/**
 * Shared memory is destroyed
 */
static void destroy_shared_mem(int shmid){
	//Detatch shared memory
	if (shmdt(shared_memory) == -1){
		fprintf(stderr, "shmdt failed \n");
		exit(EXIT_FAILURE);
	}
	if (shmctl(shmid, IPC_RMID, 0) == -1){
		fprintf(stderr, "shmctl(IPC_RMID) failed\n");
		exit(EXIT_FAILURE);
	}
}











