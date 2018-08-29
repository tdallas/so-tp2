#include <blobsBack.h>

int recuperarPartida(tipoPartida *partida){
	
  	return 1;
}

int guardarPartida(const tipoPartida *partida){
	
	return 1;
}

void liberaTablero(tipoPartida *partida){
	int i;

	for(i=0;i<(*partida).filas;i++){
		free(*((*partida).tablero+i));
	}
	free((*partida).tablero);
	return;
}

void turnoAleatorio(tipoPartida *partida){
	if(((int)rand())%2==1)
		(*partida).turno=1;
	else
		(*partida).turno=2;
	return;
}

int creaTableroVacio(tipoPartida *partida){
	int i;

	//esta funcion se usa solamente para cuando se recupera una partida
	(*partida).tablero=malloc((*partida).filas*sizeof(char*));
	if((*partida).tablero==NULL)
		return 1;
	for(i=0;i<(*partida).filas;i++){
		*((*partida).tablero+i)=malloc((*partida).columnas*sizeof(char));
		if(*((*partida).tablero+i)==NULL)
			return 1;
	}
	return 0;
}

int creaTablero(tipoPartida *partida){
	int i;

	(*partida).tablero=malloc((*partida).filas*sizeof(char*));
	if((*partida).tablero==NULL)
		return 1;
	for(i=0;i<(*partida).filas;i++){
		*((*partida).tablero+i)=malloc((*partida).columnas*sizeof(char));
		if(*((*partida).tablero+i)==NULL)
			return 1;
	}
	(*partida).tablero[0][0]='A';
	(*partida).tablero[(*partida).filas-1][0]='A';
	(*partida).tablero[0][(*partida).columnas-1]='Z';
	(*partida).tablero[(*partida).filas-1][(*partida).columnas-1]='Z';
	return 0;
}

int muevePosicion(tipoPartida *partida){
	int difFil, difCol, resultado;
	char jugador, otrojugador;

	difFil=abs((*partida).aFil-(*partida).deFil);
	difCol=abs((*partida).aCol-(*partida).deCol);
	jugador=JUGADORALETRA((*partida).turno);
	otrojugador=OTROJUGADOR(jugador);
	if((*partida).deFil>((*partida).filas-1) || (*partida).deFil<0 ||\
	(*partida).aFil>((*partida).filas-1) || (*partida).aFil<0 ||\
	(*partida).deCol>((*partida).columnas-1) || (*partida).deCol<0 ||\
	(*partida).aCol>((*partida).columnas-1) || (*partida).aCol<0)\
	//Si se pasa de los limites del tablero, no existe la posicion
		resultado=NO_EXISTE_POSICION;
	else if((*partida).tablero[(*partida).aFil][(*partida).aCol]==otrojugador ||\
	(*partida).tablero[(*partida).deFil][(*partida).deCol]!=jugador ||\
	difFil>2 || difCol>2)\
	//Si en alguna de las posiciones hay una ficha del otro jugador 
	//o si el movimiento se pasa de 2 lugares
		resultado=MOV_NO_PERMITIDO;
	else if((difFil==1 && difCol==1) || (difFil==0 && difCol==1) ||\
	(difFil==1 && difCol==0))\
	{
	//Caso mueve una posicion
		SUMAMANCHA(jugador)
		cambiaFichas(partida);
		resultado=EXITO;
	}
	else if((difFil==2 && difCol==2) || (difFil==2 && difCol==1) ||\
	(difFil==1 && difCol==2) || (difFil==0 && difCol==2) ||\
	(difFil==2 && difCol==0))\
	{
	//Caso mueve dos posiciones
		(*partida).tablero[(*partida).deFil][(*partida).deCol]=0;
		cambiaFichas(partida);
		resultado=EXITO;
	}
	return resultado;
}

void cambiaFichas(tipoPartida *partida){
	int i, j, limitei, limitej;
	char jugador, otrojugador;

	jugador=JUGADORALETRA((*partida).turno);
	otrojugador=OTROJUGADOR(jugador);

	//asigna ficha de jugador en la posicion
	(*partida).tablero[(*partida).aFil][(*partida).aCol]=jugador;

	//defino limites de fichas que deben cambiarse
	//si estos se pasan de los bordes entonces le cambio el valor

	limitei=((*partida).aFil+2);
	if(limitei>(*partida).filas)
		limitei=(*partida).filas;

	limitej=((*partida).aCol+2);
	if(limitej>(*partida).columnas)
		limitej=(*partida).columnas;

	for(i=((*partida).aFil-1); i<limitei ; i++){
		if(i<0)
			i=0;
		for(j=((*partida).aCol-1); j<limitej ; j++){
			if(j<0)
				j=0;
			if((*partida).tablero[i][j]==otrojugador){
				(*partida).tablero[i][j]=jugador;
				if(jugador=='A'){
					(*partida).manchasA++;
					(*partida).manchasZ--;
				}
				else{
					(*partida).manchasZ++;
					(*partida).manchasA--;	
				}
			}
		}
	}
	return;
}

void llenaLugares(tipoPartida *partida){
	char jugador;
	int i, j;

	//llena los espacios libres con fichas del jugador que gano

	if((*partida).manchasA>(*partida).manchasZ)
		jugador='A';
	else
		jugador='Z';

	for(i=0;i<(*partida).filas;i++){
		for(j=0;j<(*partida).columnas;j++){
			if((*partida).tablero[i][j]==0){
				(*partida).tablero[i][j]=jugador;
				SUMAMANCHA(jugador)
			}
		}
	}
}

int buscaLugar(const tipoPartida *partida){
	int i, j;
	char jugador;
	jugador=JUGADORALETRA((*partida).turno);
	if(quedanLugares(partida)){
		//primero chequeo si hay lugares libres
		//luego verifico si son movimientos posibles del jugador
		for(i=0;i<(*partida).filas;i++)
			for(j=0;j<(*partida).columnas;j++)
				if((*partida).tablero[i][j]==jugador)
					if(hayLugar( partida, i, j))
						return 1;
		return 0;
	}
	else
		return 0;
}

int quedanLugares(const tipoPartida *partida){
	int i, j;

	//devuelve 1 si encontro lugares libres, 0 si no

	for(i=0; i<(*partida).filas;i++)
		for(j=0;j<(*partida).columnas;j++)
			if((*partida).tablero[i][j]==0)
				return 1;

	return 0;
}

int hayLugar(const tipoPartida *partida, int fil, int col){
	int i, j, limitei, limitej;

	//defino limites de donde debe fijarse si encuentra un movimiento posible
	//si estos se pasan de los bordes entonces le cambio el valor
	//funcion retorna 1 con el primer espacio libre saliendo desde fil y col

	limitei=(fil+3);
	if(limitei>(*partida).filas)
		limitei=(*partida).filas;

	limitej=(col+3);
	if(limitej>(*partida).columnas)
		limitej=(*partida).columnas;

	for(i=(fil-2);i<limitei;i++){
		if(i<0)
			i=0;
		for(j=(col-2);j<limitej;j++){
			if(j<0)
				j=0;
			if((*partida).tablero[i][j]==0)
				return 1;
		}
	}
	return 0;
}

int aleatorioEntre(int izq, int der){
	return izq + (der - izq + 1) * (rand() / ((double)RAND_MAX+1));
}

void mueveComputadora(tipoPartida *partida){
	int contMaxFichas=0, indiceMovsPosibles=0, contAux, sizeVec;
	int flagMovPosible, flagBuscaFicha, flagAgrega;
	int difFil, difCol;
	int tipoBloque;

	//defini tres tipos distintos de bloques porque si el tablero es muy grande
	//para guardar los posibles movimientos va a tener que realizar mas alloc
	//entonces aca defino, de acuerdo al tamaño del tablero, que bloque utilizo
	if((*partida).filas>20 || (*partida).columnas>20)
		tipoBloque=BLOQUEGRANDE;
	else if((*partida).filas>10 || (*partida).columnas>10)
		tipoBloque=BLOQUEMEDIANO;
	else
		tipoBloque=BLOQUECHICO;

	unsigned char *movsPosibles=malloc(tipoBloque*sizeof(unsigned char));

	sizeVec=tipoBloque;

	//comienzo desde la col -1, porque la fx buscaFichaComputadora, comienza
	//desde la siguiente columna, asi no repite fichas 

	(*partida).deFil=0;
	(*partida).deCol=-1;
	do{
		flagBuscaFicha=buscaFichaComputadora(partida);

		//lo mismo aca para las columnas, comienza una atras porque, la fx
		//buscaMovPosible comienza en la siguiente columna, para no repetir 
		//movimientos posibles
		(*partida).aFil=((*partida).deFil-2);
		(*partida).aCol=((*partida).deCol-3);
		if(flagBuscaFicha==1){
			do{
				flagMovPosible=buscaMovPosible(partida);
				if(flagMovPosible==1){
					contAux=0;
					difFil=abs((*partida).aFil-(*partida).deFil);
					difCol=abs((*partida).aCol-(*partida).deCol);

					//si el movimiento es de 1 posicion, entonces el contador
					//comienza en 1 porque ya esta ganando una ficha
					if((difFil==1 && difCol==1) || (difFil==0 && difCol==1) ||\
					(difFil==1 && difCol==0))\
						contAux=1;

					contAux+=cuentaFichasPosibles(partida);
					
					if(contAux>0){
						if(contAux>contMaxFichas){
							contMaxFichas=contAux;
							sizeVec=indiceMovsPosibles;
							indiceMovsPosibles=0;
							//indice es cero porque empieza el vector denuevo
							movsPosibles[indiceMovsPosibles++]=(*partida).deFil;
							movsPosibles[indiceMovsPosibles++]=(*partida).deCol;
							movsPosibles[indiceMovsPosibles++]=(*partida).aFil;
							movsPosibles[indiceMovsPosibles++]=(*partida).aCol;
						}
						else if(contAux==contMaxFichas){
							if((indiceMovsPosibles%tipoBloque)==0 &&\
							indiceMovsPosibles>=sizeVec)\
							{
								//llama a la fx agregaMovPosible, que agranda
								//el vector
								flagAgrega=agregaMovPosible(partida,\
								movsPosibles, &indiceMovsPosibles);\
								if(flagAgrega==0){
									//corta y elige porque se quedo sin memoria
									flagMovPosible=0;
									flagBuscaFicha=0;
								}
							}
							else{
								movsPosibles[indiceMovsPosibles++]=(*partida).deFil;
								movsPosibles[indiceMovsPosibles++]=(*partida).deCol;
								movsPosibles[indiceMovsPosibles++]=(*partida).aFil;
								movsPosibles[indiceMovsPosibles++]=(*partida).aCol;
							}
						}
					}
				}
			}while(flagMovPosible==1);
		}
	}while(flagBuscaFicha==1);

	if(indiceMovsPosibles>4){
		//elige un movimiento al azar, entre todos los que ya guardo
		movRandomEntreIguales(partida, movsPosibles, indiceMovsPosibles);
		mueveFichaComputadora(partida);
	}
	else if(indiceMovsPosibles==4){
		(*partida).deFil=movsPosibles[0];
		(*partida).deCol=movsPosibles[1];
		(*partida).aFil=movsPosibles[2];
		(*partida).aCol=movsPosibles[3];
		mueveFichaComputadora(partida);
	}

	free(movsPosibles);

	return;
}

int agregaMovPosible(tipoPartida *partida, unsigned char *vec, int *i){
	int tipoBloque;

	//defino, de acuerdo al tamaño del tablero, que bloque utilizo

	if((*partida).filas>20 || (*partida).columnas>20)
		tipoBloque=BLOQUEGRANDE;
	else if((*partida).filas>10 || (*partida).columnas>10)
		tipoBloque=BLOQUEMEDIANO;
	else
		tipoBloque=BLOQUECHICO;

	unsigned char *aux=malloc(((*i)+tipoBloque)*sizeof(unsigned char));
	memcpy(aux, vec, ((*i))*sizeof(unsigned char));
	
	if(aux!=NULL){
		vec=aux;
		vec[(*i)++]=(*partida).deFil;
		vec[(*i)++]=(*partida).deCol;
		vec[(*i)++]=(*partida).aFil;
		vec[(*i)++]=(*partida).aCol;
		return 1;
	}
	else{
		return 0;
	}
}

int buscaMovPosible(tipoPartida *partida){
	int i, j, limitei, limitej;

	//defino limites, y si se pasan los achico
	limitei=((*partida).deFil+3);
	if(limitei>(*partida).filas)
		limitei=(*partida).filas;

	limitej=((*partida).deCol+3);
	if(limitej>(*partida).columnas)
		limitej=(*partida).columnas;

	i=(*partida).aFil;
	if(i<0)
		i=0;
	//primero comienzo por la fila y columna siguiente a donde quedo
	for(j=((*partida).aCol+1);j<limitej;j++){
		if(j<0)
			j=0;
		if((*partida).tablero[i][j]==0){
			(*partida).aFil=i;
			(*partida).aCol=j;
			return 1;
		}
	}
	//si en esa fila no encuentra, sigue comunmente
	for(i=((*partida).aFil+1);i<limitei;i++){
		if(i<0)
			i=0;
		for(j=((*partida).deCol-2);j<limitej;j++){
			if(j<0)
				j=0;
			if((*partida).tablero[i][j]==0){
				(*partida).aFil=i;
				(*partida).aCol=j;
				return 1;
			}
		}
	}
	return 0;
}

int buscaFichaComputadora(tipoPartida *partida){
	int i, j;

	char fichaTurno = JUGADORALETRA(partida->turno);

	//primero comienzo por la fila y columna siguiente a donde quedo
	i=(*partida).deFil;
	for(j=((*partida).deCol+1);j<(*partida).columnas;j++){
		if(j<0)
			j=0;
		if((*partida).tablero[i][j]==fichaTurno){
			(*partida).deFil=i;
			(*partida).deCol=j;
			return 1;
		}
	}
	//si en esa fila no encuentra, sigue comunmente
	for(i=((*partida).deFil+1);i<(*partida).filas;i++)
		for(j=0;j<(*partida).columnas;j++)
			if((*partida).tablero[i][j]==fichaTurno){
				(*partida).deFil=i;
				(*partida).deCol=j;
				return 1;
			}
	return 0;
}

void mueveFichaComputadora(tipoPartida *partida){
	//La diferencia entre esta fx y muevePosicion es que esta no valida los movs
	//porque ya son validos
	int difFil, difCol;

	difFil=abs((*partida).aFil-(*partida).deFil);
	difCol=abs((*partida).aCol-(*partida).deCol);
	if((difFil==1 && difCol==1) || (difFil==0 && difCol==1) ||\
	(difFil==1 && difCol==0))\
	{
	//Caso mueve una posicion
		SUMAMANCHA(JUGADORALETRA(partida->turno))
		cambiaFichas(partida);
	}
	else if((difFil==2 && difCol==2) || (difFil==2 && difCol==1) ||\
	(difFil==1 && difCol==2) || (difFil==0 && difCol==2) ||\
	(difFil==2 && difCol==0))\
	{
	//Caso mueve dos posiciones
		(*partida).tablero[(*partida).deFil][(*partida).deCol]=0;
		cambiaFichas(partida);
	}
	return;
}

void movRandomEntreIguales(tipoPartida *partida, unsigned char *vec, int dim){
	int dimaux, posrandom, i;


	dimaux=(dim/4);
	posrandom=aleatorioEntre(0, (dimaux-1));
	i=posrandom*4;
	(*partida).deFil=vec[i];
	(*partida).deCol=vec[i+1];
	(*partida).aFil=vec[i+2];
	(*partida).aCol=vec[i+3];

	return;
}

int cuentaFichasPosibles(const tipoPartida *partida){
	int i, j, limitei, limitej, contFichas=0;

	char fichaContraria = (partida->turno==1) ? 'Z' : 'A' ;

	//defino los limites de donde podria ganar fichas, si se pasan los achico
	limitei=((*partida).aFil+2);
	if(limitei>(*partida).filas)
		limitei=(*partida).filas;
	
	limitej=((*partida).aCol+2);
	if(limitej>(*partida).columnas)
		limitej=(*partida).columnas;
	
	for(i=((*partida).aFil-1); i<limitei ; i++){
		if(i<0)
			i=0;
		for(j=((*partida).aCol-1); j<limitej ; j++){
			if(j<0)
				j=0;
			if((*partida).tablero[i][j]==fichaContraria){
				contFichas++;
			}
		}
	}
	
	return contFichas;
}