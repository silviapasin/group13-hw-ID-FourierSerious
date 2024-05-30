#include <Bela.h>
#include <stdlib.h>
#include <libraries/OscSender/OscSender.h>

OscSender oscSender;

int remotePort = 7563;
const char* remoteIp = "192.168.6.1";
//const char* remoteIp = "192.168.7.1"; //uncomment this for MAC

float AnalogX, AnalogY;
int Button;
int gSampleCount = 0;
int gAudioFramesPerAnalogFrame = 0;

bool setup(BelaContext *context, void *userData)
{
	if(!context->analogInChannels)
	{
		fprintf(stderr, "Error: This example requires analog inputs to be enabled");
		return false;
	}
	if(context->analogSampleRate > context->audioSampleRate)
	{
		fprintf(stderr, "Error: for this project the sampling rate of the analog inputs has to be <= the audio sample rate\n");
		return false;
	}
	if(context->analogFrames)
		gAudioFramesPerAnalogFrame = context->audioFrames / context->analogFrames;
		
	oscSender.setup(remotePort, remoteIp);
	return true;
}

void render(BelaContext *context, void *userData)
{
	
	for(unsigned int n = 0; n < context->audioFrames; n++) {
		
		if(gAudioFramesPerAnalogFrame && !(n % gAudioFramesPerAnalogFrame)) {
			AnalogX = analogRead(context, n, 0);
			AnalogY = analogRead(context, n, 1);
			Button = digitalRead(context, 0, 1);
	}

	if(!n%2){
		if(gSampleCount >= 44100) {
		gSampleCount = 0;
		}
	oscSender.newMessage("/joystick/x").add((float) AnalogX).send();
	oscSender.newMessage("/joystick/y").add((float) AnalogY).send();
	oscSender.newMessage("/button").add((int) Button).send();
	}
	gSampleCount++;
	}	
}

void cleanup(BelaContext *context, void *userData)
{

}