/******************************************************************************
* Copyright (C) 17/04/2017
*
* @file         main.cpp
* @project		ZeroMQ
* @author       Robert Badea
* @url			www.robertbadea.ro
******************************************************************************
* ZeroMQ (also spelled ØMQ, 0MQ or ZMQ) is a high-performance asynchronous 
* messaging library, aimed at use in distributed or concurrent applications.
* It provides a message queue, but unlike message-oriented middleware,
* a ZeroMQ system can run without a dedicated message broker.
*
* Links:   https://en.wikipedia.org/wiki/ZeroMQ
* Website: http://zeromq.org
* API:	   http://api.zeromq.org/master:_start
******************************************************************************/
#include <iostream>			// for cin.get
#include <thread>			// separate threads for client and server
#include "Client.h"
#include "Server.h"

int main() 
{
	CContextHolder context;

	std::thread thread_server(server_exec, context.getContext());
	std::thread thread_client(client_exec, context.getContext());

	thread_server.join();
	thread_client.join();

	std::cin.get();
	return 0;
}
