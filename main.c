#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "data.h"

//Global variables because you might access it from each file to check if the user is logged in
char USER_NAME[50];
char USER_TYPE;

int main()
{

    char run = 'y';  // declaration to keep the program running
    int choice;
    int loggedIn = 0;  // a boolean for if user logged in or not. We start with '0' and if they log on it will change to '1'
    //printf("Hello world!\n");
    loggedIn = login(); // call "loggedIn" function & it returns a '1' if logged in or a '0' if not. The answer is stored in the "LoggedIn" function
    if(loggedIn){
        while(run == 'Y' || run == 'y'){ // while 'y' the program stays running
             choice = mainMenu(); // call "mainMenu function", it returns an answer which is stored in "choice"

             switch(choice){  // The answer from "choice" is used to run the switch
                case 1:
                break;
                case 0:
                    printf("\n*************************/nGoodbye!\n**********************/n");
                    system("pause");
                    return 0;
             }
        }
    }

    return 0;
}
