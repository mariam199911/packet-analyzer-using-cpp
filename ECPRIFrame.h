#ifndef ECPRIFRAME_H
#define ECPRIFRAME_H

#include <iostream>
#include "Packet.h"
using namespace std;

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

class ECPRIFrame : public Packet
{
  
private:
  CommonHeader common_header;
  RealTimeControlData rt_ctrl_data;

public:
    ECPRIFrame(const string &packet);

    ~ECPRIFrame();

    void write (ofstream &output_file);
};

#endif