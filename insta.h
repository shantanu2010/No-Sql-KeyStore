#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct Cell{
	char *value = 0;
	int version = 0;
	Cell *next;
}Cell;

typedef struct Columns{
	char *name = 0;
	Cell *cell;
	Columns *next;
}Columns;

typedef struct Rows{
	Columns *columns;
	int rowId = 0;
	int commitVersion = 0;
	int current;
	int lock;
	Rows *next;
}Rows;

typedef struct tables{
	char * tablename;
	struct Rows *rowHead;
	struct tables*next;
}Tables;

struct tables* table = NULL;
int nooftables = -1;


void addTable(char* c){

	
	struct tables* tempTable = (struct tables*)malloc(sizeof(struct tables));
	tempTable->tablename = (char *)malloc(100 * sizeof(char));
	strcpy(tempTable->tablename, c);
	tempTable->rowHead = NULL;
	tempTable->next = NULL;
	if (table == NULL){

		table = tempTable;
	}

	else{
		struct tables* t = table;
		while (t->next != NULL){

			t = t->next;
		}

		t->next = tempTable;

	}
}
struct tables* getTablePointer(char *tablename){


	struct tables* temp = table;

	while (temp != NULL){

		if (strcmp(temp->tablename, tablename) == 0)
			return temp;

		temp = temp->next;
	}

	return NULL;
}

void exportToFile(){

	struct tables* temp = table;

	FILE* file = NULL;
	while (temp != NULL){

		file = fopen(temp->tablename, "a");

	}

}

void dropTable(){

	char buf[256];
	printf("\nEnter table that need to be dropped : ");
	scanf(" %s", buf);

	struct tables* temp = table;
	struct tables* prev = NULL;

	if (temp != NULL && (strcmp(temp->tablename, buf) == 0)){

		table = temp->next;
		printf("\nDatabase Dropped\n");
		free(temp);
		return;
	}

	while (temp != NULL && (strcmp(temp->tablename, buf) == 0)){

		prev = temp;
		temp = temp->next;
	}


	if (temp == NULL){
		printf("\nDatabase doesnot exists\n");
		return;
	}

	else{
		prev->next = temp->next;
		printf("\nDatabase Dropped\n");
		free(temp);
	}
}
