#include <SDL\SDL.h>
#include <SDL\SDL_image.h>
#include <SDL\SDL_ttf.h>
#include "ball.h"
#include "padldle.h"
#include <time.h>
#include "ClientTcp.h"

//variáveis da janela
const int w = 800;
const int h = 600;
const int SCREEN_BPP = 32;
const float FRAMES_PER_SECOND = 60;

//variaveis de desenho
SDL_Surface *screen = NULL;
SDL_Surface *message = NULL;
SDL_Surface *tileB = NULL;
SDL_Surface *tileP = NULL;
SDL_Event event;
SDL_Color textColor = { 100, 255, 255 };
TTF_Font *font = NULL;

//comtrole do jogo
enum{menu, jogando, fim};
int estadoAtual = menu;

//inicia a SDL e cria janela
bool init()
{
	screen = SDL_SetVideoMode( w, h, SCREEN_BPP,  SDL_HWSURFACE );
	if((SDL_Init( SDL_INIT_EVERYTHING | SDL_DOUBLEBUF | SDL_INIT_TIMER) == -1) || (screen == NULL) )
    {
        return false;
    }
	if( TTF_Init() == -1 )
    {
        return false;    
    }
    SDL_WM_SetCaption( "Pong!", NULL );
    return true;
}

//carrega recursos do jogo
void load_files()
{
    tileB = IMG_Load("tileB.png");
	tileP = IMG_Load("tileP.png");
	font = TTF_OpenFont( "arial.ttf", 28 );
}

//limpa recursos e SDL
void clean_up()
{
	SDL_FreeSurface( tileP );
	SDL_FreeSurface( tileB );
	SDL_FreeSurface( message );
    SDL_Quit();
}

//função para desenhar na tela
void desenhar(int x, int y, SDL_Surface* src, SDL_Surface* dst)
{
	SDL_Rect offset;
	offset.x=x;
	offset.y=y;
	SDL_BlitSurface(src,NULL,dst,&offset);
}

int main(int argc, char* argv[])
{
	if(init()== false)
		clean_up();
	load_files();

	//cria jogadores, bola e socket
	srand(SDL_GetTicks());
	int dirBolaIni = rand()%2; 
	ball b = ball(dirBolaIni,w,h);
	padldle j1 = padldle(10,h/2-60);
	padldle j2 = padldle(w-20,h/2-60);
	ClientTcp sock;
	sock.init();

	//variáveis para controle do tempo
	float deltaTime = 0.0;
    float thisTime = 0;
    float lastTime = 0;

	//chars para mostrar os pontos na tela
	char msg[10] ="Pontos: ";
	char ponto[3];

	//char para enviar mensagem pro servidor
	char buffer[512];

	char* ip=new CHAR();
	char* porta=new CHAR();
	bool quit = false;
	while (quit == false)
	{
		thisTime = SDL_GetTicks();
		deltaTime = (float)(thisTime - lastTime) / 1000;
		lastTime = thisTime;

		//controle para sair do jogo
		while( SDL_PollEvent( &event ) )
        {
            if( event.type == SDL_QUIT )
            {
                quit = true;
            } 
			if( event.type == SDL_KEYDOWN )
			{
				switch( event.key.keysym.sym )
				{
				case SDLK_ESCAPE:
						quit=true;
						break;
				}
			}
		}

		//loop principal
		switch (estadoAtual)
		{

		//menu do jogo
		case menu:
			message = TTF_RenderText_Solid( font, "Conecte pela linha de comando", textColor );
			desenhar(w/2-message->w/2,h/2-message->h/2,message,screen);
			SDL_Flip(screen);
			//recebe variáveis para conexão
			printf("Digite o ip: \n");
			std::cin>> ip;
			printf("Digite a porta: \n");
			std::cin>> porta;
			sock.criaSock(ip,porta);
			if(sock.recebeMsg("")==1)
			{
				estadoAtual = jogando;
			}
			break;

		//loop  do jogo
		case jogando:
			if(j1.mover(deltaTime,300,h,event)==1)
			{
				sprintf(buffer, "%f",j1.posP.y);
				sock.mandaMsg(buffer);
				j2.posP.y=sock.recebeMsg(buffer);
			}
			b.mover(deltaTime,100,j1.posP,j2.posP,w,h);
			//verifica pontuação e reinicia bola
			if(b.posB.x+10<=0 || b.posB.x>=w)
			{
				if(b.posB.x+10<=0)
				{
					j2.ponto+=1;
					if(j2.ponto==10)
						estadoAtual=fim;
				}
				if(b.posB.x>=w)
				{
					j1.ponto+=1;
					if(j1.ponto==10)
						estadoAtual=fim;
				}
				dirBolaIni = rand()%2; 
				b = ball(dirBolaIni,w,h);
			}
			message = TTF_RenderText_Solid( font, msg, textColor );
			desenhar(30,20,message,screen);
			desenhar(w-message->w-50,20,message,screen);
			message = TTF_RenderText_Solid( font, itoa(j1.ponto,ponto,10), textColor );
			desenhar(140,20,message,screen);
			message = TTF_RenderText_Solid( font, itoa(j2.ponto,ponto,10), textColor );
			desenhar(w-message->w-30,20,message,screen);
			desenhar(j1.posP.x,j1.posP.y,tileP,screen);
			desenhar(j2.posP.x,j2.posP.y,tileP,screen);
			desenhar(b.posB.x,b.posB.y,tileB,screen);
			break;

		//fim do jogo
		case fim:
			if(j1.ponto==10)
			{
				message = TTF_RenderText_Solid( font, "You Win!!", textColor );
				desenhar(w/2-message->w/2,h/2,message,screen);
			}else
				message = TTF_RenderText_Solid( font, "Game Over", textColor );
				desenhar(w/2-message->w/2,h/2,message,screen);
			break;
		}
		SDL_Flip(screen);
		SDL_FillRect(screen,0,0);
		
		//verificação de frames
		if(thisTime < 1000 / FRAMES_PER_SECOND )
		{
			SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - thisTime );
		}
	}
	clean_up();
	return 0;
}