#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "FUNCTION.h"

void toLowerCase(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

VOCAL* createNode(char* word, char* pronoun, char* type, char* meaning, char* level, char* topic) {
    VOCAL* newNode = (VOCAL*)malloc(sizeof(VOCAL));
    if (newNode == NULL) {
        printf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    strncpy(newNode->Word, word, sizeof(newNode->Word) - 1);
    newNode->Word[sizeof(newNode->Word) - 1] = '\0';
    strncpy(newNode->Pronoun, pronoun, sizeof(newNode->Pronoun) - 1);
    newNode->Pronoun[sizeof(newNode->Pronoun) - 1] = '\0';
    strncpy(newNode->Type, type, sizeof(newNode->Type) - 1);
    newNode->Type[sizeof(newNode->Type) - 1] = '\0';
    strncpy(newNode->Meaning, meaning, sizeof(newNode->Meaning) - 1);
    newNode->Meaning[sizeof(newNode->Meaning) - 1] = '\0';
    strncpy(newNode->Level, level, sizeof(newNode->Level) - 1);
    newNode->Level[sizeof(newNode->Level) - 1] = '\0';
    strncpy(newNode->Topic, topic, sizeof(newNode->Topic) - 1);
    newNode->Topic[sizeof(newNode->Topic) - 1] = '\0';
    newNode->next = NULL;
    return newNode;
}

void AddNode(VOCAL** head, char* name, char* pronoun, char* type, char* meaning, char* level, char* topic) {
    VOCAL* newNode = createNode(name, pronoun, type, meaning, level, topic);
    if (*head == NULL) {
        *head = newNode;
    } else {
        VOCAL* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void FreeVOCALList(VOCAL* head) {
    VOCAL* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void LoadFile(VOCAL** head) {
    FILE* file = fopen("vocal_data.txt", "r");
    if (file == NULL) {
        printf(stderr, "Could not open file %s\n", "vocal_data.txt");
        exit(1);
    }
    char line[1000];
    while (fgets(line, sizeof(line), file)) {
        char *Word  = strtok(line, ",");
        char *Pronoun = strtok(NULL, ",");
        char *Type = strtok(NULL, ",");
        char *Meaning = strtok(NULL, ",");
        char *Level = strtok(NULL, ",");
        char *Topic = strtok(NULL, ",");
        AddNode(head, Word, Pronoun, Type, Meaning, Level, Topic);
    }
    fclose(file);
}
