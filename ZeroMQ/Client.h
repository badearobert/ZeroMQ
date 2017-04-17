#pragma once
/******************************************************************************
* Copyright (C) 17/04/2017
*
* @file         Client.h
* @project		ZeroMQ
* @author       Robert Badea
* @url			www.robertbadea.ro
******************************************************************************
* Client implementation of IBase
* The client connect to the inproc server as ZMQ_REQ (client).
* It will send multiple messages to the server until sending the goodbye msg.
*****************************************************************************/
//--------------------------------------------------------------------
//                              Includes
//--------------------------------------------------------------------
#include "IBase.h"

class Client : public IBase
{
public:
	Client(void* const context, std::string connectionAddress)
		: IBase(context, connectionAddress)
	{
		// creating the socket..
		mSocket = zmq_socket(mContext, ZMQ_REQ);
		assert(mSocket);
		
		// connecting to server..
		assert(0 == zmq_connect(mSocket, mConnectionAddress.c_str()));
	}

	virtual ~Client() override 
	{
		// disconnecting from server..
		assert(0 == zmq_disconnect(mSocket, mConnectionAddress.c_str()));

		// close the socket
		assert(0 == zmq_close(mSocket));
	} 
};

inline void client_exec(void* const context)
{
	Client c(context, CONNECTION_ADDRESS);
	auto socket = c.getSocket();

	displayOnScreen("-------------------------------------------");
	displayOnScreen("-\t Single message \t-\n");

	NMessageHelper::sendMessage(socket, REQ_MESSAGE_SINGLE_1);
	NMessageHelper::recvMessage(socket);

	displayOnScreen("-------------------------------------------");
	displayOnScreen("-\t Multi message \t-\n");

	NMessageHelper::sendMessage(socket, REQ_MESSAGE_MULTI_1, ZMQ_SNDMORE);
	NMessageHelper::sendMessage(socket, REQ_MESSAGE_MULTI_2);
	NMessageHelper::recvMessage(socket);

	displayOnScreen("-------------------------------------------");
	displayOnScreen("-\t Good-bye message \t-\n");
	NMessageHelper::sendMessage(socket, REQ_MESSAGE_CLOSE);
	NMessageHelper::recvMessage(socket);
}