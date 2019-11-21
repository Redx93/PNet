#pragma once
#include <PNet/IncludeMe.h>

using namespace std;
struct PlayerStat
{
	std::string name = "Unknown";
	uint32_t score = 0;
	PlayerStat(std::string name, uint32_t score) :name(name), score(score) {	}
};

class MyServer : public Server
{
public:
	std::vector<PlayerStat> players;
private:
	void OnConnect(TCPConnection & newConnection) override;
	void OnDisconnect(TCPConnection & lostConnection, std::string reason) override;
	bool ProcessPacket(std::shared_ptr<Packet> packet) override;
};