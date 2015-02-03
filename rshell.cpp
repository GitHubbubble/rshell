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

int fcall(char* argv[]){
    if (strlen(argv[0]) == 0){

        return -1;
    }
    if (!strcmp(argv[0], "exit")){

        return 1;
    }
    in n = 0;
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
    return n;
}

char**  breakitup (char * cstr2){
        char* sp2;
        char*  pch;
        static char* argv[1024];
        argv[0] = (char*)"";

        pch = strtok_r(cstr2, " ", &sp2);

        for( int p = 0; pch != NULL; p++){
            argv[p] = pch;
            pch = strtok_r(NULL, " ", &sp2);
        }

        return  argv;
}

int findclosest(char * sift){
    char* pcha = strchr(sift, ';');
    char* pchb = strstr(sift, "&&");
    char* pchc = strstr(sift, "||");

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
        if (pcha < pchb)
            return 1;
        else
            return 2;
    }
    else if (!pchb){
        if(pcha < pchc)
            return 1;
        else
            return 3;
    }
    else if (!pcha){
        if (pchb < pchc)
            return 2;
        else
            return 3;
    }
    else
    {
        if (pcha < pchb && pcha < pchc)
            return 1;
        else if (pchb < pcha && pchb < pchc)
            return 2;
        else
            return 3;
    }


}
int main(){

    while(1){
        std::string chunky;
        std::getline(std::cin, chunky);

        char *cstr = new char [chunky.length() + 1];
        strcpy(cstr, chunky.c_str());

        char * cstr2;

        cstr2 = strtok(cstr, "#");

        char *cstr3;
        char* sp;
        char mustpass =0; //2 must pass; 1 must fail; 0 doesn't care
        char didpass = 0;

        std::vector<std::pair <char, char *> > conn;

        int fc = findclosest(cstr2);
        switch (fc){
                case 0:
                std::cout << "that's it";
                cstr3 = strtok_r(cstr2, ";", &sp);
                conn.push_back(std::make_pair(0, cstr3));
                break;

                case 1:
                std::cout << ";";
                cstr3 = strtok_r(cstr2, ";", &sp);
                conn.push_back(std::make_pair(0, cstr3));
                break;

                case 2:
                std::cout << "&&";
                cstr3 = strtok_r(cstr2, "&", &sp);
                conn.push_back(std::make_pair(2, cstr3));
                break;

                case 3:
                std::cout << "||";
                cstr3 = strtok_r(cstr2, "|", &sp);
                conn.push_back(std::make_pair(1, cstr3));
                break;

                default:
                std::cout << "UH OH!";
        }

        while (cstr3 != NULL){
            switch (fc){
                    case 0:
                    std::cout << "that's it";
                    cstr3 = strtok_r(NULL, ";", &sp);
                    if (cstr3!= NULL)conn.push_back(std::make_pair(0, cstr3));
                    break;

                    case 1:
                    std::cout << ";";
                    cstr3 = strtok_r(NULL, ";", &sp);
                     if (cstr3!= NULL)conn.push_back(std::make_pair(0, cstr3));
                    break;

                    case 2:
                    std::cout << "&&";
                    cstr3 = strtok_r(NULL, "&", &sp);
                     if (cstr3!= NULL)conn.push_back(std::make_pair(2, cstr3));
                    break;

                    case 3:
                    std::cout << "||";
                    cstr3 = strtok_r(NULL, "|", &sp);
                     if (cstr3!= NULL)conn.push_back(std::make_pair(1, cstr3));
                    break;

                    default:
                    std::cout << "UH OH!";
            }
        }

            //puts(cstr3);
           // fc = findclosest(cstr3);
           // std::cerr << fc;
       // }
      // puts(cstr3);
             // puts(buf);
       for(int i = 0; i < conn.size(); i++)
       {

       /*     char mustfail =0;
            char mustpass =0;
            char leftoverand = 0;
            char leftoveror = 0;

            int a = fcall(breakitup(cstr3));
        */

            if (mustpass == 2 && didpass = 1){
                int a = fcall(breakitup(conn.at(i).second));
            }
            if (a > 0){
                delete[] cstr;
                goto skippy;
            }


            mustpass = conn.at(i).first;
        }
        /*
            fc = findclosest(cstr3);
            std::cout << fc;
            switch (fc){
                case 0:
                cstr3 = strtok_r(NULL, ";", &sp);
                break;

                case 1:
                std::cout << ";";
                cstr3 = strtok_r(NULL, ";", &sp);
                break;

                case 2:
                std::cout << "&&";
                cstr3 = strtok_r(NULL, "&", &sp );
                break;

                case 3:
                std::cout << "||";
                cstr3 = strtok_r(NULL, "|", &sp);
                break;

                default:
                std::cout << "e! impossible outcome!";
           }

          if (cstr3 != NULL)
              puts(cstr3);*/
       //}
    }
    skippy:
    std::cout << "Ar revoir!\n";
    return 0;
}
