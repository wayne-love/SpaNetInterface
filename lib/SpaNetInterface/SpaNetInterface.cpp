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

bool SpaNetInterface::_updateS2B(String s){
    return s.equals("1");
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
    PortCurrent._set_uFunc(_updateS2I);
    HeaterTemperature._set_uFunc(_updateS2Idiv10);
    PoolTemperature._set_uFunc(_updateS2Idiv10);
    WaterPresent._set_uFunc(_updateS2B);
    AwakeMinutesRemaining._set_uFunc(_updateS2I);
    FiltPumpRunTimeTotal._set_uFunc(_updateS2I);
    FiltPumpReqMins._set_uFunc(_updateS2I);
    LoadTimeOut._set_uFunc(_updateS2I);
    HourMeter._set_uFunc(_updateS2Idiv10);
    Relay1._set_uFunc(_updateS2I);
    Relay2._set_uFunc(_updateS2I);
    Relay3._set_uFunc(_updateS2I);
    Relay4._set_uFunc(_updateS2I);
    Relay5._set_uFunc(_updateS2I);
    Relay6._set_uFunc(_updateS2I);
    Relay7._set_uFunc(_updateS2I);
    Relay8._set_uFunc(_updateS2I);
    Relay9._set_uFunc(_updateS2I);

}

void SpaNetInterface::updateMeasures() {
    MainsCurrent.updateValue(statusResponseRaw[2]);
    MainsVoltage.updateValue(statusResponseRaw[3]);
    CaseTemperature.updateValue(statusResponseRaw[4]);
    PortCurrent.updateValue(statusResponseRaw[5]);
    HeaterTemperature.updateValue(statusResponseRaw[13]);
    PoolTemperature.updateValue(statusResponseRaw[14]);
    WaterPresent.updateValue(statusResponseRaw[15]);
    AwakeMinutesRemaining.updateValue(statusResponseRaw[17]);
    FiltPumpRunTimeTotal.updateValue(statusResponseRaw[18]);
    FiltPumpReqMins.updateValue(statusResponseRaw[19]);
    LoadTimeOut.updateValue(statusResponseRaw[20]);
    HourMeter.updateValue(statusResponseRaw[21]);
    Relay1.updateValue(statusResponseRaw[22]);
    Relay2.updateValue(statusResponseRaw[23]);
    Relay3.updateValue(statusResponseRaw[24]);
    Relay4.updateValue(statusResponseRaw[25]);
    Relay5.updateValue(statusResponseRaw[26]);
    Relay6.updateValue(statusResponseRaw[27]);
    Relay7.updateValue(statusResponseRaw[28]);
    Relay8.updateValue(statusResponseRaw[29]);
    Relay9.updateValue(statusResponseRaw[30]);
    
}
