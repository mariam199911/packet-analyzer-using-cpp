#include "ECPRIFrame.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

const int protocol_version_start_digit = 44;
const int protocol_version_digits_number = 1;
const int Concatenation_Indicator_start_digit = 45;
const int Concatenation_Indicator_digits_number = 1;
const int message_type_start_digit = 46; 
const int message_type_digits_number = 2;
const int payload_size_start_digit = 48;
const int payload_size_digits_number = 4;
const int RTC_ID_start_digit = 52;
const int RTC_ID_digits_number = 4;
const int Sequence_ID_start_digit = 56;
const int Sequence_ID_digits_number = 4;

ECPRIFrame::ECPRIFrame(const string &packet) 
    :   Packet(packet)
{
    common_header.protocol_version = packet.substr(protocol_version_start_digit, protocol_version_digits_number);
    common_header.Concatenation_Indicator = packet.substr(Concatenation_Indicator_start_digit, Concatenation_Indicator_digits_number);
    common_header.message_type = packet.substr(message_type_start_digit, message_type_digits_number);
    common_header.payload_size = packet.substr(payload_size_start_digit, payload_size_digits_number);
    rt_ctrl_data.RTC_ID = packet.substr(RTC_ID_start_digit, RTC_ID_digits_number);
    rt_ctrl_data.Sequence_ID = packet.substr(Sequence_ID_start_digit, Sequence_ID_digits_number);
}

ECPRIFrame::~ECPRIFrame()
{
}
 
void ECPRIFrame::write(ofstream &output_file) {

      output_file << "CRC: " << CRC << endl;
      output_file <<"Concatenation Indicator: "<< common_header.Concatenation_Indicator <<endl;
      output_file << "Destination Address: " << destination_address << endl;
      output_file <<"Message Type: "<< common_header.message_type <<endl;
      output_file <<"Payload Size: "<< common_header.payload_size <<endl;
      output_file <<"Protocol Version: "<< common_header.protocol_version <<endl;
      output_file <<"RTC ID: "<< rt_ctrl_data.RTC_ID <<endl;
      output_file <<"Sequence ID: "<< rt_ctrl_data.Sequence_ID <<endl;
      output_file << "Source Address: " << source_address << endl;
      output_file << "Type: " << type << endl;
      output_file << endl;
      output_file << "**************************************************************************************************************************************************************************************************************************************"<<endl;
      output_file << endl;

}