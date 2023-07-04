#include "pch.h"
#include "ClientPacketHandler.h"
#include "BufferReader.h"

void ClientPacketHandler::HandlePacket(BYTE* buffer, int32 len)
{

	BufferReader br(buffer, len);
	PacketHeader header;
	br >> header;

	// cout << "Packet ID: " << header.id << " Size: " << header.size << endl;

	switch (header.id)
	{
	case S_TEST:
		Handle_S_TEST(buffer, len);
		break;
	}
}

struct BuffData
{
	uint64 buffId;
	float remainTime;
};

struct S_TEST
{
	uint64 id;
	uint32 hp;
	uint16 attack;

	vector<BuffData> buffs;
	wstring name;
};

void ClientPacketHandler::Handle_S_TEST(BYTE* buffer, int32 len)
{
	BufferReader br(buffer, len);
	PacketHeader header;

	br >> header;
	uint64 id;
	uint32 hp;
	uint16 attack;
	br >> id >> hp >> attack;
	printf("id: %d, hp: %d, att: %d", id, hp, attack);

	vector<BuffData> buffs;
	uint16 buffCount;
	br >> buffCount;

	buffs.resize(buffCount);
	for (int32 i = 0; i < buffCount; i++)
	{
		br >> buffs[i].buffId >> buffs[i].remainTime;
	}

	cout << "BuffCOunt: " << buffCount << endl;
	for (int32 i = 0; i < buffCount; i++)
	{
		cout<<"BuffInfo: "<< buffs[i].buffId <<"  "<< buffs[i].remainTime; 
	}

	wstring name;
	uint16 nameLen;
	br >> nameLen;
	name.resize(nameLen);
	br.Read((void*)name.data(), nameLen * sizeof(WCHAR));

	wcout.imbue(std::locale("kor"));
	wcout << name << endl;

}
