#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "data.h"

//extern ensure global variables does not throw errors because it would've been defined elsewhere in the program.
//when the program sees "Extern" it assumes its defined elsewhere so it searhes and when found, grabs it.
extern char USER_NAME[50];
extern char USER_TYPE[50];

//displays main menu
int mainMenu(){
    int choice;
    char menuText[400];
    char welcomeMessage[400];
    // "1" means true so, while true, the program will continue to run forever. When exit is selected, it will break out of the loop.
    while(1){
        //if 'a' or 'A', data will be copied into "menuText"
        //this portion of the menu is for the manager
        if(getUserType() =='a' || getUserType() =='A'){
            strcpy(menuText, "****************************************************\n");
            strcat(menuText, "1. Manage Artiste Data\n2. Manage Artiste Bookings\n3. Manage Users\n4. Generate Reports\n5. Exit\n");
            strcat(menuText, "****************************************************\n");
            strcat(menuText, "Enter The number that corresponds to your choice\n");
            strcat(menuText, "****************************************************\n");
        }else{
            //else these data will be copied into "menuText"
            //this portion is for the clerk
            strcpy(menuText, "****************************************************\n");
            strcat(menuText, "1. Manage Artiste Data\n2. Manage Artiste Bookings\n3. Exit\n");
            strcat(menuText, "****************************************************\n");
            strcat(menuText, "Enter The number that corresponds to your choice\n");
            strcat(menuText, "****************************************************\n");
        }
        //introduction of the program being copied into "welcomeMessage"
        strcpy(welcomeMessage, "********************************************************\nWelcome To Artiste Booking.\n-----------------------------------------------\n");
        strcat(welcomeMessage, "This software allows to manage artiste bookings.\n");

        system("cls");
        //printing welcome message
        printf("%s", welcomeMessage);
        //printing the selected menu
        printf("%s", menuText);
        fflush(stdin);
        //reading choice/option selected by the user
        scanf("%d", &choice);

        //using the choice of the user to switch through the cases
        switch(choice)
        {
            case 1:
                if(getUserType() =='a' || getUserType() =='A'){
                   //if admin/manager then we call "artisteMenu" function and store answer in "choice"
                    choice = artisteMenu();
                }else{
                    //else if its the clerk, then we call "artisteMenuClerk function and store answer in "choice"
                    choice = artisteMenuClerk();
                //printf("test %d", choice);
            break;
            case 2:
                //everybody can do booking so "bookingMenu" is called and answer stored in "choice".
                choice = bookingMenu();
            break;
            case 3:
                //only admin/manager can access "userMenu"
                //otherwise, it'll throw 0
                if(getUserType() =='a' || getUserType() =='A'){
                    choice = userMenu();
                }else{
                    choice = 0;
                    return choice;
                }
            break;
            case 4:
                //only admin/manager can "generateReport"
                if(getUserType() =='a' || getUserType() =='A'){
                    generateReport();
                }else{
                    //this start over the menu if its not the admin/manager
                    choice = -1;
                    return choice;
                }
                break;
            default:
                return choice;
                break;
        }
        //printf("test");
        //if its not the admin/manager, then it will keep asking for user password until the correct one is given
        if(choice == -1){
            system("cls");
            continue;
        } else{
            break;
        }
    }
    return choice;
    }
}

// artiste submenu
int artisteMenu(){
    int artisteChoice;
    char menuText[400];
    //copying menu in "menuText"
    strcpy(menuText, "****************************************************\n");
    strcat(menuText, "1. Add Artiste\n2. View Artiste\n3. List Artstes\n4. Update artiste\n5. Add artiste Earnings\n6. Add artiste payment\n7. Delete artiste\n8. Back\n");
    strcat(menuText, "****************************************************\n");
    strcat(menuText, "Enter The number that corresponds to your choice\n");
    strcat(menuText, "****************************************************\n");
    printf("%s", menuText);
    fflush(stdin);
    scanf("%d", &artisteChoice);
    //switch statement used to switch through choice selected
    //a function will be called based on menu's selection
    switch(artisteChoice)
    {
        case 1:
            addArtiste();
        break;
        case 2:
            viewArtiste();
            break;
        case 3:
            viewArtisteList();
            break;
        case 4:
            updateArtiste();
            break;
        case 5:
            addEarnings();
            break;
        case 6:
            addPayment();
            break;
        case 7:
            deleteArtiste();
            break;
        default:
            //this starts over the menu
            artisteChoice = -1;
            break;
    }

    return artisteChoice;
}


//artiste menu for clerks
int artisteMenuClerk(){
    int artisteChoice;
    char menuText[400];
    //copying menu in "menuText"
    strcpy(menuText, "****************************************************\n");
    strcat(menuText, "1. View Artiste\n2. List Artstes\n3. Back\n");
    strcat(menuText, "****************************************************\n");
    strcat(menuText, "Enter The number that corresponds to your choice\n");
    strcat(menuText, "****************************************************\n");
    printf("%s", menuText);
    fflush(stdin);
    scanf("%d", &artisteChoice);
    //switch statement used to switch through choice selected
    //a function will be called based on menu's selection
    switch(artisteChoice)
    {
        case 1:
            viewArtiste();
            break;
        case 2:
            viewArtisteList();
            break;
        default:
            //this starts over the menu
            artisteChoice = -1;
            break;
    }

    return artisteChoice;
}

//update artiste menu
int updateArtisteMenu(){
    int artisteChoice;
    char menuText[400];
    //copying menu in "menuText"
    strcpy(menuText, "****************************************************\n");
    strcat(menuText, "1. Edit Personal information\n2. Edit Financial information\n3. Edit Foundation information\n4. Back\n");
    strcat(menuText, "****************************************************\n");
    strcat(menuText, "Enter The number that corresponds to your choice\n");
    strcat(menuText, "****************************************************\n");
    printf("%s", menuText);
    fflush(stdin);
    scanf("%d", &artisteChoice);
    return artisteChoice;
}

//displays booking menu
int bookingMenu(){
    int bookingChoice;
    int artisteId;
    char menuText[400];
    //copying menu in "menuText"
    strcpy(menuText, "****************************************************\n");
    strcat(menuText, "1. Add booking\n2. View bookings list by Artiste\n3. View Booking\n4. Update booking\n5. Delete Booking\n6. Back\n");
    strcat(menuText, "****************************************************\n");
    strcat(menuText, "Enter The number that corresponds to your choice\n");
    strcat(menuText, "****************************************************\n");
    printf("%s", menuText);
    fflush(stdin);
    scanf("%d", &bookingChoice);
    //switch statement used to switch through choice selected
    switch(bookingChoice)
    {
        case 1:
            addBooking();
        break;
        case 2:
            system("cls");
            printf("***************************************\nView artiste bookings\n******************************\n");
            printf("Enter the artiste's id to view a list of bookings: ");
            fflush(stdin);
            scanf("%d", &artisteId);
            //"viewBookingList" function being called based on inputted id
            viewBookingList(artisteId);
            break;
        case 3:
            system("cls");
            printf("***************************************\nView artiste bookings\n******************************\n");
            printf("Enter the artiste's id to view a list of bookings: ");
            fflush(stdin);
            scanf("%d", &artisteId);
            //"viewBooking" function being called based on inputted id
            viewBooking(artisteId);
            break;
        case 4:
            system("cls");
            printf("***************************************\nView artiste bookings\n******************************\n");
            printf("Enter the artiste's id to view a list of bookings: ");
            fflush(stdin);
            scanf("%d", &artisteId);
            //"updateBooking" function beling called based on inputted id
            updateBooking(artisteId);
            break;
        case 5:
            system("cls");
            printf("***************************************\nView artiste bookings\n******************************\n");
            printf("Enter the artiste's id to delete a booking for that artiste: ");
            fflush(stdin);
            scanf("%d", &artisteId);
            //"deleteBooking" function beling called based on inputted id
            deleteBooking(artisteId);
            break;
        case 6:
            bookingChoice = -1;
            break;
    }
    return bookingChoice;
}

//displays update booking options

int updateBookingMenu(){
    int artisteChoice;
    char menuText[400];
    //copying menu in "menuText"
    strcpy(menuText, "****************************************************\n");
    strcat(menuText, "1. Edit basic information\n2. Edit location\n3. Edit Accommodation information\n4. Edit Price\n5. Back\n");
    strcat(menuText, "****************************************************\n");
    strcat(menuText, "Enter The number that corresponds to your choice\n");
    strcat(menuText, "****************************************************\n");
    printf("%s", menuText);
    fflush(stdin);
    scanf("%d", &artisteChoice);
    return artisteChoice;
}

// displays user menu
int userMenu(){
    int userChoice;
    char menuText[400];
    //copying menu in "menuText"
    strcpy(menuText, "****************************************************\n");
    strcat(menuText, "1. Add User\n2. View User\n3. List Users\n4. Update users\n5. Unblock user\n6. Delete user\n7. Back\n");
    strcat(menuText, "****************************************************\n");
    strcat(menuText, "Enter The number that corresponds to your choice\n");
    strcat(menuText, "****************************************************\n");
    printf("%s", menuText);
    fflush(stdin);
    scanf("%d", &userChoice);
    //switch statement used to switch through choice selected
    //a function is being called based on selection
    switch(userChoice)
    {
        case 1:
            addUser();
        break;
        case 2:
            viewUser();
            break;
        case 3:
            viewUserList();
            break;
        case 4:
            updateUser();
            break;
        case 5:
            unblockUser();
            break;
        case 6:
            deleteUser();
            break;
        case 7:
            //this starts over the menu
            userChoice = -1;
            break;
    }

    return userChoice;
}
