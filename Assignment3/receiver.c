#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include <sys/msg.h>

//Receiver

struct employees_struct employees;

int main(){
	int running = 1;
	int msgid;
	struct my_msg_st some_data;
	long int msg_to_receive = 1;

	//Set up message queue
	msgid = msgget((key_t)1234, 0666 | IPC_CREAT);

	if (msgid == -1){
		fprintf(stderr, "msgget failed with error: %d\n", errno);
		exit(EXIT_FAILURE);
	}

	//Messages are retrieved from queue until an end message is encountered
	//Message queue is deleted
	while(running){
		if (msgrcv(msgid, (void *) &some_data, BUFSIZ, msg_to_receive, 0) == -1){
			fprintf(stderr, "msgrcv failed with error: %d\n", errno);
			exit(EXIT_FAILURE);
		}
		printf("You wrote: %s", some_data.some_text);
		if (strncmp(some_data.some_text, "end", 3) == 0){
			running = 0;
		}
	}

	if (msgctl(msgid, IPC_RMID, 0) == -1){
		fprintf(stderr, "msgctl(IPC_RMID) failed \n");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
