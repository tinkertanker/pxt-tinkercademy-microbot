#include "pxt.h"

#define STANDARD_SPEED_VALUE 512
#define SERVO_SPEED_VALUE 0.8f
#define STANDARD_LF_THRESHOLD 0.7f

enum class CarType{
	Servo = 0,
	Standard = 1
};


//% color=75 weight=80
//% icon="\uf1b9"
namespace microbot{

	DigitalOut *_aa, *_ba;
	MicroBitPin *_mbp, *_ab, *_bb;
	AnalogIn *_lr, *_rr;

	bool running = false;
	int lh, rh, baseHeading;
	int lf = 0;

	void diet_coke(){
		while(true){
			if(!running) {
				//stop
				_aa->write(1);
				_ab->setAnalogValue(1024);
				_ba->write(1);
				_bb->setAnalogValue(1024);
				while(!running){
					uBit.sleep(100); //do nothing
				}
			}
			if(lf == 0){
				//non line following mode
				_aa->write(0);
				_ab->setAnalogValue(STANDARD_SPEED_VALUE);
				_ba->write(0);
				_bb->setAnalogValue(STANDARD_SPEED_VALUE);
			} else {
				if(_lr->read() > STANDARD_LF_THRESHOLD) {
					_aa->write(0);
					_ab->setAnalogValue(STANDARD_SPEED_VALUE);
					_ba->write(1);
					_bb->setAnalogValue(1024);
				} else if(_rr->read() > STANDARD_LF_THRESHOLD) {
					_aa->write(1);
					_ab->setAnalogValue(1024);
					_ba->write(0);
					_bb->setAnalogValue(STANDARD_SPEED_VALUE);
				} else {
					_aa->write(0);
					_ab->setAnalogValue(STANDARD_SPEED_VALUE);
					_ba->write(0);
					_bb->setAnalogValue(STANDARD_SPEED_VALUE);
				}
			}
			
			uBit.sleep(100); //do nothing
		}
	}

	void diet_sprite(){
		while(true){
			if(!running) {
				//stop
				_ab->setAnalogValue(0);
				_bb->setAnalogValue(0);
				while(!running){
					uBit.sleep(100); //do nothing
				}
			}

			if(lf == 0){
				_ab->setServoValue(SERVO_SPEED_VALUE);
				_bb->setServoValue(SERVO_SPEED_VALUE);
			} else {
				if(_lr->read() > STANDARD_LF_THRESHOLD) {
					_ab->setServoValue(88);
					_bb->setServoValue(0);
				} else if(_rr->read() > STANDARD_LF_THRESHOLD) {
					_ab->setServoValue(180);
					_bb->setServoValue(85);
				} else {
					_ab->setServoValue(95);
					_bb->setServoValue(75);
				}
			}
			uBit.sleep(100); //do nothing
			
		}
	}

	/**
	* initializes pinout for the car.
	*/
	//% blockId=car_init
	//% block="initialise car type %car"
	void init(CarType car){
		switch (car){
			case CarType::Servo:
				_ab = new MicroBitPin(MICROBIT_ID_IO_P15, MICROBIT_PIN_P15, PIN_CAPABILITY_ALL);
				_bb = new MicroBitPin(MICROBIT_ID_IO_P16, MICROBIT_PIN_P16, PIN_CAPABILITY_ALL);
				running = false;
				create_fiber(diet_sprite);
			break;
			case CarType::Standard:
				_aa = new DigitalOut(MICROBIT_PIN_P13);
				_ab = new MicroBitPin(MICROBIT_ID_IO_P14, MICROBIT_PIN_P14, PIN_CAPABILITY_ALL);
				_ba = new DigitalOut(MICROBIT_PIN_P15);
				_bb = new MicroBitPin(MICROBIT_ID_IO_P16, MICROBIT_PIN_P16, PIN_CAPABILITY_ALL);
				
				_mbp = new MicroBitPin(MICROBIT_ID_IO_P12, MICROBIT_PIN_P12, PIN_CAPABILITY_ALL);

				_lr = new AnalogIn(MICROBIT_PIN_P0);
				_rr = new AnalogIn(MICROBIT_PIN_P1);

				_aa -> write(1);
				_ab -> setAnalogValue(1024);
				_ba -> write(1);
				_bb -> setAnalogValue(1024);
				running = false;
				create_fiber(diet_coke);
			break;
		}
		
	}

	/**
	* turns left.
	*/
	//% blockId=car_left
	//% block="turn left"
	void turnLeft(){
		if(running) return;
		//_dir->write(STANDARD_DIRECTION_LEFT);
		_mbp->setServoValue(40);
		running = true;
		uBit.sleep(1000);
		//_dir->write(STANDARD_DIRECTION_STRAIGHT);
		_mbp->setServoValue(87);
		running = false;
	}

	/**
	* turns right.
	*/
	//% blockId=car_right
	//% block="turn right"
	void turnRight(){
		if(running) return;
		//_dir->write(STANDARD_DIRECTION_RIGHT);
		_mbp->setServoValue(140);
		running = true;
		uBit.sleep(1000);
		//_dir->write(STANDARD_DIRECTION_STRAIGHT);
		_mbp->setServoValue(87);
		running = false;
	}

	/**
	* stops the car.
	*/
	//% blockId=car_stop
	//% block="stop"
	void stop(){
		printf("call to stop\r\n");
		running = false;
	}

	/**
	* sets the car to start following a line.
	*/
	//% blockId=car_linefollow
	//% block="follow line"
	void followLine(){
		lf = 1;
		//_dir->write(STANDARD_DIRECTION_STRAIGHT);
		_mbp->setServoValue(87);
		running = true;
	}

	/**
	* moves the car forward.
	*/
	//% blockId=car_move
	//% block="go forward"
	void moveUp(){
		printf("call to start\r\n");
		lf = 0;
		//_dir->write(STANDARD_DIRECTION_STRAIGHT); //need to map this to correct angle
		_mbp->setServoValue(87);
		running = true;
	}


}