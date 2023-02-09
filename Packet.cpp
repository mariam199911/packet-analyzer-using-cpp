#include <iostream>
#include "Packet.h"
using namespace std;


const int destination_address_start_digit = 16;
const int destination_address_digits_number = 12;

const int source_address_start_digit = 28;
const int source_address_digits_number = 12;

const int type_start_digit = 40;
const int type_digits_number = 4;

const int data_start_digit = 44;


const int CRC_digits_number = 8;
Packet::Packet(const string &packet)
    :   destination_address{packet.substr(destination_address_start_digit, destination_address_digits_number)},
        source_address{packet.substr(source_address_start_digit, source_address_digits_number)},
        type{packet.substr(type_start_digit, type_digits_number)},
        data(packet.substr(data_start_digit, packet.length() - data_start_digit - CRC_digits_number)),
        CRC(packet.substr(packet.length() - CRC_digits_number))
{}

Packet::~Packet()
{
}