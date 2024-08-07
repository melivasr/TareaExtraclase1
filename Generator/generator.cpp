// Created by Melissa Vásquez.
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cstring>

int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cerr << "Uso: generator -size <SIZE> -output <OUTPUT FILE PATH>\n";
        return 1;
    }

    const char* sizeFlag = argv[1];
    const char* sizeArg = argv[2];
    const char* outputFlag = argv[3];
    const char* outputPath = argv[4];

    // Verifica que las banderas de los argumentos sean correctas
    if (strcmp(sizeFlag, "-size") != 0 || strcmp(outputFlag, "-output") != 0) {
        std::cerr << "Uso: generator -size <SIZE> -output <OUTPUT FILE PATH>\n";
        return 1;
    }

    long long fileSize;
    long long constexpr megabyte = 1024 * 1024LL;
    if (strcmp(sizeArg, "XXSMALL") == 0) {
        fileSize = 1024LL; // 1 KB
    } else if (strcmp(sizeArg, "SMALL") == 0) {
        fileSize = 512 * megabyte; // 512 MB
    } else if (strcmp(sizeArg, "MEDIUM") == 0) {
        fileSize = 1 * 1024 * megabyte; // 1 GB
    } else if (strcmp(sizeArg, "LARGE") == 0) {
        fileSize = 2 * 1024 * megabyte; // 2 GB
    } else {
        std::cerr << "Tamano desconocido. Use XXSMALL, SMALL, MEDIUM, o LARGE.\n";
        return 1;
    }

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::ofstream outputFile(outputPath, std::ios::binary);
    if (!outputFile.is_open()) {
        std::cerr << "Error al abrir el archivo para escritura en: " << outputPath << "\n";
        return 1;
    }

    std::cout << "Comenzando a escribir en el archivo...\n";
    // Escribe numeros enteros aleatorios en el archivo hasta alcanzar el tamano deseado
    for (long long i = 0; i < fileSize / sizeof(int); ++i) {
        int randomInt = std::rand();
        outputFile.write(reinterpret_cast<const char*>(&randomInt), sizeof(randomInt));
    }
    std::cout << "Escritura completada.\n";

    outputFile.close();
    std::cout << "Archivo generado exitosamente en: " << outputPath << "\n";

    return 0;
}

