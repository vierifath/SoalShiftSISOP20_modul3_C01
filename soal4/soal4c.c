#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 

int main() {
    int pfds[2];
    
    pipe(pfds);

    if (pipe(pfds)==-1) 
	{ 
		fprintf(stderr, "Pipe Failed" ); 
		return 1; 
	} 

    pid_t pid = fork();

    if(pid < 0 ) {
        perror("fork error");
    }

    else if(pid==0) {
        close(1);
        dup(pfds[1]);
        close(pfds[0]);
        execlp("/bin/ls","ls",NULL);
    }
    else {
        close(0);
        dup(pfds[0]);
        close(pfds[1]);
        execlp("/usr/bin/wc","wc","-l",NULL);
    }
}
