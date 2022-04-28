#include "ReadCsvFile.c"
#include "hashs.c"
#include<stdlib.h>
#include<unistd.h>
#include "hashOrigen.c"

struct campos{
    float id;    
    float hora;
    
};
int main()
{
    FILE *fp,*fp2, *fp3;
    char *filename="BogVia.csv";
    char *pivote = NULL;
    fp=fopen(filename,"r");
    fp2=fopen("tabla_datos.bin","wb");
    fp3=fopen("tabla_datos.bin","rb");
    float datos[4];
    char strLine[MAX_LINE_SIZE];
    fgets(strLine,MAX_LINE_SIZE,fp);   
    
    int cambio=0;     
    int filas=GetTotalLineCount(fp);
    printf("el total de filas es %d", filas);
    
    
    for(int i=0; i<filas;i++)
    {
        struct campos camp;                
        printf("\n");
        fgets(strLine,MAX_LINE_SIZE,fp);
       // printf("%s",strLine); 
        pivote=strtok(strLine,",");
        printf("%d: %0.2f ",i, atof(pivote));
        datos[0]=atof(pivote);               
        for(int j=0; j<3;j++)
        {
            
            pivote=strtok(NULL,",");
            datos[j+1]=atof(pivote);
            //printf("el valor de dato en array es %0.1f ",datos[j+1]);
            printf("%0.2f ",atof(pivote));
            //printf("%f",datos[0]);
        }
        printf("\n");        
        int tre=myhash(datos,cambio);
        //printf(" hasin es %d",tre);
        struct campos a={
            .id=datos[0],                       
            .hora=datos[3],
            
        };
        fseek(fp2,tre,SEEK_SET);
        fseek(fp3,tre,SEEK_SET);
        fread(&camp,sizeof(struct campos),1,fp3);
        //fread(&camp,sizeof(struct campos),1,fp2);                
        printf("%0.2f %0.2f\n",camp.id,camp.hora);
        if((int)camp.id==0){
            fwrite(&a,sizeof(struct campos),1,fp2);            
        }
        else{
            printf("aca paso");
            sleep(5);
        }
               
        /* else{
            int hash2;
            while((int)camp.id!=0 && (int)camp.id2!=0){            
            hash2=hashOrigin(datos);
            fseek(fp3,hash2,SEEK_SET);
            fread(&camp,sizeof(struct campos),1,fp3);
            printf("en la posicion 2 hay %0.2f %0.2f %0.2f \n", camp.id,camp.id2,camp.hora);
            }
            printf("el hash2 es %d", hash2);
            fseek(fp2,hash2,SEEK_SET);            
            fwrite(&a,sizeof(struct campos),1,fp2);

            sleep(5);
        } */        
    }

    fclose(fp);
    fclose(fp3);
    fclose(fp2);
    
       
    
    return 0;
}