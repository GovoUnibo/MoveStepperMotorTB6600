#ifndef Stepper_hpp
#define Stepper_hpp

#include <Arduino.h>
#include <AccelStepper.h>

namespace taglierina{
    

    class Stepper : private AccelStepper{

        public:
            Stepper(int micro_step, int en, int dir, int step);
            ~Stepper();
            
            void moveToDistance(float pos, float vel, float acc);
            float getCurrentPositionDistance();
            void setHomeDone();
            void enableMotor();
            void disableMotor();


        private:
            int mm_To_step(float quantity_mm);
            void setMicroStep(int value) {  microSteps = value;}
            void setStepsPerRotation(int value) { stepsPerRotation = value; }
            void setDistancePerRotation(float value) { distancePerRotation = value;}

            
            bool home_done, motor_enabled;
            int step_pin, dir_pin, enable_pin;

            int microSteps;
            int stepsPerRotation;
            float distancePerRotation;

            float max_length_screw;
          

            float angle_per_step;

            unsigned long step_delay;

            int step_counter;
            
    };

};

#endif
