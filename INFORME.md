# INFORME DE INSTALACIÓN DE XV6

## Pasos Seguidos para Instalar xv6

1. Instalé Ubuntu en WSL.
2. Instalé QEMU en Ubuntu con el comando `sudo apt-get install qemu qemu-system-misc`.
3. Cloné el repositorio de xv6 usando:
   
   `git clone https://github.com/keloco23/xv6-riscv.git ~/xv6-riscv`

4. Instalé el toolchain de RISC-V usando:

    `git clone --recursive https://github.com/riscv/riscv-gnu-toolchain`
    `cd riscv-gnu-toolchain`
    `./configure --prefix=/opt/riscv`
    `make`
    
5. Verifiqué la instalación del toolchain con:

    `riscv64-unknown-elf-gcc --version`

6. Compilé el kernel de xv6 con `make qemu`.

## Problemas encontrados y soluciones

1. Error de duplicación de ID en QEMU:

- Problema: Error de ID duplicado al ejecutar `make qemu`.
- Solución: Corregí las opciones de QEMU en el archivo Makefile eliminando la línea duplicada.

2. Error de permisos en la instalación del toolchain:

- Problema: Permisos denegados al intentar crear directorios durante la instalación del toolchain.
- Solución: Usé `sudo` para tener permisos de administrador o cambié el directorio de instalación a uno donde el usuario tiene permisos.

## Confirmación de que xv6 está Funcionando Correctamente

$ ls
.              1 1 1024
..             1 1 1024
README         2 2 2403
cat            2 3 35600
echo           2 4 34456
forktest       2 5 16296
grep           2 6 39040
init           2 7 34912
kill           2 8 34376
ln             2 9 34192
ls             2 10 37720
mkdir          2 11 34440
rm             2 12 34424
sh             2 13 57168
stressfs       2 14 35312
usertests      2 15 181216
grind          2 16 50880
wc             2 17 36592
zombie         2 18 33776
console        3 19 0

-----------------------------

$ echo "Hola xv6
"Hola xv6

---------------------------
$ cat README
xv6 is a re-implementation of Dennis Ritchie's and Ken Thompson's Unix
Version 6 (v6).  xv6 loosely follows the structure and style of v6,
but is implemented for a modern RISC-V multiprocessor using ANSI C.

ACKNOWLEDGMENTS

xv6 is inspired by John Lions's Commentary on UNIX 6th Edition (Peer
to Peer Communications; ISBN: 1-57398-013-7; 1st edition (June 14,
2000)).  See also https://pdos.csail.mit.edu/6.1810/, which provides
pointers to on-line resources for v6.

The following people have made contributions: Russ Cox (context switching,
locking), Cliff Frey (MP), Xiao Yu (MP), Nickolai Zeldovich, and Austin
Clements.

We are also grateful for the bug reports and patches contributed by
Takahiro Aoyagi, Marcelo Arroyo, Silas Boyd-Wickizer, Anton Burtsev,
carlclone, Ian Chen, Dan Cross, Cody Cutler, Mike CAT, Tej Chajed,
Asami Doi,Wenyang Duan, eyalz800, Nelson Elhage, Saar Ettinger, Alice
Ferrazzi, Nathaniel Filardo, flespark, Peter Froehlich, Yakir Goaron,
Shivam Handa, Matt Harvey, Bryan Henry, jaichenhengjie, Jim Huang,
Matúš Jókay, John Jolly, Alexander Kapshuk, Anders Kaseorg, kehao95,
Wolfgang Keller, Jungwoo Kim, Jonathan Kimmitt, Eddie Kohler, Vadim
Kolontsov, Austin Liew, l0stman, Pavan Maddamsetti, Imbar Marinescu,
Yandong Mao, Matan Shabtay, Hitoshi Mitake, Carmi Merimovich, Mark
Morrissey, mtasm, Joel Nider, Hayato Ohhashi, OptimisticSide,
phosphagos, Harry Porter, Greg Price, RayAndrew, Jude Rich, segfault,
Ayan Shafqat, Eldar Sehayek, Yongming Shen, Fumiya Shigemitsu, snoire,
Taojie, Cam Tenny, tyfkda, Warren Toomey, Stephen Tu, Alissa Tung,
Rafael Ubal, Amane Uehara, Pablo Ventura, Xi Wang, WaheedHafez,
Keiichi Watanabe, Lucas Wolf, Nicolas Wolovick, wxdao, Grant Wu, x653,
Jindong Zhang, Icenowy Zheng, ZhUyU1997, and Zou Chang Wei.

The code in the files that constitute xv6 is
Copyright 2006-2024 Frans Kaashoek, Robert Morris, and Russ Cox.

ERROR REPORTS

Please send errors and suggestions to Frans Kaashoek and Robert Morris
(kaashoek,rtm@mit.edu).  The main purpose of xv6 is as a teaching
operating system for MIT's 6.1810, so we are more interested in
simplifications and clarifications than new features.

BUILDING AND RUNNING XV6

You will need a RISC-V "newlib" tool chain from
https://github.com/riscv/riscv-gnu-toolchain, and qemu compiled for
riscv64-softmmu.  Once they are installed, and in your shell
search path, you can run "make qemu".