#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEY_LEN 11
#define MAX_VAL_LEN 11
#define MAX_LINE_LEN 100

typedef struct {
    char key[MAX_KEY_LEN];
    char value[MAX_VAL_LEN];
} KeyValue;

int main() {
    FILE *file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("Error: Cannot open data.txt\n");
        return 1;
    }

    KeyValue *pairs = NULL;
    int pairCount = 0;
    int pairCapacity = 0;

    char line[MAX_LINE_LEN];
    while (fgets(line, sizeof(line), file) != NULL) {
       
        line[strcspn(line, "\n")] = '\0';

      
        if (strlen(line) == 0) {
            continue;
        }

       
        char *colonPos = strchr(line, ':');
        if (colonPos == NULL) {
          
            continue;
        }

        
        char key[MAX_KEY_LEN];
        char value[MAX_VAL_LEN];

    
        int keyLen = colonPos - line;
        int valLen = strlen(colonPos + 1);

        if (keyLen >= MAX_KEY_LEN || valLen >= MAX_VAL_LEN) {
            
            continue;
        }

        strncpy(key, line, keyLen);
        key[keyLen] = '\0';

        strcpy(value, colonPos + 1);

        
        int isDuplicate = 0;
        for (int i = 0; i < pairCount; i++) {
            if (strcmp(pairs[i].key, key) == 0) {
                isDuplicate = 1;
                break;
            }
        }
        if (isDuplicate) {
            continue;
        }

       
        if (pairCount >= pairCapacity) {
            pairCapacity = pairCapacity == 0 ? 10 : pairCapacity * 2;
            pairs = (KeyValue *)realloc(pairs, pairCapacity * sizeof(KeyValue));
            if (pairs == NULL) {
                printf("Error: Out of memory\n");
                fclose(file);
                return 1;
            }
        }

        
        strcpy(pairs[pairCount].key, key);
        strcpy(pairs[pairCount].value, value);
        pairCount++;
    }

    fclose(file);

    
    char input[MAX_KEY_LEN];
    while (1) {
        printf("Please enter a key (enter 'Quit' to exit): ");
        scanf("%s", input);

        if (strcmp(input, "Quit") == 0) {
            break;
        }

        
        int found = 0;
        for (int i = 0; i < pairCount; i++) {
            if (strcmp(pairs[i].key, input) == 0) {
                printf("%s\n", pairs[i].value);
                found = 1;
                break;
            }
        }

        if (!found) {
            printf("Error\n");
        }
    }

    
    free(pairs);

    return 0;
}