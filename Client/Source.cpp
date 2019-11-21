#include "MyClient.h"
#include <iostream>

int main()
{
	if (Network::Initialize())
	{
		MyClient client;
	//	if (client.Connect(IPEndpoint("192.168.43.233", 6113)))
	if (client.Connect(IPEndpoint("::1", 6113)))
		{
			while (client.IsConnected())
			{
				client.Frame();
			}
		}
	}
	Network::Shutdown();
	system("pause");
	return 0;
}