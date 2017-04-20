#include "pxt.h"

#define STANDARD_SPEED_VALUE 0.4f
#define SERVO_SPEED_VALUE 0.8f
#define STANDARD_LF_THRESHOLD 0.8f
#define STANDARD_DIRECTION_STRAIGHT 0.8f
#define STANDARD_DIRECTION_LEFT 0.22f
#define STANDARD_DIRECTION_RIGHT 0.78f

enum class CarType{
	Servo = 0,
	Standard = 1
};


//% color=75 weight=80
//% icon="\uf1b9"
namespace microbot{

	DigitalOut *_aa, *_ba;
	PwmOut *_ab, *_bb, *_dir;
	MicroBitPin *_mbp;
	AnalogIn *_lr, *_rr;

	bool running = false;
	int lh, rh, baseHeading;
	int lf = 0;

	void diet_coke(){
		while(true){
			if(!running) {
				//stop
				_aa->write(1);
				_ab->write(1.0f);
				_ba->write(1);
				_bb->write(1.0f);
				while(!running){
					uBit.sleep(100); //do nothing
				}
			}
			if(lf == 0){
				//non line following mode
				_aa->write(0);
				_ab->write(STANDARD_SPEED_VALUE);
				_ba->write(0);
				_bb->write(STANDARD_SPEED_VALUE);
			} else {
				if(_lr->read() > STANDARD_LF_THRESHOLD) {
					_aa->write(0);
					_ab->write(STANDARD_SPEED_VALUE);
					_ba->write(1);
					_bb->write(1.0f);
				} else if(_rr->read() > STANDARD_LF_THRESHOLD) {
					_aa->write(1);
					_ab->write(1.0f);
					_ba->write(0);
					_bb->write(STANDARD_SPEED_VALUE);
				}
			}
			
			uBit.sleep(100); //do nothing
		}
	}

	void diet_sprite(){
		while(true){
			if(!running) {
				//stop
				_ab->write(0.0f);
				_bb->write(0.0f);
				while(!running){
					uBit.sleep(100); //do nothing
				}
			}

			if(lf == 0){
				_ab->write(SERVO_SPEED_VALUE);
				_bb->write(SERVO_SPEED_VALUE);
			} else {
				if(_lr->read() > STANDARD_LF_THRESHOLD) {
					_ab->write(0.0f);
					_bb->write(0.5f);
				} else if(_rr->read() > STANDARD_LF_THRESHOLD) {
					_ab->write(0.5f);
					_bb->write(0.0f);
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
				_ab = new PwmOut(MICROBIT_PIN_P15);
				_bb = new PwmOut(MICROBIT_PIN_P16);
				running = false;
				create_fiber(diet_sprite);
			break;
			case CarType::Standard:
				_aa = new DigitalOut(MICROBIT_PIN_P13);
				_ab = new PwmOut(MICROBIT_PIN_P14);
				_ba = new DigitalOut(MICROBIT_PIN_P15);
				_bb = new PwmOut(MICROBIT_PIN_P16);
				
				//_dir = new PwmOut(MICROBIT_PIN_P12);
				_mbp = new MicroBitPin(MICROBIT_ID_IO_P12, MICROBIT_PIN_P12, PIN_CAPABILITY_ALL);

				_lr = new AnalogIn(MICROBIT_PIN_P0);
				_rr = new AnalogIn(MICROBIT_PIN_P1);

				_aa -> write(1);
				_ab -> write(1.0f);
				_ba -> write(1);
				_bb -> write(1.0f);
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