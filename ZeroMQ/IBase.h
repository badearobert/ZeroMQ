#pragma once
/******************************************************************************
* Copyright (C) 17/04/2017
*
* @file         IBase.h
* @project		ZeroMQ
* @author       Robert Badea
* @url			www.robertbadea.ro
******************************************************************************
* Interface to be used for clients and servers.
* Each derived class should init the socket as client / server. (mSocket)
*****************************************************************************/
//--------------------------------------------------------------------
//                              Includes
//--------------------------------------------------------------------
#include "Helpers.h"
#include "Constants.h"
#include "Message.h"

using namespace NHelpers;

class IBase
{
public:
	/**
	* Creates the object
	**/
	IBase(void* const context, std::string connectionAddress)
		: mContext(context)
		, mConnectionAddress(connectionAddress)
	{ 
		assert(context);
	}

	/**
	* Destroys the object
	**/
	virtual ~IBase() { } ;

	void* const getContext() const { return mContext; }

	void* const getSocket() { return mSocket; }

protected:

	/**
	* The context of zmq
	**/
	void* const mContext;

	/**
	* The connection address
	**/
	std::string mConnectionAddress;

	/**
	* The socket to bind
	**/
	void* mSocket;
};
