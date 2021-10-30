#pragma once
#include <Arduino.h>

class SevSeg {
public:
	SevSeg(int DS = 10, int ST_CP = 11, int SH_CP = 12, bool isCommonAnode = false);

	byte sendByte(byte inputByte = B00000000);
	byte sendSymbol(int symbolNumber = 1);

	byte symbols[30] = {
		B11111111,    // all on
		B00000000,    // all off
		B01111110,    // 0
		B00110000,    // 1
		B01101101,    // 2
		B01111001,    // 3
		B00110011,    // 4
		B01011011,    // 5
		B01011111,    // 6
		B01110000,    // 7
		B01111111,    // 8
		B01111011,    // 9
		B01110111,    // A
		B00011111,    // B
		B01001110,    // C
		B00111101,    // D
		B01001111,    // E
		B01000111,    // F
		B00110111,    // H
		B00010000,    // I
		B00111100,    // J
		B00011110,    // L
		B00010101,    // N
		B00011101,    // O
		B01100111,    // P
		B00000101,    // R
		B01011011,    // S
		B00001111,    // T
		B00011100,    // U
		B00111011     // Y
	};

private:
	int _data, _latch, _clock = 0;
	bool _isCommonAnode = false;
	byte _lastByte = B00000000;

SevSeg::SevSeg(int DS = 10, int ST_CP = 11, int SH_CP = 12, bool isCommonAnode = false) {
	_data = DS;
	_latch = ST_CP;
	_clock = SH_CP;
	pinMode(_data, OUTPUT);
	pinMode(_latch, OUTPUT);
	pinMode(_clock, OUTPUT);
	digitalWrite(_latch, HIGH);
	_isCommonAnode = isCommonAnode;
	sendByte();
}

byte SevSeg::sendByte(byte inputByte = B00000000) {
	if(_isCommonAnode) inputByte = ~inputByte;
	digitalWrite(_latch, LOW);
	shiftOut(_data, _clock, LSBFIRST, inputByte);
	digitalWrite(_latch, HIGH);
	_lastByte = inputByte;
	return inputByte;
}

byte SevSeg::sendSymbol(int symbolNumber = 1) {
	_lastByte = symbols[symbolNumber - 1];
	sendByte(_lastByte);
	return _lastByte;
}