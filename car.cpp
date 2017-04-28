#include "pxt.h"


enum class CarType{
	Servo = 0,
	Standard = 1
};

enum class CalibrationParameters {
	StandardSpeedValue = 0,
	StandardForwardAngle = 1,
	StandardTurnAngle = 2,
	ServoSpeed = 3,
	ServoStationaryAngle = 4,
	ServoTurnValue = 5,
	LineFollowThresholdPercentage = 6,
	LineFollowSpeed = 7,
	LineFollowAngle = 8
};


//% color=75 weight=80
//% icon="\uf1b9"
namespace microbot{

	DigitalOut *_aa, *_ba;
	MicroBitPin *_mbp, *_ab, *_bb;
	AnalogIn *_lr, *_rr;
	CarType cf;

	bool running = false;
	bool tl = false, tr = false;
	int lh, rh, baseHeading;
	int lf = 0;
	int STANDARD_SPEED_VALUE = 1023, STANDARD_DIRECTION_STRAIGHT = 97, STANDARD_TURN_VALUE = 50, SERVO_SPEED_VALUE = 70, SERVO_STATIONARY_VALUE = 90, SERVO_TURN_VALUE = 40, LF_SPEED_VALUE = 100, LF_ANGLE = 50;
	double STANDARD_LF_THRESHOLD = 0.7f;

	void diet_fanta(){
		while(true){
			if(!running) {
				//stop
				_ba->write(0);
				while(!running){
					uBit.sleep(100); //do nothing
				}
			}
			_ba->write(1);
			
			uBit.sleep(100); //do nothing
		}
	}

	void diet_coke(){
		while(true){
			if(!running) {
				//stop
				_aa->write(1);
				_ab->setAnalogValue(1023);
				_ba->write(1);
				_bb->setAnalogValue(1023);
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
				_aa->write(0);
				_ab->setAnalogValue(LF_SPEED_VALUE);
				_ba->write(0);
				_bb->setAnalogValue(LF_SPEED_VALUE);
				if(_lr->read() > STANDARD_LF_THRESHOLD) {
					_mbp->setServoValue(STANDARD_DIRECTION_STRAIGHT - LF_ANGLE);
				} else if(_rr->read() > STANDARD_LF_THRESHOLD) {
					_mbp->setServoValue(STANDARD_DIRECTION_STRAIGHT + LF_ANGLE);
				} else {
					_mbp->setServoValue(STANDARD_DIRECTION_STRAIGHT);
				}
			}
			
			uBit.sleep(100); //do nothing
		}
	}

	void diet_sprite(){
		while(true){
			if(!running) {
				//stop
				tr = false;
				tl = false;
				_ab->setAnalogValue(SERVO_STATIONARY_VALUE);
				_bb->setAnalogValue(SERVO_STATIONARY_VALUE);
				while(!running){
					uBit.sleep(100); //do nothing
				}
			}

			if(tr) {
				_ab->setServoValue(SERVO_STATIONARY_VALUE + SERVO_TURN_VALUE);
				_bb->setServoValue(SERVO_STATIONARY_VALUE + SERVO_TURN_VALUE);
			} else if (tl){
				_ab->setServoValue(SERVO_STATIONARY_VALUE - SERVO_TURN_VALUE);
				_bb->setServoValue(SERVO_STATIONARY_VALUE - SERVO_TURN_VALUE);
			} else if(lf == 0){
				_ab->setServoValue(SERVO_SPEED_VALUE);
				_bb->setServoValue(SERVO_SPEED_VALUE);
			} else {
				if(_lr->read() > STANDARD_LF_THRESHOLD) {
					_ab->setServoValue(SERVO_STATIONARY_VALUE);
					_bb->setServoValue(0);
				} else if(_rr->read() > STANDARD_LF_THRESHOLD) {
					_ab->setServoValue(180);
					_bb->setServoValue(SERVO_STATIONARY_VALUE);
				} else {
					_ab->setServoValue(SERVO_STATIONARY_VALUE + SERVO_SPEED_VALUE);
					_bb->setServoValue(SERVO_STATIONARY_VALUE - SERVO_SPEED_VALUE);
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
		cf = car;
		switch (car){
			case CarType::Servo:
				_ab = new MicroBitPin(MICROBIT_ID_IO_P16, MICROBIT_PIN_P16, PIN_CAPABILITY_ALL);
				_bb = new MicroBitPin(MICROBIT_ID_IO_P2, MICROBIT_PIN_P2, PIN_CAPABILITY_ALL);

				_lr = new AnalogIn(MICROBIT_PIN_P0);
				_rr = new AnalogIn(MICROBIT_PIN_P1);
				running = false;
				create_fiber(diet_sprite);
			break;
			case CarType::Standard:
				_aa = new DigitalOut(MICROBIT_PIN_P13);
				_ab = new MicroBitPin(MICROBIT_ID_IO_P14, MICROBIT_PIN_P14, PIN_CAPABILITY_ALL);
				_ba = new DigitalOut(MICROBIT_PIN_P15);
				_bb = new MicroBitPin(MICROBIT_ID_IO_P16, MICROBIT_PIN_P16, PIN_CAPABILITY_ALL);
				
				_mbp = new MicroBitPin(MICROBIT_ID_IO_P3, MICROBIT_PIN_P3, PIN_CAPABILITY_ALL);

				_lr = new AnalogIn(MICROBIT_PIN_P0);
				_rr = new AnalogIn(MICROBIT_PIN_P1);

				_aa -> write(1);
				_ab -> setAnalogValue(1023);
				_ba -> write(1);
				_bb -> setAnalogValue(1023);
				running = false;
				create_fiber(diet_coke);
			break;
		}
		
	}

	/**
	* set calibration parameter.
	*/
	//% blockId=car_set_calibrate
	//% block="set calibration parameter %param| to %val"
	void calibrate(CalibrationParameters param, int val){
		switch(param){
			case CalibrationParameters::StandardSpeedValue:
			STANDARD_SPEED_VALUE = val;
			break;
			case CalibrationParameters::StandardForwardAngle:
			STANDARD_DIRECTION_STRAIGHT = val;
			break;
			case CalibrationParameters::StandardTurnAngle:
			STANDARD_TURN_VALUE = val;
			break;
			case CalibrationParameters::ServoSpeed:
			SERVO_SPEED_VALUE = val;
			break;
			case CalibrationParameters::ServoStationaryAngle:
			SERVO_STATIONARY_VALUE = val;
			break;
			case CalibrationParameters::LineFollowThresholdPercentage:
			STANDARD_LF_THRESHOLD = (double)val / 100;
			break;
			case CalibrationParameters::LineFollowSpeed:
			LF_SPEED_VALUE = val;
			break;
			case CalibrationParameters::LineFollowAngle:
			LF_ANGLE = val;
			break;
			default:
			//shrugs
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
		if(cf == CarType::Standard){
			_mbp->setServoValue(STANDARD_DIRECTION_STRAIGHT - STANDARD_TURN_VALUE);
		} else {
			tl = true;
		}
		running = true;
	}

	/**
	* turns right.
	*/
	//% blockId=car_right
	//% block="turn right"
	void turnRight(){
		if(running) return;
		//_dir->write(STANDARD_DIRECTION_RIGHT);
		if(cf == CarType::Standard){
			_mbp->setServoValue(STANDARD_DIRECTION_STRAIGHT + STANDARD_TURN_VALUE);
		} else {
			tr = true;
		}

		running = true;
	}

	/**
	* checks if black is detected
	*/
	//% blockId=car_check_square
	//% block="car is on a black square"
	bool isBlack(){
		return (_lr->read() > STANDARD_LF_THRESHOLD && _rr->read() > STANDARD_LF_THRESHOLD);
	}

	/**
	* stops the car.
	*/
	//% blockId=car_stop
	//% block="stop"
	void stop(){
		//printf("call to stop\r\n");
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
		if(cf == CarType::Standard) _mbp->setServoValue(STANDARD_DIRECTION_STRAIGHT);
		running = true;
	}

	/**
	* moves the car forward.
	*/
	//% blockId=car_move
	//% block="go forward"
	void moveUp(){
		//printf("call to start\r\n");
		lf = 0;
		//_dir->write(STANDARD_DIRECTION_STRAIGHT); //need to map this to correct angle
		if(cf == CarType::Standard) _mbp->setServoValue(STANDARD_DIRECTION_STRAIGHT);
		running = true;
	}


}