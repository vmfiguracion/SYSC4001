#include <stdio.h>
#include <string.h>

//https://stackoverflow.com/questions/5403103/hex-to-ascii-string-conversion
int hex_to_int(char c){
        int first = c / 16 - 3;
        int second = c % 16;
        int result = first*10 + second;
        if(result > 9) result--;
        return result;
}

int hex_to_ascii(char d){
        int high = 16;
        int low = hex_to_int(d);
        return low;
}

int main(){
        const char* st = "506C6174653A2041424344203132333B204661696C65642053746F70";
        int length = strlen(st);
        int i;
        char buf = 0;
        for(i = 0; i < length; i++){
                if(i % 2 != 0){
                        printf("%c", hex_to_ascii(st[i]));
                }else{
                        buf = st[i];
			
                }
        }
	printf("\n");
}
