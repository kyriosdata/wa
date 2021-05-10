
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <emscripten.h>

#define TOTAL_CIRCULOS 100

// Estrutura para posição, raio e cor de cada círculo
struct Circulo {
  int x;  
  int y;  
  int r;  
  int red; 
  int green; 
  int blue; 
};

// Detalhes necessários para a animação (velocidade e direção)
struct Animar {
  int xv; 
  int yv; 
  int xd; 
  int yd; 
};

struct Circulo circulos[TOTAL_CIRCULOS];
struct Animar animacao[TOTAL_CIRCULOS];

int numeroAleatorio(max) {
  return (rand() % max);
}

// Inicia gerador de círculos
void iniciar() {

  // Inicia gerador de números aleatórios
  srand(time(NULL));

  // Create circulos
  for (int i = 0; i < TOTAL_CIRCULOS; i++) {

    // Raio varia de 0 a 50
    int raio = numeroAleatorio(50);

    animacao[i].xv = numeroAleatorio(10) + 1;
    animacao[i].yv = numeroAleatorio(10) + 1;
    animacao[i].xd = 1;
    animacao[i].yd = 1;

    // Soma assegura círculo desenhado integralmente
    circulos[i].x = numeroAleatorio(3000) + raio;
    circulos[i].y = numeroAleatorio(3000) + raio;

    circulos[i].r = raio;
    circulos[i].red = numeroAleatorio(255);
    circulos[i].green = numeroAleatorio(255);
    circulos[i].blue = numeroAleatorio(255);
  }
}


int obterTotalItens() {
  return 6;
}

int obterTamanho() {
  return TOTAL_CIRCULOS * obterTotalItens();
}

// Atualiza posições dos círculos
struct Circulo * atualizaPosicoes( int canvasWidth, int canvasHeight ) {

  for( int i = 0; i < TOTAL_CIRCULOS; i++ ) {

    // Colisão direita
    if( (circulos[i].x + circulos[i].r) >= canvasWidth ) animacao[i].xd = 0;

    // Colisão esquerda
    if( (circulos[i].x - circulos[i].r) <= 0 ) animacao[i].xd = 1;

    // Colisão topo
    if( (circulos[i].y - circulos[i].r) <= 0 ) animacao[i].yd = 1;

    // Colisão na base
    if( (circulos[i].y + circulos[i].r) >= canvasHeight ) animacao[i].yd = 0;

    // Altera posição conforme direção e velocidade
    
    if( animacao[i].xd == 1 ) {
      circulos[i].x += animacao[i].xv;
    } else {
      circulos[i].x -= animacao[i].xv;
    }

    if( animacao[i].yd == 1 ) {
      circulos[i].y += animacao[i].yv;
    } else {
      circulos[i].y -= animacao[i].yv;
    }
  }

  return circulos;
}
