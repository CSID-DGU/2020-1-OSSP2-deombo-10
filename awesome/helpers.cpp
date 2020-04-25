#include "helpers.h"

bool intersects(SDL_Rect a, SDL_Rect b)
{
	if((a.x + a.w < b.x || a.y+ a.h < b.y) || (b.x+b.w < a.x || b.y+b.h < a.y))
		return false;
	/*std::cout << "x " << a.x << "/y " << a.y << "/w " << a.w << "/h " << a.h << std::endl;
	std::cout << "x " << b.x << "/y " << b.y << "/w " << b.w << "/h " << b.h << std::endl;
	std::cout << temp << std::endl;*/
	return true;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip )
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface( source, clip, destination, &offset );
}

SDL_Surface *load_image( std::string filename )
{
    
    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimizedImage = NULL;
    loadedImage = IMG_Load( filename.c_str() );
    
    if( loadedImage != NULL )
    {
        optimizedImage = SDL_DisplayFormat( loadedImage );
        SDL_FreeSurface( loadedImage );
        
        if( optimizedImage != NULL )
        {
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
        }
    }
    
    return optimizedImage;
}
