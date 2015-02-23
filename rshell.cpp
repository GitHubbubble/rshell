#include <iostream>
#include <string>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <utility>
#include <sstream>
#include <fcntl.h>
#include <stdlib.h>

void vectortest(std::vector < std::pair<char**, int*> > wow1)
{
    for (unsigned int gg = 0; gg < wow1.size(); gg++)
    {
        int m = 0;
        while (wow1.at(gg).first[m] != NULL)
        {
            std::cout << gg << "," << m << ": " << wow1.at(gg).second[1];
            puts(wow1.at(gg).first[m]);
            m++;
        }
    }
}

int fcall(char** argv){

    const int pipew = 2;
    const int piper = 1;
    //gotta say, fully understanding pipe I really appriciate how much sense this saves me.

    if (strlen(argv[0]) == 0){

        return -1;
    }
    if (!strcmp(argv[0], "exit")){

        return 1;
    }

    int n = 0;
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

       if (0 < execvp(argv[0], argv)){
           n = -1;
           perror("execvp");
       }
       exit(1);  //when the child process finishes doing what we want it to, cout,
                 //we want to kill the child process so it doesn’t go on in the program so we exit
    }
    else if(pid > 0){//if pid is not 0 then we’re in the parent
        if (-1 == wait(0))
            perror("wait");
    }
    pid = pipew + piper;
   // delete [] argv;

    return n;
}


int  breakitup (std::string hamma){

    std::vector<std::string> bargv;
    std::istringstream strm(hamma);
    std::string s;

    while (strm >> s)
    {
        bargv.push_back(s);
    }
    if (bargv.empty())
        bargv.push_back("");

    int dd = 0;
    std::vector<std::pair<char**, int*> > gammy;

    char** argv;
    int * op;

    for(unsigned int bb = 0; bb < bargv.size(); bb++){

        argv = (char **) malloc (1024);
        while(bb < bargv.size() && bargv.at(bb).compare(">") && bargv.at(bb).compare("<")&& bargv.at(bb).compare(">>")&& bargv.at(bb).compare("|") )
        {    //if strcat((char*)bargv.at(bb).c_str(), "\0") == <
            argv[dd] = strcat((char*)bargv.at(bb).c_str(), "\0");
            bb++;
            dd++;
        }
        argv[dd] =NULL;

        op = (int*) malloc(3);
        bool caset = 1;
        if (bb >= bargv.size())
        {
            goto guddy;
        }
        else if (bb +1 >= bargv.size())
        {
            goto buddy;
        }

        int fd;



        if (bargv.at(bb).compare("<")){
            if (-1 == (fd = open(argv[dd + 1], O_RDONLY))){
                perror("open");
            }
            op[0] = 1;
            op[1] = fd;
            gammy.push_back(std::make_pair(argv, op ));
        }
        else if (bargv.at(bb).compare(">")){
            if (-1 == (fd = open(argv[dd + 1], (O_RDWR) | O_CREAT, S_IRWXU))){
                perror("open");
            }
            op[0] = 2;
            op[1] = fd;
            gammy.push_back(std::make_pair(argv, op));
        }
        else if (bargv.at(bb).compare(">>")){
            if (-1 == (fd = open(argv[dd + 1], (O_RDWR | O_APPEND) | O_CREAT, S_IRWXU))){
                perror("open");
            }
            op[0] = 3;
            op[1] = fd;

            gammy.push_back(std::make_pair(argv, op));
        }
        else if (bargv.at(bb).compare("|")){
            int fds[2];

            if(pipe(fds) == -1){
                perror("pipe");
            }
            op[0] = 4;
            op[1] = fds[0];
            op[2] = fds[1];

            gammy.push_back(std::make_pair(argv, op));
        }
        else{
            guddy:
            op[0] = 0;
            gammy.push_back(std::make_pair(argv, op));
            caset = 0;
        }

        dd =0;
        if (caset){
            if((bb + 1) >= bargv.size()){
                buddy:
                std::cerr << "Miss-matched i/o dierection!\n";
                return -1;
            }
        }
        bb++;

        if (bb < bargv.size() && bargv.at(bb).compare("|")){

            op = (int*) malloc(3);
           int fds[2];

            if(pipe(fds) == -1){
                perror("pipe");
            }
            op[0] = 4;
            op[1] = fds[0];
            op[2] = fds[1];

            gammy.push_back(std::make_pair(argv, op));
            bb++;
        }

        if (caset){
            if((bb + 1) >= bargv.size()){
                std::cerr << "Miss-matched i/o dierection!\n";
                return -1;
            }
        }
    }

    vectortest(gammy);
   // int holla = fcall(argv);

   // return holla;
   free (argv);

   return 1;
}

int findclosest(std::string bobo ){

    bool pcha = ( bobo.find(";")!= std::string::npos);
    bool pchb = ( bobo.find("&&")!= std::string::npos);
    bool pchc = ( bobo.find("||")!= std::string::npos);

    unsigned int cha = bobo.find(";");
    unsigned int chb = bobo.find("&&");
    unsigned int chc = bobo.find("||");

      if (!pcha && !pchb && !pchc){
        return 0;
    }
    else if (!pchb && !pchc){
        return 1;
    }
    else if (!pcha && !pchc){
        return 2;
    }
    else if (!pcha && !pchb){
        return 3;
    }
    else if (!pchc){
        if (cha < chb)
            return 1;
        else
            return 2;
    }
    else if (!pchb){
        if(cha < chc)
            return 1;
        else{
            return 3;
        }
    }
    else if (!pcha){
        if (chb < chc)
            return 2;
        else {
            return 3;
        }
    }
    else
    {
        if (cha < chb && cha < chc)
            return 1;
        else if (chb < cha && chb < chc)
            return 2;
        else {
            return 3;
        }
    }


}
int main(){
//welcome to the really awesome shell!


    while(1){
        std::cout << "rash$ ";
        std::string chunky;
        std::getline(std::cin, chunky);

        char *cstr = new char [chunky.length() + 1];
        strcpy(cstr, chunky.c_str());
        char * cstr2;
        cstr2 = strtok(cstr, "#");
        std::string smoothly(cstr2);

        char mustpass = 0;
        char didpass = 0;

        std::vector<std::pair<char, std::string> > conn;

        int temp = 0;
        int fc = 0;

        while (smoothly.size()!= 0){

            switch (fc){
                    case 0:
                //    std::cout << "that's it";
                        conn.push_back(std::make_pair(0,smoothly));
                        smoothly.clear();
                    break;

                    case 1:
              //      std::cout << ";";
                      temp = smoothly.find(";");
           // std::cerr << "&" << smoothly.substr(0, temp) << "\n";
                      conn.push_back(std::make_pair(0,smoothly.substr(0, temp)));
                      smoothly = smoothly.substr(temp+1);
                    break;

                    case 2:
            //        std::cout << "&&";
                      temp = smoothly.find("&&");
          //  std::cerr << "&" << smoothly.substr(0, temp) << "\n";
                      conn.push_back(std::make_pair(2,smoothly.substr(0, temp)));
                      smoothly = smoothly.substr(temp+2 );
                    break;

                    case 3:
                  //  std::cout << "||";
                      temp = smoothly.find("||");
          //  std::cerr << "&" << smoothly.substr(0, temp) << "\n";
                      conn.push_back(std::make_pair(1,smoothly.substr(0, temp)));
                      smoothly = smoothly.substr(temp+2 );
                    break;

                    default:
                    std::cout << "UH OH!";
            }
        }

       for(unsigned int i = 0; i < conn.size(); i++){

               int a = -1;
               char cancheck = 0;
            if (mustpass == 2 && didpass == 1){
                cancheck = 1;
            }
            else if (mustpass == 1 && didpass == 0){
                cancheck = 1;
            }
            else if (mustpass == 0){
                cancheck =1;
            }
            else
                didpass = 0;

            if (cancheck){
                a = breakitup(conn.at(i).second);

                //a = fcall(breakitup(conn.at(i).second));
                if (a < 0)
                   didpass = 0;
                else if (a == 0)
                   didpass = 1;
               else if (a > 0){
                   delete[] cstr;
                   goto skippy;
               }
            }

            mustpass = conn.at(i).first;
        }
     delete [] cstr;
    }
    skippy:
    std::cout << "Ar revoir!\n";
    return 0;
}
