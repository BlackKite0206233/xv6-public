//
// Created by dsp on 1/17/14.
//
#include "types.h"
#include "user.h"


// Second approach's start
void
count_stop(void) {
    int pid;

    // Fork new process
    pid = fork();
    if (pid < 0) {
        printf(1, "error in fork\n");
        exit();
    }

    if (pid == 0) {
        int i;
        for (i = 0; i < 4; i++) {
            printf(1, "count : %d\n", i);
            sleep(50);
        }
        // Call to suspend_proc to save process state
        // PC will remain here
        suspend_proc2();
        // resume_proc should start PC from here
        for (i = 4; i < 8; i++) {
            printf(1, "count : %d\n", i);
            sleep(50);
        }
    }
    wait();
    exit();
}

// Second approach's resume
void
count_resume(void) {
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

int
main(int argc, char *argv[]) {
    if (atoi(argv[1]) == 1) {
        count_stop();
    } else if (atoi(argv[1]) == 2) {
        count_resume();
    }
    exit();
}