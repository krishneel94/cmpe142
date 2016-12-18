#include<stdio.h>
#include<signal.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/syscall.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<stdbool.h>

int a=0;
int b=0;
bool printignore=0;
void signalhandle(int signum);
sig_atomic_t debug_mode=0;

int main(){
signal(SIGINT,signalhandle);
signal(SIGUSR1,signalhandle);
int count=0;
	while(1){
		sleep(2);
		if(printignore==0){
			count++;
			printf("\n");
			if(SIGINT==a){
				b=1;
				printf("\n DEBUG MODE ON...Iteration: %i",count); //ctrl+c must have been pressed to send SIGINT
				//printf("SUCCESS"); commented out for ease of grading
			}//end if
		}//end if

		else if(printignore==1){
			a=1;
			//printf("SUPRESSOR SUCCESS"); commented out for ease of grading
			
			//kill(getpid(),SIGUSR1); //after one interval of sleep send SIGUSR1 to end program to show SIGUSR1 works correctly, removing this line will allow toggle of print supression
		}//end if
	}//end while1
}//main

void signalhandle(int signum){
	if((signum==SIGINT)&&(b==0)){
		debug_mode=1;
		a=signum;
	} //end if

	if((signum==SIGINT)&&(b==1)){
		debug_mode=0;	
		printignore=1;
	}//end second if
	
	if((signum==SIGINT)&&(a==1)){
		a=b=0;
		printignore=0;
	}
	
	if(signum==SIGUSR1){
		exit(0);
	}// end if
}//end void

