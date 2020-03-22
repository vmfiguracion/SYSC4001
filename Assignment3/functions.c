#include <string.h>
#include "functions.h"
#include "message_struct.h"

struct message_struct *some_data;


/* Stores the four fields of the record according to the employee's information. */
void Insert(char *name, char *department, int employee_number, int salary){

	strcpy(some_data->name, name);
	strcpy(some_data->department, department);
	some_data->employee_number = employee_number;
	some_data->salary = salary;
}

/* Returns the employee number of the name that's passed. */
void Check_employee_number(char name){
	
}

/* Returns the salary of of the employee number that's passed. */
void Check_salary(int employee_number);

/* Returns te employee numbers of all employees that work in the department. */
void Check(char department);

/* Delete the record of the employee with the employee number that's passed. */
void Delete(int *employee_number);

int main(){
	Insert("rer", "dep", 13, 40);

}
