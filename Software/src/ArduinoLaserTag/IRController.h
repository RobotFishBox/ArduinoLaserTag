/*
 * IRremoteInt now named IRControllerInt to avoid conflicts in names
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * For details, see http://arcfn.com/2009/08/multi-protocol-infrared-remote-library.htm http://arcfn.com
 * Modified by Anderson Li <http://therobotfish.com> to streamline arduino to arduino ir communication.
 * 
 * Interrupt code based on NECIRrcv by Joe Knapp
 * http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1210243556
 * Also influenced by http://zovirl.com/2008/11/12/building-a-universal-remote-with-an-arduino/
 *
 */

#ifndef IRController_h
#define IRController_h

// Results returned from the decoder
class decode_results {
public:
  unsigned long value; // Decoded value
  int bits; // Number of bits in decoded value
  volatile unsigned int *rawbuf; // Raw intervals in .5 us ticks
  int rawlen; // Number of records in rawbuf.
};

// main class for receiving IR
class IRrecv
{
public:
  IRrecv(int recvpin);
  int decode(decode_results *results);
  void enableIRIn();
  void resume();
private:
  // These are called by decode
  long decodeIR(decode_results *results);
};

class IRsend
{
public:
  IRsend();
  void sendIR(unsigned long data, int nbits);
  void enableIROut(int khz);
  void mark(int usec);
  void space(int usec);
};

// Some useful constants

#define USECPERTICK 50  // microseconds per clock interrupt tick
#define RAWBUF 100 // Length of raw duration buffer

// Marks tend to be 100us too long, and spaces 100us too short
// when received due to sensor lag.
#define MARK_EXCESS 100

#endif
