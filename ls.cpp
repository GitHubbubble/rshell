#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <cstring>

using namespace std;

/*
   * This is a BARE BONES example of how to use opendir/readdir/closedir.  Notice
   * that there is no error checking on these functions.  You MUST add error
   * checking yourself.
 */
void lstester(char a, char l, char R, vector<char*> dirs){
    cout <<"a " <<  (int)a << endl;
    cout <<"l " <<  (int)l << endl;
    cout <<"R " <<  (int)R << endl;

    for (int i = 0;i <  dirs.size(); i++)
        puts(dirs.at(i));

    cout << endl << endl;
}

void lprint(dirent * goods){

}

void lsrunner(char a, char l, char R, vector<char*> dirs ){

    vector<char*> nextup;

    for (int i = 0; i < dirs.size(); i++){  //prints out all directories qued

        char *dirName = dirs.at(0) ;
        DIR *dirp;
        if ((dirp = opendir(dirName))== NULL ){
            perror("Open dir");
            exit(1);

        }

        if(R)
            cout << dirName << ":" << endl;

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

                lstat(fileref, &st);

                //============================================
                if(S_ISDIR(st.st_mode))
                {

                    nextup.push_back(fileref);
                    //is an directory!
                }


                //============================================
                    if (!l)
                        cout << direntp->d_name << "  " ;  // use stat here to find attributes of file
                    else
                        lprint(direntp);


                //============================================
//                delete [] fileref;
            }

        }

        if (closedir(dirp) == -1){
            perror("Close dir");
        }

        cout << endl;

        if (R&&!nextup.empty())
            cout << endl;
            lsrunner(a, l, R, nextup);

    }
}

int main(int argc, char *argv[])
{
    char fa = 0;
    char fl= 0;
    char fR = 0;

    vector< char* > dirt;

    for(int i = 1; i < (int)argc; i++){

        if(argv[i][0] == '-'){
            char j = 1;

            while(argv[i][j] != '\0'){
                if (argv[i][j] == 'a')
                    fa = 1;
                else if (argv[i][j] == 'l')
                    fl = 1;
                else if (argv[i][j] == 'R')
                    fR = 1;
                else{
                    cerr << "ls: \"" << argv[i][j] << "\" is not a recognized flag.\n";
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

    lstester(fa, fl, fR, dirt);
    lsrunner(fa, fl, fR, dirt);


}
