#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "EthernalPacket.h"
#include "ECPRIFrame.h"

using namespace std;



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
  int packet_numer(0);
  const int type_start_digit = 40;
  const int type_digits_number = 4;
  while (getline(input_file, line)) {
    string type = line.substr(type_start_digit, type_digits_number);
    // EthernetPacket *packet;
    Packet *packet;
    if (type == "AEFE") {
      // If the packet is an e-CPRI frame, parse the Common Header and Real-Time Control Data
      packet = new ECPRIFrame(line);

      output_file << "Packet # " <<packet_numer<<":"<< endl;
      output_file << line << endl;
      packet->write(output_file);

    } else {
      packet = new EthernalPacket(line);

      output_file << "Packet # " <<packet_numer<<":"<< endl;
      output_file << line << endl;
      packet->write(output_file);

    }

    delete packet;

    packet_numer++;
  }


  return 0;
}