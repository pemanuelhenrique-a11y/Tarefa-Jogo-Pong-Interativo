#include "bibtela.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <locale.h>

#define LINHAS 24
#define COLUNAS 80
#define TAM_RAQUETE 4

int main(void) {
    setlocale(LC_ALL, "");
    srand((unsigned int) time(NULL));

    init_screen(LINHAS, COLUNAS);

    // Posições iniciais das raquetes na matriz
    int r1_x = 10;
    int r2_x = 10;

    // Coordenadas da bola (centro da matriz)
    int bola_x = LINHAS / 2;
    int bola_y = COLUNAS / 2;

    // Vetores de velocidade da bola
    int vx = (rand() % 2 == 0) ? 1 : -1;
    int vy = (rand() % 2 == 0) ? 1 : -1;

    // Placar
    int pontos_p1 = 0;
    int pontos_p2 = 0;

    for (int ciclo = 0; ciclo < 400; ciclo++) {
        clear_screen();

        // Desenha a borda da quadra
        xywindow(0, 0, LINHAS - 1, COLUNAS - 1, 2);

        // Renderiza Placar
        xyprintint(1, 25, "P1: %d", pontos_p1);
        xyprint(1, 38, "|");
        xyprintint(1, 45, "P2: %d", pontos_p2);

        // Desenha a rede central pontilhada
        for (int i = 2; i < LINHAS - 1; i += 2) {
            xyprint(i, COLUNAS / 2, "|");
        }

        // Renderiza as Raquetes
        xyvline(3, r1_x, r1_x + TAM_RAQUETE - 1, "█");
        xyvline(COLUNAS - 4, r2_x, r2_x + TAM_RAQUETE - 1, "█");

        // Renderiza a Bola na matriz
        xyprintch(bola_x, bola_y, 'O');

        // Movimentação autônoma das raquetes (Simulação de jogo)
        if (bola_x > r2_x + 1 && r2_x + TAM_RAQUETE - 1 < LINHAS - 2) {
            r2_x++;
        } else if (bola_x < r2_x + 1 && r2_x > 1) {
            r2_x--;
        }

        if (bola_x > r1_x + 1 && r1_x + TAM_RAQUETE - 1 < LINHAS - 2) {
            r1_x++;
        } else if (bola_x < r1_x + 1 && r1_x > 1) {
            r1_x--;
        }

        // Atualização da posição da bola
        bola_x += vx;
        bola_y += vy;

        // Colisão com as bordas superior e inferior da matriz
        if (bola_x <= 1 || bola_x >= LINHAS - 2) {
            vx = -vx;
        }

        // Colisão com a Raquete 1 (Esquerda)
        if (bola_y == 4 && bola_x >= r1_x && bola_x <= r1_x + TAM_RAQUETE - 1) {
            vy = -vy;
        }

        // Colisão com a Raquete 2 (Direita)
        if (bola_y == COLUNAS - 5 && bola_x >= r2_x && bola_x <= r2_x + TAM_RAQUETE - 1) {
            vy = -vy;
        }

        // Ponto do Jogador 2 (Bola passou da esquerda)
        if (bola_y <= 1) {
            pontos_p2++;
            bola_x = LINHAS / 2;
            bola_y = COLUNAS / 2;
            vy = 1;
            vx = (rand() % 2 == 0) ? 1 : -1;
        }

        // Ponto do Jogador 1 (Bola passou da direita)
        if (bola_y >= COLUNAS - 2) {
            pontos_p1++;
            bola_x = LINHAS / 2;
            bola_y = COLUNAS / 2;
            vy = -1;
            vx = (rand() % 2 == 0) ? 1 : -1;
        }

        usleep(40000); // 40ms por frame (~25 FPS)
    }

    // Tela de encerramento
    clear_screen();
    xywindow(0, 0, LINHAS - 1, COLUNAS - 1, 1);
    xyprint(10, 30, "=== FIM DE JOGO ===");

    char msg_placar[80];
    snprintf(msg_placar, sizeof(msg_placar), "Placar Final: P1 [%d] x [%d] P2", pontos_p1, pontos_p2);
    xyprint(12, 24, msg_placar);

    xyprint(15, 23, "Pressione qualquer tecla para sair...");
    xygetch(15, 60);

    end_screen();
    return 0;
}
