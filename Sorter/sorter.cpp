#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <chrono>

#include "PagedArray.h"
#include "Algorithms/bubbleSort.h"
#include "Algorithms/insertionSort.h"
#include "Algorithms/NoSort.h"
#include "Algorithms/quickSort.h"

int main(int argc, char* argv[]) {
    std::cout << "Número de argumentos: " << argc << "\n";
    for (int i = 0; i < argc; ++i) {
        std::cout << "Argumento " << i << ": " << argv[i] << "\n";
    }

    if (argc != 7) {
        std::cerr << "Uso: sorter -input <INPUT FILE PATH> -output <OUTPUT FILE PATH> -alg <ALGORITMO>\n";
        return 1;
    }

    const char* inputFlag = argv[1];
    const char* inputFilePath = argv[2];
    const char* outputFlag = argv[3];
    const char* outputFilePath = argv[4];
    const char* algFlag = argv[5];
    const char* algorithm = argv[6];

    if (strcmp(inputFlag, "-input") != 0 || strcmp(outputFlag, "-output") != 0 || strcmp(algFlag, "-alg") != 0) {
        std::cerr << "Uso: sorter -input <INPUT FILE PATH> -output <OUTPUT FILE PATH> -alg <ALGORITMO>\n";
        return 1;
    }

    std::cout << "Ruta del archivo de entrada: " << inputFilePath << "\n";
    std::cout << "Ruta del archivo de salida: " << outputFilePath << "\n";
    std::cout << "Algoritmo seleccionado: " << algorithm << "\n";

    PagedArray pagedArray(inputFilePath);

    std::ifstream inputFile(inputFilePath, std::ios::binary | std::ios::ate);
    if (!inputFile.is_open()) {
        std::cerr << "Error al abrir el archivo para lectura en: " << inputFilePath << "\n";
        return 1;
    }

    std::size_t fileSize = inputFile.tellg();
    std::size_t numElements = fileSize / sizeof(int);

    if (fileSize % sizeof(int) != 0) {
        std::cerr << "El tamaño del archivo no es múltiplo del tamaño de un entero.\n";
        return 1;
    }

    std::cout << "Tamaño del archivo: " << fileSize << " bytes\n";
    std::cout << "Número de elementos: " << numElements << "\n";

    auto start = std::chrono::high_resolution_clock::now();

    if (strcmp(algorithm, "QS") == 0) {
        std::cout << "Usando Quick Sort\n";
        quickSort(pagedArray, 0, numElements - 1);
    } else if (strcmp(algorithm, "IS") == 0) {
        std::cout << "Usando Insertion Sort\n";
        insertionSort(pagedArray, 0, numElements - 1);
    } else if (strcmp(algorithm, "BS") == 0) {
        std::cout << "Usando Bubble Sort\n";
        bubbleSort(pagedArray, 0, numElements - 1);
    } else {
        std::cerr << "Algoritmo desconocido. Use QS, IS, o BS.\n";
        return 1;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    int percentage = 0;

    std::ofstream outputFile(outputFilePath, std::ios::trunc); // Open file as text
    if (!outputFile.is_open()) {
        std::cerr << "Error al abrir el archivo para escritura en: " << outputFilePath << "\n";
        return 1;
    }

    for (std::size_t i = 0; i < numElements; ++i) {
        outputFile << pagedArray[i];
        if (i != numElements - 1) {
            outputFile << ",";
        }

        if (i % (numElements / 100) == 0) { // Print progress every 1% of the total elements
            std::cout << percentage << "%" << "\n";
            percentage += 1;
        }
    }

    outputFile.close();

    std::cout << "Archivo ordenado generado exitosamente en: " << outputFilePath << "\n";
    std::cout << "Tiempo durado: " << elapsed.count() << " segundos\n";
    std::cout << "Algoritmo utilizado: " << algorithm << "\n";
    std::cout << "Page Faults: " << pagedArray.getPageFaults() << "\n";
    std::cout << "Page Hits: " << pagedArray.getPageHits() << "\n";

    return 0;
}

