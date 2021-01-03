/* dash_shell_test.c  */

/* A program that runs a dash shell */
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

const char shellcode[] =

 // "\x31\xc0" 			/* xorl %eax,%eax 	Set %eax to $0dx5 (setuid() system call number)	*/
 // "\x31\xdb" 			/* xorl %ebx,%ebx 	Set %ebs to 0									*/
 // "\xb0\xd5" 			/* movb $0xd5,%al 	Set %eax to $0dx5 (setuid() system call number)	*/
  //"\xcd\x80" 			/* int $0x80 		Execute system call								*/
  "\x31\xc0" 			/* xorl %eax,%eax */
  "\x50" 				/* pushl %eax */
  "\x68""//sh" 			/* pushl $0x68732f2f */
  "\x68""/bin" 			/* pushl $0x6e69622f */
  "\x89\xe3" 			/* movl %esp,%ebx */
  "\x50" 				/* pushl %eax */
  "\x53" 				/* pushl %ebx */
  "\x89\xe1" 			/* movl %esp,%ecx */
  "\x99"				/* cdq */
  "\xb0\x0b" 			/* movb $0x0b,%al */
  "\xcd\x80" 			/* int $0x80 */
;

int main()
{
     char *argv[2];
     argv[0] = "/bin/sh";
	 argv[1] = NULL;
	 setuid(0);
	 execve("/bin/sh", argv, NULL);
	 return 0;
}

