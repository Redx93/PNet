#include "MyServer.h"
#include <iostream>

void MyServer::OnConnect(TCPConnection & newConnection)
{
	std::cout << newConnection.ToString() << " - New connection accepted." << std::endl;

	
	std::shared_ptr<Packet> welcomeMessagePacket = std::make_shared<Packet>(PacketType::PT_ChatMessage);
	*welcomeMessagePacket << std::string("Welcome!");
	newConnection.pm_outgoing.Append(welcomeMessagePacket);
	
	std::shared_ptr<Packet> newUserMessagePacket = std::make_shared<Packet>(PacketType::PT_ChatMessage);
	*newUserMessagePacket << std::string("New user connected!");
	for (auto & connection : connections)
	{
		if (&connection == &newConnection)
			continue;

		connection.pm_outgoing.Append(newUserMessagePacket);
	}

	// Send playerstats packet
	std::shared_ptr<Packet> playerPacket = std::make_shared<Packet>(PacketType::PT_PlayerArray);
	uint32_t playerSize = this->players.size();
	*playerPacket << playerSize;
	for (auto player : players)
	{
		std::string name = player.name;
		std::uint32_t score = player.score;
		*playerPacket << name;
		*playerPacket << score;
	}
	newConnection.pm_outgoing.Append(playerPacket);
	

}

void MyServer::OnDisconnect(TCPConnection & lostConnection, std::string reason)
{
	std::cout << "[" << reason << "] Connection lost: " << lostConnection.ToString() << "." << std::endl;

	std::shared_ptr<Packet> connectionLostPacket = std::make_shared<Packet>(PacketType::PT_ChatMessage);
	*connectionLostPacket << std::string("A user disconnected!");
	for (auto & connection : connections)
	{
		if (&connection == &lostConnection)
			continue;

		connection.pm_outgoing.Append(connectionLostPacket);
	}
}

bool MyServer::ProcessPacket(std::shared_ptr<Packet> packet)
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
				//this->players.push_back(PlayerStat(name, score));
				std::cout << "Player name: " << name << "\nScore :" << score << std::endl;
			}
			break;
		}
		case PacketType::PT_PlayerStats:
		{
			std::string name;
			std::uint32_t score;
			*packet >> name;
			*packet >> score;
			//this->players.push_back(PlayerStat(name, score));
			/* GET Player stats from clien and sort it */
			std::cout << "Player name: " << name << "\nScore :" << score << std::endl;
			break;
		}
		default:
			std::cout << "Unrecognized packet type: " << packet->GetPacketType() << std::endl;
			return false;
	}

	return true;
}
