#define STRING_SIZE 255
#define MIN_SIZE 10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "StructureFile.h"



void putData(struct tables * t, char **columnNames, char **values, int index, int id){

	Rows *tempRowNode = t->rowHead;
	while (tempRowNode != NULL){
		//printf("%d", tempRowNode->rowId);

		if (tempRowNode->rowId == id){
			for (int i = 0; i < index; ++i)
				tempRowNode->columns = getColumnHead(tempRowNode->columns, columnNames[i], values[i]);
		}
		tempRowNode = tempRowNode->next;
	}



	tempRowNode = t->rowHead;
	Rows *newRowNode = createRowNode();
	for (int i = 0; i < index; ++i){
		newRowNode->columns = getColumnHead(newRowNode->columns, columnNames[i], values[i]);
	}
	if (t->rowHead == NULL){
		newRowNode->rowId = 1;
		newRowNode->commitVersion = 1;
		//appendToAnotherTable(newRowNode->rowId);
		t->rowHead = newRowNode;
	}
	else{
		while (tempRowNode->next != NULL){
			tempRowNode = tempRowNode->next;
		}
		newRowNode->rowId = tempRowNode->rowId + 1;
		//appendToAnotherTable(newRowNode->rowId);
		newRowNode->commitVersion = getCommitVersion(newRowNode);
		tempRowNode->next = newRowNode;
	}
}

void getData(struct tables * t, int id){
	Rows *tempNode = t->rowHead;
	int flag = 1;
	while (tempNode != NULL){
		if (tempNode->rowId == id){
			printDetails(tempNode);
			flag = 0;
			break;
		}
		tempNode = tempNode->next;
	}
	if (flag)
		printf("\n%d id not found", id);
}


void deleteData(struct tables * t, int id){

	Rows **tempNode1 = &t->rowHead, *prevNode = t->rowHead;
	Rows *tempNode = *tempNode1;

	if (tempNode->rowId == id){

		t->rowHead = tempNode->next;
	}

	while (tempNode != NULL){
		if (tempNode->rowId != id){
			prevNode->next = tempNode->next;
			free(tempNode);
			break;
		}
		prevNode = tempNode;
		tempNode = tempNode->next;
	}
}


