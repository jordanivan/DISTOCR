#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "pixel_operations.h"

void init_sdl()
{
	if(SDL_Init(SDL_INIT_VIDEO) == -1)
		errx(1,"Could not initialize SDL : %s.\n", SDL_GetError());
}

SDL_Surface* load_image(char *path)
{
	SDL_Surface *img;
	img = IMG_Load(path);
	if(!img)
		errx(3,"can't load %s : %s ", path, IMG_GetError());

	return img;
}

SDL_Surface* display_image(SDL_Surface *img)
{
	SDL_Surface *screen;

	screen = SDL_SetVideoMode(img->w, img->h, 0 , SDL_SWSURFACE|SDL_ANYFORMAT);
	if ( screen == NULL)
	{
		errx(1," Couldn't set %dx%d video mode: %s\n",
				img->w, img-> h, SDL_GetError());
	}
	if(SDL_BlitSurface(img,NULL,screen,NULL)<0)
		warnx("BlitSurface error: %s\n", SDL_GetError());
	SDL_UpdateRect(screen, 0, 0 , img->w , img ->h);
	return screen;
}

void wait_for_keypressed()
{
	SDL_Event event;
	do
	{
		SDL_PollEvent(&event);
	}while(event.type!= SDL_KEYDOWN);

	do
	{
		SDL_PollEvent(&event);
	}while(event.type!= SDL_KEYUP);
}

int main()
{
printf("ok1gttt ");
	SDL_Surface* image_surface;
	SDL_Surface* screen_surface;

	init_sdl();

	image_surface = load_image("index.jpg");
	printf("ok");

	image_surface = display_image(image_surface);

	wait_for_keypressed();

	int width  = image_surface -> w;
	int height = image_surface -> h;

	for(int i=0; i < width ; i++)
	{
		printf("okay");
		for(int j=0; j < height; j++)
		{
			printf("tout va bien");
			Uint32 pixel = get_pixel(image_surface, i,j);
			Uint8 r,g,b;
			SDL_GetRGB(pixel , image_surface->format, &r , &g , &b);
			if(i==0)
			{
				Uint32 pixel1 = get_pixel(image_surface, i+1,j);
				Uint8 r1,g1,b1;
				SDL_GetRGB(pixel1, image_surface->format, &r1, &g1, &b1);
				if (j==0)
				{
					Uint32 pixel2 = get_pixel(image_surface, i,j+1);
					Uint32 pixel3 = get_pixel(image_surface, i+1,j+1);
					Uint8 r2,g2,b2;
					Uint8 r3,g3,b3;
					SDL_GetRGB(pixel2, image_surface->format, &r2,&g2,&b2);
					SDL_GetRGB(pixel3, image_surface->format, &r3,&g3,&b3);

					r= r/4 + r1/4 + r2/4 + r3/4;
					g= g/4 + g1/4 + g2/4 + g3/4;
					b= b/4 + b1/4 + b2/4 + b3/4;

					pixel = SDL_MapRGB(image_surface->format, r,g,b);
					put_pixel(image_surface, i,j,pixel);
				}
				if(j==height-1)
				{
					Uint32 pixel2 = get_pixel(image_surface, i,j-1);
					Uint32 pixel3 = get_pixel(image_surface, i+1,j-1);
					Uint8 r2,g2,b2;
					Uint8 r3,g3,b3;
					SDL_GetRGB(pixel2, image_surface->format, &r2,&g2,&b2);
					SDL_GetRGB(pixel3, image_surface->format, &r3,&g3,&b3);
 					r= r/4 + r1/4 + r2/4 + r3/4;
 					g= g/4 + g1/4 + g2/4 + g3/4;
                                        b= b/4 + b1/4 + b2/4 + b3/4;

                                        pixel = SDL_MapRGB(image_surface->format, r,g,b);
                                        put_pixel(image_surface, i,j,pixel);
				}
				else
				{
					Uint32 pixel2 = get_pixel(image_surface, i,j+1);
					Uint32 pixel3 = get_pixel(image_surface, i+1,j+1);
					Uint32 pixel4 = get_pixel(image_surface, i,j-1);
					Uint32 pixel5 = get_pixel(image_surface, i+1,j-1);
					Uint8 r2,g2,b2;
					Uint8 r3,g3,b3;
					Uint8 r4,g4,b4;
					Uint8 r5,g5,b5;
					SDL_GetRGB(pixel2, image_surface->format, &r2,&g2,&b2);
					SDL_GetRGB(pixel3, image_surface->format, &r3,&g3,&b3);
					SDL_GetRGB(pixel4, image_surface->format, &r4,&g4,&b4);
					SDL_GetRGB(pixel5, image_surface->format, &r5,&g5,&b5);

					r= r/6 + r1/6 + r2/6 + r3/6 + r4/6 + r5/6;
					g= g/6 + g1/6 + g2/6 + g3/6 + g4/6 + g5/6;
					b= b/6 + b1/6 + b2/6 + b3/6 + b4/6 + b5/6;
 
 					pixel = SDL_MapRGB(image_surface->format, r,g,b);
 					put_pixel(image_surface, i,j,pixel);
				}	
			}	
			if(i==width-1)
			{
				Uint32 pixel1 = get_pixel(image_surface, i-1,j);
				Uint8 r1,g1,b1;
				SDL_GetRGB(pixel1, image_surface->format,&r1, &g1, &b1); //est ce qu'il faut enlever les &
				if (j==0)
				{
					Uint32 pixel2 = get_pixel(image_surface, i,j+1);
					Uint32 pixel3 = get_pixel(image_surface, i-1,j+1);
					Uint8 r2,g2,b2;
					Uint8 r3,g3,b3;
					SDL_GetRGB(pixel2, image_surface->format, &r2,&g2,&b2);
					SDL_GetRGB(pixel3, image_surface->format, &r3,&g3,&b3);

					r= r/4 + r1/4 + r2/4 + r3/4;
					g= g/4 + g1/4 + g2/4 + g3/4;
					b= b/4 + b1/4 + b2/4 + b3/4;
					
					pixel = SDL_MapRGB(image_surface->format, r,g,b);
					put_pixel(image_surface, i,j,pixel);
				}
				if(j==height-1)
				{
					Uint32 pixel2 = get_pixel(image_surface, i,j-1);
					Uint32 pixel3 = get_pixel(image_surface, i-1,j-1);
					Uint8 r2,g2,b2;
					Uint8 r3,g3,b3;
					SDL_GetRGB(pixel2, image_surface->format, &r2,&g2,&b2);
					SDL_GetRGB(pixel3, image_surface->format, &r3,&g3,&b3);
					
					r= r/4 + r1/4 + r2/4 + r3/4;
					g= g/4 + g1/4 + g2/4 + g3/4;
					b= b/4 + b1/4 + b2/4 + b3/4;

					pixel = SDL_MapRGB(image_surface->format, r,g,b);
					put_pixel(image_surface, i,j,pixel);
				}
				else
				{

					Uint32 pixel2 = get_pixel(image_surface, i,j+1);
					Uint32 pixel3 = get_pixel(image_surface, i-1,j+1);
					Uint32 pixel4 = get_pixel(image_surface, i,j-1);
					Uint32 pixel5 = get_pixel(image_surface, i-1,j-1);
					Uint8 r2,g2,b2;
					Uint8 r3,g3,b3;
					Uint8 r4,g4,b4;
					Uint8 r5,g5,b5;
					SDL_GetRGB(pixel2, image_surface->format, &r2,&g2,&b2);
					SDL_GetRGB(pixel3, image_surface->format, &r3,&g3,&b3);
					SDL_GetRGB(pixel4, image_surface->format, &r4,&g4,&b4);
					SDL_GetRGB(pixel5, image_surface->format, &r5,&g5,&b5);
	
					r= r/6 + r1/6 + r2/6 + r3/6 + r4/6 + r5/6;
					g= g/6 + g1/6 + g2/6 + g3/6 + g4/6 + g5/6;
					b= b/6 + b1/6 + b2/6 + b3/6 + b4/6 + b5/6;

					pixel = SDL_MapRGB(image_surface->format, r,g,b);
					put_pixel(image_surface, i,j,pixel);
				}
			}
			else
			{
				Uint32 pixel1 = get_pixel(image_surface, i+1,j);
				Uint32 pixel2 = get_pixel(image_surface, i+1,j);
				Uint32 pixel3 = get_pixel(image_surface, i+1,j);
				Uint32 pixel4 = get_pixel(image_surface, i+1,j);
				Uint32 pixel5 = get_pixel(image_surface, i+1,j);
				Uint32 pixel6 = get_pixel(image_surface, i+1,j);
				Uint32 pixel7 = get_pixel(image_surface, i+1,j);
				Uint32 pixel8 = get_pixel(image_surface, i+1,j);
				Uint8 r1,g1,b1;
				Uint8 r2,g2,b2;
				Uint8 r3,g3,b3;
				Uint8 r4,g4,b4;
				Uint8 r5,g5,b5;
				Uint8 r6,g6,b6;
				Uint8 r7,g7,b7;                          
				Uint8 r8,g8,b8;
				SDL_GetRGB(pixel1, image_surface->format, &r1,&g1,&b1);
				SDL_GetRGB(pixel2, image_surface->format, &r2,&g2,&b2);
				SDL_GetRGB(pixel3, image_surface->format, &r4,&g4,&b3);
				SDL_GetRGB(pixel4, image_surface->format, &r4,&g4,&b4);
				SDL_GetRGB(pixel5, image_surface->format, &r5,&g5,&b5);
				SDL_GetRGB(pixel6, image_surface->format, &r6,&g6,&b6);
				SDL_GetRGB(pixel7, image_surface->format, &r7,&g7,&b7);
				SDL_GetRGB(pixel8, image_surface->format, &r8,&g8,&b8);

				r= r/9 + r1/9 + r2/9 + r3/9 + r4/9 + r5/9 + r6/9 + r7/9 + r8/9;
				g= g/9 + g1/9 + g2/9 + g3/9 + g4/9 + g5/9 + g6/9 + g7/9 + g8/9;
				b= b/9 + b1/9 + b2/9 + b3/9 + b4/9 + b5/9 + b6/9 + b7/9 + b8/9;
	
				pixel = SDL_MapRGB(image_surface->format, r,g,b);
				put_pixel(image_surface, i,j,pixel);
			
			}
		}
	}
	printf("caca");
	update_surface(screen_surface, image_surface);

	wait_for_keypressed();

	SDL_FreeSurface(image_surface);
	SDL_FreeSurface(screen_surface);
}













