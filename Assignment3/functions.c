#include <string.h>
#include <stdlib.h>
#include "functions.h"
#include "employees_struct.h"

/*Linked List*/
typedef struct node{
	int val;
	struct node *next;
}node_t;

employees_struct employees[100];

/* Stores the four fields of the record according to the employee's information. */
void Insert(char *name, char *department, int employee_number, int salary){
	node_t *head = (node_t*) malloc(sizeof(node_t));
	node_t *current = head;

	int count = 0;
	//Traverses through the list
	while(current->next != NULL){
		current = current->next;
		count++;
	}
	count++;
	
	strcpy(employees[count].name, name);
	strcpy(employees[count].department, department);
	employees[count].employee_number = employee_number;
	employees[count].salary = salary;	
}

/* Returns the employee number of the name that's passed. */
int Check_employee_number(char name){
	node_t *head = (node_t*) malloc(sizeof(node_t));
	node_t *current = head;

	//Traverses through the list
	int count = 0;
	while(current->next != NULL){
		if (employees[count].name == &name){
			return employees[count].employee_number;
		}		
		current = current->next;
		count++;
	}
	return -1;	
}

/* Returns the salary of the employee number that's passed. */
int Check_salary(int employee_number){
	node_t *head = (node_t*) malloc(sizeof(node_t));
	node_t *current = head;

	//Traverses through the list
	int count = 0;
	while(current->next != NULL){
		if (employees[count].employee_number == employee_number){
			return employees[count].salary;
		}		
		current = current->next;
		count++;
	}
	return -1;
}

/* Returns te employee numbers of all employees that work in the department. */
int *Check(char department){
	int *emp_in_dep[100];
	int index = 0;
	node_t *head = (node_t*) malloc(sizeof(node_t));
	node_t *current = head;

	//Traverses through the list
	int count = 0;
	while(current->next != NULL){
		if (employees[count].department == &department){
			emp_in_dep[index] = &employees[count].employee_number;
			index++;
		}		
		current = current->next;
		count++;
	}
	return *emp_in_dep;
}

/* Delete the record of the employee with the employee number that's passed. */
void Delete(int employee_number){
	node_t *head = (node_t*) malloc(sizeof(node_t));
	node_t *current = head;

	int count = 0;
	//Traverses through the list
	while(current->next != NULL){
		node_t *curr2 = current;

		if (employees[count].employee_number == employee_number){
			int index = count;

			//Shifts the list of employee data by 1 to the left
			//so that the list does not have a NULL value in
			//betweeen data
			while(curr2->next != NULL){
				strcpy(employees[index].name, employees[index+1].name);
				strcpy(employees[index].department, employees[index+1].department);
				employees[index].employee_number = 			employees[index+1].employee_number;
				employees[index].salary = employees[index+1].salary;
				index++;
			} 

		}
		current = current->next;
		count++;
	}
}

int main(){
	Insert("rer", "dep", 13, 40);

}
