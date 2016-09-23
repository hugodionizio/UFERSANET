/*
 * IPv4.h
 *
 *  Created on: 11/09/2016
 *      Authors: 
 *				Hugo Dionizio Santos
 */
#ifndef IP_H_
#define IP_H_

typedef struct IPv4 {
	// Tipo - Posição no formato
	// 1ª linha
	int versao; // 0º ao 3º bit
	int tamCabecalho; // 4º a 7º bit
	int tipoServico; // 8º a 15º bit
	int tamanhoDatagrama; // 16º ao 31º bit

	// 2ª linha
	int identificador; // 0º ao 15º bit
	int flags; // 16º ao 18º bit
	int deslocamentoFragmentacao; // 19º ao 31º bit

	// 3ª linha
	int ttl; // 0º ao 7º bit
	int protocoloNivelSuperior; // 8º ao 15º bit
	int checksumCabecalho; // 16º ao 31º bit

	// 4ª e 5ª linhas
	int enderecoOrigem; // 0º ao 31º bit
	int enderecoDestino; // 0º ao 31º bit

	// 6ª linha
	int opcoes; // 0º ao nº bit, n < 32
	int preenchimento; // n+1º ao 31º bit (0000...00), n > 0
	int dados; // 0º ao 31º bit
} IPv4;

#endif /* IP_H_ */
