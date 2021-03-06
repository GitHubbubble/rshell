#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <cstring>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <iomanip>
#include <ios>
using namespace std;

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"



/*
   * This is a BARE BONES example of how to use opendir/readdir/closedir.  Notice
   * that there is no error checking on these functions.  You MUST add error
   * checking yourself.
 */
void lstester(char a, char l, char R, vector<char*> dirs){
    cout <<"a " <<  (int)a << endl;
    cout <<"l " <<  (int)l << endl;
    cout <<"R " <<  (int)R << endl;

    for (unsigned int i = 0;i <  dirs.size(); i++)
        puts(dirs.at(i));

    cout << endl << endl;
}


void lsrunner(char a, char l, char R, vector<char*> dirs ){

    vector<char*> nextup;

    for (unsigned int i = 0; i < dirs.size(); i++){  //prints out all directories quede

    if (!nextup.empty()){
        cout << "where did he come from??: " << nextup.at(0);
    }
        char *dirName = dirs.at(i) ;
        DIR *dirp;
        if ((dirp = opendir(dirName))== NULL ){
            perror("Open dir");
            exit(1);

        }

        if(R || dirs.size() > 1){
            if (i > 0) cout << endl << endl;
            cout << dirName << ":"<< endl;

        }
        char * mover;
        dirent *direntp;
        while ((direntp = readdir(dirp)))
        {
            if (errno != 0){
                perror("Read dir");
                exit(1);
            }



            if(a || direntp->d_name[0] != '.' ){

                //============================================
                struct stat st;
                char  fileref[1024];

                snprintf(fileref, sizeof(fileref), "%s/%s", dirName, direntp->d_name);


                stat(fileref, &st);

                if(-1 == stat(fileref, &st))
                {
                    perror("stat");
                    exit(1);

                }

                //============================================




                if(R){
                    if (strcmp(direntp -> d_name, ".")&& strcmp(direntp -> d_name, "..")){
                        if(S_ISDIR(st.st_mode))
                        {

                            mover = (char*) malloc (1024);
                            nextup.push_back(strcpy(mover, fileref));

                            //                                   cout << fileref << " or " << direntp->d_name << " is a directory!" << endl;
                        }
                    }
                //is an directory!
                }


                //============================================
                if (!l){

                    if (S_ISDIR(st.st_mode)){
                        printf(ANSI_COLOR_GREEN "%s" ANSI_COLOR_RESET "  ", direntp->d_name);
                    }
                    else if (st.st_mode & S_IXUSR){

                        printf(ANSI_COLOR_BLUE "%s" ANSI_COLOR_RESET "  ", direntp->d_name);
                    }
                    else
                        cout << direntp->d_name << "  " ;  // use stat here to find attributes of file
                }
                else
                {

                    //permissions

                    cout << ((S_ISDIR(st.st_mode)) ? 'd' : '-');
                    cout << (st.st_mode & S_IRUSR ? 'r' : '-');
                    cout << (st.st_mode & S_IWUSR ? 'w' : '-');
                    cout << (st.st_mode & S_IXUSR ? 'x' : '-');
                    cout << (st.st_mode & S_IRGRP ? 'r' : '-');
                    cout << (st.st_mode & S_IWGRP ? 'w' : '-');
                    cout << (st.st_mode & S_IXGRP ? 'x' : '-');
                    cout << (st.st_mode & S_IROTH ? 'r' : '-');
                    cout << (st.st_mode & S_IWOTH ? 'w' : '-');
                    cout << (st.st_mode & S_IXOTH ? 'x' : '-');

                    cout << " ";

                    //files within
                    cout << setw(3);
                    if (!(S_ISDIR(st.st_mode)))cout << "1" << " ";
                    else
                    {
                        cout << st.st_nlink << dec << " ";
                    }
                    //Userid
                    struct passwd *pw;
                    if(!(pw = getpwuid(st.st_uid)))
                        perror("getpuid");


                    cout << pw->pw_name << " ";
                    //group id
                    struct group *gp;
                    if(!(gp = getgrgid(st.st_gid)))
                        perror("getgrgid. ");


                    cout << gp -> gr_name << " ";
                    //size in bytes
                    cout << setw(7);
                    cout << st.st_size << " ";

                    //Month of last access
                    time_t t = st.st_mtime;
                    struct tm lt;
                    if (localtime_r(&t, &lt) == NULL)
                        perror("ctime");

                    string ned;
                    switch( lt.tm_mon + 1){

                        case 1:
                        ned = "Jan";
                        break;

                        case 2:
                        ned = "Feb";
                        break;

                        case 3:
                        ned = "Mar";
                        break;

                        case 4:
                        ned = "Apr";
                        break;

                        case 5:
                        ned = "May";
                        break;

                        case 6:
                        ned = "Jun";
                        break;

                        case 7:
                        ned = "Jul";
                        break;

                        case 8:
                        ned = "Aug";
                        break;

                        case 9:
                        ned = "Sep";
                        break;

                        case 10:
                        ned = "Oct";
                        break;

                        case 11:
                        ned = "Nov";
                        break;

                        case 12:
                        ned = "Dec";
                        break;

                    }
                    cout << ned << " ";

                    //day of last access

                    cout << setw(2);
                    cout << lt.tm_mday << " ";
                    //time of last access
                    if(lt.tm_hour/10 ==0) cout << "0";
                        cout << lt.tm_hour << ":";
                    if(lt.tm_min/10 == 0) cout << "0";
                        cout << lt.tm_min << " ";
                    //
                    // if (S_ISDIR(st.st_mode)) printf("\x1b[34");
                    //   if (direntp->d_name[0] == '.') printf("\x1b[47 ");
                    //   if (S_IXUSR & st.st_mode) printf("\x1b[34");

                    if (S_ISDIR(st.st_mode)){
                        printf(ANSI_COLOR_GREEN "%s" ANSI_COLOR_RESET "  ", direntp->d_name);
                    }
                    else if (st.st_mode & S_IXUSR){

                        printf(ANSI_COLOR_BLUE "%s" ANSI_COLOR_RESET "  ", direntp->d_name);
                    }
                    else
                        cout << direntp->d_name << "  " ;

                    //  printf("\x1b[0m");
                    cout << endl;
                    // use stat here to find attributes of file

                }

            //============================================
            }

        }

        std::cout << endl;

        if (closedir(dirp) == -1){
            perror("Close dir");
        }

        if (R&&!nextup.empty()){
            cout << endl << endl;
            lsrunner(a, l, R, nextup);

            for (unsigned int og; og < nextup.size(); og++){
                free( nextup.at(og));
            }

            nextup.clear();
        }
        else{
          /*  for (unsigned int og; og < nextup.size(); og++){
                free( nextup.at(og));
            }*/
        }
    }
    return;
}

int main(int argc, char *argv[]){
    char fa = 0;
    char fl= 0;
    char fR = 0;

    vector< char* > dirt;

    for(unsigned int i = 1; i < (unsigned int)argc; i++){

        if(argv[i][0] == '-'){
            int j = 1;

            while(argv[i][j] != '\0'){
                if (argv[i][j] == 'a')
                    fa = 1;
                else if (argv[i][j] == 'l')
                    fl = 1;
                else if (argv[i][j] == 'R')
                    fR = 1;
                else{
                    cerr << "ls: \"" <<(unsigned char)argv[i][j] << "\" is not a recognized flag.\n";
                    exit(1);
                }
                j++;
            }
        }
        else{
        dirt.push_back(argv[i]);

        }
    }

    if(dirt.empty())
    dirt.push_back((char*)".");

    //    lstester(fa, fl, fR, dirt);
    lsrunner(fa, fl, fR, dirt);


}
