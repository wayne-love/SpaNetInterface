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

    #pragma region R5
    // Unknown encoding - TouchPad2._set_uFunc();
    // Unknown encoding - TouchPad1._set_uFunc();
    RB_TP_Pump1._set_uFunc(_updateS2I);
    RB_TP_Pump2._set_uFunc(_updateS2I);
    RB_TP_Pump3._set_uFunc(_updateS2I);
    RB_TP_Pump4._set_uFunc(_updateS2I);
    RB_TP_Blower._set_uFunc(_updateS2I);
    RB_TP_Light._set_uFunc(_updateS2I);
    RB_TP_Auto._set_uFunc(_updateS2B);
    RB_TP_Heater._set_uFunc(_updateS2B);
    RB_TP_Ozone._set_uFunc(_updateS2B);
    RB_TP_Sleep._set_uFunc(_updateS2B);
    WTMP._set_uFunc(_updateS2Idiv10);
    CleanCycle._set_uFunc(_updateS2B);
    #pragma endregion

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
    PSAV_LVL._set_uFunc(_updateS2I);
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
    TemperatureUnits._set_uFunc(_updateS2B);
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

    //R9.
    F1_HR._set_uFunc(_updateS2Idiv10);
    F1_Time._set_uFunc(_updateS2I);
    F1_ER._set_uFunc(_updateS2I);
    F1_I._set_uFunc(_updateS2Idiv10);
    F1_V._set_uFunc(_updateS2I);
    F1_PT._set_uFunc(_updateS2Idiv10);
    F1_HT._set_uFunc(_updateS2Idiv10);
    F1_CT._set_uFunc(_updateS2Idiv10);
    F1_PU._set_uFunc(_updateS2I);
    F1_VE._set_uFunc(_updateS2B);
    F1_ST._set_uFunc(_updateS2Idiv10);
    //RA.
    F2_HR._set_uFunc(_updateS2Idiv10);
    F2_Time._set_uFunc(_updateS2I);
    F2_ER._set_uFunc(_updateS2I);
    F2_I._set_uFunc(_updateS2Idiv10);
    F2_V._set_uFunc(_updateS2I);
    F2_PT._set_uFunc(_updateS2Idiv10);
    F2_HT._set_uFunc(_updateS2Idiv10);
    F2_CT._set_uFunc(_updateS2Idiv10);
    F2_PU._set_uFunc(_updateS2I);
    F2_VE._set_uFunc(_updateS2B);
    F2_ST._set_uFunc(_updateS2Idiv10);
    //RB.
    F3_HR._set_uFunc(_updateS2Idiv10);
    F3_Time._set_uFunc(_updateS2I);
    F3_ER._set_uFunc(_updateS2I);
    F3_I._set_uFunc(_updateS2Idiv10);
    F3_V._set_uFunc(_updateS2I);
    F3_PT._set_uFunc(_updateS2Idiv10);
    F3_HT._set_uFunc(_updateS2Idiv10);
    F3_CT._set_uFunc(_updateS2Idiv10);
    F3_PU._set_uFunc(_updateS2I);
    F3_VE._set_uFunc(_updateS2B);
    F3_ST._set_uFunc(_updateS2Idiv10);
    //RC
    //Outlet_Heater._set_uFunc(_updateS2I);
    //Outlet_Circ._set_uFunc(_updateS2I);
    //Outlet_Sanitise._set_uFunc(_updateS2I);
    //Outlet_Pump1._set_uFunc(_updateS2I);
    //Outlet_Pump2._set_uFunc(_updateS2I);
    //Outlet_Pump4._set_uFunc(_updateS2I);
    //Outlet_Pump5._set_uFunc(_updateS2I);
    Outlet_Blower._set_uFunc(_updateS2I);
    //RE
    HP_Present._set_uFunc(_updateS2I);
    //HP_FlowSwitch._set_uFunc(_updateS2I);
    //HP_HighSwitch._set_uFunc(_updateS2I);
    //HP_LowSwitch._set_uFunc(_updateS2I);
    //HP_CompCutOut._set_uFunc(_updateS2I);
    //HP_ExCutOut._set_uFunc(_updateS2I);
    //HP_D1._set_uFunc(_updateS2I);
    //HP_D2._set_uFunc(_updateS2I);
    //HP_D3._set_uFunc(_updateS2I);
    HP_Ambient._set_uFunc(_updateS2I);
    HP_Condensor._set_uFunc(_updateS2I);
    HP_Compressor_State._set_uFunc(_updateS2B);
    HP_Fan_State._set_uFunc(_updateS2B);
    HP_4W_Valve._set_uFunc(_updateS2B);
    HP_Heater_State._set_uFunc(_updateS2B);
    HP_State._set_uFunc(_updateS2I);
    HP_Mode._set_uFunc(_updateS2I);
    HP_Defrost_Timer._set_uFunc(_updateS2I);
    HP_Comp_Run_Timer._set_uFunc(_updateS2I);
    HP_Low_Temp_Timer._set_uFunc(_updateS2I);
    HP_Heat_Accum_Timer._set_uFunc(_updateS2I);
    HP_Sequence_Timer._set_uFunc(_updateS2I);
    HP_Warning._set_uFunc(_updateS2I);
    FrezTmr._set_uFunc(_updateS2I);
    DBGN._set_uFunc(_updateS2I);
    DEND._set_uFunc(_updateS2I);
    DCMP._set_uFunc(_updateS2I);
    DMAX._set_uFunc(_updateS2I);
    DELE._set_uFunc(_updateS2I);
    DPMP._set_uFunc(_updateS2I);
    //CMAX._set_uFunc(_updateS2I);
    //HP_Compressor._set_uFunc(_updateS2I);
    //HP_Pump_State._set_uFunc(_updateS2I);
    //HP_Status._set_uFunc(_updateS2I);

    #pragma region RG
    Pump1InstallState._set_uFunc(_updateS2S);
    Pump2InstallState._set_uFunc(_updateS2S);
    Pump3InstallState._set_uFunc(_updateS2S);
    Pump4InstallState._set_uFunc(_updateS2S);
    Pump1OkToRun._set_uFunc(_updateS2B);
    Pump2OkToRun._set_uFunc(_updateS2B);
    Pump3OkToRun._set_uFunc(_updateS2B);
    Pump4OkToRun._set_uFunc(_updateS2B);
    LockMode._set_uFunc(_updateS2I);

#pragma endregion
}

void SpaNetInterface::updateMeasures() {
    #pragma region R2
    MainsCurrent._updateValue(statusResponseRaw[2]);
    MainsVoltage._updateValue(statusResponseRaw[3]);
    CaseTemperature._updateValue(statusResponseRaw[4]);
    PortCurrent._updateValue(statusResponseRaw[5]);
    HeaterTemperature._updateValue(statusResponseRaw[13]);
    PoolTemperature._updateValue(statusResponseRaw[14]);
    WaterPresent._updateValue(statusResponseRaw[15]);
    AwakeMinutesRemaining._updateValue(statusResponseRaw[17]);
    FiltPumpRunTimeTotal._updateValue(statusResponseRaw[18]);
    FiltPumpReqMins._updateValue(statusResponseRaw[19]);
    LoadTimeOut._updateValue(statusResponseRaw[20]);
    HourMeter._updateValue(statusResponseRaw[21]);
    Relay1._updateValue(statusResponseRaw[22]);
    Relay2._updateValue(statusResponseRaw[23]);
    Relay3._updateValue(statusResponseRaw[24]);
    Relay4._updateValue(statusResponseRaw[25]);
    Relay5._updateValue(statusResponseRaw[26]);
    Relay6._updateValue(statusResponseRaw[27]);
    Relay7._updateValue(statusResponseRaw[28]);
    Relay8._updateValue(statusResponseRaw[29]);
    Relay9._updateValue(statusResponseRaw[30]);
    #pragma endregion
    CLMT._updateValue(statusResponseRaw[34]);
    PHSE._updateValue(statusResponseRaw[35]);
    LLM1._updateValue(statusResponseRaw[36]);
    LLM2._updateValue(statusResponseRaw[37]);
    LLM3._updateValue(statusResponseRaw[38]);
    SVER._updateValue(statusResponseRaw[39]);
    Model._updateValue(statusResponseRaw[40]);
    SerialNo1._updateValue(statusResponseRaw[41]);
    SerialNo2._updateValue(statusResponseRaw[42]);
    D1._updateValue(statusResponseRaw[43]);
    D2._updateValue(statusResponseRaw[44]);
    D3._updateValue(statusResponseRaw[45]);
    D4._updateValue(statusResponseRaw[46]);
    D5._updateValue(statusResponseRaw[47]);
    D6._updateValue(statusResponseRaw[48]);
    Pump._updateValue(statusResponseRaw[49]);
    LS._updateValue(statusResponseRaw[50]);
    HV._updateValue(statusResponseRaw[51]);
    SniMR._updateValue(statusResponseRaw[52]);
    Status._updateValue(statusResponseRaw[53]);
    PrimeCount._updateValue(statusResponseRaw[54]);
    EC._updateValue(statusResponseRaw[55]);
    HAMB._updateValue(statusResponseRaw[56]);
    HCON._updateValue(statusResponseRaw[57]);
    HV_2._updateValue(statusResponseRaw[58]);
    Mode._updateValue(statusResponseRaw[63]);
    Ser1_Timer._updateValue(statusResponseRaw[64]);
    Ser2_Timer._updateValue(statusResponseRaw[65]);
    Ser3_Timer._updateValue(statusResponseRaw[66]);
    HeatMode._updateValue(statusResponseRaw[67]);
    PumpIdleTimer._updateValue(statusResponseRaw[68]);
    PumpRunTimer._updateValue(statusResponseRaw[69]);
    AdtPoolHys._updateValue(statusResponseRaw[70]);
    AdtHeaterHys._updateValue(statusResponseRaw[71]);
    Power._updateValue(statusResponseRaw[72]);
    Power_kWh._updateValue(statusResponseRaw[73]);
    Power_Today._updateValue(statusResponseRaw[74]);
    Power_Yesterday._updateValue(statusResponseRaw[75]);
    ThermalCutOut._updateValue(statusResponseRaw[76]);
    Test_D1._updateValue(statusResponseRaw[77]);
    Test_D2._updateValue(statusResponseRaw[78]);
    Test_D3._updateValue(statusResponseRaw[79]);
    ElementHeatSourceOffset._updateValue(statusResponseRaw[80]);
    Frequency._updateValue(statusResponseRaw[81]);
    HPHeatSourceOffset_Heat._updateValue(statusResponseRaw[82]);
    HPHeatSourceOffset_Cool._updateValue(statusResponseRaw[83]);
    HeatSourceOffTime._updateValue(statusResponseRaw[84]);
    Vari_Speed._updateValue(statusResponseRaw[86]);
    Vari_Percent._updateValue(statusResponseRaw[87]);
    Vari_Mode._updateValue(statusResponseRaw[85]);
    
   #pragma region R5
    //R5
    // Unknown encoding - TouchPad2.updateValue();
    // Unknown encoding - TouchPad1.updateValue();
    RB_TP_Pump1._updateValue(statusResponseRaw[110]);
    RB_TP_Pump2._updateValue(statusResponseRaw[111]);
    RB_TP_Pump3._updateValue(statusResponseRaw[112]);
    RB_TP_Pump4._updateValue(statusResponseRaw[113]);
    RB_TP_Pump4._updateValue(statusResponseRaw[114]);
    //RB_TP_Blower.updateValue(statusResponseRaw[101]);
    //RB_TP_Light.updateValue(statusResponseRaw[102]);
    RB_TP_Auto._updateValue(statusResponseRaw[105]);
    RB_TP_Heater._updateValue(statusResponseRaw[104]);
    RB_TP_Ozone._updateValue(statusResponseRaw[103]);
    RB_TP_Sleep._updateValue(statusResponseRaw[102]);
    WTMP._updateValue(statusResponseRaw[107]);
    CleanCycle._updateValue(statusResponseRaw[108]);
    #pragma endregion

    //R6
    VARIValue._updateValue(statusResponseRaw[121]);
    LBRTValue._updateValue(statusResponseRaw[122]);
    CurrClr._updateValue(statusResponseRaw[123]);
    ColorMode._updateValue(statusResponseRaw[124]);
    LSPDValue._updateValue(statusResponseRaw[125]);
    FiltSetHrs._updateValue(statusResponseRaw[126]);
    FiltBlockHrs._updateValue(statusResponseRaw[127]);
    STMP._updateValue(statusResponseRaw[128]);
    L_24HOURS._updateValue(statusResponseRaw[129]);
    PSAV_LVL._updateValue(statusResponseRaw[130]);
    PSAV_BGN._updateValue(statusResponseRaw[131]);
    PSAV_END._updateValue(statusResponseRaw[132]);
    L_1SNZ_DAY._updateValue(statusResponseRaw[133]);
    L_2SNZ_DAY._updateValue(statusResponseRaw[134]);
    L_1SNZ_BGN._updateValue(statusResponseRaw[135]);
    L_2SNZ_BGN._updateValue(statusResponseRaw[136]);
    L_1SNZ_END._updateValue(statusResponseRaw[137]);
    L_2SNZ_END._updateValue(statusResponseRaw[138]);
    DefaultScrn._updateValue(statusResponseRaw[139]);
    TOUT._updateValue(statusResponseRaw[140]);
    VPMP._updateValue(statusResponseRaw[141]);
    HIFI._updateValue(statusResponseRaw[142]);
    BRND._updateValue(statusResponseRaw[143]);
    PRME._updateValue(statusResponseRaw[144]);
    ELMT._updateValue(statusResponseRaw[145]);
    TYPE._updateValue(statusResponseRaw[146]);
    GAS._updateValue(statusResponseRaw[147]);
    //R7
    WCLNTime._updateValue(statusResponseRaw[151]);
    // The following 2 may be reversed
    TemperatureUnits._updateValue(statusResponseRaw[153]);
    OzoneOff._updateValue(statusResponseRaw[152]);
    Ozone24._updateValue(statusResponseRaw[154]);
    // The following 2 may be reversed
    Circ24._updateValue(statusResponseRaw[156]);
    CJET._updateValue(statusResponseRaw[155]);
    VELE._updateValue(statusResponseRaw[167]);
    StartDD._updateValue(statusResponseRaw[157]);
    StartMM._updateValue(statusResponseRaw[158]);
    StartYY._updateValue(statusResponseRaw[159]);
    V_Max._updateValue(statusResponseRaw[160]);
    V_Min._updateValue(statusResponseRaw[161]);
    V_Max_24._updateValue(statusResponseRaw[162]);
    V_Min_24._updateValue(statusResponseRaw[163]);
    CurrentZero._updateValue(statusResponseRaw[164]);
    CurrentAdjust._updateValue(statusResponseRaw[165]);
    VoltageAdjust._updateValue(statusResponseRaw[166]);
    Ser1._updateValue(statusResponseRaw[168]);
    Ser2._updateValue(statusResponseRaw[169]);
    Ser3._updateValue(statusResponseRaw[170]);
    VMAX._updateValue(statusResponseRaw[171]);
    AHYS._updateValue(statusResponseRaw[172]);
    HUSE._updateValue(statusResponseRaw[173]);
    HELE._updateValue(statusResponseRaw[174]);
    HPMP._updateValue(statusResponseRaw[175]);
    PMIN._updateValue(statusResponseRaw[176]);
    PFLT._updateValue(statusResponseRaw[177]);
    PHTR._updateValue(statusResponseRaw[178]);
    PMAX._updateValue(statusResponseRaw[179]);

    //R9
    F1_HR._updateValue(statusResponseRaw[185]);
    F1_Time._updateValue(statusResponseRaw[186]);
    F1_ER._updateValue(statusResponseRaw[187]);
    F1_I._updateValue(statusResponseRaw[188]);
    F1_V._updateValue(statusResponseRaw[189]);
    F1_PT._updateValue(statusResponseRaw[190]);
    F1_HT._updateValue(statusResponseRaw[191]);
    F1_CT._updateValue(statusResponseRaw[192]);
    F1_PU._updateValue(statusResponseRaw[193]);
    F1_VE._updateValue(statusResponseRaw[194]);
    F1_ST._updateValue(statusResponseRaw[195]);
    //RA
    F2_HR._updateValue(statusResponseRaw[199]);
    F2_Time._updateValue(statusResponseRaw[200]);
    F2_ER._updateValue(statusResponseRaw[201]);
    F2_I._updateValue(statusResponseRaw[202]);
    F2_V._updateValue(statusResponseRaw[203]);
    F2_PT._updateValue(statusResponseRaw[204]);
    F2_HT._updateValue(statusResponseRaw[205]);
    F2_CT._updateValue(statusResponseRaw[206]);
    F2_PU._updateValue(statusResponseRaw[207]);
    F2_VE._updateValue(statusResponseRaw[208]);
    F2_ST._updateValue(statusResponseRaw[209]);
    //RB
    F3_HR._updateValue(statusResponseRaw[213]);
    F3_Time._updateValue(statusResponseRaw[214]);
    F3_ER._updateValue(statusResponseRaw[215]);
    F3_I._updateValue(statusResponseRaw[216]);
    F3_V._updateValue(statusResponseRaw[217]);
    F3_PT._updateValue(statusResponseRaw[218]);
    F3_HT._updateValue(statusResponseRaw[219]);
    F3_CT._updateValue(statusResponseRaw[220]);
    F3_PU._updateValue(statusResponseRaw[221]);
    F3_VE._updateValue(statusResponseRaw[222]);
    F3_ST._updateValue(statusResponseRaw[223]);
    //RC
    //Outlet_Heater.updateValue(statusResponseRaw[]);
    //Outlet_Circ.updateValue(statusResponseRaw[]);
    //Outlet_Sanitise.updateValue(statusResponseRaw[]);
    //Outlet_Pump1.updateValue(statusResponseRaw[]);
    //Outlet_Pump2.updateValue(statusResponseRaw[]);
    //Outlet_Pump4.updateValue(statusResponseRaw[]);
    //Outlet_Pump5.updateValue(statusResponseRaw[]);
    Outlet_Blower._updateValue(statusResponseRaw[235]);
    //RE
    HP_Present._updateValue(statusResponseRaw[242]);
    //HP_FlowSwitch.updateValue(statusResponseRaw[]);
    //HP_HighSwitch.updateValue(statusResponseRaw[]);
    //HP_LowSwitch.updateValue(statusResponseRaw[]);
    //HP_CompCutOut.updateValue(statusResponseRaw[]);
    //HP_ExCutOut.updateValue(statusResponseRaw[]);
    //HP_D1.updateValue(statusResponseRaw[]);
    //HP_D2.updateValue(statusResponseRaw[]);
    //HP_D3.updateValue(statusResponseRaw[]);
    HP_Ambient._updateValue(statusResponseRaw[251]);
    HP_Condensor._updateValue(statusResponseRaw[252]);
    HP_Compressor_State._updateValue(statusResponseRaw[253]);
    HP_Fan_State._updateValue(statusResponseRaw[254]);
    HP_4W_Valve._updateValue(statusResponseRaw[255]);
    HP_Heater_State._updateValue(statusResponseRaw[256]);
    HP_State._updateValue(statusResponseRaw[257]);
    HP_Mode._updateValue(statusResponseRaw[258]);
    HP_Defrost_Timer._updateValue(statusResponseRaw[259]);
    HP_Comp_Run_Timer._updateValue(statusResponseRaw[260]);
    HP_Low_Temp_Timer._updateValue(statusResponseRaw[261]);
    HP_Heat_Accum_Timer._updateValue(statusResponseRaw[262]);
    HP_Sequence_Timer._updateValue(statusResponseRaw[263]);
    HP_Warning._updateValue(statusResponseRaw[264]);
    FrezTmr._updateValue(statusResponseRaw[265]);
    DBGN._updateValue(statusResponseRaw[266]);
    DEND._updateValue(statusResponseRaw[267]);
    DCMP._updateValue(statusResponseRaw[268]);
    DMAX._updateValue(statusResponseRaw[269]);
    DELE._updateValue(statusResponseRaw[270]);
    DPMP._updateValue(statusResponseRaw[271]);
    //CMAX.updateValue(statusResponseRaw[]);
    //HP_Compressor.updateValue(statusResponseRaw[]);
    //HP_Pump_State.updateValue(statusResponseRaw[]);
    //HP_Status.updateValue(statusResponseRaw[]);

    #pragma region RG
    Pump1InstallState._updateValue(statusResponseRaw[280]);
    Pump2InstallState._updateValue(statusResponseRaw[281]);
    Pump3InstallState._updateValue(statusResponseRaw[282]);
    Pump4InstallState._updateValue(statusResponseRaw[283]);
    Pump5InstallState._updateValue(statusResponseRaw[284]);
    Pump1OkToRun._updateValue(statusResponseRaw[274]);
    Pump2OkToRun._updateValue(statusResponseRaw[275]);
    Pump3OkToRun._updateValue(statusResponseRaw[276]);
    Pump4OkToRun._updateValue(statusResponseRaw[277]);
    Pump5OkToRun._updateValue(statusResponseRaw[278]);
    LockMode._updateValue(statusResponseRaw[285]);

#pragma endregion

};