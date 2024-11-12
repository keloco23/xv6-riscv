# README

## Protección de Memoria en xv6

Este informe describe el proceso de implementación de la protección de memoria en xv6 mediante las llamadas al sistema `mprotect` y `munprotect`. Estas syscalls permiten marcar regiones de memoria como solo lectura o restaurarlas a lectura/escritura, respectivamente.

### Funcionamiento y Lógica de la Protección de Memoria

La protección de memoria permite que una aplicación limite el acceso a regiones de su memoria, previniendo la modificación de datos en áreas críticas. La lógica básica de esta implementación es la siguiente:

1. **mprotect**: Marca una región de memoria como solo lectura. A través de la modificación del bit de escritura (PTE_W) en la entrada de la tabla de páginas, impide que esa región sea modificada.
2. **munprotect**: Restaura los permisos de escritura a la región de memoria previamente protegida. Esta función establece el bit de escritura (PTE_W) en la entrada de la tabla de páginas, permitiendo que la región sea modificada nuevamente.

Ambas funciones operan sobre direcciones alineadas a páginas y recorren las páginas involucradas dentro de la longitud especificada. Si la dirección no es válida o la página no está presente, las funciones retornan un error.

### Explicación de las Modificaciones Realizadas

Para implementar la protección de memoria en xv6, se realizaron los siguientes cambios:

1. **Definición de Syscalls en `syscall.h`**:
   - Se agregaron `SYS_mprotect` y `SYS_munprotect` con números únicos de syscall para habilitar las nuevas llamadas al sistema.

2. **Funciones Envolventes en `sysproc.c`**:
   - Se implementaron `sys_mprotect` y `sys_munprotect` como funciones que obtienen los argumentos desde el espacio de usuario y llaman a las funciones `mprotect` y `munprotect`.
   - Se utilizó `fetchaddr` para obtener la dirección base y `fetchint` (creada como una función adicional) para obtener la longitud desde el espacio de usuario.

3. **Implementación de `mprotect` y `munprotect` en `proc.c`**:
   - `mprotect`: Recorre cada página en la región especificada, localiza la entrada de la tabla de páginas con `pte_lookup` (función creada para obtener la dirección de la entrada de la tabla de páginas), y desactiva el bit de escritura.
   - `munprotect`: Similar a `mprotect`, pero reactiva el bit de escritura en cada entrada de página de la región especificada.
   - La función `pte_lookup` fue creada para obtener el puntero a `pte_t` de una dirección virtual dada, similar a `uvmlookup`.

4. **Función Adicional `fetchint` en `syscall.c`**:
   - Se implementó `fetchint` para obtener el argumento `int` directamente desde el espacio de usuario, usando `fetchaddr` como base.

5. **TEST** 
   - Se logra testear funciones ejecutando `test_mprotect.c`

### Dificultades Encontradas y Soluciones Implementadas

1. **Error en `argaddr` y `argint`**:
   - Al principio, intentamos utilizar `argaddr` y `argint` para extraer los argumentos, pero generaban errores de tipo `void value not ignored as it ought to be`. La solución fue reemplazar `argint` con `fetchint`, que se implementó basándose en `fetchaddr`.

2. **Falta de `uvmlookup` en xv6 RISC-V**:
   - xv6 RISC-V no cuenta con la función `uvmlookup` para obtener el puntero a la entrada de la tabla de páginas. Se creó `pte_lookup`, una función que recorre las tablas de páginas hasta encontrar la entrada `pte_t` para una dirección virtual dada.

3. **Problemas de Compilación en las Syscalls**:
   - En la tabla de syscalls (`syscalls[]` en `syscall.c`), hubo problemas iniciales de tipos incompatibles al conectar las funciones `sys_mprotect` y `sys_munprotect`. Estos errores se resolvieron definiendo las funciones sin parámetros y utilizando `fetchaddr` y `fetchint` para extraer los argumentos dentro de las funciones.

4. **Verificación de Páginas Válidas y Presentes**:
   - Para evitar errores en páginas no válidas o ausentes, se incluyó una verificación en `pte_lookup` para asegurarse de que cada `pte_t` fuera válida (`PTE_V` presente). Esto garantiza que `mprotect` y `munprotect` operen solo en páginas válidas.
