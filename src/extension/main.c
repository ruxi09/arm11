#include "structures.h"

//verifies whether a specific character is a capital letter
bool is_letter(char c) {
    return c >= 'A' && c <= 'Z';
}

//takes the character and the index in the string
//returns whether there is another letter before it
bool has_a_letter_before(char *c, int i) {
    for (int j = i; j >= 0; j--) {
        if (is_letter(c[j])) {
            return true;
        }
    }
    return false;
}

//takes the character and the index in the string
//returns whether there is another letter after it
bool has_a_letter_after(char *c, int i) {
    for (int j = i; c[j] != '\0'; j++) {
        if (is_letter(c[j])) {
            return true;
        }
    }
    return false;
}

//takes a string and and turns each character into uppercase
char *uppercase(char *str) {
    //   assert(str);
    int length = (int) strlen(str);
    for (int i = 0; i < length; i++) {
        if (str[i] != '\n') {
            str[i] = toupper(str[i]);
        }
    }
    return str;
}

//takes a string as input
//checks it contains only letters
//removes unnecessary  spaces
void clean_string(char *str) {
    int len = strlen(str);
    char temp[len];
    int pos = 0;
    for (int i = 0; i < len; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            temp[pos] = str[i];
            pos++;
        } else if (str[i] == ' ') {
            if (has_a_letter_before(str, i) && has_a_letter_after(str, i)) {
                if (temp[pos - 1] != ' ') {
                    temp[pos] = ' ';
                    pos++;
                }
            }
        }

    }
    temp[pos] = '\0';
    strcpy(str, temp);
}

//processes the input
void preprocess_input(char *str) {
    uppercase(str);
    clean_string(str);
}

//searches through the record database
int find_match(char *result, char *input) {
    //printf("%d\n", nKnowledgeBaseSize);
    for (int i = 0; i < nKnowledgeBaseSize; i++) {
        //checks if the exact input if found in the database
        if (!strcmp(KnowledgeBase[i].input, uppercase(input))) {
            return i;
        }//checks if there is a derivation of the input
        else if (strstr(input, KnowledgeBase[i].input)) {
            return i;
        } else if (strstr(KnowledgeBase[i].input, input)) {
            return i;
        }
    }
    return -1; //returned if there is nothing similar in the database
}


int main() {
    char input[256] = "";
    //int array storing if the user repeats itself
    int repetitions[nKnowledgeBaseSize];
    for (int i = 0; i < nKnowledgeBaseSize; i++) {
        repetitions[i] = 0;
    }
    printf("HELLO, I'LL BE YOUR FRIEND FOR A FEW MINUTES\n");
    do {
        printf(">>> ");
        fgets(input, 256, stdin);
        preprocess_input(input);
        char result[strlen(input) + 1];
        if (!strcmp(input, "EXIT")) {
            printf("It was nice talking to you. Bye");
            break;
        } else {
            int index = find_match(result, input);
            if (index >= 0) {
                int r = rand() % 3;  // for each input there are 3 possible answers
                if (repetitions[index] == 0) {
                    printf("%s\n", KnowledgeBase[index].responses[r]);
                    repetitions[index] = repetitions[index] + 1;
                } else {
                    printf("I ALREADY TOLD YOU, %s\n", KnowledgeBase[index].responses[r]);
                }
            } else {
                printf("%s\n", "Sorry I don't understand");
            }
        }
    } while (1);
}


