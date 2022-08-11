#include<stdio.h>
#include<winsock2.h>
#include <windows.h>
#include <string>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

int main(int argc , char *argv[])
{
	WSADATA wsa;
    SOCKET slisten;
    SOCKET client; 
    int NumOfClients = 0;
	
	printf("\n%s\n", "Initialising Winsock...");
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		printf("%s%d\n", "Failed. Winsock Error Code : ",WSAGetLastError());
		return 1;
	}
	
	printf("%s\n", "Initialised Winsock.");

    if((slisten = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        printf("%s%d\n", "Failed to create socket : ", WSAGetLastError());
		return 1;
    }

    printf("%s\n", "Created socket.");

    sockaddr_in info;
    info.sin_addr.s_addr = inet_addr("127.0.0.1");
    info.sin_family      = AF_INET;
    info.sin_port        = htons(2556);
    int infolen = sizeof(info);

    if((bind(slisten, (struct sockaddr*)&info, infolen)) == SOCKET_ERROR)
    {
        printf("%s%d\n", "Failed to bind socket : ", WSAGetLastError());
		return 1;
    }

    printf("\n\n%s%s:%hu\n", "LISTENING ON SOCKET ", inet_ntoa(info.sin_addr), ntohs(info.sin_port));
    if(listen(slisten, SOMAXCONN) == SOCKET_ERROR)
    {
        printf("%s%d\n", "Failed to connect to socket : ", WSAGetLastError());
        return 1;
    }

    sockaddr_in clientinfo;
    int clientinfolen = sizeof(clientinfo);

    while(1)
    {
        client = accept(slisten, (struct sockaddr *)&clientinfo, &clientinfolen);
        if(client != SOCKET_ERROR)
        {
            printf("%s%s:%hu\n", "Client accepted:: ", inet_ntoa(clientinfo.sin_addr), ntohs(clientinfo.sin_port));
        }

        while(1)
        {
            if(send(client, "test", strlen("test"), 0) == SOCKET_ERROR)
            {
                printf("%s%d\n", "Failed to send message to client!", WSAGetLastError());
            }
        }
    }

    closesocket(client);
    closesocket(slisten);
    WSACleanup();
	return 0;
}