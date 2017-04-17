#pragma once
/******************************************************************************
* Copyright (C) 17/04/2017
*
* @file         Constants.h
* @project		ZeroMQ
* @author       Robert Badea
* @url			www.robertbadea.ro
******************************************************************************
* File containing constants such the connection address and the messages that are sent.
*****************************************************************************/
//--------------------------------------------------------------------
//                              Includes
//--------------------------------------------------------------------
#include <string>

static std::string CONNECTION_ADDRESS = "inproc://IPC-Connection";

static std::string REQ_MESSAGE_SINGLE_1 = "Hello!";
static std::string REQ_MESSAGE_MULTI_1 = "Hello again!";
static std::string REQ_MESSAGE_MULTI_2 = "This is a multi part message!";
static std::string REQ_MESSAGE_CLOSE = "Bye!";

static std::string DEFAULT_RESP_MESSAGE = "OK!";
static std::string RESP_MESSAGE_CLOSE = "Received goodbye message, closing!";




