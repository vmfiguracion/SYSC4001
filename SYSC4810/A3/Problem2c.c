/*
Problem2c.c
Password file
*/

#include <openssl/evp.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Generates a random 128 bit long hex number
void saltGenerator(){
	#define STR_LEN 128
	unsigned char str[STR_LEN] = {0};
   	const char *hex_digits = "0123456789ABCDEF";
 
 	//Intializes random number generator
   	srand((unsigned) time(0));

   	for(int i = 0 ; i < STR_LEN; i++ ) {
      str[i] = hex_digits[ ( rand() % 16 ) ];
   	}
   	//printf("%s\n", str);
   	//return str;
}

/*char space_to_underscore(char *string){
	int length = strlen(string);
	char newString[length];

	for (int i = 0; i < length; i++){
		if (string[i] == ' '){
			newString[i] = '_';
		} else {
			newString[i] = string[i];
		}	
	}
	return *newString;
}*/

/*void addRecord(char *username, char *password, char *role, char *name){
	//For generating 128 bit long hex number
	#define STR_LEN 128
	char salt[STR_LEN];
   	const char* hex_digits = "0123456789ABCDEF";

   	//Intializes random number generator
   	srand((unsigned) time(0));

   	for(int i = 0 ; i < STR_LEN; i++ ) {
    	salt[i] = hex_digits[ ( rand() % 16 ) ];
   	}
   	
	char entry[500];
	unsigned char hashedPassword[EVP_MAX_MD_SIZE];
	unsigned int md_len = strlen(password);

	EVP_MD_CTX *ctx = EVP_MD_CTX_create(); //Creates digest context
	const EVP_MD *type = EVP_sha512();

	//Open file
	FILE *file = fopen("passwd.txt", "a");
	
	//Generate hashed password
	EVP_DigestInit_ex(ctx, type, NULL);//NULL because only using one hash algorithm
	EVP_DigestUpdate(ctx, password, strlen(password));
	EVP_DigestUpdate(ctx, salt, 128);
	EVP_DigestFinal_ex(ctx, hashedPassword, &md_len);
	EVP_MD_CTX_destroy(ctx);

	//Store information as UserName:PlainTextSalt:HashedPassword:Role:Name
	strcpy(entry, username);
	strcat(entry, ":"); //Delimiter
	strcat(entry, salt);
	strcat(entry, ":"); //Delimiter
	strcat(entry, hashedPassword);
	strcat(entry, ":"); //Delimiter
	strcat(entry, role);
	strcat(entry, ":"); //Delimiter
	strcat(entry, name);
	fputs(entry, file);

	EVP_cleanup();
}*/


void addRecord(char *username, char *password, char *role, char *name){
	char entry[500];
	unsigned char hashedPassword[EVP_MAX_MD_SIZE];
	unsigned int md_len = strlen(password);
//printf("a");
	EVP_MD_CTX *ctx = EVP_MD_CTX_create(); //Creates digest context
	const EVP_MD *type = EVP_sha512();
//printf("b");
	//Open file
	FILE *file = fopen("passwd.txt", "a");
	//Get rid of spaces
	//char _role = space_to_underscore(role);
	//char _name = space_to_underscore(name);
	//printf("c");
	//Generate salt value
	saltGenerator();
	//printf("%s", salt);
//printf("d");
	//Generate hashed password
	EVP_DigestInit_ex(ctx, type, NULL);//NULL because only using one hash algorithm
	EVP_DigestUpdate(ctx, password, strlen(password));
	EVP_DigestUpdate(ctx, salt, 128);
	EVP_DigestFinal_ex(ctx, hashedPassword, &md_len);
	EVP_MD_CTX_destroy(ctx);
//printf("e");
	//Store information as UserName:PlainTextSalt:HashedPassword:Role:Name
	strcpy(entry, username);
	strcat(entry, ":"); //Delimiter
	strcat(entry, salt);
	strcat(entry, ":"); //Delimiter
	strcat(entry, hashedPassword);
	strcat(entry, ":"); //Delimiter
	strcat(entry, role);
	strcat(entry, ":"); //Delimiter
	strcat(entry, name);
	fputs(entry, file);
//printf("f");
	EVP_cleanup();
	//printf("g");
}


void getRecord(char *username, char *password){
	char buffer[500];
	char user[100];
	char salt[128];
	char hash[200];
	char role[50];
	char name[100];

	//Open file
	FILE *file = fopen("passwd.txt", "r");

	//Use username to get plaintext salt and hashed password
	fscanf(file, "%s", buffer);
	//fscanf(file,"%[^:]s%[^:]s%[^:]s%[^:]s%[^:]s",user,salt,hash,role,name);
	//printf("%s, %s, %s, %s, %s",user,salt,hash,role,name);
	printf("%s\n", buffer);

	/*TODO
	Use username to get plaintext salt and hashed password
	Compute hashed password from salt and given password
	Compare computed password from stored hashed password
	Grant/Deny access
	*/
}

int main(){
	//addRecord("mischalowery", "1234567890", "Regular Client", "Mischa Lowery");
	//getRecord("mischalowery", "1234567890");
	
	/*char username[] = "mischalowery";
	char password[] = "1234567890";
	char role[] = "Regular Client";
	char name[] = "Mischa Lowery";
	
	
	//For generating 128 bit long hex number
	#define STR_LEN 128
	char salt[STR_LEN];
   	const char* hex_digits = "0123456789ABCDEF";

   	//Intializes random number generator
   	srand((unsigned) time(0));

   	for(int i = 0 ; i < STR_LEN; i++ ) {
    	salt[i] = hex_digits[ ( rand() % 16 ) ];
   	}
   	
	char entry[500];
	unsigned char hashedPassword[EVP_MAX_MD_SIZE];
	unsigned int md_len = strlen(password);

	EVP_MD_CTX *ctx = EVP_MD_CTX_create(); //Creates digest context
	const EVP_MD *type = EVP_sha512();

	//Open file
	FILE *file = fopen("passwd.txt", "a");
	
	//Generate hashed password
	EVP_DigestInit_ex(ctx, type, NULL);//NULL because only using one hash algorithm
	EVP_DigestUpdate(ctx, password, strlen(password));
	EVP_DigestUpdate(ctx, &salt, strlen(salt));
	EVP_DigestFinal_ex(ctx, hashedPassword, &md_len);
	EVP_MD_CTX_destroy(ctx);

	//Store information as UserName:PlainTextSalt:HashedPassword:Role:Name
	
	strcpy(entry, username);
	strcat(entry, ":"); //Delimiter
	strcat(entry, salt);
	/*strcat(entry, ":"); //Delimiter
	strcat(entry, hashedPassword);
	strcat(entry, ":"); //Delimiter
	strcat(entry, role);
	strcat(entry, ":"); //Delimiter
	strcat(entry, name);
	fputs(entry, file);

	EVP_cleanup();*/

 	exit(0);
	
}
