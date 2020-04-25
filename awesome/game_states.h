#include "helpers.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

const int PLAYER_WIDTH = 30;
const int PLAYER_HEIGHT = 21;

const int BALL_SIZE = 10;
const int MAX_BALLS = 25;

const int BALL_VELOCITY = 2;
const int LEVEL_UP_COUNT = 100;//level이 증가할때에 대비해서 추가
const int INITIAL_MODE = 10;
const int EXIT = -1;
const int SINGLE_MODE = 0;
const int MULTI_MODE = 1;
const int SERVER_MODE = 2;
const int CLIENT_MODE = 3;
const int WINNER = 1;
const int LOSER = 2;

extern SDL_Surface *background;
extern SDL_Surface *screen;
extern SDL_Surface* title_message;
extern SDL_Surface* message;
extern SDL_Surface* message2;
extern SDL_Surface* player;
extern SDL_Surface* player2;
extern SDL_Surface* ball;
extern SDL_Surface* heart;
extern SDL_Surface* enemy_heart;

extern SDL_Event event;
extern TTF_Font *font;
extern TTF_Font *font2;

extern SDL_Rect balls[MAX_BALLS];

extern SDL_Color textColor;

bool init();
bool load_files();
void clean_up();

void main_game(int selector, int mode);
void init_ball();
void game_over(int level, int score, int state);
void menu();
int select_mode();
int select_level();
void waiting(bool **isConnect);
int socketing();
void waitClient(bool **isConnect);

//socket variable
static const int bufsize = 16;
static const char ip[20] = "127.0.0.1";
static int client, server;
static int portNum = 1500;
static int buffer_int[bufsize / 4];
static int clientCount = 1;
static unsigned int time_now;

static struct sockaddr_in server_addr;
static socklen_t size;
