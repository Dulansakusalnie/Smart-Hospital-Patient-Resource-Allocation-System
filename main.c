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
int specialtyCurrentQueues[NUM_SPECIALTIES]={0,0,0,0};

double waitTime[MAX_PATIENTS];
double emergencySurcharge[MAX_PATIENTS];
double totalWardCost[MAX_PATIENTS];
double grossTotal[MAX_PATIENTS];
double ageSubsidyDiscount[MAX_PATIENTS];
double finalPayableAmount[MAX_PATIENTS];

//Function prototypes
void displayDoctorSpecialtiesData();
void displayHospitalWardsData();
int getOccupiedBeds(int wardIndex);
void patientRegistration(char patientName[][30],int patientAge[],int triageLevel[],int patientSpecialtyIds[],
    int patientIsAdmitted[],int patientWardIds[],int patientDaysAdmitted[],int *totalPatients[],
    int patientBedNumbers[]);
double getBaseConsultationFee(int specialtyId);
double calculateEmergencySurcharge(int triageLevel,double baseFee);
double getEmergencySurchargeRate(int triageLevel);
double calculateWardCost(int isAdmitted,int wardId,int daysAdmitted);
double calculateGrossTotal(double baseFee,double emergencySurcharge,double wardCost);
double calculateAgeSubsidyDiscount(int age,double grossTotal);
double getAgeSubsidyRate(int age);
double calculateFinalPayable(double grossTotal,double discount);
double calculateWaitingTime(int specialtyId,int currentQueueCount);
void incrementSpecialtyQueue(int specialtyId);
void calculatePatientBill(int i,int patientAge[],int triageLevel[],int patientSpecialtyIds[],
    int patientIsAdmitted[],int patientWardIds[],int patientDaysAdmitted[]);
void printPatientBill(int i,char patientName[][30],int patientAge[],int triageLevel[],int patientSpecialtyIds[],
    int patientIsAdmitted[],int patientWardIds[],int patientDaysAdmitted[],int patientBedNumbers[]);
void sortPatientByPriority(int sortedIndices[],int totalPatients,int triageLevel[]);
void displayPatientByPriority(int sortedIndices[],int totalPatients,char patientName[][30],int patientAge[],
    int triageLevel[],int patientSpecialtyIds[],int patientIsAdmitted[],int patientWardIds[],
    int patientBedNumbers[]);
void displayPerformanceReport(int totalPatients,int triageLevel[],char patientName[][30],int patientAge[],
    double finalPayableAmount[],double ageSubsidyDiscount[],double grossTotal[]);
void saveBedsStatus();
void loadBedsStatus();
void appendPatientRecords(int i,char patientName[][30],int patientAge[],int triageLevel[],
    int patientSpecialtyIds[],int patientIsAdmitted[],int patientWardIds[],int patientDaysAdmitted[],
    int patientBedNumbers[]);


int main(){
    char patientName[MAX_PATIENTS][30];
    int patientAge[MAX_PATIENTS];
    int triageLevel[MAX_PATIENTS];
    int patientSpecialtyIds[MAX_PATIENTS];
    int patientIsAdmitted[MAX_PATIENTS];
    int patientWardIds[MAX_PATIENTS];
    int patientDaysAdmitted[MAX_PATIENTS];
    int patientBedNumbers[MAX_PATIENTS];

    int sortedIndices[MAX_PATIENTS];

    int totalPatients=0;
    int choice;

    loadBedsStatus();

    do{
        printf("===========================================\n");
        printf("\t\tSMART HOSPITAL MANAGEMENT SYSTEM\n");
        printf("===========================================\n");
        printf("1.View Doctor Specialties\n");
        printf("2.View Hospital Wards\n");
        printf("3.Register New Patient\n");
        printf("4.Print Patient Bill\n");
        printf("5.View Patients By Priority\n");
        printf("6.View Performance Report\n");
        printf("7.Save Bed Status\n");
        printf("8.Load Bed Status\n");
        printf("9.Exit\n");
        printf("===========================================\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);

        switch(choice){
            case 1:
                displayDoctorSpecialtiesData();
                break;
            case 2:
                displayHospitalWardsData();
                break;
            case 3:
                patientRegistration(patientName,patientAge,triageLevel,patientSpecialtyIds,patientIsAdmitted,
                    patientWardIds,patientDaysAdmitted,&totalPatients,patientBedNumbers);
                if(totalPatients>0){
                    int i=totalPatients-1;
                    calculatePatientBill(i,patientAge,triageLevel,patientSpecialtyIds,patientIsAdmitted,
                    patientWardIds,patientDaysAdmitted);
                    printPatientBill(i,patientName,patientAge,triageLevel,patientSpecialtyIds,patientIsAdmitted,
                    patientWardIds,patientDaysAdmitted,patientBedNumbers);
                    appendPatientRecords(i,patientAge,triageLevel,patientSpecialtyIds,patientIsAdmitted,
                    patientWardIds,patientDaysAdmitted);
                    print("Patient registered successfully,\n");
                }
                break;
            case 4:
                if(totalPatients==0){
                    printf("Patients are not registered yet.\n");
                }
                else{
                    int patientId;
                    printf("Enter patient ID number(1 to %d): ",totalPatients);
                    scanf("%d",&patientId);
                    if(patientId>=1&&patientId<=totalPatients){
                        printPatientBill(patientId-1,patientName,patientAge,triageLevel,patientSpecialtyIds,
                            patientIsAdmitted,patientWardIds,patientDaysAdmitted,patientBedNumbers);
                    }
                    else{
                        printf("Invalid patient ID\n");
                    }
                }
                break;
            case 5:
                displayPatientByPriority(sortedIndices,totalPatients,patientName,patientAge,triageLevel,
                    patientSpecialtyIds,patientIsAdmitted,patientWardIds,patientBedNumbers);
                break;
            case 6:
                displayPerformanceReport(totalPatients,triageLevel,patientName,patientAge,finalPayableAmount,
                    ageSubsidyDiscount,grossTotal);
                break;
            case 7:
                saveBedsStatus();
                printf("Bed status saved to beds_status.txt\n");
                break;
            case 8:
                loadBedsStatus();
                printf("Bed status loaded from bed_status.txt\n");
                break;
            case 9:
                saveBedsStatus();
                break;
            default:
                printf("Invalid choice.\n");
            
        }
    }while(choice!=9);

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
    printf("%-10s%-25s%-25s%-20s%-20d\n","Ward ID","Ward Name","Daily Bed Rate(LKR/Day)","Total Bed Capacity","Available Beds");
    for(int i=0;i<NUM_WARDS;i++){
        int occupiedBeds=getOccupiedBeds;
        int availableBeds=TOTAL_BED_CAPACITY[i]-occupiedBeds;
        printf("%-10d%-25s%-25.2lf%-20d%-20d\n",WARD_IDS[i],WARD_NAMES[i],DAILY_BED_RATE[i],TOTAL_BED_CAPACITY[i],availableBeds);
    }
}

int getOccupiedBeds(int wardIndex){
    int bedCount=0;
    for(int b=0;b<TOTAL_BED_CAPACITY[wardIndex];b++){
        if(bedOccupancy[wardIndex][b]==1){
            bedCount++;
        }
    }
    return bedCount;
}

void patientRegistration(char patientName[][30],int patientAge[],int triageLevel[],int patientSpecialtyIds[],
    int patientIsAdmitted[],int patientWardIds[],int patientDaysAdmitted[],int *totalPatients[],
    int patientBedNumbers[i]){
        
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

        int spIndex=patientSpecialtyIds[i]-1;
        waitTime[i]=calculateWaitingTime(patientSpecialtyIds[i],specialtyCurrentQueues[spIndex]);
        incrementSpecialtyQueue(patientSpecialtyIds[i]);

        printf("Is admitted to ward?(1=Yes,0=No): ");
        scanf("%d",&patientIsAdmitted[i]);

        if(patientIsAdmitted[i]==1){
            displayHospitalWardsData();
            patientWardIds[i]=0;
        
            printf("Enter ward ID(1 to 4): ");
            scanf("%d",&patientWardIds[i]);

            int wardIndex=patientWardIds[i]-1;
        
            while(patientWardIds[i]<1||patientWardIds[i]>4||getOccupiedBeds(wardIndex)>=TOTAL_BED_CAPACITY){
                if(patientWardIds[i]<1||patientWardIds[i]>4){
                    printf("Invalid ward ID.Please enter again.: ");
                }
                else if(getOccupiedBeds(wardIndex)>=TOTAL_BED_CAPACITY){
                    printf("Sorry %s ward is full.Please choose another ward",WARD_NAMES[wardIndex]);
                }
                scanf("%d",&patientWardIds[i]);
                wardIndex=patientWardIds[i]-1;
            }

            patientBedNumbers[i]=0;
            for(int b=0;b<TOTAL_BED_CAPACITY;b++){
                if(bedOccupancy[wardIndex][b]==0){
                    bedOccupancy[wardIndex][b]=1;
                    patientBedNumbers[i]=b+1;
                    printf("Patient %s admitted to %s.Bed number %d assigned.\n",patientName[i],WARD_NAMES[wardIndex],patientBedNumbers[i]);
                    break;
                }
            }

            printf("Enter number of days admitted: ");
            scanf("%d",&patientDaysAdmitted[i]);

        }
        else{
            patientWardIds[i]=0;
            patientDaysAdmitted[i]=0;
            patientBedNumbers[i]=0;
        }            
    (*totalPatients)++;
}

double getBaseConsultationFee(int specialtyId){
    return BASE_CONSULTATION_FEE[specialtyId-1];
}


double calculateEmergencySurcharge(int triageLevel,double baseFee){
    return baseFee*getEmergencySurchargeRate(triageLevel);
}

double getEmergencySurchargeRate(int triageLevel){
    switch(triageLevel){
        case 3: return 0.50;
        case 2: return 0.20;
        case 1: return 0.00;
    }
}

double calculateWardCost(int isAdmitted,int wardId,int daysAdmitted){
    if(isAdmitted!=1){
        return 0.0;
    }
    return daysAdmitted*DAILY_BED_RATE[wardId-1];
}

double calculateGrossTotal(double baseFee,double emergencySurcharge,double wardCost){
    return baseFee+emergencySurcharge+wardCost;
}

double calculateAgeSubsidyDiscount(int age,double grossTotal){
        return grossTotal*getAgeSubsidyRate(age);
 }

double getAgeSubsidyRate(int age){
    if(age<5||age>65){
        return 0.15;
    }
    else{
        return 0.00;
    }
}

double calculateFinalPayable(double grossTotal,double discount){
    return grossTotal-discount;
}

double calculateWaitingTime(int specialtyId,int currentQueueCount){
    return currentQueueCount*CONSULTATION_TIME_PER_PATIENT[specialtyId-1];
}

void incrementSpecialtyQueue(int specialtyId){
    specialtyCurrentQueues[specialtyId-1]++;
}

void calculatePatientBill(int i,int patientAge[],int triageLevel[],int patientSpecialtyIds[],
    int patientIsAdmitted[],int patientWardIds[],int patientDaysAdmitted[]){
    double baseFee=getBaseConsultationFee(patientSpecialtyIds[i]);
    emergencySurcharge[i]=calculateEmergencySurcharge(triageLevel[i],baseFee);
    totalWardCost[i]=calculateWardCost(patientIsAdmitted[i],patientWardIds[i],patientDaysAdmitted[i]);
    grossTotal[i]=calculateGrossTotal(baseFee,emergencySurcharge[i],totalWardCost[i]);
    ageSubsidyDiscount[i]=calculateAgeSubsidyDiscount(patientAge[i],grossTotal[i]);
    finalPayableAmount[i]=calculateFinalPayable(grossTotal[i],ageSubsidyDiscount[i]);
}

void printPatientBill(int i,char patientName[][30],int patientAge[],int triageLevel[],int patientSpecialtyIds[],
    int patientIsAdmitted[],int patientWardIds[],int patientDaysAdmitted[],int patientBedNumbers[]){
    int spIndex=patientSpecialtyIds[i]-1;
    const char *UrgencyText[]={"Normal","Urgent","Critical"};

    double surchargeRate=getEmergencySurchargeRate(triageLevel[i]);
    double subsidyRate=getAgeSubsidyRate(patientAge[i]);

    printf("========================================================\n");
    printf("\t\tSMART HOSPITAL ADMISSION & BILL\n");
    printf("--------------------------------------------------------\n");
    printf("Patient ID              :PAT-%04d\n",i+1);
    printf("Patient Name             :%s\n",patientName[i]);
    printf("Age                     :%d Years",patientAge[i]);
    if(patientAge[i]<5||patientAge[i]>65)
        printf("(15%% Subsidy Eligible)");
    printf("\n");
    printf("Specialty               :%s\n",SPECIALTY_NAMES[spIndex]);
    if(patientIsAdmitted[i]==1){
        int wIndex=patientWardIds[i]-1;
        printf("Assigned Ward           :%s(Bed #%02d)\n",WARD_NAMES[wIndex],patientBedNumbers[i]);
    }
    else{
        printf("Assigned Ward           :OPD(Outpatient)\n");
    }
    printf("Urgency Level           :Level %d (%s)\n",triageLevel[i],urgencyText[triageLevel[i]-1]);
    printf("--------------------------------------------------------\n");
    printf("Base Consultation Fee   :LKR %10.2lf\n",BASE_CONSULTATION_FEE[spIndex]);
    printf("Emergency Surcharge     :LKR %10.2lf(%.0lf%%)\n",emergencySurcharge[i],surchargeRate*100);;
    printf("Ward Stay Cost(%d Days) :LKR %10.2f\n",patientDaysAdmitted[i],totalWardCost[i]);
    printf("--------------------------------------------------------\n");
    printf("Gross Total Bill        :LKR %10.2lf\n",grossTotal[i]);
    printf("Age Subsidy Discount    :LKR %10.2lf(%.0lf%%)\n",-ageSubsidyDiscount[i],subsidyRate*100);
    printf("--------------------------------------------------------\n");
    printf("Final Payable Amount    :LKR %10.2lf\n",finalPayableAmount[i]);
    if(waitTime[i]==0.0){
        printf("Estimated Waiting Time  :0.00 mins(Immediate Attention)\n");
    }
    else{
        printf("Estimated Waiting Time  :%.2f\n",waitTime[i]);
    }
    printf("========================================================\n");

}

void sortPatientByPriority(int sortedIndices[],int totalPatients,int triageLevel[]){
    for(int i=0;i<totalPatients;i++){
        sortedIndices[i]=i;
    }
    for(int pass=0;pass<totalPatients-1;pass++){
        int swapped=0;

        for(int j=0;j<totalPatients-1-pass;j++){
            int a=sortedIndices[j];
            int b=sortedIndices[j+1];
            int shouldSwap=0;
            if(triageLevel[b]>triageLevel[a]){
                shouldSwap=1;
            }
            else if(triageLevel[b]==triageLevel[a]&&b<a){
                shouldSwap=1;
            }
            if(shouldSwap){
                int temp=sortedIndices[j];
                sortedIndices[j]=sortedIndices[j+1];
                sortedIndices[j+1]=temp;
                swapped=1;
            }
        }
        if(!swapped) break;
    }
}

void displayPatientByPriority(int sortedIndices[],int totalPatients,char patientName[][30],int patientAge[],
    int triageLevel[],int patientSpecialtyIds[],int patientIsAdmitted[],int patientWardIds[],
    int patientBedNumbers[]){

    if(totalPatients==0){
        printf("Patients are not registered yet.\n");
        return;
    }
    sortPatientByPriority(sortedIndices,totalPatients,triageLevel);
    const char *urgencyText[]={"Normal","Urgent","Critical"};

    printf("========Patients in priority order========\n");
    printf("%-12s %-22s %-5s %-15s %-22s %-18s %-5s\n","Patient ID","Patient Name","Age","Urgency Level","Specialty","Ward","Bed");
    for(int k=0;k<totalPatients;k++){
        int i=sortedIndices[k];
        int spIndex=patientSpecialtyIds[i]-1;

        printf("PAT-%04d %-20s %-5d Level %d %-10s %-22s",i+1,patientName[i],patientAge[i],triageLevel[i],urgencyText[triageLevel[i]-1],SPECIALTY_NAMES[spIndex]);

        if(patientIsAdmitted[i]==1){
            int wIndex=patientWardIds[i]-1;
            printf("%-18s %-5d\n",WARD_NAMES[wIndex],patientBedNumbers[i]);
        }
        else{
            printf("%-18s %-5s\n","OPD","-");
        }

    }
}

void displayPerformanceReport(int totalPatients,int triageLevel[],char patientName[][30],int patientAge[],
    double finalPayableAmount[],double ageSubsidyDiscount[],double grossTotal[]){

    printf("========Hospital Performance Report========\n");
    int normalCount=0;
    int urgentCount=0;
    int criticalCount=0;
    for(int i=0;i<totalPatients;i++){
        if(triageLevel[i]==1){
            normalCount++;
        }
        else if(triageLevel[i]==2){
            urgentCount++;
        }
        else if(triageLevel[i]==3){
            criticalCount++;
        }
    }
    printf("Patient Summary\n");
    printf("Total patient registered:%d\n",totalPatients);
    printf("Level 1(Normal)         :%d\n",normalCount);
    printf("Level 2(Urgent)         :%d\n",urgentCount);
    printf("Level 3(Critical)       :%d\n",criticalCount);

    double totalRevenue=0.0;
    double totalDiscount=0.0;
    for(int i=0;i<totalPatients;i++){
        totalRevenue+=finalPayableAmount[i];
        totalDiscount+=ageSubsidyDiscount[i];
    }
    printf("Financial Summarry\n");
    printf("Total revenue earned    :LKR %12.2lf\n",totalRevenue);
    printf("Total discount granted  :LKR %12.2lf\n",totalDiscount);

    printf("Bed Occupancy Per Ward\n");
    printf("%-25s %-14s %-14s %-10s\n","Ward","Occupied beds","Total Capacity","Occupancy %");
    for(int w=0;w<NUM_WARDS;w++){
        int occupiedBeds=getOccupiedBeds(w);
        int totalCapacity=TOTAL_BED_CAPACITY[w];
        double percentage=0.0;
        if(totalCapacity!=0){
            percentage=((double)occupiedBeds/totalCapacity)*100;
        }
        printf("%-25s %-14d %-14d %6.2lf%%\n",WARD_NAMES[w],occupiedBeds,total capacity,percentage);
    }

    printf("Highest paying patient\n");
    if(totalPatients==0){
        printf("Patients are not registered yet.\n");
    }
    else{
        int highestIndex=0;
        for(int i=1;i<totalPatients;i++){
            if(grossTotal[i]>grossTotal[highestIndex]){
                highestIndex=i;
            }
        }
        printf("Patient Name        :%s\n",patientName[highestIndex]);
        printf("Patient Age         :%dYears\n",patientAge[highestIndex]);
        printf("Gross Total         :%.2lf\n",grossTotal[highestIndex]);
        printf("Final Payable Amount:%.2lf\n",finalPayableAmount[highestIndex]);
    }
    }

void saveBedsStatus(){
    FILE *fp=fopen("beds_status.txt","w");
    if(fp==NULL){
        printf("Can not open beds_status.txt file for writing.\n");
        return;
    }
    fprintf(fp,"Total_wards=%d\n",NUM_WARDS);
    for(int w=0;w<NUM_WARDS;w++){
        fprintf(fp,"Capacity=%d\n",TOTAL_BED_CAPACITY[w]);
        fprintf(fp,"Beds=");
        for(int b=0;b<TOTAL_BED_CAPACITY[w];b++){
            fprintf(fp,"%d",bedOccupancy[w][b]);
            if(b!=TOTAL_BED_CAPACITY[w]-1){
                fprintf(fp," ");
            }
        }
        fprintf(fp,"\n");
    }
    fclose(fp);
}

void loadBedsStatus(){
    FILE *fp=fopen("beds_status.txt","r");
    if(fp==NULL){
        printf("Saved bed status can not found.\n");
        return;
    }
    int totalWards;
    fscanf(fp,"Total_Wards=%d",&totalWards);
    for(int w=0;w<totalWards;w++){
        int totalCapacity;
        fscanf(fp,"Capacity=%d",&totalCapacity);
        fscanf(fp,"Beds=");
        for(int b=0;b<totalCapacity;b++){
            fscanf(fp,"%d",&bedOccupancy[w][b]);
        }
    }
    fclose(fp);
}

void appendPatientRecords(int i,char patientName[][30],int patientAge[],int triageLevel[],
    int patientSpecialtyIds[],int patientIsAdmitted[],int patientWardIds[],int patientDaysAdmitted[],
    int patientBedNumbers[]){

    FILE *fp=fopen("patient_records.txt","a");
    if(fp==NULL){
        printf("Can not open patients_records.txt for appending.\n");
        return;
    }
    const char *urgencyText[]={"Normal","Urgent","Critical"};
    int spIndex=patientSpecialtyIds[i]-1;
    
    fprintf(fp,"Patient ID               :PAT-%04d\n",i+1);
    fprintf(fp,"Patient Name             :%s\n",patientName[i]);
    fprintf(fp,"Age                      :%d Years\n",patientAge[i]);
    fprintf(fp,"Urgency Level            :Level %d (%s)\n",triageLevel[i],urgencyText[triageLevel[i]-1]);
    fprintf(fp,"Specialty                :%s\n",SPECIALTY_NAMES[spIndex]);
    if(patientIsAdmitted[i]==1){
        int wIndex=patientWardIds[i]-1;
        fprintf(fp,"Assigned Ward            :%s(Bed #%02d)\n",WARD_NAMES[wIndex],patientBedNumbers[i]);
        fprintf(fp,"Days admitted            :%d\n",patientDaysAdmitted[i]);
    }
    else{
        fprintf(fp,"Assigned Ward            :OPD(Outpatient)\n");
        fprintf(fp,"Days admitted            :0\n");
    }
    
    fprintf(fp,"Base Consultation Fee   :LKR %10.2lf\n",BASE_CONSULTATION_FEE[spIndex]);
    fprintf(fp,"Emergency Surcharge     :LKR %10.2lf\n",emergencySurcharge[i]);;
    fprintf(fp,"Ward Stay Cost          :LKR %10.2f\n",totalWardCost[i]);
    fprintf(fp,"Gross Total Bill        :LKR %10.2lf\n",grossTotal[i]);
    fprintf(fp,"Age Subsidy Discount    :LKR %10.2lf\n",-ageSubsidyDiscount[i]);
    fprintf(fp,"Final Payable Amount    :LKR %10.2lf\n",finalPayableAmount[i]);
    if(waitTime[i]==0.0){
        fprintf(fp,"Estimated Waiting Time  :0.00 mins(Immediate Attention)\n");
    }
    else{
        fprintf(fp,"Estimated Waiting Time  :%.2f\n",waitTime[i]);
    }
    fclose(fp);
    }

