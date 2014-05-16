#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 200
#define NAME_MAX 50
#define TIME_MAX 10

typedef struct{
	char*	locationStart;
	char*	locationEnd;
	char*	timeEnd;
	char*	timeStart;
	int		odometerStart;
	int		odometerEnd;
}drivingDiary;

void initialize(drivingDiary* d);
void saveTrip(FILE* f, drivingDiary d);
void addTrip(drivingDiary* d);
void readAllTrips(FILE* f);
void readOneTrip(FILE* f, int lineToDisplay);
int linesNumber(FILE* f);
void removeTrip(FILE* f, drivingDiary* d, int tripToRemove, int tripsNum);
void printReport(drivingDiary* d, int size);
void readFileToDiary(FILE* f, drivingDiary* d);
void cleanDiary(drivingDiary* diary);
int odometerInput(char* prompt);

