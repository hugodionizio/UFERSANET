/*
 * IP.h
 *
 *  Created on: 11/09/2016
 *      Authors: 
 *				Hugo Dionizio Santos
 */
#ifndef IP_H_
#define IP_H_

typedef struct IP {
	// 1ª linha
	int versao; //  a  bits
	int tamCabecalho; //  a  bits
	int tipoServico; //  a  bits
	int tamanhoDatagrama; //  a  bits

	// 2ª linha
	int identificador; //  a  bits
	int flags; //  a  bits
	int deslocamentoFragmentacao; //  a  bits

	// 3ª linha
	int protocoloNivelSuperior; //  a  bits
	int checksumCabecalho; //  a  bits

	// 4ª e 5ª linhas
	int enderecoOrigem; //  a  bits
	int enderecoDestino; //  a  bits

	// 6ª linha
	int opcoes; //  a  bits
	int preenchimento; //  a  bits (0000...00)
	int dados;
} IP;

#endif /* IP_H_ */
