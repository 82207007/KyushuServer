#pragma once


////////////////////////////////////////////////////////////////////////////////////////////////////
class CKyushuServer
{
public:
	CKyushuServer();
	~CKyushuServer();

public:
	virtual bool_t			ServerStop() = 0;
	virtual bool_t			ServerStart() = 0;

protected:
	void_t					OnAcceptCompletion(HANDLE hConnHandler, const char_t* ip);
	void_t					OnRecvCompletion(void_t* data, int32_t datalen);
	void_t					OnCloseCompletion(HANDLE hConnHandler);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
CKyushuServer* InitKyushuServer(int32_t dwServer, int32_t dwDataCenter, int32_t dwWorkThreadCount, int32_t usPort);