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

        /// @brief Each field of the RF cmd response as seperate elements.
        String statusResponseRaw[290];

        /// @brief Does the status response array contain valid information?
        bool validStatusResponse = false;
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


    public:
        /// @brief Init SNI to read from stream p. This stream needs to be started and configured baud 38400/8N1.
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
};


#endif