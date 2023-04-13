#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType {
    int id;
    char name;
    int order;
    // next record
    struct RecordType* next;
};

// Fill out this structure
struct HashType {
    // number of records in the array
    int size;
    //array of records
    struct RecordType* table;
};

// Compute the hash function
int hash(int x, int tableSize) {
    return x % tableSize;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData) {
    FILE* inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType* pRecord;
    *ppData = NULL;

    if (inFile) {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType*)malloc(sizeof(struct RecordType) * dataSz);
        // Implement parse data block
        if (*ppData == NULL) {
            printf("Cannot allocate memory\n");
            exit(-1);
        }
        for (i = 0; i < dataSz; ++i) {
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, "%c ", &c);
            pRecord->name = c;
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
            pRecord->next = NULL;
        }

        fclose(inFile);
    }

    return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz) {
    int i;
    printf("\nRecords:\n");
    for (i = 0; i < dataSz; ++i) {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType* pHashArray, int hashSz) {
    for (int i = 0;i < hashSz;i++) {
        printf("Index %d -> ", i);
        struct RecordType* temp = pHashArray[i].table;
        if (temp != NULL) {
            while (temp != NULL) {
                printf(" %d, %c, %d ", temp->id, temp->name, temp->order);
                if (temp->next == NULL) {
                    printf("-> NULL");
                }
                temp = temp->next;
            }
            printf("\n");
        }
    }
}

void insertRecord(struct HashType* hashTable, struct RecordType* record, int tableSize) {
    // Implement insertRecord
    int index = hash(record->id, tableSize);
    struct RecordType* temp = hashTable[index].table;
    if (temp == NULL) {
        hashTable[index].table = record;
    }
    else {
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = record;
    }
}

int main(void) {
    struct RecordType* pRecords;
    int recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);
    int hashTableSz = 11;
    // Your hash implementation
    struct HashType* hashTable = (struct HashType*)malloc(sizeof(struct HashType) * hashTableSz);
    for (int i = 0; i < recordSz; i++) {
        hashTable[i].table = NULL;
    }
    for (int i = 0; i < recordSz; i++) {
        insertRecord(hashTable, &pRecords[i], hashTableSz);
    }
    printf("\n~~~~~Hash Table~~~~~\n");
    displayRecordsInHash(hashTable, hashTableSz);
    free(hashTable);
    free(pRecords);
    return 0;
}
