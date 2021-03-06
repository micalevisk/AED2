/* http://urs.bira.nom.br/informatica/comando.htm
========================= [ PARA COMPILAR ] ======================
- diretório corrente deve ser ../src

- Para utilizar a ordenação completa, usar na linha de comando:
$ gcc -o transcoder *.c TADS/!(ordenacaoParcial).c

- Para utilizar a ordenação parcial, usar na linha de comando:
$ gcc -o transcoder *.c TADS/!(ordenacaoCompleta).c


========================= [ PARA TESTAR UMA INSTÂNCIA ] =========
- após compilar;
- diretório corrente deve ser ../src
- ./transcoder < ../Dado/instancia.x
{onde 'x' é o número da instância a ser testada}
*/

#include "agenda.h"
#include "evento.h"
#include "job.h"
#include "servico.h"

#include <stdio.h>
#include <stdlib.h>

int main(){
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

		// evento->print(evento);

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

				// destruirEvento(novoEvento);/**/
			}
		} else{

			exit(0);
		}

	}while( !agenda->vazia(agenda) );


	oServico->analytics(oServico);


	return 0;
}
