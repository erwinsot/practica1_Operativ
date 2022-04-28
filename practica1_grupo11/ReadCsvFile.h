#pragma once
#include <stdio.h>
#include <memory.h> // for memset
#include <stdlib.h> // for malloc, free
#include <string.h> // for strtok
 
 
#define MAX_LINE_SIZE 256   // El número máximo de bytes leídos por la función fgets
 
 
int* giCsvData ;           // Un puntero a la memoria de datos asignada dinámicamente
int giNumData ;            // Número de bytes de datos leídos
int giNumRow ;             // El número de bytes por línea
int giNumCol ;             // El número de bytes en cada columna
 
 
int GetTotalLineCount(FILE* fp);              // Calcula el número total de filas en el archivo csv
int GetTotalColCount(FILE * fp);              // Calcula el número total de columnas en el archivo csv (basado en el número de columnas en la primera fila)
int AssignSpaceForData(int inumdata);         // Asignación dinámica de espacio de memoria a datos a través del puntero * giCsvData
void FreeCsvData();                           // Liberar memoria dinámica de datos
int ReadCsvData(char* csvFilePath);           // Leer los datos en Csv (el tipo de datos predeterminado en este ejemplo es int)
void  ShowCsvData();        