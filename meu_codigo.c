#include "meu_codigo.h"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~_NAVE_~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void initNave(nave *nave){
	nave->x = SCREEN_W/2;
	nave->vel = SCREEN_H/50;
	nave->dir = 0;
	nave->esq = 0;
	nave->tipoCor = 0;

	if(nave->tipoNave == 2){
		nave->vel+= 4;
	}
}

void desenha_nave(nave nave, ALLEGRO_BITMAP *normandy_img, ALLEGRO_BITMAP *millenium_falcom_img, ALLEGRO_BITMAP *perola_negra_img){
	//~~~~~~~~~~NORMANDY~~~~~~~~//
	if (nave.tipoCor==0 && nave.tipoNave == 1){
	al_draw_bitmap(normandy_img, 420 + nave.x-NAVE_W/2, 240 + y_base - NAVE_H, 0);
	al_draw_tinted_bitmap(normandy_img, al_map_rgb(254, 254, 254), 420 + nave.x-NAVE_W/2, 240 + y_base - NAVE_H, 0);
	}
	if (nave.tipoCor==1 && nave.tipoNave == 1){
	al_draw_bitmap(normandy_img, 420 + nave.x-NAVE_W/2, 240 + y_base - NAVE_H, 0);
	al_draw_tinted_bitmap(normandy_img, al_map_rgb(rand()%256, rand()%256, rand()%256), 420 + nave.x-NAVE_W/2, 240 + y_base - NAVE_H, 0);
	}
	if (nave.tipoCor==2 && nave.tipoNave == 1){
	al_draw_bitmap(normandy_img, 420 + nave.x-NAVE_W/2, 240 + y_base - NAVE_H, 0);
	al_draw_tinted_bitmap(normandy_img, al_map_rgb(0, 34, 255), 420 + nave.x-NAVE_W/2, 240 + y_base - NAVE_H, 0);
	}
//~~~~~~~~~~MILLENIUM_FALCOM~~~~~~~~//
	if (nave.tipoCor==0 && nave.tipoNave == 2){
	al_draw_bitmap(millenium_falcom_img, 420 + nave.x-NAVE_W/2, 240 + y_base - NAVE_H, 0);
	al_draw_tinted_bitmap(millenium_falcom_img, al_map_rgb(254, 254, 254), 420 + nave.x-NAVE_W/2, 240 + y_base - NAVE_H, 0);
	}
	if (nave.tipoCor==1 && nave.tipoNave == 2){
	al_draw_bitmap(millenium_falcom_img, 420 + nave.x-NAVE_W/2, 240 + y_base - NAVE_H, 0);
	al_draw_tinted_bitmap(millenium_falcom_img, al_map_rgb(rand()%256, rand()%256, rand()%256), 420 + nave.x-NAVE_W/2, 240 + y_base - NAVE_H, 0);
	}
	if (nave.tipoCor==2 && nave.tipoNave == 2){
	al_draw_bitmap(millenium_falcom_img, 420 + nave.x-NAVE_W/2, 240 + y_base - NAVE_H, 0);
	al_draw_tinted_bitmap(millenium_falcom_img, al_map_rgb(0, 34, 255), 420 + nave.x-NAVE_W/2, 240 + y_base - NAVE_H, 0);
	}
//~~~~~~~~~~PEROLA_NEGRA~~~~~~~//
	if (nave.tipoCor==0 && nave.tipoNave == 3){
	al_draw_bitmap(perola_negra_img, 420 + nave.x-NAVE_W/2, 240 + y_base - NAVE_H, 0);
	al_draw_tinted_bitmap(perola_negra_img, al_map_rgb(254, 254, 254), 420 + nave.x-NAVE_W/2, 240 + y_base - NAVE_H, 0);
	}
	if (nave.tipoCor==1 && nave.tipoNave == 3){
	al_draw_bitmap(perola_negra_img, 420 + nave.x-NAVE_W/2, 240 + y_base - NAVE_H, 0);
	al_draw_tinted_bitmap(perola_negra_img, al_map_rgb(rand()%256, rand()%256, rand()%256), 420 + nave.x-NAVE_W/2, 240 + y_base - NAVE_H, 0);
	}
	if (nave.tipoCor==2 && nave.tipoNave == 3){
	al_draw_bitmap(perola_negra_img, 420 + nave.x-NAVE_W/2, 240 + y_base - NAVE_H, 0);
	al_draw_tinted_bitmap(perola_negra_img, al_map_rgb(0, 34, 255), 420 + nave.x-NAVE_W/2, 240 + y_base - NAVE_H, 0);
	}
}

void update_nave(nave *nave){
	if(nave->dir){
		nave->x += nave->vel;
	}
	if(nave->esq){
		nave->x -= nave->vel;
	}
}

void limiteNave(nave *nave){
	if(nave->x - NAVE_W/2<= 0){
	nave->x = NAVE_W/2;
}else if(nave->x + NAVE_W/2>=SCREEN_W){
	nave->x = SCREEN_W - NAVE_W/2;
}
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~_INIMIGO_~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void initInimigo(float dificuldade_game, float dificuldade, inimigo *inimigo){
		inimigo->x = SCREEN_W - INIMIGO_W/2 - 10;
		inimigo->y = SCREEN_H/96+20;
		inimigo->x_vel = (SCREEN_W/96 - 4) * (1 + dificuldade/15 * dificuldade_game);
		inimigo->y_vel = INIMIGO_H/2 + 40;
		inimigo->cor = al_map_rgb(55+rand()%201, rand()%256, rand()%256);
		inimigo->acertou=0;
}			

void desenha_inimigo(inimigo inimigo[], int dificuldade, ALLEGRO_BITMAP *alien_img){
	for(int i=0 ;i<QNT_INI*dificuldade; i++){
		al_draw_bitmap(alien_img, 420 + inimigo[i].x - INIMIGO_W/2, 220 + inimigo[i].y, 0);
		al_draw_tinted_bitmap(alien_img, inimigo[i].cor, 420 + inimigo[i].x - INIMIGO_W/2, 220 + inimigo[i].y, 0);
	}
}

void update_inimigo(inimigo inimigo[], int dificuldade){
	for(int i=0;i<QNT_INI*dificuldade; i++){
		if(inimigo[i].x - INIMIGO_W/2 <= 4 || inimigo[i].x + INIMIGO_W/2 >= SCREEN_W - 4){
			inimigo[i].y += inimigo[i].y_vel;
			inimigo[i].x_vel *= -1;
		}
		inimigo[i].x -= inimigo[i].x_vel;
}
}

void acerta_inimigo(int dificuldade, disparo disparo, inimigo inimigo[], nave nave){
	for(int i=0; i<QNT_INI*dificuldade; i++){
		if(disparo.y+ DISPARO_H/2 >= inimigo[i].y-INIMIGO_H/2 && disparo.y-DISPARO_H/2 <= inimigo[i].y + INIMIGO_H/2 && disparo.x - DISPARO_W/2 >= inimigo[i].x - INIMIGO_W/2 && disparo.x + DISPARO_W/2 <= inimigo[i].x + INIMIGO_W/2){
			inimigo[i].acertou=1;
		}
		if(inimigo[i].y + INIMIGO_H/2>=Y_DISPARO){
			inimigo[i].acertou=0;
		}
		if(nave.tipoNave == 3){
			if(disparo.y+ DISPARO_H/2 +10 >= inimigo[i].y-INIMIGO_H/2 && disparo.y-DISPARO_H/2 -10 <= inimigo[i].y + INIMIGO_H/2 && disparo.x - DISPARO_W/2 +10  >= inimigo[i].x - INIMIGO_W/2 && disparo.x + DISPARO_W/2 -10 <= inimigo[i].x + INIMIGO_W/2){
			inimigo[i].acertou=1;
		}
	}

	}

}

void destroiInimigo(int *destruicoes, int dificuldade, int *muda_power_up, int *speed_power_up, ALLEGRO_SAMPLE *explosion, ALLEGRO_SAMPLE *sonic_coin, ALLEGRO_SAMPLE *mario_coin, inimigo inimigo[]){
	int x = 0;
	for(int i=0; i<QNT_INI*dificuldade; i++){
		if(inimigo[i].acertou == 1 || inimigo[i].acertou == 2){
			inimigo[i].x_vel =0;
			inimigo[i].x = -2000;
			inimigo[i].y = -2000;
			x++;
			if(inimigo[i].acertou == 1 && *muda_power_up == 1 && *speed_power_up ==0){
				al_play_sample(explosion, 1, 1, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
				inimigo[i].acertou = 2;
			}
			if(inimigo[i].acertou == 1 && *muda_power_up == 0){
				al_play_sample(mario_coin, 1, 1, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
				inimigo[i].acertou = 2;
			}
			if(inimigo[i].acertou == 1 && *speed_power_up != 0){
				al_play_sample(sonic_coin, 1, 1, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
				printf("OPA");
				inimigo[i].acertou = 2;
			}

		}
	}
	*destruicoes = x;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~_DISPARO_~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void initDisparo(int speed_power_up, nave nave, disparo *disparo){
	disparo->x = nave.x;
	disparo->y = Y_DISPARO;
	disparo->vel = SCREEN_W/96 + speed_power_up;
	disparo->verdade=0;
	disparo->cor = al_map_rgb(0,123,45);
	if(nave.tipoNave==1){
		disparo->vel += 4;
	}
}

void desenha_disparo(disparo *disparo, nave nave, ALLEGRO_SAMPLE *laser, ALLEGRO_SAMPLE *canon, ALLEGRO_BITMAP *disparo_img, ALLEGRO_BITMAP *canhao_img){
	if(disparo->verdade){
		 if(nave.tipoNave!=3){
			al_draw_bitmap(disparo_img,420 + disparo->x - DISPARO_W/2, 240 + disparo->y, 0 );
			if(disparo->som == 1){
			al_play_sample(laser, 1, 1, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			disparo->som = 0;
			}
		}else{
			al_draw_bitmap(canhao_img, 410 + disparo->x - DISPARO_W/2, 230 + disparo->y, 0 );
			if(disparo->som == 1){
			al_play_sample(canon, 0.6, 1, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			disparo->som = 0;
			}
		}
	}
}

void update_disparo(int muda_power_up ,nave nave, inimigo inimigo[],  disparo *disparo, int dificuldade){
	disparo->y -= disparo->vel;
	for(int i=0; i<QNT_INI*dificuldade; i++){
		    //LIMTE TELA         //ENCOSTA INIMIGO
		if((disparo->y <=0) || muda_power_up*(disparo->y + DISPARO_H/2 >= inimigo[i].y-INIMIGO_H/2 && disparo->y-DISPARO_H/2 <= inimigo[i].y + INIMIGO_H/2 && disparo->x - DISPARO_W/2 >= inimigo[i].x - INIMIGO_W/2 && disparo->x + DISPARO_W/2 <= inimigo[i].x + INIMIGO_W/2)){
			disparo->verdade=0;
			disparo->som=1;
		}
		
		if(nave.tipoNave == 3){
			if((disparo->y <=0) || muda_power_up*(disparo->y + DISPARO_H/2 +5 >= inimigo[i].y-INIMIGO_H/2 && disparo->y-DISPARO_H/2  -5 <= inimigo[i].y + INIMIGO_H/2 && disparo->x - DISPARO_W/2 +5 >= inimigo[i].x - INIMIGO_W/2 && disparo->x + DISPARO_W/2-5 <= inimigo[i].x + INIMIGO_W/2)){
			disparo->verdade=0;
			disparo->som=1;
		}
		}
	}
	
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~_COLISAO_~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
int colisaoInimigo(nave nave, inimigo inimigo[], int dificuldade){
	for(int i=0; i<QNT_INI*dificuldade; i++){
		//        ATAQUE PELA DIREITA                                         ATAQUE PELA ESQUERDA                                LIMITE VINDO DE CIMA
		if(inimigo[i].x - INIMIGO_W/2 <= (nave.x + (float)NAVE_W/5)  && inimigo[i].x + INIMIGO_W/2 >= (nave.x - (float)NAVE_W/5) && inimigo[i].y + INIMIGO_H/2 >=y_base - NAVE_H){
			return 1;
		}
	}
	return 0;
}

int colisaoPowerUp(nave *nave, power_up power_up, int dificuldade){
	for(int i=0; i<QNT_INI*dificuldade; i++){
		//        ATAQUE PELA DIREITA                                         ATAQUE PELA ESQUERDA                                LIMITE VINDO DE CIMA
		if(power_up.x - RAIO_POWER_UP/2 <= (nave->x + (float)NAVE_W/3)  && power_up.x + RAIO_POWER_UP/2 >= (nave->x - (float)NAVE_W/3) && power_up.y + RAIO_POWER_UP/2 >=y_base-NAVE_H && power_up.y - RAIO_POWER_UP/2 <= y_base + NAVE_H/2){
			return 1;
		}
		if(power_up.y >= SCREEN_H){
			return 2;
		}
	}
	return 0;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~_POWER-UPs_~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
	void initPowerUp(int tipo_power_up, inimigo inimigo[], power_up *power_up, int dificuldade){
		for(int i=0; i<QNT_INI*dificuldade; i++){
			if(inimigo[i].acertou == 1 && inimigo[i].powerUp == 1){
				power_up->x = inimigo[i].x;
				power_up->y = inimigo[i].y;
				power_up->vel = SCREEN_H/180;
				power_up->cor = al_map_rgb(0,255,0);
				power_up->tipo = tipo_power_up;
			}
		}
	}

	void desenhaPowerUp(power_up power_up, ALLEGRO_BITMAP *estrela_img, ALLEGRO_BITMAP *ring_img){
		//al_draw_filled_circle(420 + power_up.x, 240 + power_up.y, RAIO_POWER_UP,power_up.cor);
		if(power_up.tipo==1){
			al_draw_bitmap(estrela_img, 420 + power_up.x, 240 + power_up.y, 0);
		}

		if(power_up.tipo==2){
			al_draw_bitmap(ring_img, 420 + power_up.x, 240 + power_up.y, 0);
		}
	}

	void updatePowerUp(power_up  *power_up){
		power_up->y += power_up->vel;
	}

	void destroiPowerUp(power_up *power_up){
			power_up->vel =0;
			power_up->x = -2000;
			power_up->y = -2000;	
	}

	void piercing(int *muda_power_up, int *altera_font, ALLEGRO_TIMER *tempoPowerUp, power_up power_up, nave *nave, disparo *disparo, ALLEGRO_AUDIO_STREAM *background, ALLEGRO_SAMPLE_INSTANCE *mario_instance, ALLEGRO_BITMAP *mario_img, ALLEGRO_BITMAP *arcade_img, ALLEGRO_BITMAP *background_img){
		if(power_up.tipo == 1){
			nave->tipoCor = 1;
			if(al_get_timer_count(tempoPowerUp) < TEMPO_POWER_UP){
				*muda_power_up = 0;
				*altera_font = 1;
				al_set_audio_stream_playing(background, false);
				al_play_sample_instance(mario_instance);
				al_start_timer(tempoPowerUp);
				al_draw_bitmap(mario_img, 420, 240, 0);
			}else{
				*muda_power_up = 1;
				*altera_font = 0;
				nave->tipoCor = 0;
				al_set_audio_stream_playing(background, true);
				al_stop_sample_instance(mario_instance);
				al_draw_bitmap(arcade_img, 0, 0, 0);
				al_draw_bitmap(background_img, 420, 240, 0);
				al_draw_rounded_rectangle(420, 240, 1380, 780, 20,20,al_map_rgb(255,255,255), 10);
			}	
		}
	}

	void speed_boost(int *speed_power_up, int *altera_font, ALLEGRO_TIMER *tempoPowerUp, power_up power_up, nave *nave, disparo *disparo, ALLEGRO_AUDIO_STREAM *background, ALLEGRO_SAMPLE_INSTANCE *sonic_instance, ALLEGRO_BITMAP *sonic_img, ALLEGRO_BITMAP *arcade_img, ALLEGRO_BITMAP *background_img){
		if(power_up.tipo == 2){
			nave->tipoCor = 2;
			if(al_get_timer_count(tempoPowerUp) < TEMPO_POWER_UP){
				*speed_power_up = SPEED_POWER_UP;
				*altera_font = 2;
				disparo->cor = al_map_rgb(0, 34, 255);
				al_set_audio_stream_playing(background, false);
				al_play_sample_instance(sonic_instance);
				al_start_timer(tempoPowerUp);
				al_draw_bitmap(sonic_img, 420, 240, 0);
			}else{
				nave->tipoCor = 0;
				*speed_power_up = 0;
				*altera_font = 0;
				al_set_audio_stream_playing(background, true);
				al_stop_sample_instance(sonic_instance);
				al_draw_bitmap(arcade_img, 0, 0, 0);
				al_draw_bitmap(background_img, 420, 240, 0);
				al_draw_rounded_rectangle(420, 240, 1380, 780, 20,20,al_map_rgb(255,255,255), 10);
			}
		}
	}
