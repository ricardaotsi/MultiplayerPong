#include <ws2tcpip.h>
#include <WinSock2.h>
#include <stdio.h>
#include <iostream>

class ClientTcp
{
private:
	int ir;
	struct sockaddr_in my_addr;
	SOCKET s;
public:
	ClientTcp();
	int init();
	int criaSock(  char* ip, char* porta);
	int mandaMsg( char* dados);
	float recebeMsg(char* dados );
	int fecharSock( );
};

