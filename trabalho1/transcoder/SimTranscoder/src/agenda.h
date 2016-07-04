
typedef struct agenda TAgenda;
typedef void* (*TProximoAgenda)(TAgenda* agenda);
typedef void (*TNovoAgenda)(TAgenda *agenda, void *evento);
typedef short (*TVaziaAgenda)(TAgenda *agenda);

struct agenda{
	void *dado;

	TProximoAgenda proximo;
	TNovoAgenda novo;
	TVaziaAgenda vazia;
};

TAgenda *criarAgenda();
