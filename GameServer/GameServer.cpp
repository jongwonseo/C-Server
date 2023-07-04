#include "pch.h"
#include "ThreadManager.h"
#include "Service.h"
#include "Session.h"
#include "GameSession.h"
#include "GameSessionManager.h"
#include "BufferWriter.h"
#include "ServerPacketHandler.h"

// 컴퓨터는 8바이트 주소로 접근을 해야 빠름
#pragma pack(1) //os야 1바이트씩 확인해라
struct PKT_S_TEST
{
	uint32 hp; //8 빈공간은 더미
	uint64 id; //8
	uint16 attack; //8

};
#pragma pack()

int main()
{
	PKT_S_TEST pkt;
	pkt.hp = 1;
	pkt.id = 2;
	pkt.attack = 3;

	ServerServiceRef service = MakeShared<ServerService>(
		NetAddress(L"127.0.0.1", 7777),
		MakeShared<IocpCore>(),
		MakeShared<GameSession>, // TODO : SessionManager 등
		100);

	ASSERT_CRASH(service->Start());

	for (int32 i = 0; i < 5; i++)
	{
		GThreadManager->Launch([=]()
			{
				while (true)
				{
					service->GetIocpCore()->Dispatch();
				}
			});
	}

	char sendData[1000] = "Hello World";

	while (true)
	{
		vector<BuffData> buffs{ BuffData {100, 1.5f}, BuffData{ 200, 2.3f }, BuffData{ 300, 0.7f } };
		SendBufferRef sendBuffer = ServerPacketHandler::Make_S_TEST(1001, 100, 10, buffs, L"안녕하세요");
		GSessionManager.Broadcast(sendBuffer);

		this_thread::sleep_for(250ms);
	}

	GThreadManager->Join();
}