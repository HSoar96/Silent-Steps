    #include <motor.h>

    Motor::Motor(int enable, int inA, int inB)
    {
        _enable = enable;
        _inA = inA;
        _inB = inB;
        SetupPins();
    }

    void Motor::SetupPins()
    {
        pinMode(_enable, OUTPUT);
        pinMode(_inA, OUTPUT);
        pinMode(_inB, OUTPUT);
    }

    void Motor::Enable(directions dir, int speed)
    {
        // Convert the speed 0-100 to duty cycle.
        int duty = map(speed, 0, 100, 0, 255);

        // Take the parsed direction and enable the correct pins.
        switch (dir)
        {
            case FORWARD:
            analogWrite(_enable, duty);
            digitalWrite(_inA, HIGH);
            digitalWrite(_inB, LOW);
            break;

            case BACKWARD:
            analogWrite(_enable, duty);
            digitalWrite(_inA, LOW);
            digitalWrite(_inB, HIGH);
            break;

            case STOP:
            digitalWrite(_enable, LOW);
            digitalWrite(_inA, LOW);
            digitalWrite(_inB, LOW);
            break;

            default:
            throw Error(DIRECTION_INVALID, "Invalid direction argument parsed.");
            break;
        }
    }

    int Motor::GetEnable()
    {
        return _enable;
    }

    int Motor::GetInA()
    {
        return _inA;
    }

    int Motor::GetInB()
    {
        return _inB;
    }

