#include <sys/msg.h>
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

//When the server ends, the file-scope variables are set to illegal values. Will catch any bugs if the server attempts to send messages after it has called server_ending.
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
	//struct msg_passed my_msg;
	
	#if DEGUB_TRACE
		printf("%d :-read_request_from_client()\n", getpid());
	#endif
	
	if (msgrcv(serv_qid, (void *)&my_msg, sizeof(*rec_ptr), 0, 0) == -1) {
		return 0;
	}
	*rec_ptr = my_msg.employee_data;
	int i = my_msg.request;

	switch(i){
		//Insert
		case 1:
			Insert(rec_ptr->name, rec_ptr->department, rec_ptr->employee_number, rec_ptr->salary);
			my_msg.result = 1;
			break;
		//Check employee number
		case 2:
			my_msg.result = Check_employee_number(*rec_ptr->name);
			break;
		//Check salary
		case 3:
			my_msg.result = Check_salary(rec_ptr->employee_number);
			break;
		//Check employees in a department
		case 4:
			my_msg.result = *Check(*rec_ptr->department);
			break;
		//Delete
		case 5:
			my_msg.result = Delete(rec_ptr->employee_number);
			break;
		//default
		default:
			return 0;
	
	}
	return 1;
}

//Sending a response to the client with the result of 
int send_resp_to_client(){
	//struct msg_passed my_msg;

	#if DEBUG_TRACE
		printf("%d :- send_resp_to_client()\n", getpid());
	#endif
	
	if (msgsnd(cli_qid, (void *)&my_msg, sizeof(my_msg), 0) == -1) {
		return(0);
	}
	return 1;
}
