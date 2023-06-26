#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <atomic>
#include <mutex>
#include <windows.h>
#include <future>
#include "ThreadManager.h"

#include <winsock2.h>
#include <mswsock.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

void HandleError(const char* cause)
{
	int32 errCode = ::WSAGetLastError();
	cout << cause << " ErrorCode: " << errCode << endl;
}
int main()
{
	// ���� �ʱ�ȭ (ws2_32 ���̺귯�� �ʱ�ȭ)
	// ���� ������ wsaData�� ä����
	WSAData wsaData;
	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return 0;

	// UDP�� �������� accpet�� ��Ĺ(client_socket)�� �ʿ����� �ʰ� 1���� �������� ������ Ŀ��
	SOCKET serverSocket = ::socket(AF_INET, SOCK_DGRAM, 0);
	if (serverSocket == INVALID_SOCKET)
	{
		HandleError("Socket");
		return 0;
	}

	SOCKADDR_IN serverAddr;
	::memset(&serverAddr, 0, sizeof(SOCKADDR_IN));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = ::htonl(INADDR_ANY);
	serverAddr.sin_port = ::htons(7777);

	if (::bind(serverSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		HandleError("Bind");
		return 0;
	}

	while (true)
	{
		SOCKADDR_IN clientAddr;
		::memset(&clientAddr, 0, sizeof(clientAddr));
		int32 addrLen = sizeof(clientAddr);
		char recvBuffer[1000];
		
		int32 recvLen = ::recvfrom(serverSocket, recvBuffer, sizeof(recvBuffer), 0, (SOCKADDR*)&clientAddr, &addrLen);
		
		if (recvLen <= 0)
		{
			HandleError("RecvFrom");
			return 0;
		}

		cout << "receive Data! Len " << recvLen << endl;
		cout << "receive Data! " << recvBuffer << endl;
	
	
		int32 errorCode = ::sendto(serverSocket, recvBuffer, recvLen,0,(SOCKADDR*)&clientAddr,sizeof(clientAddr));
	
		if (errorCode == SOCKET_ERROR)
		{
			HandleError("SandTo");
			return 0;
		}

		cout << "Send Data! Len = " << recvLen << endl;
	}
	// ���� ����
	::WSACleanup();
}