#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUM_SPECIALTIES 4
#define NUM_WARDS 4
#define MAX_DAILY_PATIENT_CAP 30
#define MAX_TOTAL_BED_CAPACITY 20

const int SPECIALTY_IDS[NUM_SPECIALTIES]={1,2,3,4};
const char SPECIALTY_NAMES[NUM_SPECIALTIES][25]={"General Practice(OPD)","Paediatrics","Cardiology","Neurology"};
const double BASE_CONSULTATION_FEE[NUM_SPECIALTIES]={1500.00,2500.00,4500.00,5000.00};
const int CONSULTATION_TIME_PER_PATIENT[NUM_SPECIALTIES]={15,20,30,30};
const int DAILY_PATIENT_CAP[NUM_SPECIALTIES]={30,20,12,10};

const int WARD_IDS[NUM_WARDS]={1,2,3,4};
const char WARD_NAMES[NUM_WARDS][25]={"General Ward","Paediatric Ward","Surgical Ward","ICU(Intensive Care Unit)"};
const double DAILY_BED_RATE[NUM_WARDS]={3000.00,6000.00,12000.00,25000.00};
const int TOTAL_BED_CAPACITY[NUM_WARDS]={20,10,10,05};

int bedOccupancy[NUM_WARDS][MAX_TOTAL_BED_CAPACITY]={0};
int specialtyCurrentQueues[NUM_WARDS]={0,0,0,0};