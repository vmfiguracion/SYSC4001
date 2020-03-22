#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include <sys/msg.h>
#include "functions.h"
#include "message_struct.h"

#define BUFSIZ 512

//Sender

struct employees_struct *some_data;

int main(){
	int running = 1;
	int msgid;
	char buffer[BUFSIZ];

	//Set up message queue
	msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
	//If error occurs
	if (msgid == -1){
		fprintf(stderr, "msgget failed with error: %d\n", errno);
		exit(EXIT_FAILURE);
	}

	//Messages are retrieved from queue until an end message is encountered
	//Message queue is deleted
	while(running){
		printf("Enter some text: ");
		fgets(buffer, BUFSIZ, stdin);
		//strcpy(some_data->name, buffer);

		if(msgsnd(msgid, (void *)&some_data, MAX_TEXT, 0) == -1){
			fprintf(stderr, "msgsnd failed\n");
			exit(EXIT_FAILURE);
		}

		if(strncmp(buffer, "end", 3) == 0){
			running = 0;
		}
	}
	exit(EXIT_SUCCESS);
}


