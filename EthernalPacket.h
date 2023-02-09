#ifndef ETHERNALPACKET_H
#define ETHERNALPACKET_H

#include <iostream>
#include "Packet.h"
using namespace std;

class EthernalPacket : public Packet
{
public:
    EthernalPacket(const string &packet);

    ~EthernalPacket();

    void write(ofstream &output_file);
};

#endif

