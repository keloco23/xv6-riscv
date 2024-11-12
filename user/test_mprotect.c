#include "types.h"
#include "user.h"
#include "syscall.h"

int mprotect(void *addr, int len) {
    return syscall(SYS_mprotect, addr, len);
}

int munprotect(void *addr, int len) {
    return syscall(SYS_munprotect, addr, len);
}

int main() {
    char *ptr = sbrk(4096); // Reserva una página
    if (mprotect(ptr, 4096) < 0) {
        printf("Error en mprotect\n");
    } else {
        printf("mprotect exitosa\n");
    }

    if (munprotect(ptr, 4096) < 0) {
        printf("Error en munprotect\n");
    } else {
        printf("munprotect exitosa\n");
    }
    exit();
}
