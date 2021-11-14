#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

struct Datacenter{
	int id;
	char codigo[25];
	char ciudad[25];
	char pais[25];
 	char latitud[25];
 	char longitud[25];
};

struct Datacenter datacenters[100];
int conCenter=-1;


//se convierte grados a radianes
float aRadianes(float convertir){
	//M_PI es el valor de PI obtenido de la libreria math.h
	//Aqui se saca el valor de un grado en radianes
	float un_grado = (M_PI)/180;
	
	return (un_grado * convertir);
}

//devuelve la distancia en kilometros entre dos puntos 
float devolverKM(float lat1, float long1, float lat2, float long2){
	float km = 0;
	float r = 6371e3;
	
	//se convierten de grados a radianes
	long1 = aRadianes(long1);
	lat1 = aRadianes(lat1);
	long2 = aRadianes(long2);
	lat2 = aRadianes(lat2);
	
	float diflong = long2 - long1;
	float diflat = lat2 - lat1;
	
	//la parte de abajo de la formula
	float res = pow(sin(diflat / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(diflong / 2), 2);
	
	float resdef = 2 * r * sin(sqrt(res));
	
	//Se ingresa a la formula
	
	
	return resdef;
}

void arbolExpansionMinima(float matriz[conCenter][conCenter]){
	bool visitado[conCenter];
	int expansion[conCenter];
	float minimo=INT_MAX;
	int min_aux, locacion=0;
	int i=0,j=0;
	
	//se inicializa el vector de visitado a false
	for(i=0;i<conCenter-1; i++){
		visitado[i]= false;
		expansion[i]=INT_MAX;
	}
	for(i = 0; i<conCenter-1; i++){
		minimo=0;
		printf("MALDITA SEA  %f", minimo);
			for(j= 0; j<conCenter-1; j++){
				//if(visitado[i]==true) continue;
				printf("matriz %.2f minimo %.2f \n", matriz[i][j], minimo);
				if(matriz[i][j] == 0) continue;
				if(matriz[i][j] < matriz[i][locacion]){
					minimo = matriz[i][j];
					locacion=j;
				}
				
				expansion[i]=locacion;
				printf(" %d expa ", expansion[i]);
			}
		
		
	}
}



int main(){
	
	
	
	
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
	
	//se declara el grafo como matriz adyacencia
	float matriz[conCenter][conCenter];
	float matrizaux[conCenter][conCenter];
	j=0;
	i=0;
	for(i=0; i<conCenter-1;i++){
		for( j=0; j<conCenter-1;j++){
			matriz[i][j]= devolverKM(atof(datacenters[i].latitud), atof(datacenters[i].longitud),atof(datacenters[j].latitud),atof(datacenters[j].longitud));
			matrizaux[i][j]= devolverKM(atof(datacenters[i].latitud), atof(datacenters[i].longitud),atof(datacenters[j].latitud),atof(datacenters[j].longitud));
			printf("%.2f ", matriz[i][j]);
		}
		printf("\n");
	}
	
	
	arbolExpansionMinima(matriz);
	
	
	
	printf("\n\n\n");
	printf("%f.2", devolverKM(9.5503646,-69.1804708,  8.59207, -70.225082));
	printf("\nCantidad de centros: %d", conCenter);
	
	return 0;
}

