#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "data.h"
#include "menu.h"

int addBooking(){
    int artisteId;
    booking bookingToAdd;
    artiste artisteForBooking;
    int artisteFound = 0, position;
    char filename[255];

    system("cls");
    printf("******************************\nInsert new booking\n******************************\n");
    printf("Enter an artiste ID to add a booking for that artiste: \n");
    quickViewArtisteList();
    fflush(stdin);
    scanf("%d", &artisteId);

    sprintf(filename, "Booking-%d.dat", artisteId);
    artisteFound = loadArtisteFromFile(&artisteForBooking, artisteId);
    if(artisteFound){
        bookingToAdd.bookingNum = generateBookingNum(filename);
        position = findBookingPositionInFile(bookingToAdd.bookingNum, filename);
        printf("\n%dpos\n", bookingToAdd.bookingNum);
        if(!(position > 15)){

            //generateBookingNumber
            printf("Adding booking for %s (%s)", artisteForBooking.realName, artisteForBooking.stageName);
            enterBookingBasic(&bookingToAdd, filename);
            enterBookingLocation(&bookingToAdd);
            enterBookingAccommodation(&bookingToAdd);
            enterBookingPrice(&bookingToAdd);
            printf("priced %d", bookingToAdd.bookingNum);
            printf("\n%d bookings(s) saved to database\n", saveBooking(&bookingToAdd, artisteForBooking.artisteId, position, "ab+"));
        }else{
            printf("You have reached the maximum number of bookings for this artiste - 15. \nYou must delete a booking before you can add a new one.");
        }

    }
    system("pause");
}

int saveBooking(booking *bookingPtr, int artisteId, int position, char mode[]){
    int written = 0;
    char filename[255];
    sprintf(filename, "Booking-%d.dat", artisteId);
    FILE *filePtr;
    filePtr = fopen(filename, mode);
    if(filePtr == NULL){
        printf("File could not be openend.");
    }else{
        fseek(filePtr, sizeof(*bookingPtr)*(position-1), SEEK_SET);
        written = fwrite(bookingPtr, sizeof(*bookingPtr), 1, filePtr);

    }
    fclose(filePtr);
    return written;
}

void updateBooking(int artisteId){
    int bookingNum, infoToUpdateChoice;
    booking bookingToUpdate;
    int bookingFound = 0, artisteFound = 0;
    char filename[255];
    int position = 1;
    artiste artisteForBooking;

    sprintf(filename, "Booking-%d.dat", artisteId);
    system("cls");

    printf("*******************************\nEnter booking num to update information\n*******************************\n Booking Num: ");
    scanf("%d", &bookingNum);

    bookingFound = loadBookingFromFile(&bookingToUpdate, bookingNum, filename);
    if(bookingFound ){
        artisteFound = loadArtisteFromFile(&artisteForBooking, artisteId);
        if(artisteFound){
            printf("Editing booking for %s (%s)", artisteForBooking.realName, artisteForBooking.stageName);
        }
        position = findBookingPositionInFile(bookingToUpdate.bookingNum, filename);
        infoToUpdateChoice = updateBookingMenu();
        switch(infoToUpdateChoice){
            case 1:
                enterBookingBasic(&bookingToUpdate);
                printf("\n%d artiste(s) saved to database\n",saveBooking(&bookingToUpdate, artisteId, position, "rb+"));
                break;
            case 2:
                enterBookingLocation(&bookingToUpdate);
                printf("\n%d artiste(s) saved to database\n", saveBooking(&bookingToUpdate, artisteId, position, "rb+"));
                break;
            case 3:
                enterBookingAccommodation(&bookingToUpdate);
                printf("\n%d artiste(s) saved to database\n",saveBooking(&bookingToUpdate, artisteId, position, "rb+"));
                break;
            case 4:
                enterBookingPrice(&bookingToUpdate);
                printf("\n%d artiste(s) saved to database\n",saveBooking(&bookingToUpdate, artisteId, position, "rb+"));
                break;

            case 5 :
                break;
        }

    }
    system("pause");

}

int deleteBooking(int artisteId){
    int bookingNum, found = 0, written = 0;
    booking bookingToDelete;
    int bookingFound = 0, artisteFound = 0;;
    char filename[255];
    int position = 1;
    artiste artisteForBooking;

    FILE *filePtr;
    FILE *tempFilePtr;
    sprintf(filename, "Booking-%d.dat", artisteId);

    system("cls");

    artisteFound = loadArtisteFromFile(&artisteForBooking, artisteId);
    if(artisteFound){
        printf("Editing booking for %s (%s)", artisteForBooking.realName, artisteForBooking.stageName);
    }

    filePtr = fopen(filename, "rb");
    if(filePtr == NULL){
        printf("No booking found for that artiste.");
        return -1;
    }
    tempFilePtr = fopen("tempBook.bin", "wb");
    if(tempFilePtr == NULL){
        printf("Delete cannot be completed at this moment.");
        return -1;
    }

    printf("*******************************\nEnter booking num to delete record\n*******************************\n Booking Num: ");
    scanf("%d", &bookingNum);

    while(!feof(filePtr)){
        found = fread(&bookingToDelete, sizeof(bookingToDelete), 1, filePtr);
        if(found && bookingToDelete.bookingNum == bookingNum){
            printf("Booking deleted");
        }else if(found){
            written = fwrite(&bookingToDelete, sizeof(bookingToDelete), 1, tempFilePtr);
        }
    }

    fclose(filePtr);
    fclose(tempFilePtr);

    int ret = remove(filename);

    if(ret == 0) {
        printf("File renamed successfully");
    } else {
        printf("Error: unable to rename the file");
    }
    rename("tempBook.bin", filename);
    system("pause");

}

void viewBooking(int artisteId){
    int bookingNum;
    booking bookingToView;
    int bookingFound = 0;
    char filename[255];
    sprintf(filename, "Booking-%d.dat", artisteId);
    system("cls");

    printf("*******************************\nEnter booking id to view information\n*******************************\n Booking Num id: ");
    scanf("%d", &bookingNum);

    bookingFound = loadBookingFromFile(&bookingToView, bookingNum, filename);
    if(bookingFound ){
        printBooking(&bookingToView);
    }
    system("pause");
}
void viewBookingList(int artisteId){
    int count = 1, found = 0;
    artiste artisteFound;
    booking bookingFound;
    char filename[255];
    char dateString[255];
    FILE *filePtr;
    if(loadArtisteFromFile(&artisteFound, artisteId)){
        sprintf(filename, "Booking-%d.dat", artisteId);
        filePtr = fopen(filename, "rb+");
        if(filePtr == NULL){
            printf("Booking database could not be opened.\n");
        }else{
    //        fseek(filePtr, sizeof(*artistePtr)*id-1, SEEK_END);
    //        currentPosition = ftell(filePtr);
            while(!feof(filePtr)){
                found = fread(&bookingFound, sizeof(bookingFound), 1, filePtr);
                if(found){
                    printf("\n******************************************\nBooking ID#: %3d", bookingFound.bookingNum);
                    strftime(dateString, sizeof(dateString), "%x - %I:%M%p", &(bookingFound.date));
                    printf("\nDate: %s", dateString);
                    printf("\nLocation: %s, %s, %s, %s \n", bookingFound.location.street,bookingFound.location.cityTown, bookingFound.location.parishState, bookingFound.location.country);
                    printf("\n------------------------------------------\n");
                    count++;
                }
            }
        }
        fclose(filePtr);
    }
    return count;
    system("pause");
}

void printBooking(booking *bookingPtr){
    char dateString[255];
    printf("\n******************************************\nID#: %3d", bookingPtr->bookingNum);
    strftime(dateString, sizeof(dateString), "%x - %I:%M%p", &(bookingPtr->date));
    printf("\nDate: %s", dateString);
    printf("\nLocation: %s, %s, %s, %s \n", bookingPtr->location.street, bookingPtr->location.cityTown, bookingPtr->location.parishState, bookingPtr->location.country);
    printf("\n------------------------------------------\n");
}


int loadBookingFromFile(booking *bookingPtr, int id, char filename[]){
    int count = 0, match = 0;
    FILE *filePtr;
    filePtr = fopen(filename, "rb");
    if(filePtr == NULL){
        printf("Booking database could not be opened.");
    }else{
//        fseek(filePtr, sizeof(*artistePtr)*id-1, SEEK_END);
//        currentPosition = ftell(filePtr);
        while(!feof(filePtr)){
            count = fread(bookingPtr, sizeof(*bookingPtr), 1, filePtr);
            if(bookingPtr->bookingNum == id){
                match = 1;
                break;
            }
        }
    }
    fclose(filePtr);
    return match;
}
int checkBookingDate(booking *bookingPtr, char filename[]){
    time_t now;
    booking book;
    time(&now);
    double secondsFromToday = 0;
    int count = 0, match = 0;

    secondsFromToday = difftime(now, mktime(&(bookingPtr->date)));
    printf("%f %d", secondsFromToday, bookingPtr->date.tm_mday);


    FILE *filePtr;
    filePtr = fopen(filename, "rb");
    if(filePtr == NULL){
        printf("File could not be openend.");
    }else{
//        fseek(filePtr, sizeof(*artistePtr)*id-1, SEEK_END);
//        currentPosition = ftell(filePtr);
        while(!feof(filePtr)){
            count = fread(&book, sizeof(booking), 1, filePtr);
          if(count){

          }
//            if(bookingPtr->bookingNum == id){
//                match = 1;
//                break;
//            }
        }
    }
    fclose(filePtr);
    return count;
}
int findBookingPositionInFile(int id, char filename[]){
    int count = 0, match = 0, read = 0;
    booking book;
    FILE *filePtr;
    filePtr = fopen(filename, "rb");
    if(filePtr == NULL){
        //printf("File could not be openend.");
        count++;
    }else{
//        fseek(filePtr, sizeof(*artistePtr)*id-1, SEEK_END);
//        currentPosition = ftell(filePtr);
        while(!feof(filePtr)){
            count = count + 1;
            read = fread(&book, sizeof(book), 1, filePtr);
            if(book.bookingNum == id){
                break;
            }
        }
    }
    fclose(filePtr);
    return count;
}
int countBooking(char filename[]){
    booking book;
    int currentPosition = 0;
    int count = 0;
    FILE *filePtr;
    filePtr = fopen(filename, "rb");
    if(filePtr == NULL){
        printf("Booking database could not be opened.");
    }else{
        fseek(filePtr, 0, SEEK_END);
        currentPosition = ftell(filePtr);
        count = (currentPosition/(sizeof(book)));
    }
    fclose(filePtr);
//    printf("%d count openend.", count);
    return count;
}
int generateBookingNum(char filename[]){
    booking book;
    int currentPosition = 0;
    int count = 0, id=1;

    FILE *filePtr;
    filePtr = fopen(filename, "rb");
    if(filePtr == NULL){
        printf("Booking file could not be openend.%s", filename);
    }else{
        count = fseek(filePtr, 0-(sizeof(book)), SEEK_END);

        if(count==0){
            fread(&book, sizeof(book),1,filePtr);
            //printf("%d", book.bookingNum);
            id = book.bookingNum + 1;
        }
    }
    fclose(filePtr);
    return id;
}
void enterBookingBasic(booking *bookingPtr, char filename[]){
    printf("Enter booking type - L for local and F for foreign: ");
    fflush(stdin);
    scanf("%c", &(bookingPtr->type));
    enterBookingDate(bookingPtr, filename);
}
void enterBookingLocation(booking *bookingPtr){
    printf("*****************************\nBooking location\n*****************************\n");
    printf("Enter street address: ");
    fflush(stdin);
    scanf("%[^\n]s", bookingPtr->location.street);
    printf("Enter city: ");
    fflush(stdin);
    scanf("%[^\n]s", bookingPtr->location.cityTown);
    printf("Enter parish/state: ");
    fflush(stdin);
    scanf("%[^\n]s", bookingPtr->location.parishState);
    printf("Enter country: ");
    fflush(stdin);
    scanf("%[^\n]s", bookingPtr->location.country);
}
void enterBookingAccommodation(booking *bookingPtr){
    printf("*****************************\nBooking accomodation\n*****************************\n");
    printf("Enter flight information: ");
    fflush(stdin);
    scanf("%[^\n]s", bookingPtr->flightInfo);
    printf("Enter booking hotel: ");
    fflush(stdin);
    scanf("%[^\n]s", bookingPtr->hotel);
}
void enterBookingPrice(booking *bookingPtr){
    printf("*****************************\nBooking rates\n*****************************\n");
    printf("Is this booking voluntary - enter y for yes and n for no: ");
    fflush(stdin);
    scanf("%c", &(bookingPtr->voluntary));

    if(bookingPtr->voluntary == 'y' || bookingPtr->voluntary == 'Y'){
        bookingPtr->showRateLocal = 0;
        bookingPtr->showRateForeign = 0;
    }else{
        printf("Enter local rate: ");
        fflush(stdin);
        scanf("%f", &(bookingPtr->showRateLocal));
        printf("Enter foreign rate: ");
        fflush(stdin);
        scanf("%f", &(bookingPtr->showRateForeign));
    }
    if(bookingPtr->type == 'f' || bookingPtr->type == 'F'){
        printf("Enter travel and accomodation cost per team member: ");
        fflush(stdin);
        scanf("%f", &(bookingPtr->travelCost));
        printf("Enter team size(no. of members): ");
        fflush(stdin);
        scanf("%d", &(bookingPtr->teamSize));
    }
}

void enterBookingDate(booking *bookingPtr, char filename[]){
    printf("Enter booking date: ");
    printf("Enter booking day(dd): ");
    fflush(stdin);
    scanf("%d", &(bookingPtr->date.tm_mday));
    printf("Enter booking month(mm): ");
    fflush(stdin);
    scanf("%d", &(bookingPtr->date.tm_mon));
    printf("Enter booking year(yyyy): ");
    fflush(stdin);
    scanf("%d", &(bookingPtr->date.tm_year));
    printf("Enter booking Time: ");
    printf("Enter booking hour(hh): ");
    fflush(stdin);
    scanf("%d", &(bookingPtr->date.tm_hour));
    printf("Enter booking minute(mm): ");
    fflush(stdin);
    scanf("%d", &(bookingPtr->date.tm_min));

    checkBookingDate(bookingPtr, filename);
}
