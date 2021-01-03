/*
Problem7a.c
Decrypts the signature "174BC865C9023B4978B807A2CF24B15F4F382D20050307E253373C5AAE246ADC"
Uses the encryption function M = S^e mod n
*/

#include <stdio.h>
#include <openssl/bn.h>
#include <string.h>
#include <assert.h>

void printBN(char *msg, BIGNUM * a) {
	// Use BN_bn2hex(a) for hex string
	char * number_str = BN_bn2hex(a);
	//Prints out the number string
	printf("%s %s\n", msg, number_str);
	//Free the dynamically allocated memory
	OPENSSL_free(number_str);
}

//Convert hex string into int
int hex_to_int(char c){
        int first = c / 16 - 3;
        int second = c % 16;
        int result = first*10 + second;
        if(result > 9) result--;
        return result;
}

//Convert hex string into ASCII
int hex_to_ascii(char c, char d){
        int high = hex_to_int(c) * 16;
        int low = hex_to_int(d);
        return high+low;
}

//Convert ASCII into hex string
void string2hexString(char* input, char* output)
{
    int loop;
    int i; 
    
    i=0;
    loop=0;
    
    while(input[loop] != '\0')
    {
        sprintf((char*)(output+i),"%02X", input[loop]);
        loop+=1;
        i+=2;
    }
    //insert NULL at the end of the output string
    output[i++] = '\0';
}

/*Verifies if the message received came from a valid roadsisde unit.*/
void verify(char *msg, BIGNUM *M){
	int len = strlen(msg);
	//Declare output string with double size of input string
	//because each character of input string will be converted
	//in 2 bytes
	char hex_str[(len*2)+1];
	
	//Convert ASCII string into a hexadecimal
	string2hexString(msg, hex_str);

	//Convert into a string for comparison
	char * M_str = BN_bn2hex(M);
	
	//Compares between the decrypted message and the original message (before encryption).
	//Decrypted M should be the same as the plaintext
	assert(strcmp(M_str, hex_str) == 0);
	
	printf("%s \n", "Test passed.");
}


int main(){
	BN_CTX *ctx = BN_CTX_new();
	BIGNUM *n = BN_new();
	BIGNUM *e = BN_new();
	BIGNUM *d = BN_new();
	BIGNUM *M = BN_new();
	BIGNUM *S = BN_new();
	
	//Convert hexadecimal numbers into BIGNUM
	BN_hex2bn(&S, "174BC865C9023B4978B807A2CF24B15F4F382D20050307E253373C5AAE246ADC");
	BN_hex2bn(&n, "22E929B981FFC200B13E601177E398F1B965B34FD419420DD8DB603B35286145");
	BN_hex2bn(&e, "9EF23");
	BN_hex2bn(&d, "07A0CC8B662312154E670D2B767A6E5FE4607BE3215AE3CCD710D1418828D507");
	
	//Verify the signature
	BN_mod_exp(M, S, e, n, ctx);

	//Convert BIGNUM to hex
	char * msg_str = BN_bn2hex(M);
	
	//Convert hex into string
        int length = strlen(msg_str);
        int i;
        char buf = 0;
        printf("The decrypted messasge is: ");
        
        for(i = 0; i < length; i++){
                if(i % 2 != 0){
                        printf("%c", hex_to_ascii(buf, msg_str[i]));
                }else{
                        buf = msg_str[i];
			
                }
        }
        
	printf("\n");

	//Testing
	//Test to see if the encrypting the decrypted message using the public keys will 
	//provide the ciphertext.
	verify("Plate: GOOD 100; Clear Record", M);
}
