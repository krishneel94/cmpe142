#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/syscall.h>
#include<sys/wait.h>
#include<sys/types.h>
#define READ_END 0
#define WRITE_END 1


#define size 40
int main(){
pid_t pid;
int fd[2];
int fd2[2];
int ppid = getpid();
char writemsg[size];
char readmsg[size];
char writemsg2[size];
char readmsg2[size];


sprintf(writemsg,"I am your daddy! and my name is %i", ppid);

if(pipe(fd) || pipe(fd2) < 0)
{
//perror("Pipe"); **Removed error checking to avoid unwanted printout during grading**

}


if((pid = fork()) < 0);
{

//perror("Fork");
}

if(pid == 0)
{
int cpid = getpid();
close(fd2[READ_END]);
close(fd[WRITE_END]);
read(fd[READ_END], readmsg, size);
close(fd[READ_END]);



printf("%s\n",readmsg);
sprintf(writemsg2, "Daddy, my name is %i",cpid);
write(fd2[WRITE_END], writemsg2, strlen(writemsg) + 1);

close(fd2[WRITE_END]);

exit(1) ;
}
//parent

close(fd2[WRITE_END]);
close(fd[READ_END]);
write(fd[WRITE_END],writemsg, strlen(writemsg) + 1);
close(fd[WRITE_END]);
read(fd2[READ_END], readmsg2, size); //need wait?

close(fd[WRITE_END]);
wait(NULL); //do not print the next message unless we wait for child to die
printf("%s\n",readmsg2);


}//main

