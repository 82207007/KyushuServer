#include "stdafx.h"
#include "CKyushServer.h"


extern CKyushuServer* theServer;
////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t OnCommand(const char_t* command)
{

	return true;
};

struct SConfigServer
{
	SConfigServer()
	{
		memset(this, 0, sizeof(SConfigServer));
		return;
	};

	int32_t usServerID;
	int32_t usDataCenterID;
	int32_t	usDBThreadCount;
	int32_t usPort;
};
SConfigServer g_config;

void_t loadServerDefaultConfig()
{
#ifdef _DEBUG
	//char_t path[] = "..\\bin\\ServerInfo.ini";
	char_t path[] = "ServerInfo.ini";
#else
	char_t path[] = "ServerInfo.ini";
#endif // _DEBUG
	
	g_config.usServerID = GetPrivateProfileIntA("SYSTEM", "SERVER_ID", 1, path);
	g_config.usDataCenterID = GetPrivateProfileIntA("SYSTEM", "DATACENTERID", 1, path);
	g_config.usDBThreadCount = GetPrivateProfileIntA("SYSTEM", "DBThreadCount", 4, path);
	g_config.usPort = GetPrivateProfileIntA("SYSTEM", "SERVER_PORT", 14800, path);
	return;
};


#include "CNetworkDefault.h"
#pragma warning(disable : 4996)

////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t main()
{
	loadServerDefaultConfig();

	theServer = InitKyushuServer(g_config.usServerID, g_config.usDataCenterID, g_config.usDBThreadCount, g_config.usPort);
	if (theServer)
	{
		if (false == theServer->ServerStart())
			return 0;

		stUserRequestLoginCmd cmd;
		cmd.subtype = 10001;
		strcpy(cmd.name, "82207007");
		strcpy(cmd.password, "qq2691351");
		//theServer->SendMsg(nullptr, &cmd);


		char_t command[1024] = { NULL };
		while (true)
		{
			gets_s(command);

			if (strlen(command) <= 0)
				continue;

			if (false == OnCommand(command))
				break;
		}

		theServer->ServerStop();
		delete theServer;
		theServer = 0;
	}	

	return 0;
};