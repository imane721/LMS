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
////////////////////////////////////////////////////////////////
void pipe_example()
{
   int fds[2];
   int rc = pipe( fds );
    
   if( rc == -1 ) {
      perror( "creating the pipe failed" );
      exit( 1 );
   }
    
   printf("PARENT: fds: %d, %d\n", fds[0], fds[1] ); // read from 0, write from 1
   int readFd  = fds[ 0 ];
   int writeFd = fds[ 1 ];
   int pid = fork();
   if( pid < 0 ) {
      perror( "fork failed" ); // prints string version of errno
   }
   else if( pid == 0 ) {
      // CHILD
      sleep( 1 );
      const int size = 1024;
      int buffer[ size ];
      while( true ) {
         read( readFd, buffer, 1*sizeof(int) );
         printf( "CHILD: got #s: %d\n", buffer[0] );
      }
   }
   else {
      // PARENT
      int data[2];
      data[0] = 99;
      data[1] = -77;
      while( true ) {
         cout << "Enter a number: ";
         cin >> data[0];
         write( writeFd, data, 1*sizeof(int) );
      }
      printf("PARENT - begin wait\n");
      wait( NULL );
      printf("PARENT - done wait\n");
   }
}
////////////////////////////////////////////////////////////////
//
/*
int main( int argc, char *argv[] )
{
   pipe_example();
   return 0;
}
*/
