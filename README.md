README


rshell
OVERVIEW

really awesome shell (rash) is a shell that can

execute commands (limited to what commands are available)
parse commands using ";" , "&&" , "||"
interpret input and output redirection
change current directory


==============
|            |
| HOW TO USE |
|            |
==============


===============EXECUTE COMMANDS=======================



When rash opens up properly it will ask for a command, displaying the following prompt:

rash-<loginname>$

After this, you can enter in any (AVAILABLE) command. Currently, rash looks at $PATH variable to determine if a command is available. If a command cannot execute, check to see if the command exists within $PATH.

For example:
rash-<loginname>$ echo hello!
hello!

Once the command has executed, rash will ask for another command.



===========PARSE COMMANDS USING ";" , "&&", "||"==========================



Multiple commands can be called on the same line, separated by ";".

For example:
rash-<loginname>$ echo hello! ; echo goodbye!
hello!
goodbye!

If commands are separated by "&&", the second command will only execute if the previous command worked.

For example:
rash-<loginname>$ true && echo hello!
hello!
rash-<loginname>$ false && echo hello!

If commands are spereated by "||", the second command will only execute if the previous command failed.

For example:
rash-<loginname>$ true || echo hello!
rash-<loginname>$ false || echo hello!
hello!


=================INTERPRET INPUT AND OUTPUT REDIRECTION=======================




command and parameter separated by "<" will link standard in from the first command to standard out from the second parameter

For example:
rash-<loginname>$ cat <  input.txt
this is a great file!
see ya later!

command and parameter separated by ">" will redirect standard out from the first command, and instead output to a file. If the file does not exist, it creates one. Otherwise,the old file is overwritten.

For example:
rash-<loginname>$ echo hello! > input.txt

The contents of "input.txt" are now :
hello!

command and parameter separated by ">>" will redirect standard out from the first command, and instead output to a file. If the file does not exist, it creates one. Otherwise, the output will be appended at the end of the file.

For example:
input.txt contains:
hello!

rash-<loginname>$ echo goodbye! > input.txt

The contents of "input.txt" are now :
hello!
goodbye!

Commands separated by "|" will redirect standard out from the first command into standard in of the second.

For example:
rash-<loginname>$ echo hello! | tr a-z A-Z
HELLO!


===================CHANGE DIRECTORIES=============================================================

by using "cd", you can choose what directory you want to be the working directory.

For example:
rash-<loginname>$ cd happyfile
/home/computa/src/happyfile

=====================================================================================
|                                                                                   |
|                              Known Bugs!                                          |
|                                                                                   |
=====================================================================================

===PARSE COMMANDS===

There is no current way to determine if a command failed or passed. This means that the command "&&" always passes and "||" always fails.

===REDIRECTION===

">" does not overwrite the file it reads to. Rather, it writes to the front of the file.




===========================================
===========================================
===========================================
===========================================
===========================================
===========================================
===========================================
===========================================







ls
OVERVIEW

lists files depending on flags and optional target file


$./ls .
> README main.cpp out


./ls -[FLAG] [file]

INSTILLATION

make ls

KNOWN BUGS

currently not sorted.
