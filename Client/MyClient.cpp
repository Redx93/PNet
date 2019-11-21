#include "MyClient.h"
#include <iostream>

bool MyClient::ProcessPacket(std::shared_ptr<Packet> packet)
{
	switch (packet->GetPacketType())
	{
	case PacketType::PT_ChatMessage:
	{
		std::string chatmessage;
		*packet >> chatmessage;
		std::cout << "Chat Message: " << chatmessage << std::endl;
		break;
	}
	case PacketType::PT_IntegerArray:
	{
		uint32_t arraySize = 0;
		*packet >> arraySize;
		std::cout << "Array Size: " << arraySize << std::endl;
		for (uint32_t i = 0; i < arraySize; i++)
		{
			uint32_t element = 0;
			*packet >> element;
			std::cout << "Element[" << i << "] - " << element << std::endl;
		}
		break;
	}
	case PacketType::PT_PlayerArray:
	{
		uint32_t playerSize = 0;
		*packet >> playerSize;
		std::cout << "Number of Players : " << playerSize << std::endl;
		for (uint32_t i = 0; i < playerSize; i++)
		{
			std::string name;
			std::uint32_t score = 0;
			*packet >> name;
			*packet >> score;
			this->players.push_back(PlayerStat(name, score));
			std::cout << "Player name: " <<name << "	 Score :" << score  << std::endl;
		}
		break;
	}
	case PacketType::PT_PlayerStats:
	{
		std::string name;
		std::uint32_t score;
		*packet >> name;
		*packet >> score;
		this->players.push_back(PlayerStat(name, score));
		std::cout << "Player name: " << name << "\nScore :" << score << std::endl;
		break;
	}
	default:
		std::cout << "Unrecognized packet type: " << packet->GetPacketType() << std::endl;
		return false;
	}

	return true;
}

void MyClient::OnConnect()
{

	std::cout << "Successfully connected to the server!" << std::endl;

	std::shared_ptr<Packet> helloPacket = std::make_shared<Packet>(PacketType::PT_ChatMessage);
	*helloPacket << std::string("Hello I am a new Client");
	connection.pm_outgoing.Append(helloPacket);

}
