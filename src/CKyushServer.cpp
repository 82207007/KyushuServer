#include "stdafx.h"
#include "CKyushServer.h"


CKyushuServer* theServer;
////////////////////////////////////////////////////////////////////////////////////////////////////
CKyushuServer::CKyushuServer()
{
	return;
};

CKyushuServer::~CKyushuServer()
{
	return;
};


void_t CKyushuServer::OnAcceptCompletion(HANDLE hConnHandler, const char_t* ip)
{
#ifdef _DEBUG
	PrintLog("UserConnect: %s\n", ip);

#endif

	return;
};

void_t CKyushuServer::OnRecvCompletion(void_t* data, int32_t datalen)
{
#ifdef _DEBUG
	PrintLog("UserData: %X[%d]\n", data, datalen);

#endif

	return;
};

void_t CKyushuServer::OnCloseCompletion(HANDLE hConnHandler)
{
#ifdef _DEBUG
	PrintLog("UserClose: %X[%d]\n", hConnHandler);

#endif

	return;
};