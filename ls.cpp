#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

#include <iostream>

using namespace std;

/*
   * This is a BARE BONES example of how to use opendir/readdir/closedir.  Notice
   * that there is no error checking on these functions.  You MUST add error
   * checking yourself.
 */
void lstester(char a, char l, char R){
    cout << (int)a << endl;
    cout << (int)l << endl;
    cout << (int)R << endl
}

void lsrunner(char a, char l, char R, char* nam){
    char *dirName = nam ;
    DIR *dirp
    if ((dirp = opendir(dirNamei))== NULL ){
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
    char fa;
    char fl;
    char fR;


    for(int i = 0; int i < (int)argc; i++){

        char str[] =argv[i] ;
        char * pch;
        printf ("Splitting string \"%s\" into tokens:\n",str);
        pch = strtok (str," ,.-");
        while (pch != NULL){
         printf ("%s\n",pch);
        pch = strtok (NULL, " ,.-");
          }
    }

}
