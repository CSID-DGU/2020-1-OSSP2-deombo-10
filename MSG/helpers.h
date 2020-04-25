#include "define.h"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include <vector>
#include <string>
#include <ctime>
#include <sstream>
#include <iostream>//출력 테스트를 위해서 추가
#include <thread>
/*
socket programming을 위하여 추가되 해더
*/
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <unistd.h>
#include <netdb.h>
#include <stdlib.h>
using namespace std;

bool intersects(SDL_Rect a, SDL_Rect b);

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);

SDL_Surface *load_image( std::string filename );
