#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(){

	int fd1[2];	

	if (pipe(fd1) < 0){ 
        printf("Pipe Failed \n"); 
        return 1; 
    }  
    printf("Pipe Created \n");   
    
    pid_t p1 = fork(); 

    if (p1 < 0){ 
        printf("Fork Failed \n"); 
        return 1; 
    }    
    else if (p1 > 0){ // parent

    	char* input = "Hello I am Parent";    	

    	printf("Input : %s\n", input);
    	printf("Strlen Input : %ld\n", strlen(input));

        close(fd1[0]); // closing reading end of pipe
    	write(fd1[1], input, strlen(input));
    	close(fd1[1]);

    	pid_t p2 = fork();    	

    	if (p2 < 0){ 
            printf("Fork Failed \n"); 
            return 1;
        }
        else if ( p2 == 0){ // child 2nd
        	printf("2nd child \n");
        	char output[20]; 
        	//memset(output,'\0',sizeof(output));       	

        	//printf("output %s\n", output);
    	    //printf("Strlen output %ld\n", strlen(output));

            close(fd1[1]); //closing writing end of pipe
        	//read(fd1[0],output,strlen(output));
        	read(fd1[0],output,20);
        	close(fd1[0]);
        	printf ("Child 2nd : %s \n", output);
        	
        	exit(0);
        }
        wait(NULL);

    } // else if (p1 > 0){ // parent
    else if (p1 == 0){ // child 1
        printf("Fisrt child \n");
        char output1[20];
        //memset(output1,'\0',sizeof(output1));         

        //printf("output1 %s\n", output1);
    	//printf("Strlen output1 %ld\n", strlen(output1));
        
        close(fd1[1]); //closing writing end of
        //read(fd1[0],output1,strlen(output1));
        read(fd1[0],output1,20);
        printf ("Child 1st : %s \n", output1);
        close(fd1[0]);
        exit(0);
    }

	return 0;
}