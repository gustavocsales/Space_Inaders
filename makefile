CC = gcc
FLAGS = -std=c99 -O3
PATH_ALLEGRO=/usr/lib/x86_64-linux-gnu
LIB_ALLEGRO=-lallegro -lallegro_acodec -lallegro_audio -lallegro_color -lallegro_dialog -lallegro_font -lallegro_image -lallegro_primitives -lallegro_ttf

SRCS = tp.c meu_codigo.c

OBJS = $(SRCS:.c=.o)

all: space_inaders
	
space_inaders: $(OBJS) # Depende de todos os arquivos objeto
	$(CC) $(FLAGS) -o space_inaders $(OBJS) -L $(PATH_ALLEGRO) $(LIB_ALLEGRO) -lm

%.o: %.c meu_codigo.h 
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) space_inaders
