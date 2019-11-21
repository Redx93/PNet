#include "MyServer.h"
#include <iostream>

int main()
{
	if (Network::Initialize())
	{
		MyServer server;
		std::string arr[10] = { "Per","Carl", "Olle", "Filip", "Pelle", "Karl", "Sceeet", "Frame", "shutdown", "IP" };
		for (size_t i = 0; i < 10; i++)
		{
			server.players.push_back(PlayerStat(arr[i], i));
		}

		if (server.Initialize(IPEndpoint("::", 6113)))
		{
			while (true)
			{
				server.Frame();
			}
		}
	}
	Network::Shutdown();
	system("pause");
	return 0;
}