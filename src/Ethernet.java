import java.util.Random;
import java.math.*;

public class Ethernet {
	int numColisoes;
	boolean colisao[];
	int numSlots;
	int slot[];
	float piorTempoPropagacao;
	int numEstacoes;
	Estacao estacao[];
	Estacao tmp;

	float tempo;

	// Após a colisão,
	public boolean ocorreuColisao() {
		return true;
	}

	// o tempo é dividido em slot discretos,
	public int dividirTempoSlots() {
		// cujo tamanho é igual ao
		int tamanho = 0;
		// pior tempo de propagação de ida e
		// volta (51,2 μs)
		float tempoPropagacaoIda;
		float tempoPropagacaoVolta;
		
		return tamanho;
	}

	// • Depois da 1a colisão,
	public void ocorreuPrimeiraColisao() {
		// cada estação espera 0 ou 1 slot antes de tentar novamente
		for (int i = 0; i < estacao.length; i++) {
			if (slot[0] == 0 || slot[1] == 0)
				estacao[i].tentarNovamente();
			// – Se duas estações escolherem o mesmo número aleatório,
			// seus quadros colidirão novamente
			for (int j = 0; j < estacao.length; j++) {
				if (estacao[i] == estacao[j]) {
					quadroColidirNovamente(i, j);
				}
			}
		}
	}

	// • Depois da 2a colisão,
	public int ocorreuSegundaColisao() {
		int num = 0;
		// cada uma seleciona ao acaso 0, 1, 2 ou 3 slot e
		for (int i = 0; i < estacao.length; i++) {
			estacao[i].seleciona(0, 3, true);
			// aguarda durante esse tempo
			while (tempo < piorTempoPropagacao) {
				// Se ocorrer uma 3a colisão,
				if (ocorreuTerceiraColisao()) {
					// a quantidade de slot que as estações terão que aguardar
					// será escolhido
					// ao acaso no intervalo de 0 a 2^3 − 1 slot
					piorTempoPropagacao = (float) (Math.pow(2, 3) - 1);
					// – Em geral, após i colisões,
					// é escolhido um número aleatório entre 0 e 2^i − 1 slot
					num = escolher(0, (int)(Math.pow(2, i)) -1);
				}
			}
		}
		
		return num;
	}

	// • Entretanto, após alcançadas dez colisões,
	public void ocorreuDecimaColisao() {
		// o intervalo de randomização será congelado em 1023 slot
		int numIntervaloStots = 1023;
	}

	// • Após 16 colisões,
	public void ocorreuDecimaSextaColisao() {
		// as tentativas de transmissão são definitivamente abortadas
		boolean novasTentativas = false;
	}

	private void quadroColidirNovamente(int i, int j) {
		// TODO Auto-generated method stub

	}

	private boolean ocorreuTerceiraColisao() {
		// TODO Auto-generated method stub
		return false;
	}

	private int escolher(int i, int j) {
		// TODO Auto-generated method stub
		return 0;
	}
	public void recuoBinarioExponencial() {
		if (ocorreuColisao()) {
			numSlots = dividirTempoSlots();
			for (int i = 0; i < numSlots; i++) {
				dividirTempoSlots();
				switch(i) {
				case 1: 
					ocorreuPrimeiraColisao();
					break;
				case 2: 
					ocorreuSegundaColisao();
					break;
				case 3:
					ocorreuDecimaColisao();
					break;
				case 4:
					ocorreuDecimaSextaColisao();
					break;
				}
			}
		}
	}

	private int aleatorio() {
		// TODO Auto-generated method stub
		return 0;
	}
}