#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libgen.h>

struct user_t
{
    char name[25];
    double time;
    double latitude;
    double longitude;
    double altitude;
};

void addUser(struct user_t *src, int *n)
{
    char name[25];
    double time;
    double latitude;
    double longitude;
    double altitude;

    printf("Enter your name: ");
    scanf(" %s", &name);
    printf("Enter your time: ");
    scanf(" %lf", &time); //Don't think this is right 
    printf("Enter your latitude: ");
    scanf(" %lf", &latitude);
    printf("Enter your longitude: ");
    scanf(" %lf", &longitude);
    printf("Enter your altitude: ");
    scanf(" %lf", &altitude);

    struct user_t thisUser;
    strcpy(thisUser.name, name);
    thisUser.time = time;
    thisUser.latitude = latitude;
    thisUser.longitude = longitude;
    thisUser.altitude = altitude;

    src[*n] = thisUser;
    *n = *n + 1;
}

// int distance()
// {

// }

struct user_t users[20];

int main(void)
{
    int num = 0;
    printf("Currently %d users\n", num);
    addUser(users, &num);
    printf("Now %d users\n", num);
    addUser(users, &num);
    printf("Now %d users\n", num);
}