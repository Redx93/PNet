#pragma once
#include <PNet/IncludeMe.h>

struct Player
{
	char name[32] = "Unknown";
	uint32_t score = 7;
};

struct Data {
	Player playerData[10];
};
class MyClient : public Client
{
private:
	Player player;
public:
	bool ProcessPacket(std::shared_ptr<Packet> packet) override;
	void OnConnect() override;
	//void OnConnectFail() override;
	//void OnDisconnect(std::string reason) override;
};