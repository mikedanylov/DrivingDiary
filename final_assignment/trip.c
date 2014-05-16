#include "trip.h"

void initialize(drivingDiary* d){
	d->locationStart = (char*)calloc(NAME_MAX, sizeof(char));
	d->locationEnd = (char*)calloc(NAME_MAX, sizeof(char));;
	d->timeStart = (char*)malloc(TIME_MAX * sizeof(char));;
	d->timeEnd = (char*)malloc(TIME_MAX * sizeof(char));;
	d->odometerStart = 0;
	d->odometerEnd = 0;
}
void addTrip(drivingDiary* d){

	// start location input-------------------------------
	fflush(stdin);// clear stdin
	printf("\nInput start location: ");
	scanf("%[^\n]s", d->locationStart);
	while (!isalpha(d->locationStart[0])){
		fflush(stdin);// clear stdin
		printf("Location name should start with a letter...\n");
		printf("Please, input start location again: ");
		scanf("%[^\n]s", d->locationStart);
	}
	// start time input and error checking----------------
	printf("Input start time (hh:mm): ");
	scanf("%s", d->timeStart);
	while (	!isdigit(d->timeStart[0]) ||
			!isdigit(d->timeStart[1]) ||
			d->timeStart[2] != ':'    ||
			!isdigit(d->timeStart[3]) ||
			!isdigit(d->timeStart[4])){
		fflush(stdin);// clear stdin
		printf("Please, input time in (hh:mm) format: ");
		scanf("%s", d->timeStart);
	}
	// start odometer input and error checking------------
	d->odometerStart = odometerInput("Odometer value before the trip (0 - 99999): ");
	// end location input---------------------------------
	fflush(stdin);// clear stdin
	printf("\nInput end location: ");
	scanf("%[^\n]s", d->locationEnd);
	while (!isalpha(d->locationEnd[0])){
		fflush(stdin);// clear stdin
		printf("Location name should start with a letter...\n");
		printf("Please, input end location again: ");
		scanf("%[^\n]s", d->locationEnd);
	}
	// end time input and error checking------------------
	printf("Input end time (hh:mm): ");
	scanf("%s", d->timeEnd);
	while (!isdigit(d->timeEnd[0]) ||
		!isdigit(d->timeEnd[1]) ||
		d->timeEnd[2] != ':' ||
		!isdigit(d->timeEnd[3]) ||
		!isdigit(d->timeEnd[4])){
		fflush(stdin);// clear stdin
		printf("Please, input time in (hh:mm) format: ");
		scanf("%s", d->timeEnd);
	}
	// end odometer input and error checking--------------
	d->odometerEnd = odometerInput("Odometer value after the trip (0 - 99999): ");
}
void saveTrip(FILE* outfile, drivingDiary d){

	outfile = fopen("test.txt", "a");
	if (outfile == NULL) {
		printf("\nError saving to file!\n");
	}
	else{
		fprintf(outfile, "%s ", d.locationStart);
		fprintf(outfile, "%s ", d.timeStart);
		fprintf(outfile, "%d ", d.odometerStart);
		fprintf(outfile, "%s ", d.locationEnd);
		fprintf(outfile, "%s ", d.timeEnd);
		fprintf(outfile, "%d\n", d.odometerEnd);
		fclose(outfile);
	}
}
void readAllTrips(FILE* outfile){

	char tmpStr[MAX] = "";

	outfile = fopen("test.txt", "r");
	if (outfile == NULL)
		printf("\nError opening file!\n");
	else{
		printf("\nReading driving diary...\n");
		while (!feof(outfile)){
			if (fgets(tmpStr, MAX, outfile) != NULL){
				printf("%s", tmpStr);
			}
		}
		fclose(outfile);
	}
}
void readOneTrip(FILE* outfile, int lineToDisplay){

	char tmpStr[MAX] = "";
	int counter = 1; // counting trips starts from 1
	int numOfRecords = linesNumber(outfile);

	// display next line after each f call---------------------
	outfile = fopen("test.txt", "r");
	if (outfile == NULL)
		printf("\nError opening file!\n");
	else{
		while (!feof(outfile)){
			if (fgets(tmpStr, MAX, outfile) != NULL
				&& counter == lineToDisplay){
				printf("\n%s", tmpStr);
			}
			counter++;
		}
		// display message if no lines left--------------------
		if (lineToDisplay > numOfRecords)
			printf("\nNo such trip data to display\n");
	}
	
	fclose(outfile);
}
int linesNumber(FILE* file){

	char tmpStr[MAX] = "";
	int numOfRecords = 0;

	// counting number of lines------------------------------------
	file = fopen("test.txt", "r");
	if (file == NULL)
		printf("\nError opening file!\n");
	else{
		//printf("Counting trips from driving diary...\n");
		while (!feof(file)){
			if (fgets(tmpStr, MAX, file) != NULL)
				numOfRecords++;
		}
		fclose(file);
	}
	return numOfRecords;
}
void removeTrip(FILE* file, drivingDiary* diary, int tripToRemove, int tripsNum){

	char tmpStr[MAX] = "";
	int lineCount = 1;
	FILE* fileTmp;

	// remove trip data from diary array--------------------
	for (int i = tripToRemove; i <= tripsNum; i++)
		diary[i] = diary[i + 1];
	// copy data except line to be removed to temporary file
	fileTmp = fopen("test_tmp.txt", "w");
	file = fopen("test.txt", "r");
	if (file == NULL)
		printf("\nError opening file!\n");
	else{
		while (!feof(file)){
			if (fgets(tmpStr, MAX, file) != NULL && 
				tripToRemove != lineCount)
				fputs(tmpStr, fileTmp);
			lineCount++;
		}
	}
	fclose(file);
	fclose(fileTmp);
	// copy data back from tmp file to original
	fileTmp = fopen("test_tmp.txt", "r");
	file = fopen("test.txt", "w");

	if (fileTmp == NULL)
		printf("\nError opening file!\n");
	else{
		while (!feof(fileTmp)){
			if (fgets(tmpStr, MAX, fileTmp) != NULL)
				fputs(tmpStr, file);
		}
	}
	fclose(file);
	fclose(fileTmp);
}
void printReport(drivingDiary* diary, int size){

	int lowBound = 0;
	int upBound = 0;
	int number = 1;
	
	printf("\nInput specified range from odometer\n");
	// lower bound input and error checking------------------------------------
	lowBound = odometerInput("input lower odometer value (0 - 99999): ");
	// upper bound input and error checking------------------------------------
	upBound = odometerInput("input upper odometer value (0 - 99999): ");
	// display the report result-----------------------------------------------
	printf("\n");
	for (int i = 0; i < size; i++){
		if ((diary[i].odometerStart >= lowBound) &&
			(diary[i].odometerEnd <= upBound)){
			printf("%2d %+30s ", number, diary[i].locationStart);
			printf("%+7s ", diary[i].timeStart);
			printf("%10d\t", diary[i].odometerStart);
			printf("%+30s ", diary[i].locationEnd);
			printf("%+7s ", diary[i].timeEnd);
			printf("%10d\n", diary[i].odometerEnd);
			number++;
		}
	}
}
void readFileToDiary(FILE* file, drivingDiary* diary){

	int i = 0;
	
	file = fopen("test.txt", "r");
	if (file == NULL)
		printf("\nError opening file!\n");
	else{
		while(fscanf(file, " %[a-zA-Z ]%[0-9:]%d %[a-zA-Z ]%[0-9:]%d%*[\n]",
				diary[i].locationStart,
				diary[i].timeStart,
				&diary[i].odometerStart,
				diary[i].locationEnd,
				diary[i].timeEnd,
				&diary[i].odometerEnd) != EOF)
			i++;		
	}
}
void cleanDiary(drivingDiary* diary){
	free(diary->locationStart);
	free(diary->locationEnd);
	free(diary->timeStart);
	free(diary->timeEnd);
	diary->odometerStart = 0;
	diary->odometerEnd = 0;
}
int odometerInput(char* prompt){

	int result = 0;
	char* tmpStr = (char*)calloc(TIME_MAX, sizeof(char));
	int valid = 1; // false by default

	fflush(stdin);// clear stdin
	printf("%s", prompt);
	scanf("%[^\n]s", tmpStr);
	while (valid != 0 || tmpStr == ""){
		for (int i = 0; i < strlen(tmpStr); ++i){//doesn't run if empty string
			if (!isdigit(tmpStr[i])){
				valid = 1;
				break;
			}
			valid = 0; // if all chars are digits valid set to 0
		}
		if (valid == 0){
			result = (int)strtol(tmpStr, NULL, 10); // convert string to int
			if (result > 99999)
				valid = 1;
		}
		if (valid == 1){
			fflush(stdin);// clear stdin
			printf("Please, input values from 0 to 99999: ");
			scanf("%[^\n]s", tmpStr);
		}
	}
	free(tmpStr);
	return result;
}
