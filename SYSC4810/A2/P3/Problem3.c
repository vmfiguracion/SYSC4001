/*
Problem3.c
Calculates d given p, q, and e.
Uses the multiplicative inverse function.
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

/*Checks if decrypting an encrypted message will restore the original message.*/
void check(char *PT, BIGNUM *e, BIGNUM *d, BIGNUM *p, BIGNUM *q, BN_CTX *ctx){
	BIGNUM *n = BN_new();
	BIGNUM *BN_PT = BN_new();
	BIGNUM *C = BN_new();
	BIGNUM *M = BN_new();
	
	//Convert plainext (PT) into BIGNUM
	BN_hex2bn(&BN_PT, PT);
	//Compute n
	BN_mul(n, p, q, ctx);
	
	//Create ciphertext (ie encrypt). C = PT^e mod n.
	BN_mod_exp(C, BN_PT, e, n, ctx);
	
	//Decrypt ciphertext into plaintext. M = C^d mod n.
	BN_mod_exp(M, C, d, n, ctx);
	
	//Convert into a string for comparison
	char * M_str = BN_bn2hex(M);
	//Decrypted M should be the same as the plaintext
	assert(strcmp(M_str, PT) == 0);
	printf("%s \n", "Test passed.");
}
	
int main(){
	BN_CTX *ctx = BN_CTX_new();
	BIGNUM *one = BN_new();
	BIGNUM *p = BN_new();
	BIGNUM *pminus1 = BN_new();
	BIGNUM *q = BN_new();
	BIGNUM *qminus1 = BN_new();
	BIGNUM *e = BN_new();
	BIGNUM *d = BN_new();
	BIGNUM *totN = BN_new();
	BIGNUM *randmsg = BN_new();
	
	//Convert hexadecimal numbers into BIGNUM
	BN_hex2bn(&p, "B5E26E74EB5068C447D660920255A6EF");
	BN_hex2bn(&q, "3122EFFD6FF0246608195B81D3111B0B");
	BN_hex2bn(&e, "34CA9");
	BN_dec2bn(&one, "1");
	
	//p-1
	BN_sub(pminus1, p, one);
	//q-1
	BN_sub(qminus1, q, one);
	
	//Totient n
	BN_mul(totN, pminus1, qminus1, ctx);
	
	//Multiplicative inverse. (e x d) mod totN = 1. Finds d.
	BN_mod_inverse(d, e, totN, ctx);
	printBN("The private key d is ", d);
	
	//Testing
	//Create random message
	BN_rand(randmsg, 128, 0, 0);
	char * number_str = BN_bn2hex(randmsg);
	
	//Test to see if the correct private number d has been found.
	check(number_str, e, d, p, q, ctx);
}
