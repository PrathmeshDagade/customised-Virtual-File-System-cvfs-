FILE NAME :- 

cvfs.c



TECHNOLOGY USED :- 

c programming language 



USER INTERFACE USED :-

command line interface (CLI)



PLATFORM REQUIRED :- 

windows , macos , linux like os 



OVERVIEW :- 

This project implements a Command Line Virtual File System (CVFS) in C language.
It simulates the behavior of a simple operating system’s file management system using data structures like inodes, superblocks, and file tables.

The system allows users to create, read, write, and delete (unlink) virtual files within the terminal environment — without interacting with the actual OS file system.



FEATURES :-

Create a new virtual file with custom permissions

Write data to a virtual file

Read data from a virtual file

Delete (unlink) a file

Display a help menu with all supported commands

Simulates a real file system structure (boot block, superblock, inode list, file tables)



CORE CONCEPTS :-

Component	Description

struct boot	Simulates the OS booting message.
struct superblock	Holds overall file system information (total/used/free inodes & blocks).
struct inode	Represents metadata for each file (file name, size, permissions, etc.).
struct filetable	Maintains read/write offsets and file access modes.
struct UAREA	Represents the user area, which stores pointers to open file tables.



IMPORTANT FUNCTIONS :-

Function	Description

structuresinitilizer()	Initializes all system structures with default values.
DILB()	Creates a linked list of inodes (Disk Inode List Block).
isFileExist()	Checks whether a file exists in the virtual system.
CreatFile()	Creates a virtual file and allocates an inode and file table.
UnlinkFile()	Deletes a file and frees its resources.
WriteFile()	Writes user input into the file’s buffer.
ReadFile()	Reads and displays data from a file.
Help()	Displays supported CVFS commands and their purpose.




HOW IT WORKS (EXECUTION FLOW)

1. Boot & Initialization:
When the program starts, it runs DILB() and structuresinitilizer() to set up all inodes and tables.


2. Command Interface:
A terminal prompt prathmeshs' CVFS $ accepts commands from the user.


3. Command Processing:

creat filename permission → Create a file

write filename size → Write data to file

read filename size → Read data

unlink filename → Delete a file

help → Display available commands

clear → Clear terminal screen

exit → Exit CVFS




EXAMPLE USAGE :-

$ gcc cvfs.c -o cvfs
$ ./cvfs
prathmeshs' CVFS $ help
prathmeshs' CVFS $ creat demo.txt 2
prathmeshs' CVFS $ write demo.txt 20
prathmeshs' CVFS $ read demo.txt 20
prathmeshs' CVFS $ unlink demo.txt
prathmeshs' CVFS $ exit




ERROR CODES :-

ERR_FILE_ALREADY_EXISTS (-1)	File with the same name already exists.
ERR_THERE_IS_NO_FREEINODE (-2)	No free inodes available to create new files.
ERR_THEREIS_NO_SIMIILARFILE (-3)	File not found in virtual system.




CONCEPTS COVERD :-

File System Design

Linked Lists and Dynamic Memory

Structures and Pointers

File Metadata Simulation

Command-Line Parsing


AUTHOR :-

Prathmesh Bhanudas Dagade


FUTURE ENHANCMENT :-

Add file opening and closing mechanism

Add file seek and truncate functionality

Save file system state to disk using serialization

Introduce user-level permissions (read-only, write-only, read-write)
