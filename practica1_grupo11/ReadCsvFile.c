
#include "readCSVFile.h"

int GetTotalLineCount(FILE * fp)
{   
    int i = 0;
    char strLine[MAX_LINE_SIZE];
    fseek(fp,0,SEEK_SET);
    while (fgets(strLine, MAX_LINE_SIZE, fp))
        i++;
    fseek(fp,0,SEEK_SET);
    return i;
}
// Calcula el número total de columnas en el archivo csv (basado en el número de columnas en la primera fila)
int GetTotalColCount(FILE * fp)
{   
    int i = 0;
    char strLine[MAX_LINE_SIZE];
    fseek(fp,0,SEEK_SET);
    if (fgets(strLine, MAX_LINE_SIZE, fp))
    {
        i=strlen(strLine)/2;   // Debido a que el archivo csv usa una coma ',' como separador, divídalo por 2 aquí
    }
    else
    {
        fseek(fp,0,SEEK_SET);
        return -1;
    }
    fseek(fp,0,SEEK_SET);
    return i;
}
// Asignar dinámicamente espacio de memoria para datos a través del puntero * giCsvData
int AssignSpaceForData(int inumdata){
    giCsvData=NULL;
    giCsvData = (int*)malloc(sizeof(int)*inumdata); 
    if (giCsvData == NULL)
        return 0;
    memset(giCsvData, 0, sizeof(int)*inumdata);
    return 1;
}
 
// Liberar memoria dinámica de datos
void FreeCsvData(){
    free(giCsvData);
    giCsvData = NULL;
}
 
// leer datos del archivo csv
int ReadCsvData(char* csvFilePath)
{
    FILE* fCsv;
    char *ptr;
    char strLine[MAX_LINE_SIZE];
    int i;
    int j;
    // ya tiene datos, elimine primero
    if (giCsvData != NULL)
        FreeCsvData();
    // abre un archivo
    if( fopen_s( &fCsv, csvFilePath, "r" ) != 0 )
    {
        printf("open file %s failed",csvFilePath);
        return -1;
    }
    else
    {
        // Determine el tamaño de la matriz dinámica y luego abra el espacio
        giNumRow = GetTotalLineCount(fCsv);
        giNumCol = GetTotalColCount(fCsv);
        giNumData = giNumRow*giNumCol;
        AssignSpaceForData(giNumData);
 
        // leer datos
        for (i = 0; i < giNumRow; i++)
        { 
 
            j=0;
            if(fgets(strLine,MAX_LINE_SIZE,fCsv))
            {
                ptr=strtok(strLine,",");  // Devuelve los caracteres antes del carácter "," en la matriz de caracteres y mantén el resto en la matriz estática (este método no se considera seguro)
                // Puedes intentar reemplazar con strtok_s
                while(ptr!=NULL)
                {
                    giCsvData[i*giNumCol+j]=atoi(ptr);     // Convierta caracteres a datos de tipo int y guárdelos en una matriz dinámica
                    j++;
                    ptr = strtok(NULL,",");                // Leer la matriz de caracteres restante de la línea actual del archivo y leer el byte antes del carácter ","
                }
            }
        }
        // cierra el archivo
        fclose(fCsv);
    }
    return 1;
}
 
// Muestra los datos csv leídos a través de la consola
void  ShowCsvData()                           
{
    int i;
    int j;
    for (i = 0; i < giNumRow; i++)
    {
        printf("Line %i :",i+1);    // Muestra el número de línea de cada línea Línea:
        for (j=0;j<giNumCol;j++)
        {
            printf("%i",giCsvData[i*giNumCol+j]);  // Imprimir datos CSV
        }
        printf("\n");                           // Salto de línea de salida
    }
}