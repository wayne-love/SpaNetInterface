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
        static float _updateS2Idiv100(String s);
        static int _updateS2I(String s);
        static bool _updateS2B(String s);
        static String _updateS2S(String s);

    public:
        /// @brief Init SNI to read from stream p. This stream needs to be started and configured baud 38400/8N1.
        /// @param p 
        SpaNetInterface(Stream &p);

        /// @brief Init SNI and user Serial2 for comms.  Serial 2 DOES NOT need to be configured.
        SpaNetInterface();

        ~SpaNetInterface();

        /// @brief Read from serial interface, expect it to contain return from RF command
        /// @return true if successful read, false if there was a corrupted read
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

        /// @brief Mains current draw (A)
        Attribute<float> MainsCurrent;
        /// @brief Mains voltage (V)
        Attribute<int> MainsVoltage;
        /// @brief Internal case temperature ('C)
        Attribute<int> CaseTemperature;
        /// @brief 12v port current (mA)
        Attribute<int> PortCurrent;
        //TODO - Reg 6 unknown data
        //TODO - Need to implement clock date/time Regs 7 to 12
        /// @brief Heater temperature ('C)
        Attribute<float> HeaterTemperature;
        /// @brief Pool temperature ('C)
        Attribute<float> PoolTemperature;
        /// @brief Water present
        Attribute<bool> WaterPresent;
        //TODO - Reg 16 unknown
        /// @brief AwakeMinutesRemaining (min)
        Attribute<int> AwakeMinutesRemaining;
        /// @brief FiltPumpRunTimeTotal (min)
        Attribute<int> FiltPumpRunTimeTotal;
        /// @brief FiltPumpReqMins (sec)
        //TODO - the value here does not match the value in the snampshot data (1442 != 2:00)
        Attribute<int> FiltPumpReqMins; 
        /// @brief LoadTimeOut (sec)
        Attribute<int> LoadTimeOut;
        /// @brief HourMeter (sec)
        Attribute<float> HourMeter;
        /// @brief Relay1 (?)
        Attribute<int> Relay1;
        /// @brief Relay2 (?)
        Attribute<int> Relay2;
        /// @brief Relay3 (?)
        Attribute<int> Relay3;
        /// @brief Relay4 (?)
        Attribute<int> Relay4;
        /// @brief Relay5 (?)
        Attribute<int> Relay5;
        /// @brief Relay6 (?)
        Attribute<int> Relay6;
        /// @brief Relay7 (?)
        Attribute<int> Relay7;
        /// @brief Relay8 (?)
        Attribute<int> Relay8;
        /// @brief Relay9 (?)
        Attribute<int> Relay9;
        //TODO - Reg 31 unknown data
        /// @brief Current limit (A)
        Attribute<int> CLMT;
        /// @brief Power phases in use
        Attribute<int> PHSE;
        /// @brief LLM1
        Attribute<int> LLM1;
        /// @brief LLM2
        Attribute<int> LLM2;
        /// @brief LLM3
        Attribute<int> LLM3;
        /// @brief Software version
        Attribute<String> SVER;
        /// @brief Model
        Attribute<String> Model;
        /// @brief SerialNo1
        Attribute<String> SerialNo1;
        /// @brief SerialNo2
        Attribute<String> SerialNo2;
        /// @brief Dipswitch 1
        Attribute<bool> D1;
        /// @brief Dipswitch 2
        Attribute<bool> D2;
        /// @brief Dipswitch 3
        Attribute<bool> D3;
        /// @brief Dipswitch 4
        Attribute<bool> D4;
        /// @brief Dipswitch 5
        Attribute<bool> D5;
        /// @brief Dipswitch 6
        Attribute<bool> D6;
        /// @brief Pump
        Attribute<String> Pump;
        /// @brief Load shed services
        Attribute<int> LS;
        /// @brief HV
        Attribute<bool> HV;
        /// @brief MR / name clash with MR constant from specreg.h
        Attribute<int> SniMR;
        /// @brief Status (Filtering, etc)
        Attribute<String> Status;
        /// @brief PrimeCount
        Attribute<int> PrimeCount;
        /// @brief EC
        Attribute<float> EC;
        /// @brief HAMB
        Attribute<int> HAMB;
        /// @brief HCON
        Attribute<int> HCON;
        /// @brief HV_2
        //TODO - This could also be reg 59....
        Attribute<bool> HV_2;
        Attribute<String> Mode;
        Attribute<int> Ser1_Timer;
        Attribute<int> Ser2_Timer;
        Attribute<int> Ser3_Timer;
        // 1 = Standby
        // 2 = HeatMix
        Attribute<int> HeatMode;
        // assume sec
        Attribute<int> PumpIdleTimer;
        Attribute<int> PumpRunTimer;
        Attribute<float> AdtPoolHys;
        Attribute<float> AdtHeaterHys;
        // (W)
        Attribute<float> Power;
        Attribute<float> Power_kWh;
        // (kWh)
        Attribute<float> Power_Today;
        // (kWh)
        Attribute<float> Power_Yesterday;
        // 0 = ok
        Attribute<int> ThermalCutOut;
        Attribute<int> Test_D1;
        Attribute<int> Test_D2;
        Attribute<int> Test_D3;
        Attribute<float> ElementHeatSourceOffset;
        Attribute<int> Frequency;
        Attribute<float> HPHeatSourceOffset_Heat;
        // 100 = 0!?
        Attribute<float> HPHeatSourceOffset_Cool;
        Attribute<int> HeatSourceOffTime;
        Attribute<int> Vari_Speed;
        Attribute<int> Vari_Percent;
        // 5 = Filt
        // 4 = Off
        Attribute<int> Vari_Mode;
        // Unknown encoding - Attribute<int> TouchPad2;
        // Unknown encoding - Attribute<int> TouchPad1;
        Attribute<int> RB_TP_Pump1;
        Attribute<int> RB_TP_Pump2;
        Attribute<int> RB_TP_Pump3;
        Attribute<int> RB_TP_Pump4;
        Attribute<int> RB_TP_Blower;
        Attribute<int> RB_TP_Light;
        Attribute<int> RB_TP_Auto;
        Attribute<int> RB_TP_Heater;
        Attribute<int> RB_TP_Ozone;
        Attribute<int> RB_TP_Sleep;
        /// @brief Water temperature ('C)
        Attribute<float> WTMP;

        Attribute<int> VARIValue;
        Attribute<int> LBRTValue;
        Attribute<int> CurrClr;
        Attribute<int> ColorMode;
        Attribute<int> LSPDValue;
        Attribute<int> FiltSetHrs;
        Attribute<int> FiltBlockHrs;
        /// @brief Water temperature set point ('C)
        Attribute<float> STMP;
        // 1 = 12 hrs
        Attribute<int> L_24HOURS;
        Attribute<bool> PSAV_LVL;
        // 3584 = 14:00 (1hr = 256)
        Attribute<int> PSAV_BGN;
        // 5120 = 20:00
        Attribute<int> PSAV_END;
        // 127 = all week (bit encoding?)
        Attribute<int> L_1SNZ_DAY;
        // 128 = disabled
        Attribute<int> L_2SNZ_DAY;
        Attribute<int> L_1SNZ_BGN;
        Attribute<int> L_2SNZ_BGN;
        Attribute<int> L_1SNZ_END;
        Attribute<int> L_2SNZ_END;
        /// @brief Default screen for control panels
        ///
        /// 0 = WTPM
        Attribute<int> DefaultScrn;
        Attribute<int> TOUT;
        Attribute<bool> VPMP;
        Attribute<bool> HIFI;
        /// @brief BRND
        ///
        /// 2 = VORT
        Attribute<int> BRND;
        /// @brief PRME
        ///
        /// 0 = 10secF
        Attribute<int> PRME;
        Attribute<int> ELMT;
        /// @brief TYPE
        ///
        /// 3 = SV3
        Attribute<int> TYPE;
        Attribute<int> GAS;
        // R7
        /// @brief Daily clean cycle start time (1 hr = 256, 2pm = 3584)
        Attribute<int> WCLNTime;
        /// @brief Use 'F instead of 'C as the temp. UMO
        Attribute<bool> TemperatureUnits;
        Attribute<bool> OzoneOff;
        Attribute<int> Ozone24;
        Attribute<bool> Circ24;
        Attribute<bool> CJET;
        /// @brief VELE
        ///
        /// This may be mapped wrong to the wrong register
        /// 3 = Vari
        Attribute<int> VELE;
        /// @brief Date of comissioning
        Attribute<int> StartDD;
        /// @brief Month of comissioning
        Attribute<int> StartMM;
        /// @brief Year of comissioning
        Attribute<int> StartYY;
        /// @brief Highest voltage ever recorded (V)
        Attribute<int> V_Max;
        /// @brief Lowest voltage ever recorded (V)
        Attribute<int> V_Min;
        /// @brief Highest voltage in past 24 hrs (V)
        Attribute<int> V_Max_24;
        /// @brief Lowest voltage in past 24 hrs (V)
        Attribute<int> V_Min_24;
        Attribute<int> CurrentZero;
        Attribute<float> CurrentAdjust;
        Attribute<float> VoltageAdjust;
        Attribute<int> Ser1;
        Attribute<int> Ser2;
        Attribute<int> Ser3;
        Attribute<int> VMAX;
        Attribute<float> AHYS;
        /// @brief HUSE
        ///
        /// 1 = Off
        Attribute<int> HUSE;
        Attribute<bool> HELE;
        /// @brief HPMP
        ///
        /// 1 = HEAT
        Attribute<int> HPMP;
        Attribute<int> PMIN;
        Attribute<int> PFLT;
        Attribute<int> PHTR;
        Attribute<int> PMAX;
        //R9
        /// @brief Fault runtime occurance (hrs)
        Attribute<float> F1_HR;
        /// @brief Fault time of day occurance
        Attribute<int> F1_Time;
        /// @brief Fault error codes
        ///
        /// 6 = ER612VOverload - High current detected on 12v line
        Attribute<int> F1_ER;
        /// @brief Supply current draw at time of error (A)
        Attribute<float> F1_I;
        /// @brief Supply voltage at time of error (V)
        Attribute<int> F1_V;
        /// @brief Pool temperature at time of error ('C)
        Attribute<float> F1_PT;
        /// @brief Heater temperature at time of error ('C)
        Attribute<float> F1_HT;
        Attribute<float> F1_CT;
        Attribute<int> F1_PU;
        Attribute<bool> F1_VE;
        /// @brief Heater setpoint at time of error ('C)
        Attribute<float> F1_ST;
        //RA
        /// @brief Fault runtime occurance (hrs)
        Attribute<float> F2_HR;
        /// @brief Fault time of day occurance
        Attribute<int> F2_Time;
        /// @brief Fault error codes
        ///
        /// 6 = ER612VOverload - High current detected on 12v line
        Attribute<int> F2_ER;
        /// @brief Supply current draw at time of error (A)
        Attribute<float> F2_I;
        /// @brief Supply voltage at time of error (V)
        Attribute<int> F2_V;
        /// @brief Pool temperature at time of error ('C)
        Attribute<float> F2_PT;
        /// @brief Heater temperature at time of error ('C)
        Attribute<float> F2_HT;
        Attribute<float> F2_CT;
        Attribute<int> F2_PU;
        Attribute<bool> F2_VE;
        /// @brief Heater setpoint at time of error ('C)
        Attribute<float> F2_ST;
        //RB
        /// @brief Fault runtime occurance (hrs)
        Attribute<float> F3_HR;
        /// @brief Fault time of day occurance
        Attribute<int> F3_Time;
        /// @brief Fault error codes
        ///
        /// 6 = ER612VOverload - High current detected on 12v line
        Attribute<int> F3_ER;
        /// @brief Supply current draw at time of error (A)
        Attribute<float> F3_I;
        /// @brief Supply voltage at time of error (V)
        Attribute<int> F3_V;
        /// @brief Pool temperature at time of error ('C)
        Attribute<float> F3_PT;
        /// @brief Heater temperature at time of error ('C)
        Attribute<float> F3_HT;
        Attribute<float> F3_CT;
        Attribute<int> F3_PU;
        Attribute<bool> F3_VE;
        /// @brief Heater setpoint at time of error ('C)
        Attribute<float> F3_ST;
        //RC
        // Encoding of the RC registers is not obvious
        //Attribute<bool> Outlet_Heater;
        //Attribute<bool> Outlet_Circ;
        //Attribute<bool> Outlet_Sanitise;
        //Attribute<bool> Outlet_Pump1;
        //Attribute<bool> Outlet_Pump2;
        //Attribute<bool> Outlet_Pump4;
        //Attribute<bool> Outlet_Pump5;
        //Attribute<bool> Outlet_Blower;
        //RE
        /// @brief Heatpump installed / interface version
        Attribute<int> HP_Present;
        // Encoding of these registers is not clear
        //Attribute<bool> HP_FlowSwitch;
        //Attribute<bool> HP_HighSwitch;
        //Attribute<bool> HP_LowSwitch;
        //Attribute<bool> HP_CompCutOut;
        //Attribute<bool> HP_ExCutOut;
        //Attribute<bool> HP_D1;
        //Attribute<bool> HP_D2;
        //Attribute<bool> HP_D3;
        /// @brief Ambient air temperature ('C)
        Attribute<int> HP_Ambient;
        /// @brief Compressor temperature ('C)
        Attribute<int> HP_Condensor;
        /// @brief Compressor running
        Attribute<bool> HP_Compressor_State;
        /// @brief Fan running
        Attribute<bool> HP_Fan_State;
        Attribute<bool> HP_4W_Valve;
        Attribute<bool> HP_Heater_State;
        /// @brief Heatpump state
        ///
        /// 0 = Standby
        Attribute<int> HP_State;
        /// @brief Heatpump mode
        ///
        /// 1 = Heat
        Attribute<int> HP_Mode;
        Attribute<int> HP_Defrost_Timer;
        Attribute<int> HP_Comp_Run_Timer;
        Attribute<int> HP_Low_Temp_Timer;
        Attribute<int> HP_Heat_Accum_Timer;
        Attribute<int> HP_Sequence_Timer;
        Attribute<int> HP_Warning;
        Attribute<int> FrezTmr;
        Attribute<int> DBGN;
        Attribute<int> DEND;
        Attribute<int> DCMP;
        Attribute<int> DMAX;
        Attribute<int> DELE;
        Attribute<int> DPMP;
        //Attribute<int> CMAX;
        //Attribute<int> HP_Compressor;
        //Attribute<int> HP_Pump_State;
        //Attribute<int> HP_Status;




};


#endif