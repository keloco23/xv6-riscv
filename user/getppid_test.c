#include "user/user.h"
#include "kernel/types.h"

int main() {
    printf("PPID: %d\n", getppid());
    exit(0);
}