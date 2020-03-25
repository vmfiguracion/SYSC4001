#include <sys/msg.h>
#include <stdio.h>
#include "employees_struct.h"
#include "functions.h"

#define SERVER_MQUEUE 1234
#define CLIENT_MQUEUE 4321

struct msg_passed{
	int request;
	int result;
	employees_struct employee_data; //Struct for employee data
};
struct msg_passed my_msg;

//Two variables with file scope hold the two queue identifiers returned from the msgget function
static int serv_qid = -1;
static int cli_qid = -1;

//Client needs to find the server & client queue identifiers. DOES NOT CREATE QUEUE. 
//Will fail if server isn't running because the message queues will not exist.
int client_starting(){
	#if DEBUG_TRACE
		printf("%d :- client_starting\n", getpid());
	#endif
	
	serv_qid = msgget((key_t)SERVER_MQUEUE, 0666);
	if (serv_qid == -1) return(0);

	cli_qid = msgget((key_t)CLIENT_MQUEUE, 0666);
	if (cli_qid == -1) return(0);

	return(1);
}

//When client ends, the file-scope variables are set to illegal values.
//Will catch any bugs where the client attempts to send messages after the client has called client_ending
void client_ending(){
	#if DEBUG_TRACE
		printf("%d :- client_ending()\n", getpid());
	#endif
	serv_qid = -1;
	cli_qid = -1;
}

//To send a message to the server, store the data inside a structure. 
//Must set the message key to know what which function from function.c will be used.
int send_mess_to_server(employees_struct mess_to_send, int i){

	#if DEBUG_TRACE
		printf("%d :- send_mess_to_server()\n", getpid());
	#endif

	my_msg.employee_data = mess_to_send;
	my_msg.request = i;
	
	if (msgsnd(serv_qid, (void *)&my_msg, sizeof(my_msg), 0) == -1) {
		return(0);
	}
	printf("Message sent");
	return(1);
}

//Client receiving messages from the server.
int read_resp_from_server(){
	
	#if DEBUG_TRACE
		printf("%d :- read_resp_from_server()\n", getpid());
	#endif
	
	if (msgrcv(cli_qid, (void *)&my_msg, sizeof(my_msg), 0, 0) == -1) {
		return(0);
	}

	printf("%d", my_msg.result);
	return(1);
}
