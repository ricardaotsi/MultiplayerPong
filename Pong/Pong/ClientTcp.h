#include <ws2tcpip.h>
#include <WinSock2.h>
#include <stdio.h>
#include <iostream>
#include "GameState.h"

class ClientTcp
{
private:
	int ir;
	struct sockaddr_in my_addr;
	SOCKET s;
	

public:
	char cmd[8][100];
	ClientTcp();
	int init();
	int criaSock(  char* ip, char* porta);
	int mandaMsg( char* dados);
	float recebeMsg(char *buffer, size_t size, GameState &gState);
	int fecharSock( );
	void nBlock();
};

