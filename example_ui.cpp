#include "daisy_patch.h"
#include "daisysp.h"

using namespace daisy;
using namespace daisysp;

DaisyPatch hw;

void AudioCallback(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		out[0][i] = in[0][i];
		out[1][i] = in[1][i];
		out[2][i] = in[2][i];
		out[3][i] = in[3][i];
	}
}

int main(void)
{
	hw.Init();
	hw.SetAudioBlockSize(4); // number of samples handled per callback
	hw.SetAudioSampleRate(SaiHandle::Config::SampleRate::SAI_48KHZ);
	hw.StartAdc();
	hw.StartAudio(AudioCallback);
	while(1) {
		hw.ProcessAllControls();
		
		hw.display.SetCursor(0, 0);
		
		if (hw.encoder.Increment() == -1) {
			hw.display.WriteString("counter-clockwise", Font_7x10, true);
		} else if (hw.encoder.Increment() == 1) {
			hw.display.WriteString("clockwise        ", Font_7x10, true);
		}

		if (hw.encoder.RisingEdge()) {
			hw.display.SetCursor(0, 11);
			hw.display.WriteString("Button pressed", Font_7x10, true);
		}

		hw.display.Update();

		hw.DelayMs(1);
	}
}
