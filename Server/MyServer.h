#pragma once
#include <PNet/IncludeMe.h>

using namespace std;
struct Player
{
	char name[32] = "Unknown";
	uint32_t score = 55;
};
class MyServer : public Server
{
public:
	Player player;
private:
	void OnConnect(TCPConnection & newConnection) override;
	void OnDisconnect(TCPConnection & lostConnection, std::string reason) override;
	bool ProcessPacket(std::shared_ptr<Packet> packet) override;
};