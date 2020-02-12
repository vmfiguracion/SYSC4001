#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int main(){
	int n = 4;
	pid_t pid_children[n]; //Ensure that each child has the same parent

	char *message;
	

	for(int i = 0; i < n; i++){
		//Forking failed
		if((pid_children[i] = fork()) < 0){
			perror("fork");
			exit(1);
		//Child processes
		} else if(pid_children[i] == 0){
			printf("%d\n", getppid());
		}
	}


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
	exit(0);
}
