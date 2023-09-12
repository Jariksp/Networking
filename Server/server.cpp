#include "server.h"

#pragma warning(disable:4996)

namespace Net 
{
	Server::Server(int port, std::string ipaddress) :
		wsa{ 0 },
		port(port),
		ipaddress(ipaddress),
		serversocket(INVALID_SOCKET),
		info{ 0 }, 
		infolength(sizeof(info)) {}
		
	
	void Server::init() {

		info.sin_family = AF_INET;
		info.sin_port = htons(port);
		info.sin_addr.s_addr = inet_addr(ipaddress.c_str());


		printf("WSA init\n");
		assert(!WSAStartup(MAKEWORD(2,2), &wsa) && "Couldn't init wsa");
		printf("WSA succes\n");

		printf("Creating socket\n");
		assert(!((serversocket = socket(AF_INET, SOCK_DGRAM, 0)) == SOCKET_ERROR) && "Couldn't create socket");
		printf("Succes!\n");


		printf("bind socket\n");
		assert(!(bind(serversocket, (struct sockaddr*)&info, infolength)) && "Couldn't bind socket");
		printf("socket binded\n");

		printf("Server started at:%s:%d\n", inet_ntoa(info.sin_addr), ntohs(info.sin_port));

	}
	
	void Server::start() {

		init();

		for (;;) {
			receive();
			proccess();
			send();
		}
	}
	
	void Server::receive() {
		
		if ((recvlength = recvfrom(serversocket, buffer, SIZE, 0, (struct sockaddr*)&info, &infolength)) == SOCKET_ERROR)
		{
			printf("Receive failed... %d\n", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
	}


	void Server::proccess() {
		printf("packet from:%s:%d\n", inet_ntoa(info.sin_addr), ntohs(info.sin_port));
		for (unsigned i = 0; i < recvlength; ++i)
		{
			printf("%c", buffer[i]);
		}
		printf("\n");

	}

	void Server::send() {
		if (sendto(serversocket, buffer, recvlength, 0, (struct sockaddr*)&info, infolength) == SOCKET_ERROR) 
		{
			printf("send failed... %d\n", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
	}

	Server::~Server() {
		WSACleanup();
		closesocket(serversocket);
	}
}