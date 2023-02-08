#ifndef SPANETINTERFACE_H
#define SPANETINTERFACE_H

#include <Arduino.h>
#include <RemoteDebug.h>
#include <functional>
#include "SpaNetProperties.h"




#ifndef DEBUG_
#define DEBUG_
RemoteDebug Debug;
#endif

#define UPDATEFREQUENCY 60000 //(ms) Frequency to poll controller when idle.






class SpaNetInterface : public SpaNetProperties {
    private:

        /// @brief Each field of the RF cmd response as seperate elements.  NOTE: Not Syntax checked!
        String String;
        bool validStatusResponse;
        Stream &port;

        void initialise();
        /// @brief Read from serial interface, expect it to contain return from RF command
        /// @return true if successful read, false if there was a corrupted read
        bool readStatus();
        void updateMeasures();

        /// @brief Sends command to SpaNet controller.
        /// @param cmd - cmd to be executed.
        void sendCommand(String cmd);

        /// @brief Updates the attributes by sending the RF command and parsing the result.
        void updateStatus();

        /// @brief Stores millis time at which next update should occur
        unsigned long _nextUpdateDue = 0;

        String _sendCommand(String cmd);

        static float _updateS2Idiv10(String s);
        static float _updateS2Idiv100(String s);
        static int _updateS2I(String s);
        static bool _updateS2B(String s);
        static String _updateS2S(String s);

        bool _setSTMP(float temp);

    public:
        /// @brief Init SNI to read from stream p. This stream needs to be started and configured baud 38400/8N1.
        /// @param p 
        SpaNetInterface(Stream &p);

        /// @brief Init SNI and user Serial2 for comms.  Serial 2 DOES NOT need to be configured.
        SpaNetInterface();

        ~SpaNetInterface();

        /// @brief To be called my loop function of main sketch.  Does regular updates, etc.
        void loop();
/*
        template<class T>
        class Property {
            private: 
                T _value;
                T (*_uFunc)(String);

            public:
                Property() {};

                T getValue() { return _value; }
                void (*callBack)(){};

                void _updateValue(String s) {
                    T newValue = _uFunc(s);
                    bool changed = (_value != newValue);
                    _value = newValue;
                    if (changed && callBack) {
                        callBack;
                    }
                }
                void _set_uFunc(T (*func)(String)) { _uFunc = func;  }
        };

        template <class T>
        class Property_Idiv10 : public Property {

        }
*/
        template<class T>
        class SettableAttribute : public Property<T> {
            private:
                T (*_wFunc)(T);

            public:
                T setValue();
                void _setwFunc(bool (*func)(T)) { _wFunc = func; }
        };

#pragma region R2
        // R2
 

        //TODO - Reg 6 unknown data
        //TODO - Reg 16 unknown



};


#endif