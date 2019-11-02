 void i2c_init(){

	DDRC |= (1<< PORTC0) | (1 << PORTC1);
    TWBR=0x02;    // Bit rate
    // SCL freq= F_CPU/(16+2(TWBR).4^TWPS)
TWCR |= (1<<TWEN);
    TWSR = 0x00;    // Setting prescalar bits to 1


}

void i2c_start(){

    // Clear TWI interrupt flag, Put start condition on SDA, Enable TWI
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
    while(!(TWCR & (1<<TWINT))); // Wait till start condition is transmitted
    //while((TWSR & 0xF8)!= 0x08); // Check for the acknowledgement


}

void i2c_stop(){

    // Clear TWI interrupt flag, Put stop condition on SDA, Enable TWI
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
    while(!(TWCR & (1<<TWSTO)));  // Wait till stop condition is transmitted

}

void i2c_write_address(uint8_t input){

    TWDR = input;    // Address and read instruction
    TWCR=(1<<TWINT)|(1<<TWEN);    // Clear TWI interrupt flag,Enable TWI
    while (!(TWCR & (1<<TWINT))); // Wait till complete TWDR byte received
    //while((TWSR & 0xF8)!= 0x18);  // Check for the acknoledgement

}

void i2c_read_address(uint8_t input){

    TWDR = input;    // Address and read instruction
    TWCR=(1<<TWINT)|(1<<TWEN);    // Clear TWI interrupt flag,Enable TWI
    while (!(TWCR & (1<<TWINT))); // Wait till complete TWDR byte received
//    while((TWSR & 0xF8)!= 0x40);  // Check for the acknoledgement

}
void i2c_write_data(uint8_t input){

TWDR = input;    // Address and read instruction
TWCR=(1<<TWINT)|(1<<TWEN);    // Clear TWI interrupt flag,Enable TWI
while (!(TWCR & (1<<TWINT))); // Wait till complete TWDR byte received
//while((TWSR & 0xF8)!= 0x28);  // Check for the acknoledgement

}
uint8_t i2c_read(int ack){

if(ack == 0){
    TWCR=(1<<TWINT)|(1<<TWEN);    // Clear TWI interrupt flag,Enable TWI
    while (!(TWCR & (1<<TWINT))); // Wait till complete TWDR byte transmitted
    while((TWSR & 0xF8) != 0x58); // Check for the acknoledgement
}else{
    TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);    // Clear TWI interrupt flag,Enable TWI
    while (!(TWCR & (1<<TWINT))); // Wait till complete TWDR byte transmitted
    //while((TWSR & 0xF8) != 0x50); // Check for the acknoledgement  
 
}
 return TWDR;
 
}


uint8_t ReadRegisterSingleByte(uint8_t deviceAddress, uint8_t registerAddress){
		uint8_t toReturn = 0x00;
		
		i2c_start();
		i2c_write_address(deviceAddress << 1);

		i2c_write_data(registerAddress);
		
		//i2c_stop();
		i2c_start();
				
		i2c_read_address((deviceAddress << 1) | 0x01);
		toReturn = i2c_read(0);
		i2c_stop();

		return toReturn;
}

uint16_t ReadRegisterMultipleBytes(uint8_t deviceAddress, uint8_t MSBAddress, uint8_t LSBAddress){
		uint16_t toReturn = 0x0000;
		
		//get MSB
		i2c_start();
		i2c_write_address(deviceAddress << 1);

		i2c_write_data(MSBAddress);
		
		i2c_start();
		
		i2c_read_address((deviceAddress << 1) | 0x01);
		toReturn = i2c_read(0) << 8;
		i2c_stop();
		
		//get LSB
		i2c_start();
		i2c_write_address(deviceAddress << 1);

		i2c_write_data(LSBAddress);
		
		i2c_start();
		
		i2c_read_address((deviceAddress << 1) | 0x01);
		toReturn |= i2c_read(0);
		i2c_stop();
		
		return toReturn;
	
	
}

void WriteRegisterSingleByte(uint8_t deviceAddress, uint8_t registerAddress, uint8_t data){
	
	i2c_start();
	i2c_write_address(deviceAddress << 1);

	i2c_write_address(registerAddress);
	
	i2c_write_data(data);
	
	i2c_stop();

	
}









