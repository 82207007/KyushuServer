#include "stdafx.h"
#include "CKyushServer.h"


CKyushuServer* theServer;
////////////////////////////////////////////////////////////////////////////////////////////////////
CKyushuServer::CKyushuServer()
{
#ifdef ThreadEvent
	CreateIOCPWorkers(dwNumberOfProcess * 2);
	CAcceptor* acceptor = nullptr;
	for (int32_t i = 0; i < acceptor.Count(); i++) {
		acceptor = m_acceptors[i];
		acceptor->Start();
	}

#endif
	return;
};

CKyushuServer::~CKyushuServer()
{
#ifdef ThreadEvent
	CAcceptor* acceptor = NULL;
	for (int i = 0; i < m_acceptors.Count(); i++) {
		acceptor = m_acceptors[i];
		acceptor->Stop();
	}

#endif

	return;
};


void_t CKyushuServer::OnAcceptCompletion(HANDLE hConnHandler, const char_t* ip)
{
#ifdef ThreadEvent
	PrintLog("UserConnect: %s\n", ip);
	
	CAcceptor* acceptor = new CAcceptor;
	if (NULL == acceptor)
		return false;

	acceptor->Init(acceptHandler, port, SOMAXCONN);
	m_acceptors.AddToTail(acceptor);
#endif

	return;
};

void_t CKyushuServer::OnRecvCompletion(void_t* data, int32_t datalen)
{
#ifdef ThreadEvent
	PrintLog("UserData: %X[%d]\n", data, datalen);

	int32_t result = Push((char_t*)recvIOCP.GetBuffer(), datalen);
	if (0 == result) {
		requestdisconnect();
		return;
	}

	recvIOCP.Clear();
	if (false = requestRecv()) {
		requestDisconnect();
		return;
	}

	inline bool RequestRecv()
	{
		DWORD flags = 0;
		DWORD recved = 0;
		int result = WSARecv(m_socket, recvIOCP.GetWSABUF(), 1, &recved, &flags, (LPWSAOVERLAPPED)&recvIOCP, NULL);
		if (0 != result) {
			DWORD error = WSAGetLastError();
			if (error != ERROR_IO_PENDING) {
				Trace("WSARecv Error (%d)\n", error);
				return false;
			}
		}

		m_refCnt++;
		return true;
	}
	RequestRecv();

	switch ((int32_t*)data)
	{
	case login:
		if (true == getlogin(data, datalen, buffer))
			send(buffer)
		break;

	case reg:
		if (true == getreg(data, datalen, buffer))
			send(buffer)
		break;

	case reg2:
		if (true == getreg2(data, datalen, buffer))
			send(buffer)
		break;

	default:
		break;
	}

#endif

	return;
};

void_t CKyushuServer::OnCloseCompletion(HANDLE hConnHandler)
{
#ifdef ThreadEvent
	PrintLog("UserClose: %X[%d]\n", hConnHandler);

	close(hConnHandler);
#endif

	return;
};