#include <stdio.h>
#include <string.h>

//https://www.includehelp.com/c/convert-ascii-string-to-hexadecimal-string-in-c.aspx#:~:text=To%20convert%20an%20ASCII%20string,(like%20int%2C%20char).
//function to convert ascii char[] to hex-string (char[])
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

int main(){
    char ascii_str[] = "Plate: LMNO 456; Illegal Turn";
    //declare output string with double size of input string
    //because each character of input string will be converted
    //in 2 bytes
    int len = strlen(ascii_str);
    char hex_str[(len*2)+1];
    
    //converting ascii string to hex string
    string2hexString(ascii_str, hex_str);
    
    printf("ascii_str: %s\n", ascii_str);
    printf("hex_str: %s\n", hex_str);
    
    return 0;
}

