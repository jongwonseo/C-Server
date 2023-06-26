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
		char sendBuffer[100] = "Hello World!";

		for (int32 i = 0; i < 10; i++) {
			int32 resultCode = ::send(clientSocket, sendBuffer, sizeof(sendBuffer), 0);

			if (resultCode == SOCKET_ERROR)
			{
				int32 errCode = ::WSAGetLastError();
				cout << "Socket ErrorCode: " << errCode << endl;
				return 0;
			}
		}
		cout << "Send Data! Len = " << sizeof(sendBuffer) << endl;

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
