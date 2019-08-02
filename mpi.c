/*
Universidad Guadalajara Lamar
Sistemas Operativos Avanzados
Programa: 
Comunicacion de paso de mensajes (Envio y recepcion MPI)
Maria Ines Calderon Zetter
*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define MAX_CAD 32
#define ETIQUETA1 1
#define ETIQUETA2 2

/*
El objetivo de este programa es lograr que 
maquinas (nodos) con distinto numero identificador
se comuniquen, funcionando ya sea como RX o TX.
*/

typedef char cadena[MAX_CAD];

int main(int argc, char ** argv){
int id, total;
cadena maquina, mensaje;

//Tipo de dato MPI_Status.
MPI_Status estado;

//Inicializamos y le pasamos 
//los datos del main.
MPI_Init(&argc,&argv);

//Esta primitiva nos retorna el 
//id de la maquina.
MPI_Comm_rank(MPI_COMM_WORLD,&id);

//Esta primitiva nos retorna el numero total de procesos.
MPI_Comm_size(MPI_COMM_WORLD,&total); 


if(id==0){
/*
>>strcpy sirve para copiar una cadena de texto en una variable destino.
>>strlen nos devuelve la longitud de una cadena.
*/

strcpy(mensaje, "Hola como estas !");

/*
>>Estructura de TX:
MPI_Send(void *buf, int count, MPI_Datatype dtype, int dest, int tag, MPI_Comm comm); 

>>Estructura de RX:
MPI_Recv(void *buf, int count, MPI_Datatype dtype, int source, int tag, MPI_Comm comm, MPI_Status status); 
*/

int i;
for (i=0; i<total; i++)
{
MPI_Send(mensaje,strlen(mensaje)+1,MPI_UNSIGNED_CHAR,i,ETIQUETA1,MPI_COMM_WORLD);
}
MPI_Recv(mensaje,MAX_CAD,MPI_UNSIGNED_CHAR,1,ETIQUETA2,MPI_COMM_WORLD, &estado);
printf("Soy %d. Recibo %s\n",id,mensaje);

} //fin if


else{
	strcpy(mensaje, "Hola como estas !");
	//Aqui estaremos recibiendo el mensaje del nodo 0
	MPI_Recv(mensaje,MAX_CAD,MPI_UNSIGNED_CHAR,0,ETIQUETA1,MPI_COMM_WORLD, &estado);
	
	printf("Soy %d. Recibo %s de %d. \n",id,mensaje,id);
	strcpy(mensaje, "Bien gracias !");
	MPI_Send(mensaje,strlen(mensaje)+1,MPI_UNSIGNED_CHAR,0,ETIQUETA2,MPI_COMM_WORLD);
}

MPI_Finalize();
return 0;
} //fin main
