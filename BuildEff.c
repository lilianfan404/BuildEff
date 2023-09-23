#include<stdio.h> 
#include<stdlib.h> 
#include <string.h>
#define MAX_BUILDINGS 100
#define MAX_NAME 64
  


typedef struct Building{
    char BuildingName[MAX_NAME];
    int SquareFootage;
    float ElectricityUsed;
    double Efficiency;
    struct Building* next;
}bd;

typedef struct Node 
{ 
    struct Building* data;
    struct Node* next;

}node; 

void bubbleSort(struct Node *start); 

void freeList(struct Node *start);
  
/* Function to swap data of two nodes a and b*/
void swap(struct Node *a, struct Node *b); 
  
/* Function to print nodes in a given linked list */
void printList(struct Node *start); 
  
node* getBuildingList(FILE *file){
    node *i = (node*)malloc(sizeof(node));
    i->data = (bd*)malloc(sizeof(bd));
    if (i == NULL || i->data == NULL) {
    // Handle memory allocation failure
    free(i);
    fclose(file);
    return NULL;
    }
    int fileRead = fscanf(file, "%s\n%d\n%f\n", i->data->BuildingName, &i->data->SquareFootage, &i->data->ElectricityUsed);
    if (fileRead == 3){
        if (i->data->SquareFootage < 0 || i->data->ElectricityUsed < 0){
            printf("Error: invalid file format\n");
            free (i);
            return NULL;
        }

        if (i->data->SquareFootage == 0){
            i->data->Efficiency = 0;
        }

        else if (i->data->ElectricityUsed == 0){
            i->data->Efficiency = 0;
        }

        else {
            i->data->Efficiency = i->data->ElectricityUsed / i->data->SquareFootage;

            i->next = NULL;
        }


    }
    else if (fileRead == 1 && strcmp(i->data->BuildingName, "DONE") == 0) {
        free(i->data);
        free(i);
        return NULL;
    }
    i->next = getBuildingList(file);
    return i;
}
    
/*int main(int argc, char *argv[]) 
{ 
    if (argc != 2) {
        printf("Usage: ./buildEff <number>\n");
        return 0;
    }
    
    FILE *fptr = fopen(argv[1], "r");
    
    if (fptr == NULL){
        printf("Error: file not found\n");
        return 0;
    }


    struct Node *start = getBuildingList(fptr);


    //int arr[] = {12, 56, 2, 11, 1, 90}; 
    //int list_size, i; 
    //int arr[MAX_BUILDINGS];



  if (start != NULL) {
    bubbleSort(start);
    printList(start);
}
    return 0; 
} 
*/

int main(int argc, char *argv[]) 
{ 
    if (argc != 2) {
        printf("Usage: ./buildEff <number>\n");
        return 0;
    }
    
    FILE *fptr = fopen(argv[1], "r");
    
    if (fptr == NULL){
        printf("Error: file not found\n");
        return 0;
    }

    // Check if the file is empty or the first word is "DONE"
    char firstWord[MAX_NAME];
    if (fscanf(fptr, "%63s", firstWord) != 1 || strcmp(firstWord, "DONE") == 0) {
        printf("BUILDING FILE IS EMPTY\n");
        fclose(fptr);
        return 0;
    }

    // Rewind the file to start reading from the beginning
    rewind(fptr);

    struct Node *start = getBuildingList(fptr);
    
    if (start != NULL) {
        bubbleSort(start);
        printList(start);
        freeList(start);
    } else {
        printf("BUILDING FILE IS EMPTY\n");
    }

    fclose(fptr);
    return 0; 
}


  
/* Function to insert a node at the beginning of a linked list */
/*void insertAtTheBegin(struct Node **start_ref, struct Building data) 
{ 
    struct Node *ptr1 = (struct Node*)malloc(sizeof(struct Node)); 
    ptr1->data = &data; 
    ptr1->next = *start_ref; 
    *start_ref = ptr1; 
} 
*/
  
/* Function to print nodes in a given linked list */
void printList(struct Node *start) 
{ 
    struct Node *temp = start;  
    while (temp!=NULL) 
    { 
       // printf("%d ", temp->data); 
        printf("%s %.6f\n", temp->data->BuildingName, temp->data->Efficiency); 
        temp = temp->next; 
    } 
} 
  
/* Bubble sort the given linked list */
void bubbleSort(struct Node *start) 
{ 
    int swapped, i; 
    struct Node *ptr1; 
    struct Node *lptr = NULL; 
  
    /* Checking for empty list */
    if (start == NULL) 
        return; 
  
    do
    { 
        swapped = 0; 
        ptr1 = start; 
  
        while (ptr1->next != lptr) 
        { 
            //if (ptr1->data > ptr1->next->data) 
            if (ptr1->data->Efficiency < ptr1->next->data->Efficiency) 
            { 
                swap(ptr1, ptr1->next); 
                swapped = 1; 
            } 
            else if (ptr1->data->Efficiency == ptr1->next->data->Efficiency){
                if (strcmp(ptr1->data->BuildingName, ptr1->next->data->BuildingName) > 0){
                    swap(ptr1, ptr1->next);
                    swapped = 1;
                }
            }
            ptr1 = ptr1->next; 
        } 
        lptr = ptr1; 
    } 
    while (swapped); 
} 

void freeList(struct Node *start) {
    while (start != NULL) {
        struct Node *temp = start;
        start = start->next;
        free(temp->data); // free the building structure
        free(temp); // free the node
    }
}

/* function to swap data of two nodes a and b*/
void swap(struct Node *a, struct Node *b) 
{ 
    struct Building* temp = a->data; 
    a->data = b->data; 
    b->data = temp; 
} 