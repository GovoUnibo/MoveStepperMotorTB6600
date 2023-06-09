#include "Stepper_taglierina.hpp"

using namespace taglierina;


// stepper si muove 4xe-5 m per fullstep--> 4e-5 x 200 = 0,008m per giro
// ho un microstepping di 16 quindi gli step per giro sono 200x16= 3200 step per fare 0.008 mm



Stepper::Stepper(int micro_step, int en, int dir, int step) : AccelStepper(1, step, dir){

    //Motor pins
    
    this->enable_pin = en;
    this->dir_pin = dir;
    this->step_pin = step;

    //Motor char
    this->setMicroStep(micro_step);
    this->setStepsPerRotation(200*micro_step);
    this->setDistancePerRotation(8); //mm
    this->angle_per_step = 1.8/micro_step;
    this->max_length_screw = 8000;

    // AccelStepper::setEnablePin(en);
    // AccelStepper::setPinsInverted(false, false, true);
    this->home_done = false;
}

Stepper::~Stepper(){}

float Stepper::getCurrentPositionDistance() {
	return AccelStepper::currentPosition() / (this->microSteps * this->stepsPerRotation / this->distancePerRotation);
}

int Stepper::mm_To_step(float quantity_mm){
    return quantity_mm * this->microSteps * this->stepsPerRotation / this->distancePerRotation;
}


void Stepper::moveToDistance(float pos, float vel, float acc) {
  
  AccelStepper::setMaxSpeed(this->mm_To_step(vel));
  AccelStepper::setAcceleration(this->mm_To_step(acc));
  Serial.println(this->mm_To_step(pos));
  if (this->home_done){
  	AccelStepper::moveTo(this->mm_To_step(pos));
    AccelStepper::runToPosition();
  }
  this->home_done = false;
  
}

void Stepper::setHomeDone(){
  this->home_done = true;
  AccelStepper::setCurrentPosition(0);
  
}


void Stepper::enableMotor(){
    AccelStepper::enableOutputs();
}

void Stepper::disableMotor(){
    AccelStepper::disableOutputs();
}
