#include <stdio.h>
#include <stdlib.h>

//TA INSTRUCTION: table size 23

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order;
};



// Fill out this structure
struct HashType
{
    struct RecordType record;
    struct HashType *next;
};

// Compute the hash function
int hash(int x)
{
    return x % 23;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	int i, a, c;
	char b;

	for (i=0;i<hashSz;++i)
	{
		// if index is occupied with any records, print all
		a = pHashArray->record.id;
		b = pHashArray->record.name;
		c = pHashArray->record.order;

		if(pHashArray->record.id != NULL)
		{
			printf("Index %d ->", i);
			printf("%d, %c, %d", a, b, c);

			while(pHashArray->record.id == pHashArray->next->record.id)
				printf(" -> %d, %c, %d", a, b, c);
			printf("\n");
		}
		pHashArray = pHashArray->next;
	}
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);
	// Your hash implementation
	struct HashType *pHash = (struct HashType*) malloc(sizeof(struct HashType) * 23);
	for(int i = 0; i < 23; i++)
    {
        pHash[i].next = NULL;
        
		pHash[i].record.id = NULL;
		pHash[i].record.name = NULL;
		pHash[i].record.order = NULL;
	}


    for(int i = 0; i < recordSz; i++)
    {
        int hashnum = hash(pRecords[i].id);

        if(pHash[hashnum].record.id != NULL)
        {
            struct HashType curHash = pHash[hashnum];
            while(curHash.next != NULL)
            {
                curHash = *curHash.next;
            }
        }
        else
        {
            pHash[hashnum].record = pRecords[i];
        }

        displayRecordsInHash(&pHash, 23);
        }
    }
