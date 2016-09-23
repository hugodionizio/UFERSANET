/*
 * Rede.h
 *
 *  Created on: 11/09/2016
 *      Authors: 
 *				Hugo Dionizio Santos
 */
#ifndef REDE_H_
#define REDE_H_

typedef struct Rede {
	char nomeSubrede[20];
	int numEnderecos;
	int bits;
	int redePrincipal[4];
	int subRede[4];
	int cidr;
	int mascara[4];
} Rede;

int teto(float);
int piso(float);
void copiarIP(int *, int [4]);
void imprimirRedePrincipal(Rede);
void imprimirRede(Rede);
void imprimirRedeEmLinha(Rede);
void segmentarRede(Rede, Rede *);
void configurarIP(int *, int, int, int, int);
void inicializarRede(Rede *, char [20], int, int [4]);

#endif /* REDE_H_ */
