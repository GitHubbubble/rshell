#include "Timer.h"
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <cstring>
void thestream(char* inf, char* outf){


    strcat(outf, "3");

   std::ifstream is(inf);
   std::ofstream os(outf);
   char c;
   if (is.is_open())
   {

        while(is.get(c))
        {
            os.put(c);
        }
    }
}

void thechar(char* inf,char * outf){

    strcat(outf, "2");
    int fd1;
    if (-1 == (fd1 = open(inf,O_RDONLY))){
        perror("open");
    }

    int fd2;

    if (-1 == (fd2 = open(outf,(O_RDWR |O_APPEND)|O_CREAT,S_IRWXU))){
        perror("open");
    }

    char buf[1];
    int size;

    while((size=read(fd1,buf,sizeof(buf))) > 0)
    {
        write(fd2, buf, size);
    }
    close (fd1);
    close (fd2);
}

void thebuf(char* inf,char * outf){

    strcat(outf, "1");

    int fd1;
    if (-1 == (fd1 = open(inf,O_RDONLY))){
        perror("open");
    }

    int fd2;

    if (-1 == (fd2 = open(outf,(O_RDWR| O_APPEND) | O_CREAT,S_IRWXU))){
        perror("open");
    }

    char buf[BUFSIZ];
    int size;

    while((size=read(fd1,buf,BUFSIZ)) > 0)
    {
        write(fd2, buf, size);
    }
    close (fd1);
    close (fd2);

}

int main(int argc, char* argv[]){

    if (argc == 4){

    Timer t;
    double eTime;
    double gTime;
    double pTime;
    t.start();
        thebuf(argv[1], argv[2]);
    t.elapsedUserTime(eTime);
    t.elapsedSystemTime(gTime);
    t.elapsedWallclockTime(pTime);
    std::cout << "\n=Buf=\n" << std::endl;
    std::cout <<"User: " << eTime << std::endl;
    std::cout <<"System: " <<  gTime << std::endl;
    std::cout <<"Wallclock: " << pTime << std::endl;

    Timer t1;
    double eTime1;
    double gTime1;
    double pTime1;
    t1.start();
        thechar(argv[1], argv[2]);
    t1.elapsedUserTime(eTime1);
    t1.elapsedSystemTime(gTime1);
    t1.elapsedWallclockTime(pTime1);
    std::cout << "\n=char=\n" << std::endl;
    std::cout <<"User: " << eTime1 << std::endl;
    std::cout <<"System: " <<  gTime1 << std::endl;
    std::cout <<"Wallclock: " << pTime1 << std::endl;

    Timer t2;
    double eTime2;
    double gTime2;
    double pTime2;
    t2.start();
        thebuf(argv[1], argv[2]);
    t2.elapsedUserTime(eTime2);
    t2.elapsedSystemTime(gTime2);
    t2.elapsedWallclockTime(pTime2);
    std::cout << "\n=Stream=\n" << std::endl;
    std::cout <<"User: " << eTime2 << std::endl;
    std::cout <<"System: " <<  gTime2 << std::endl;
    std::cout <<"Wallclock: " << pTime2 << std::endl;
    }
    else
        thebuf(argv[1], argv[2]);
    return 0;
}
