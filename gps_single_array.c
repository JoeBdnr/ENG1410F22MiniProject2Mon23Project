/*
    THIS PROGRAM IS NOT OUR FINAL PROGRAM
    IT WAS THE INITIAL PROGRAM WHICH ADDED THE USER STRUCT TO THE ARRAY OF STRUCTS
    IT DIDNT COMPARE THEM SEPRATELY
    GPS.C IS THE FILE WERE SUBMITTING
*/

#include <stdio.h>
#include <string.h>
#include <float.h>
#include <math.h>

typedef struct user
{
    char name[25];
    double time;
    double latitude;
    double longitude;
    double altitude;
    double distance;
} user_t;

user_t other_users[20];

int numUsers(char filename[], user_t *other_users)
{
    int num = 0; 

    FILE * readFile = fopen(filename, "r");
    if(readFile)
    {
        // read in number of records
        fscanf(readFile, "%d", &num);

        for(int i = 0; i < num; i++)
        {
           fscanf(readFile, "%s", other_users[i].name);
           //   printf("Reading user - %s\n", users[i].name);
           fscanf(readFile, "%lf", &other_users[i].time);
           fscanf(readFile, "%lf", &other_users[i].latitude); 
           fscanf(readFile, "%lf", &other_users[i].longitude); 
           fscanf(readFile, "%lf", &other_users[i].altitude);
        }
    }
    fclose(readFile);
    return num; 
}

void printUsersToFile(char filename[], user_t *other_users, int num)
{
    FILE * userfile = fopen(filename, "w");
    if(userfile)
    {
        fprintf(userfile, "%d\n", num);
        for(int i = 0; i < num; i++)
        {
            fprintf(userfile, "%s\n", other_users[i].name);
            fprintf(userfile, "%.0lf\n", other_users[i].time);
            fprintf(userfile, "%.2lf\n", other_users[i].latitude); 
            fprintf(userfile, "%.2lf\n", other_users[i].longitude); 
            fprintf(userfile, "%.2lf\n", other_users[i].altitude);         
            fprintf(userfile, "%.2lf", other_users[i].distance);         
        }
    }
    fclose(userfile);
}

void addUser(user_t *users, int *n)
{
    char name[25];
    double time;
    double latitude;
    double longitude;
    double altitude;

    printf("Enter your name: ");
    scanf(" %s", &name);
    printf("Enter your time: ");
    scanf(" %lf", &time);
    printf("Enter your latitude: ");
    scanf(" %lf", &latitude);
    printf("Enter your longitude: ");
    scanf(" %lf", &longitude);
    printf("Enter your altitude: ");
    scanf(" %lf", &altitude);

    strcpy(users[*n].name, name);
    users[*n].time = time;
    users[*n].latitude = latitude;
    users[*n].longitude = longitude;
    users[*n].altitude = altitude;
    *n = *n + 1;
}

int distance(user_t *users, int num, int ourUser)
{
    double lowestDistance = DBL_MAX;
    int closestUser = -1;
    for(int i = 0; i < num; i++)
    {
        if(i != ourUser)
        {
            users[i].distance = sqrt(pow((users[i].latitude - users[ourUser].latitude),2) + pow((users[i].longitude - users[ourUser].longitude),2) + pow((users[i].altitude - users[ourUser].altitude),2)); //Calc distance
            if( users[i].distance <= lowestDistance )
            {
                lowestDistance = users[i].distance;
                closestUser = i;
            }
        }
    }
    return closestUser;
}

int main(void)
{
    int num = 0;
    int closestUser = -1;
    int our_user = -1;

    num = numUsers("users.txt", other_users);
    addUser(other_users, &num);

    our_user = num - 1;
    closestUser = distance(other_users, num, our_user);

    printf("The closest person to %s is %s\n", other_users[our_user].name, other_users[closestUser].name);
    printf("They are %.02lfm apart\n", other_users[closestUser].distance);

    printUsersToFile("newUsers.txt", other_users, num);
}