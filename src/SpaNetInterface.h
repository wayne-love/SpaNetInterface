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
#define FAILEDREADFREQUENCY 1000 //(ms) Frequency to retry on a failed read of the status registers.






class SpaNetInterface : public SpaNetProperties {
    private:

        /// @brief Each field of the RF cmd response as seperate elements.
        String statusResponseRaw[290];

        /// @brief Does the status response array contain valid information?
        bool validStatusResponse = false;

        /// @brief Serial stream to interface to SpanNet hardware.
        Stream &port;

        /// @brief Read from serial interface, expect it to contain return from RF command
        /// @return true if successful read, false if there was a corrupted read
        bool readStatus();

        void updateMeasures();

        /// @brief Sends command to SpaNet controller.  Result must be read by some other method.
        /// Used for the 'RF' command so that we can do a optomised read of the return array.
        /// @param cmd - cmd to be executed.
        void sendCommand(String cmd);

        
        /// @brief Sends a command to the SpanNet controller and returns the result string
        /// @param cmd - cmd to be executed
        /// @return String - result string
        String sendCommandReturnResult(String cmd);

        /// @brief Updates the attributes by sending the RF command and parsing the result.
        void updateStatus();

        /// @brief Stores millis time at which next update should occur
        unsigned long _nextUpdateDue = 0;

        bool _initialised = false;



    public:
        /// @brief Init SNI to read from stream p. This stream needs to be started and configured baud 38400/8N1.
        /// useful if you want to link this to a software COM port on a chip similar to a ESP8266.
        /// Needs to be set to 38400/8/N/1
        /// @param p 
        SpaNetInterface(Stream &p);

        /// @brief Init SNI and use Serial2 for comms.  Serial 2 DOES NOT need to be configured.
        SpaNetInterface();

        ~SpaNetInterface();

        /// @brief To be called by loop function of main sketch.  Does regular updates, etc.
        void loop();

        /// @brief Set the desired water temperature
        /// @param temp Between 5 and 40 in 0.5 increments
        /// @return Returns True if succesful
        bool setSTMP(float temp);

        /// @brief Have we sucessfuly read the registers from the SpaNet controller.
        /// @return 
        bool isInitialised();
};


#endif