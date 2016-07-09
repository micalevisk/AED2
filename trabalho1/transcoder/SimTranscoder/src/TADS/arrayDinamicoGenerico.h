// TAD Vetor Dinâmico
typedef struct arraydinamico TArrayDinamico;

typedef void*	(*TTamanhoAD)(TArrayDinamico*);
typedef void*	(*TAcessarAD)(TArrayDinamico*,int);
typedef void 	(*TAtualizarAD)(TArrayDinamico*,int,void*);

struct arraydinamico{
	void* dado;

	TTamanhoAD tamanho;
	TAcessarAD acessar;
	TAtualizarAD atualizar;
};

TArrayDinamico* construirAD(unsigned);
void destruirAD(TArrayDinamico*);
void ajustarAD(TArrayDinamico*, unsigned); // realoca  o vetor.
// unsigned tamanhoAD(TArrayDinamico*);
