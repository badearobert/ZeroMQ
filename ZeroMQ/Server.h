#pragma once
/******************************************************************************
* Copyright (C) 17/04/2017
*
* @file         Server.h
* @project		ZeroMQ
* @author       Robert Badea
* @url			www.robertbadea.ro
******************************************************************************
* Server implementation of IBase
* The server connect to the inproc server as ZMQ_REP (server).
* It will receive multiple messages from the client until receiving the goodbye msg.
*****************************************************************************/
//--------------------------------------------------------------------
//                              Includes
//--------------------------------------------------------------------
#include "IBase.h"

class Server : public IBase
{
public:
	Server(void* const context, std::string connectionAddress)
		: IBase(context, connectionAddress)
	{ 
		// creating the socket..
		mSocket = zmq_socket(mContext, ZMQ_REP);
		assert(mSocket);

		// binding to server..
		assert(0 == zmq_bind(mSocket, mConnectionAddress.c_str()));
	}

	virtual ~Server() override 
	{ 
		// unbinding from server..
		assert(0 == zmq_unbind(mSocket, mConnectionAddress.c_str()));

		// close the socket
		assert(0 == zmq_close(mSocket));
	}

};

inline void server_exec(void* const context)
{
	Server s(context, CONNECTION_ADDRESS);
	string message;
	auto socket = s.getSocket();

	bool stop = false;
	while (!stop)
	{
		// waiting for a message..
		message = NMessageHelper::recvMessage(socket);
		//displayOnScreen("[Server] received message from client: " + message);

		string reply;
		if (message == REQ_MESSAGE_CLOSE)
		{
			stop = true;
			reply = RESP_MESSAGE_CLOSE;
		}
		else
		{
			reply = DEFAULT_RESP_MESSAGE;
		}

		// sending a response back..
		//displayOnScreen("[Server] sending message to client: " + reply);
		NMessageHelper::sendMessage(socket, reply);
	}
}