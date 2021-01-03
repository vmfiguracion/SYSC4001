/*
Problem3c.c
Enrolling users
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addForbiddenPasswords(char *forbiddenPassword){
	//Get file of forbidden passwords
	FILE *file = fopen("forbiddenpasswords.txt", "a");
	fputs(forbiddenPassword, file);

}

void passwordChecker(char *username, char *password){
	int upper = 0;
	int lower = 0;
	int digit = 0;
	int special = 0;
	int length = strlen(password);
	
	char forbiddenPasswords[100];
	char line[80];
	
	//Get file of forbidden passwords
	FILE *file = fopen("forbiddenpasswords.txt", "r");

	//Checks if the username and password are the same
	if(strcmp(username, password) == 0){
		printf("Password is the same as the username. Please choose another password: ");
		scanf("%s", password);
		passwordChecker(username, password);
	}
	
	//Checks if the passwords has a common format (ie phone number, lisence plate, calendar date, etc)
	//Phone number
	if(length == 10){
		int count = 0;
		for (int i = 0; i < length; i++){
			if (password[i] >= '0' && password[i] <= '9'){
				count++;
			}
			if (count == 10){
				printf("Password has a common format. Please choose another password: ");
				scanf("%s", password);
				passwordChecker(username, password);
			}
		}
	}
	
	//Checks against common weak passwords and passwords with common dates listed in forbiddenpasswords.txt
	while(fscanf(file, "%s", forbiddenPasswords) == 1){
		if(strcmp(forbiddenPasswords, password) == 0){
			printf("Password is weak. Please choose another password: ");
			scanf("%s", password);
			passwordChecker(username, password);
		} 
	}
	
	//Checks if length is between 8-12 characters
	if(length > 7 && length < 13){
		//Checks if it has at least one upper case, one lower case, one numerical digit, and one special character from the list
		for (int i = 0; i < length; i++){
			//Upper case
			if (password[i] >= 'A' && password[i] <= 'Z'){
				upper = 1;
			}
			//Lower case
			if (password[i] >= 'a' && password[i] <= 'z'){
				lower = 1;
			}
			//Numerical digit
			if (password[i] >= '0' && password[i] <= '9'){
				digit = 1;
			}
			//Special case
			if (password[i] == '!' || password[i] == '@' || password[i] == '#' ||
			    password[i] == '$' || password[i] == '%' || password[i] == '?' ||
			    password[i] == '*'){
				special = 1;
			}
		
			//All criteria is satisfied
			if (upper == 1 && lower == 1 && digit == 1 && special == 1){
				printf("Perfect, you are now registered.\n");
				return;
			}			
		}
	
		//If after going through the password it's still not satisfied, ask for another password.
		if (upper == 0 || lower == 0 || digit == 0 || special == 0){
			printf("Password does not meet the criteria. Please choose another password: ");
			scanf("%s", password);
			passwordChecker(username, password);
		}
	}
	else{
		printf("Password is too small or too big. Please choose another password: ");
		scanf("%s", password);
		passwordChecker(username, password);
	}
	
	/*TODO
	Check against passwords with common format: Calendar Dates
	*/

}

int main(){
	char username[100];
	char password[100];
	char name[100];
	char role[100];

	printf("Name: ");
	scanf("%s", name);
	printf("What is your role in the company? ");
	scanf("%s", role);
	printf("Choose a username: ");
	scanf("%s", username);
	printf("Choose a password between 8-12 characters.");
	scanf("%s", password);
	
	passwordChecker(username, password);
	return 0;
}

