#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>
#include "MODE_3.h"
#include "FUNCTION.h"

// Bang mau
#define RESET       "\033[0m"
#define GREEN       "\033[1;32m"
#define RED         "\033[1;31m"
#define YELLOW      "\033[1;33m"
#define CYAN        "\033[1;36m"
#define BLUE        "\033[1;34m"
#define BOLD        "\033[1m"

Quiz* createQuizNode(int ID, char* question, char* answer, char* userAnswer, char* status) {
    Quiz* newNode = (Quiz*)malloc(sizeof(Quiz));
    if (newNode != NULL) {
        newNode->ID = ID;
        strncpy(newNode->Question, question, sizeof(newNode->Question) - 1);
        newNode->Question[sizeof(newNode->Question) - 1] = '\0'; // Ensure null-termination
        strncpy(newNode->Answer, answer, sizeof(newNode->Answer) - 1);
        newNode->Answer[sizeof(newNode->Answer) - 1] = '\0'; // Ensure null-termination
        strncpy(newNode->UserAnswer, userAnswer, sizeof(newNode->UserAnswer) - 1);
        newNode->UserAnswer[sizeof(newNode->UserAnswer) - 1] = '\0'; // Ensure null-termination
        strncpy(newNode->Status, status, sizeof(newNode->Status) - 1);
        newNode->Status[sizeof(newNode->Status) - 1] = '\0'; // Ensure null-termination
        newNode->next = NULL;
    }
    return newNode;
}

void addQuizNode(Quiz** head, int ID, char* question, char* answer, char* userAnswer, char* status) {
    Quiz* newNode = createQuizNode(ID, question, answer, userAnswer, status);
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

void printBorder(int width) {
    printf("+");
    for (int i = 0; i < width; i++) printf("-");
    printf("+\n");
}

void printBorderDouble(int width) {
    printf("+");
    for (int i = 0; i < width; i++) printf("=");
    printf("+\n");
}

void printBoxLine(const char* content, int width) {
    printf("| %-*s |\n", width - 2, content);
}

void fprintBorderDouble(FILE* f, int width) {
    fprintf(f, "+");
    for (int i = 0; i < width; i++) fprintf(f, "=");
    fprintf(f, "+\n");
}

void fprintBorder(FILE* f, int width) {
    fprintf(f, "+");
    for (int i = 0; i < width; i++) fprintf(f, "-");
    fprintf(f, "+\n");
}

void showExportLoading() {
    printf(YELLOW "  Exporting to file: " RESET);
    printf("[");
    for (int i = 0; i < 20; i++) {
        printf(GREEN "."); 
        Sleep(50); 
    }
    printf(GREEN "]" RESET " 100%%\n");
    Sleep(300);
}
void playReviewGame() {
    VOCAL* head = NULL;
    Quiz* quizHead = NULL;
    LoadFile(&head);

    if (head == NULL) {
        system("cls"); // Xóa màn hình trước khi báo lỗi
        printf(RED);
        printBorderDouble(42);
        printBoxLine("  ERROR: Cannot load vocabulary file!", 42);
        printBorderDouble(42);
        printf(RESET);
        _getch(); // Dừng lại để người dùng thấy lỗi
        return;
    }

    // ==========================================
    // BANNER CHAO MUNG
    // ==========================================
    system("cls"); 
    printf(CYAN);
    printBorderDouble(54);
    printBoxLine("                                            ", 54);
    printBoxLine("    Welcome to the Vocabulary Review Game! ", 54);
    printBoxLine("                                            ", 54);
    printBorderDouble(54);
    printf(RESET "\n");

    // NHAP SO CAU HOI
    int numWords;
    printf(YELLOW);
    printBorder(46);
    printBoxLine("  Please enter the number of questions      ", 46);
    printBoxLine("  (Max: 50)                                 ", 46);
    printBorder(46);
    printf(RESET);

    printf(BOLD ">>> " RESET);
    do {
        scanf("%d", &numWords);
        if (numWords <= 0 || numWords > 50)
            printf(RED "  Please enter a number between 1 and 50: " RESET);
    } while (numWords <= 0 || numWords > 50);

    // Dem tong so tu
    int totalWords = 0;
    VOCAL* temp = head;
    while (temp != NULL) { totalWords++; temp = temp->next; }

    if (numWords > totalWords) {
        numWords = totalWords;
        printf(YELLOW "\n  Note: Only %d words available. Reviewing all!\n" RESET, totalWords);
        printf("  Press any key to start...");
        _getch();
    }

    int score = 0;
    char userAnswer[50];
    srand(time(NULL));

    // ==========================================
    // VONG LAP CAU HOI
    // ==========================================
    for (int i = 1; i <= numWords; i++) {
        system("cls"); // XÓA MÀN HÌNH trước mỗi câu hỏi mới

        char questionHeader[60];
        sprintf(questionHeader, "  Question %d / %d", i, numWords);

        printf(BLUE);
        printBorderDouble(50);
        printf("| %-48s |\n", questionHeader);
        printBorder(50);
        printf(RESET);

        // Boc ngau nhien & Kiem tra trung lap
        int randomIndex = rand() % totalWords;
        VOCAL* target = head;
        for (int j = 0; j < randomIndex; j++) target = target->next;

        int isDuplicate = 0;
        Quiz* tempQuiz = quizHead;
        while (tempQuiz != NULL) {
            if (strcmp(tempQuiz->Answer, target->Word) == 0) { isDuplicate = 1; break; }
            tempQuiz = tempQuiz->next;
        }
        if (isDuplicate) { i--; continue; }

        // Hien thi cau hoi
        printf(BLUE "| " RESET BOLD "  Meaning : " RESET "%s\n", target->Meaning);
        printf(BLUE); printBorder(50); printf(RESET);

        printf(BOLD "  Your answer: " RESET);
        fflush(stdin);
        scanf("%s", userAnswer);
        toLowerCase(userAnswer);

        // Ket qua
        int Result;
        if (strcmp(userAnswer, target->Word) == 0) {
            printf(GREEN);
            printBorderDouble(42);
            printBoxLine("  >>> Correct! Well done! <<<          ", 42);
            printBorderDouble(42);
            printf(RESET);
            Result = 1;
            score++;
        } else {
            char wrongMsg[60];
            printf(RED);
            printBorderDouble(42);
            printBoxLine("  >>> Wrong answer!                     ", 42);
            sprintf(wrongMsg, "  Correct answer: %-22s", target->Word);
            printBoxLine(wrongMsg, 42);
            printBorderDouble(42);
            printf(RESET);
            Result = 0;
        }

        addQuizNode(&quizHead, i, target->Meaning, target->Word, userAnswer, Result ? "true" : "false");

        // HIỆU ỨNG TẠM DỪNG: Cho người dùng xem kết quả Đúng/Sai
        printf(YELLOW "\n  Press any key to continue..." RESET);
        _getch(); 
    }

    // TONG KET (Xóa sạch màn hình để show bảng điểm)
    // ==========================================
    system("cls");
    const char* verdict;
    const char* verdictColor;
    if (score >= numWords * 0.8) { verdict = "  >>> Excellent! <<<  "; verdictColor = GREEN; }
    else if (score >= numWords * 0.5) { verdict = "  >>> Good job!  <<<  "; verdictColor = YELLOW; }
    else { verdict = "  >>> Try again! <<<  "; verdictColor = RED; }

    char scoreMsg[50];
    sprintf(scoreMsg, "  Your Score: %d / %d", score, numWords);

    printf(CYAN);
    printBorderDouble(44);
    printBoxLine("              GAME  OVER                  ", 44);
    printBorder(44);
    printf("| %-42s |\n", scoreMsg);
    printf(RESET "%s", verdictColor);
    printf("| %-42s |\n", verdict);
    printf(RESET CYAN);
    printBorderDouble(44);
    printf(RESET "\n");

    printf(YELLOW "  Would you like to review your answers? (Y/N): " RESET);
    char reviewChoice;
    scanf(" %c", &reviewChoice);
/* Hien thi review chi tiet tung cau hoi co mau tren terminal
    if (reviewChoice == 'Y' || reviewChoice == 'y') {
        system("cls"); // Xóa màn hình để bắt đầu Review
        printf(CYAN "=================== REVIEW ANSWERS ===================\n\n" RESET);
        Quiz* tempQ = quizHead;
        int qNum = 1;
        while (tempQ != NULL) {
            int correct = strcmp(tempQ->UserAnswer, tempQ->Answer) == 0;
            const char* resColor = correct ? GREEN : RED;
            const char* resText  = correct ? "[TRUE]" : "[FALSE]";

            char hdr[256], buf[256];

            printf(resColor);
            printBorderDouble(52);
            sprintf(hdr, "  Question #%d  %s", qNum, resText);
            printf("| %-50s |\n", hdr);
            printBorder(52);
            printf(RESET);

            sprintf(buf, "  Question : %s", tempQ->Question);
            printf("| %-50s |\n", buf);
            sprintf(buf, "  Yours : %s", tempQ->UserAnswer);
            printf("%s| %-50s |\n" RESET, correct ? GREEN : RED, buf);
            sprintf(buf, "  Answer: %s", tempQ->Answer);
            printf("| %-50s |\n", buf);

            printf(resColor);
            printBorderDouble(52);
            printf(RESET "\n");

            tempQ = tempQ->next;
            qNum++;
        }
        printf(YELLOW "  Press any key to return to menu..." RESET);
        _getch();
    } else {
        printf(CYAN "\n  Thank you for playing! See you next time!\n\n" RESET);
        _getch();
    }
*/
    printf(YELLOW "\n  Would you like to export your results to 'ReviewHistory.txt'? (Y/N): " RESET);
    char exportChoice;
    scanf(" %c", &exportChoice);
    if (exportChoice == 'Y' || exportChoice == 'y') {

        FILE *f = fopen("ReviewHistory.txt", "w");
        Quiz* tempQ = quizHead;
        int qNum = 1;
        if (f == NULL) {
            printf(RED "  Error: Could not create file!\n" RESET);
        } else {
            showExportLoading();
            // Ghi tiêu đề và điểm số
            fprintf(f, "====================================================\n");
            fprintf(f, "|           VOCABULARY GAME REVIEW HISTORY         |\n");
            fprintf(f, "====================================================\n");
            fprintf(f, "  Total Score: %d / %d\n", score, numWords);
            fprintf(f, "  Status: %s\n", (score >= numWords * 0.5) ? "PASSED" : "FAILED");
            fprintf(f, "====================================================\n\n");

            while (tempQ != NULL) {
                int correct = strcmp(tempQ->UserAnswer, tempQ->Answer) == 0;
                char hdr[256], buf[256];

                fprintBorderDouble(f, 52);
                sprintf(hdr, "  Question #%d  %s", qNum, correct ? "[CORRECT]" : "[INCORRECT]");
                fprintf(f, "| %-50s |\n", hdr);
                fprintBorder(f, 52);

                fprintf(f, "|   Question : %-37s |\n", tempQ->Question);
                fprintf(f, "|   Yours    : %-37s |\n", tempQ->UserAnswer);
                fprintf(f, "|   Correct  : %-37s |\n", tempQ->Answer);

                fprintBorderDouble(f, 52);
                fprintf(f, "\n");

                tempQ = tempQ->next;
                qNum++;
            }
            fclose(f);
            printf(GREEN "  Successfully exported to 'ReviewHistory.txt'!\n" RESET);
        }
    }

    FreeQuizList(quizHead);
    FreeVOCALList(head);
}