#include <stdio.h>
#include <stdlib.h>
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

int scan_user_file(char filename[], user_t *other_users)
{
    int num = 0; 

    FILE * readFile = fopen(filename, "r");
    if(readFile)
    {
        // Get num from first line in file
        fscanf(readFile, "%d", &num);

        // Go through text file creating structs and adding them to the array
        for(int i = 0; i < num; i++)
        {
           fscanf(readFile, "%s", other_users[i].name);
           fscanf(readFile, "%lf", &other_users[i].time);
           fscanf(readFile, "%lf", &other_users[i].latitude); 
           fscanf(readFile, "%lf", &other_users[i].longitude); 
           fscanf(readFile, "%lf", &other_users[i].altitude);
        }
    }
    fclose(readFile);
    return num; 
}

void printUsersToFile(char filename[], user_t other_users[], int num, user_t ourUser)
{
    FILE * userfile = fopen(filename, "w");
    if(userfile)
    {
        fprintf(userfile, "%d\n", (num+1));
        for(int i = 0; i < num; i++)
        {
            fprintf(userfile, "%s\n", other_users[i].name);
            fprintf(userfile, "%.0lf\n", other_users[i].time);
            fprintf(userfile, "%.2lf\n", other_users[i].latitude);
            fprintf(userfile, "%.2lf\n", other_users[i].longitude);
            fprintf(userfile, "%.2lf\n", other_users[i].altitude);
        }
        fprintf(userfile, "%s\n", ourUser.name);
        fprintf(userfile, "%.0lf\n", ourUser.time);
        fprintf(userfile, "%.2lf\n", ourUser.latitude);
        fprintf(userfile, "%.2lf\n", ourUser.longitude);
        fprintf(userfile, "%.2lf\n", ourUser.altitude);
    }
    fclose(userfile);
}

void scan_user(user_t *new_user)
{
    char name[25];
    double time;
    double latitude;
    double longitude;
    double altitude;

    // Get user input
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

    // Create struct from user input
    strcpy((*new_user).name, name);
    (*new_user).time = time;
    (*new_user).latitude = latitude;
    (*new_user).longitude = longitude;
    (*new_user).altitude = altitude;
}

void distance(user_t users[], int num, user_t ourUser)
{
    double lowestDistance = DBL_MAX;
    int closestUser = -1;
    printf("Distance from %s to ...\n", ourUser.name);
    for(int i = 0; i < num; i++)
    { 
        double new_distance = sqrt(pow((users[i].latitude - ourUser.latitude),2) + 
            pow((users[i].longitude - ourUser.longitude),2) + 
            pow((users[i].altitude - ourUser.altitude),2)); //Calc distance with formula
        printf("\t %s is %.2lfm\n", users[i].name, new_distance);
        if( new_distance <= lowestDistance )
        {
            lowestDistance = new_distance;
            closestUser = i;
        }
    }
    printf("\n*** The closest user to %s is %s ***\n\n", ourUser.name, users[closestUser].name);
}

int main(int argc, char **argv)
{
    int num = 0;
    user_t other_users[20]; 
    user_t our_user;

    num = scan_user_file(argv[1], other_users);
    // num = scan_user_file("users.txt", other_users);
    scan_user(&our_user);

    distance(other_users, num, our_user);

    printUsersToFile(argv[1], other_users, num, our_user);
    // printUsersToFile("newUsers.txt", other_users, num, our_user);
    // The newUsers text file was the test text file to see if the program was printing right, 
    // I'm keeping it just because
}