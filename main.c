#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUM_SPECIALTIES 4
#define NUM_WARDS 4
#define MAX_PATIENTS 100
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

int main(){
    char patientName[MAX_PATIENTS][30];
    int patientAge[MAX_PATIENTS];
    int triageLevel[MAX_PATIENTS];
    int patientSpecialtyIds[MAX_PATIENTS];
    int patientIsAdmitted[MAX_PATIENTS];
    int patientWardIds[MAX_PATIENTS];
    int patientDaysAdmitted[MAX_PATIENTS];

    int totalPatients=0;

    return 0;    
}

void displayDoctorSpecialtiesData(){
    printf("========Doctor Specialties Data========\n");
    printf("%-12s%-25s%-20s%-20s%-15s\n",
        "Specialty ID",
        "Specialty Name",
        "Base Consultation Fee",
        "Consultation Time/Patient",
        "Daily Patient Cap");
    for(int i=0;i<NUM_SPECIALTIES;i++){
        printf("%-12d%-25s%-20.2lf%-20d%-15d\n",
            SPECIALTY_IDS[i],
            SPECIALTY_NAMES[i],
            BASE_CONSULTATION_FEE[i],
            CONSULTATION_TIME_PER_PATIENT[i],
            DAILY_PATIENT_CAP[i]);
    }
}

void displayHospitalWardsData(){
    printf("========Hospital Wards Data========\n");
    printf("%-10s%-25s%-25s%-20s\n","Ward ID","Ward Name","Daily Bed Rate(LKR/Day)","Total Bed Capacity");
    for(int i=0;i<NUM_WARDS;i++){
        printf("%-10d%-25s%-25.2lf%-20d\n",WARD_IDS[i],WARD_NAMES[i],DAILY_BED_RATE[i],TOTAL_BED_CAPACITY[i]);
    }
}

void patientRegistration(char patientName[][30],int patientAge[],int triageLevel[],int patientSpecialtyIds[],
    int patientIsAdmitted[],int patientWardIds[],int patientDaysAdmitted[],int *totalPatients[]){
        
        if(*totalPatients>= MAX_PATIENTS){
            printf("Hospital has reached maximum capacity(%d\n)",MAX_PATIENTS);
            return;
        }

        int i=*totalPatients;

        printf("========Patient Registration========\n");
        printf("Enter patient name: ");
        scanf(" %[^\n]",patientName[i]);

        printf("Enter patient age: ");
        scanf("%d",&patientAge[i]);

        printf("Enter Emergency/Triage Level(1=Normal,2=Urgent,3=Critical): ");
        scanf("%d",&triageLevel[i]);
       
        while(triageLevel[i]<1||triageLevel[i]>3){
            printf("Invalid triage level.");
            printf("Enter Emergency/Triage Level(1=Normal,2=Urgent,3=Critical): ");
            scanf("%d",&triageLevel[i]);
        }

        displayDoctorSpecialtiesData();
        patientSpecialtyIds[i]=0;
       
        printf("Enter specialty ID(1 to 4): ");
        scanf("%d",&patientSpecialtyIds[i]);
        
        while(patientSpecialtyIds[i]<1||patientSpecialtyIds[i]>4){
            printf("Invalid specialty ID.Please enter again.: ");
            scanf("%d",&patientSpecialtyIds[i]);
        }

        printf("Is admitted to ward?(1=Yes,0=No): ");
        scanf("%d",&patientIsAdmitted[i]);

        if(patientIsAdmitted[i]==1){
            displayHospitalWardsData();
            patientWardIds[i]=0;

            printf("Enter ward ID(1 to 4): ");
            scanf("%d",&patientWardIds[i]);
        
            while(patientWardIds[i]<1||patientWardIds[i]>4){
                printf("Invalid ward ID.Please enter again.: ");
                scanf("%d",&patientWardIds[i]);
            }

            printf("Enter number of days admitted: ");
            scanf("%d",patientDaysAdmitted[i]);

        }
        else{
            patientWardIds[i]=0;
            patientDaysAdmitted[i]=0;
        }            
    (*totalPatients)++;
}

