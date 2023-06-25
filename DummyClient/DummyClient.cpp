#include "pch.h"
#include <iostream>

///////////////////////////
#include<WinSock2.h>
#include<MSWSock.h>
#include<WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")
///////////////////////////

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
	SOCKET clientSocket = ::socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket == INVALID_SOCKET)
	{
		int32 errCode = ::WSAGetLastError();
		cout << "Socket ErrorCode: " << errCode << endl;
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

	// Little-Endian(almost) vs Big-Endian
	// ex) 0x12345678 4바이트 정수
	// low [0x78][0x56][0x34][0x21] high : little
	// low [0x12][0x34][0x56][0x78] high : big

	if(::connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr))==SOCKET_ERROR)
	{
		int32 errCode = ::WSAGetLastError();
		cout << "Socket ErrorCode: " << errCode << endl;
		return 0;
	}

	/////////////////////////////////////////////////
	// 연결성공, 데이터 송수신 가능
	
	cout << "Connected to server";
	while (true)
	{
		this_thread::sleep_for(1s);
	}

	//소켓 리소스 반환
	::closesocket(clientSocket);

	//윈속 종료
	::WSACleanup();
}
