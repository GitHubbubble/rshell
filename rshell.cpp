#include <iostream>
#include <string>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstring>
#include <cstdlib>


int fcall(char* argv[]){
    if (strlen(argv[0]) == 0){

        return -1;
    }
    if (!strcmp(argv[0], "exit")){

        return 1;
    }

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

int main(){

    while(1){
        std::string chunky;
        std::getline(std::cin, chunky);

        char *cstr = new char [chunky.length() + 1];
        strcpy(cstr, chunky.c_str());

        char * cstr2;

        cstr2 = strtok(cstr, "#");


        char*  pch;
        char* argv[1024];
        argv[0] = (char*)"";

        pch = strtok(cstr2, " ");

        for( int p = 0; pch != NULL; p++){
            argv[p] = pch;
            pch = strtok(NULL, " ");
        }

        if (fcall(argv) > 0){
            delete[] cstr;
            goto skippy;
        }
    }
    skippy:
    std::cout << "Ar revoir!\n";
    return 0;
}
