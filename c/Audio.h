/*
 * Audio.h
 *
 * Created: 11/21/2019 11:57:22 PM
 *  Author: sberk
 */ 


#ifndef AUDIO_H_
#define AUDIO_H_

void AudioInit(){
	
	//using PORTB 4,5, and 7
	//4 is MSB 7 is LSB
	
	DDRB |= 0xB0;
	
	PORTB &= ~0xB0;

}

//after command sent delay to let command process
//might need to be extended
void AudioProcessingDelay(){
	_delay_us(1);
	PORTB &= ~0xB0;

}

void AudioOff(){
	PORTB &= ~0xB0;
}

void PlayMenuSelectAudio(){
	PORTB &= ~0xB0;
	PORTB |= 0x10;
	
	AudioProcessingDelay();

}

void PlayWallBounceAudio(){
	PORTB &= ~0xB0;
	PORTB |= 0x20;
	
	AudioProcessingDelay();
}

void PlayPaddleBounceAudio(){
	PORTB &= ~0xB0;
	PORTB |= 0x30;
	
	AudioProcessingDelay();

}

void PlayGameOverAudio(){
	PORTB &= ~0xB0;
	PORTB &= 0x80;
	
	AudioProcessingDelay();

}




#endif /* AUDIO_H_ */