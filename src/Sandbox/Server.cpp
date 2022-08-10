#include<stdio.h>
#include<winsock2.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

int main(int argc , char *argv[])
{
	WSADATA wsa;
	
	printf("\n%s\n", "Initialising Winsock...");
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		printf("%s%d\n", "Failed. Winsock Error Code : ",WSAGetLastError());
		return 1;
	}
	
	printf("%s\n", "Initialised Winsock.");

    if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
	{
		printf("%s%d\n", "Could not create socket : " , WSAGetLastError());
        return -1;
	}

	printf("%s\n", "Created Socket.");
    

	return 0;
}