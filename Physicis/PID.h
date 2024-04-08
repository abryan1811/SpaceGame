#ifndef PID
#define PID
#include <vector>

class RingBuffer
{
private:
    std::vector<float > buffer;
    size_t head;
    const size_t capacity;

public:
    RingBuffer(size_t _size)
        : buffer(_size)
        , head(0)
        , capacity(_size)
    {}

    void Push(float val)
    {
        buffer[head] = val;
        head = (head + 1) % capacity;
    }

    float Get(float dealtaTime)
    {
        float sumResult = 0.0f;

        for(int i = 0; i < capacity; i++)
        {
            sumResult += buffer[i] * dealtaTime;
        }
        
        return sumResult;
    }
};

class Pid_Controller
{
    const size_t bufferSize = 4;

    public:
    Pid_Controller()
        :ringBuffer(bufferSize)
    {

    }
        
    RingBuffer ringBuffer;
    
    const float cp = -1.0f; //Kp
   
    const float ci = -25.0f;    

    const float cd = -1.0f;

    float error = 0.0f;

    void SetError(float desiredValue, float measuredValue)
    {
        error = measuredValue - desiredValue;
        ringBuffer.Push(error);
    }  
    
    float Get_P_output()
    {
        return cp * error;
    }

    float Get_I_output(float deltaTime)
    {
        return ci * ringBuffer.Get(deltaTime);
    }   

};

#endif

