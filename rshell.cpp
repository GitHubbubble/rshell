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

void vectortest(std::vector < std::pair<char**, std:: vector<std::string> > > wow1)
{
    for (unsigned int gg = 0; gg < wow1.size(); gg++)
    {
        int m = 0;
        while (wow1.at(gg).first[m] != NULL)
        {
            std::cout << gg << "," << m << ": " << wow1.at(gg).second[0];
            puts(wow1.at(gg).first[m]);
            m++;
        }
    }
}

int fcall(std::vector < std::pair<char**, std::vector <std::string> > > argvv ){

    const int pipew = 1;
    const int piper = 0;
    //gotta say, fully understanding pipe I really appriciate how much sense this saves me.


    int status;
    if (strlen(argvv.at(0).first[0]) == 0){

        return -1;
    }
    if (!strcmp(argvv.at(0).first[0], "exit")){

        return 1;
    }

    //counter of weights


    unsigned int waitcount = 0;
    std::vector<int> pipecount;

    int pdf[1024];
    int n = 0;

    for (unsigned int k = 0; k < argvv.size(); k++){
        if (!argvv.at(k).second.at(0).compare("4") ){ //figures out how many pipes we'll need
            if(pipe(pdf+(2*k)) == -1)
                perror("pipe");
          /*  if (-1 == close(pdf[((2*k)+0)]))
                perror("close");
            if (-1 == close (pdf[((2*k) +1)]))
                perror("close");*/
            pipecount.push_back(2*k);

        }
            waitcount++;

    }


    /* PATH FINDER - Locate paths and put them in the vector
     */
     std::vector<char*> path;

    /* getenv()
     */

     /* parse using ":"
     */

     /* place into vector
     *
     */




    int stdins;
    int stdouts;

    if (-1 == (stdins = dup(0)))
        perror("dup");
    if (-1 == (stdouts = dup(1)))
        perror("dup");

    for (unsigned int i = 0; i < argvv.size(); i++ ){

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
            int fdx;
            int fdy;

            //(I) ==============
            int y = ((int)argvv.at(i).second.at(0).at(0)-48);

            switch (y){
                case 0:
                break;

                case 1:
                    if (-1 == (fdy = open(argvv.at(i).second.at(1).c_str(), O_RDONLY))){
                        perror("open");
                    }
                    if (-1 == dup2(fdy, 0)){
                        perror("dup");
                    }
                break;

                case 2:
                break;

                case 3:
                break;

                case 4:
                if(-1 == dup2(pdf[((2*i)+piper)],0 ))
                    perror("dup");
                break;

                }

            //(I +1) ==============
            if (i+1 < argvv.size()){
               int z = ((int)argvv.at(i+1).second.at(0).at(0)-48);
                switch (z){
                    case 0:
                    break;

                    case 1:
                    break;

                    case 2:
                    if (-1 == (fdx = open(argvv.at(i+1).second.at(1).c_str(), O_RDWR | O_CREAT,S_IRWXU ))){
                        perror("open");
                    }
                    if (-1 ==  dup2(fdx,1 ))
                        perror("dup");
                    break;

                    case 3:
                    if (-1 == (fdx = open(argvv.at(i+1).second.at(1).c_str(), (O_RDWR | O_APPEND) | O_CREAT,S_IRWXU ))){
                        perror("open");
                    }
                    if (-1 ==  dup2(fdx,1 ))
                        perror("dup");
                    break;

                    case 4:
                        if(-1 == dup2(pdf[(((i+1)*2) + pipew)],1 ))
                            perror("dup");
                    break;
                 }
            }



            for(unsigned int kg = 0; kg < pipecount.size(); kg++){
                if (-1 == close(pdf[pipecount.at(kg)]))
                    perror("close");
                if (-1 == close(pdf[pipecount.at(kg) +1]))
                    perror("close");
            }

            if (y != 2 && y!= 3){

                /* look through all paths */
                for (]unsigned int pp  = 0; pp < path
                /*catenate current path with call examined*/


                if (0 < execvp(,argvv.at(i).first )){
                    perror("execvp");
                    n = -1;
                }
            }

            exit(1);  //when the child process finishes doing what we want it to, cout,
            //we want to kill the child process so it doesn’t go on in the program so we exit

        }

    }

    for(unsigned int kg = 0; kg < pipecount.size(); kg++){
        if (-1 == close(pdf[pipecount.at(kg)]))
            perror("close");
        if (-1 == close(pdf[pipecount.at(kg) +1]))
            perror("close");


    }

    for (unsigned int f = 0; f < waitcount; f++){
        if (-1 == wait(&status))
            perror("wait");
    }

    if (-1 == dup2(stdins, 0))
        perror("dup");
    if (-1 == dup2(stdouts, 1))
        perror("dup");


    if (-1 == close(stdins))
        perror("close");
    if (-1 == close(stdouts))
        perror("close");

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

    int dd = 0; //not one of my better names
    std::vector<std::pair<char**, std::vector<std::string> > > gammy;
    char** argv;

    for(unsigned int bb = 0; bb < bargv.size(); bb++){
        std::vector<std::string > op;
        if (!bargv.at(bb).compare(">")){
            op.push_back ( "2");
            op.push_back(bargv.at(bb +1));
            gammy.push_back(std::make_pair(argv, op));
            bb += 2;
        }
        else if (!bargv.at(bb).compare(">>")){
            op.push_back ( "3");
            op.push_back(bargv.at(bb +1));
            gammy.push_back(std::make_pair(argv, op));
            bb += 2;
        }
        else if (!bargv.at(bb).compare("|")){
            op.push_back ( "4");
            bb++;
        }
        else{
            op.push_back("0");
        }
        argv = (char **) malloc (1024);
        while(bb < bargv.size() && bargv.at(bb).compare(">") && bargv.at(bb).compare("<")&& bargv.at(bb).compare(">>")&& bargv.at(bb).compare("|") )
        {    //if strcat((char*)bargv.at(bb).c_str(), "\0") == <
            argv[dd] = strcat((char*)bargv.at(bb).c_str(), "\0");
            bb++;
            dd++;
        }
        argv[dd] =NULL;

        if (bb < bargv.size() &&  !bargv.at(bb).compare("<")){
            op.pop_back();
            op.push_back ( "1");
            op.push_back(bargv.at(bb +1));
            gammy.push_back(std::make_pair(argv, op ));
            bb++;
        }
        else{
            if (bb < bargv.size() && !op.back().compare("4")){
                if (dd == 0){
                    std::cerr << "Miss-matched i/o dierection!\n";
                    return -1;
                }
                else{
                    gammy.push_back(std::make_pair(argv,op));
                    if (bb == 0){
                        std::cerr << "Miss-matched i/o dierection!\n";
                        return -1;
                    }
                    bb--;
                }
            }
            else if (bb >= bargv.size()){
                gammy.push_back(std::make_pair(argv, op));
            }
            else{
                gammy.push_back(std::make_pair(argv, op));
                bb--;
            }
        }
        dd =0;

    }
    vectortest(gammy);
    int holla = fcall(gammy);
   // int holla = 1;
    free (argv);
    return holla;

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
