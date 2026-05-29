#ifndef MODE_3_H
#define MODE_3_H

typedef struct Quiz {
    int ID;
    char Question[50];
    char Answer[200];
    char UserAnswer[50];
    char Status[20];
    struct Quiz* next;
} Quiz;  

Quiz* createQuizNode(int ID, char* question, char* answer , char* userAnswer,char *status);
void addQuizNode(Quiz** head, int ID ,char* question, char* answer , char* userAnswer,char *status);
void FreeQuizList(Quiz* head);
void printBorder(int width);
void printBorderDouble(int width);
void printBoxLine(const char* content, int width);
void fprintBorderDouble(FILE* f, int width);
void fprintBorder(FILE* f, int width);
void showExportLoading();
void ReviewAnswers(Quiz* head,int score, int numWords);
void playGame();
#endif