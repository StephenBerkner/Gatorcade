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
	//
	//DDRB |= 0xB0;
	//
	//PORTB &= ~0xB0;
	//
	

}

//after command sent delay to let command process
//might need to be extended
void AudioProcessingDelay(){
	_delay_ms(20);
	PORTB &= ~0xB0;

	DDRB &= ~0xB0;
}

void AudioOff(){
	DDRB |= 0xB0;
	PORTB &= ~0xB0;
	
	AudioProcessingDelay();
}

void PlayMenuSelectAudio(){
	
	DDRB |= 0xB0;
	PORTB &= ~0xB0;
	PORTB |= 0x10;
	
	AudioProcessingDelay();

}

void PlayWallBounceAudio(){
	DDRB |= 0xB0;
	PORTB &= ~0xB0;
	
	PORTB |= 0x20;
	
	AudioProcessingDelay();
}

void PlayPaddleBounceAudio(){
	DDRB |= 0xB0;
	PORTB &= ~0xB0;
	PORTB |= 0x30;
	
	AudioProcessingDelay();

}

void PlayGameOverAudio(){
	DDRB |= 0xB0;
	PORTB &= ~0xB0;
	PORTB |= 0x80;
	
	AudioProcessingDelay();

}



void PlaySuddenDeathAudio(){
	for (int i = 0; i < 3; i++){
		DDRB |= 0xB0;
		PORTB &= ~0xB0;
		PORTB |= 0x90;
	
		AudioProcessingDelay();
		
		_delay_ms(100);
	
	}
	
}


void PlayGamePointAudio(){
	DDRB |= 0xB0;
	PORTB &= ~0xB0;
	PORTB |= 0xA0;
	
	AudioProcessingDelay();

}



#endif /* AUDIO_H_ */