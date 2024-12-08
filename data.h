/* check if the file has already been included to ensure it is only included once. This helps to save memory, also the program won't
compile because by defining the variable twice, you'd be redefining the variables. */
#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED
#define ARTISE_FILE "Artiste.dat"
#define USER_FILE "Bookings"
#define USER_FILE "User.dat"
#include <time.h>

typedef struct User{
    char Username[50];
    char password[50];
    char usertype;
    int UserId;
    int loginAttempts;

} user;

typedef struct ArtisteFoundation {
    int fAccountNum;
    float balance;
    char majorCurCharity [200];
    char name[200];
} foundation;

typedef struct Address {
    char street[100];
    char cityTown[100];
    char parishState[100];
    char country[100];
} address;

typedef struct Artiste{
    int artisteId;
    char realName[50];
    char stageName[50];
    int accountNum;
    float accountBal;
    float earningPerYr;
    char telephone[12];
    address address;
    foundation foundation;
} artiste;

typedef struct ArtisteBooking{
    int bookingNum;
    char type;// - (O)versea or (L)ocal -
    struct tm date;// counld be struct
    char voluntary;
    char hotel[100];
    float travelCost;
    int teamSize;
    address location;
    char guide[100];
    char flightInfo[100];
    float showRateLocal;
    float showRateForeign;
    char tour[100];
} booking;

typedef struct Date{
    short day;
    short month;
    short year;
    short hour;
    short minute;
} date;


#endif // DATA_H_INCLUDED
