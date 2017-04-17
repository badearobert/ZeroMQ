#pragma once
/******************************************************************************
* Copyright (C) 17/04/2017
*
* @file         Message.h
* @project		ZeroMQ
* @author       Robert Badea
* @url			www.robertbadea.ro
******************************************************************************
* This file include the zmq library and add a wrapper over those calls.
*****************************************************************************/
//--------------------------------------------------------------------
//                              Includes
//--------------------------------------------------------------------
#include <zmq.h>
#include <cassert>
#include <string>
#include "Helpers.h"

using std::string;

/**
* RAII zmq message container
**/
struct Message
{
	Message()
	{
		assert(0 == zmq_msg_init(&_msg));
	}

	~Message()
	{
		// de-init of the message
		assert(0 == zmq_msg_close(&_msg));
	}

	void setMessage(const std::string data)
	{
		int dataLen = data.length() + 1;
		zmq_msg_init_size(&_msg, dataLen);
		memcpy(zmq_msg_data(&_msg), data.c_str(), dataLen);
	}

	/**
	* Sends the message
	* Call setMessage function before using this function
	*
	* @returns the number of bytes sent
	**/
	int sendMessage(void* const socket, int flags = 0)
	{
		// sending the message
		return zmq_msg_send(&_msg, socket, flags);
	}

	/**
	* Receives the message - blocking call if flags = 0
	* @returns the message
	**/
	string recvMessage(void* const socket, int flags = 0)
	{
		string result;
	
		int more;
		size_t more_size = sizeof(more);
		do {
			auto rc = zmq_msg_recv(&_msg, socket, flags);
			assert(rc != -1);
			/* Determine if more message parts are to follow */
			result += string((const char*)zmq_msg_data(&_msg));
			rc = zmq_getsockopt(socket, ZMQ_RCVMORE, &more, &more_size);
			assert(rc == 0);
		} while (more);
		return result;
	}
	zmq_msg_t _msg;
};

//-----------------------------------------------------------------------------

namespace NMessageHelper
{
	inline void sendMessage(void* const socket, const std::string data, int flags = 0)
	{
		assert(socket);
		// creating the message..
		Message msg;

		// setting the data..
		msg.setMessage(data);

		// sending the message..
		int bytesSent = msg.sendMessage(socket, flags);

		// checking if the message was successfully sent..
		auto dataLen = data.length() + 1;
		assert(bytesSent == dataLen);

		NHelpers::displayOnScreen("Sending message: " + data);
	}

	inline string recvMessage(void* const socket, int flags = 0)
	{
		assert(socket);

		// creating the message..
		Message msg;

		// blocking call until we receive a message
		string message = msg.recvMessage(socket, flags);

		NHelpers::displayOnScreen("Receiving message: " + message);
		return message;
	}
} // NMessageHelper

//-----------------------------------------------------------------------------

/**
* RAII context holder
**/
class CContextHolder
{
public:
	CContextHolder()
	{
		mContext = zmq_ctx_new();
	}
	~CContextHolder()
	{
		zmq_ctx_destroy(mContext);
	}

	void* const getContext() const { return mContext; }
private:
	void* mContext;
};