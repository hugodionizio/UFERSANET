#include <math.h>
#include <stdio.h>

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
	int rede[4];
	int subRede[4];
	int cidr;
	int mascara[4];
} Rede;


int teto(float num) {
	return (int)(num)+1;
}

int piso(float num) {
	return (int)(num);
}

int segmentarRede(int numEnderecos, int rede[]) {
	int bits = teto(log((float)numEnderecos)/log(2)),
		cidr = 0;
	int i;
	int mascara[4];
	Rede subRede;
	subRede.numEnderecos = numEnderecos;
	subRede.
	subRede.
	subRede.
	subRede.
	
	for(i = 4-1; i > -1 && rede[i] == 0; i--) mascara[i] = 0;
	cidr+=(i+1)*8+(8-bits);
	mascara[i+1] = 256-pow(2,8*(piso((float)cidr/8)+1)-cidr);
	for(; i > -1; i--) mascara[i] = 255;
	
	printf("\n%d endereços requer %d bits\n", numEnderecos, bits);
	printf("Rede/CIDR: %d.%d.%d.%d/%d\n", rede[0], rede[1], rede[2], rede[3], cidr);
	printf("Máscara de rede: %d.%d.%d.%d\n", mascara[0], mascara[1], mascara[2], mascara[3]);
	
	return mascara[3];	
}

void configurarIP(int *rede, int oct1, int oct2, int oct3, int oct4) {
	rede[0] = oct1;
	rede[1] = oct2;
	rede[2] = oct3;
	rede[3] = oct4;
}

int main (int argc, char *argv[]) {
	int rede[4] = {192,168,50,0};
	int ultOct;
	
	ultOct = segmentarRede(100, rede);
	configurarIP(rede, 192, 168, 50, ultOct);
	
	ultOct = segmentarRede(50, rede);
	configurarIP(rede, 192, 168, 50, ultOct);
	
	ultOct = segmentarRede(15, rede);
	configurarIP(rede, 192, 168, 50, ultOct);
	
	ultOct = segmentarRede(7, rede);
	configurarIP(rede, 192, 168, 50, ultOct);
	
	ultOct = segmentarRede(2, rede);
	configurarIP(rede, 192, 168, 50, ultOct);
	
	segmentarRede(2, rede);
	
	return 0;
}
