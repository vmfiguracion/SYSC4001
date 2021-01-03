/*
Problem6a.c
Creates a digital signature and encrypts the message
"M = Plate: LMNO 456; Illegal Turn"
Uses the encryption function S = M^d mod n
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

/*Checks if decrypting an encrypted message will restore the original message.*/
void check(BIGNUM *M, BIGNUM *S, BIGNUM *e, BIGNUM *n, BN_CTX *ctx){
	BIGNUM *decrypt_msg = BN_new();
	
	//Decrypt ciphertext into plaintext. M = S^e mod n.
	BN_mod_exp(decrypt_msg, S, e, n, ctx);
	
	//Convert into a string for comparison
	char * M_str = BN_bn2hex(M);
	char * decrypt_msg_str = BN_bn2hex(decrypt_msg);
		
	//Compares between the decrypted message and the original message (before encryption).
	//Decrypted M should be the same as the plaintext
	assert(strcmp(M_str, decrypt_msg_str) == 0);
	printf("%s \n", "Test passed.");
}


int main(){
	BN_CTX *ctx = BN_CTX_new();
	BIGNUM *n = BN_new();
	BIGNUM *e = BN_new();
	BIGNUM *d = BN_new();
	BIGNUM *M = BN_new();
	BIGNUM *S = BN_new();
	char ascii_str[] = "Plate: LMNO 456; Illegal Turn";
	int len = strlen(ascii_str);
	//Declare output string with double size of input string
	//because each character of input string will be converted
	//in 2 bytes
	char hex_str[(len*2)+1];
	
	//Convert ASCII string into a hexadecimal
	string2hexString(ascii_str, hex_str);

	//Convert hexadecimal numbers into BIGNUM
	BN_hex2bn(&M, hex_str);
	BN_hex2bn(&n, "22E929B981FFC200B13E601177E398F1B965B34FD419420DD8DB603B35286145");
	BN_hex2bn(&e, "9EF23");
	BN_hex2bn(&d, "07A0CC8B662312154E670D2B767A6E5FE4607BE3215AE3CCD710D1418828D507");
	
	//Sign the message
	BN_mod_exp(S, M, d, n, ctx);
	printBN("The signature is: ", S);

	//Testing
	//Test to see if the signature generates can be verified by comparing the message using
	//the public keys (e,n) and the original message.
	check(M, S, e, n, ctx);
}
