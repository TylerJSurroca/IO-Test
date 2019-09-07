#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_NAMELEN 32
#define MAX_PEOPLE 32
#define DEBUG 0

/////////
//Defines a person with a name, age, and location
/////////
struct person{
    char name[MAX_NAMELEN];
    int age;
    char location[MAX_NAMELEN];
};

////////
//Takes char filename and
//Opens file for writing
//Returns file pointer
////////
FILE * openFileForWrite(char filename[])
{
    FILE *fptr;

    fptr = fopen(filename,"w");

    if (fptr == NULL)
    {
        printf("Error writing file!\n");
        printf("Value of errno: %d\n", errno);
        exit(1);
    }

    return fptr;
}

////////
//Takes char filename and
//Opens file for reading
//Returns file pointer
////////
FILE* openFileForRead(char filename[])
{
    FILE* fptr;

    fptr = fopen(filename, "r");

    if(DEBUG == 1)printf("File starts too open.\n");

    if (fptr == NULL)
    {
        printf("Error reading file!\n");
        printf("Value of errno: %d\n", errno);
        exit(1);
    }

    return fptr;
}

////////
//Takes file pointer and closes file
////////
int closeFile(FILE *fptr)
{
    fclose(fptr);
    return 0;
}

////////
//Takes a file pointer and a personType structure
//Writes the size of a person when called
////////
int writeToFile(FILE *fptr, struct person personType)
{
    fwrite(&personType, sizeof(struct person), 1 , fptr);
    return 0;
}

////////
//Takes a file pointer and a personType structure
//Reads through an array of people
////////
int readFromFile(FILE* fptr, struct person personArray[])
{
    int i = 0;

    while(fread(&personArray[i], sizeof(struct person),1,fptr))
    {
        i++;
    }

    return i;
}

int main()
{
    char name[MAX_NAMELEN];
    int age;
    char location[MAX_NAMELEN];
    char filename[] = "C:\\Users\\Tyler\\Desktop\\IO name\\PeopleStorage.bin";
    char cont[] = "y";

    struct person personType;

    FILE *fptr;

    fptr = openFileForWrite(filename);

    while(cont[0] == 'y')
    {
        printf("Enter your name: \n");
        scanf("%s",&name);
        printf("\nEnter your age: \n");
        scanf("%d",&age);
        printf("\nEnter your location: \n");
        scanf("%s",&location);

        strcpy(personType.name,name);
        personType.age = age;
        strcpy(personType.location,location);

        writeToFile(fptr,personType);

        printf("Do you want to continue? \n");
        scanf("%s",&cont);
    }
    if(DEBUG == 1)printf("If this prints the while loop is broken\n");

    closeFile(fptr);

    if(DEBUG == 1)printf("File successfully closes\n");
    if(DEBUG == 1)printf("File successfully opens!");

    struct person readPeople[MAX_PEOPLE];
    int count;

    fptr = openFileForRead(filename);

    if(DEBUG == 1)printf("File opened correctly\n");

    count = readFromFile(fptr, readPeople);
    closeFile(fptr);

    if(DEBUG == 1)printf("The count is: %d",count);

    for(int i = 0; i < count; i++)
    {
        printf("\nName: %s.\nAge: %d.\nLocation: %s.\n\n", readPeople[i].name, readPeople[i].age, readPeople[i].location);
    }

    return 0;
}
