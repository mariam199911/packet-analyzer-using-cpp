#include "EthernalPacket.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
EthernalPacket::EthernalPacket(const string &packet) 
    :   Packet(packet)
{
}

EthernalPacket::~EthernalPacket()
{
}
 
void EthernalPacket::write(ofstream &output_file) {

    output_file << "CRC: " << CRC << endl;
    output_file << "Destination Address: " << destination_address << endl;
    output_file << "Source Address: " << source_address << endl;
    output_file << "Type: " << type << endl;
    output_file << "Data: " << data << endl;
    output_file << endl;
    output_file << "**************************************************************************************************************************************************************************************************************************************"<<endl;
    output_file << endl;

}