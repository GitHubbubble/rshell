#include <iostream>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstring>
#include <cstdlib>
int main(){



   char* argv[3];
   argv[0] = "ls";

   argv[1] =  "-t";
   argv[2] =  "-l";


  int pid = fork();
    if(pid == -1)//fork’s return value for an error is -1
    {
       //perror("There was an error with fork(). ");
       perror("fork"); //although you certainly can use the above, it is good
                       //practice not to write more information than necessary
       exit(1);//there was an error with fork so exit the program and go back and fix it
    }
    else if(pid == 0)//when pid is 0 you are in the child process
    {

       if (0 < execvp(argv[0], argv))
           perror("execvp");

       exit(1);  //when the child process finishes doing what we want it to, cout,
                 //we want to kill the child process so it doesn’t go on in the program so we exit
    }
    else if(pid > 0){//if pid is not 0 then we’re in the parent
        if (-1 == wait(0))
            perror("wait");

    }
    return 0;
}
