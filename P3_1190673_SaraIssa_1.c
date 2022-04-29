#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int SIZE = 0;

//Sara Saleh Issa Issa, 1190673, section NO.1

struct AVLnode;
typedef struct AVLnode *AVL_Tree, *Node;
FILE *input, *output;

struct AVLnode
{
    char Patient_Name[30]; //Patient Name
    char Gender[5]; //Gender
    int Date_of_admission; //Date of admission
    int Date_of_birth; //Date of birth
    char Illness[20]; //Illness
    char Address[20]; //Address
    char Blood_type[3]; //Blood type
    AVL_Tree Left;
    AVL_Tree Right;
    int Height; //Balance information
};

// To check if the AVL tree is empty or not
int isEmpty(AVL_Tree T)
{
    return T == NULL;
}

// To make the AVL tree is empty
AVL_Tree MakeEmpty(AVL_Tree T)
{
    if( T != NULL )
    {
        T->Right = MakeEmpty( T->Right );
        T->Left = MakeEmpty( T->Left );
        free(T);
    }
    // else if (T == NULL)
    return NULL;
}

// To find a patient in AVL tree
Node Find(char Patient_Name[30], AVL_Tree T)
{
    // if the AVL tree is empty
    if( T == NULL )
    {
        printf("This patient was not found in the tree!");
        return NULL;
    }
    else if( T != NULL)
    {
        // Patient_Name = T->Patient_Name
        if( strcmp(Patient_Name, T->Patient_Name) == 0)
            return T;
        // Patient_Name < T->Patient_Name
        if( strcmp(Patient_Name, T->Patient_Name) < 0 )
            return Find( Patient_Name, T->Left );

        // Patient_Name > T->Patient_Name
        else if( strcmp(Patient_Name, T->Patient_Name) > 0 )
            return Find( Patient_Name, T->Right );

        else if(strcmp(Patient_Name, T->Patient_Name) != 0)
            return NULL;
        else
            return T;
    }
}

// To find a minimum patient name in AVL tree
Node FindMin(AVL_Tree T)
{
    // if the AVL tree is empty
    if( T == NULL )
        return NULL;
    // if the left node in AVL tree is empty
    else if( T->Left == NULL )
        return T;
    //T != NULL && T->Left != NULL
    else
        return FindMin( T->Left );
}

// To find a maximum patient name in AVL tree
Node FindMax(AVL_Tree T)
{
    // if the AVL tree is empty
    if( T == NULL )
        return NULL;
    else if( T != NULL )
    {
        // if the right node in AVL tree is empty
        if( T->Right == NULL )
            return T;
        // if the right node in AVL tree is not empty
        else if( T->Right != NULL )
            T = T->Right;
    }

    return T;
}

int getHeight(AVL_Tree T)
{
    if( T == NULL )
        return -1;
    else
        return T->Height;
}

// To find the maximum height between two nodes
int Max(int x, int y)
{
    // if(x>y) return x; & else return y
    return x > y ? x : y;
}

// To do single rotate left to AVL tree
AVL_Tree SingleRotateWithLeft(AVL_Tree T1)
{
    AVL_Tree  T2;

    T2 = T1->Right;
    T1->Right = T2->Left;
    T2->Left = T1;

    T1->Height = 1 + Max(getHeight(T1->Left), getHeight(T1->Right));
    T2->Height = 1 + Max(getHeight(T2->Right), getHeight(T1));

    return T2;
}

// To do single rotate right to AVL tree
AVL_Tree SingleRotateWithRight(AVL_Tree T1)
{
    AVL_Tree T2;

    T2 = T1->Left;
    T1->Left = T2->Right;
    T2->Right = T1;

    T1->Height = 1 + Max(getHeight(T1->Left), getHeight(T1->Right));
    T2->Height = 1 + Max(getHeight(T2->Left), getHeight(T1));

    return T2;
}

// To do double rotate left to AVL tree
AVL_Tree DoubleRotateWithLeft(AVL_Tree T1)
{
    // Rotate between T1 and T2
    T1->Left = SingleRotateWithLeft(T1->Left);
    return SingleRotateWithRight(T1);
}

// To do double rotate right to AVL tree
AVL_Tree DoubleRotateWithRight(AVL_Tree T1)
{
    // Rotate between T1 and T2
    T1->Right = SingleRotateWithRight(T1->Right);
    return SingleRotateWithLeft(T1);
}

// To insert a one-node tree in AVL tree
AVL_Tree Insert(char Patient_Name[30], char Gender[5], int Date_of_admission, int Date_of_birth, char Illness[20], char Address[20], char Blood_type[3], AVL_Tree T)
{
    // if the AVL tree is empty
    if(T == NULL)
    {
        T = (AVL_Tree) malloc(sizeof (struct AVLnode));
        strcpy(T->Patient_Name, Patient_Name);
        strcpy(T->Gender, Gender);
        T->Date_of_admission = Date_of_admission;
        T->Date_of_birth = Date_of_birth;
        strcpy(T->Illness, Illness);
        strcpy(T->Address, Address);
        strcpy(T->Blood_type, Blood_type);
        T->Height = 0;
        T->Right = T->Left = NULL;

    }
    // Patient_Name < T->Patient_Name
    else if(strcmp(Patient_Name, T->Patient_Name) < 0)
    {
        T->Left = Insert(Patient_Name, Gender, Date_of_admission, Date_of_birth, Illness, Address, Blood_type, T->Left);
        if(getHeight(T->Left) - getHeight(T->Right) >= 2)
        {
            // Patient_Name < T->Left->Patient_Name
            if(strcmp(Patient_Name, T->Left->Patient_Name) < 0)
                T = SingleRotateWithRight(T);
            else
                T = DoubleRotateWithLeft(T);
        }
    }
    // Patient_Name > T->Patient_Name
    else if(strcmp(Patient_Name, T->Patient_Name) > 0)
    {
        T->Right = Insert(Patient_Name, Gender, Date_of_admission, Date_of_birth, Illness, Address, Blood_type, T->Right);
        if(getHeight(T->Right) - getHeight(T->Left) >= 2 )
        {
            // Patient_Name > T->Right->Patient_Name
            if(strcmp(Patient_Name, T->Right->Patient_Name) > 0)
                T = SingleRotateWithLeft(T);
            else
                T = DoubleRotateWithRight(T);
        }
    }
    // if Patient_Name is already in the AVL tree (Don't do anything)

    T->Height = 1 + Max(getHeight(T->Left), getHeight(T->Right));
    return T;
}

// To delete a patient from AVL tree
Node Delete(char Patient_Name[30], AVL_Tree T)
{
    // if the AVL tree is empty
    if(isEmpty(T))
        printf("The Tree is Empty!");

    // else if the AVL tree is not empty

    // A search of patient must be performed to find out if the patient was found or not
    Node searchTheNode = Find(Patient_Name, T);

    // if a patient is not found
    if(searchTheNode == NULL)
    {
        printf("This node was not found in the tree!");
        return NULL;
    }
    // else if a patient is found
    else if(searchTheNode != NULL)
    {

        // Patient_Name < T->Patient_Name
        if(strcmp(Patient_Name, T->Patient_Name) < 0)
        {
            T->Left = Delete(Patient_Name, T->Left);
            if(getHeight(T->Left) - getHeight(T->Right) >= 2)
            {
                // Patient_Name < T->Left->Patient_Name
                if(strcmp(Patient_Name, T->Left->Patient_Name) < 0)
                    T = SingleRotateWithRight(T);
                else
                    T = DoubleRotateWithLeft(T);
            }
        }
        // Patient_Name > T->Patient_Name
        else if(strcmp(Patient_Name, T->Patient_Name) > 0)
        {
            T->Right = Delete(Patient_Name, T->Right);
            if(getHeight(T->Right) - getHeight(T->Left) >= 2 )
            {
                // Patient_Name > T->Right->Patient_Name
                if(strcmp(Patient_Name, T->Right->Patient_Name) > 0)
                    T = SingleRotateWithLeft(T);
                else
                    T = DoubleRotateWithRight(T);
            }
        }
        // Patient_Name = T->Patient_Name
        else
        {
            // if the node has not children (neither left nor right).
            if(T->Left == NULL && T->Right == NULL)
            {
                free(T);
                T = NULL;
            }
            // if the node has one-child (left child).
            else if(T->Left && T->Right == NULL)
            {
                Node swap = T;
                T = T->Left;
                free(swap);
            }
            // if the node has one-child (right child).
            else if(T->Left == NULL && T->Right)
            {
                Node swap = T;
                T = T->Right;
                free(swap);
            }
            // if the node has two-children (left & right children).
            else
            {
                // The minimum value of the patient's name will be searched on the right nodes
                Node MinmumValueInRight = FindMin(T->Right);
                // Then the values ​​in it are placed inside the node to be deleted
                strcpy(T->Patient_Name, MinmumValueInRight->Patient_Name);
                strcpy(T->Gender, MinmumValueInRight->Patient_Name);
                T->Date_of_admission = MinmumValueInRight->Date_of_admission;
                T->Date_of_birth = MinmumValueInRight->Date_of_birth;
                strcpy(T->Illness, MinmumValueInRight->Illness);
                strcpy(T->Address, MinmumValueInRight->Address);
                strcpy(T->Blood_type, MinmumValueInRight->Blood_type);
                // Then delete operation is done
                T->Right = Delete(MinmumValueInRight->Patient_Name, T->Right);
            }
        }
    }
    if(T != NULL)
        T->Height =  Max(getHeight(T->Left), getHeight(T->Right)) - 1;
    return T;
}

// To print all patients have same illness in AVL tree
void PrintSameIllness (char Illness[20], AVL_Tree T)
{

    // if the AVL tree is not empty
    if( T != NULL)
    {

        PrintSameIllness(Illness, T->Left );
        // if AVL tree has another patient with same illness, print the patient name and their illness
        if(strcmp(Illness, T->Illness) == 0)
            printf("Patient Name:%s\n", T->Patient_Name);
        PrintSameIllness(Illness, T->Right );
    }

}

// To read the file patients.txt and load the data in AVL tree
AVL_Tree ReadFromInputFile()
{
    input = fopen("patients.txt", "r");
    AVL_Tree Tree = NULL;

    if(input == NULL)
    {
        printf("Error: Unable to open this file!");
        exit(1);
    }

    char informationOfPatients[300];

    while(fgets(informationOfPatients, 300, input))
    {

        // Patient information will be parted based on #
        char *PatientInformation = strtok(informationOfPatients, "#");

        char Patient_Name[30];
        char Gender[5];
        int Date_of_admission;
        int Date_of_birth;
        char Illness[20];
        char Address[20];
        char Blood_type[3];
        int count = 1;

        while(PatientInformation != NULL)
        {

            switch(count)
            {

            case 1:
                strcpy(Patient_Name, PatientInformation);
                break;

            case 2:
                strcpy(Gender, PatientInformation);
                break;

            case 3:
                Date_of_admission = 0;
                for(int i=0; PatientInformation[i] != '\0'; i++)
                {
                    Date_of_admission = (PatientInformation[i] - 48) + (Date_of_admission * 10);
                }
                break;

            case 4:
                Date_of_birth = 0;
                for(int j=0; PatientInformation[j] != '\0'; j++)
                {
                    Date_of_birth = (PatientInformation[j] - 48) + (Date_of_birth * 10);
                }
                break;

            case 5:
                strcpy(Illness, PatientInformation);
                break;

            case 6:
                strcpy(Address, PatientInformation);
                break;

            case 7:
                strcpy(Blood_type, PatientInformation);
                break;

            }
            count++;
            if(count == 8)
            {
                SIZE+=1; //increment the number of element of hash table which is full
                // To insert the patient information in AVL tree
                Tree = Insert(Patient_Name, Gender, Date_of_admission, Date_of_birth, Illness, Address, Blood_type, Tree);

                count = 1;
            }

            PatientInformation = strtok(NULL, "#");
        }

    }
    fclose(input);
    return Tree;
}

// To print In-Order in the output File
void PrintInOrderInFile(AVL_Tree T)
{
    if(T != NULL)
    {
        PrintInOrderInFile(T->Left);
        fprintf(output,
                "Patient Name:%s, Gender:%s, Date of admission:%d, Date of birth:%d, Illness:%s, Address:%s, Blood type:%s\n",
                T->Patient_Name, T->Gender, T->Date_of_admission, T->Date_of_birth, T->Illness, T->Address, T->Blood_type);
        PrintInOrderInFile(T->Right);
    }
}

// To print Pre-Order in the output File
void PrintPreOrderInFile(AVL_Tree T)
{
    if(T != NULL)
    {
        fprintf(output,
                "Patient Name:%s, Gender:%s, Date of admission:%d, Date of birth:%d, Illness:%s, Address:%s, Blood type:%s\n",
                T->Patient_Name, T->Gender, T->Date_of_admission, T->Date_of_birth, T->Illness, T->Address, T->Blood_type);
        PrintPreOrderInFile(T->Left);
        PrintPreOrderInFile(T->Right);
    }
}

// To print Post-Order in the output File
void PrintPostOrderInFile(AVL_Tree T)
{
    if(T != NULL)
    {
        PrintPostOrderInFile(T->Left);
        PrintPostOrderInFile(T->Right);
        fprintf(output,
                "Patient Name:%s, Gender:%s, Date of admission:%d, Date of birth:%d, Illness:%s, Address:%s, Blood type:%s\n",
                T->Patient_Name, T->Gender, T->Date_of_admission, T->Date_of_birth, T->Illness, T->Address, T->Blood_type);
    }
}

// To save all patients in file “patients_hash.data”
void PrintInOutputFile(AVL_Tree T)
{
    output = fopen("patients_hash.data", "w");
    if (T == NULL)
        fprintf(output, "ERROR: The Tree is Empty!\n");
    else
    {
        // Printing in the file in alphabetical order in ascending order of the names of the patients.
        fprintf(output, "\nIn-order print to see the elements:\n");
        PrintInOrderInFile(T);

        fprintf(output,"\n------------------------------------------------------------------------------------------------------------------");

        fprintf(output, "\nPre-order print to see the elements:\n");

        PrintPostOrderInFile(T);

        fprintf(output,"\n------------------------------------------------------------------------------------------------------------------");

        fprintf(output, "\nPost-order print to see the elements:\n");
        PrintPostOrderInFile(T);

        fprintf(output,"\n------------------------------------------------------------------------------------------------------------------\n");
    }
}

//in-order print to see the elements
void PrintInOrder(AVL_Tree T)
{
    if(T != NULL)
    {
        PrintInOrder(T->Left );
        printf("Patient Name:%s, Gender:%s, Date of admission:%d, Date of birth:%d, Illness:%s, Address:%s, Blood type:%s\n"
               , T->Patient_Name, T->Gender, T->Date_of_admission, T->Date_of_birth, T->Illness, T->Address, T->Blood_type);
        PrintInOrder( T->Right );
    }
}

//pre-order print to see the elements
void PrintPreOrder(AVL_Tree T)
{
    if(T != NULL)
    {
        printf("Patient Name:%s, Gender:%s, Date of admission:%d, Date of birth:%d, Illness:%s, Address:%s, Blood type:%s\n"
               , T->Patient_Name, T->Gender, T->Date_of_admission, T->Date_of_birth, T->Illness, T->Address, T->Blood_type);
        PrintPreOrder(T->Left );
        PrintPreOrder( T->Right );
    }
}

//post-order print to see the elements
void PrintPostOrder(AVL_Tree T)
{
    if(T != NULL)
    {
        PrintPreOrder(T->Left );
        PrintPreOrder( T->Right );
        printf("Patient Name:%s, Gender:%s, Date of admission:%d, Date of birth:%d, Illness:%s, Address:%s, Blood type:%s\n"
               , T->Patient_Name, T->Gender, T->Date_of_admission, T->Date_of_birth, T->Illness, T->Address, T->Blood_type);
    }
}

/*
 To  create a Hash Table using the patients’ data of the previous step
*/

#define EMPTY 0 //if this part in hash table is empty, then the status is 0
#define INSERT 1 //if this part in hash table has patient information, then the status is 1
#define DELETE 2 //if this part in hash table is delete a patient information, then the status is 2

typedef struct PatientData Data;
typedef struct hashTable HT;

struct PatientData
{
    char key[30]; //Patient Name
    char Gender[5]; //Gender
    int Date_of_admission; //Date of admission
    int Date_of_birth; //Date of birth
    char Illness[20]; //Illness
    char Address[20]; //Address
    char Blood_type[3]; //Blood type
    int status; //status in hash table
};

struct hashTable
{
    int size;
    int numOfPatientsData;
    Data *PatientsData;
};

void Rehashing(HT *);
void InsertINHashTable( HT *, Data);
int requiredTableSize(int);
int QuadraticProbing(HT, char[30] );
int hashKey(HT, char[30] );
int findPatientData(HT, char[30] );
void deleteFromTable(HT, char[30] );
void MoveDataToHash(HT*, AVL_Tree );
void printTable(HT table);
void PrintInOutputFile1(HT table);

int main()
{

    char Patient_Name[30];
    char Gender[5];
    int Date_of_admission;
    int Date_of_birth;
    char Illness[20];
    char Address[20];
    char Blood_type[3];
    AVL_Tree Tree = NULL;

    char Data1[30];
    char Data2[5];
    int Date1;
    int Date2;
    char Data3[20];
    char Data4[20];
    char Data5[3];

    // To read the file patients.txt and load the data in AVL tree
    Tree = ReadFromInputFile();


    int choice = 0;
    do
    {
        printf("\nMENU:\n");
        printf("1- Please insert a new patient with all its associated data.\n");
        printf("2- Find a patient and give the user the option to update the information of the patient if found.\n");
        printf("3- List all patients in lexicographic order with their associated information.\n");
        printf("4- List all patients that have the same illness, after enter the name of illness.\n");
        printf("5- Delete a patient from the system.\n");
        printf("6- Save all patients in file (patients_hash.data).\n");
        printf("7- Exit the system.\n");
        printf("Please enter The number of choice:");
        scanf("%d", &choice);

        // Insert a new patient from user with all its associated data
        if(choice == 1)
        {
            printf("Patient Name:");
            scanf("%s",&Patient_Name);
            printf("Gender:");
            scanf("%s",&Gender);
            printf("Date of admission:");
            scanf("%d",&Date_of_admission);
            printf("Date of birth:");
            scanf("%d",&Date_of_birth);
            printf("Illness:");
            scanf("%s",&Illness);
            printf("Address:");
            scanf("%s",&Address);
            printf("Blood type:");
            scanf("%s",&Blood_type);
            SIZE+=1; //increment the number of element of hash table which is full
            // To insert the new patient information in AVL tree
            Insert(Patient_Name, Gender, Date_of_admission, Date_of_birth, Illness, Address, Blood_type, Tree);
            printf("\n");
        }

        //Find a patient and give the user the option to update the information of the patient if found
        else if(choice == 2)
        {
            printf("Please enter Patient Name you want to find:");
            scanf("%s", &Data1);

            // A search of patient must be performed to find out if the patient was found or not
            Node searchPatient = Find(Data1, Tree);

            int updateChoice = 0;
            // if a patient was found
            if(searchPatient != NULL)
            {
                while(1)
                {
                    printf("\nMENU for details patient:\n");
                    printf("1-Update patient name (current value : %s)\n", searchPatient->Patient_Name);
                    printf("2-Update patient gender (current value : %s)\n", searchPatient->Gender);
                    printf("3-Update patient date of admission (current value : %d)\n",
                           searchPatient->Date_of_admission);
                    printf("4-Update patient date of birth (current value : %d)\n", searchPatient->Date_of_birth);
                    printf("5-Update patient illness (current value : %s)\n", searchPatient->Illness);
                    printf("6-Update patient address (current value : %s)\n", searchPatient->Address);
                    printf("7-Update patient blood type (current value : %s)\n", searchPatient->Blood_type);
                    printf("8- Exit the system.\n");
                    printf("Please enter the number of choice you want to update it:");
                    scanf("%d", &updateChoice);

                    if (updateChoice == 8)
                        break;

                    switch (updateChoice)
                    {
                    case 1:
                        printf("Enter patient name:");
                        scanf("%s", &searchPatient->Patient_Name);
                        break;
                    case 2:
                        printf("Enter patient gender:");
                        scanf("%s", &searchPatient->Gender);
                        break;
                    case 3:
                        printf("Enter patient Date_of_admission:");
                        scanf("%d", &searchPatient->Date_of_admission);
                        break;
                    case 4:
                        printf("Enter patient Date_of_birth:");
                        scanf("%d", &searchPatient->Date_of_birth);
                        break;
                    case 5:
                        printf("Enter patient Illness:");
                        scanf("%s", &searchPatient->Illness);
                        break;
                    case 6:
                        printf("Enter patient Address:");
                        scanf("%s", &searchPatient->Address);
                        break;
                    case 7:
                        printf("Enter patient Blood_type:");
                        scanf("%s", &searchPatient->Blood_type);
                        break;
                    case 8:
                        printf("Enter patient gender:");
                        scanf("%s", &searchPatient->Gender);
                        break;
                    }
                }
                printf("\n");
            }
        }

        //List all patients in lexicographic order with their associated information
        else if (choice == 3)
        {
            //in-order print to see the elements
            PrintInOrder(Tree);
            printf("\n");
        }

        //List all patients that have the same illness
        else if (choice == 4)
        {
            //The user must enter the name of the disease that he/she wants to know the names of patients who suffer from it
            printf("Please enter the name of illness:\n");
            scanf("%s", Data3);
            // To print all patients have same illness in AVL tree
            PrintSameIllness (Data3, Tree);
            printf("\n");
        }

        //Delete a patient from the system
        else if (choice == 5)
        {
            //The user must enter the name of the patient that he/she wants to delete it
            printf("Patient Name:");
            scanf("%s",  &Data1);
            // To delete a patient from AVL tree
            Delete(Data1, Tree);
            SIZE--; //decrement the number of element of hash table which is full
            printf("The patient has been deleted.\n");
        }

        //Save all words in file “patients_hash.data”
        else if (choice == 6)
            PrintInOutputFile(Tree);
    }
    while(choice != 7); //Exit the system

    printf("-------------------------------------------------------------------------------------------------------------------------\n");

    HT table = {0, 0, NULL}; //size=0, numOfPatientsData=0, PatientsData=NULL
    table.size =requiredTableSize(SIZE);
    table.numOfPatientsData = 0;
    free(table.PatientsData);
    table.PatientsData = NULL;

    table.PatientsData = (Data *) calloc((table).size, sizeof(Data));
    MoveDataToHash(&table, Tree);

    while(1)
    {
        printf("\nMENU:\n");
        printf("1-Print hashed table (print the entire table to the screen including empty spots).\n");
        printf("2-Print out table size.\n");
        printf("3-Print out the used hash function.\n");
        printf("4-Insert a new PatientData into the hash table.\n");
        printf("5-Search for a specific patient\n");
        printf("6-Delete for a specific patient\n");
        printf("7-Save hash table back to file.\n");
        printf("8- Exit the system.\n");
        printf("Please enter the number of choice:");
        scanf("%d", &choice);

        if (choice == 8)
            break;

        switch (choice)
        {
        case 1:
            //Print hashed table (i.e., print the entire table to the screen including empty spots)
            printf("Print hashed table:\n");
            printTable(table);
            break;

        case 2:
            //Print out table size
            printf("\nPrint out table size: %d\n",table.size);
            printf("\n");
            break;

        case 3:
            //Print out the used hash function.
            printf("\nPrint out the used hash function:\n");
            printf("unsigned long hashKey(char *key){\nreturn (( key[0] + 27 * key[1] + 729 * key[2] ) %% %d );\n}\n",table.size);
            printf("\nPrint out the used Collision Resolution Techniques (Open Addressing 'Quadratic probing (nonlinear search)'),quadratic hash function:\n");
            printf("f(x) = (h(x) + i*i) %% %d = (x %% %d + i*i) %% %d\n",table.size, table.size, table.size);
            printf("\n");
            break;

        case 4:
            //Insert a new record into the hash table
            printf("Insert a new PatientData into the hash table:\n");
            Data PatientData;
            char namepatient[30];
            printf("Patient Name:");
            scanf("%s", PatientData.key);
            printf("Gender:");
            scanf("%s", &PatientData.Gender);
            printf("Date of admission:");
            scanf("%d", &PatientData.Date_of_admission);
            printf("Date of birth:");
            scanf("%d", &PatientData.Date_of_birth);
            printf("Illness:");
            scanf("%s", &PatientData.Illness);
            printf("Address:");
            scanf("%s", &PatientData.Address);
            printf("Blood type:");
            scanf("%s", &PatientData.Blood_type);
            // To insert a new patient data in hash table
            InsertINHashTable(&table, PatientData);
            break;

        case 5:
            //Search for a specific patient
            printf("Search for a specific patient:\n");
            printf("Please enter Patient Name:");
            char* keyFind;
            scanf("%s", &keyFind);

            int key = findPatientData(table, &keyFind);
            if (key != -1) //if this patient is exist, print their data
            {

                //printing PatientData's data
                printf("\nPatient Data has been found:\n");
                printf("key = %s\n",table.PatientsData[key].key);
                printf("gender = %s\n",table.PatientsData[key].Gender);
                printf("Blood_type = %s\n",table.PatientsData[key].Blood_type);
                printf("Address = %s\n",table.PatientsData[key].Address);
                printf("Illness = %s\n",table.PatientsData[key].Illness);
                printf("Date_of_birth = %d\n",table.PatientsData[key].Date_of_birth);
                printf("Date_of_admission = %d\n",table.PatientsData[key].Date_of_admission);
            }
            else // if this patient is not found
                printf("ERROR: This patient is not found!");
            break;

        case 6:
            //Delete a specific record
            printf("Delete a specific Patient data:\n");
            printf("Please enter Patient Name:");
            char* keyFindDelete;
            scanf("%s", &keyFindDelete);
            deleteFromTable(table, &keyFindDelete);

            printf("\nPatient data deleted successfully.\n");
            break;

        case 7:
            //Save hash table back to file
            printf("Finally, save hash table back to file.");
            //print all patients in file “patients_hash.data”
            PrintInOutputFile1(table);
            break;
        }
    }
    printf("\n");

    return 0;
}

// To check if the size of hash table is prime number or not
int isPrimeNumber(int table_size)
{
    if(table_size==1 || table_size==0)
        return 0;
    for(int i=2; i<=table_size/2; i++)
    {
        if(table_size%i == 0)
            return 0;
    }
    return 1;
}

// To return the value of table size
int requiredTableSize(int n)
{

    int requiredTableSize = n /0.7; // Because Load factors (𝜆) should not exceed 0.7
    if(requiredTableSize%2 ==0)
        requiredTableSize++;
    while(!isPrimeNumber(requiredTableSize))
        requiredTableSize++;

    return requiredTableSize;
}

// To double the hash table size & re-insert the patient data
void Rehashing(HT *table)
{

    int oldTableSize = (*table).size; // The value of old table size
    int newTableSize = requiredTableSize(oldTableSize); // The value of new table size
    (*table).size = newTableSize;

    Data *temp = (*table).PatientsData;
    // allocates memory as requested, initialized it to zero, and returns a pointer to it.
    (*table).PatientsData = (Data *) calloc(newTableSize, sizeof(Data));

    for (int i = 0; i < oldTableSize; i++)
        if( temp[i].status == INSERT)
            // To insert all patients data in hash table
            InsertINHashTable(table, temp[i]);
    free(temp);
}

// if the event of a collision, Quadratic probing is used
int QuadraticProbing(HT table, char key[30])
{

    int i = 1;
    int index = hashKey(table, key);
    int quadIndex = index;

    while(table.PatientsData!= NULL && table.PatientsData[quadIndex].status == INSERT)
    {
        quadIndex = (index + i*i) % table.size;
        i++;
    }
    return quadIndex;
}

// To find the value of key by Separate Chaining with String Keys
int hashKey(HT table, char key[30])
{
    //if the patient name have only one char
    if(key[1]<0)
        key[1]=1;
    //if the patient name have only two char
    if(key[2]<0)
        key[2]=1;
    //if the patient name have three or more char
    return (( key[0] + 27 * key[1] + 729 * key[2] ) % (table).size );
}

// To create a Hash Table using the patients’ data of the previous step
void MoveDataToHash(HT* table, AVL_Tree T)
{
    if(T != NULL)
    {
        MoveDataToHash(table,T->Left );
        Data PatientData;
        strcpy(PatientData.key, T->Patient_Name);
        strcpy(PatientData.Gender, T->Gender);
        PatientData.Date_of_admission =T->Date_of_admission;
        PatientData.Date_of_birth,T->Date_of_birth;
        strcpy(PatientData.Illness, T->Illness);
        strcpy(PatientData.Address, T->Address);
        strcpy( PatientData.Blood_type, T->Blood_type);
        InsertINHashTable(table, PatientData);
        MoveDataToHash( table,T->Right );
    }
}

// To insert a patient data in hash table
void InsertINHashTable( HT *table, Data PatientData)
{
    (*table).numOfPatientsData++; //increment the number of patient data in hash table
    if ( (*table).size < requiredTableSize( (*table).numOfPatientsData ) )
        Rehashing(table); //double the hash table size & re-insert the patient data
    PatientData.status = INSERT;
    int index = QuadraticProbing(*table, PatientData.key);
    (*table).PatientsData[index] = PatientData;

}

// To find a specific record in hash table
int findPatientData(HT table, char key[30])
{

    int i = 1;
    int index = hashKey(table, key);
    int quadIndex = index;
    while(table.PatientsData[quadIndex].status != EMPTY)
    {
        if (table.PatientsData[quadIndex].status != DELETE && strcmp( table.PatientsData[quadIndex].key, key) == 0)
            return quadIndex;
        else
        {
            quadIndex = (index + i*i) % table.size;
            i++;
        }
    }
    return -1;
}

// To delete a specific record from hash table
void deleteFromTable(HT table, char key[30])
{

    int index = findPatientData(table, key);

    if (index != -1)
        table.PatientsData[index].status = DELETE;
}

void printTable(HT table)
{
    for(int i = 0 ; i < table.size ; i++)
    {
        if (table.PatientsData[i].status != EMPTY)
        {
            if(table.PatientsData[i].status == 1)
                printf("(Index:%d),(status = INSERTED = 1):Patient name:%s, Gender:%s, Date of admission:%d, Date of birth:%d, Illness:%s, Address:%s, Blood type:%s\n"
                       ,i, table.PatientsData[i].key, table.PatientsData[i].Gender, table.PatientsData[i].Date_of_admission, table.PatientsData[i].Date_of_birth,
                       table.PatientsData[i].Illness,table.PatientsData[i].Address, table.PatientsData[i].Blood_type);
            else
                printf("(Index:%d),(status = DELETED = 2):Patient name:%s, Gender:%s, Date of admission:%d, Date of birth:%d, Illness:%s, Address:%s, Blood type:%s\n"
                       ,i, table.PatientsData[i].key, table.PatientsData[i].Gender, table.PatientsData[i].Date_of_admission, table.PatientsData[i].Date_of_birth,
                       table.PatientsData[i].Illness,table.PatientsData[i].Address, table.PatientsData[i].Blood_type);
        }
        else
            printf("(Index:%d), (status = EMPTY = 0 )\n\n", i);
    }
}

// To save all patients in file “patients_hash.data”
void PrintInOutputFile1(HT table)
{
    for(int i = 0 ; i < table.size ; i++)
    {
        if (table.PatientsData[i].status != EMPTY)
        {
            if(table.PatientsData[i].status == 1)
                fprintf(output,"(Index:%d),(status = INSERTED = 1):Patient name:%s, Gender:%s, Date of admission:%d, Date of birth:%d, Illness:%s, Address:%s, Blood type:%s\n"
                        ,i, table.PatientsData[i].key, table.PatientsData[i].Gender, table.PatientsData[i].Date_of_admission, table.PatientsData[i].Date_of_birth,
                        table.PatientsData[i].Illness,table.PatientsData[i].Address, table.PatientsData[i].Blood_type);
            else
                fprintf(output,"(Index:%d),(status = DELETED = 2):Patient name:%s, Gender:%s, Date of admission:%d, Date of birth:%d, Illness:%s, Address:%s, Blood type:%s\n"
                        ,i, table.PatientsData[i].key, table.PatientsData[i].Gender, table.PatientsData[i].Date_of_admission, table.PatientsData[i].Date_of_birth,
                        table.PatientsData[i].Illness,table.PatientsData[i].Address, table.PatientsData[i].Blood_type);
        }
        // else if (table.PatientsData[i].status == EMPTY)
        else
            fprintf(output,"(Index:%d),(status = EMPTY = 0 )\n\n", i);
    }
    fclose(output);
}
