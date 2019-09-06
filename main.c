#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_NAMELEN 32
#define MAX_PEOPLE 32

struct person{
    char name[MAX_NAMELEN];
    int age;
    char location[MAX_NAMELEN];
};
/*
int writeToFile(char name[MAX_NAMELEN])
{
    FILE *fptr;

    fptr = fopen("C:\\Users\\Tyler\\Desktop\\IO name\\PeopleStorage.txt","w");

    if (fptr == NULL)
    {
        printf("Error!");
        exit(1);
    }

    struct person input1 = {"Tyler",19,"Longwood"};
    struct person input2 = {"Francisco",49,"Longwood"};

    fwrite (&input1, sizeof(struct person),1,fptr);
    fwrite (&input2, sizeof(struct person),1,fptr);

    fclose(fptr);
}
*/

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

FILE * openFileForRead(char filename[])
{
    FILE *fptr;

    fptr = fopen(filename,"r");

    printf("File starts too open.\n");

    if (fptr == NULL)
    {
        printf("Error reading file!\n");
        printf("Value of errno: %d\n", errno);
        exit(1);
    }

    return fptr;
}


int closeFile(FILE *fptr)
{
    fclose(fptr);
    return 0;
}

int writeToFile(FILE *fptr, struct person personType)
{
    fwrite(&personType, sizeof(struct person), 1 , fptr);
    return 0;
}

/*
int readFromFile(char name[MAX_NAMELEN])
{
    FILE *fptr;

    fptr = fopen("C:\\Users\\Tyler\\Desktop\\IO name\\PeopleStorage.txt","r");

    if (fptr == NULL)
    {
        printf("ERROR could not open file!");
        exit(1);
    }

    fscanf(fptr,"%s",name);

    return 0;

}
*/

//personArray must be initialized before passing in
int readFromFile(struct person personArray[])
{
    FILE *fptr;

    int i = 0;

    while(fread(&personArray[i], sizeof(struct person),1,fptr))
    {
        i++;
    }

    fclose(fptr);

    return i;
}

int main()
{
    /*
    char name[MAX_NAMELEN];

    printf("What is your name?\n");
    scanf("%s",name);

    writeToFile(name);

    readFromFile(name);
    printf("Your name is: %s",name);
    */

    char name[MAX_NAMELEN];
    int age;
    char location[MAX_NAMELEN];
    char filename[] = "C:\\Users\\Tyler\\Desktop\\IO name\\PeopleStorage.bin";
    char cont = 'y';

    struct person personType;

    FILE *fptr;

    fptr = openFileForWrite(filename);

    while(cont == 'y')
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
    printf("\nIf this prints the while loop is broken\n");

    closeFile(fptr);

    printf("\nFile successfully closes\n");

    //Begin reading file
    //fptr = openFileForRead(filename);
    fptr = fopen(filename,"r");

    printf("\nFile successfully opens!");

    struct person readPeople[MAX_PEOPLE];
    int count;

    printf("\n\nFile opened correctly");

    readFromFile(readPeople);

    printf("The count is: %d",count);

    for(int i = 0; i < count; i++)
    {
        printf("\nName: %s.\nAge: %d.\nLocation: %s.\n\n", readPeople[i].name, readPeople[i].age, readPeople[i].location);
    }

    closeFile(fptr);


    /*
    struct person input1 = {"Tyler" , 19 , "Longwood"};
    struct person input2 = {"Francisco" , 49 , "Longwood"};
    struct person input3 = {"Trevor" , 25 , "Lakeland"};

    fwrite (&input1, sizeof(struct person),1,fptr);
    fwrite (&input2, sizeof(struct person),1,fptr);
    fwrite (&input3, sizeof(struct person),1,fptr);
    */


    return 0;
}
