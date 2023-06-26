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
	// 윈속 초기화 (ws2_32 라이브러리 초기화)
	// 관련 정보가 wsaData에 채워짐
	WSAData wsaData;
	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return 0;

	// UDP는 여러개의 accpet된 소캣(client_socket)이 필요하지 않고 1개의 소켓으로 모든것을 커버
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

	// 옵션을 해석하고 처리할 주체
	// 소켓 -> SOL_SOCKET
	// IPv4 -> IPPROTO_IP
	// TCP 프로토콜 -> IPPROTO_TCP

	// SO_KEEPALIVE = 주기적으로 연결 상태 확인 여부(TCP only)
	// 상대방이 소리소문없이 연결 끊는다면?
	// 주기적으로 TCP 프로토콜 연결 상태 확인 -> 끊어진 연결 감지
	bool enable = true;
	::setsockopt(serverSocket, SOL_SOCKET, SO_KEEPALIVE,(char*)&enable, sizeof(enable));
	
	// SO_LINGER
	// 송신 버퍼에 있는 데이터를 보낼 것인가? 날릴 것인가?
	// onoff = 0이면 closesocket()이 바로 리턴, 아니면 linger초만큼 대기 (default 0)
	//linger: 대기시간
	LINGER linger;
	linger.l_onoff = 1;
	linger.l_linger = 5;
	::setsockopt(serverSocket, SOL_SOCKET, SO_LINGER, (char*)&linger, sizeof(linger));

	//Half-Close
	// SD_SEND: send 막는다
	// SD_RECEIVEL: recv 막는다
	// SD_BOTH: 둘다 막는다
	//::shutdown(serverSocket, SD_SEND); // 듣기만 하겠다
	
	//소켓리소스 반환
	//::closesocket(serverSocket);

	// SO_SNDBUF = 송신 버퍼 크기
	// SO_RCVBUF = 수신 버퍼 크기
	
	int32 sendBufferSize;
	int32 optionLen = sizeof(sendBufferSize);
	::getsockopt(serverSocket, SOL_SOCKET, SO_SNDBUF, (char*)&sendBufferSize, &optionLen);
	cout << "송신 버퍼 크기: " << sendBufferSize;

	int32 recvBufferSize;
	optionLen = sizeof(recvBufferSize);
	::getsockopt(serverSocket, SOL_SOCKET, SO_RCVBUF, (char*)&sendBufferSize, &optionLen);
	cout << "송신 버퍼 크기: " << recvBufferSize;


	// SO_REUSEADDR
	// IP주소 및 port 재사용
	{	
		bool enable = true;
		::setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&enable, sizeof(enable));
	}

	// IPPROTO_TCP
	// TCP_NODELAY = 네이글 알고리즘 작동 여부
	// // 데이터가 충분히 크면 보내고, 그렇지 않으면 충분히 쌓일때까지 대기(회선낭비 줄이고, 효율적으로)
	// 장) 작은패킷이 불필요하게 많이 생성되는 일을 방지
	// 단) 반응 시간 손해
	{
		bool enable = true;
		::setsockopt(serverSocket, IPPROTO_TCP, TCP_NODELAY, (char*)&enable, sizeof(enable));
	}

	// 윈속 종료
	::WSACleanup();
}