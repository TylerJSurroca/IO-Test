#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#pragma warning(disable : 4996)
#pragma warning(disable : 4700)

#define MAX_NAMELEN 32
#define MAX_PEOPLE 32

struct person {
	char name[MAX_NAMELEN];
	int age;
	char location[MAX_NAMELEN];
};

//////// WARNING: HACKY //////////////////////////////////////////////////////////////////
const int DEBUG = 0; // GLOBAL DEBUG FLAG, SET TO 1 TO SEE OUTPUT, 0 TO MUTE OUTPUT 
//////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////
// Parameters
// char filenamd[] -> a path to a file location to open
// Returns
// FILE* fptr -> A pointer to a previously opened for WRITE file
//////////////////////////////////////////////////////////////////////////////////////////
FILE* openFileForWrite(char filename[])
{
	FILE* fptr;

	fptr = fopen(filename, "w");

	if (fptr == NULL)
	{
		printf("Error writing file!\n");
		printf("Value of errno: %d\n", errno);
		exit(1);
	}

	return fptr;
}

//////////////////////////////////////////////////////////////////////////////////////////
// Parameters
// char filenamd[] -> a path to a file location to open
// Returns
// FILE* fptr -> A pointer to a previously opened for READ file
//////////////////////////////////////////////////////////////////////////////////////////
FILE* openFileForRead(char filename[])
{
	FILE* fptr;

	fptr = fopen(filename, "r");

	if (DEBUG == 1) printf("DEBUG: File starts too open.\n");

	if (fptr == NULL)
	{
		printf("Error reading file!\n");
		printf("Value of errno: %d\n", errno);
		exit(1);
	}

	return fptr;
}

//////////////////////////////////////////////////////////////////////////////////////////
// Parameters
// FILE* fptr -> a previously open for READ or WRITE file pointer
// Returns
// Just returns value from fclose
//////////////////////////////////////////////////////////////////////////////////////////
int closeFile(FILE* fptr)
{
	return fclose(fptr);	
}

//////////////////////////////////////////////////////////////////////////////////////////
// Parameters
// FILE* fptr -> a previously open for WRITE file pointer
// struct person personType -> a previously allocated person to write to the file
// Returns
// Just returns value from fwrite
//////////////////////////////////////////////////////////////////////////////////////////
int writeToFile(FILE* fptr, struct person personType)
{
	return fwrite(&personType, sizeof(struct person), 1, fptr);
}

//////////////////////////////////////////////////////////////////////////////////////////
// Parameters
// struct person personArray[] -> An array of persons, must be initialized before passing in
// FILE* fptr -> A pointer to a previously opened for read file
//////////////////////////////////////////////////////////////////////////////////////////
int readFromFile(FILE* fptr /* Notice how fptr is passed in as a parameter */, 
				 struct person personArray[])
{
	///// ERROR /////////// ERROR /////////// ERROR /////////// ERROR /////////// ERROR ////////
	// This is the problem here
	// You have an uninitialized fptr declared in this function
	// Instead, you need to pass fptr as a parameter to this function like as demonstrated above
	// FILE* fptr; <<<<<------ BAD CODE
	///// ERROR /////////// ERROR /////////// ERROR /////////// ERROR /////////// ERROR ////////

	int i = 0;

	while (fread(&personArray[i], sizeof(struct person), 1, fptr))
	{
		i++;
	}

	fclose(fptr);

	return i;
}

int main()
{
	char name[MAX_NAMELEN];
	int age;
	char location[MAX_NAMELEN];
	char filename[] = "PeopleStorage.bin";
	// char cont = 'y'; // This was causing a memory corruption error.
	// Better to just allocate a string like before
	char cont[] = "y"; // Strings in C are NULL terminated so, even a 1 char string actually has 2 chars ex: ['y'][\0]
	// Read this article for more info
	// https://www.tutorialspoint.com/cprogramming/c_strings.htm#targetText=C%20%2D%20Strings&targetText=Strings%20are%20actually%20one%2Ddimensional,of%20the%20word%20%22Hello%22.

	struct person personType;

	FILE* fptr;

	fptr = openFileForWrite(filename);

	while (cont[0] == 'y') 
	{
		printf("Enter your name: \n");
		scanf("%s", &name);
		printf("Enter your age: \n");
		scanf("%d", &age);
		printf("Enter your location: \n");
		scanf("%s", &location);

		strcpy(personType.name, name);
		personType.age = age;
		strcpy(personType.location, location);

		writeToFile(fptr, personType);

		printf("Do you want to continue? \n");
		scanf("%s", &cont);
	}

	if (DEBUG == 1) printf("DEBUG: If this prints the while loop is broken\n");

	closeFile(fptr);

	if (DEBUG == 1) printf("DEBUG: File successfully closes\n");

	struct person readPeople[MAX_PEOPLE];
	int count; // This is going to hold the number of people read in, you need to capture from readFromFile
		
	// Begin reading file
	fptr = openFileForRead(filename);
	// fptr = fopen(filename, "r"); // There is no problem with the openFileForRead function above
	if (DEBUG == 1) printf("DEBUG: File opened correctly\n");
	count = readFromFile(fptr, /* Here, we are passing in the fptr we opened above */
				 readPeople);
	// Close the file immediately after using it. I found this at the end of the file
	closeFile(fptr);


	if (DEBUG == 1) printf("DEBUG: File successfully opens!\n");

	printf("The number of people read from file is: %d\n", count);

	printf("/////// Dump the people read: %d ///////////////////\n", count);
	for (int i = 0; i < count; i++)
	{
		/// NOTE: Always do you \n at the end of a printf. You should almost never see one at the beginning
		/// NOTE: If you see one at the beginning, there is one unbalanced somewhere so you'll have to inspect 
		/// NOTE: all of your printfs
		printf("-------------------- Person #%d --------------------\n", i+1);
		printf("Name: %s.\nAge: %d.\nLocation: %s.\n\n", readPeople[i].name, readPeople[i].age, readPeople[i].location);	
		printf("----------------------------------------------------\n");
	}

	return 0;
}
