#include "pch.h"
#include <iostream>

///////////////////////////
#include<WinSock2.h>
#include<MSWSock.h>
#include<WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")
///////////////////////////
void HandleError(const char* cause)
{
	int32 errCode = ::WSAGetLastError();
	cout << cause << " ErrorCode: " << errCode << endl;
}

int main()
{
	// 윈소켓 초기화
	WSAData wsaData;
	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return 0;

	// af: Address Family(AF_INET = IPv4, AF_INET6 = IPv^)
	// type: TCP(SOCK_STREAM) vs UDP(SOCK_DGRAM)
	// protocol : 0
	// return : descriptor
	SOCKET clientSocket = ::socket(AF_INET, SOCK_DGRAM, 0);
	if (clientSocket == INVALID_SOCKET)
	{
		HandleError("Socket");
		return 0;
	}

	//연결 목적지(IP +port)
	SOCKADDR_IN serverAddr; //IPv4
	::memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	//serverAddr.sin_addr.s_addr = ::inet_addr("127.0.0.1");
		
	::inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);
	// 서버 아이피를 넣으면 됨
	
	serverAddr.sin_port = ::htons(7777);
	//host to network short

	// Connected UDP
	::connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));


	while (true)
	{
		char sendBuffer[100] = "Hello World!";

		
		// connected UDP
		int32 resultCode = ::send(clientSocket, sendBuffer, sizeof(sendBuffer), 0);
		
		// original UDP(unconnected UDP)
		//int32 resultCode = ::sendto(clientSocket, sendBuffer, sizeof(sendBuffer), 0, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
		
		if (resultCode == SOCKET_ERROR)
		{
			HandleError("SandTo");
			return 0;
		}
	
		cout << "Send Data! Len = " << sizeof(sendBuffer) << endl;

		char recvBuffer[1000];

		SOCKADDR_IN recvAddr;
		::memset(&recvAddr, 0, sizeof(recvAddr));
		int32 addrLen = sizeof(recvAddr);

		// connected UDP
		int32 recvLen = ::recv(clientSocket, recvBuffer, sizeof(recvBuffer), 0);


		// original UDP(unconnected UDP)
		//int32 recvLen = ::recvfrom(clientSocket, recvBuffer, sizeof(recvBuffer), 0,(SOCKADDR*)&recvAddr, &addrLen);
		if (recvLen <= 0)
		{
			HandleError("RecvFrom");
			return 0;
		}
		this_thread::sleep_for(1s);
		//// 서버에서 데이터 받음
		//char recvBuffer[100]; //넉넉하게 만들기

		//// receive한 바이트 리턴
		//int32 recevLen = ::recv(clientSocket, recvBuffer, sizeof(recvBuffer), 0);

		//if (recevLen <= 0)
		//{
		//	int32 errCode = ::WSAGetLastError();
		//	cout << "Socket ErrorCode: " << errCode << endl;
		//	return 0;
		//}

		//cout << "receive Data! Len " << recevLen << endl;
		//cout << "receive Data! " << recvBuffer << endl;

		//this_thread::sleep_for(1s);
	}

	//소켓 리소스 반환
	::closesocket(clientSocket);

	//윈속 종료
	::WSACleanup();
}
