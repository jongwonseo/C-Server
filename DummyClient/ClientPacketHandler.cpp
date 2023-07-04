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

// [ PK_S_TEST ][BuffsListItem BuffsListItem BuffsListItem(가변 데이터)]
#pragma pack(1)
struct PKT_S_TEST
{
	struct BuffsListItem
	{
		uint64 buffId;
		float remainTime;
	};

	uint16 packetSize;
	uint16 packetId;
	uint64 id;
	uint32 hp;
	uint16 attack;

	uint16 buffsOffset; // 가변인자 등장하는 인덱스
	uint16 buffsCount;
	
	bool Validation()
	{
		uint32 size = 0;
		size += sizeof(PKT_S_TEST);
		size += buffsCount * sizeof(BuffsListItem);
		
		if (size != packetSize)
			return false;
		
		if (buffsOffset + buffsCount * sizeof(BuffsListItem) < packetSize)
			return false;
		return true;
	}

	// vector<BuffData> buffs;
	// wstring name;
};
#pragma pack()

void ClientPacketHandler::Handle_S_TEST(BYTE* buffer, int32 len)
{
	BufferReader br(buffer, len);
	
	if (len < sizeof(PKT_S_TEST))
		return;

	PKT_S_TEST pkt;
	br >> pkt;

	if (pkt.Validation() == false)
		return;
	// br >> id >> hp >> attack;
	// printf("id: %d, hp: %d, att: %d", id, hp, attack);

	vector<PKT_S_TEST::BuffsListItem> buffs;

	buffs.resize(pkt.buffsCount);
	for (int32 i = 0; i < pkt.buffsCount; i++)
	{
		br >> buffs[i];
	}

	cout << "BuffCOunt: " << pkt.buffsCount << endl;
	for (int32 i = 0; i < pkt.buffsCount; i++)
	{
		cout<<"BuffInfo: "<< buffs[i].buffId <<"  "<< buffs[i].remainTime; 
	}
}
