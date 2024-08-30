#include "kernel/types.h"
#include "user/user.h"

int main() {
    printf("Soy mi propio ancestro: %d\n", getancestor(0));
    printf("Mi padre es: %d\n", getancestor(1));
    printf("Mi abuelo es: %d\n", getancestor(2));
    printf("Ancestro inválido: %d\n", getancestor(10)); 
    exit(0);
}
