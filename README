# README

---

## Funcionamiento y lógica

El objetivo principal fue implementar la funcionalidad de `chmod`, que permite cambiar los permisos de un archivo. Además, desarrollé `chmodtest.c` para probar escenarios comunes relacionados con permisos.

1. **Comando de usuario (`chmod`)**:
   - El usuario puede ejecutar `chmod <mode> <file>` para cambiar los permisos de un archivo específico.
   - Los permisos están representados por un número entero que se guarda en los metadatos del archivo (en el `dinode`).

2. **Pruebas con `chmodtest.c`**:
   - Este archivo verifica el comportamiento correcto de `chmod` en múltiples casos:
     - Creación de un archivo.
     - Cambio de permisos.
     - Intento de modificar archivos inmutables.
   - Utiliza llamadas al sistema como `chmod` y `open` para interactuar con el sistema de archivos.

3. **Lógica del kernel**:
   - Cuando se ejecuta `chmod`, el sistema realiza una llamada al sistema (`sys_chmod`) que verifica los argumentos, bloquea el inode correspondiente y actualiza los permisos en el disco.

4. **Seguridad**:
   - Los permisos se verifican en el nivel del kernel para evitar modificaciones accidentales o maliciosas. Por ejemplo, algunos archivos tienen permisos inmutables que no pueden modificarse con `chmod`.

---

## Explicación de las modificaciones realizadas

### 1. **Estructura del sistema de archivos**
   - **`struct dinode`**: Añadí un campo `perm` (int) en la estructura del `dinode` para almacenar los permisos de cada archivo.
   - **Alineación de tamaño**: Para evitar errores de alineación en disco, ajusté el tamaño del `dinode` con un campo de relleno (`padding`).

### 2. **Implementación del sistema de llamadas**
   - En **`sys_chmod`** (en `kernel/sysfile.c`):
     - Verifiqué los argumentos de entrada (`path` y `mode`).
     - Bloqueé el inode del archivo con `ilock`.
     - Accedí al bloque del `dinode` correspondiente, verifiqué los permisos actuales y los actualicé.
     - Sincronizé los cambios con `log_write` y liberé el inode.
   - Añadí `sys_chmod` a los archivos relevantes del kernel:
     - `kernel/syscall.c`
     - `kernel/syscall.h`
     - `user/user.h`
     - `user/usys.pl`

### 3. **Comando de usuario**
   - Implementé `chmod` como un archivo en `user/chmod.c`.
   - Incluye lógica para validar los argumentos de usuario y realizar la llamada al sistema.

### 4. **Pruebas con `chmodtest.c`**
   - Creé un archivo `chmodtest.c` en el directorio `user` para verificar:
     - La creación exitosa de un archivo con permisos iniciales.
     - Cambios de permisos válidos.
     - Restricción de cambios en archivos marcados como inmutables.
   - El archivo utiliza funciones como `open`, `chmod` y mensajes impresos (`printf`) para verificar los resultados.
   - Ejemplo del código:
     ```c
     #include "kernel/types.h"
     #include "kernel/stat.h"
     #include "user/user.h"
     #include "kernel/fcntl.h"

     int main() {
         int fd = open("testfile", O_CREATE | O_RDWR);
         if (fd < 0) {
             printf("Error: could not create file.\n");
             exit(1);
         }
         printf("File created successfully.\n");

         if (chmod("testfile", 1) < 0) {
             printf("Error: chmod failed.\n");
             exit(1);
         }
         printf("Permissions changed successfully.\n");

         exit(0);
     }
     ```

### 5. **Modificaciones al sistema de compilación**
   - Modifiqué el `Makefile` para incluir el nuevo comando `chmod` y el archivo de pruebas `chmodtest.c`.

---

## Dificultades encontradas y soluciones implementadas

### 1. **Error en la alineación del tamaño del `dinode`**
   - **Problema**: Al añadir el campo `perm`, el tamaño del `dinode` ya no era divisible por el tamaño del bloque (`BSIZE`), lo que provocaba errores durante la inicialización.
   - **Solución**: Añadí un campo de relleno (`padding`) para garantizar que el tamaño del `dinode` sea divisible por `BSIZE`.

### 2. **Errores de compilación relacionados con `sys_chmod`**
   - **Problema**: Inicialmente, el compilador lanzaba errores al intentar usar funciones o estructuras no declaradas.
   - **Solución**: Aseguré que todas las declaraciones necesarias estuvieran en los encabezados correctos (`fs.h`, `syscall.h`, etc.) y que las funciones se implementaran correctamente.

### 3. **Pánico en el kernel: "log_write outside of trans"**
   - **Problema**: Intentaba escribir en el log fuera de una transacción.
   - **Solución**: Encapsulé las operaciones críticas dentro de una transacción para cumplir con las reglas del sistema de logs.

### 4. **Errores al compilar `chmodtest.c`**
   - **Problema**: Conflictos entre las definiciones de `fcntl.h` en xv6 y las del sistema host.
   - **Solución**: Incluí la versión de `fcntl.h` específica de xv6 y ajusté el código para evitar conflictos.

### 5. **Verificación del funcionamiento de `chmod`**
   - **Problema**: No estaba claro si los permisos se aplicaban correctamente.
   - **Solución**: Usé múltiples `printf` para depurar, verificar y ajustar el código hasta que las pruebas pasaron exitosamente.