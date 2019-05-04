#include  "parte_grafica.h"

// definition of some strings: they cannot be changed when the program is executed !
const char myName[] = "Beatriz Alves IST186951";
const char myNumber[] = "Diogo Moura IST186976";

int menuGrafic()
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    TTF_Font *serif = NULL;

    SDL_Surface *imgs[2];
    SDL_Event event;
    int delay = 300;
    int quit = 0;
    int width = (ECRA_SIZE + LEFT_BAR_SIZE);
    int height = ECRA_SIZE;
    int l=0;    // corresponde ao raio do circulo
    char pos_str[MOUSE];
    int mouseX;
    int mouseY;

    // initialize graphics
    InitEverything(width, height, &serif, imgs, &window, &renderer);
    DrawCircle(renderer,100,100,80,255,0,0,0); //raio 70 cor vermelha

    while( quit == 0 )
    {
        // while there's events to handle
        while( SDL_PollEvent( &event ) )
        {
            if( event.type == SDL_QUIT )
            {
                quit = 1;
            }//para controlar onde o cursor do rato está
            else if(event.type==SDL_MOUSEMOTION)
            {
                mouseX=event.motion.x;		//coordenadas onde esta o cursor no dado momento
                mouseY=event.motion.y;

                sprintf(pos_str,"%d %d", mouseX,mouseY);
                SDL_SetWindowTitle(window, pos_str);

            }
//            else if ( event.type == SDL_MOUSEBUTTONDOWN )
//            {
//                switch ( event.button.button)
//                {
//                case(SDL_BUTTON_LEFT):
//                    break;
//                case(SDL_BUTTON_RIGHT):
//                    break;
//                default:
//                    break;
//
//                }
//            }

            // render game table
            RenderTable( serif, imgs, renderer);

            //desenho de um circulo com largura maior para isso desenham-se varios circulos de um raio de 200 até 208
            for(l=200; l<215; l++)
            {
                DrawCircle(renderer,300,300,l,0,0,0,255); //raio 300 cor branca
            }
            Drawpoints(renderer,300,300,204, mouseX, mouseY);  //desenho das "cruzes" que vão simbolizar as estações3-66
            // render in the screen all changes above
            SDL_RenderPresent(renderer);

            // add a delay
            SDL_Delay( delay );
        }

    }

    // free memory allocated for images and textures and closes everything including fonts
    TTF_CloseFont(serif);
    SDL_FreeSurface(imgs[0]);
    SDL_FreeSurface(imgs[1]);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
/*
 * DrawCircle: desenha o circulo:
 * \param  n_cx passa a coordenada x do centro do circulo
 * \param  n_cy passa a coordenada y do centro do circulo
 * \param  radius passa o raio do circulo
 * \param  r, g, b passam em conjunto a cor que vai ser o circulo
 * \param  a refere-se a opacidade do circulo
 */
void DrawCircle(SDL_Renderer *surface, int n_cx, int n_cy, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{

	float step = (2*PI)/2000.0f;		//vai dizer de quanto em quanto tempo eu vou calcular de um dado pixel que vou desenhar
	int x_new=0, y_new=0, x_old=0, y_old=0;
    float theta=0;

	x_old = (int)floor(n_cx + radius*cos(0)+0.5f);
	y_old = (int)floor(n_cy + radius*sin(0)+0.5f);

	for(theta=0; theta<=(2*PI);theta+=step)
	{
		//X=xcenter+rcos(theta) e Y=ycenter +rsen(theta)
		x_new = (int)floor(n_cx + radius*cos(theta)+0.5f);
		y_new = (int)floor(n_cy + radius*sin(theta)+0.5f);

		SDL_SetRenderDrawColor(surface, r, g, b, a);
		SDL_RenderDrawLine(surface, x_old, y_old, x_new,y_new);
		x_old=x_new;
		y_old=y_new;
	}

}

/*
 * Drawpoints: desenha as cruzes que representam as estações:
 * \param  n_cx passa a coordenada x do centro do circulo em que vão ser postas as cruzes
 * \param  n_cy passa a coordenada y do centro do circulo em que vão ser postas as cruzes
 * \param  radius passa o raio do circulo em que vão ser postas as cruzes
 * \param  r, g, b passam em conjunto a cor que as cruzes vão ter
 * \param  a refere-se a opacidade das cruzes
 */
void Drawpoints(SDL_Renderer *surface, int n_cx, int n_cy, int radius,int mouseX, int mouseY)
{

	float step = (2*PI)/64.0f;		//vai dizer de quanto em quanto tempo eu vou calcular de um dado pixel que vou desenhar
	int x=0, y=0;
    float theta=0;

	x = (int)floor(n_cx + radius*cos(0)+0.5f);
	y = (int)floor(n_cy + radius*sin(0)+0.5f);

	for(theta=0; theta<=(2*PI);theta+=step)
	{
		//X=xcenter+rcos(theta) e Y=ycenter +rsen(theta)
		x = (int)floor(n_cx + radius*cos(theta)+0.5f);
		y = (int)floor(n_cy + radius*sin(theta)+0.5f);
		DistanciaMouse(mouseY, mouseX, x, y,theta);


		//SDL_SetRenderDrawColor(surface, r, g, b, a);


        SDL_Rect retStation;

        retStation.x=x-2;
        retStation.y=y-3;
        retStation.h=11;
        retStation.w=11;

        SDL_SetRenderDrawColor(surface, 0,255,0,53);  // azul e a opacidade
        SDL_RenderFillRect(surface, &retStation);


		//SDL_RenderDrawLine(surface, x+5, y-5, x-5, y+5);        //para localizar as linhas que fazem as cruzes
		//SDL_RenderDrawLine(surface, x-5, y-5, x+5, y+5);

	}
	//SDL_SetRenderDrawColor(surface,255,255,255,255);
}

/*
 * DistanciaMouse: calcula a distância entre o cursor do mouse e cada estação e diz qual é a estação que está mais perto
 * \param  mouseY coordenada y do cursor do rato
 * \param  mouseX coordenada x do cursos do rato
 * \param  x coordenada x da estação
 * \param  y corrdenada y da estação
 */
int DistanciaMouse(int mouseY, int mouseX, int x, int y, float theta)
{
    int varX;
    int varY;
    int d;
    int dminimo=5000;
    float dmtheta=0;
    float step = (2*PI)/64.0f;
    int stepstation=0;

    varX= mouseX -(x-2);
    varY= mouseY -(y-3);

    d=sqrt((varX*varX)+(varY*varY));

    //quero guardar a estação que está à menor distância do cursor
    if(dminimo>d)
    {
        dminimo = d;
        dmtheta= theta;     //gurada o theta associado à distância minima
    }



    if (dminimo<= 10)
    {
        stepstation=(int)floor(dmtheta/step);
 //   dividir o theta pelo step para saber qunato steps foram acrescentados e assim diz-me o id da estação sendo que step 0-> id 3


    }
    return stepstation;
}

/*
 * RenderTable: Draws the table where the game will be played, namely:
 * -  some texture for the background
 * -  the right part with the IST logo and the student name and number
 * \param _font font used to render the text
 * \param _img surfaces with the table background and IST logo (already loaded)
 * \param _renderer renderer to handle all rendering in a window
*/
void RenderTable(TTF_Font *_font, SDL_Surface *_img[], SDL_Renderer* _renderer )
{
    SDL_Color black = { 0, 0, 0 }; // black
    SDL_Color dark = { 120, 110, 102 };
    SDL_Texture *table_texture;
    SDL_Rect tableSrc, tableDest, board;
    int height;

    // set color of renderer to some color
    SDL_SetRenderDrawColor( _renderer, 255, 255, 255, 255 );

    // clear the window
    SDL_RenderClear( _renderer );

    tableDest.x = tableSrc.x = 0;
    tableDest.y = tableSrc.y = 0;
    tableSrc.w = _img[0]->w;
    tableSrc.h = _img[0]->h;
    tableDest.w = TABLE_SIZE;
    tableDest.h = TABLE_SIZE;

    // draws the table texture
    table_texture = SDL_CreateTextureFromSurface(_renderer, _img[0]);
    SDL_RenderCopy(_renderer, table_texture, &tableSrc, &tableDest);

    // render the IST Logo
    height = RenderLogo(TABLE_SIZE, 0, _img[1], _renderer);

    // render the student name
    height += RenderText(TABLE_SIZE+3*MARGIN, height, myName, _font, &black, _renderer);

    // this renders the student number
    RenderText(TABLE_SIZE+3*MARGIN, height, myNumber, _font, &black, _renderer);

    // destroy everything
    SDL_DestroyTexture(table_texture);
}

/**
 * RenderLogo function: Renders the IST logo on the app window
 * \param x X coordinate of the Logo
 * \param y Y coordinate of the Logo
 * \param _logoIST surface with the IST logo image to render
 * \param _renderer renderer to handle all rendering in a window
 */
int RenderLogo(int x, int y, SDL_Surface *_logoIST, SDL_Renderer* _renderer)
{
    SDL_Texture *text_IST;
    SDL_Rect boardPos;

    // space occupied by the logo
    boardPos.x = x;
    boardPos.y = y;
    boardPos.w = _logoIST->w;
    boardPos.h = _logoIST->h;

    // render it
    text_IST = SDL_CreateTextureFromSurface(_renderer, _logoIST);
    SDL_RenderCopy(_renderer, text_IST, NULL, &boardPos);

    // destroy associated texture !
    SDL_DestroyTexture(text_IST);
    return _logoIST->h;
}

/**
 * RenderText function: Renders some text on a position inside the app window
 * \param x X coordinate of the text
 * \param y Y coordinate of the text
 * \param text string with the text to be written
 * \param _font TTF font used to render the text
 * \param _color color of the text
 * \param _renderer renderer to handle all rendering in a window
 */
int RenderText(int x, int y, const char *text, TTF_Font *_font, SDL_Color *_color, SDL_Renderer* _renderer)
{
    SDL_Surface *text_surface;
    SDL_Texture *text_texture;
    SDL_Rect solidRect;

    solidRect.x = x;
    solidRect.y = y;
    // create a surface from the string text with a predefined font
    text_surface = TTF_RenderText_Blended(_font,text,*_color);
    if(!text_surface)
    {
        printf("TTF_RenderText_Blended: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    // create texture
    text_texture = SDL_CreateTextureFromSurface(_renderer, text_surface);
    // obtain size
    SDL_QueryTexture( text_texture, NULL, NULL, &solidRect.w, &solidRect.h );
    // render it !
    SDL_RenderCopy(_renderer, text_texture, NULL, &solidRect);
    // clear memory
    SDL_DestroyTexture(text_texture);
    SDL_FreeSurface(text_surface);
    return solidRect.h;
}

/**
 * InitEverything: Initializes the SDL2 library and all graphical components: font, window, renderer
 * \param width width in px of the window
 * \param height height in px of the window
 * \param _font font that will be used to render the text
 * \param _img surface to be created with the table background and IST logo
 * \param _window represents the window of the application
 * \param _renderer renderer to handle all rendering in a window
 */
void InitEverything(int width, int height, TTF_Font **_font, SDL_Surface *_img[], SDL_Window** _window, SDL_Renderer** _renderer)
{
    InitSDL();
    InitFont();
    *_window = CreateWindow(width, height);
    *_renderer = CreateRenderer(width, height, *_window);

    // load the table texture
    _img[0] = IMG_Load("boston_texture.png");
    if (_img[0] == NULL)
    {
        printf("Unable to load image: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // load IST logo
    _img[1] = SDL_LoadBMP("ist_logo.bmp");
    if (_img[1] == NULL)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    // this opens (loads) a font file and sets a size
    *_font = TTF_OpenFont("FreeSerif.ttf", 16);
    if(!*_font)
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

}

/**
 * InitSDL: Initializes the SDL2 graphic library
 */
void InitSDL()
{
    // init SDL library
    if ( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        printf(" Failed to initialize SDL : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

/**
 * InitFont: Initializes the SDL2_ttf font library
 */
void InitFont()
{
    // Init font library
    if(TTF_Init()==-1)
    {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
}

/**
 * CreateWindow: Creates a window for the application
 * \param width width in px of the window
 * \param height height in px of the window
 * \return pointer to the window created
 */
SDL_Window* CreateWindow(int width, int height)
{
    SDL_Window *window;
    // init window
    window = SDL_CreateWindow( "BikeStation", WINDOW_POSX, WINDOW_POSY, width, height, 0 );
    // check for error !
    if ( window == NULL )
    {
        printf("Failed to create window : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    return window;
}

/**
 * CreateRenderer: Creates a renderer for the application
 * \param width width in px of the window
 * \param height height in px of the window
 * \param _window represents the window for which the renderer is associated
 * \return pointer to the renderer created
 */
SDL_Renderer* CreateRenderer(int width, int height, SDL_Window *_window)
{
    SDL_Renderer *renderer;
    // init renderer
    renderer = SDL_CreateRenderer( _window, -1, 0 );

    if ( renderer == NULL )
    {
        printf("Failed to create renderer : %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // set size of renderer to the same as window
    SDL_RenderSetLogicalSize( renderer, width, height );

    return renderer;
}

