#include "mbed.h"
#include "hcsr04.h"
#include "Servo.h"
#include <cstdio>

HCSR04  usensor(D11,D10); //TRIG PIN 11 ECHO PIN 10;
float dist;
Servo myservo (D6); //SERVO PIN 6
DigitalOut Motor_pin_left (D8);
DigitalOut Motor_pin_left_reverse (D9);
DigitalOut Motor_pin_right (D7);
DigitalOut Motor_pin_right_reverse (D4);

PwmOut speed_control_left(D3);
PwmOut speed_control_right(D5);
 

bool servo_max = false;
bool servo_min = false;
float servo_stand = 45;

float ultrasoon_lezen(){
    usensor.start();
        ThisThread::sleep_for(50); 
        dist=usensor.get_dist_cm();
        return dist;
}

void Start_position(){
    myservo.write(1);
    servo_stand = 45;
}



int main()
{
    speed_control_left.write(0.90f);
    speed_control_right.write(0.90f);
    Start_position();
    while(true) {
     //printf("Readings: %f \n", dist);
        if(ultrasoon_lezen() > 45){
            Motor_pin_right = 1;
            Motor_pin_left = 1;
            myservo.position(servo_stand);
                if(servo_stand == -45){
                servo_max = false;
                servo_min = true;
                }   
                if(servo_stand == 45){
                servo_min = false;
                servo_max = true;
                }  
                if(servo_max == true){
                    servo_stand = servo_stand - 5;
                } 
                if(servo_min == true){
                    servo_stand = servo_stand + 5;
                }         
        }else{
            if(servo_stand < 0){
                Motor_pin_right = 0;
                Motor_pin_left_reverse = 1;
            }
            else if(servo_stand > 0){
                Motor_pin_left = 0;
                Motor_pin_right_reverse = 1;
            }
            }
            Motor_pin_right_reverse = 0;
            Motor_pin_left_reverse = 0;
        }
}