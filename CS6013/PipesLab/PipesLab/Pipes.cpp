#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <ctime>
#include <iostream>
#include <string>
////////////////////////////////////////////////////////////////
using namespace std;


int readPipe(){
    
    // We use two pipes
     // First pipe to send input string from parent
     // Second pipe to send concatenated string from child
  
     int fd1[2]; // Used to store two ends of first pipe
     int fd2[2]; // Used to store two ends of second pipe
  
     char fixed_str[] = "this is a test";
    
     char input_str[100];
     pid_t p;
  
     if (pipe(fd1) == -1) {
         fprintf(stderr, "Pipe Failed");
         return 1;
     }
     if (pipe(fd2) == -1) {
         fprintf(stderr, "Pipe Failed");
         return 1;
     }
  
     scanf("%s", input_str);
     p = fork();
  
     if (p < 0) {
         fprintf(stderr, "fork Failed");
         return 1;
     }
  
     // Parent process
     else if (p > 0) {
         char concat_str[100];
  
         close(fd1[0]); // Close reading end of first pipe
  
         // Write input string and close writing end of first
         // pipe.
         write(fd1[1], input_str, sizeof(input_str) + 1);
         
         close(fd1[1]);
  
         // Wait for child to send a string
         wait(NULL);
  
         close(fd2[1]); // Close writing end of second pipe
  
         // Read string from child, print it and close
         // reading end.
         
         read(fd2[0], concat_str, 100);
         printf("Concatenated string %s\n", concat_str);
         close(fd2[0]);
         
     }
  
     // child process
     else {
         
         close(fd1[1]); // Close writing end of first pipe
  
         // Read a string using first pipe
         char concat_str[100];
         
         read(fd1[0], concat_str, 100);
  
         // Concatenate a fixed string with it
         
         int k = sizeof(concat_str);
         int i;
         
         for (i = 0; i < 1*sizeof(fixed_str); i++)
             
             concat_str[k++] = fixed_str[i];
         
  
         concat_str[k] = '\0'; // string ends with '\0'
  
         // Close both reading ends
         
         close(fd1[0]);
         close(fd2[0]);
  
         // Write concatenated string and close writing end
         write(fd2[1], concat_str, sizeof(concat_str) + 1);
         close(fd2[1]);
  
         exit(0);
     }
    
    return 0;
}

int readWritePipe(char *argv[]){
    
    int fd[2];
    
        string childID = "";

        // create pipe descriptors
        pipe(fd);

        // fork() returns 0 for child process, child-pid for parent process.
        if (fork() != 0) {
            // parent: writing only, so close read-descriptor.
            close(fd[0]);

            // send the childID on the write-descriptor.
            //childID = 1;
            childID=argv[1];
            
            write(fd[1], &childID, sizeof(childID));
            
            printf("Parent(%d) send childID: %s\n", getpid(), childID.c_str());

            // close the write descriptor
            close(fd[1]);
        } else {
            // child: reading only, so close the write-descriptor
            close(fd[1]);

            // now read the data (will block until it succeeds)
            read(fd[0], &childID, sizeof(childID));
            printf("Child(%d) received childID: %s\n", getpid(), childID.c_str());

            // close the read-descriptor
            close(fd[0]);
        }
        return 0;
    }



void pipe(){
    
    int n=0;
    int pid;
    pid_t childWait;
    
    printf("Before fork: n=%d\n",n);
    sleep(1);
    
    pid=fork();
    
    //Parent process
    
    if( pid < 0 ) {
       perror( "fork failed" ); // prints string version of errno
    }
    
    if(pid==0){
        n=1;
        printf("\t\t\t\t Child Process: \n");
        printf("\t\t\t\t n=%d, PID=%d\n",n,pid);
        
        while(n<10){
            printf("\t\t\t\t n=%d\n",n);
            n++;
            sleep(1);
            
        }
        printf("\t\t\t\t Child Complete.\n");
        //Parent process
        
    }else{
        printf("\t Parent Process:\n");
        printf("\t n=%d, PID=%d\n",n,pid);
        while(n<=50){
            printf("\t n=%d\n",n);
            n+=10;
            sleep(1);
            
        }
        printf("\t Parent Done:waiting for Child to complete.\n");
        wait(&childWait);
        printf("\t Parent: Child complete.\n");
        printf("\t Parent complete.\n");
        }
    sleep(2);

    
}

int main( int argc, char *argv[] )
{
    //pipe();
    //readPipe();
    readWritePipe(argv);
   exit(0);
}



