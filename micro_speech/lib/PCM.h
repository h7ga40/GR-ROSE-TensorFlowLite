#ifndef _PCM_H_INCLUDED
#define _PCM_H_INCLUDED

#include <Arduino.h>
#define DEFAULT_PCM_BUFFER_SIZE 512

class PCMClass
{
public:
	PCMClass(int inputPin, int dmaCh);
	virtual ~PCMClass();

	int begin(int channels, long sampleRate);
	void end();

	int read(void* buffer, size_t size);

	void onReceive(void(*)(void));

	void setGain(int gain);

	// private:
	void IrqHandler();

private:
	int _inputPin;
	int _dmaCh;
	volatile struct st_dmac1 *_DMACm;

	int _gain;
	int _channels;

	void (*_onReceive)(void);
};

extern PCMClass PCM;

#endif
