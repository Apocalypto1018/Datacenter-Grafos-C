#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

struct Datacenter{
	char codigo[25];
	char ciudad[25];
	char pais[25];
 	char latitud[25];
 	char longitud[25];
};



int main(){
	struct Datacenter datacenters[100];
	int conCenter=-1;
	
	FILE* fichero;
	char linea[80];
	char aux[25];
	int i=0, j=0;
	int control=1;
	int contador=0;
	
    fichero=fopen("datacenters.txt","rt");
    
    if(fichero==NULL){
    	printf("Archivo no encontrado\n");
    	exit(1);
	}
	
	while (!feof(fichero)) { 
		
		i=0;
		conCenter++;
		memset(aux, 0, 80);	
		control=1;
		
        fgets(linea, 80, fichero); 

        if (!feof(fichero)) {
        	
        	while(linea[i]!='\n'){
        		
        		aux[j]=linea[i];
        		
        		j++;
        		
        		if(linea[i]==' '){
        			
        			if(control==1){
        				strcpy(datacenters[conCenter].codigo, aux);
        				control++;
					}else if(control==2){
        				strcpy(datacenters[conCenter].ciudad, aux);
        				control++;
					}else if(control==3){
        				strcpy(datacenters[conCenter].pais, aux);
        				control++;
					}else if(control==4){
        				strcpy(datacenters[conCenter].latitud, aux);
        				control++;
					}
        			
        			memset(aux, 0, 25);	
        			j=0;
				}
				
				i++;
				
				if(linea[i]=='\n'){
    				strcpy(datacenters[conCenter].longitud, aux);
    				control++;
    				memset(aux, 0, 25);	
    				j=0;
				}
				
			}
			
	
		}
		   
    } 

    for(i=0;i<conCenter;i++){
    	
    	printf("\n\nDatacenter %i:\n", i+1);
    	printf("Codigo: %s\n",datacenters[i].codigo);
	    printf("Ciudad: %s\n",datacenters[i].ciudad);
	    printf("Pais: %s\n",datacenters[i].pais);
	    printf("Latitud: %s\n",datacenters[i].latitud);
	    printf("Longitud: %s\n",datacenters[i].longitud);
	
	}
    
	fclose(fichero);
	return 0;
}


