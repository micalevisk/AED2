/*
 * servico.h
 *
 *  Created on: 25/06/2016
 *      Author: cesar
 */

#ifndef SERVICO_H_
#define SERVICO_H_
typedef struct servico TServico;
typedef void* (*TSaidaServico)(TServico *);
typedef void (*TAnalyticServico)(TServico *);
typedef void (*TChegadaServico)(TServico *, void*);
typedef void (*TRunTranscodingServico)(TServico *, void *);
typedef void (*TStopTranscodingServico)(TServico *);
typedef short (*TOciosoServico)(TServico *);

struct servico{
	void *dado;
	TSaidaServico saida;
	TChegadaServico chegada;
	TAnalyticServico analytics;
	TRunTranscodingServico runTranscoding;
	TStopTranscodingServico stopTranscoding;
	TOciosoServico ocioso;
};
TServico* criarServico(int nroServidores);



#endif /* SERVICO_H_ */
