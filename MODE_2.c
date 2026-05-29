#include <stdio.h>
#include <string.h>

#include "MODE_2.h"

void mode2_print_homophones(VOCAL* head) {
    if (head == NULL) {
        printf("No vocabulary loaded.\n");
        return;
    }

    // FUNCTION.h không có field homophone_group_id.
    // Xem đồng âm theo Pronoun (phiên âm): các từ có cùng Pronoun sẽ được in cặp.
    for (VOCAL* i = head; i != NULL; i = i->next) {
        if (i->Pronoun[0] == '\0') continue;

        for (VOCAL* j = i->next; j != NULL; j = j->next) {
            if (j->Pronoun[0] == '\0') continue;

            if (strcmp(i->Pronoun, j->Pronoun) == 0) {
                printf("%s (%s) <-> %s (%s)\n", i->Word, i->Meaning, j->Word, j->Meaning);
            }
        }
    }
}

