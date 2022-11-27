#include <stdio.h>
#include <string.h>
#include <float.h>
#include <math.h>

typedef struct user //Why this?
{
    char name[25];
    double time;
    double latitude;
    double longitude;
    double altitude;
    double distance;
} user_t;

user_t other_users[20];

int numUsers(char filename[], user_t *users)
{
    int num = 0; //How does this 0

    FILE * readFile = fopen(filename, "r");
    if(readFile)
    {
        // read in number of records
        fscanf(readFile, "%d", &num);

        for(int i = 0; i < num; i++)
        {
           fscanf(readFile, "%s", users[i].name);
           //   printf("Reading user - %s\n", users[i].name);
           fscanf(readFile, "%lf", &users[i].time);
           fscanf(readFile, "%lf", &users[i].latitude); 
           fscanf(readFile, "%lf", &users[i].longitude); 
           fscanf(readFile, "%lf", &users[i].altitude);
        }
    }
    fclose(readFile);
    return num; //Change to number of users
}

void printUsersToFile(char filename[], user_t *users, int num)
{
    FILE * userfile = fopen(filename, "w");
    if(userfile)
    {
        fprintf(userfile, "%d\n", num);
        for(int i = 0; i < num; i++)
        {
            fprintf(userfile, "%s\n", users[i].name);
            fprintf(userfile, "%.0lf\n", users[i].time);
            fprintf(userfile, "%.2lf\n", users[i].latitude); 
            fprintf(userfile, "%.2lf\n", users[i].longitude); 
            fprintf(userfile, "%.2lf\n", users[i].altitude);         
            fprintf(userfile, "%.2lf", users[i].distance);         
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
    int thisUser = -1;

    num = numUsers("users.txt", other_users);
    addUser(other_users, &num);

    thisUser = num - 1;
    closestUser = distance(other_users, num, thisUser);

    printf("The closest person to %s is %s\n", other_users[thisUser].name, other_users[closestUser].name);
    printf("They are %.02lfm apart\n", other_users[closestUser].distance);

    printUsersToFile("newUsers.txt", other_users, num);
}