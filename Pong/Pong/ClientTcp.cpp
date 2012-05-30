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

void ClientTcp::nBlock()
{
	u_long iMode = 1;
	ioctlsocket(s, FIONBIO, &iMode);
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


float ClientTcp::recebeMsg(char *buffer, size_t size, GameState &gState)
{
	int i=0;
	int n = 1, total = 0, found = 0;
    while (!found) {
        n = recv(s, &buffer[total], size - total - 1, 0);
        if (n == -1) {
            /* Error, check 'errno' for more details */
            break;
        }
        total += n;
        buffer[total] = '\0';
        found = (strchr(buffer, '\n') != 0);
    }

	char *pch;
	pch = strtok (buffer,";");
	int j=0;
	while (pch != NULL && j < 8)
	{
		strcpy(cmd[j],pch);
		pch = strtok (NULL, ";");
		j++;
	}
	if(strncmp("comando:inicia",cmd[1],14)==0)
	{
		i = 1;
	}

	gState.fromBuffer(cmd);

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