#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"

//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////
// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
   printf("Pat.# Name            Phone#\n"
          "----- --------------- --------------------\n");
}
// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
   if (fmt == FMT_FORM)
   {
       printf("Name  : %s\n"
              "Number: %05d\n"
              "Phone : ", patient->name, patient->patientNumber);
       displayFormattedPhone(patient->phone.number);
       printf(" (%s)\n", patient->phone.description);
   }
   else
   {
       printf("%05d %-15s ", patient->patientNumber,
              patient->name);
       displayFormattedPhone(patient->phone.number);
       printf(" (%s)\n", patient->phone.description);
   }
}

//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////
// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
   int selection;
   do
   {
       printf("Veterinary Clinic System\n"
              "=========================\n"
              "1) PATIENT     Management\n"
              "2) APPOINTMENT Management\n"
              "-------------------------\n"
              "0) Exit System\n"
              "-------------------------\n"
              "Selection: ");
       selection = inputIntRange(0, 2);
       putchar('\n');
       switch (selection)
       {
       case 0:
           printf("Are you sure you want to exit? (y|n): ");
           selection = !(inputCharOption("yn") == 'y');
           putchar('\n');
           if (!selection)
           {
               printf("Exiting system... Goodbye.\n\n");
           }
           break;
       case 1:
           menuPatient(data->patients, data->maxPatient);
           break;
       case 2:
           printf("<<< Feature not yet available >>>\n\n");
           break;
       }
   }
   while (selection);
}
// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
   int selection;
   do
   {
       printf("Patient Management\n"
              "=========================\n"
              "1) VIEW   Patient Data\n"
              "2) SEARCH Patients\n"
              "3) ADD    Patient\n"
              "4) EDIT   Patient\n"
              "5) REMOVE Patient\n"
              "-------------------------\n"
              "0) Previous menu\n"
              "-------------------------\n"
              "Selection: ");
       selection = inputIntRange(0, 5);
       putchar('\n');
       switch (selection)
       {
       case 1:
           displayAllPatients(patient, max, FMT_TABLE);
           suspend();
           break;
       case 2:
           searchPatientData(patient, max);
           break;
       case 3:
           addPatient(patient, max);
           suspend();
           break;
       case 4:
           editPatient(patient, max);
           break;
       case 5:
           removePatient(patient, max);
           suspend();
           break;
       }
   }
   while (selection);
}
// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
   int selection;
   do
   {
       printf("Edit Patient (%05d)\n"
              "=========================\n"
              "1) NAME : %s\n"
              "2) PHONE: ", patient->patientNumber, patient->name);
       displayFormattedPhone(patient->phone.number);
       printf("\n"
              "-------------------------\n"
              "0) Previous menu\n"
              "-------------------------\n"
              "Selection: ");
       selection = inputIntRange(0, 2);
       putchar('\n');
       if (selection == 1)
       {
           printf("Name  : ");
           inputCString(patient->name, 1, NAME_LEN);
           putchar('\n');
           printf("Patient record updated!\n\n");
       }
       else if (selection == 2)
       {
           inputPhoneData(&patient->phone);
           printf("Patient record updated!\n\n");
       }
   }
   while (selection);
}

// ---------------------------------------------------------------------------
// !!! Put all the remaining function definitions below !!!
// Note: Maintain the same order/sequence as it is listed in the header file
// ---------------------------------------------------------------------------
// Display's all patient data in the FMT_FORM | FMT_TABLE format
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
   int i;
   int flag=0;
   // check if there are no eligible records to display
   for (i=0; i<max; i++)
   {
       if(patient[i].patientNumber != 0)
       {
           // set flag to 1 if there are eligible records
           flag = 1;
           // break out of the for loop immediately
           break;
       }
   }
   if (flag == 0)
   {
       printf("*** No records found ***\n");
   }
   else
   {
       // display the table header
       displayPatientTableHeader();
       for (i=0; i<max; i++)
       {
           // display a single eligible patient record
           if(patient[i].patientNumber != 0)
               displayPatientData(&patient[i], fmt);
       }
   }
   putchar('\n');
}

// Search for a patient record based on patient number or phone number
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void searchPatientData(const struct Patient patient[], int max)
{
   int selection;
   // display the search options
   do
   {
       printf("Search Options\n"
              "=========================\n"
              "1) By patient number\n"
              "2) By phone number\n"
              "-------------------------\n"
              "0) Previous menu\n"
              "-------------------------\n"
              "Selection: ");
       // use the inputIntRange() function in core.c
       selection = inputIntRange(0, 2);
       putchar('\n');
       // call the appropriate function depending on user input
       if (selection == 1)
       {
           searchPatientByPatientNumber(patient, max);
           suspend();
       }
       else if (selection == 2)
       {
           searchPatientByPhoneNumber(patient, max);
           suspend();
       }
   }
   while (selection);
}

// Add a new patient record to the patient array
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void addPatient(struct Patient patient[], int max)
{
   int i;
   int freeIndex;
   int flag=0;
   // check if there is a free element for new record
   for (i=0; i<max; i++)
   {
       if(patient[i].patientNumber == 0)
       {
           // set flag to 1 if there is a free element
           flag = 1;
           freeIndex = i;
           // break out of the for loop immediately
           break;
       }
   }
   // if flag is 0, then patient array is already full
   if (flag == 0)
   {
       printf("ERROR: Patient listing is FULL!\n");
   }
   // if flag is 1, add new patient
   else
   {
       patient[freeIndex].patientNumber = nextPatientNumber(patient, max);
       inputPatient(&patient[freeIndex]);
       printf("*** New patient record added ***\n");
   }
   putchar('\n');
}
 
// Edit a patient record from the patient array
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void editPatient(struct Patient patient[], int max)
{
   // get the patient number as user input
   printf("Enter the patient number: ");
   int num = inputInt();
   // using the patient number, get the index in the patient array
   int index = findPatientIndexByPatientNum(num, patient, max);
   putchar('\n');
   // if index is -1, patient number is not existing
   if (index == -1)
   {
       printf("ERROR: Patient record not found!\n");
   }
   else
   {
       // call the menuPatientEdit() function using the index
       menuPatientEdit(&patient[index]);
   }
}

// Remove a patient record from the patient array
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void removePatient(struct Patient patient[], int max)
{
   // get the patient number as user input
   printf("Enter the patient number: ");
   int num = inputInt();
   // using the patient number, get the index in the patient array
   int index = findPatientIndexByPatientNum(num, patient, max);
   putchar('\n');
   // if index is -1, patient number is not existing
   if (index == -1)
   {
       printf("ERROR: Patient record not found!\n");
   }
   else
   {
       // remove the patient in the array using the index
       printf("Name  : %s\n", patient[index].name);
       printf("Number: %05d\n", patient[index].patientNumber);
       printf("Phone : ");
       displayFormattedPhone(patient[index].phone.number);
       printf(" (%s)\n", patient[index].phone.description);
       printf("\nAre you sure you want to remove this patient record? (y/n): ");
       char answer;
       answer = inputCharOption("yn");
       if (answer == 'n')
       {
           printf("Operation aborted.\n");
       }
       else
       {
           patient[index].patientNumber = 0;
           printf("Patient record has been removed!\n");
       }
   }
   putchar('\n');
}

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
   // get the patient number as user input
   printf("Search by patient number: ");
   int num = inputInt();
   // using the patient number, get the index in the patient array
   int index = findPatientIndexByPatientNum(num, patient, max);
   putchar('\n');
   // if index is -1, patient number is not existing
   if (index == -1)
   {
       printf("*** No records found ***\n");
   }
   else
   {
       // call the displayPatientData() using the index in the patient array
       displayPatientData(&patient[index], FMT_FORM);
   }
   putchar('\n');
}

// Search and display patient records by phone number (tabular)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
   char phoneNum[11];
   // get the phone number of the patient as user input
   printf("Search by phone number: ");
   inputCString(phoneNum, 10, 10);
   putchar('\n');
   int flag = 0;
   int i;
   for (i=0; i<max; i++)
   {
       // display a single eligible patient record
       if(strcmp(phoneNum, patient[i].phone.number) == 0)
       {
           flag = 1;
           break;
       }
   }
   // display the table header
   displayPatientTableHeader();
   if (flag == 0)
   {
       putchar('\n');
       printf("*** No records found ***\n");
   }
   else
   {
       for (i=0; i<max; i++)
       {
           // display a single eligible patient record
           if(strcmp(phoneNum, patient[i].phone.number) == 0)
               displayPatientData(&patient[i], FMT_TABLE);
       }
   }
   putchar('\n');
}

// Get the next highest patient number
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
int nextPatientNumber(const struct Patient patient[], int max)
{
   int i;
   int next = -1;
   // find the largest patient number in the array
   // and store in variable next
   for (i=0; i<max; i++)
   {
       if(patient[i].patientNumber > next)
       {
           next = patient[i].patientNumber;
       }
   }
   // add 1 to the largest patient number in the array
   ++next;
   return next;
}

// Find the patient array index by patient number (returns -1 if not found)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
int findPatientIndexByPatientNum(int patientNumber, const struct Patient patient[], int max)
{
   int i ;
   // -1 is default return value, which is patient number not found
   int ret = -1;
   // iterate over each element the patient array
   for (i=0; i<max; i++)
   {
       // if patientNumber is found, return the index
       if (patient[i].patientNumber == patientNumber)
       {
           ret = i;
           break;
       }
   }
   return ret;
}

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void inputPatient(struct Patient* patient)
{
   // get the patient info as user input
   printf("Patient Data Input\n"
          "------------------\n");
   printf("Number: %05d\n", patient->patientNumber);
   printf("Name  : ");
   inputCString(patient->name, 1, NAME_LEN);
   putchar('\n');
   inputPhoneData(&(patient->phone));
}

// Get user input for phone contact information
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void inputPhoneData(struct Phone* phone)
{
   int selection;
   // get the phone info as user input
   printf("Phone Information\n"
          "-----------------\n");
   printf("How will the patient like to be contacted?\n");
   printf("1. Cell\n");
   printf("2. Home\n");
   printf("3. Work\n");
   printf("4. TBD\n");
   printf("Selection: ");
   selection = inputIntRange(1, 4);
   putchar('\n');
   if (selection == 1)
   {
       printf("Contact: ");
       puts("CELL");
       strcpy(phone->description, "CELL");
   }
   if (selection == 2)
   {
       printf("Contact: ");
       puts("HOME");
       strcpy(phone->description, "HOME");
   }
   if (selection == 3)
   {
       printf("Contact: ");
       puts("WORK");
       strcpy(phone->description, "WORK");
   }
   if (selection == 4)
   {
       strcpy(phone->description, "TBD");
   }
   else
   {
       printf("Number : ");
       inputCString(phone->number, 10, 10);
       putchar('\n');
   }
}

