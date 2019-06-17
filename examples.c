/// SDL TUTORIAL

http://gigi.nullneuron.net/gigilabs/sdl2-pixel-drawing/

///


Example 2-3. Loading and Displaying a BMP File

void display_bmp(char *file_name)
{
    SDL_Surface *image;

    /* Load the BMP file into a surface */
    image = SDL_LoadBMP(file_name);
    if (image == NULL) {
        fprintf(stderr, "Couldn't load %s: %s\n", file_name, SDL_GetError());
        return;
    }

    /*
     * Palettized screen modes will have a default palette (a standard
     * 8*8*4 colour cube), but if the image is palettized as well we can
     * use that palette for a nicer colour matching
     */
    if (image->format->palette && screen->format->palette) {
    SDL_SetColors(screen, image->format->palette->colors, 0,
                  image->format->palette->ncolors);
    }

    /* Blit onto the screen surface */
    if(SDL_BlitSurface(image, NULL, screen, NULL) < 0)
        fprintf(stderr, "BlitSurface error: %s\n", SDL_GetError());

    SDL_UpdateRect(screen, 0, 0, image->w, image->h);

    /* Free the allocated BMP surface */
    SDL_FreeSurface(image);
}

int init_sdl() {
    t_sdl       sdl;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		print_err(SDL_GetError());
	if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) < 0)
		print_err(SDL_GetError());
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
		print_err(SDL_GetError());
	if (TTF_Init() < 0)
		print_err(SDL_GetError());
    if (!(sdl.win = SDL_CreateWindow("Wolf3d",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI)))
        print_err(SDL_GetError());
    return (1);
}