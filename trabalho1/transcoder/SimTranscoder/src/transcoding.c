/*
$ shopt -s extglob

$ TAD="FILA"
<<<<<<< HEAD
$ TESTES=(10 100 1000 10000 100000 1000000 10000000 )
=======
$ TESTES=(10 15 20)
>>>>>>> 21e873bc897949a54ba604bb8bf0acbe15d0d61e

$ gcc -o transcoder !(heap).c
$ gcc -o transcoder !(fila).c

/////// [ TESTE INDIVIDUAL ] ////////
$ ./transcoder < ../Dado/instancia.10
$ ./transcoder < ../Dado/instancia.15
$ ./transcoder < ../Dado/instancia.20
$ for i in ${TESTES[@]}; do time ./transcoder < ../Dado/instancia.${i}; done

///////////////////////////////// [ MOSTRA A SAÍDA PADRÃO DO PROGRAMA ] /////////////////////////////////////////////////////////////
$ for i in ${TESTES[@]}; do ./transcoder < ../Dado/instancia.${i} | sed -r 's/\[..?m//' > ../testes/teste_${TAD}_instancia.${i}; done

///////////////////////////////// [ MOSTRA A SAÍDA GRÁFICA DO PROGRAMA ] //////////////////////////////////////////////////
$ gcc -Wall -pg -o transcoder !(heap).c
$ for i in ${TESTES[@]}; do ./transcoder < ../Dado/instancia.${i} | sed -r 's/\[..?m//' > _log${i} ; done
$ for i in ${TESTES[@]}; do gprof -b transcoder < ../Dado/instancia.${i}  > ../outputs/outuput_${TAD}_instancia.${i} ; done

///////////////////////////////// [ MOSTRA A SAÍDA PADRÃO DO PROGRAMA E SALVA O TEMPO DE EXECUÇÃO ] ///////////////////////////////////////
$ for i in ${TESTES[@]}; do { time ./transcoder < ../Dado/instancia.${i} ; } 2> ../executionTimes/executionTime_${TAD}_instancia.${i}; done
$ for i in ${TESTES[@]}; do ( time ./transcoder < ../Dado/instancia.${i} ) 2> ../executionTimes/executionTime_${TAD}_instancia.${i}; done
<<<<<<< HEAD

////// [ SALVA O TEMPO DE EXECUÇÃO REAL] //////
$ ( time [cmd] ) |& grep real > realTime
*/

#include <stdio.h>
#include <stdlib.h>
#include "agenda.h"
#include "evento.h"
#include "job.h"
#include "servico.h"

int main(void){
	int nroServidores;
	double relogio, tempoEvento;

	TEvento *evento, *novoEvento;
	TAgenda *agenda;
	TServico *oServico;
	TJob *video, *transVideo;

	scanf("%d", &nroServidores);

	oServico = criarServico(nroServidores);

	//cria agenda de eventos
	agenda = criarAgenda();

	//ler job
	video=criarJob();

	//novo evento a ser agendado
	novoEvento = criarEvento(CHEGADA, video->getTempoChegada(video));
	agenda->novo(agenda,novoEvento);

	do{
		//recuperar o evento
		evento = agenda->proximo(agenda);
		relogio = evento->getTempo(evento);

		evento->print(evento);

		if ( (evento->getTipo(evento) == CHEGADA) && (oServico->ocioso(oServico)) ){
			oServico->chegada(oServico,video);

			oServico->runTranscoding(oServico, video);

			// agenda novo evento
			tempoEvento = relogio+video->getTempoTranscoding(video);
			novoEvento=criarEvento(TRANSCODING, tempoEvento);
			agenda->novo(agenda,novoEvento);

			// transcoding iniciado imediatamente
			video = oServico->saida(oServico);
			destruirJob(video);

			video = criarJob();
			if(video!=NULL){
				// agenda novo evento
				tempoEvento = video->getTempoChegada(video);
				novoEvento = criarEvento(CHEGADA, tempoEvento);
				agenda->novo(agenda,novoEvento);
			}

		} else if (evento->getTipo(evento) == CHEGADA){
			oServico->chegada(oServico,video);

			video = criarJob();
			if (video != NULL){
				// agenda novo evento
				tempoEvento = video->getTempoChegada(video);
				novoEvento = criarEvento(CHEGADA, tempoEvento);
				agenda->novo(agenda, novoEvento);
			}

		} else if(evento->getTipo(evento) == TRANSCODING){
			oServico->stopTranscoding(oServico);

			transVideo = oServico->saida(oServico);
			if (transVideo != NULL){

				oServico->runTranscoding(oServico, transVideo);

				//termino do transcoding
				tempoEvento = relogio + transVideo->getTempoTranscoding(transVideo);

				// agenda novo evento
				novoEvento = criarEvento(TRANSCODING, tempoEvento);
				agenda->novo(agenda, novoEvento);

				destruirJob(transVideo);
			}
		} else{
			printf("PANIC: Evento nao catalogado\n");
			exit(0);
		}

	}while( !agenda->vazia(agenda) );


	oServico->analytics(oServico);


	return 0;
}
