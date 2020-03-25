#define MAX_TEXT 12

typedef struct {
	pid_t client_pid;
	char name[MAX_TEXT];
	char department[MAX_TEXT];
	int employee_number;
	int salary;
}employees_struct;
