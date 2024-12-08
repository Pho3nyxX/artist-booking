#include <stdio.h>
#include <stdlib.h>
#include "data.h"

void addArtiste(){
    struct Artiste artiste;
    int position = 1;

    system("cls");

    char addFinancials = 'n';
//    artiste.artisteId = (countArtiste()+1);
    artiste.artisteId = generateArtisteId();
    position = findPositionInFile(artiste.artisteId);
    if(!(position > 20)){

        //printf("artiste id: %d", artiste.artisteId);
    //    printf("position: %d \n",findPositionInFile(artiste.artisteId));
        printf("*******************************\nEnter new artiste information\n*******************************\n");
        enterPersonalInformation(&artiste);

        printf("would you like to Add financial information for this artiste?\n --Press y to add financials information or any key to skip--");
        fflush(stdin);
        scanf("%c", &addFinancials);
        if(addFinancials == 'y' || addFinancials == 'Y'){ /*if yes, "enterFinancialInformation" function will run */
            enterFinancialInformation(&artiste);
        }
        printf("would you like to add a foundation for this artiste?\n --Press y to add foundation information or any key to skip--");
        fflush(stdin);
        scanf("%c", &addFinancials);
        if(addFinancials == 'y' || addFinancials == 'Y'){ /*if yes, "enterFoundationInformation" function will run */
            enterFoundationInformation(&artiste);
        }
        //appending info entered to binary and updating same time
        printf("\n%d artiste(s) saved to database\n", saveArtiste(&artiste, position, "ab+"));
        //artiste is stored to database where the "countArtiste()" is being used to track the amount of artiste entered//
        printf("\n%d artistes stored in database\n", countArtiste());
    }else{
        //letting the user know they've reached their limit of 20 artiste//
        printf("You have reached the maximum number of artistes - 20. You must delete an artiste to add a new one.");
    }
    system("pause");

}
void viewArtiste(){
    int artisteId;
    artiste artisteToView;
    int artistesFound = 0;
    system("cls");

    printf("*******************************\nEnter artiste id to view information\n*******************************\n Artiste id: ");
    scanf("%d", &artisteId);

    //"loadArtisteFromFile()" is being called & info stored in "artistesFound" variable//
    artistesFound = loadArtisteFromFile(&artisteToView, artisteId);
    //if the artiste is found, "printArtiste" as well as "viewBookingList" functions will run//
    if(artistesFound ){
        printArtiste(&artisteToView);
        viewBookingList(artisteToView.artisteId);
    }
    system("pause");

}


void updateArtiste(){
    int artisteId, infoToUpdateChoice;
    artiste artisteToUpdate;
    int artistesFound = 0;
    system("cls");
    int position = 1;

    //asking for the id of the artiste whose info they wish to update
    printf("*******************************\nEnter artiste id to update information\n*******************************\n Artiste id: ");
    scanf("%d", &artisteId);

    //"loadArtisteFromFile()" is called and valued saved in "artistesFound" variable
    artistesFound = loadArtisteFromFile(&artisteToUpdate, artisteId);
    //"findPositionInFile()" as well as "updateArtisteMenu()" will run if artiste is found//
    if(artistesFound ){
        position = findPositionInFile(artisteToUpdate.artisteId);
        infoToUpdateChoice = updateArtisteMenu();
       //switch statement used to run the functions they wish to update//
       //a message to let them know the info is saved to the database is outputted on the screen//
       //its written to the artistes.dat binary file and updated same time//
        switch(infoToUpdateChoice){
            case 1:
                enterPersonalInformation(&artisteToUpdate);
                printf("\n%d artiste(s) saved to database\n",saveArtiste(&artisteToUpdate, position, "rb+"));
                break;
            case 2:
                enterFinancialInformation(&artisteToUpdate);
                printf("\n%d artiste(s) saved to database\n", saveArtiste(&artisteToUpdate, position, "rb+"));
                break;
            case 3:
                enterFoundationInformation(&artisteToUpdate);
                printf("\n%d artiste(s) saved to database\n",saveArtiste(&artisteToUpdate, position, "rb+"));
                break;

            case 4 :
                break;
        }

    }else{
        printf("\nartiste not found\n"); //letting the user know the artist is not found//
    }
    system("pause");

}

//"addEarnings" takes the info from the user. The "loadArtisteFromFile()" is called and its value stored to "artistesFound"
//The purpose of this function is: if the artiste makes money, its added to the "accountBal" and "earningPerYr"
void addEarnings(){
    int artisteId, infoToUpdateChoice;
    artiste artisteToUpdate;
    int artistesFound = 0;
    float amount;
    system("cls");
    int position = 1;

    printf("*******************************\nEnter artiste id to add earnings\n*******************************\n Artiste id: ");
    scanf("%d", &artisteId);

    //try to load artist from database
    artistesFound = loadArtisteFromFile(&artisteToUpdate, artisteId);
    if(artistesFound ){
            //if artist has been found allow balance to be updated
        position = findPositionInFile(artisteToUpdate.artisteId);
        printf("The current balance is %.2f\n", artisteToUpdate.accountBal);
        scanf("%f", &amount);
        artisteToUpdate.accountBal = artisteToUpdate.accountBal + amount;
        artisteToUpdate.earningPerYr = artisteToUpdate.earningPerYr + amount;
        //try to save artist to the database and print result to the user
        printf("\n%d artiste(s) saved to database\n",saveArtiste(&artisteToUpdate, position, "rb+"));
        printf("The new account balance is %.2f\n", artisteToUpdate.accountBal);
    }
    //allow the user time to view the results before clearing the menu
    system("pause");
}

//"addPayment" takes the info from the user. The "loadArtisteFromFile()" is called and its value stored to "artistesFound"
//The purpose of this function is: if any payment has to be taken from the artist account
void addPayment(){
    int artisteId, infoToUpdateChoice;
    artiste artisteToUpdate;
    int artistesFound = 0;
    float amount;
    system("cls");
    int position = 1;

    printf("*******************************\nEnter artiste id to deduct payment\n*******************************\n Artiste id: ");
    scanf("%d", &artisteId);

    artistesFound = loadArtisteFromFile(&artisteToUpdate, artisteId);
    if(artistesFound ){
        position = findPositionInFile(artisteToUpdate.artisteId);
        printf("The current balance is %.2f\n", artisteToUpdate.accountBal);
        scanf("%f", &amount);
        artisteToUpdate.accountBal = artisteToUpdate.accountBal - amount;
        artisteToUpdate.earningPerYr = artisteToUpdate.earningPerYr - amount;
        printf("\n%d artiste(s) saved to database\n",saveArtiste(&artisteToUpdate, position, "rb+"));
        printf("The new account balance is %.2f\n", artisteToUpdate.accountBal);
    }
    system("pause");
}

//This list all artistin the database (id, name and stage name)
void viewArtisteList(){
    int count = 1, found = 0;
    artiste artisteFound;
    FILE *filePtr;
    filePtr = fopen(ARTISE_FILE, "rb");
    if(filePtr == NULL){
        printf("File could not be openend.");
    }else{
//        fseek(filePtr, sizeof(*artistePtr)*id-1, SEEK_END);
//        currentPosition = ftell(filePtr);
        //loop through artist until end of file is reached
        while(!feof(filePtr)){
            found = fread(&artisteFound, sizeof(artisteFound), 1, filePtr);
            if(found){
                    //print artist name and stage name
                printf("\n******************************************\nID#: %3d", artisteFound.artisteId);
                printf("\nName: %s", artisteFound.realName);
                printf("\nStage Name: %s\n", artisteFound.stageName);
                printf("\n--------------------------------------------\n");
                count++;
            }
        }
    }
    fclose(filePtr);
    system("pause");
    return count;
}

//This list all artistin the database (id, name and stage name)
void quickViewArtisteList(){
    int count = 1, found = 0;
    artiste artisteFound;
    FILE *filePtr;
    filePtr = fopen(ARTISE_FILE, "rb");
    if(filePtr == NULL){
        printf("Artistes database could not be openend.");
    }else{
//        fseek(filePtr, sizeof(*artistePtr)*id-1, SEEK_END);
//        currentPosition = ftell(filePtr);
        //loop through artist until end of file is reached
        printf("\n-------------------------------------------\n");
        printf("ID: \tName");
        while(!feof(filePtr)){
            found = fread(&artisteFound, sizeof(artisteFound), 1, filePtr);
            if(found){
                    //print artist name and stage name
                printf("\n%3d \t%s (%s)", artisteFound.artisteId, artisteFound.realName, artisteFound.stageName);
                printf("\n--------------------------------------------\n");
                count++;
            }
        }
    }
    fclose(filePtr);
    return count;
}

//prints an artist information
void printArtiste(artiste *artistePtr){
    printf("\n******************************************\nName: %s", artistePtr->realName);
    printf("\nStage Name: %s", artistePtr->stageName);
    printf("\nContact No: %s", artistePtr->telephone);
    printf("Address: %s, %s\n\t%s\n\t%s", artistePtr->address.street, artistePtr->address.cityTown, artistePtr->address.parishState, artistePtr->address.country);
    printf("--------------------------------------------\n");
}

//This function saves an artist to the database
//it accepts the 'artist' as well as the 'position' they are to be placed at in the file and the 'mood'
int saveArtiste(artiste *artistePtr, int pos, char mode[]){
    int written = 0, position = 0;
    FILE *filePtr;
    filePtr = fopen(ARTISE_FILE, mode);
    if(filePtr == NULL){
        printf("File could not be openend.\n");
    }else{
        //if(artistePtr->artisteId>1){
        position = findPositionInFile(artistePtr->artisteId);
        fseek(filePtr, sizeof(*artistePtr)*(position-1), SEEK_SET);
        //}
        //printf("full name %d: %s", sizeof(*artistePtr),artistePtr->realName);
        written = fwrite(artistePtr, sizeof(*artistePtr), 1, filePtr);

    }
    fclose(filePtr);
    return written;
}

//allows the deletion of an artiste. Because there is no way to delete a structure from a binary file, we will
//copy all records except the one to be deleted, to a new file
//the artiste file will then be deleted and the new file renamed to replace it
int deleteArtiste(){
    int artisteId, found = 0, written = 0;
    artiste artisteToDelete;
    int artisteFound = 0;
    char filename[255];
    int position = 1;
    FILE *filePtr;
    FILE *tempFilePtr;
    system("cls");

    printf("*******************************\nEnter Artiste ID to delete record\n*******************************\n Artiste ID: ");
    scanf("%d", &artisteId);
    filePtr = fopen(ARTISE_FILE, "rb");
    if(filePtr == NULL){
        printf("File could not be openend.");
        return -1;
    }
    tempFilePtr = fopen("tempArtiste.bin", "wb");
    if(tempFilePtr == NULL){
        printf("File could not be openend.");
        return -1;
    }
    //loop through the artist found in the file and write them to the new file.
    //the one that is to be deleted is not transferred to the new file
    while(!feof(filePtr)){
        found = fread(&artisteToDelete, sizeof(artisteToDelete), 1, filePtr);
        if(found && artisteToDelete.artisteId == artisteId){
                //if this artiste is the one that is to be deleted, ignore it
            printf("\n**********************************\nArtiste deleted.\n");
        }else if(found){
            //or else write it to the temp file
            written = fwrite(&artisteToDelete, sizeof(artisteToDelete), 1, tempFilePtr);
        }
    }

    fclose(filePtr);
    fclose(tempFilePtr);
//the deletion of the original file
    int ret = remove(ARTISE_FILE);

	if(ret == 0) {
        printf("Delete finished successfully");
    } else {
        printf("Unable to finalise delete. Contact admin");
    }
   //if everything goes through, the renaming is done
   rename("tempArtiste.bin", ARTISE_FILE);
   system("pause");
}

//loads an artiste record from the file if it exists. Record is matched by id. returns zero if it doesn't
int loadArtisteFromFile(artiste *artistePtr, int id){
    int count = 0, match = 0;
    FILE *filePtr;
    filePtr = fopen(ARTISE_FILE, "rb");
    if(filePtr == NULL){
        printf("File could not be openend.");
    }else{
//        fseek(filePtr, sizeof(*artistePtr)*id-1, SEEK_END);
//        currentPosition = ftell(filePtr);
//      loop through records
        while(!feof(filePtr)){
            count = fread(artistePtr, sizeof(*artistePtr), 1, filePtr);
//            check if record exists
            if(artistePtr->artisteId == id){
                match = 1;
                break;
            }
        }
    }
    fclose(filePtr);
    return match;
}

// loads a record from the file based on stage name
int loadArtisteFromFileByName(artiste *artistePtr, char stageName[]){
    int count = 0, match = 0;
    FILE *filePtr;
    filePtr = fopen(ARTISE_FILE, "rb");
    if(filePtr == NULL){
        printf("File could not be openend.");
    }else{
//        fseek(filePtr, sizeof(*artistePtr)*id-1, SEEK_END);
//        currentPosition = ftell(filePtr);
        while(!feof(filePtr)){
            count = fread(artistePtr, sizeof(*artistePtr), 1, filePtr);
            if(strcmp(artistePtr->stageName, stageName)== 0){
                match = 1;
                break;
            }
        }
    }
    fclose(filePtr);
    return match;
}

//finds the position in the file of a record. A the record does not yet exist in the file it will be positions at the end of the file
int findPositionInFile(int id){
    int count = 0, match = 0, read = 0;
    artiste artiste;
    FILE *filePtr;
    filePtr = fopen(ARTISE_FILE, "rb");
    if(filePtr == NULL){
        printf("File could not be openend.");
    }else{
//        fseek(filePtr, sizeof(*artistePtr)*id-1, SEEK_END);
//        currentPosition = ftell(filePtr);
        while(!feof(filePtr)){
            count = count + 1;
            read = fread(&artiste, sizeof(artiste), 1, filePtr);
            if(artiste.artisteId == id){
                break;
            }
        }
    }
    fclose(filePtr);
    return count;
}

// count the number of records in the artise file
int countArtiste(){
    struct Artiste artiste;
    int currentPosition = 0;
    int count = 0;
    FILE *filePtr;
    filePtr = fopen(ARTISE_FILE, "rb");
    if(filePtr == NULL){
        printf("File could not be openend.");
    }else{
        fseek(filePtr, 0, SEEK_END);
        currentPosition = ftell(filePtr);
        count = currentPosition/(sizeof(artiste));
    }
    fclose(filePtr);
    return count;
}

//gereates an id for an artiste by adding 1 to the last id in the file
int generateArtisteId(){
    struct Artiste artiste;
    int currentPosition = 0;
    int count = 0, id=1;
    FILE *filePtr;
    filePtr = fopen(ARTISE_FILE, "rb");
    if(filePtr == NULL){
        //printf("File could not be openend.");
    }else{
        count = fseek(filePtr, 0-(sizeof(artiste)), SEEK_END);

        if(count==0){
            fread(&artiste, sizeof(artiste),1,filePtr);
            id = artiste.artisteId + 1;
        }
    }
    fclose(filePtr);
    return id;
}

void enterPersonalInformation(artiste *artistePtr){
    artiste tempArtise;
    char tempStageName[50];
    int stageNameFound = 1;
    printf("artiste id: %d", artistePtr->artisteId);
    printf("Enter artiste Name Full: ");
    fflush(stdin);
    scanf("%[^\n]s", artistePtr->realName);
    while(stageNameFound){
    printf("Enter artiste stage name: ");
        fflush(stdin);
        scanf("%[^\n]s", tempStageName);
        stageNameFound = loadArtisteFromFileByName(&tempArtise, tempStageName);
        if(stageNameFound){
            printf("An artiste exists with that stage name");
        }
    }
    strcpy(artistePtr->stageName, tempStageName);

    printf("*******************************\nContact information\n*******************************\n");
    printf("Enter artiste contact number: ");
    fflush(stdin);
    scanf("%[^\n]s", artistePtr->telephone);
    printf("Enter artiste street address: ");
    fflush(stdin);
    scanf("%[^\n]s", artistePtr->address.street);
    printf("Enter artiste city: ");
    fflush(stdin);
    scanf("%[^\n]s", artistePtr->address.cityTown);
    printf("Enter artiste parish/state: ");
    fflush(stdin);
    scanf("%[^\n]s", artistePtr->address.parishState);
    printf("Enter artiste country: ");
    fflush(stdin);
    scanf("%[^\n]s", artistePtr->address.country);
}

void enterFoundationInformation(artiste *artistePtr){
    printf("Foundation name: ");
    fflush(stdin);
    scanf("%[^\n]s", artistePtr->foundation.name);
    printf("Major charity: ");
    fflush(stdin);
    scanf("%[^\n]s", artistePtr->foundation.majorCurCharity);
    printf("Foundation Bank Account Number: ");
    fflush(stdin);
    scanf("%d", &(artistePtr->foundation.fAccountNum));
    printf("Foundation Bank Account Balance: ");
    fflush(stdin);
    scanf("%f", &(artistePtr->foundation.balance));
}

void enterFinancialInformation(artiste *artistePtr){
    printf("Bank account Number: ");
    fflush(stdin);
    scanf("%d", &(artistePtr->accountNum));
    printf("Bank Account Balance: ");
    fflush(stdin);
    scanf("%f", &(artistePtr->accountBal));
    printf("Earnings per year: ");
    fflush(stdin);
    scanf("%f", &(artistePtr->earningPerYr));
}

//generates a report for an artiste report is saved to a text file in addition to being printed on the screen
void generateReport(){
    artiste artisteToReport;
    int artisteId = 0, artisteFound = 0, bookingsFound = 0;
    char filename[255];
    char report[510];
    char bookingsStr[100];
    FILE *filePtr;
    printf("*******************************\nEnter Artiste ID to generate a report\n*******************************\n Artiste ID: ");
    scanf("%d", &artisteId);

    artisteFound = loadArtisteFromFile(&artisteToReport, artisteId);
    if(artisteFound){
        sprintf(filename, "Booking-%d.dat", artisteId);
        bookingsFound = countBooking(filename);
        sprintf(report, "%s (%s) has yearly income of %.2f. \n The foundation (%s) which benefits %s has $ %.2f. ", artisteToReport.realName, artisteToReport.stageName, artisteToReport.earningPerYr, artisteToReport.foundation.name, artisteToReport.foundation.majorCurCharity, artisteToReport.foundation.balance);
        sprintf(bookingsStr, "\nThe artiste has %d open bookings.\n---------------------------------------------\n", bookingsFound);
    }
    system("cls");
    printf("\n*****************************************************\n%s\n---------------------------------------------", report);
    printf("%s", bookingsStr);
    sprintf(filename, "Report-%d-%s.txt", artisteId, artisteToReport.stageName);
    filePtr = fopen(filename, "w");
    if(filePtr != NULL){
        fprintf(filePtr, "%s", report);
        fprintf(filePtr, "%s", bookingsStr);
    }
    fclose(filePtr);
    system("pause");

}
