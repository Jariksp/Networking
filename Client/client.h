#pragma once
#include <cassert>
#include <thread>
#include <unordered_map>
#include <vector>
#include <string>
#include <WinSock2.h>
#include <iostream>

#pragma comment(lib, "Ws2_32.lib")

#define SIZE 1024

namespace Net {

	class Client {

		private:
		WSADATA wsa;
		SOCKET clientsocket;

		private:
		std::string ipaddress;
		std::string massage;
		char buffer[SIZE];
		int port;

		private:
		struct sockaddr_in info;

		private:
		int infolength;
		int recvlength;

		private:
		void receive();
		void proccess();

		private:
		void init();
		void send();

		public:
		void connect();

		public:
		Client(int, std::string);
		~Client();

	};
}