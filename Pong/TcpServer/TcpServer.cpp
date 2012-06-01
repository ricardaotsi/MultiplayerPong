#include "TcpServer.h"

#include <iostream>
#include <stdio.h>
#include "Vector2D.h"
#include <tchar.h>
#include "GameState.h"

#define W 800
#define H 600

GameState *gState;
SOCKET sd;
SOCKET sd2;

void sendGameState()
{
	char* dados=gState->toBuffer(1);
	send( sd, dados, (int)strlen(dados), 0 );
	// printf("Dados para o player 1:\n%s\n", dados);
	dados=gState->toBuffer(2);
	send( sd2, dados, (int)strlen(dados), 0 );
}

int _tmain()
{
	//Inicia socket v2.0
	int verErro;
	WSADATA wsaData;
	verErro = WSAStartup(2.0,&wsaData);
	if (verErro != 0) {
        printf("WSAStartup failed with error: %d\n", verErro);
        return 1;
    }


	//cria socket
	SOCKET s = INVALID_SOCKET;
	s = socket(AF_INET, SOCK_STREAM,6);
	if (s == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

	//seta opções do socket
	int * p_int ;
	p_int = (int*)malloc(sizeof(int));
	*p_int = 1;
	verErro = setsockopt(s,SOL_SOCKET,SO_REUSEADDR, (char*)p_int, sizeof(int));
	if (verErro == SOCKET_ERROR) {
        wprintf(L"setsockopt for SO_REUSEADDR failed with error: %u\n", WSAGetLastError());
    } else
        wprintf(L"Set SO_REUSEADDR: ON\n");

	//Descobre a porta e ip do servidor
	// std::cout << "Digite a porta: \n";
	// char* porta = new CHAR();
	// std::cin>> porta;
	PCSTR porta = {"2222"};
	struct addrinfo *result = NULL;
	struct addrinfo hints;
	ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;
    verErro = getaddrinfo(NULL,porta, &hints, &result);
    if ( verErro != 0 ) {
        printf("getaddrinfo failed with error: %d\n", verErro);
        WSACleanup();
        return 1;
    }	

	//Cria a função de listen do socket 
	bind(s,result->ai_addr, (int)result->ai_addrlen);
	 if (verErro == SOCKET_ERROR) {
        wprintf(L"bind failed with error %u\n", WSAGetLastError());
        closesocket(s);
        WSACleanup();
       return 1;
    }
    else
        wprintf(L"bind returned success\n");
	
	verErro = listen(s,2);
	if (verErro == SOCKET_ERROR)
	{
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(s);
		WSACleanup();
		return 1;
	}

	
	//aceita conexão do cliente 1
	sd = accept(s,NULL,NULL);
	if (sd == INVALID_SOCKET) {
		printf("accept failed with error: %d\n", WSAGetLastError());
		closesocket(sd);
		WSACleanup();
		return 1;
	}else
		printf("Connection successful \n");

	sd2 = INVALID_SOCKET;
	//aceita conexão do cliente 1
	sd2 = accept(s,NULL,NULL);
	if (sd2 == INVALID_SOCKET) {
		printf("accept failed with error: %d\n", WSAGetLastError());
		closesocket(sd);
		WSACleanup();
		return 1;
	}else
		printf("Connection successful \n");

	//seta como não bloqueante
	u_long iMode = 1;
	ioctlsocket(sd, FIONBIO, &iMode);
	ioctlsocket(sd2, FIONBIO, &iMode);
	//char* dados = "inicia";
	gState = new GameState(W,H);
	sendGameState();
	//printf(gState->toBuffer());

	int fps = 15;
	while(1){
		char buffer[512];
		//memset(buffer, 0, 511);
		verErro = recv(sd, buffer,(int)strlen(buffer), 0);
		if(verErro>0)
		{
			gState->update(buffer,1);
		}
		char buffer2[512];
		verErro = recv(sd2, buffer2,(int)strlen(buffer2), 0);
		if(verErro>0)
		{
			gState->update(buffer2,2);
		}

		// Fazer cálculo da bola fora do update
		// Como passar o deltaTime? Tem que ser o mesmo para os dois jogadores, então terá que estar no servidor (?)
		gState->moverBola(0.05, 200);

		sendGameState();

		Sleep(1000 / fps);
	}
	return 0;
}


