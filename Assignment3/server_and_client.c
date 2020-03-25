#include <sys/msg.h>
#include "employees_struct.h"
#include "functions.h"

#define SERVER_MQUEUE 1234
#define CLIENT_MQUEUE 4321

struct msg_passed{
	long int msg_key; /* for client pid */
	employees_struct employee_data; //Struct for employee data
}

//Two variables with file scope hold the two queue identifiers returned from the msgget function
static int serv_qid = -1;
static int cli_qid = -1;

//SERVER -------------------------------------------------------------------------------------------
//Make server responsible for creating both mesage ueues
int server_starting(){
	#if DEGUB_TRACE
		printf("%d :-server_starting()\n", getpid());
	#endif
	
	serv_qid = msgget((key_t)SERVER_MQUEUE, 0666 | IPC_CREAT);
	if (serv_qid == -1) return(0);
	
	cli_qid = msgget((key_t)CLIENT_MQUEUE, 0666 | IPC_CREAT);
	if (cli_qid == -1) return(0);
	
	return(1);
}

//When the server ends, the file-scope variables are set to illefal values. Will catcch any bugs
//if the server attempts to send messages after it has called server_ending.
void server_ending(){
	#if DEGUB_TRACE
		printf("%d :-server_ending()\n", getpid());
	#endif
	
	(void)msgctl(serv_qid, IPC_RMID, 0);
	(void)msgctl(cli_qid, IPC_RMID, 0);
	
	serv_qid = -1;
	cli_qid = -1;
}

//Read function reads a message of any time (ie from any client) from the queue, and it returns
//the data part (ignoring type) of the message
int read_request_from_client(employees_struct *rec_ptr){
	struct msg_passed my_msg;
	
	#if DEGUB_TRACE
		printf("%d :-read_request_from_client()\n", getpid());
	#endif
	
	if (msgrcv(serv_qid, (void *)&my_msg, sizeof(*rec_ptr), 0, 0) == -1) {
		return(0);
	}
	*rec_ptr = my_msg.employee_data;

	return(1);
}

//Sending a response uses the client process ID it was stored in the request to address the message
int send_resp_to_client(const employees_struct mess_to_send){
	struct msg_passed my_msg;
	#if DEBUG_TRACE
		printf("%d :- send_resp_to_client()\n", getpid());
	#endif
	
	my_msg.employee_data = mess_to_send;
	my_msg.msg_key = mess_to_send.client_pid;
	if (msgsnd(cli_qid, (void *)&my_msg, sizeof(mess_to_send), 0) == -1) {
		return(0);
	}
}

//CLIENT-------------------------------------------------------------------------------------------------
//Client needs to find the server & client queue identifiers. DOES NOT CREATE QUEUE. Will fail if server isn't running
//b/c message queues won't exist
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

//To send a message to the server, store the data inside a structure. Must set the message key.
//Leaving key undefined would mean that it takes a random value, so the function could occasionally
//if the value is 0
int send_mess_to_server(employees_struct mess_to_send){
	struct msg_passed my_msg;
	#if DEBUG_TRACE
		printf("%d :- send_mess_to_server()\n", getpid());
	#endif
	my_msg.employee_data = mess_to_send;
	my_msg.msg_key = mess_to_send.client_pid;
	if (msgsnd(serv_qid, (void *)&my_msg, sizeof(mess_to_send), 0) == -1) {
		//perror("Message send failed");
		return(0);
	}
	return(1);
}

//When a client retrieves a message from the server it uses its proesses ID to receive only
//messages addressed to itself
int read_resp_from_server(employees_struct *rec_ptr){
	struct msg_passed my_msg;
	#if DEBUG_TRACE
		printf("%d :- read_resp_from_server()\n", getpid());
	#endif
	if (msgrcv(cli_qid, (void *)&my_msg, sizeof(*rec_ptr), getpid(), 0) == -1) {
		return(0);
	}
	*rec_ptr = my_msg.employee_data;
	return(1);
}

//To retain complete compatibility with pipe_imp.c 4 extra functions are defined and are empty.
int start_resp_to_client(const employees_struct mess_to_send){
	return(1);
}

void end_resp_to_client(void){
}

int start_resp_from_server(void){
	return(1);
}

void end_resp_from_server(void){
}

