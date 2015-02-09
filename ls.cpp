#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <cstdlib>

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

}

void lsrunner(char a, char l, char R, vector<char*> dirs ){
    char *dirName = nam ;
    DIR *dirp;
    if ((dirp = opendir(dirName))== NULL ){
        perror("Open dir");
        exit(1);

    }

    dirent *direntp;
    while ((direntp = readdir(dirp)))

        cout << direntp->d_name << "  " ;  // use stat here to find attributes of file
    closedir(dirp);

    cout << endl;
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



}
