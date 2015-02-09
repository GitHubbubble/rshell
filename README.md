
=====================================================================================
ls
OVERVIEW

lists files depending on flags and optional target file


$./ls .
> README main.cpp out


./ls -[FLAG] [file]

INSTILLATION

make ls

KNOWN BUGS

Has known to encounter ** glibc detected *** ./ls: double free or corruption upon using ".." as a target file.

currently not sorted.

-R may result in an attempt to read a non-existent file.







I'm sorry to put something so informal in here, by the makefile doesn't work. It doesn't make the directories in the bin. I've been up all night trying to figure out how to do it, but I'm exausted.
