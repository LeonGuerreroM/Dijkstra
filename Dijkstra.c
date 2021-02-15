#include <stdlib.h>
#include <stdio.h>


typedef struct Nodo{
    char letra;
	int peso;
	struct Nodo *sig;
	struct Nodo *ant;
	struct Nodo *abajo;
}Lista;

typedef struct Nodo1{
    char letra;
	int peso;
	char nodoP;
	int estado;
	struct Nodo1 *sig;
	struct Nodo1 *ant;
}ListaExt;

int lectura[100];
int matrizA[9][9];
char letras[] = {'A','B','C','D','E','F','G','H','I'};

void lecturaBin(char direccion[]);
void matrizAdyacencia();
Lista* ListaAyacencia();
void imprimirLista(Lista *top);
Lista* arbolGenerador(Lista *top);
void Dijkstra(Lista *top);

Lista* Crear(int dato,char letra);
Lista* AltaFinal(Lista *top, int dato, char letra);
Lista* AltaAbajo(Lista *top, int dato, char letra);
void Consulta(Lista *top);
void ConsultaA(Lista *top);
ListaExt* CrearExt(int dato,char letra);
ListaExt* AltaFinalExt(ListaExt *top, int dato, char letra);
void ConsultaExt(ListaExt *top);



int main(){
    int i,j,contLetras=0;
    int **matriz;
    char direccion[] = "C:\\Users\\leonm\\Desktop\\Grafo_matriz.bin";
    Lista *listaAyacencia=NULL,*arbolGene=NULL;

    lecturaBin(direccion);
    /*for(i=0;i<82;i++){
        printf("%d ",lectura[i]);
    }*/
    printf("\nMatriz de Adyacencia\n\n");
    matrizAdyacencia();
    for(i=0;i<10;i++){
        if(i==0){
            printf("  \t");
            continue;
        }
        printf("%c \t",letras[i-1]);

    }
    printf("\n");
    for(i=0;i<9;i++){
        printf("%c \t",letras[i]);
        for(j=0;j<9;j++){
            printf("%d \t",matrizA[i][j]);
        }
        printf("\n");
    }

    printf("\n\nListas de Adyacencia\n");
    listaAyacencia=ListaAyacencia();
    imprimirLista(listaAyacencia);

    arbolGene=arbolGenerador(listaAyacencia);
    printf("\nArbol Generador(BPA)\n");
    ConsultaA(arbolGene);

    printf("\n\nCamino mas corto con Dijkstra\n");
    Dijkstra(listaAyacencia);


return 0;
}

void lecturaBin(char direccion[]){
    FILE *ar;
    ar=fopen(direccion,"rb");
    fread(lectura,sizeof(int),82,ar);
    fclose(ar);
}

void matrizAdyacencia(){
    int i, j, tama=lectura[0],contLectura=1;
    for(i=0;i<tama;i++){
        for(j=0;j<tama;j++){
            matrizA[i][j]=lectura[contLectura];
            contLectura++;
        }
    }
}

Lista* ListaAyacencia(){
    Lista *la=NULL,*aux,*aux2;
    int i,j,tama=lectura[0],movMatrizi=0;

    for(i=0;i<tama;i++){
        la=AltaFinal(la,0,letras[i]);
    }

    aux=la;

    while(aux!=NULL){
        for(j=0;j<tama;j++){
            if(matrizA[movMatrizi][j]!=0){
                if(aux->abajo==NULL){
                    aux=AltaAbajo(aux,matrizA[movMatrizi][j],letras[j]);
                    aux2=aux->abajo;
                }else{
                    aux2=AltaFinal(aux2,matrizA[movMatrizi][j],letras[j]);
                }
            }
        }
        aux=aux->sig;
        movMatrizi++;
    }

    return la;
}

void imprimirLista(Lista *top){
    Lista *aux,*aux2;
    aux=top;

    while(aux!=NULL){
        printf("%c ",aux->letra);
        aux2=aux->abajo;
        while(aux2!=NULL){
            printf("%c-%d ",aux2->letra,aux2->peso);
            aux2=aux2->sig;
        }
        printf("\n");
        aux=aux->sig;
    }
    printf("\n");
}

Lista* Crear(int dato,char letra){
	Lista *nuevo;
	nuevo=(Lista*)malloc(sizeof(Lista));
	nuevo->letra=letra;
	nuevo->peso=dato;
	nuevo->sig=NULL;
	nuevo->ant=NULL;
	nuevo->abajo=NULL;
	return nuevo;
}

ListaExt* CrearExt(int dato,char letra){
	ListaExt *nuevo;
	nuevo=(ListaExt*)malloc(sizeof(ListaExt));
	nuevo->letra=letra;
	nuevo->peso=dato;
	nuevo->nodoP='*';
	nuevo->estado=0;
	nuevo->sig=NULL;
	nuevo->ant=NULL;
	return nuevo;
}

Lista* AltaFinal(Lista *top, int dato, char letra){
	Lista *nuevo, *aux;
	aux=top;
	nuevo=Crear(dato,letra);
	if(aux==NULL){
        return nuevo;
	}else{
		while(aux->sig!=NULL){
			aux=aux->sig;
		}
		aux->sig=nuevo;
		nuevo->ant=aux;
		return top;
	}
}

ListaExt* AltaFinalExt(ListaExt *top, int dato, char letra){
	ListaExt *nuevo, *aux;
	aux=top;
	nuevo=CrearExt(dato,letra);
	if(aux==NULL){
        return nuevo;
	}else{
		while(aux->sig!=NULL){
			aux=aux->sig;
		}
		aux->sig=nuevo;
		nuevo->ant=aux;
		return top;
	}
}

Lista* AltaAbajo(Lista *top, int dato, char letra){
	Lista *nuevo;
	nuevo=Crear(dato,letra);
    top->abajo=nuevo;
    return top;
}

void Consulta(Lista *top){
    char x;
    Lista *aux;
    aux=top;
    while(aux!=NULL){
        x=aux->letra;
        printf("%c-%d ",x,aux->peso);
        aux=aux->sig;
    }
}

void ConsultaExt(ListaExt *top){
    char x;
    ListaExt *aux;
    aux=top;
    while(aux!=NULL){
        x=aux->letra;
        printf("%c ",x);
        aux=aux->sig;
    }
}

void ConsultaA(Lista *top){
    char x;
    Lista *aux;
    aux=top;
    while(aux!=NULL){
        x=aux->letra;
        printf("%c ",x);
        aux=aux->sig;
    }
}

Lista* arbolGenerador(Lista *top){
    int tama=lectura[0],contUsados=0,apuntadorUsados=1,i,existe=0;
    char usados[tama];
    Lista *aux=NULL,*aux2=NULL,*arbolG=NULL;
    char buscado;
    aux=top;

    while(contUsados<9){ //prefiere contadores sobre strlen
        if(contUsados==0){
            printf("Ingrese la letra del nodo raiz para el arbol generador\n"); //por primera vez ingresa un dato, lo guarda en usados y lo establece para buscar su l.a.
            scanf("%c",&buscado);
            usados[contUsados]=buscado;
            contUsados++;
            arbolG=AltaFinal(arbolG,0,buscado);
        }else{
            buscado=usados[apuntadorUsados]; //si no es la primera vez, mueve el apuntador en los usados para asignarlo a buscados y encontrar su l.a.
            apuntadorUsados++;
            //movimiento en el arreglo de usados
        }

        aux=top;
        while(aux!=NULL){ //busqueda de lista de adyacencia
            if(aux->letra==buscado){
                aux2=aux->abajo; //ahora tiene la direccion del inicion de su l.a.
                break;
            }
            aux=aux->sig;
        }

        while(aux2!=NULL){ //recorre l.a del buscado
            existe=0;
            for(i=0;i<tama;i++){
                if(usados[i]==aux2->letra){
                    existe=1;
                    break;
                }
            }

            if(existe==0){
                arbolG=AltaFinal(arbolG,0,aux2->letra);
                usados[contUsados]=aux2->letra;
                contUsados++;
            }

            aux2=aux2->sig;
        }

    }

    return arbolG;
}

void Dijkstra(Lista *top){
    ListaExt *tabla=NULL,*auxFinal=NULL,*aux3=NULL,*aux4=NULL,*aux5=NULL,*aux6=NULL;
    Lista *aux=NULL,*aux2=NULL;
    char buscado,restriccion,alFinal; //definicion de nodo inicio
    int pesoAcumulado=0,pesoTemp,elMasChico=50000,contadorRuta=0,i;
    char letraChica,ultimoGuardado='x';
    int ruta[100];

    fflush(stdin);
    printf("Indique el nodo Inicio\n");
    scanf("%c",&buscado);
    restriccion=buscado;

    fflush(stdin);
    printf("Indique el nodo Destino\n");
    scanf("%c",&alFinal);

    //llenado de tabla con nodos no etiquetados
    aux=top;
    while(aux!=NULL){
        tabla=AltaFinalExt(tabla,50000,aux->letra);
        if(aux->sig==NULL){
            auxFinal=CrearExt(50000,aux->letra);
        }
        aux=aux->sig; //definicion de nodos final (inicial a)
    }


    //inicio del algoritmo de Dijkstra
    while(buscado!=alFinal){
        elMasChico=50000;
        letraChica='x';
        //busqueda de lista de adyacencia del buscado
        aux=top;
        while(aux!=NULL){
            if(aux->letra==buscado){
                aux2=aux->abajo; //ahora tiene la direccion del inicio de su l.a.
                break;
            }
            aux=aux->sig;
        }

        //etiquetado
        while(aux2!=NULL){
            aux3=tabla;
            while(aux3!=NULL){
                if(aux3->letra==aux2->letra){ //aux2 recorre la l.a. y aux3 la tabla
                   pesoTemp=pesoAcumulado+aux2->peso;
                   if(pesoTemp<=aux3->peso && aux3->estado==0 && aux3->letra!=restriccion){
                        aux3->peso=pesoTemp;
                        aux3->nodoP=buscado;
                        //printf("la letra %c ahora se etiqueto como %c %d\n",aux3->letra,aux3->nodoP,aux3->peso);
                   }
                }
               aux3=aux3->sig;
            }
            aux2=aux2->sig;
        }
        //elegir el mas chico
        aux4=tabla;
        while(aux4!=NULL){
            //determina el peso y letra mas chico de la tabla
            if(aux4->estado==0 && aux4->peso <= elMasChico && aux4->letra!=restriccion){
                elMasChico=aux4->peso;
                letraChica=aux4->letra;
            }
             aux4=aux4->sig;
        }
        //printf("el mas chico fue %c con %d\n",letraChica,elMasChico);

            //busca la letra y marca como definitivo
        aux5=tabla;
        while(aux5!=NULL){
            if(aux5->letra==letraChica){
                aux5->estado=1; //definitivo
                //printf("El nodo %c ahora es definitivo, ve estado = %d\n",aux5->letra,aux5->estado);
                buscado=aux5->letra;
                pesoAcumulado=aux5->peso;
                //printf("ahora buscamos adyacentes a %c con un peso acumulado de %d\n",buscado,pesoAcumulado);
            }
            aux5=aux5->sig;
        }
    }

    //obtencion de la ruta a aprtir de los etiquetados de la tabla
    ruta[contadorRuta]=buscado;
    contadorRuta++;
    while(buscado!=restriccion){
        aux6=tabla;
        while(aux6!=NULL){
            if(aux6->letra==buscado){
                ruta[contadorRuta]=aux6->nodoP;
                contadorRuta++;
                buscado=aux6->nodoP;
            }
            aux6=aux6->sig;
        }
    }

    printf("La ruta mas corta de A a I es: ");
    for(i=contadorRuta-1;i>=0;i--){
        printf("%c-",ruta[i]);
    }
    printf("\n");

    printf("El peso final es: %d\n",pesoAcumulado);

}

