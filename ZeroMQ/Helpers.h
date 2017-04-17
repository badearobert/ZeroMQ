#pragma once
/******************************************************************************
* Copyright (C) 17/04/2017
*
* @file         Helpers.h
* @project		ZeroMQ
* @author       Robert Badea
* @url			www.robertbadea.ro
******************************************************************************
* Header file containing functions that are used in other files as helper functions.
*****************************************************************************/
//--------------------------------------------------------------------
//                              Includes
//--------------------------------------------------------------------
#include <iostream>
#include <string>
#include <mutex>

static std::mutex _mx;

namespace NHelpers
{
	inline void displayOnScreen(std::string message)
	{
		std::lock_guard<std::mutex> lock(_mx);
		std::cout << message << std::endl;
	}
}