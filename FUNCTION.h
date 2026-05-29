#ifndef FUNCTION_H
#define FUNCTION_H

typedef struct VOCAL{
    char Word[50];
    char Pronoun[50];
    char Type[20];
    char Meaning[100];
    char Level[20];
    char Topic[20];
    struct VOCAL* next;
} VOCAL;

void toLowerCase(char* str);
VOCAL* createNode(char* word, char* pronoun, char* type, char* meaning, char* level, char* topic);
void AddNode(VOCAL** head, char* word, char* pronoun, char* type, char* meaning, char* level, char* topic);
void FreeVOCALList(VOCAL* head);
void LoadFile(VOCAL** head);

                                                                                                                                                                                    

#endif