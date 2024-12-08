#include <stdio.h>
#include <stdlib.h>
#include "data.h"
//store logged  users data
extern char USER_NAME[50];
extern char USER_TYPE;

// get the user type of logged in user
char getUserType(){
    return USER_TYPE;
}
//get username of loggein user
char getUserName(){
    return USER_NAME;
}

// logs a user into the system
int login(){
    int BLOCK_LOGINS = 0;
    char username[50], password[50];
    int loggedIn = 0, userFound = 0, i=0;
    while(!BLOCK_LOGINS){
        user userL;

        //system("cls");
        printf("************************************\n-----------ARTISTE BOOKER-----------\n");
        printf("************************************\nUSER LOGIN\n*************************************\n");
        printf("Enter username: ");
        fflush(stdin);
        scanf("%s", username);
        printf("Enter password: ");
        fflush(stdin);
        scanf("%s", password);
        userFound = loadUserFromFileByUsername(&userL, username);
        if(userFound){
            if(userL.loginAttempts > 2){
                BLOCK_LOGINS = 1;
                printf("you have exceeded the number of login attempts. Contact administrator.");
                break;
            }
            //if the password entered is the correct password then they'll be accepted in the system
            //the "saveUser()" will be called and and it'll be written and updated to the file
            if(strcmp(userL.password,password)==0){
                loggedIn =1;
                strcpy(USER_NAME,userL.Username);
                USER_TYPE = userL.usertype;
                userL.loginAttempts = 0;
                saveUser(&userL, "rb+");
                printf("\nLogin Successfull\n***********************************\n");
                break;
                //else their attempts will be added to "loginAttempts"
                //a message letting them know the name or password is incorrect will be displayed
                //and its written and updated to the file
            }else{
                //printf("%d", userL.loginAttempts);
                userL.loginAttempts = (userL.loginAttempts+1);
                //printf("%d", userL.loginAttempts);
                printf("\nUser name or password incorrect.\n");
                //system("pause");
                saveUser(&userL, "rb+");
            }
        }else{
            printf("\nUser name or password incorrect\n");
        }
    }
    system("pause");

    return loggedIn;
}

//Adds a new user
void addUser(){
    user user;
    system("cls");

    user. UserId = generateUserId();
    printf("The new user will be assigned user Id: %d",  user.UserId);
    //    printf("position: %d \n",findUserPositionInFile( user.UserId));
    printf("*******************************\nEnter new user information\n*******************************\n");
    printf("Enter username: ");
    fflush(stdin);
    scanf("%s", user.Username);
    printf("Enter password: ");
    fflush(stdin);scanf("%s", user.password);
    printf("Enter usertype - C for clerk or A for admin - incorrect type will default to clerk: ");
    fflush(stdin);
    scanf("%c",  &user.usertype);
    //if the user type is not admin then it assumes clerk
    if(user.usertype != 'A' && user.usertype != 'a'){
        user.usertype = 'C';
    }
    user.loginAttempts = 0;
    printf("\n%d user(s) saved to database\n", saveUser(&user, "ab+"));
    printf("\n%d userstored in database\n", countUser());
    system("pause");

}

//Update a users information
void updateUser(){
    int userId;
    user userToUpdate;
    int usersFound = 0;
    system("cls");
    int position = 1;

    printf("*******************************\nEnter userid to update information\n*******************************\n User id: ");
    scanf("%d", &userId);

    usersFound = loadUserFromFile(&userToUpdate, userId);
    if(usersFound ){
        printf("Enter username: ");
        fflush(stdin);
        scanf("%s",  userToUpdate.Username);
        printf("Enter password: ");
        fflush(stdin);
        scanf("%s",  userToUpdate.password);
        printf("Enter usertype - C for clerk or A for admin - incorrect type will default to clerk: ");
        fflush(stdin);
        scanf("%c",  &userToUpdate.usertype);
        if(userToUpdate.usertype != 'A' && userToUpdate.usertype != 'a'){
            userToUpdate.usertype = 'C';
        }
        userToUpdate.loginAttempts = 0;
        printf("\n%d user(s) saved to database\n", saveUser(&userToUpdate, "rb+"));
        printf("\n%d userstored in database\n", countUser());
    }else{
        printf("\nUser not found\n");
    }
    system("pause");

}

//Release the login block on a user
// if a users has tried to login three times and failed the user will be blocked from logging in
// this function allows an admin to release that lock by resetting the failed login count to 0
void unblockUser(){
    int userId;
    user userToUpdate;
    int usersFound = 0;
    system("cls");
    int position = 1;

    printf("*******************************\nEnter userid to unblock \n*******************************\n User id: ");
    scanf("%d", &userId);

    usersFound = loadUserFromFile(&userToUpdate, userId);
    if(usersFound ){
        userToUpdate.loginAttempts = 0;
        printf("\n%d user(s) saved to database\n", saveUser(&userToUpdate, "rb+"));
        printf("\n%d User(s) stored in database\n", countUser());
    }else{
        printf("\nUser not found.\n");
    }
    system("pause");

}

//save a user to the file
int saveUser(user *userPtr, char mode[]){
    int written = 0, position = 0;
    FILE *filePtr;
    filePtr = fopen(USER_FILE, mode);
    if(filePtr == NULL){
        printf("User dattabase could not be opened.");
    }else{
        position = findUserPositionInFile(userPtr->UserId);
        fseek(filePtr, sizeof(*userPtr)*(position-1), SEEK_SET);
        written = fwrite(userPtr, sizeof(*userPtr), 1, filePtr);
        //printf("\nsaving ...%d\n", written);
    }

    fclose(filePtr);
    return written;
}

//allows a user to view a users data
void viewUser(){
    int userId;
    artiste userToView;
    int userFound = 0;
    system("cls");

    printf("*******************************\nEnter user id to view information\n*******************************\n Artiste id: ");
    fflush(stdin);
    scanf("%d", &userId);

    userFound = loadUserFromFile(&userToView, userId);
    if(userFound ){
        printUser(&userToView);
    }
    system("pause");

}
//print a list of users
void viewUserList(){
    int count = 1, found = 0;
    user userFound;
    FILE *filePtr;
    filePtr = fopen(USER_FILE, "rb");
    if(filePtr == NULL){
        printf("File could not be opened.");
    }else{
//        fseek(filePtr, sizeof(*artistePtr)*id-1, SEEK_END);
//        currentPosition = ftell(filePtr);
        while(!feof(filePtr)){
            found = fread(&userFound, sizeof(userFound), 1, filePtr);
            if(found){
                printf("\n******************************************\nID#: %3d", userFound.UserId);
                printf("\nUser Name: %s", userFound.Username);
                printf("\nUser type: %c", userFound.usertype);
                printf("\n------------------------------------------\n");
                count++;
            }
        }
    }
    fclose(filePtr);
    system("pause");

    return count;
}

//prints a users data
void printUser(user *userPtr){
    printf("\n******************************************\nID#: %3d", userPtr->UserId);
    printf("\nUser Name: %s", userPtr->Username);
    printf("\nUser type: %c", userPtr->usertype);
    printf("\nFail Login Attempts: %d", userPtr->loginAttempts);
    printf("\n------------------------------------------\n");

}

//allows a user to be deleted
int deleteUser(){
    int userId, found = 0, written = 0;
    user userToDelete;
    int userFound = 0;
    char filename[255];
    int position = 1;
    FILE *filePtr;
    FILE *tempFilePtr;
    system("cls");

    printf("*******************************\nEnter User Id to delete a user\n*******************************\n User Id: ");
    scanf("%d", &userId);
    filePtr = fopen(USER_FILE, "rb");
    if(filePtr == NULL){
        printf("File could not be opened.");
        return -1;
    }
    tempFilePtr = fopen("tempUser.bin", "wb");
    if(tempFilePtr == NULL){
        printf("File could not be opened.");
        return -1;
    }
    while(!feof(filePtr)){
        found = fread(&userToDelete, sizeof(userToDelete), 1, filePtr);
        if(found && userToDelete.UserId == userId){
            printf("User deleted");
        }else if(found){
            written = fwrite(&userToDelete, sizeof(userToDelete), 1, tempFilePtr);
        }
    }

    fclose(filePtr);
    fclose(tempFilePtr);

    int ret = remove(USER_FILE);

    if(ret == 0) {
        printf("Delete finished successfully");
    } else {
        printf("Unable to finalise delete. Contact admin");
    }
   rename("tempUser.bin", USER_FILE);
   system("pause");

}

//loads a user's data from the file store
int loadUserFromFile(user *userPtr, int id){
    int count = 0, match = 0;
    int fileExists = 0;
    FILE *filePtr;
    filePtr = fopen(USER_FILE, "rb");
    if(filePtr == NULL){
        printf("User database could not be openend.\n");
    }else{
//        fseek(filePtr, sizeof(*artistePtr)*id-1, SEEK_END);
//        currentPosition = ftell(filePtr);
        fileExists = 1;
        while(!feof(filePtr)){
            count = fread(userPtr, sizeof(*userPtr), 1, filePtr);
            if(userPtr->UserId == id){
                match = 1;
                break;
            }
        }
    }
    fclose(filePtr);

    return match;
}

//loads user data using username
int loadUserFromFileByUsername(user *userPtr, char username[]){
    int count = 0, match = 0;
    int fileExists = 0;
    FILE *filePtr;
    filePtr = fopen(USER_FILE, "rb");
    if(filePtr == NULL){
        printf("User database could not be openend.\n");
        //create default admin user if file did not exist
        createDefaultUser(userPtr);

    }else{
//        fseek(filePtr, sizeof(*artistePtr)*id-1, SEEK_END);
//        currentPosition = ftell(filePtr);
        while(!feof(filePtr)){
            count = fread(userPtr, sizeof(*userPtr), 1, filePtr);
            if(strcmp(userPtr->Username,username)==0){
                //printf("\n%d\n", userPtr->loginAttempts);
                match = 1;
                break;
            }
        }
    }
    fclose(filePtr);

    return match;
}

//finds the position of the next record in file
int findUserPositionInFile(int id){
    int count = 0, match = 0, read = 0;
    user user;
    FILE *filePtr;
    filePtr = fopen(USER_FILE, "rb");
    if(filePtr == NULL){
        //printf("File could not be openend.");
    }else{
//        fseek(filePtr, sizeof(*artistePtr)*id-1, SEEK_END);
//        currentPosition = ftell(filePtr);
        while(!feof(filePtr)){
            count = count + 1;
            read = fread(&user, sizeof(user), 1, filePtr);
            if(user.UserId == id){
                break;
            }
        }
    }
    fclose(filePtr);
    return count;
}

//finds the number of users in the file
int countUser(){
    user user;
    int currentPosition = 0;
    int count = 0;
    FILE *filePtr;
    filePtr = fopen(USER_FILE, "rb");
    if(filePtr == NULL){
        printf("User database could not be opened.");
    }else{
        fseek(filePtr, 0, SEEK_END);
        currentPosition = ftell(filePtr);
        count = currentPosition/(sizeof(user));
    }
    fclose(filePtr);
    return count;
}

//generates a user id by adding 1 to the last record in the file
int generateUserId(){
    user user;
    int currentPosition = 0;
    int count = 0, id=1;
    FILE *filePtr;
    filePtr = fopen(USER_FILE, "rb");
    if(filePtr == NULL){
        //printf("File could not be openend.");
    }else{
        count = fseek(filePtr, 0-(sizeof(user)), SEEK_END);

        if(count==0){
            fread(&user, sizeof(user),1,filePtr);
            id = user.UserId + 1;
        }
    }
    fclose(filePtr);
    return id;
}
//inserts the default admin into the database with a username of 'Matthews' and a password of 'PassMat1'
void createDefaultUser(user *userPtr){
    strcpy(userPtr->Username, "Matthews");
    strcpy(userPtr->password, "PassMat1");
    userPtr->UserId = 1;
    userPtr->usertype = 'A';
    userPtr->loginAttempts = 0;

    saveUser(userPtr, "ab+");
}
