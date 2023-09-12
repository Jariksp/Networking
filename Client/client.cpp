#include "client.h"

#pragma warning(disable:4996)

namespace Net {
	Client::Client(int port, std::string ipaddress) :
		wsa{ 0 },
		port(port),
		ipaddress(ipaddress),
		clientsocket(INVALID_SOCKET),
		info{ 0 },
		infolength(sizeof(info)) {
	}


	void Client::init() {

		info.sin_family = AF_INET;
		info.sin_port = htons(port);
		info.sin_addr.s_addr = inet_addr(ipaddress.c_str());


		printf("WSA init\n");
		assert(!WSAStartup(MAKEWORD(2, 2), &wsa) && "Couldn't init wsa");
		printf("WSA succes\n");

		printf("Creating socket\n");
		assert(!((clientsocket = socket(AF_INET, SOCK_DGRAM, 0)) == SOCKET_ERROR) && "Couldn't create socket");
		printf("Succes!\n");

	}

	void Client::connect() {

		init();

		for (;;)
		{
			send();
			receive();
			proccess();
		}
	}

	void Client::send() {
		printf("Enter the message:");
		std::getline(std::cin, massage);
		if (sendto(clientsocket, massage.c_str(), massage.size(), 0, (struct sockaddr*)&info, infolength) == SOCKET_ERROR)
		{
			printf("send failed... %d\n", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
	}

	void Client::receive() {

		if (recvlength = recvfrom(clientsocket, buffer, SIZE, 0, (struct sockaddr*)&info, &infolength) == SOCKET_ERROR)
		{
			printf("Receive failed... %d\n", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
	}


	void Client::proccess() {
		printf("packet from:%s:%d\n", inet_ntoa(info.sin_addr), ntohs(info.sin_port));
		for (unsigned i = 0; i < recvlength; ++i) printf("%c", buffer[i]);

	}



	Client::~Client() {
		WSACleanup();
		closesocket(clientsocket);
	}
}