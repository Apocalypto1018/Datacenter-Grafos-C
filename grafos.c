#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

struct Datacenter{
	int id;
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
	int control=0;
	int contador=0;
	int codigo=0;
	int pasarUnEspacio=0;
	
    fichero=fopen("datacenters.txt","rt");
    
    if(fichero==NULL){
    	printf("Archivo no encontrado\n");
    	exit(1);
	}
	
	while (!feof(fichero)) { 
		
		i=0;
		conCenter++;
		memset(aux, 0, 80);	
		codigo=0;
		control=1;
		pasarUnEspacio=0;
		
        fgets(linea, 80, fichero);
		
		datacenters[conCenter].id=conCenter;

        if (!feof(fichero)) {
        	
        	while(linea[i]!='\n'){
        		
        		aux[j]=linea[i];
        		
        		j++;
        				
    			if(control==1 && linea[i]==' '){
    				strcpy(datacenters[conCenter].codigo, aux);
    				control++;
    				
    				memset(aux, 0, 25);	
    				j=0;
    				
				}else if(control==2 && linea[i]==','){
    				strcpy(datacenters[conCenter].ciudad, aux);
    				control++;
    				
    				memset(aux, 0, 25);	
    				j=0;
    				
    				pasarUnEspacio=1;
    			
				
				}else if(linea[i]==' ' && pasarUnEspacio==1 && control==3){
					pasarUnEspacio=2;
				}
				
				else if(control==3 && linea[i]==' ' && pasarUnEspacio==2){
    				strcpy(datacenters[conCenter].pais, aux);
    				control++;
    				
    				memset(aux, 0, 25);	
    				j=0;
    				
				}else if(control==4 && linea[i]==' ' && pasarUnEspacio==2){
    				strcpy(datacenters[conCenter].latitud, aux);
    				control++;
    				
    				memset(aux, 0, 25);	
    				j=0;
				}
    			
				i++;
				
				if(linea[i]=='\n'){
    				strcpy(datacenters[conCenter].longitud, aux);
    				memset(aux, 0, 25);	
    				j=0;
				}
				
			}
			
	
		}
		   
    } 

    for(i=0;i<conCenter;i++){
    	
    	printf("\n\nDatacenter %i:\n", datacenters[i].id+1);
    	printf("Codigo: %s\n",datacenters[i].codigo);
	    printf("Ciudad: %s\n",datacenters[i].ciudad);
	    printf("Pais: %s\n",datacenters[i].pais);
	    printf("Latitud: %s\n",datacenters[i].latitud);
	    printf("Longitud: %s\n",datacenters[i].longitud);
	
	}
    
	fclose(fichero);
	return 0;
}

