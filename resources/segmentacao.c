#include <math.h>
#include <stdio.h>
#include <string.h>

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

typedef struct Rede {
	char nomeSubrede[20];
	int numEnderecos;
	int bits;
	int redePrincipal[4];
	int subRede[4];
	int cidr;
	int mascara[4];
} Rede;

int teto(float num) {
	return (int) (num) + 1;
}

int piso(float num) {
	return (int) (num);
}

void copiarIP(int *ipA, int ipB[4]) {
	int i;

	for (i = 0; i < 4; i++) {
		ipA[i] = ipB[i];
	}
}

void imprimirRedePrincipal(Rede rede) {
	printf("Rede/CIDR: %d.%d.%d.%d/%d\n", rede.subRede[0], rede.subRede[1],
			rede.subRede[2], rede.subRede[3], rede.cidr);
}

void imprimirRede(Rede rede) {
	printf("\n%d endereços requer %d bits\n", rede.numEnderecos, rede.bits);
	imprimirRedePrincipal(rede);
	printf("Máscara de rede: %d.%d.%d.%d\n", rede.mascara[0], rede.mascara[1],
			rede.mascara[2], rede.mascara[3]);
}

void imprimirRedeEmLinha(Rede rede) {
	printf("%s\t%d.%d.%d.%d/%d\t%d.%d.%d.%d-%d.%d.%d.%d\t%d.%d.%d.%d\n",
			rede.nomeSubrede, rede.subRede[0], rede.subRede[1], rede.subRede[2],
			rede.subRede[3], rede.cidr, rede.subRede[0], rede.subRede[1],
			rede.subRede[2], (rede.subRede[3] + 1), rede.subRede[0],
			rede.subRede[1], rede.subRede[2], (rede.mascara[3] - 2),
			rede.subRede[0], rede.subRede[1], rede.subRede[2],
			(rede.mascara[3] - 1));
}

void segmentarRede(Rede subRedeAnterior, Rede *subRede) {
	int numEnderecos = subRede->numEnderecos;
	int rede[4];
	int bits = teto(log((float) numEnderecos) / log(2)), cidr = 0;
	int i;
	int mascara[4];

	copiarIP(rede, (int *) subRede->redePrincipal);
	subRede->bits = bits;

	if (strcmp(subRedeAnterior.nomeSubrede, subRede->nomeSubrede) == 0) {
		copiarIP(subRede->subRede, (int *) subRede->redePrincipal);
	} else {
		copiarIP(subRede->subRede, (int *) subRede->redePrincipal);
		subRede->subRede[3] = subRedeAnterior.mascara[3];
	}

	for (i = 4 - 1; i > -1 && rede[i] == 0; i--) {
		mascara[i] = 0;
		subRede->mascara[i] = mascara[i];
	}

	cidr += (i + 1) * 8 + (8 - bits);
	subRede->cidr = cidr;

	mascara[i + 1] = 256 - pow(2, 8 * (piso((float) cidr / 8) + 1) - cidr);
	subRede->mascara[i + 1] = mascara[i + 1];
	for (; i > -1; i--) {
		mascara[i] = 255;
		subRede->mascara[i] = mascara[i];
	}
}

void configurarIP(int *rede, int oct1, int oct2, int oct3, int oct4) {
	rede[0] = oct1;
	rede[1] = oct2;
	rede[2] = oct3;
	rede[3] = oct4;
}

void inicializarRede(Rede *subRede, char nomeSubrede[20], int redePrincipal[4]) {
	strcpy(subRede->nomeSubrede, nomeSubrede);
	copiarIP(subRede->redePrincipal, redePrincipal);
}

int main(int argc, char *argv[]) {
	int redePrincipal[4] = { 192, 168, 50, 0 };
	int ultOct;
	char ch[20];

	int numRedes = 6;
	Rede redes[numRedes];
	int i;

	ch[1] = '\0';
	for (i = 0; i < numRedes; ++i) {
		ch[0] = 65 + i;
		inicializarRede(&redes[i], ch, redePrincipal);
//		imprimirRedePrincipal(redes[i]);
	}

	redes[0].numEnderecos = 100;
	redes[1].numEnderecos = 50;
	redes[2].numEnderecos = 15;
	redes[3].numEnderecos = 7;
	redes[4].numEnderecos = 2;
	redes[5].numEnderecos = 2;

	for (i = 0; i < numRedes; ++i) {
		if (i > 0)
			segmentarRede(redes[i - 1], &redes[i]);
		else
			segmentarRede(redes[i], &redes[i]);
		imprimirRede(redes[i]);
	}

	printf(
			"Sub-rede\tSub-rede/Máscara\tFaixa de Endereços Utilizáveis\tEndereço de Broadcast\n");
	for (i = 0; i < numRedes; ++i) {
		imprimirRedeEmLinha(redes[i]);
	}

	return (0);
}
