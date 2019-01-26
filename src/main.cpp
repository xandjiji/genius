#include <allegro.h>
#include <stdlib.h>
#include <time.h>

#include "node.h"
#include "fila.h"
#include "operacoes.h"

int main()
{
    // inicializaçao padrao do allegro:
    BITMAP *buffer = NULL;
    allegro_init();
    set_color_depth(32);
    install_keyboard();
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
    buffer = create_bitmap(SCREEN_W, SCREEN_H);

	fila computador; // onde a sequencia de cores sera armazenada
	fila jogador; // onde o jogador ira entrar com a sequencia de cores a cada rodada

	// (por algum motivo o compilador nao me deixou inicializar os headers como null na classe)
	computador.header = NULL;
	jogador.header = NULL;

	nodePtr aux;
	bool perdeu = false; // condiçao de derrota/vitoria da partida


    // tela inicial:
	while(!key[KEY_SPACE] && !key[KEY_ESC]){ // tecla ESC sai do jogo ou tecla ESPAÇO inicia o jogo

		// variaveis para as funçoes "pisca"
		int vermelho = 0;
    	int azul = 0;
    	int verde = 0;
    	int amarelo = 0;


         // as variaveis mudam de valor conforme as setas sao pressionadas fazendo com que as cores pisquem
        if(key[KEY_UP])
        {
            vermelho = 1;
        }
        if(key[KEY_DOWN])
        {
            verde = 1;
        }
        if (key[KEY_LEFT])
        {
            azul = 1;
        }
        if (key[KEY_RIGHT])
        {
            amarelo = 1;
        }

        clear(buffer);

        // textos
		textprintf_ex(buffer, font, 20, 20, makecol(255, 255, 255), -1, "Pressione ESPACO para iniciar!");
		textprintf_ex(buffer, font, 20, 450, makecol(255, 255, 255), -1, "(Pressione ESC para sair!)");

        // quadrados
        rectfill(buffer, 229, 170, 400, 60, makecol(vermelhopiscar(vermelho), 0, 0));
		rectfill(buffer, 52, 171, 228, 279, makecol(0, azulpiscar(azul), 255));
		rectfill(buffer, 401, 171, 570, 279, makecol(255, 255, amarelopiscar(amarelo)));
		rectfill(buffer, 229, 280, 400, 390, makecol(0, verdepiscar(verde), 0));

        // textos dos quadrados
        textprintf_ex(buffer, font, 303, 112, makecol(0, 0, 0), -1, "cima");
        textprintf_ex(buffer, font, 110, 223, makecol(0, 0, 0), -1, "esquerda");
        textprintf_ex(buffer, font, 461, 223, makecol(0, 0, 0), -1, "direita");
		textprintf_ex(buffer, font, 297, 332, makecol(0, 0, 0), -1, "baixo");

        // "desenha" o buffer
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
	}

    // garante que as duas filas comecem como vazias
	while(jogador.header != NULL){
				remove(jogador);
		}
	while(computador.header != NULL){
				remove(jogador);
		}


    // loop principal do progresso do jogo
    while(!key[KEY_ESC] && perdeu == false){ // ocorrera enquanto o jogador nao tiver errado a sequencia

        // a cada loop completo, a fila do jogador volta a ser vazia
		while(jogador.header != NULL){
				remove(jogador);
		}

        // sorteando uma cor para ser inserida na sequencia do computador
		srand (time(NULL));
		int cor = rand() % 4;
		insere(computador, cor);
		aux = computador.header;


		clear(buffer);

        // loop em que o computador repete visualmente a sequencia para o jogador
		while(aux != NULL && !key[KEY_ESC]){ // ocorrera enquanto o ponteiro que percorre a fila do computador nao for NULL

            // variaveis para as funçoes "pisca"
			int vermelho = 0;
    		int azul = 0;
    		int verde = 0;
			int amarelo = 0;

            // quadrados
			rectfill(buffer, 229, 170, 400, 60, makecol(vermelhopiscar(vermelho), 0, 0));
			rectfill(buffer, 52, 171, 228, 279, makecol(0, azulpiscar(azul), 255));
			rectfill(buffer, 401, 171, 570, 279, makecol(255, 255, amarelopiscar(amarelo)));
			rectfill(buffer, 229, 280, 400, 390, makecol(0, verdepiscar(verde), 0));

            // "desenha" o buffer
			blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

			rest(250);

			clear(buffer);

            // faz as cores piscar e "imprime" elas em texto
			if(aux->info == 0){ // pisca vermelho
				vermelho = 1;
				textprintf_ex(buffer, font, 20, 40, makecol(255, 255, 255), -1, "vermelho");
			}
			if(aux->info == 1){ // pisca azul
				azul = 1;
				textprintf_ex(buffer, font, 20, 40, makecol(255, 255, 255), -1, "azul");
			}
			if(aux->info == 2){ // pisca amarelo
				amarelo = 1;
				textprintf_ex(buffer, font, 20, 40, makecol(255, 255, 255), -1, "amarelo");
			}
			if(aux->info == 3){ // pisca verde
				verde = 1;
				textprintf_ex(buffer, font, 20, 40, makecol(255, 255, 255), -1, "verde");
			}


            // texto "vez do computador!"
			textprintf_ex(buffer, font, 20, 20, makecol(255, 255, 255), -1, "Vez do computador!");

            // quadrados
			rectfill(buffer, 229, 170, 400, 60, makecol(vermelhopiscar(vermelho), 0, 0));
			rectfill(buffer, 52, 171, 228, 279, makecol(0, azulpiscar(azul), 255));
			rectfill(buffer, 401, 171, 570, 279, makecol(255, 255, amarelopiscar(amarelo)));
			rectfill(buffer, 229, 280, 400, 390, makecol(0, verdepiscar(verde), 0));

            // "desenha" o buffer
			blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

            // avança o ponteiro que percorre a fila do computador com a sequencia de cores
			aux = aux->next;
			rest(650);
		}

		clear(buffer);

        // loop em que o jogador entra com a sequencia de cores
		while(!key[KEY_SPACE] && !key[KEY_ESC]){ // ocorrera ate que o jogador pressione ESPAÇO

            // variaveis para as funçoes "pisca"
            int vermelho = 0;
            int azul = 0;
            int verde = 0;
            int amarelo = 0;

            // conforme o jogador pressiona as setas, as cores correspondentes sao inseridas na fila "jogador"
            if(key[KEY_UP])
            {
                vermelho = 1;
                insere(jogador, 0);
                rest(200);
            }
            if(key[KEY_DOWN])
            {
                verde = 1;
                insere(jogador, 3);
                rest(200);
            }
            if (key[KEY_LEFT])
            {
                azul = 1;
                insere(jogador, 1);
                rest(200);
            }
            if (key[KEY_RIGHT])
            {
                amarelo = 1;
                insere(jogador, 2);
                rest(200);
            }


        // texto "sua vez"
        textprintf_ex(buffer, font, 20, 20, makecol(255, 255, 255), -1, "Sua vez!");

        // quadrados
        rectfill(buffer, 229, 170, 400, 60, makecol(vermelhopiscar(vermelho), 0, 0));
		rectfill(buffer, 52, 171, 228, 279, makecol(0, azulpiscar(azul), 255));
		rectfill(buffer, 401, 171, 570, 279, makecol(255, 255, amarelopiscar(amarelo)));
		rectfill(buffer, 229, 280, 400, 390, makecol(0, verdepiscar(verde), 0));

        // textos dos quadrados
        textprintf_ex(buffer, font, 303, 112, makecol(0, 0, 0), -1, "cima");
        textprintf_ex(buffer, font, 110, 223, makecol(0, 0, 0), -1, "esquerda");
        textprintf_ex(buffer, font, 461, 223, makecol(0, 0, 0), -1, "direita");
		textprintf_ex(buffer, font, 297, 332, makecol(0, 0, 0), -1, "baixo");

        // "desenha" o buffer
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        rest(50);
		}

        // compara as filas "jogador" e "computador"
		if(compara(jogador, computador) == false){ // caso sejam diferentes:
			perdeu = true;
			clear(buffer);
			textprintf_ex(buffer, font, 20, 20, makecol(255, 255, 255), -1, "Voce perdeu!");
			blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
			rest(2500);
		}
        // o loop principal ira parar caso "perdeu" seja TRUE, e o jogo ira encerrar
	}
	clear(buffer);
	allegro_exit();
    return 0;
}
END_OF_MAIN();
