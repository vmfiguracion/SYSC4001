#include <string.h>
#include "functions.h"
#include "employees_struct.h"

/*Linked List*/
typedef struct node{
	int val;
	struct node *next;
}node_t;

node_t *head = NULL;
head = (node_t *) malloc(sizeof(node_t));

head->val = 1;
head->next = NULL;

struct employees_struct *current_employee;
struct employees_struct employees[100];


/* Stores the four fields of the record according to the employee's information. */
void Insert(char *name, char *department, int employee_number, int salary){

	node_t *current = head;
	while(current->next != NULL){
		current = current->next;
	}
	
	/* Add new */
	current->next = (node_t *) malloc(sizeof(node_t));
	current->next->val = val;
	current->next->next = NULL;
	
	strcpy(current_employee->name, name);
	strcpy(current_employee->department, department);
	current_employee->employee_number = employee_number;
	current_employee->salary = salary;
	
	
}

/* Returns the employee number of the name that's passed. */
int Check_employee_number(char name){
	return;	
}

/* Returns the salary of the employee number that's passed. */
int Check_salary(int employee_number){
	return;
}

/* Returns te employee numbers of all employees that work in the department. */
char[] Check(char department){
	return;
}

/* Delete the record of the employee with the employee number that's passed. */
void Delete(int *employee_number){
}

int main(){
	Insert("rer", "dep", 13, 40);

}
