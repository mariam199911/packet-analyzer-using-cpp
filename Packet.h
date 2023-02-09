#ifndef PACKET_H
#define PACKET_H

#include <iostream>
using namespace std;

class Packet
{
public:
    Packet(const string &packet);
    ~Packet();

    virtual void write(ofstream &output_file) = 0;

protected:
    string destination_address;
    string source_address;
    string type;
    string data;
    string CRC; // FCS
};




#endif