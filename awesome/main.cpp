#include "game_states.h"

SDL_Surface *background = NULL;
SDL_Surface *screen = NULL;
SDL_Surface* title_message = NULL;
SDL_Surface* message = NULL;
SDL_Surface* message2 = NULL;
SDL_Surface* player = NULL;
SDL_Surface* player2 = NULL;
SDL_Surface* ball = NULL;
SDL_Surface* heart = NULL;
SDL_Surface* enemy_heart = NULL;

SDL_Event event;
TTF_Font *font = NULL;
TTF_Font *font2 = NULL;

SDL_Rect balls[MAX_BALLS];

SDL_Color textColor = { 0, 0, 0 };

int main(int argc, char* argv[])
{
	if (init() == false)
	{
		return 1;
	}

	if (load_files() == false)
	{
		return 1;
	}

	menu();
	clean_up();
	return 0;
}
