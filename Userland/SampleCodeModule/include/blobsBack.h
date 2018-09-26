#ifndef BLOBSBACK_H
#define BLOBSBACK_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define JUGADORALETRA(j) ((j==1) ? 'A' : 'Z' )
#define OTROJUGADOR(j) ((j=='A') ? 'Z' : 'A' )
#define SUMAMANCHA(j) if(j=='A') (*partida).manchasA++;else (*partida).manchasZ++;

#define BLOQUECHICO 20
#define BLOQUEMEDIANO 60
#define BLOQUEGRANDE 100

enum{DISTINTOEXITO=0, EXITO, MOV_NO_PERMITIDO, NO_EXISTE_POSICION};
enum{LEE_Y_MUEVE=1, GUARDA_PARTIDA, SALE_SIN_GUARDAR, SALE_Y_GUARDA};

typedef struct{
	int modojuego;
	int turno;
	int filas;
	int columnas;
	int manchasA;
	int manchasZ;
	char **tablero;
	char *s;
	int deFil;
	int deCol;
	int aFil;
	int aCol;
}	tipoPartida;

int recuperarPartida(tipoPartida *partida);
int guardarPartida(const tipoPartida *partida);
void turnoAleatorio(tipoPartida *partida);
int creaTableroVacio(tipoPartida *partida);
int creaTablero(tipoPartida *partida);
int muevePosicion(tipoPartida *partida);
void cambiaFichas(tipoPartida *partida);
void llenaLugares(tipoPartida *partida);
int quedanLugares(const tipoPartida *partida);
int buscaLugar(const tipoPartida *partida);
int hayLugar(const tipoPartida *partida, int fil, int col);
int aleatorioEntre(int izq, int der);
void mueveComputadora(tipoPartida *partida);
int agregaMovPosible(tipoPartida *partida, unsigned char *vec, int *i);
int buscaMovPosible(tipoPartida *partida);
int buscaFichaComputadora(tipoPartida *partida);
void mueveFichaComputadora(tipoPartida *partida);
void movRandomEntreIguales(tipoPartida *partida, unsigned char *vec, int dim);
int cuentaFichasPosibles(const tipoPartida *partida);
void liberaTablero(tipoPartida *partida);

#endif