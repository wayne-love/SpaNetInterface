#ifndef SPANETINTERFACE_H
#define SPANETINTERFACE_H

#include <Arduino.h>

class SpaNetInterface {
    private:

        /// @brief Each field of the RF cmd response as seperate elements.  NOTE: Not Syntax checked!
        String statusResponseRaw[289];
        bool validStatusResponse;
        Stream &port;

        void updateMeasures();
        void initialise();

        static float _updateS2Idiv10(String s);
        static int _updateS2I(String s);

    public:
        /// @brief Init SNI to read from stream p. This stream needs to be started and configured baud 38400/8N1.
        /// @param p 
        SpaNetInterface(Stream &p);

        /// @brief Init SNI and user Serial2 for comms.  Serial 2 DOES NOT need to be configured.
        SpaNetInterface();

        ~SpaNetInterface();

        bool readStatus();

        template<class T>
        class Attribute {
            private: 
                T _value;
                T (*_uFunc)(String);

            public:
                T getValue() { return _value; }
                void updateValue(String s) { _value = _uFunc(s); }
                void _set_uFunc(T (*func)(String)) { _uFunc = func;  }

        };

        Attribute<float>    MainsCurrent;
        Attribute<int>      MainsVoltage;
        Attribute<int>      CaseTemperature;
};


#endif