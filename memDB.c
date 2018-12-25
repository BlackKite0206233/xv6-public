#include "types.h"
#include "user.h"

typedef struct data {
    char *key;
    char *value;
} Data;

Data *db;
char *cmd;
int count;

void start() {
    int pid;

    // Fork new process
    pid = fork();
    if (pid < 0) {
        printf(1, "error in fork\n");
        exit();
    }

    if (pid == 0) {
        db    = (Data *)calloc(1000, sizeof(Data *));
        count = 0;
        while (1) {
            if (strcmp(cmd, "set") == 0) {
                Data data;
                data.key   = (char *)malloc(1000 * sizeof(char *));
                data.value = (char *)malloc(1000 * sizeof(char *));
                gets(data.key,   1000);
                gets(data.value, 1000);
                db[count] = data;
                count++;
            } else if (strcmp(cmd, "get") == 0) {
                char *key = (char *)malloc(1000 * sizeof(char *));
                gets(key, 1000);
                for (int i = 0; i < count; i++) {
                    if (strcmp(key, "*") || strcmp(db[i].key, key)) {
                        printf(1, "%s\n", db[i].value);
                    }
                }
            } else if (strcmp(cmd, "update") == 0) {
                char *key   = (char *)malloc(1000 * sizeof(char *));
                char *value = (char *)malloc(1000 * sizeof(char *));
                gets(key,   1000);
                gets(value, 1000);
                for (int i = 0; i < count; i++) {
                    if (strcmp(db[i].key, key)) {
                        db[i].value = value;
                    }
                }
            } else if (strcmp(cmd, "delete") == 0) {
                char *key = (char *)malloc(1000 * sizeof(char *));
                gets(key, 1000);
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
            suspend_proc2();
        }
    }
    wait();
    exit();
}

void resume() {
    int pid;

    // Fork new process
    pid = fork();
    if (pid < 0) {
        printf(1, "error in fork\n");
        exit();
    }

    if (pid == 0) {
        resume_proc2();
    }
    wait();
    exit();
}

int flag = 0;
int main(int argc, char *argv[]) {
    cmd = argv[1];
    if (strcmp(argv[1], "start") == 0) {
        start();
    } else {
        resume();
    }
    exit();
}