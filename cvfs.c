
// file inclusion 

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
#  include <string.h>

// ERR edefines 

# define ERR_FILE_ALREADY_EXISTS -1 
# define ERR_THERE_IS_NO_FREEINODE -2 
# define ERR_THEREIS_NO_SIMIILARFILE -3 
 
// # defines 

# define MAXINODE 5  
# define READ 1 
# define WRITE 2 
# define CREAT 3 

// Structures 

/*
    struct name  : boot
    struct information : this struct is defines the activity of booting operating system .

*/
struct boot 
{
    char information [80] ;
} ;

/*
    struct name  : superblock 
    struct information : this struct holds all the information from file systems .

*/
struct superblock
{

    int totalinode ; 
    int totalfreeinode ;
    int totalblocks ; 
    int totalfreebolcks ; 
    int totalusedinode ;
    int totalusedbolck ;

} ;

/*
    struct name  : inode 
    struct information : this struct is defines the inode table from operating system , which contains all meta data of a file .

*/
typedef struct inode 
{
    char * buffer ; 
    char filename [80] ;

    int inodenumber ; 
    int permissions ; 
    int reffrencount ; 
    int filesize ; 
    int filetype ; 

    struct inode * next ; 
   
   
}NODE , *PNODE ; 

 PNODE head = NULL ; 


/*
    struct name        : inode 
    struct information : this struct is used to hold permissions about a file and hold a pointer towards inodes .

*/
typedef struct filetable 
{

    int iCount ; 
    int READOFFSET ; 
    int WRITEOFFSET ; 
    int mode ; 
    PNODE inodeptr ; 
    
} FFILE , * PFILE ; 


/*
    struct name  : UAREA
    struct information : this struct has  a linear linkedlist which holds the pointers of file tables through this conectivity we casn write the data into our buffer . 

*/


struct UAREA
{
    
   char ProcessNmame[80] ;
   PFILE ufdt [MAXINODE] ; 

} ; 


/* STRUCT OBJECTCREATION */

struct boot bootobj ;
struct superblock superblockobj ;
struct inode inodeobj ; 
struct filetable filetableobj ;
struct UAREA uareaobj ;


/*

function name            : structuresinitialisers ; 
function input           : nothing  
function output          : nothing     
function description     : this function is used to intialise all structures by its default values ; 
author                   : Prathmesh Bhanudas Dagade 
date                     : 30 / 10 / 2025  

*/


void structuresinitilizer()
{
    // uareainitializer 
    int i = 0 ;
    
    while (i < MAXINODE )
    {
        uareaobj.ufdt[i] = NULL ;
        i++ ;
    }

    // bootinitializer 
    strcpy(bootobj.information,"booting activity is done succesfully \n ") ;

    // superblockinitialiser 

    superblockobj.totalblocks = 0 ; 
    superblockobj.totalfreebolcks = 0 ; 
    superblockobj.totalinode = MAXINODE ;
    superblockobj.totalfreeinode = MAXINODE ; 
    superblockobj.totalusedinode = 0 ; 
    superblockobj.totalusedbolck = 0 ; 

}

/*

function name            : DILB (disk inode list bolck ) ; 
function input           : nothing  
function output          : nothing     
function description     : this function is used to create linkedlist of inode ; 
author                   : Prathmesh Bhanudas Dagade 
date                     : 30 / 10 / 2025 

*/


void DILB ()
{
   
   
    int i = 0 ; 


    while (i != MAXINODE )
    {

        PNODE newnode = NULL ;

        newnode = ( struct inode * ) malloc (sizeof(struct inode ) ) ;

        newnode->next = NULL ;

        PNODE temp ;

        if (head == NULL )
        {

            head = newnode ; 
            temp = head ;

        }
        else 
        {

            temp -> next = newnode ;
            temp = newnode ;
            
        }

        newnode-> inodenumber = 0 ;
        newnode -> permissions = 0 ; 
        newnode -> reffrencount = 0 ; 
        newnode -> filesize = 0 ; 
        newnode -> filetype = 0 ; 

        i++ ;
    }

}

/*

function name            : IsFileexisit ; 
function input           : char filename
function output          : bool true : if exists , false if dont exists     
function description     : this function is used to check wether the file is present iin our inode or not  ; 
author                   : Prathmesh Bhanudas Dagade 
date                     : 30 / 10 / 2025 

*/

bool isFileExist (char * filename )
{
    bool bRet = false ;
    PNODE temp = head ; 

    while (temp != NULL )
    {
        if (strcmp(temp -> filename , filename ) == 0 )
        {
            bRet = true ; 
            break ; 
        }
        temp = temp -> next ;
    }

    return bRet ; 

}

/*

function name            : CreatFile ; 
function input           : char filename and int permssion for file
function output          : int file discriptor   
function description     : this function is used to creat a file  which handles all expected exceptions ; 
author                   : Prathmesh Bhanudas Dagade 
date                     : 30 / 10 / 2025 

*/

int CreatFile (char * filename , int permissions )
{
    int i = 0 ; 
    PNODE temp = head ;
    bool bRet = isFileExist (filename) ;

    if (temp == NULL)
    {
        return ERR_THERE_IS_NO_FREEINODE;
    }

    if (superblockobj.totalfreeinode == 0 )
    {
        return ERR_THERE_IS_NO_FREEINODE ;
    }

    if (bRet == false )
    {
       
        for( i = 0 ; i < MAXINODE ; i++ )
        {
            if (uareaobj.ufdt[i] == NULL )
            {
               
                break ; 
            }
        }

        while (temp != NULL )
        {
            if (temp -> filetype == 0 )
            {
                break;
            }

            temp = temp -> next ;

        }

    
        uareaobj.ufdt[i] = (PFILE)malloc(sizeof (FFILE)) ;

        uareaobj.ufdt[i]->inodeptr = temp ;  
         

        uareaobj.ufdt[i] ->iCount = 0 ; 
        uareaobj.ufdt[i] ->mode = READ|WRITE ; 
        uareaobj.ufdt[i] ->READOFFSET = 0 ; 
        uareaobj.ufdt[i] ->WRITEOFFSET = 0 ; 


       strcpy(uareaobj.ufdt[i] ->inodeptr->filename , filename ) ;

       uareaobj.ufdt[i] ->inodeptr->filesize = 0 ; 
       uareaobj.ufdt[i] ->inodeptr->filetype = 1 ;
       uareaobj.ufdt[i] ->inodeptr->inodenumber = i ; 
       uareaobj.ufdt[i] ->inodeptr->permissions = permissions ;
       uareaobj.ufdt[i] ->inodeptr->reffrencount = 1 ; 

       uareaobj.ufdt[i] ->inodeptr->buffer = (char *) malloc (1024 * sizeof(char) ) ;

       superblockobj.totalfreeinode -- ;
       superblockobj.totalusedinode ++ ; 

       return i ;
       
    }
    else 
    {
       return ERR_FILE_ALREADY_EXISTS ; 
    }

}

/*

function name            : UnlinkFile ; 
function input           : char filename 
function output          : int file discriptor   
function description     : this function is used to unlink file it is like deleting a file  ; 
author                   : Prathmesh Bhanudas Dagade 
date                     : 30 / 10 / 2025 

*/

int UnlinkFile (char * filename )
{
    int i = 0 ;
    
    bool bRet = isFileExist (filename) ;

    if (bRet == true )
    {
        for( i = 0 ; i < MAXINODE ; i++ )
        {
            if ( strcmp (uareaobj.ufdt[i] ->inodeptr ->filename , filename ) == 0  )
            {
                break ; 
            }
        }

         strcpy(uareaobj.ufdt[i] ->inodeptr ->filename , " '\0' " ) ;
        uareaobj.ufdt[i] ->inodeptr ->reffrencount = 0 ; 
        uareaobj.ufdt[i] ->inodeptr->filesize = 0 ; 
       uareaobj.ufdt[i] ->inodeptr->filetype = 0 ;
       uareaobj.ufdt[i] ->inodeptr->inodenumber = 0 ; 
       uareaobj.ufdt[i] ->inodeptr->permissions = 0 ;
     //  strcpy(uareaobj.ufdt[i] ->inodeptr -) 
 
    
       free ( uareaobj.ufdt[i] ->inodeptr ->buffer ) ; 
      
       uareaobj.ufdt[i] ->iCount = 0 ; 
        uareaobj.ufdt[i] ->mode = 0 ; 
        uareaobj.ufdt[i] ->READOFFSET = 0 ; 
        uareaobj.ufdt[i] ->WRITEOFFSET = 0 ; 


        uareaobj.ufdt[i] -> inodeptr = NULL ;

        free ( uareaobj.ufdt[i]) ;

        uareaobj.ufdt[i] = NULL ;

        superblockobj.totalfreeinode ++ ;
        superblockobj.totalusedinode -- ;

        return i ;

    }
    else 
    {
        return ERR_THEREIS_NO_SIMIILARFILE ;
    }

}


/*

function name            : WriteFile ; 
function input           : char filename 
function output          : int file discriptor   
function description     : this function is used to write data into file   ; 
author                   : Prathmesh Bhanudas Dagade 
date                     : 31 / 10 / 2025 

*/


int WriteFile (char * filename  , int noofdata )
{

    char enterdata [noofdata] ;
    int i = 0 ;
    bool bRet = isFileExist (filename) ;

    if (bRet == true )
    {
        for (i = 0 ; i < MAXINODE ; i++ )
        {
            if (( strcmp(uareaobj.ufdt[i] ->inodeptr ->filename , filename ) == 0 ) && (uareaobj.ufdt[i] ->inodeptr ->filetype == 1 )) 
            {
                break ; 
            }
        }

        printf("write the data \n  ") ;

        scanf("%[^'\n']s",&enterdata) ;


        strcpy(uareaobj.ufdt[i] ->inodeptr ->buffer + uareaobj.ufdt[i] ->WRITEOFFSET , enterdata ) ;

        uareaobj.ufdt[i] ->WRITEOFFSET = uareaobj.ufdt[i] ->WRITEOFFSET + noofdata ;


        return i ; 

    }
    else
    {
        return ERR_THEREIS_NO_SIMIILARFILE ; 
    }

}

/*

function name            : ReadFile ; 
function input           : char filename 
function output          : int file discriptor   
function description     : this function is used to read data from file ; 
author                   : Prathmesh Bhanudas Dagade 
date                     : 31 / 10 / 2025 

*/


char * ReadFile (char * filename  , int noofdata )
{
    char * Buffer = NULL ;

    Buffer = (char * ) malloc (noofdata*(sizeof(char)) ) ;
    
    int i = 0 ;
    bool bRet = isFileExist (filename) ;

    if (bRet == true )
    {
        for (i = 0 ; i < MAXINODE ; i++ )
        {
            if (( strcmp(uareaobj.ufdt[i] ->inodeptr ->filename , filename ) == 0 ) && (uareaobj.ufdt[i] ->inodeptr ->filetype == 1 )) 
            {
                break ; 
            }
        }
    }
    else
    {
        return ERR_THEREIS_NO_SIMIILARFILE ; 
    } 
       

    strcpy( Buffer , uareaobj.ufdt[i] ->inodeptr ->buffer) ;

    uareaobj.ufdt[i] ->READOFFSET = uareaobj.ufdt[i] ->READOFFSET + noofdata ;
    

 
    return Buffer ;

}

/*

function name            : Help; 
function input           : nothing 
function output          : nothing 
function description     : this function is used to help user and gives basic informations about cvfs commands  ; 
author                   : Prathmesh Bhanudas Dagade 
date                     : 1 / 11 / 2025 

*/

void Help ()
{
    printf("-------------------------------Help-------------------------------------\n") ;

    printf("\n") ;

    printf(" 1] Creat enterFilename you want to creat and permission : this command is used to creat a virtual file \n ") ;

    printf("\n") ;

    printf(" 2] write Filename : this command is used to write the data into virtual file \n ") ;

    printf("\n") ;

    printf(" 3] read Filename : this command is used to read the data from virtual file \n ") ;

    printf("\n") ;

    printf(" 4] unlink Filename : this command is used to delete the virtual file \n ") ;

    printf("\n") ;

    printf(" 5] exit : this command is used to exit from cvfs virtual terminal  \n ") ;

    printf("\n") ;

    printf(" 6] clear : this command is used to clear cvfs virtual terminal  \n ") ;

    printf("\n") ;

     printf("------------------------------------------------------------------------\n") ;
}



int main ()
{
    
    DILB ()  ;
    structuresinitilizer () ;

    while (1) 
    {
        char * buffret ;
        int iCount  , iRet = 0 ; 
        char EnterString [80] ;

        printf(" prathmeshs' CVFS $  ") ;
        fgets(  EnterString , 80 , stdin ) ;


        char Command [4] [80] ;
        
       iCount =  sscanf( EnterString , "%s" "%s" "%s" "%s" , Command[0]  , Command[1] ,  Command[2] , Command[3] ) ;
 

        if (iCount == 1 )
        {
            
           if (strcmp(Command[0] , "exit" ) == 0 )
           {    
              break ;
           } 
           else if (strcmp(Command[0] , "clear" ) == 0 )
           {
               system("clear") ;
           }
           else if (strcmp(Command[0] , "help" ) == 0)
           {
              Help() ;
           }


        }
        else if (iCount == 2 )
        {
            if (strcmp(Command[0] , "unlink" ) == 0 )
            {
                iRet = UnlinkFile(Command[1]) ;

                if (iRet ==  ERR_THEREIS_NO_SIMIILARFILE )
                {
                    printf("there is no such a file existing in disk \n") ;
                }
                else 
                {
                    printf("file sucessfuly deleted ffrom disk with the fd : %d \n ",iRet) ;
                }

            }
        
        }
        else if (iCount == 3 )
        {
            if (strcmp(Command[0] , "creat") == 0 )
            {
                iRet = CreatFile(Command[1] , atoi(Command[2] ) ) ;

                if (iRet == ERR_FILE_ALREADY_EXISTS)
                {
                    printf("ERROR : file is Already exists in disk \n ") ;  
                }
                else if (iRet == ERR_THERE_IS_NO_FREEINODE)
                {
                    printf("ERROR : There is no enough inode to create this file \n ") ;
                }
                else 
                {
                    printf(" File Created Sucessfuly with fd : %d \n ",iRet ); 
                }
            }
            else if (strcmp(Command[0] , "write" ) == 0 )
            {
                iRet = WriteFile(Command[1] ,atoi(Command[2])) ;

                if (iRet ==  ERR_THEREIS_NO_SIMIILARFILE )
                {
                    printf("there is no such a file existing in disk \n") ;
                }
                else 
                {
                    printf("data written sucessfuly in disk with fd : %d  \n ",iRet ) ;
                }
            }
            else if (strcmp(Command[0] , "read" ) == 0 )
            {
                buffret = ReadFile(Command[1] ,atoi(Command[2])) ;

                if (iRet ==  ERR_THEREIS_NO_SIMIILARFILE )
                {
                    printf("there is no such a file existing in disk \n") ;
                }
                else 
                {
                    printf("data from file is : \n  %s \n ", buffret ) ;
                }
            }

        }
        else if (iCount == 4 )
        {

        }
        else 
        {
                 
        }

    }

    return 0 ; 
}
