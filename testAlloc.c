#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

typedef struct test {
    int a;
    unsigned long long b;
    char c;
} Test;

int main() {
    Test t;
    t.a = 1;
    t.b = -1;
    t.c = 'Z';

    int len = 10;
    Test *tArray = (Test *)valloc(len, sizeof(Test), &t);
    for (int i = 0; i < len; i++) {
        printf(1, "%d 0x%x ", i, tArray + i);
        Test *t_i = &tArray[i];
        char *c = (char *)t_i;
        for (int j = 0; j < sizeof(Test); j++) {
            printf(1, "%x ", *(c + j));
        }
        printf(1, "\n");
    }
}