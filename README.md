# Algoritmo Generator

Este programa en C++ genera archivos binarios grandes que contienen una cantidad predeterminada de números enteros aleatorios. A continuación se indican las instrucciones para compilar y ejecutar el generador.

## Estructura del Programa

- `Generator/`
  - `generator.cpp` - Código fuente del generador.
  - `generator.exe` - Archivo ejecutable del generador (después de la compilación).

## Instrucciones de Compilación

1. **Asegúrate de estar en el directorio `Generator`:**

    ```bash
       cd <GENERATOR DIRECTORY PATH>
    ```

2. **Compila el código utilizando `g++`:**

    ```bash
    g++ generator.cpp -o generator.exe
    ```

    - `-o generator.exe` especifica el nombre del archivo ejecutable resultante.

## Ejecución del Generador

Para ejecutar el generador, usa el siguiente comando, ajustando el tamaño y la ruta del archivo de salida según sea necesario:

```bash
.\generator.exe -size <SIZE> -output <OUTPUT FILE PATH>
```
**-size <SIZE>**: Tamaño del archivo que se desea generar. Puede tomar uno de los siguientes valores:

**XXSMALL:** genera un archivo de 1KB

**SMALL:** genera un archivo de 512 MB

**MEDIUM:** genera un archivo de 1 GB

**LARGE:** genera un archivo 2 GB

**-output** <OUTPUT FILE PATH>: corresponde a la ruta del sistema de archivos donde se guarda el archivo.

Por ejemplo:
```bash
.\Generator\generator.exe -size XXSMALL -output C:\Users\melis\OneDrive\Documents\GitHub\TareaExtraclase1\Generator\input.dat
```

# Algoritmo Sorter

Este programa en C++ sirve para ordenar archivos binarios grandes utilizando diferentes algoritmos de ordenamiento. A continuación se indican las instrucciones para compilar y ejecutar el programa.

## Estructura del Programa

- `Sorter/`
  - `sorter.cpp` - Archivo principal del programa.
  - `PagedArray.cpp` - Implementación de la clase `PagedArray`.
  - `PagedArray.h` - Cabecera de la clase `PagedArray`.
  - `Algorithms/`
    - `bubbleSort.cpp` - Implementación del algoritmo Bubble Sort.
    - `bubbleSort.h` - Cabecera del algoritmo Bubble Sort.
    - `insertionSort.cpp` - Implementación del algoritmo Insertion Sort.
    - `insertionSort.h` - Cabecera del algoritmo Insertion Sort.
    - `quickSort.cpp` - Implementación del algoritmo Quick Sort.
    - `quickSort.h` - Cabecera del algoritmo Quick Sort.

## Instrucciones de Compilación

1. **Asegúrate de estar en el directorio raíz del programa:**

    ```bash
    cd <SORTER DIRECTORY PATH>
    ```

2. **Compila el código utilizando `g++`:**

    ```bash
    g++ -o Sorter/sorter.exe Sorter/sorter.cpp Sorter/PagedArray.cpp Sorter/Algorithms/bubbleSort.cpp Sorter/Algorithms/insertionSort.cpp Sorter/Algorithms/quickSort.cpp -ISorter
    ```

    - `-o Sorter/sorter.exe` especifica el nombre del archivo ejecutable resultante.
    - `-ISorter` indica la ruta del directorio que contiene los archivos de cabecera necesarios.

## Ejecución del Programa

Para ejecutar el programa, usa el siguiente comando, asegurándote de ajustar las rutas a los archivos de entrada y salida según sea necesario:

```bash
./Sorter/sorter.exe -input <INPUT FILE PATH> -output <OUTPUT FILE PATH> -alg QS
```
**-input** <INPUT FILE PATH>: Ruta del archivo de entrada en formato binario que contiene los números enteros aleatorios a ordenar.

**-output** <OUTPUT FILE PATH>: Ruta del archivo de salida donde se guardarán los datos ordenados.

**-alg** <ALGORITHM>: Algoritmo de ordenamiento a utilizar. Puede tomar uno de los siguientes valores:

**QS:** Quick Sort

**IS:** Insertion Sort

**BS:** Bubble Sort

Por ejemplo:
```bash
./Sorter/sorter.exe -input C:/Users/melis/OneDrive/Documents/GitHub/TareaExtraclase1/Generator/input.dat -output C:/Users/melis/OneDrive/Documents/GitHub/TareaExtraclase1/Sorter/data.txt -alg QS
```

Estas instrucciones son para Windows y fueron utilizadas en CLion. Si estás utilizando Linux o un entorno diferente, los comandos pueden variar.

Asegúrate de tener g++ instalado y correctamente configurado en tu sistema para compilar el código.
