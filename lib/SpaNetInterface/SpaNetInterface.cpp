#include "SpaNetInterface.h"

SpaNetInterface::SpaNetInterface(Stream &p) : port(p) {
    initialise();
}

SpaNetInterface::SpaNetInterface() : port(Serial2) {
    Serial2.setRxBufferSize(1024);  //required for unit testing
    Serial2.setTxBufferSize(1024);  //required for unit testing
    Serial2.begin(38400, SERIAL_8N1, 16, 17);
    Serial2.setTimeout(250);
    initialise();
}

SpaNetInterface::~SpaNetInterface() {}




float SpaNetInterface::_updateS2Idiv10(String s) {
    return s.toFloat()/10;
}

int SpaNetInterface::_updateS2I(String s) {
    return s.toInt();
}

bool SpaNetInterface::readStatus() {

    int field = 0;
    validStatusResponse = false;

    while (field < 289)
    {
        String s = port.readStringUntil(',');

        if (s.isEmpty()) { // If we get a empty field then we've had a bad read.
            return false;
        }

        statusResponseRaw[field] = s;
        field++;
    }

    validStatusResponse = true;

    //Flush the remaining data from the buffer as the last field is meaningless
    //TODO - If there is a lot of noise on the serial line then this could be a endless loop
    while (port.available() > 0) { 
        port.read();
    }

    updateMeasures();
    return true;
}

void SpaNetInterface::initialise() {
    MainsCurrent._set_uFunc(_updateS2Idiv10);
    MainsVoltage._set_uFunc(_updateS2I);
    CaseTemperature._set_uFunc(_updateS2I);
}

void SpaNetInterface::updateMeasures() {
    MainsCurrent.updateValue(statusResponseRaw[2]);
    MainsVoltage.updateValue(statusResponseRaw[3]);
    CaseTemperature.updateValue(statusResponseRaw[4]);
}

