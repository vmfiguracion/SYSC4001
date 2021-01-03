/*
Problem5.c
Decrypts the ciphertext "19C308D172F3E6CB4A9E2D93FC75D662B97C6743FF94BE50CF5F788106C8AA71"
Uses the encryption function M = C^d mod n
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

/*Checks if encrypting a decrypted message will restore the original ciphertext.*/
void check(BIGNUM *M, BIGNUM *C, BIGNUM *e, BIGNUM *n, BN_CTX *ctx){
	BIGNUM *encrypt_msg = BN_new();
	
	//Enrypt message into ciphertext. C = M^e mod n.
	BN_mod_exp(encrypt_msg, M, e, n, ctx);
	
	//Convert into a string for comparison
	char * C_str = BN_bn2hex(C);
	char * encrypt_msg_str = BN_bn2hex(encrypt_msg);
	
	//Compares between the decrypted message and the original message (before encryption).
	//Decrypted M should be the same as the plaintext
	assert(strcmp(C_str, encrypt_msg_str) == 0);
	
	printf("%s \n", "Test passed.");
}


int main(){
	BN_CTX *ctx = BN_CTX_new();
	BIGNUM *n = BN_new();
	BIGNUM *e = BN_new();
	BIGNUM *d = BN_new();
	BIGNUM *M = BN_new();
	BIGNUM *C = BN_new();
	
	//Convert hexadecimal numbers into BIGNUM
	BN_hex2bn(&C, "19C308D172F3E6CB4A9E2D93FC75D662B97C6743FF94BE50CF5F788106C8AA71");
	BN_hex2bn(&n, "22E929B981FFC200B13E601177E398F1B965B34FD419420DD8DB603B35286145");
	BN_hex2bn(&e, "9EF23");
	BN_hex2bn(&d, "07A0CC8B662312154E670D2B767A6E5FE4607BE3215AE3CCD710D1418828D507");
	
	//Decrypt message
	BN_mod_exp(M, C, d, n, ctx);

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
	check(M, C, e, n, ctx);
}
