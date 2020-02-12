#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){
	int lengthOfArray = sizeof(&argv)/sizeof(argv[0]);

	//Prints the number of arguments given by the console
	printf("%d \n", argc);

	//Prints the arguments
	for (int arg = 1; arg < argc; arg++){
		printf ("%s \n", argv[arg]);
	}

	exit(0);
}
