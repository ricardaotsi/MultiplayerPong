#include "ClientTcp.h"
#include <string.h>
ClientTcp::ClientTcp()
{
	s = INVALID_SOCKET;
}

int ClientTcp::init()
{
	WSADATA wsaData;
	ir = WSAStartup(2.0,&wsaData);
	if (ir != 0) {
        printf("WSAStartup failed with error: %d\n", ir);
        return 1;
    }
	return 0;
}

int ClientTcp::criaSock(  char* ip, char* porta)
{
	//cria socket
	s = socket(AF_INET, SOCK_STREAM,6);
	if (s == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
	unsigned long ulAddr = INADDR_NONE;
	ulAddr = inet_addr(ip);
    if ( ulAddr == INADDR_NONE ) {
        printf("inet_addr failed and returned INADDR_NONE\n");
        WSACleanup();
        return 1;
    }
    if (ulAddr == INADDR_ANY) {
        printf("inet_addr failed and returned INADDR_ANY\n");
        WSACleanup();
        return 1;  
    }
    printf("inet_addr returned success\n");
	my_addr.sin_family = AF_INET ;
	my_addr.sin_port = htons((u_short) strtoul(porta, NULL, 0));
	my_addr.sin_addr.s_addr = inet_addr(ip);
	//conecta com o servidor
	ir = connect(s,(struct sockaddr*)&my_addr, sizeof(my_addr));
	if (ir == SOCKET_ERROR) {
        wprintf(L"connect function failed with error: %ld\n", WSAGetLastError());
        ir = closesocket(s);
        if (ir == SOCKET_ERROR)
            wprintf(L"closesocket function failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
	/*u_long iMode = 1;
	ioctlsocket(s, FIONBIO, &iMode);*/
	return 0;
}

int ClientTcp::mandaMsg(  char* dados)
{
	ir = send( s, dados, (int)strlen(dados), 0 );
    if (ir == SOCKET_ERROR) {
        wprintf(L"send failed with error: %d\n", WSAGetLastError());
        closesocket(s);
        WSACleanup();
        return 1;
    }/*else
		printf("Bytes Sent: %d\n", ir);*/
	return 0;
}

float ClientTcp::recebeMsg(char* dados)
{
	int i=0;
	char bufferrecv[1024];
	ir = recv(s, bufferrecv, (int)strlen(bufferrecv), 0);
	if(ir>0)
	{
		if(strncmp("inicia",bufferrecv,ir)==0)
		{
			i = 1;
			printf("Conexao feita jogo inicio \n");
		}else if(strncmp(dados,bufferrecv,ir)){
			i=atof(dados);
		}
	}
	return i;
}

int ClientTcp::fecharSock( )
{
	ir = shutdown(s, SD_SEND);
    if (ir == SOCKET_ERROR) {
        wprintf(L"shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(s);
        WSACleanup();
        return 1;
    }
	//finaliza cliente
	closesocket(s);
	WSACleanup();
	return 0;
}