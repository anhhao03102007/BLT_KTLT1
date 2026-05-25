#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "MODE_3.h"
#include "FUNCTION.h"

Quiz* createQuizNode(int ID, char* question, char* answer, char* userAnswer, char* Mode) {
    Quiz* newNode = (Quiz*)malloc(sizeof(Quiz));
    if (newNode != NULL) {
        newNode->ID = ID;
        strncpy(newNode->Question, question, sizeof(newNode->Question) - 1);
        newNode->Question[sizeof(newNode->Question) - 1] = '\0'; // Ensure null-termination
        strncpy(newNode->Answer, answer, sizeof(newNode->Answer) - 1);
        newNode->Answer[sizeof(newNode->Answer) - 1] = '\0'; // Ensure null-termination
        strncpy(newNode->UserAnswer, userAnswer, sizeof(newNode->UserAnswer) - 1);
        newNode->UserAnswer[sizeof(newNode->UserAnswer) - 1] = '\0'; // Ensure null-termination
        strncpy(newNode->Mode, Mode, sizeof(newNode->Mode) - 1);
        newNode->Mode[sizeof(newNode->Mode) - 1] = '\0'; // Ensure null-termination
        newNode->next = NULL;
    }
    return newNode;
}

void addQuizNode(Quiz** head, int ID, char* question, char* answer, char* userAnswer, char* Mode) {
    Quiz* newNode = createQuizNode(ID, question, answer, userAnswer, Mode);
    if (newNode == NULL) {
        printf("Loi: Khong the tao node moi.\n");
        return;
    }
    if (*head == NULL) {
        *head = newNode;
    } else {
        Quiz* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void FreeQuizList(Quiz* head) {
    Quiz* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}
void playReviewGame() {
    VOCAL* head = NULL;
    Quiz* quizHead = NULL;
    LoadFile(&head);
    
    if (head == NULL) {
        printf("ERROR !\n");
        return;
    }
    
    int numWords;
    printf("--- Welcome to join the mini game of our project  ---\n");
    printf("Please, enter the number of questions  ( Max 50 ) : ");
    do {
        scanf("%d", &numWords);
        if (numWords <= 0 || numWords > 50) {
            printf("Please enter a number between 1 and 50: ");
        }
    } while (numWords <= 0 || numWords > 50);

    // 1. Dem tong so tu trong danh sach 
    int totalWords = 0;
    VOCAL* temp = head;
    while (temp != NULL) {
        totalWords++;
        temp = temp->next;
    }
    if (numWords > totalWords) {
    numWords = totalWords; // Tự động giảm số câu hỏi xuống bằng kho từ vựng hiện có
    printf("Note: We only have %d words in data, let's review all of them!\n", totalWords);
    }

    int score = 0;
    char userAnswer[50];
    
    // Khoi tao bo sinh so ngau nhien
    srand(time(NULL));

    printf("--- Start ---\n", numWords);

    // 2. Vong lap chay
    for (int i = 1; i <= numWords; i++) {
        printf("\nQuestion  %d/%d \n", i, numWords);

        // Bốc ngẫu nhiên một vị trí từ 0 đến totalWords - 1
        int randomIndex = rand() % totalWords;

        // Duyệt danh sách liên kết đến đúng vị trí đó
        VOCAL* target = head;
        for (int j = 0; j < randomIndex; j++) {
            target = target->next;
        }

        if (target == NULL) {
            printf("ERROR ! \n");
            continue;
        }
        
        // ==========================================
        // LOGIC KIỂM TRA TRÙNG LẶP CHUẨN XÁC
        // ==========================================
        int isDuplicate = 0;
        Quiz* tempQuiz = quizHead;
        
        while (tempQuiz != NULL) {
            if (strcmp(tempQuiz->Answer, target->Word) == 0) { 
                isDuplicate = 1;
                break; 
            }
            tempQuiz = tempQuiz->next;
        }       

        if (isDuplicate == 1) {
            i--; 
            continue;
        }
        
        // 3. Hien thi nghia tieng Viet
        printf("\nQuestion : %s", target->Meaning);
        printf("\nEnter your answer ( Please enter the English word  ) : ");
        
        fflush(stdin); 
        scanf("%s", userAnswer);
        toLowerCase(userAnswer);

        int Result;
        
        // 4. So sanh ket qua (strcmp tra ve 0 neu giong nhau)
        if (strcmp(userAnswer, target->Word) == 0) {
            printf(" Congratulation !\n");
            Result = 1;
            score++;
        } else {
            printf("It's wrong ! \n The correct answer is: %s\n", target->Word);
            Result = 0;
        }

        if (Result == 1) {
            addQuizNode(&quizHead, i, target->Meaning, target->Word, userAnswer, "true");
        } else {
            addQuizNode(&quizHead, i, target->Meaning, target->Word, userAnswer, "false");
        }
    } 

    // 5. Tong ket sau khi kết thúc trò chơi
    printf("\n======================================");
    printf("\nEND !");
    printf("\nYour total score : %d/%d", score, numWords);

    if (score >= (numWords * 0.8)) printf("\n Exactly!");
    else if (score >= (numWords * 0.5)) printf("\n Good !");
    else printf("\n Try again !");

    printf (" Would you like to review your answers ? (Y/N) : ");
    char reviewChoice;
    scanf(" %c", &reviewChoice);
    if (reviewChoice == 'Y' || reviewChoice == 'y') {
        Quiz* tempQuiz = quizHead;
        int questionNumber = 1;
        while (tempQuiz != NULL) {
            printf("\nQuestion Number %d:", questionNumber);
            printf("\nQuestion: %s", tempQuiz->Question);
            printf("\nYour answer: %s", tempQuiz->UserAnswer);
            printf("\nCorrect answer: %s", tempQuiz->Answer);
            printf("\nResult: %s\n", strcmp(tempQuiz->UserAnswer, tempQuiz->Answer) == 0 ? "True" : "False");
            tempQuiz = tempQuiz->next;
            questionNumber++;
        }
    }else {
        printf("\nThank you for playing! See you next time!\n");
    }
    FreeQuizList(quizHead); 
    FreeVOCALList(head);
} 