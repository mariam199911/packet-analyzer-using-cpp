#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;


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
      destination_address = packet.substr(16, 12);
      source_address = packet.substr(28, 12);
      type = packet.substr(40, 4);
      // 52 came from the totao length of the packet - the length of the CRC - the length of the destination address - the length of the source address - the length of the type  
      data = packet.substr(44, packet.length() - 52);
      CRC =  packet.substr(packet.length() - 8);
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


int main() {
  // Open input file
  ifstream input_file("input_packets");
  // Open output file
  ofstream output_file("output");

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
  // vector<EthernetPacket> packets;
  while (getline(input_file, line)) {
    EthernetPacket packet;
    packet.parse_packet(line, packet);
    // Write parsed packets with their fields in output file
    output_file << "Packet # " <<packet_numer<<":"<< endl;
    output_file << line << endl;
    output_file << "CRC: " << packet.get_CRC() << endl;
    output_file << "Destination Address: " << packet.get_destination_address() << endl;
    output_file << "Source Address: " << packet.get_source_address() << endl;
    output_file << "Type: " << packet.get_type() << endl;
    output_file << "Data: " << packet.get_data() << endl;
    output_file << endl;
    output_file << "**************************************************************************************************************************************************************************************************************************************"<<endl;
    output_file << endl;
    // packets.push_back(packet);
    packet_numer++;
  }


  return 0;
}
