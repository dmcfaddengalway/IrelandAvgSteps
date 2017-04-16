//
//  main.c
//  IrelandAvgSteps
//
//  Created by Danny McFadden on 26/3/17.
//  Copyright © 2017 Danny McFadden. All rights reserved.
//

#include <stdio.h>
#include "string.h"
#include "stdlib.h"

//Structure of data, with first column being steps of the day (starting Jan 7th, 2017 until today)
//Second column being kilometers
typedef struct {
    int steps;
    double km;
    double mi;
    int flights;
    double sleepHrs;
} irelandAvg;

irelandAvg *avgData[500];
int numAvgs = 0;

double convertKm(double *avgData) {
    double miles = 0.0;
    int i = 0;
    
    miles = avgData[i] / 1.6093;
    
    return miles;
}

int readFile(char *fileName) {
    FILE *filePointer;
    
    filePointer = fopen(fileName, "r");
    
    if (filePointer == NULL) {
        printf("Error opening file.");
        return 0;
    }
    
    while (!feof(filePointer)) {
        //Allocate specific space for the structure
        avgData[numAvgs] = ((irelandAvg *)malloc(sizeof(irelandAvg)));
        
        //Scan in Steps and Kilometers walked
        fscanf(filePointer, "%d\t%lf%d\t%.2lf\n", &avgData[numAvgs]->steps, &avgData[numAvgs]->km, &avgData[numAvgs]->flights, &avgData[numAvgs]->sleepHrs);
        
        //Convert kilometers to miles
        avgData[numAvgs]->mi = convertKm(&avgData[numAvgs]->km);
        
        numAvgs++;
    }
    fclose(filePointer);
    
    return 1;
}

int main() {
    char fileName[] = "stepData.txt";
    int i = 0;
    int numSteps, sumSteps = 0;
    int numFlights, sumFlights = 0;
    double numKm, numMi = 0.0;
    double sumKm, sumMi = 0.0;
    double numSleepHrs, sumSleepHrs = 0.0;
    double avgSteps, avgKm, avgMi, avgSleepHrs, avgFlights = 0.0;
    
    if (!readFile(fileName)) {
        printf("File could not be opened!\n");
        return 0;
    }
    
    while (avgData[i] != NULL) {
        //Get total steps taken
        numSteps = avgData[i]->steps;
        sumSteps += numSteps;
        
        //Get total kilometers walked
        numKm = avgData[i]->km;
        sumKm += numKm;
        
        //Get total miles walked
        numMi = convertKm(&avgData[i]->km);
        sumMi += numMi;
        
        //Get total flights climbed
        numFlights = avgData[i]->flights;
        sumFlights += numFlights;
        
        //Get total sleep hours accumulated
        numSleepHrs = avgData[i]->sleepHrs;
        sumSleepHrs += numSleepHrs;
        
        i++;
    }
    
    avgSteps = (float)(sumSteps / i);
    avgKm = (float)(sumKm / i);
    avgMi = (float)(sumMi / i);
    avgSleepHrs = (float)(sumSleepHrs / i);
    avgFlights = (float)(sumFlights / i);
    
    printf("Total Steps: %d\n", sumSteps);
    printf("Total Kilometers: %.2lf\n", sumKm);
    printf("Total Miles: %.2lf\n", sumMi);
    printf("Total Sleep Hours: %.2lf\n", sumSleepHrs);
    printf("Total Flights: %d\n", sumFlights);
    printf("=======================================\n");
    printf("Average Steps: %.2lf\n", avgSteps);
    printf("Average Kilometers: %.2lf\n", avgKm);
    printf("Average Miles: %.2lf\n", avgMi);
    printf("Average Sleep Hours: %.2lf\n", avgSleepHrs);
    printf("Average Flights: %.2lf\n", avgFlights);
    
    printf("\n\n");
    
    return 0;
}
