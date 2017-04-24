#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H


class MovementComponent
{
    public:
        MovementComponent();
        virtual ~MovementComponent();

        void update();

        void setAccelRate(float r);
        void setAccelRateLimit(float r);
        void setRotationRate(float r);
        void setVelLimit(float v);


        ///State Functions
        void setRotateRightState();
        void setRotateLeftState();
        void setRotateRightStateFalse();
        void setRotateLeftStateFalse();
        void setAccelState();
        void setAccelStateFalse();
        void setBrakeState();
        void setBrakeStateFalse();

        ///Action Functions
        void rotateRight();
        void rotateLeft();
        void accelerate();
        void brake();

         enum RotateRightState
        {
            ROTATE_RIGHT,
            ROTATE_RIGHT_F
        }rotateRightState;
         enum RotateLefttState
        {
            ROTATE_LEFT,
            ROTATE_LEFT_F
        }rotateLeftState;
        enum AccelState
        {
            ACCELERATE,
            ACCELERATE_F
        }accelState;
        enum BrakeState
        {
            BRAKE,
            BRAKE_F

        }brakeState;


    protected:
    private:
        float accelRate;
        float accelRateLimit;
        float velLimit;
        float rotationRate;

};

#endif // MOVEMENTCOMPONENT_H
