#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Define the start and end digits of the fields in the Ethernet packet
const int destination_address_start_digit = 16;
const int destination_address_digits_number = 12;
const int source_address_start_digit = 28;
const int source_address_digits_number = 12;
const int type_start_digit = 40;
const int type_digits_number = 4;
const int CRC_digits_number = 8;
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



// Define a struct to store the Common Header information
struct CommonHeader
{
  string protocol_version;
  string Concatenation_Indicator;
  string message_type;
  string payload_size;
  
};

// Define a struct to store the Real-Time Control Data information
struct RealTimeControlData
{
  string RTC_ID;
  string Sequence_ID;
};

class EthernetPacket {
  private:
    string destination_address;
    string source_address;
    string type;
    string data;
    string CRC;

  public:
    //Function to parse an Ethernet packet into its own fields
    virtual void parse_packet(const string &packet, EthernetPacket &eth_packet) {
      destination_address = packet.substr(destination_address_start_digit, destination_address_digits_number);
      source_address = packet.substr(source_address_start_digit, source_address_digits_number);
      type = packet.substr(type_start_digit, type_digits_number);
      // 52 came from the totao length of the packet - the length of the CRC - the length of the destination address - the length of the source address - the length of the type  
      // data = packet.substr(44, packet.length() - 52);
      CRC =  packet.substr(packet.length() - CRC_digits_number);
    }

    string get_destination_address() {
      return destination_address;
    }
    string get_source_address() {
      return source_address;
    }
    string get_type() {
      return type;
    }
    string get_data() {
      return data;
    }
    string get_CRC() {
      return CRC;
    }

};

class ECPRIFrame : public EthernetPacket {
  
private:
  CommonHeader common_header;
  RealTimeControlData rt_ctrl_data;

public:
  // Function to parse an e-CPRI frame into its own fields
  void parse_packet_new(const string &packet, EthernetPacket &eth_packet){
    EthernetPacket::parse_packet(packet, eth_packet);
    common_header.protocol_version = packet.substr(protocol_version_start_digit, protocol_version_digits_number);
    common_header.Concatenation_Indicator = packet.substr(Concatenation_Indicator_start_digit, Concatenation_Indicator_digits_number);
    common_header.message_type = packet.substr(message_type_start_digit, message_type_digits_number);
    common_header.payload_size = packet.substr(payload_size_start_digit, payload_size_digits_number);
    rt_ctrl_data.RTC_ID = packet.substr(RTC_ID_start_digit, RTC_ID_digits_number);
    rt_ctrl_data.Sequence_ID = packet.substr(Sequence_ID_start_digit, Sequence_ID_digits_number);
  }
  CommonHeader get_common_header() {
    return common_header;
  }
  RealTimeControlData get_rt_ctrl_data() {
    return rt_ctrl_data;
  }


};

int main() {
  // Open input file
  ifstream input_file("input_packets");
  // Open output file
  ofstream output_file("output.txt");

  //check if the file is open
   if (!input_file.is_open()) {
    std::cerr << "Unable to open input file" << std::endl;
    return 1;
  }

  if (!output_file.is_open()) {
    std::cerr << "Unable to open output file" << std::endl;
    return 1;
  }
  // Read file into packets
  string line;
  int packet_numer = 0;
  while (getline(input_file, line)) {
    string type = line.substr(40, 4);
    // EthernetPacket *packet;
    if (type == "AEFE") {
      // If the packet is an e-CPRI frame, parse the Common Header and Real-Time Control Data
      ECPRIFrame packet;
      packet.parse_packet_new(line,packet);
      output_file << "Packet # " <<packet_numer<<":"<< endl;
      output_file << line << endl;
      output_file << "CRC: " << packet.get_CRC() << endl;
      output_file <<"Concatenation Indicator: "<<packet.get_common_header().Concatenation_Indicator <<endl;
      output_file << "Destination Address: " << packet.get_destination_address() << endl;
      output_file <<"Message Type: "<<packet.get_common_header().message_type <<endl;
      output_file <<"Payload Size: "<<packet.get_common_header().payload_size <<endl;
      output_file <<"Protocol Version: "<< packet.get_common_header().protocol_version<<endl;
      output_file <<"RTC ID: "<<packet.get_rt_ctrl_data().RTC_ID <<endl;
      output_file <<"Sequence ID: "<<packet.get_rt_ctrl_data().Sequence_ID <<endl;
      output_file << "Source Address: " << packet.get_source_address() << endl;
      output_file << "Type: " << packet.get_type() << endl;
      output_file << endl;
      output_file << "**************************************************************************************************************************************************************************************************************************************"<<endl;
      output_file << endl;
    } else {
      EthernetPacket packet;
      packet.parse_packet(line, packet);
      output_file << "Packet # " <<packet_numer<<":"<< endl;
      output_file << line << endl;
      output_file << "CRC: " << packet.get_CRC() << endl;
      output_file << "Destination Address: " << packet.get_destination_address() << endl;
      output_file << "Source Address: " << packet.get_source_address() << endl;
      output_file << "Type: " << packet.get_type() << endl;
      output_file << endl;
      output_file << "**************************************************************************************************************************************************************************************************************************************"<<endl;
      output_file << endl;
    }
    packet_numer++;
  }


  return 0;
}
