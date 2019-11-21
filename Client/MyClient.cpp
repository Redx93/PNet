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
	case PacketType::PT_Player:
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
			std::cout << "Player name: " <<name << "\nScore :" << score  << std::endl;
		}
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



	// Send playerstats packet
	//std::shared_ptr<Packet> playerPacket = std::make_shared<Packet>(PacketType::PT_Player);
	//uint32_t playerSize = 1;
	//*playerPacket << playerSize;
	////std::cout << "Number of Players : " << playerSize << std::endl;
	//for (int i = 0;	i < playerSize;i++)
	//{
	//	//std::cout << "Inside for loop in server for Players : " << playerSize << std::endl;
	//	std::string name = player.name;
	//	std::uint32_t score = player.score;
	//	*playerPacket << name;
	//	*playerPacket << score;
	//}
	//connection.pm_outgoing.Append(playerPacket);

	//std::cout << "Successfully connected to the server!" << std::endl;
	//std::shared_ptr<Packet> helloPacket = std::make_shared<Packet>(PacketType::PT_ChatMessage);
	//*helloPacket << player.name;
	//connection.pm_outgoing.Append(helloPacket);
	//player.score = 222;
	//std::shared_ptr<Packet> integersPacket = std::make_shared<Packet>(PacketType::PT_IntegerArray);
	////uint32_t arraySize = 1;
	////uint32_t integerArray[6] = { 2, 5, 7, 1, 2, 9 };
	////player.score = 111;
	//*integersPacket << 1;
	////for (auto integer : integerArray)
	////{
	////	*integersPacket << integer;
	////}
	//*integersPacket << player.score;
	//connection.pm_outgoing.Append(integersPacket);
}
