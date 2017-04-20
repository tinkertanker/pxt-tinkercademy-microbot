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
