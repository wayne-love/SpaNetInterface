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

float SpaNetInterface::_updateS2Idiv100(String s) {
    return s.toFloat()/100;
}

int SpaNetInterface::_updateS2I(String s) {
    return s.toInt();
}

bool SpaNetInterface::_updateS2B(String s){
    return s.equals("1");
}

String SpaNetInterface::_updateS2S(String s){
    return s;
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
    CLMT._set_uFunc(_updateS2I);
    PHSE._set_uFunc(_updateS2I);
    LLM1._set_uFunc(_updateS2I);
    LLM2._set_uFunc(_updateS2I);
    LLM3._set_uFunc(_updateS2I);
    SVER._set_uFunc(_updateS2S);
    Model._set_uFunc(_updateS2S);
    SerialNo1._set_uFunc(_updateS2S);
    SerialNo2._set_uFunc(_updateS2S);
    D1._set_uFunc(_updateS2B);
    D2._set_uFunc(_updateS2B);
    D3._set_uFunc(_updateS2B);
    D4._set_uFunc(_updateS2B);
    D5._set_uFunc(_updateS2B);
    D6._set_uFunc(_updateS2B);
    Pump._set_uFunc(_updateS2S);
    LS._set_uFunc(_updateS2I);
    HV._set_uFunc(_updateS2B);
    SniMR._set_uFunc(_updateS2I);
    Status._set_uFunc(_updateS2S);
    PrimeCount._set_uFunc(_updateS2I);
    EC._set_uFunc(_updateS2Idiv10);
    HAMB._set_uFunc(_updateS2I);
    HCON._set_uFunc(_updateS2I);
    HV_2._set_uFunc(_updateS2B);
    Mode._set_uFunc(_updateS2S);
    Ser1_Timer._set_uFunc(_updateS2I);
    Ser2_Timer._set_uFunc(_updateS2I);
    Ser3_Timer._set_uFunc(_updateS2I);
    HeatMode._set_uFunc(_updateS2I);
    PumpIdleTimer._set_uFunc(_updateS2I);
    PumpRunTimer._set_uFunc(_updateS2I);
    AdtPoolHys._set_uFunc(_updateS2Idiv10);
    AdtHeaterHys._set_uFunc(_updateS2Idiv10);
    Power._set_uFunc(_updateS2Idiv10);
    Power_kWh._set_uFunc(_updateS2Idiv100);
    Power_Today._set_uFunc(_updateS2Idiv100);
    Power_Yesterday._set_uFunc(_updateS2Idiv100);
    ThermalCutOut._set_uFunc(_updateS2I);
    Test_D1._set_uFunc(_updateS2I);
    Test_D2._set_uFunc(_updateS2I);
    Test_D3._set_uFunc(_updateS2I);
    ElementHeatSourceOffset._set_uFunc(_updateS2Idiv10);
    Frequency._set_uFunc(_updateS2I);
    HPHeatSourceOffset_Heat._set_uFunc(_updateS2Idiv10);
    HPHeatSourceOffset_Cool._set_uFunc(_updateS2Idiv10);
    HeatSourceOffTime._set_uFunc(_updateS2I);
    Vari_Speed._set_uFunc(_updateS2I);
    Vari_Percent._set_uFunc(_updateS2I);
    Vari_Mode._set_uFunc(_updateS2I);
    // Unknown encoding - TouchPad2._set_uFunc();
    // Unknown encoding - TouchPad1._set_uFunc();
    RB_TP_Pump1._set_uFunc(_updateS2I);
    RB_TP_Pump2._set_uFunc(_updateS2I);
    RB_TP_Pump3._set_uFunc(_updateS2I);
    RB_TP_Pump4._set_uFunc(_updateS2I);
    RB_TP_Blower._set_uFunc(_updateS2I);
    RB_TP_Light._set_uFunc(_updateS2I);
    RB_TP_Auto._set_uFunc(_updateS2I);
    RB_TP_Heater._set_uFunc(_updateS2I);
    RB_TP_Ozone._set_uFunc(_updateS2I);
    RB_TP_Sleep._set_uFunc(_updateS2I);
    WTMP._set_uFunc(_updateS2Idiv10);
    // R6
    VARIValue._set_uFunc(_updateS2I);
    LBRTValue._set_uFunc(_updateS2I);
    CurrClr._set_uFunc(_updateS2I);
    ColorMode._set_uFunc(_updateS2I);
    LSPDValue._set_uFunc(_updateS2I);
    FiltSetHrs._set_uFunc(_updateS2I);
    FiltBlockHrs._set_uFunc(_updateS2I);
    STMP._set_uFunc(_updateS2Idiv10);
    L_24HOURS._set_uFunc(_updateS2I);
    PSAV_LVL._set_uFunc(_updateS2B);
    PSAV_BGN._set_uFunc(_updateS2I);
    PSAV_END._set_uFunc(_updateS2I);
    L_1SNZ_DAY._set_uFunc(_updateS2I);
    L_2SNZ_DAY._set_uFunc(_updateS2I);
    L_1SNZ_BGN._set_uFunc(_updateS2I);
    L_2SNZ_BGN._set_uFunc(_updateS2I);
    L_1SNZ_END._set_uFunc(_updateS2I);
    L_2SNZ_END._set_uFunc(_updateS2I);
    DefaultScrn._set_uFunc(_updateS2I);
    TOUT._set_uFunc(_updateS2I);
    VPMP._set_uFunc(_updateS2B);
    HIFI._set_uFunc(_updateS2B);
    BRND._set_uFunc(_updateS2I);
    PRME._set_uFunc(_updateS2I);
    ELMT._set_uFunc(_updateS2I);
    TYPE._set_uFunc(_updateS2I);
    GAS._set_uFunc(_updateS2I);
    //R7
    WCLNTime._set_uFunc(_updateS2I);
    TemperatureUnits._set_uFunc(_updateS2I);
    OzoneOff._set_uFunc(_updateS2B);
    Ozone24._set_uFunc(_updateS2I);
    Circ24._set_uFunc(_updateS2B);
    CJET._set_uFunc(_updateS2B);
    VELE._set_uFunc(_updateS2I);
    StartDD._set_uFunc(_updateS2I);
    StartMM._set_uFunc(_updateS2I);
    StartYY._set_uFunc(_updateS2I);
    V_Max._set_uFunc(_updateS2I);
    V_Min._set_uFunc(_updateS2I);
    V_Max_24._set_uFunc(_updateS2I);
    V_Min_24._set_uFunc(_updateS2I);
    CurrentZero._set_uFunc(_updateS2I);
    CurrentAdjust._set_uFunc(_updateS2Idiv10);
    VoltageAdjust._set_uFunc(_updateS2Idiv10);
    Ser1._set_uFunc(_updateS2I);
    Ser2._set_uFunc(_updateS2I);
    Ser3._set_uFunc(_updateS2I);
    VMAX._set_uFunc(_updateS2I);
    AHYS._set_uFunc(_updateS2Idiv10);
    HUSE._set_uFunc(_updateS2I);
    HELE._set_uFunc(_updateS2B);
    HPMP._set_uFunc(_updateS2I);
    PMIN._set_uFunc(_updateS2I);
    PFLT._set_uFunc(_updateS2I);
    PHTR._set_uFunc(_updateS2I);
    PMAX._set_uFunc(_updateS2I);


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
    CLMT.updateValue(statusResponseRaw[34]);
    PHSE.updateValue(statusResponseRaw[35]);
    LLM1.updateValue(statusResponseRaw[36]);
    LLM2.updateValue(statusResponseRaw[37]);
    LLM3.updateValue(statusResponseRaw[38]);
    SVER.updateValue(statusResponseRaw[39]);
    Model.updateValue(statusResponseRaw[40]);
    SerialNo1.updateValue(statusResponseRaw[41]);
    SerialNo2.updateValue(statusResponseRaw[42]);
    D1.updateValue(statusResponseRaw[43]);
    D2.updateValue(statusResponseRaw[44]);
    D3.updateValue(statusResponseRaw[45]);
    D4.updateValue(statusResponseRaw[46]);
    D5.updateValue(statusResponseRaw[47]);
    D6.updateValue(statusResponseRaw[48]);
    Pump.updateValue(statusResponseRaw[49]);
    LS.updateValue(statusResponseRaw[50]);
    HV.updateValue(statusResponseRaw[51]);
    SniMR.updateValue(statusResponseRaw[52]);
    Status.updateValue(statusResponseRaw[53]);
    PrimeCount.updateValue(statusResponseRaw[54]);
    EC.updateValue(statusResponseRaw[55]);
    HAMB.updateValue(statusResponseRaw[56]);
    HCON.updateValue(statusResponseRaw[57]);
    HV_2.updateValue(statusResponseRaw[58]);
    Mode.updateValue(statusResponseRaw[63]);
    Ser1_Timer.updateValue(statusResponseRaw[64]);
    Ser2_Timer.updateValue(statusResponseRaw[65]);
    Ser3_Timer.updateValue(statusResponseRaw[66]);
    HeatMode.updateValue(statusResponseRaw[67]);
    PumpIdleTimer.updateValue(statusResponseRaw[68]);
    PumpRunTimer.updateValue(statusResponseRaw[69]);
    AdtPoolHys.updateValue(statusResponseRaw[70]);
    AdtHeaterHys.updateValue(statusResponseRaw[71]);
    Power.updateValue(statusResponseRaw[72]);
    Power_kWh.updateValue(statusResponseRaw[73]);
    Power_Today.updateValue(statusResponseRaw[74]);
    Power_Yesterday.updateValue(statusResponseRaw[75]);
    ThermalCutOut.updateValue(statusResponseRaw[76]);
    Test_D1.updateValue(statusResponseRaw[77]);
    Test_D2.updateValue(statusResponseRaw[78]);
    Test_D3.updateValue(statusResponseRaw[79]);
    ElementHeatSourceOffset.updateValue(statusResponseRaw[80]);
    Frequency.updateValue(statusResponseRaw[81]);
    HPHeatSourceOffset_Heat.updateValue(statusResponseRaw[82]);
    HPHeatSourceOffset_Cool.updateValue(statusResponseRaw[83]);
    HeatSourceOffTime.updateValue(statusResponseRaw[84]);
    Vari_Speed.updateValue(statusResponseRaw[86]);
    Vari_Percent.updateValue(statusResponseRaw[87]);
    Vari_Mode.updateValue(statusResponseRaw[85]);
    // Unknown encoding - TouchPad2.updateValue();
    // Unknown encoding - TouchPad1.updateValue();
    RB_TP_Pump1.updateValue(statusResponseRaw[97]);
    RB_TP_Pump2.updateValue(statusResponseRaw[98]);
    RB_TP_Pump3.updateValue(statusResponseRaw[99]);
    RB_TP_Pump4.updateValue(statusResponseRaw[100]);
    RB_TP_Blower.updateValue(statusResponseRaw[101]);
    RB_TP_Light.updateValue(statusResponseRaw[102]);
    RB_TP_Auto.updateValue(statusResponseRaw[103]);
    RB_TP_Heater.updateValue(statusResponseRaw[104]);
    RB_TP_Ozone.updateValue(statusResponseRaw[105]);
    RB_TP_Sleep.updateValue(statusResponseRaw[106]);
    WTMP.updateValue(statusResponseRaw[107]);
    //R6
    VARIValue.updateValue(statusResponseRaw[121]);
    LBRTValue.updateValue(statusResponseRaw[122]);
    CurrClr.updateValue(statusResponseRaw[123]);
    ColorMode.updateValue(statusResponseRaw[124]);
    LSPDValue.updateValue(statusResponseRaw[125]);
    FiltSetHrs.updateValue(statusResponseRaw[126]);
    FiltBlockHrs.updateValue(statusResponseRaw[127]);
    STMP.updateValue(statusResponseRaw[128]);
    L_24HOURS.updateValue(statusResponseRaw[129]);
    PSAV_LVL.updateValue(statusResponseRaw[130]);
    PSAV_BGN.updateValue(statusResponseRaw[131]);
    PSAV_END.updateValue(statusResponseRaw[132]);
    L_1SNZ_DAY.updateValue(statusResponseRaw[133]);
    L_2SNZ_DAY.updateValue(statusResponseRaw[134]);
    L_1SNZ_BGN.updateValue(statusResponseRaw[135]);
    L_2SNZ_BGN.updateValue(statusResponseRaw[136]);
    L_1SNZ_END.updateValue(statusResponseRaw[137]);
    L_2SNZ_END.updateValue(statusResponseRaw[138]);
    DefaultScrn.updateValue(statusResponseRaw[139]);
    TOUT.updateValue(statusResponseRaw[140]);
    VPMP.updateValue(statusResponseRaw[141]);
    HIFI.updateValue(statusResponseRaw[142]);
    BRND.updateValue(statusResponseRaw[143]);
    PRME.updateValue(statusResponseRaw[144]);
    ELMT.updateValue(statusResponseRaw[145]);
    TYPE.updateValue(statusResponseRaw[146]);
    GAS.updateValue(statusResponseRaw[147]);
    //R7
    WCLNTime.updateValue(statusResponseRaw[151]);
    // The following 2 may be reversed
    TemperatureUnits.updateValue(statusResponseRaw[153]);
    OzoneOff.updateValue(statusResponseRaw[152]);
    Ozone24.updateValue(statusResponseRaw[154]);
    // The following 2 may be reversed
    Circ24.updateValue(statusResponseRaw[156]);
    CJET.updateValue(statusResponseRaw[155]);
    VELE.updateValue(statusResponseRaw[167]);
    StartDD.updateValue(statusResponseRaw[157]);
    StartMM.updateValue(statusResponseRaw[158]);
    StartYY.updateValue(statusResponseRaw[159]);
    V_Max.updateValue(statusResponseRaw[160]);
    V_Min.updateValue(statusResponseRaw[161]);
    V_Max_24.updateValue(statusResponseRaw[162]);
    V_Min_24.updateValue(statusResponseRaw[163]);
    CurrentZero.updateValue(statusResponseRaw[164]);
    CurrentAdjust.updateValue(statusResponseRaw[165]);
    VoltageAdjust.updateValue(statusResponseRaw[166]);
    Ser1.updateValue(statusResponseRaw[168]);
    Ser2.updateValue(statusResponseRaw[169]);
    Ser3.updateValue(statusResponseRaw[170]);
    VMAX.updateValue(statusResponseRaw[171]);
    AHYS.updateValue(statusResponseRaw[172]);
    HUSE.updateValue(statusResponseRaw[173]);
    HELE.updateValue(statusResponseRaw[174]);
    HPMP.updateValue(statusResponseRaw[175]);
    PMIN.updateValue(statusResponseRaw[176]);
    PFLT.updateValue(statusResponseRaw[177]);
    PHTR.updateValue(statusResponseRaw[178]);
    PMAX.updateValue(statusResponseRaw[179]);

};