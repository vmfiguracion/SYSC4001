#ifndef FUNCTIONS_DOT_H
#define FUNCTIONS_DOT_H

/* Stores the four fields of the record according to the employee's information. */
extern void Insert(char *name, char *department, int employee_number, int salary);

/* Returns the employee number of the name that's passed. */
extern void Check_employee_number(char name);

/* Returns the salary of of the employee number that's passed. */
extern void Check_salary(int employee_number);

/* Returns te employee numbers of all employees that work in the department. */
extern void Check(char department);

/* Delete the record of the employee with the employee number that's passed. */
extern void Delete(int *employee_number);

#endif