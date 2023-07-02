﻿#pragma once
#include "IocpCore.h"
#include "IocpEvent.h"
#include "NetAddress.h"
#include "RecvBuffer.h"

class Service;

/*--------------
	Session
---------------*/

class Session : public IocpObject
{

	friend class Listener;
	friend class IocpCore;
	friend class Service;

	enum
	{
		BUFFER_SIZE = 0x10000,
	};

public:
	Session();
	virtual ~Session();

public:
	void				Send(BYTE* buffer, int32 len);

	void				Disconnect(const WCHAR* cause);
	bool				Connect();
	shared_ptr<Service> GetService() { return _service.lock(); }
	void				SetService(shared_ptr<Service> service) { _service = service; }

public:
	/* 정보 관련 */
	void		SetNetAddress(NetAddress address) { _netAddress = address; }
	NetAddress	GetAddress() { return _netAddress; }
	SOCKET		GetSocket() { return _socket; }
	bool		IsConnected() { return _connected; }
	SessionRef	GetSessionRef() { return static_pointer_cast<Session>(shared_from_this()); }
	
private:
	/* 인터페이스 구현 */
	virtual HANDLE		GetHandle() override;
	virtual void		Dispatch(class IocpEvent* iocpEvent, int32 numOfBytes = 0) override;

private:
	/* 전송 관련*/
	bool		RegisterConnect();
	bool		RegisterDisconnect();
	void		RegisterRecv();
	void		RegisterSend(SendEvent* sendEvent);

	void		ProcessConnect();
	void		ProcessDisconnect();
	void		ProcessRecv(int32 numOfBytes);
	void		ProcessSend(SendEvent* seendEvent, int32 numOfBytes);

	void		HandleError(int32 errorCode);

protected:
	/* 칸텐츠 코드에서 오버로딩*/
	virtual void		OnConnected() {}
	virtual int32		OnRecv(BYTE* buffer, int32 len) { return len; }
	virtual void		OnSend(int32 len) {}
	virtual void		OnDisconnected() {}

private:
	weak_ptr<Service>	_service;
	SOCKET				_socket = INVALID_SOCKET;
	NetAddress			_netAddress = {};
	Atomic<bool>		_connected = false;

private:
	USE_LOCK;

	RecvBuffer _recvBuffer;
private:
	/* IocpEvent 재사용*/
	ConnectEvent		_connectEvent;
	DisconnectEvent		_disconnectEvent;
	
	RecvEvent			_recvEvent;
};

