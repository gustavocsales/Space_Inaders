#include "meu_codigo.h"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~_PROGRAMA_~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
int main(int argc, char **argv){
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT ev;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL, *tempoPowerUp = NULL;
	ALLEGRO_FONT *font = NULL , *font_score = NULL, *mario_font = NULL, *sonic_font = NULL;
	ALLEGRO_AUDIO_STREAM *background = NULL;
	ALLEGRO_SAMPLE *explosion = NULL, *sonic = NULL, *sonic_ring = NULL, *mario = NULL, *mario_coin = NULL, *laser = NULL, *canon = NULL;
	ALLEGRO_SAMPLE_INSTANCE *explosion_instance = NULL, *sonic_instance = NULL, *sonic_ring_instance = NULL, *mario_instance = NULL, *mario_coin_instance = NULL, *laser_instance = NULL, *canon_instance = NULL;
	ALLEGRO_MIXER *mixer = NULL;
	ALLEGRO_BITMAP *sonic_img = NULL, *mario_img = NULL, *end_img = NULL, *arcade_img = NULL, *menu_img = NULL, *background_img = NULL, *alien_img = NULL, *normandy_img = NULL, *disparo_img = NULL, *millenium_falcom_img = NULL, *perola_negra_img = NULL, *canhao_img = NULL, *estrela_img = NULL, *ring_img = NULL;
	srand(time(NULL));
	FILE *RECORDE = NULL;
	//----------------------- rotinas de inicializacao ---------------------------------------
    
	//inicializa o Allegro
	if(!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}
	
    //inicializa o módulo de primitivas do Allegro
    if(!al_init_primitives_addon()){
		fprintf(stderr, "failed to initialize primitives!\n");
        return -1;
    }	
	
	//inicializa o modulo que permite carregar imagens no jogo
	if(!al_init_image_addon()){
		fprintf(stderr, "failed to initialize image module!\n");
		return -1;
	}

	//inicializa o modulo allegro que carrega as fontes
	al_init_font_addon();

	//inicializa o modulo allegro que entende arquivos tff de fontes
	if(!al_init_ttf_addon()) {
		fprintf(stderr, "failed to load tff font module!\n");
		return -1;
	}
	
	//cria um temporizador que incrementa uma unidade a cada 1.0/FPS segundos
    timer = al_create_timer(1.0 / FPS);
	tempoPowerUp = al_create_timer(1.0);
    if(!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}
 
	//cria uma tela com dimensoes de SCREEN_W, SCREEN_H pixels
	display = al_create_display(1792,1008);
	if(!display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(timer);
		return -1;
	}

 	//cria a fila de e	ventos
	event_queue = al_create_event_queue();
	if(!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		al_destroy_timer(tempoPowerUp);
		return -1;
	}
   
	//instala o teclado
	if(!al_install_keyboard()) {
		fprintf(stderr, "failed to install keyboard!\n");
		return -1;
	}
	
	//instala o mouse
	if(!al_install_mouse()) {
		fprintf(stderr, "failed to initialize mouse!\n");
		return -1;
	}

	//registra na fila os eventos de tela (ex: clicar no X na janela)
	al_register_event_source(event_queue, al_get_display_event_source(display));
	//registra na fila os eventos de tempo: quando o tempo altera de t para t+1
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	//registra na fila os eventos de teclado (ex: pressionar uma tecla)
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	//registra na fila os eventos de mouse (ex: clicar em um botao do mouse)
	al_register_event_source(event_queue, al_get_mouse_event_source());  	
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~_TIPOS_NAVE_~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
		normandy_img = al_load_bitmap("imagens/NORMANDY.png");
		if(!normandy_img){
			fprintf(stderr, "Erro ao carregar a imagem NORMANDY.png\n");
			return -1;
		}

		millenium_falcom_img = al_load_bitmap("imagens/MILLENIUM_FALCOM.png");
		if(!millenium_falcom_img){
			fprintf(stderr, "Erro ao carregar a imagem MILLENIUM_FALCOM.png\n");
			return -1;
		}

		perola_negra_img = al_load_bitmap("imagens/PEROLA_NEGRA.png");
		if(!perola_negra_img){
			fprintf(stderr, "Erro ao carregar a imagem PEROLA_NEGRA.png\n");
			return -1;
		}
		
		nave nave;
		nave.tipoNave=1;
		int escolheNave = 1;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~_MENU_~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
		menu_img = al_load_bitmap("imagens/MENU.png");
		if (!menu_img) {
			fprintf(stderr, "Erro ao carregar a imagem MENU.png\n");
			return -1;
		}
		int menu = 1;
		int menu_dificuldade = 1;
		float dificuldade_game = 1;
		int finalizar = 1;
		int playing = 1;
		int cancela_display1 = 1;
		font = al_load_ttf_font("fonts/ARCADE.ttf", 70, 0);
		if(font == NULL) {
			fprintf(stderr, "font file does not exist or cannot be accessed!\n");
			return -1;
		}

		while (menu){

			al_draw_bitmap(menu_img, 0,0,0);
			al_draw_textf(font, al_map_rgb(0, 255, 255), 750, 250, 0, "JOGAR");
			al_draw_textf(font, al_map_rgb(0, 255, 255), 780, 400, 0, "NAVE");

			if(nave.tipoNave == 1){
				al_draw_scaled_bitmap(normandy_img, 0, 0, al_get_bitmap_width(normandy_img), al_get_bitmap_height(normandy_img), 830, 600, al_get_bitmap_width(normandy_img)*2.5, al_get_bitmap_height(normandy_img)*2.5, 0);
			}
			if(nave.tipoNave == 2){
				al_draw_scaled_bitmap(millenium_falcom_img, 0, 0, al_get_bitmap_width(millenium_falcom_img), al_get_bitmap_height(millenium_falcom_img), 830, 600, al_get_bitmap_width(millenium_falcom_img)*2.5, al_get_bitmap_height(millenium_falcom_img)*2.5, 0);
			}
			if(nave.tipoNave == 3){
				al_draw_scaled_bitmap(perola_negra_img, 0, 0, al_get_bitmap_width(perola_negra_img), al_get_bitmap_height(perola_negra_img), 830, 600, al_get_bitmap_width(perola_negra_img)*2.5, al_get_bitmap_height(perola_negra_img)*2.5, 0);
			}

			al_flip_display();
			al_wait_for_event(event_queue, &ev);
			
			if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
				printf("\nmouse clicado em: %d, %d", ev.mouse.x, ev.mouse.y);
	
				if(ev.mouse.x >=780 && ev.mouse.x <= 1040 && ev.mouse.y<= 460 && ev.mouse.y>= 400){
					escolheNave = 1;
					al_draw_bitmap(menu_img, 0,0,0);
					al_draw_textf(font, al_map_rgb(0, 255, 255), 200, 250, 0, "NORMANDY");
					al_draw_scaled_bitmap(normandy_img, 0, 0, al_get_bitmap_width(normandy_img), al_get_bitmap_height(normandy_img), 1500, 210, al_get_bitmap_width(normandy_img)*2, al_get_bitmap_height(normandy_img)*2, 0);
					
					al_draw_textf(font, al_map_rgb(0, 255, 255), 200, 470, 0, "MILLENIUM FALCOM");
					al_draw_scaled_bitmap(millenium_falcom_img, 0, 0, al_get_bitmap_width(millenium_falcom_img), al_get_bitmap_height(millenium_falcom_img), 1500, 420, al_get_bitmap_width(millenium_falcom_img)*2, al_get_bitmap_height(millenium_falcom_img)*2, 0);
				
					al_draw_textf(font, al_map_rgb(0, 255, 255), 200, 690, 0, "PEROLA NEGRA");
					al_draw_scaled_bitmap(perola_negra_img, 0, 0, al_get_bitmap_width(perola_negra_img), al_get_bitmap_height(perola_negra_img), 1500, 630, al_get_bitmap_width(perola_negra_img)*2, al_get_bitmap_height(perola_negra_img)*2, 0);

					al_flip_display();
					

					while(escolheNave){
						al_wait_for_event(event_queue, &ev);
						if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
							if(ev.mouse.x >=200 && ev.mouse.x <= 740 && ev.mouse.y<= 310 && ev.mouse.y>= 250){
								nave.tipoNave = 1;
								escolheNave = 0;
							}
							if(ev.mouse.x >=200 && ev.mouse.x <= 1300 && ev.mouse.y<= 530 && ev.mouse.y>= 470){
								nave.tipoNave = 2;
								escolheNave = 0;
							}
							if(ev.mouse.x >=200 && ev.mouse.x <= 1300 && ev.mouse.y<= 750 && ev.mouse.y>= 690){
								nave.tipoNave = 3;
								escolheNave = 0;
							}
						}
						if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
							escolheNave = 0;
							menu_dificuldade = 0;
							menu = 0;
							finalizar = 0;
							playing = 0;
						}
						if(ev.type == ALLEGRO_EVENT_KEY_UP) {
							switch (ev.keyboard.keycode){
								case ALLEGRO_KEY_ESCAPE:
									escolheNave = 0;
									menu_dificuldade = 0;
									menu = 0;
									finalizar = 0;
									playing = 0;
								break;
							}
						}
					}
				}

				if(ev.mouse.x >=700 && ev.mouse.x <= 1080 && ev.mouse.y<= 310 && ev.mouse.y>= 250){

					while(menu_dificuldade){
						al_draw_bitmap(menu_img, 0,0,0);
						al_draw_textf(font, al_map_rgb(0, 255, 255), 750, 250, 0, "EASY");
						al_draw_textf(font, al_map_rgb(0, 255, 255), 700, 400, 0, "NORMAL");
						al_draw_textf(font, al_map_rgb(0, 255, 255), 750, 550, 0, "HARD");
						al_flip_display();
						al_wait_for_event(event_queue, &ev);
						if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
							if(ev.mouse.x >=750 && ev.mouse.x <= 1020 && ev.mouse.y<= 310 && ev.mouse.y>= 250){
							dificuldade_game = 1;
							menu_dificuldade = 0;
							menu = 0;
							}
							if(ev.mouse.x >=700 && ev.mouse.x <= 1100 && ev.mouse.y<= 460 && ev.mouse.y>= 400){
							dificuldade_game = 1.5;
							menu_dificuldade = 0;
							menu = 0;
							}
							if(ev.mouse.x >=750 && ev.mouse.x <= 1020 && ev.mouse.y<= 610 && ev.mouse.y>= 550){
							dificuldade_game = 2;
							menu_dificuldade = 0;
							menu = 0;
							}
						}
						if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
							menu_dificuldade = 0;
							menu = 0;
							finalizar = 0;
							playing = 0;
						}
						if(ev.type == ALLEGRO_EVENT_KEY_UP) {
							switch (ev.keyboard.keycode){
								case ALLEGRO_KEY_ESCAPE:
									menu_dificuldade = 0;
									menu = 0;
									finalizar = 0;
									playing = 0;
								break;
							}
						}
					}
				}
			}
				
			if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				menu = 0;
				finalizar = 0;
				playing = 0;
			}
			if(ev.type == ALLEGRO_EVENT_KEY_UP) {
				switch (ev.keyboard.keycode){
					case ALLEGRO_KEY_ESCAPE:
						menu = 0;
						finalizar = 0;
						playing = 0;
					break;
				}
			}
		}
				
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~_SCORE_~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
		font = al_load_ttf_font("fonts/ARCADE.ttf", 26, 0);
			if(font == NULL) {
				fprintf(stderr, "font file does not exist or cannot be accessed!\n");
				return -1;
			}

		font_score = al_load_ttf_font("fonts/ARCADE2.ttf", 40, 0);
			if(font_score == NULL) {
				fprintf(stderr, "font_score file does not exist or cannot be accessed!\n");
				return -1;
			}	

		mario_font = al_load_ttf_font("fonts/MARIO.ttf", 28, 0);
			if(mario_font == NULL) {
				fprintf(stderr, "MARIO.font file does not exist or cannot be accessed!\n");
				return -1;
			}

		sonic_font = al_load_ttf_font("fonts/SONIC.ttf", 24, 0);
			if(sonic_font == NULL) {
				fprintf(stderr, "SONIC.font file does not exist or cannot be accessed!\n");
				return -1;
			}	

		int altera_font = 0;
		int score = 0;
		if(dificuldade_game == 1){
			RECORDE = fopen("RECORDE_EASY.txt", "r");
		}else if(dificuldade_game == 1.5){
			RECORDE = fopen("RECORDE_NORMAL.txt", "r");
		}else if(dificuldade_game == 2){
			RECORDE = fopen("RECORDE_HARD.txt", "r");
		}
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~_FIM--SCORE_~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~_AUDIO_~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
		if(!al_install_audio()) {
			fprintf(stderr, "failed to install audio module!\n");
			return -1;
		}

		if(!al_init_acodec_addon()) {
			fprintf(stderr, "failed to install acodec module!\n");
			return -1;
		}
		
		al_reserve_samples(11);
		if (!al_get_default_mixer()) {
			mixer = al_create_mixer(44100, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_2);
			al_attach_mixer_to_voice(mixer, al_get_default_voice());
			al_set_default_mixer(mixer);
		}
		al_set_mixer_gain(al_get_default_mixer(), 2.0);

		background = al_load_audio_stream("music/BACKGROUND.ogg", 4, 2048);
		al_set_audio_stream_gain(background, 0.4);
		al_attach_audio_stream_to_mixer(background, al_get_default_mixer());
		al_set_audio_stream_playmode(background, ALLEGRO_PLAYMODE_LOOP);

		explosion = al_load_sample("music/EXPLOSION.ogg");
		explosion_instance = al_create_sample_instance(explosion);
		al_attach_sample_instance_to_mixer(explosion_instance, al_get_default_mixer());

		sonic = al_load_sample("music/SONIC.ogg");
		sonic_instance = al_create_sample_instance(sonic);
		al_set_sample_instance_gain(sonic_instance, 0.8);
		al_attach_sample_instance_to_mixer(sonic_instance, al_get_default_mixer());

		sonic_ring = al_load_sample("music/SONIC_RING.ogg");
		sonic_ring_instance = al_create_sample_instance(sonic_ring);
		al_attach_sample_instance_to_mixer(sonic_ring_instance, al_get_default_mixer());

		mario = al_load_sample("music/MARIO.ogg");
		mario_instance = al_create_sample_instance(mario);
		al_set_sample_instance_gain(mario_instance, 2);
		al_attach_sample_instance_to_mixer(mario_instance, al_get_default_mixer());

		mario_coin = al_load_sample("music/MARIO_COIN.ogg");
		mario_coin_instance = al_create_sample_instance(mario_coin);
		al_attach_sample_instance_to_mixer(mario_coin_instance, al_get_default_mixer());

		laser = al_load_sample("music/LASER.ogg");
		laser_instance = al_create_sample_instance(laser);
		al_attach_sample_instance_to_mixer(laser_instance, al_get_default_mixer());

		canon = al_load_sample("music/CANHAO.ogg");
		canon_instance = al_create_sample_instance(canon);
		al_attach_sample_instance_to_mixer(canon_instance, al_get_default_mixer());
		
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~_FIM--AUDIO_~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~_IMAGEM_~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
		
		sonic_img = al_load_bitmap("imagens/SONIC.png");
		if (!sonic_img) {
			fprintf(stderr, "Erro ao carregar a imagem SONIC.png\n");
			return -1;
		}

		mario_img = al_load_bitmap("imagens/MARIO.png");
		if (!mario_img) {
			fprintf(stderr, "Erro ao carregar a imagem MARIO.png\n");
			return -1;
		}

		background_img = al_load_bitmap("imagens/BACKGROUND.png");
		if (!background_img) {
			fprintf(stderr, "Erro ao carregar a imagem BACKGROUND.png\n");
			return -1;
		}

		arcade_img = al_load_bitmap("imagens/ARCADE.png");
		if (!sonic_img) {
			fprintf(stderr, "Erro ao carregar a imagem ARCADE.png\n");
			return -1;
		}

		alien_img = al_load_bitmap("imagens/INIMIGO.png");
		if (!alien_img) {
			fprintf(stderr, "Erro ao carregar a imagem ALIEN.png\n");
			return -1;
		}

		disparo_img = al_load_bitmap("imagens/DISPARO.png");
		if(!normandy_img){
			fprintf(stderr, "Erro ao carregar a imagem DISPARO.png\n");
			return -1;
		}

		canhao_img = al_load_bitmap("imagens/CANHAO.png");
		if(!canhao_img){
			fprintf(stderr, "Erro ao carregar a imagem CANHAO.png\n");
			return -1;
		}

		estrela_img = al_load_bitmap("imagens/ESTRELA.png");
		if (!estrela_img) {
			fprintf(stderr, "Erro ao carregar a imagem ESTRELA.png\n");
			return -1;
		}

		ring_img = al_load_bitmap("imagens/RING.png");
		if (!ring_img) {
			fprintf(stderr, "Erro ao carregar a imagem RING.png\n");
			return -1;
		}

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~_FIM--IMAGEM_~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~_SET--POWER-UPS_~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
		power_up power_up;
		power_up.x = -2000;
		power_up.y = -2000;
		power_up.vel = 0; 
		// APLICAM O POWER UP QUANDO MODIFICADOS
		int muda_power_up = 1;
		int speed_power_up = 0;
		// FIM DA APLICAÇÃO
		int temPowerUp = 0;
		int auxTempoPowerUp = 0;
		int aux_power_up = 1;
		int tipo_power_up = 0;
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~_FIM--SET--POWER-UPS_~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
		initNave(&nave);

		inimigo inimigo[QNT_INI_MAX];
		for (int i=0; i<QNT_INI_MAX; i++){
			inimigo[i].x = -2000;
			inimigo[i].y = -2000;
		}
		

		disparo disparo;
		int i=0;
		disparo.verdade = 0;
		disparo.som=1;

		char recorde[1000];
		char *nome_recorde = NULL;
		int valor_recorde = 0;

		if(fgets(recorde, 1000, RECORDE) != NULL){
			nome_recorde = strtok(recorde, ",");
			valor_recorde = atoi(strtok(NULL,","));
		}
		printf("\n%s%d", nome_recorde, valor_recorde);
		fclose(RECORDE);
		
		//inicia o temporizador
		al_start_timer(timer);
		int scorenivel1=0;
		double t = 0;
		int dificuldade = 1;
		double corrige_menu = 0 ;

		while(playing!=0 && QNT_INI_MAX>QNT_INI*dificuldade){
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~NIVEL--1_~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
		temPowerUp = rand()%QNT_INI_MAX;
		tipo_power_up = rand()%2+1;
		for(int i=0; i<QNT_INI*dificuldade; i++){
				inimigo[i].x = -2000;
				inimigo[i].y = -2000;
				inimigo[i].x_vel = 0;
				inimigo[i].y_vel = 0;
				inimigo[i].cor = al_map_rgb(rand()%256, rand()%256, rand()%256);
				inimigo[i].acertou=0;
				inimigo[i].powerUp = 0;
				if(temPowerUp == i){
					inimigo[i].powerUp = 1;
				}	
				//printf("\nINIMIGO[%d]: %d", i, inimigo[i].powerUp);
				//printf("\n");

		}
			al_stop_timer(tempoPowerUp);
			al_set_timer_count(tempoPowerUp, 0);	

			power_up.x = -2000;
			power_up.y = -2000;
			power_up.vel = 0;
			aux_power_up = 1;
			muda_power_up = 1;
			speed_power_up = 0;
			auxTempoPowerUp = 0;
			double temponivel1 = t;
			i=0;
			corrige_menu = al_get_time();

			while(playing == 1) 
			{
				al_draw_bitmap(arcade_img, 0, 0, 0);
				al_draw_bitmap(background_img, 420, 240, 0);
				al_draw_rounded_rectangle(420, 240, 1380, 780, 20,20,al_map_rgb(255,255,255), 10);
				t = al_get_time();
				//espera por um evento e o armazena na variavel de evento ev
				al_wait_for_event(event_queue, &ev);
				if(disparo.verdade == 0){
					initDisparo(speed_power_up, nave, &disparo);
				}
				if (dificuldade != 1){
					corrige_menu=0;
				}
				if(i<QNT_INI*dificuldade){
					if(t >= corrige_menu + temponivel1 +FREEZE + TEMPOGERA*i){
						initInimigo(dificuldade_game, dificuldade, &inimigo[i]);
						i++;
						
					}
				}


				//se o tipo de evento for um evento do temporizador, ou seja, se o tempo passou de t para t+1
				if(ev.type == ALLEGRO_EVENT_TIMER) {

					//desenha cenario
					//desenha_cenario();
					update_nave(&nave);
					update_inimigo(inimigo, dificuldade);
					if(disparo.verdade){
					update_disparo(muda_power_up, nave, inimigo, &disparo, dificuldade);
					}
					updatePowerUp(&power_up);
					limiteNave(&nave);
					
					if(colisaoPowerUp(&nave, power_up, dificuldade) == 1 || auxTempoPowerUp == 1){
						piercing(&muda_power_up, &altera_font, tempoPowerUp, power_up, &nave, &disparo, background, mario_instance, mario_img, arcade_img, background_img);
						speed_boost(&speed_power_up, &altera_font, tempoPowerUp, power_up, &nave, &disparo, background, sonic_instance, sonic_img, arcade_img, background_img);
						auxTempoPowerUp = 1;
					}
					desenha_nave(nave, normandy_img, millenium_falcom_img, perola_negra_img);
					desenha_inimigo(inimigo, dificuldade, alien_img);
					desenha_disparo(&disparo, nave, laser, canon,disparo_img, canhao_img);
					acerta_inimigo(dificuldade, disparo, inimigo, nave);
					for (int j=0; j<QNT_INI*dificuldade; j++){
						if(inimigo[j].acertou ==1 && inimigo[j].powerUp == 1 && aux_power_up==1){
							initPowerUp(tipo_power_up, inimigo, &power_up, dificuldade);
							aux_power_up =0;
						}
					}
					desenhaPowerUp(power_up, estrela_img, ring_img);
					destroiInimigo(&scorenivel1, dificuldade, &muda_power_up, &speed_power_up, explosion, sonic_ring, mario_coin, inimigo);
					colisaoPowerUp(&nave, power_up, dificuldade);
					if(colisaoPowerUp(&nave, power_up, dificuldade)){
						destroiPowerUp(&power_up);
					}
					
					
					//aplica fisica
					//desenha
				if(altera_font == 0){
						//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~_EXIBE_NIVEL_~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
						al_draw_textf(font, al_map_rgb(255, 255, 0), 420 + 20, 240 + 10, 0, "NIVEL: %d / %d ", dificuldade, QNT_INI_MAX/QNT_INI);
						
						//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~_TEMPORIZADOR_~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
						al_draw_textf(font, al_map_rgb(0, 255, 255), 420 +20, 240 + SCREEN_H-MATO_H/2, 0, "TEMPO DE JOGO: %.2f ", t-corrige_menu);
						
						//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~_SCORE_~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
						al_draw_textf(font, al_map_rgb(0, 255, 255), 420 + SCREEN_W-250, 240 + SCREEN_H-MATO_H/2, 0, "SCORE: %d", scorenivel1+score);
					}
					
					if(altera_font == 1){
						//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~_EXIBE_NIVEL_~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
						al_draw_textf(mario_font, al_map_rgb(255, 255, 0), 420 + 20, 240 + 10, 0, "NIVEL: %d / %d ", dificuldade, QNT_INI_MAX/QNT_INI);
						
						//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~_TEMPORIZADOR_~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
						al_draw_textf(mario_font, al_map_rgb(0, 255, 255), 420 + 20, 240 + SCREEN_H-MATO_H/2, 0, "TEMPO DE JOGO: %.2f ", t-corrige_menu);
						
						//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~_SCORE_~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
						al_draw_textf(mario_font, al_map_rgb(0, 255, 255), 420 + SCREEN_W-250, 240 + SCREEN_H-MATO_H/2, 0, "SCORE: %d", scorenivel1+score);
					}
					if(altera_font == 2){
						//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~_EXIBE_NIVEL_~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
						al_draw_textf(sonic_font, al_map_rgb(255, 255, 0), 420 + 20, 240 + 10, 0, "NIVEL: %d / %d ", dificuldade, QNT_INI_MAX/QNT_INI);
						
						//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~_TEMPORIZADOR_~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
						al_draw_textf(sonic_font, al_map_rgb(0, 255, 255), 420 + 20, 240 + SCREEN_H-MATO_H/2, 0, "TEMPO DE JOGO: %.2f ", t-corrige_menu);
						
						//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~_SCORE_~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
						al_draw_textf(sonic_font, al_map_rgb(0, 255, 255), 420 + SCREEN_W-250, 240 + SCREEN_H-MATO_H/2, 0, "SCORE: %d", scorenivel1+score);
					}
					//atualiza a tela (quando houver algo para mostrar)
					al_flip_display();
					
					
				}

				//se o tipo de evento for o fechamento da tela (clique no x da janela)
				else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
					playing = 0;
				}
				//se o tipo de evento for um clique de mouse
				else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
					//printf("\nmouse clicado em: %d, %d", ev.mouse.x, ev.mouse.y);

				}
				//se o tipo de evento for um pressionar de uma tecla
				else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) { 
					//imprime qual tecla foi
					//printf("\ncodigo tecla: %d", ev.keyboard.keycode);
					
						switch (ev.keyboard.keycode){
						case ALLEGRO_KEY_A:
							nave.esq = 1;
						break;
						case ALLEGRO_KEY_D:
							nave.dir= 1;
						break;
						}
					}
				
				else if(ev.type == ALLEGRO_EVENT_KEY_UP) { 
					//imprime qual tecla foi
					//printf("\ncodigo tecla: %d", ev.keyboard.keycode);

					switch (ev.keyboard.keycode){
						case ALLEGRO_KEY_A:
							nave.esq = 0;
						break;
						case ALLEGRO_KEY_D:
							nave.dir= 0;
						break;
						case ALLEGRO_KEY_SPACE:
							disparo.verdade ++;
						break;
						case ALLEGRO_KEY_ESCAPE:
							playing=0;
						break;
					}
				}
				if(colisaoInimigo(nave, inimigo, dificuldade)){
				playing = 0;
				}
				if(scorenivel1 == QNT_INI*dificuldade){
					playing = 2;
				}
			} 
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~_FIM--NIVEL--1_~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
			score += scorenivel1;
			scorenivel1 = 0;
			dificuldade++;
			altera_font = 0;
			nave.tipoCor=0;
			al_stop_sample_instance(sonic_instance);
			al_stop_sample_instance(mario_instance);
			al_set_audio_stream_speed(background, 1 + (float)dificuldade / 100);
			al_set_audio_stream_playing(background, true);
			font = al_load_ttf_font("fonts/ARCADE.ttf", 26, 0);
			if(font == NULL) {
				fprintf(stderr, "ARCADE.txt file does not exist or cannot be accessed!\n");
			}
			al_draw_bitmap(arcade_img, 0, 0, 0);
			al_draw_rounded_rectangle(420, 240, 1380, 780, 20,20,al_map_rgb(255,255,255), 10);
			//al_draw_tinted_bitmap(normandy_img, al_map_rgb(254, 254, 254), 420 + nave.x-NAVE_W/2, 240 + y_base - NAVE_H, 0);
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~_NIVEL--2_~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
			al_stop_timer(tempoPowerUp);
			al_set_timer_count(tempoPowerUp, 0);

			int scorenivel2 = 0;
			double temponivel2 = t;
			temPowerUp = rand()%QNT_INI_MAX*2;
			tipo_power_up = rand()%2+1;
			for(int i=0; i<QNT_INI*dificuldade; i++){
				inimigo[i].x_vel = 0;
				inimigo[i].y_vel = 0;
				inimigo[i].cor = al_map_rgb(rand()%256, rand()%256, rand()%256);
				inimigo[i].acertou=0;
				inimigo[i].powerUp = 0;
				if(temPowerUp == i){
					inimigo[i].powerUp = 1;
				}	
				//printf("\nINIMIGO[%d]: %d", i, inimigo[i].powerUp);
				//printf("\n");
			}

			i=0;
			
			power_up.x = -2000;
			power_up.y = -2000;
			power_up.vel = 0;
			aux_power_up = 1;
			muda_power_up = 1;
			speed_power_up = 0;
			auxTempoPowerUp = 0;

			while(playing == 2) 
			{
				al_draw_bitmap(arcade_img, 0, 0, 0);
				al_draw_bitmap(background_img, 420, 240, 0);
				al_draw_rounded_rectangle(420, 240, 1380, 780, 20,20,al_map_rgb(255,255,255), 10);
				t = al_get_time();
				//espera por um evento e o armazena na variavel de evento ev
				al_wait_for_event(event_queue, &ev);
				if(disparo.verdade == 0){
					initDisparo(speed_power_up ,nave, &disparo);
				}

				if(i<QNT_INI*dificuldade){
					if(t-0.25 >= temponivel2 +FREEZE+ TEMPOGERA*i){
						initInimigo(dificuldade_game, dificuldade, &inimigo[i]);
						i++;
						
					}
				}


				//se o tipo de evento for um evento do temporizador, ou seja, se o tempo passou de t para t+1
				if(ev.type == ALLEGRO_EVENT_TIMER) {

					//desenha cenario
					update_nave(&nave);
					update_inimigo(inimigo, dificuldade);
					if(disparo.verdade){
					update_disparo(muda_power_up, nave, inimigo, &disparo, dificuldade);
					}
					updatePowerUp(&power_up);
					limiteNave(&nave);
					if(colisaoPowerUp(&nave, power_up, dificuldade) ==1 || auxTempoPowerUp == 1){
						
							piercing(&muda_power_up, &altera_font, tempoPowerUp, power_up, &nave, &disparo, background, mario_instance, mario_img, arcade_img, background_img);
							speed_boost(&speed_power_up, &altera_font, tempoPowerUp, power_up, &nave, &disparo, background, sonic_instance, sonic_img, arcade_img, background_img);
							auxTempoPowerUp = 1;
					}
					desenha_nave(nave, normandy_img, millenium_falcom_img, perola_negra_img);
					desenha_inimigo(inimigo, dificuldade, alien_img);
					desenha_disparo(&disparo, nave, laser, canon, disparo_img, canhao_img);
					acerta_inimigo(dificuldade, disparo, inimigo, nave);
					for (int j=0; j<QNT_INI*dificuldade; j++){
						if(inimigo[j].acertou ==1 && inimigo[j].powerUp == 1 && aux_power_up==1){
							initPowerUp(tipo_power_up, inimigo, &power_up, dificuldade);
							aux_power_up =0;
						}
					}
					desenhaPowerUp(power_up, estrela_img, ring_img);
					destroiInimigo(&scorenivel2, dificuldade, &muda_power_up, &speed_power_up, explosion, sonic_ring, mario_coin, inimigo);
					if(colisaoPowerUp(&nave, power_up, dificuldade)){
						destroiPowerUp(&power_up);
					}
					
					
					//aplica fisica
					//desenha
					if(altera_font == 0){
						//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~_EXIBE_NIVEL_~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
						al_draw_textf(font, al_map_rgb(255, 255, 0), 420 + 20, 240 + 10, 0, "NIVEL: %d / %d ", dificuldade, QNT_INI_MAX/QNT_INI);
						
						//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~_TEMPORIZADOR_~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
						al_draw_textf(font, al_map_rgb(0, 255, 255), 420 +20, 240 + SCREEN_H-MATO_H/2, 0, "TEMPO DE JOGO: %.2f ", t-corrige_menu);
						
						//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~_SCORE_~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
						al_draw_textf(font, al_map_rgb(0, 255, 255), 420 + SCREEN_W-250, 240 + SCREEN_H-MATO_H/2, 0, "SCORE: %d", scorenivel2+score);
					}
					
					if(altera_font == 1){
						//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~_EXIBE_NIVEL_~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
						al_draw_textf(mario_font, al_map_rgb(255, 255, 0), 420 + 20, 240 + 40, 0, "NIVEL: %d / %d ", dificuldade, QNT_INI_MAX/QNT_INI);
						
						//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~_TEMPORIZADOR_~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
						al_draw_textf(mario_font, al_map_rgb(0, 255, 255), 420 + 20, 240 + SCREEN_H-MATO_H/2, 0, "TEMPO DE JOGO: %.2f ", t-corrige_menu);
						
						//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~_SCORE_~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
						al_draw_textf(mario_font, al_map_rgb(0, 255, 255), 420 + SCREEN_W-250, 240 + SCREEN_H-MATO_H/2, 0, "SCORE: %d", scorenivel2+score);
					}
					if(altera_font == 2){
						//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~_EXIBE_NIVEL_~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
						al_draw_textf(sonic_font, al_map_rgb(255, 255, 0), 420 + 20, 240 + 40, 0, "NIVEL: %d / %d ", dificuldade, QNT_INI_MAX/QNT_INI);
						
						//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~_TEMPORIZADOR_~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
						al_draw_textf(sonic_font, al_map_rgb(0, 255, 255), 420 + 20, 240 + SCREEN_H-MATO_H/2, 0, "TEMPO DE JOGO: %.2f ", t-corrige_menu);
						
						//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~_SCORE_~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
						al_draw_textf(sonic_font, al_map_rgb(0, 255, 255), 420 + SCREEN_W-250, 240 + SCREEN_H-MATO_H/2, 0, "SCORE: %d", scorenivel2+score);
					}
					//atualiza a tela (quando houver algo para mostrar)
					al_flip_display();
					
					
				}

				//se o tipo de evento for o fechamento da tela (clique no x da janela)
				else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
					playing = 0;
				}
				//se o tipo de evento for um clique de mouse
				else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
					//printf("\nmouse clicado em: %d, %d", ev.mouse.x, ev.mouse.y);

				}
				//se o tipo de evento for um pressionar de uma tecla
				else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) { 
					//imprime qual tecla foi
					//printf("\ncodigo tecla: %d", ev.keyboard.keycode);
					
						switch (ev.keyboard.keycode){
						case ALLEGRO_KEY_A:
							nave.esq = 1;
						break;
						case ALLEGRO_KEY_D:
							nave.dir= 1;
						break;
						}
					}
				
				else if(ev.type == ALLEGRO_EVENT_KEY_UP) { 
					//imprime qual tecla foi
					//printf("\ncodigo tecla: %d", ev.keyboard.keycode);

					switch (ev.keyboard.keycode){
						case ALLEGRO_KEY_A:
							nave.esq = 0;
						break;
						case ALLEGRO_KEY_D:
							nave.dir= 0;
						break;
						case ALLEGRO_KEY_SPACE:
							disparo.verdade ++;
						break;
						case ALLEGRO_KEY_ESCAPE:
							playing=0;
						break;
					}
				}
				if(colisaoInimigo(nave, inimigo, dificuldade)){
				playing = 0;
				}
				if(scorenivel2 == QNT_INI*dificuldade){
					playing = 1;
					
				}
			} //fim do while
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~_FIM--NIVEL--2_~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
			score+=scorenivel2;
			scorenivel2=0;
			dificuldade++;
			altera_font = 0;
			nave.tipoCor=0;
			al_stop_sample_instance(sonic_instance);
			al_stop_sample_instance(mario_instance);
			al_set_audio_stream_speed(background, 1 + (float)dificuldade / 100);
			al_set_audio_stream_playing(background, true);
			font = al_load_ttf_font("fonts/ARCADE.ttf", 26, 0);
			if(font == NULL) {
				fprintf(stderr, "ARIAL file does not exist or cannot be accessed!\n");
			}
			al_draw_bitmap(arcade_img, 0, 0, 0);
			al_draw_rounded_rectangle(420, 240, 1380, 780, 20,20,al_map_rgb(255,255,255), 10);
			al_draw_tinted_bitmap(normandy_img, al_map_rgb(254, 254, 254), 420 + nave.x-NAVE_W/2, 240 + y_base - NAVE_H, 0);
		}
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~_FIM--DO--JOGO_~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
		printf("\nTEMPO DE JOGO = %.2fs", al_get_time());
		al_set_audio_stream_speed(background, 1);

		font = al_load_ttf_font("fonts/ARCADE2.ttf", 60, 0);
		al_draw_bitmap(arcade_img, 0, 0, 0);
		al_draw_rounded_rectangle(420, 240, 1380, 780, 20,20,al_map_rgb(255,255,255), 10);
		
		if(QNT_INI_MAX>QNT_INI*(dificuldade-2)){
			end_img = al_load_bitmap("imagens/LOSE.png");
		}else{
			end_img = al_load_bitmap("imagens/WIN.png");
		}

		int cancela_flip = 1;
		while (finalizar){

			al_draw_bitmap(end_img, 420, 240, 0);
			al_wait_for_event(event_queue, &ev);

			if(QNT_INI_MAX>QNT_INI*(dificuldade - 2)){
				al_draw_textf(font, al_map_rgb(0, 0, 0), 420 + SCREEN_W/8 +4, 240 + SCREEN_H/20 +4, 0, "VOCE PERDEU!");
				al_draw_textf(font, al_map_rgb(188, 2, 2), 420 + SCREEN_W/8, 240 + SCREEN_H/20, 0, "VOCE PERDEU!");
			}else{
				al_draw_textf(font, al_map_rgb(0, 0, 0), 420 + SCREEN_W/8 +4, 240 + SCREEN_H/20 + 4, 0, "VOCE VENCEU!");
				al_draw_textf(font, al_map_rgb(188, 2, 2), 420 + SCREEN_W/8, 240 + SCREEN_H/20, 0, "VOCE VENCEU!");
			}
				//EXIBE TEMPO E SCORE
				al_draw_textf(font_score, al_map_rgb(0, 0, 0), 420 + SCREEN_W/20+4, 240 + SCREEN_H - 196, 0, "SEU SCORE: %d ", score);
				al_draw_textf(font_score, al_map_rgb(255, 255, 0), 420 + SCREEN_W/20, 240 + SCREEN_H - 200, 0, "SEU SCORE: %d ", score);
				al_draw_textf(font_score, al_map_rgb(0, 0, 0), 420 + SCREEN_W/20+4, 240 + SCREEN_H - 136, 0, "TEMPO DE JOGO: %.2f", t);
				al_draw_textf(font_score, al_map_rgb(255, 255, 0), 420 + SCREEN_W/20, 240 + SCREEN_H - 140, 0, "TEMPO DE JOGO: %.2f", t);
			
			//ATUALIZA RECORDE//
			if(score>valor_recorde){
				if(dificuldade_game == 1){
					RECORDE = fopen("RECORDE_EASY.txt", "w");
				}else if(dificuldade_game == 1.5){
					RECORDE = fopen("RECORDE_NORMAL.txt", "w");
				}else if(dificuldade_game == 2){
					RECORDE = fopen("RECORDE_HARD.txt", "w");
				}
				fprintf(RECORDE, "%s, %d", nome_recorde, score);
					al_draw_textf(font_score, al_map_rgb(0, 0, 0), 420 + SCREEN_W/20 +4, 240 + SCREEN_H - 76, 0, "NOVO RECORDE: %d ", score);
					al_draw_textf(font_score, al_map_rgb(255, 255, 0), 420 + SCREEN_W/20 , 240 + SCREEN_H - 80, 0, "NOVO RECORDE: %d ", score);
				fclose(RECORDE);
			}
			if(score<=valor_recorde){
				al_draw_textf(font_score, al_map_rgb(0, 0, 0), 420 + SCREEN_W/20+4, 240 + SCREEN_H - 76, 0, "RECORDE ATUAL: %d ", valor_recorde);
				al_draw_textf(font_score, al_map_rgb(255, 255, 0), 420 + SCREEN_W/20, 240 + SCREEN_H - 80, 0, "RECORDE ATUAL: %d ", valor_recorde);
			}

			if(cancela_flip){
			al_flip_display();
			cancela_flip = 0;
			}
			//se o tipo de evento for o fechamento da tela (clique no x da janela)
				
					if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
						finalizar = 0;
					}
					if(ev.type == ALLEGRO_EVENT_KEY_UP) { 
						switch (ev.keyboard.keycode){
							case ALLEGRO_KEY_ESCAPE:
								finalizar = 0;
							break;
						}
					}
		}
	//procedimentos de fim de jogo (fecha a tela, limpa a memoria, etc)
	
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_destroy_font(font);
	al_destroy_font(mario_font);
	al_destroy_font(sonic_font);
	al_destroy_audio_stream(background);
	al_destroy_sample_instance(explosion_instance);
	al_destroy_sample_instance(sonic_instance);
	al_destroy_sample_instance(sonic_ring_instance);
	al_destroy_sample_instance(mario_instance);
	al_destroy_sample_instance(mario_coin_instance);
	al_destroy_sample_instance(laser_instance);
	al_destroy_sample_instance(canon_instance);
    al_destroy_sample(explosion);
	al_destroy_sample(sonic);
	al_destroy_sample(sonic_ring);
	al_destroy_sample(mario);
	al_destroy_sample(mario_coin);
	al_destroy_sample(laser);
	al_destroy_sample(canon);
	al_destroy_mixer(mixer);
	al_destroy_bitmap(sonic_img);
	al_destroy_bitmap(mario_img);
	al_destroy_bitmap(end_img);
	al_destroy_bitmap(arcade_img);
	al_destroy_bitmap(menu_img);
	al_destroy_bitmap(background_img);
	al_destroy_bitmap(canhao_img);
	al_destroy_bitmap(estrela_img);
	al_destroy_bitmap(ring_img);
   
 
	return 0;
}