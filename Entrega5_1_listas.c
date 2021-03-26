#include <stdio.h>
#include <string.h>

typedef struct{
	char nombre[20];
	int socket;
}TConectado;

typedef struct{
	
	TConectado conectados[100];
	int num;
}TListaConectados;

int pon(TListaConectados *lista, char nombre[20],int socket){//Añadir usuario a la lista
	if(lista->num==100){
		return -1;//Lista llena
	}
	
	else{
		strcpy(lista->conectados[lista->num].nombre,nombre);//Añadir el nombre del usuario a la lista
		lista->conectados[lista->num].socket=socket;//Añadir num (id) de socket de conex de ese usuario
		lista->num++;//Incremento de la lista 1 ud
		return 0;
	}
}
int DameSocket(TListaConectados *lista,char nombre[20]){
		int i=0;
		int encontrado=0;
		
		while((i<lista->num)&&(encontrado!=1)){
			if(strcmp(lista->conectados[i].nombre,nombre)==0){
				encontrado=1;
			}
			i++;
		}
		if(encontrado==0){//Socket no está en la lista
			return -1;
		}
		
		else{
			return lista->conectados[i-1].socket;
		}
	}
	
	int Eliminar(TListaConectados *lista,char nombre[20]){
		int i=0;
		int encontrado=0;
		
		while((i<lista->num)&&(encontrado!=1)){
			if(strcmp(lista->conectados[i].nombre,nombre)==0){
				encontrado=1;
			}
			i++;
		}
		if(encontrado==0){
			return -1;
		}
		
		else{
			int j=0;
			i=i-1;
			while(j<lista->num){
				strcpy(lista->conectados[i].nombre,lista->conectados[i+1].nombre);
				lista->conectados[i].socket=lista->conectados[i+1].socket;
				j++;
				i++;
			}
			lista->num=lista->num-1;
			return 0;
		}
	}
	
void DameConectados(TListaConectados *lista,char conectados[300]){
	int i=0;
	sprintf(conectados,"%d",lista->num);
	while(i<lista->num){
		sprintf(conectados,"%s,%s",conectados,lista->conectados[i].nombre);
		i++;
	}
	
}
 	

int main(int argc, char *argv[]) {
	TListaConectados lista;
	int res;
	int sock;
	int count;
	
	lista.num=0;
	
	pon(&lista,"Pedro",8);
	pon(&lista,"Sara",2);
	pon(&lista,"Antonia",11);
	pon(&lista,"Diego",12);
	pon(&lista,"Carlos",10);
	res=pon(&lista,"Ferran",6);

	
	if(res!=-1){
		printf("Usuario añadido\n");
	}
	else{
		printf("Usuario no añadido\n");
	}
	
	printf("\n");
	
	count=0;
	while(count<lista.num){
		printf("Nombre: %s; Conex. %d\n",lista.conectados[count].nombre,lista.conectados[count].socket);
		count++;
	}
	printf("\n");
	
	sock = DameSocket(&lista,"Ferran");
	
	   if(sock!=-1){
		printf("El socket de Ferran es %d \n",sock);
		printf("\n");
	}
	   else{
		   printf("NO hay socket\n");
	   }
	   
	   int usuario_eliminado;
	   usuario_eliminado=Eliminar(&lista,"Sara");
	   
		count=0;
	   if(usuario_eliminado==0){
		   printf("Se ha eliminado Sara \n");
		   printf("\n");
		   while(count<lista.num){
			   printf("Nombre: %s; Conex. %d\n",lista.conectados[count].nombre,lista.conectados[count].socket);
			   count++;
		   }
	   }
	   else{
		   printf("Error \n");
	   }
	   
	   char usuarios_conectados[300];
	   DameConectados(&lista,usuarios_conectados);
	   
	   printf("Usuarios conectados: %s\n",usuarios_conectados);
	   
	   char *p=strtok(usuarios_conectados,",");
	   int numero = atoi(p);
	   
	   printf("\n");
	   printf("Total Usuarios: %d\n",numero);
	   
	   count=1;
	   char nombre[20];
	   
	   printf("\n");
	   while(p!=NULL){
		   p=strtok(NULL,",");
		   strcpy(nombre,p);
		   printf("Nombre Usuario %d: %s\n",count,nombre);
		   count++;
	   }
	
}

