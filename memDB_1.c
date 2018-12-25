#include "types.h"
#include "user.h"

typedef struct data {
    char *key;
    char *value;
} Data;

int main(int argc, char *argv[]) {
    Data *db   = (Data *)calloc(1000, sizeof(Data *));
    int  count = 0;
    while (1) {
        char *s = (char *)malloc(2100 * sizeof(char *));
        int count = 0;
        char **cmd = strtok(s, " ", &count);
        if (strcmp(cmd[0], "set") == 0) {
            Data data;
            data.key   = cmd[1];
            data.value = cmd[2];
            db[count]  = data;
            count++;
        } else if (strcmp(cmd[0], "get") == 0) {
            char *key = cmd[1];
            for (int i = 0; i < count; i++) {
                if (strcmp(key, "*") || strcmp(db[i].key, key)) {
                    printf(1, "%s\n", db[i].value);
                }
            }
        } else if (strcmp(cmd[0], "update") == 0) {
            char *key   = cmd[1];
            char *value = cmd[2];
            for (int i = 0; i < count; i++) {
                if (strcmp(db[i].key, key)) {
                    db[i].value = value;
                }
            }
        } else if (strcmp(cmd[0], "delete") == 0) {
            char *key = cmd[1];
            for (int i = 0; i < count; i++) {
                if (strcmp(db[i].key, key)) {
                    for (int j = i; j < count - 1; j++) {
                        db[j] = db[j + 1];
                    }
                    db[count].key   = "";
                    db[count].value = "";
                    count--;
                }
            }
        }
    }
}