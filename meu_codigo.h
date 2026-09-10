#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_video.h>

#define QNT_INI 10
#define TEMPOGERA 0.5
#define FREEZE 1
#define QNT_INI_MAX 100
#define TEMPO_POWER_UP 10

typedef struct nave{
	float x;
	float vel;
	int dir, esq;
	int tipoCor;
	int tipoNave;
	ALLEGRO_COLOR cor;
}nave;

typedef struct inimigo{
	float x;
	float y;
	float x_vel;
	float y_vel;
	int acertou;
	int powerUp;
	ALLEGRO_COLOR cor;
}inimigo;

typedef struct disparo{
	float x;
	float y;
	float vel;
	int verdade;
	int som;
	ALLEGRO_COLOR cor;
}disparo;

typedef struct power_up{
	float x;
	float y;
	float vel;
	float verdade;
	int tipo;
	ALLEGRO_COLOR cor;

}power_up;


static const float FPS = 60;  

static const float SCREEN_W = 960;
static const float SCREEN_H = 540;

static const float MATO_H = SCREEN_H/9;
static const float y_base = SCREEN_H - MATO_H/2;

static const float NAVE_W = SCREEN_W/15;
static const float NAVE_H = SCREEN_H/7;

static const float INIMIGO_W = SCREEN_W/12;
static const float  INIMIGO_H = SCREEN_H/9;

static const float DISPARO_W = SCREEN_W/90;
static const float DISPARO_H =SCREEN_H/60;
static const float Y_DISPARO = SCREEN_H - (NAVE_H + MATO_H/2);

static const float RAIO_POWER_UP = SCREEN_H/108;
static const float SPEED_POWER_UP = SCREEN_H/25;



//void desenha_cenario();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~_NAVE_~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void initNave(nave *nave);

void desenha_nave(nave nave, ALLEGRO_BITMAP *normandy_img, ALLEGRO_BITMAP *millenium_falcom, ALLEGRO_BITMAP *perola_negra_img);

void update_nave(nave *nave);

void limiteNave(nave *nave);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~_INIMIGO_~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void initInimigo(float dificuldade_game, float dificuldade, inimigo *inimigo);

void desenha_inimigo(inimigo inimigo[], int dificuldade, ALLEGRO_BITMAP *alien_img);

void update_inimigo(inimigo inimigo[], int dificuldade);

void acerta_inimigo(int dificuldade, disparo disparo, inimigo inimigo[], nave nave);

void destroiInimigo(int *destruicoes, int dificuldade, int *muda_power_up, int *speed_power_up, ALLEGRO_SAMPLE *explosion, ALLEGRO_SAMPLE *sonic_coin, ALLEGRO_SAMPLE *mario_coin, inimigo inimigo[]);
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~_DISPARO_~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void initDisparo(int speed_power_up, nave nave, disparo *disparo);

void desenha_disparo(disparo *disparo, nave nave, ALLEGRO_SAMPLE *laser, ALLEGRO_SAMPLE *canon, ALLEGRO_BITMAP *disparo_img, ALLEGRO_BITMAP *canhao_img);

void update_disparo(int muda_power_up ,nave nave, inimigo inimigo[],  disparo *disparo, int dificuldade);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~_COLISAO_~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
int colisaoInimigo(nave nave, inimigo inimigo[], int dificuldade);

int colisaoPowerUp(nave *nave, power_up power_up, int dificuldade);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~_POWER-UPs_~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void initPowerUp(int tipo_power_up, inimigo inimigo[], power_up *power_up, int dificuldade);

void desenhaPowerUp(power_up power_up, ALLEGRO_BITMAP *estrela_img, ALLEGRO_BITMAP *ring_img);

void updatePowerUp(power_up  *power_up);

void destroiPowerUp(power_up *power_up);

void piercing(int *muda_power_up, int *altera_font, ALLEGRO_TIMER *tempoPowerUp, power_up power_up, nave *nave, disparo *disparo, ALLEGRO_AUDIO_STREAM *background, ALLEGRO_SAMPLE_INSTANCE *mario_instance, ALLEGRO_BITMAP *mario_img, ALLEGRO_BITMAP *arcade_img, ALLEGRO_BITMAP *background_img);

void speed_boost(int *speed_power_up, int *altera_font, ALLEGRO_TIMER *tempoPowerUp, power_up power_up, nave *nave, disparo *disparo, ALLEGRO_AUDIO_STREAM *background, ALLEGRO_SAMPLE_INSTANCE *sonic_instance, ALLEGRO_BITMAP *sonic_img, ALLEGRO_BITMAP *arcade_img, ALLEGRO_BITMAP *background_img);