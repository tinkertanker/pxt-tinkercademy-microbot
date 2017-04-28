// Auto-generated. Do not edit.



    //% color=75 weight=80
    //% icon="\uf1b9"
declare namespace microbot {

    /**
     * initializes pinout for the car.
     */
    //% blockId=car_init
    //% block="initialise car type %car" shim=microbot::init
    function init(car: CarType): void;

    /**
     * set calibration parameter.
     */
    //% blockId=car_set_calibrate
    //% block="set calibration parameter %param| to %val" shim=microbot::calibrate
    function calibrate(param: CalibrationParameters, val: number): void;

    /**
     * turns left.
     */
    //% blockId=car_left
    //% block="turn left" shim=microbot::turnLeft
    function turnLeft(): void;

    /**
     * turns right.
     */
    //% blockId=car_right
    //% block="turn right" shim=microbot::turnRight
    function turnRight(): void;

    /**
     * checks if black is detected
     */
    //% blockId=car_check_square
    //% block="car is on a black square" shim=microbot::isBlack
    function isBlack(): boolean;

    /**
     * stops the car.
     */
    //% blockId=car_stop
    //% block="stop" shim=microbot::stop
    function stop(): void;

    /**
     * sets the car to start following a line.
     */
    //% blockId=car_linefollow
    //% block="follow line" shim=microbot::followLine
    function followLine(): void;

    /**
     * moves the car forward.
     */
    //% blockId=car_move
    //% block="go forward" shim=microbot::moveUp
    function moveUp(): void;
}

// Auto-generated. Do not edit. Really.
