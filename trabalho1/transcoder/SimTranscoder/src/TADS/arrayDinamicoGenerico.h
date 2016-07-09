// TAD Vetor Dinâmico Circular
typedef struct arraydinamico TArrayDinamico;

typedef void*	(*TAcessarAD)(TArrayDinamico*,int);
typedef void 	(*TAtualizarAD)(TArrayDinamico*,int,void*);

struct arraydinamico{
	void* dado;
	unsigned tamanho;

	TAcessarAD acessar;
	TAtualizarAD atualizar;
};

TArrayDinamico* criarAD(unsigned);
void destruirAD(TArrayDinamico*);
unsigned tamanhoAD(TArrayDinamico*);
void ajustarAD(TArrayDinamico*, unsigned); // realoca  o vetor.
