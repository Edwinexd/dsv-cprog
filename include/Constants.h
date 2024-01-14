#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
typedef unsigned long long wlong;
namespace constants
{
    //gResPath-contains the relative path to your resources.
    //if '/resources/' is used, use the following:
	const std::string gResPath = "../../resources/";
    
    //if '/build/debug/resources/' is used, use the following:

    // const std::string gResPath = "./resources/";
    const unsigned int FPS = 80;
}

#endif