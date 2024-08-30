# INFORME.md TAREA 1

## Funcionamiento de las Llamadas al Sistema

se han implementado dos nuevas llamadas al sistema:

1. **`getppid()`**: Esta llamada al sistema devuelve el ID de proceso del padre (PPID) del proceso que la invoca. Permite a un proceso conocer quién lo ha creado, lo cual es útil para depuración y monitoreo del sistema.

2. **`getancestor(int n)`**: Esta llamada al sistema devuelve el ID de proceso de un ancestro `n` del proceso que la invoca. Por ejemplo, `getancestor(0)` devuelve el propio proceso, `getancestor(1)` devuelve el proceso padre, y así sucesivamente. Si `n` es mayor que el número de ancestros disponibles, la función devuelve `-1`.

Ambas llamadas al sistema proporcionan información importante sobre la jerarquía de procesos y pueden ser útiles para la depuración y administración de procesos en el sistema.

## Explicación de las Modificaciones Realizadas

### Parte I: Implementación de `getppid()`

1. **Definición de la Llamada al Sistema:**
   - Se añadió la definición de `SYS_getppid` en el archivo `kernel/syscall.h`.

2. **Asignación del Número de Llamada al Sistema:**
   - Se añadió la entrada `[SYS_getppid] sys_getppid` en el archivo `kernel/syscall.c` para asociar el número de llamada al sistema con su función correspondiente.

3. **Implementación de la Función del Núcleo:**
   - La función `sys_getppid()` fue implementada en `kernel/sysproc.c` para obtener y devolver el ID del proceso padre del proceso actual (`myproc()->parent->pid`).

4. **Modificación del Archivo `user.h`:**
   - Se añadió la declaración `int getppid(void);` en el archivo `user/user.h` para que los programas de usuario puedan invocar la nueva llamada al sistema.

5. **Creación de Programa de Prueba `getppid_test.c`:**
   - Se añadió un programa en `user/getppid_test.c` para probar la nueva llamada al sistema. Este programa simplemente invoca `getppid()` y muestra el resultado.

6. **Modificación del Makefile:**
   - Se actualizó el `Makefile` para compilar `getppid_test` y asegurarse de que se incluya en la construcción de xv6.

### Parte II: Implementación de `getancestor(int n)`

1. **Definición de la Llamada al Sistema:**
   - Se añadió la definición de `SYS_getancestor` en el archivo `kernel/syscall.h`.

2. **Asignación del Número de Llamada al Sistema:**
   - Se añadió la entrada `[SYS_getancestor] sys_getancestor` en el archivo `kernel/syscall.c` para asociar el número de llamada al sistema con su función correspondiente.

3. **Implementación de la Función del Núcleo:**
   - La función `sys_getancestor()` fue implementada en `kernel/sysproc.c` para recorrer la jerarquía de procesos ascendentes hasta encontrar el ancestro `n`-ésimo. Si no existe tal ancestro, la función retorna `-1`.

4. **Modificación del Archivo `user.h`:**
   - Se añadió la declaración `int getancestor(int n);` en el archivo `user/user.h` para que los programas de usuario puedan invocar la nueva llamada al sistema.

5. **Creación de Programa de Prueba `getancestor_test.c`:**
   - Se añadió un programa en `user/getancestor_test.c` para probar la nueva llamada al sistema. Este programa invoca `getancestor(n)` con diferentes valores de `n` y muestra los resultados.

6. **Modificación del Makefile:**
   - Se actualizó el `Makefile` para compilar `getancestor_test` y asegurarse de que se incluya en la construcción de xv6.

## Dificultades Encontradas y Cómo Se Resolvieron

1. **Problemas con la Declaración y Definición de las Funciones:**
   - Se encontraron errores relacionados con la no declaración de funciones en `syscall.c` y `user.h`. Esto se resolvió asegurando que cada nueva llamada al sistema tuviera tanto una declaración en `user/user.h` como una definición en `kernel/sysproc.c`.

2. **Errores de Compilación al Usar `argint`:**
   - Hubo errores debido a un mal uso de `argint` en `sys_getancestor`. Esto se resolvió cambiando la estructura del código para manejar el retorno de `argint` correctamente y verificar que el argumento es válido antes de continuar con la lógica de la función.

3. **Errores en el Makefile:**
   - Al agregar nuevos programas de usuario, hubo que actualizar el `Makefile` adecuadamente. Se aprendió a agregar nuevos programas correctamente a la lista de compilación y se aseguró de que cada nuevo archivo de prueba estuviera bien definido.

4. **Problemas con la Ejecución de `qemu`:**
   - Hubo dificultades iniciales para ejecutar `qemu` debido a configuraciones incorrectas y a la falta de parámetros adecuados. Se resolvió al asegurar que se utilizaban los parámetros correctos (`-nographic -bios none`) para iniciar xv6 en modo de terminal sin interfaz gráfica.