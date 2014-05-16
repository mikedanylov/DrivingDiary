// m_danylov

#include "trip.h"

#define EXIT 6

int main(){

	// initializing variables-------------------------------------------------
	drivingDiary diary[MAX]; // array of trip records
	int option = 0; // application menu choise option
	int tripToRead = 0; // stores number of line we need to read
	int tripsNumber = 0; // number of lines in the file
	int tripToRemove = 0; // number of line to remove
	char input = ' '; // stores char which was read from console
	FILE* file = NULL; // innitializing file
	/* create new file each time application starts---------
	//add if needed-----------------------------------------
	file = fopen("test.txt", "w");
	fclose(file);*/
	// initializing diary array and other variables---------------------------
	for (int i = 0; i < MAX; i++)
		initialize(&diary[i]);
	printf("\nWELCOME TO DRIVING DIARY!\n\n");
	// save number of existing trips from file---------------------------------
	tripsNumber = linesNumber(file);
	// scan file if such exists and write data to diary array
	readFileToDiary(file, diary);
	// display menu until correct selection is made----------------------------
	while (option != EXIT){
		printf("\n1. Add a new trip\n");
		printf("2. Read all trip data from disk\n");
		printf("3. Read single trip data from disk\n");
		printf("4. Remove a trip\n");
		printf("5. Print a report\n");
		printf("6. Exit\n");
		printf("\nMake your choice: ");
		// get input as one character and check for integer--------------------
		fflush(stdin);
		input = getche();
		if (isdigit(input))
			option = input - 48;
		switch (option){// action chooser--------------------------------------
			case 1:
				tripsNumber++;
				addTrip(&diary[tripsNumber]); // + input error checking
				saveTrip(file, diary[tripsNumber]);
				break;
			case 2:// read all trip data at once-------------------------------
				readAllTrips(file);
				break;
			case 3:// read selected trip from file-----------------------------
				tripsNumber = linesNumber(file); // get current number of trips
				if (tripsNumber > 1){
					printf("\nThere are %d trips. Chose number to read: ", tripsNumber);
					scanf("%d", &tripToRead);
					readOneTrip(file, tripToRead);
				}
				else if (tripsNumber == 1){
					printf("\nThere is only %d trip.\n");
					tripToRead = 1;
					readOneTrip(file, tripToRead);
				}
				else
					printf("\nNo trips data to read...\n");
				break;
			case 4:// remove trip from file------------------------------------
				tripsNumber = linesNumber(file); // get current number of trips
				if (tripsNumber > 0){
					printf("\nThere are %d trips. Chose number to remove: ", tripsNumber);
					scanf("%d", &tripToRemove);
					if (tripToRemove <= tripsNumber)
						removeTrip(file, diary, tripToRemove, tripsNumber);
					else
						printf("\nNo such trip to remove...\n");
				}
				else
					printf("\nNo trips data to read...\n");
				break;
			case 5://print a report--------------------------------------------
				readFileToDiary(file, diary);
				printReport(diary, tripsNumber);
				break;
			case 6:// exit-----------------------------------------------------
				printf("\n");
				break;
			default:// display menu again--------------------------------------
				printf("\nPlease input numbers from 1 to 6\n\n");
				break;
		}
	}
	for (int i = 0; i <= tripsNumber; i++)
		cleanDiary(&diary[i]);
	return 0;
}
