/**
    @file ConnectionRemote.cpp
    @author Lime Microsystems
    @brief Implementation of EVB7 connection of serial COM port.
*/

#include "ConnectionRemote.h"
#include <fstream>
#include <iostream>

using namespace std;
using namespace lime;

static const int comBaudrate = 9600;

//! make a static-initialized entry in the registry
void __loadConnectionRemoteEntry(void) //TODO fixme replace with LoadLibrary/dlopen
{
static ConnectionRemoteEntry EVB7COMEntry;
}

ConnectionRemoteEntry::ConnectionRemoteEntry(void):
    ConnectionRegistryEntry("EVB7COM")
{
    return;
}

std::vector<ConnectionHandle> ConnectionRemoteEntry::enumerate(const ConnectionHandle &hint)
{
    std::vector<ConnectionHandle> result;

        ConnectionHandle handle;
        handle.media = "TCP";
        handle.name = "Remote";
        handle.addr = "127.0.0.1:5000";
        if(hint.addr.length() == 0 || hint.addr == handle.addr)
            result.push_back(handle);

    return result;
}

IConnection *ConnectionRemoteEntry::make(const ConnectionHandle &handle)
{
    return new ConnectionRemote(handle.addr.c_str());
}