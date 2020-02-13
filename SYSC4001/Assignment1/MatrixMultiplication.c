#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

//Q[i][k] = sum(M[i][j]*N[j][k])
int main(){
	int n = 4;
	int i, j, k;
	//pid_t pid_children[n]; //Ensure that each child has the same parent


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

	int Q[4][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};

	//Q before multiplication.
	//Should be: Q = [0 0 0 0
	//				  0 0 0 0
	//				  0 0 0 0
	//				  0 0 0 0]
	printf("Q = [");
	for (int a = 0; a < n; a++){
		for (int b = 0; b < n; b++){
			printf("%d ", Q[a][b]);
		}
		printf("\n");
	}
	printf("]");


	//Creating child processes
	for (int childNum = 0; childNum < n; childNum++){
		//In child process
		if (fork() == 0){
			//Deals with one column of the row
			//eg Q[1][3] = P13
			for(k = 0; k < n; k++){

				//Deals with one term of the sum
				//eg j=2: (M[i][2] * N[2][k])
				printf("Row %d ", childNum);
				for(j = 0; j < n; j++){
					Q[childNum][k] += (M[childNum][j] * N[j][k]);
					printf("%d ", (Q[childNum][k] + 1));
				}
				printf("\n");

			}

		}
	}

	/*

	//Forking has failed.
	if (fork() < 0) {
		perror("Forking has failed");
		abort();



	} else if (fork() == 0) {
		printf("Child with %d process ID from parent %d is running...\n", getpid(), getppid());

		for (i = 0; i < n; ++i) {

			//Deals with one column of the row
			//eg Q[1][3] = P13
			for(k = 0; k < n; k++){

				//Deals with one term of the sum
				//eg j=2: (M[i][2] * N[2][k])
				for(j = 0; j < n; j++){
					Q[i][k] += (M[i][j] * N[j][k]);
				}
			}
		}
	}
*/
	sleep(10);

	/*
	//Logic
	for (i = 0; i < n; i++){
		//Deals with one row of Q at row i
		//eg Q[1] = [P11, P12, P13, P14]
		for(k = 0; k < n; k++){
			//Deals with one column of the row
			//eg Q[1][3] = P13
			for(j = 0; j < n; j++){
				//Deals with one term of the sum
				//eg j=2: (M[i][2] * N[2][k])

				Q[i][k] += (M[i][j] * N[j][k]);
			}
		}
	}
	*/

	//Q after multiplication.
	//Should be: Q = [670 710 930 1150
	//				  175 243 353 463
	//				  68  144 232 320
//					  176 316 492 668]
	printf("Q = [");
	for (int a = 0; a < n; a++){
		for (int b = 0; b < n; b++){
			printf("%d ", Q[a][b]);
		}
		printf("\n");
	}
	printf("]");









	/*
	//char *message;
	for (i = 0; i < n; ++i) {

	  if ((pid_children[i] = fork()) < 0) {
		  perror("fork");
		  abort();

	  } else if (pid_children[i] == 0) {
		  printf ("child process #%d: the value returned by fork is %d\n", i, getppid());

	  }
	  /*else {
		  printf ("parent process: the value returned by fork is %d\n\n", getppid());
	  }

	}
**/

/**
	for(int i = 0; i < n; i++){

		switch(pid_children[i]){
		//Forking failed
		case -1:
			perror("Fork failed");
			exit(1);
		//Child was able to be forked
		case 0:
			printf ("child process #%d: the value returned by fork is %d\n", i, getppid());
			break;
		//Parent process
		default:
			printf ("parent process: the value returned by fork is %d\n\n", getppid());
			break;
		}
	}**/
	//sleep(10);




/*
	//Switch between parent and child(ren)
	switch(pid){
		//Fork failed
		case -1:
			perror("fork failed");
			exit(1);

		//Child was able to be forked
		case 0:
			message = "This is child";
			printf ("child process: the value returned by fork is %d\n", getppid());
			pid = fork();
			
			//Switch between child of parent (child) or child or child (grandchild)
			switch(pid){
				//Fork failed
				case -1:
					perror("fork failed");
					exit(1);

				//Grandchild was able to be forked
				case 0:
					message = "This is child of child / secondary child process / grandchild";
					n = 15;
					break;
				
					message = "This is the parent of child / initial child process";
					n = 5;
					break;
			}	
			n = 15;
			break;

		default:
			message = "This is the parent";
			printf ("parent process: the value returned by fork is %d\n", getppid());
			n = 5;
			break;
	}

	for (;n > 0; n--){
		puts(message);
		sleep(1);
	}
	exit(0);*/
}
