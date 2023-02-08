#ifndef SPANETPROPERTIES_H
#define SPANETPROPERTIES_H

#include <Arduino.h>
#include <RemoteDebug.h>
#include <time.h>



#ifndef DEBUG_
#define DEBUG_
RemoteDebug Debug;
#endif

template <typename T>
class Property {
    private:
        T _value;
        void (*_callback)(T) = nullptr;

    public:
        T getValue() { return _value; }
        void update_Value(T){
            T oldvalue = _value;
            _value = newval;
            if (_callback) && (oldvalue != newval) {
                _callback(_value);
            }
        };
        void setCallback(void (*c)(T)) { _callback = c; };
        void clearCallback() { _callback = nullptr; };
};

/// @brief represents the properties of the spa.
class SpaNetProperties {
    private:
        #pragma region R2
        /// @brief Mains current draw (A)
        Property<float> MainsCurrent;
        /// @brief Mains voltage (V)
        Property<int> MainsVoltage;
        /// @brief Internal case temperature ('C)
        Property<int> CaseTemperature;
        /// @brief 12v port current (mA)
        Property<int> PortCurrent;
        /// @brief Current time on Spa RTC
        //TODO #1 this should be settable.
        Property<time_t> SpaTime;
        /// @brief Heater temperature ('C)
        Property<float> HeaterTemperature;
        /// @brief Pool temperature ('C). Note this seems to return rubbish most of the time.
        Property<float> PoolTemperature;
        /// @brief Water present
        Property<bool> WaterPresent;
        /// @brief AwakeMinutesRemaining (min)
        Property<int> AwakeMinutesRemaining;
        /// @brief FiltPumpRunTimeTotal (min)
        Property<int> FiltPumpRunTimeTotal;
        /// @brief FiltPumpReqMins
        //TODO - the value here does not match the value in the snampshot data (1442 != 2:00)
        Property<int> FiltPumpReqMins; 
        /// @brief LoadTimeOut (sec)
        Property<int> LoadTimeOut;
        /// @brief HourMeter (hours)
        Property<float> HourMeter;
        /// @brief Relay1 (?)
        Property<int> Relay1;
        /// @brief Relay2 (?)
        Property<int> Relay2;
        /// @brief Relay3 (?)
        Property<int> Relay3;
        /// @brief Relay4 (?)
        Property<int> Relay4;
        /// @brief Relay5 (?)
        Property<int> Relay5;
        /// @brief Relay6 (?)
        Property<int> Relay6;
        /// @brief Relay7 (?)
        Property<int> Relay7;
        /// @brief Relay8 (?)
        Property<int> Relay8;
        /// @brief Relay9 (?)
        Property<int> Relay9;
        #pragma endregion
        #pragma region R3
        //R3
        /// @brief Current limit (A)
        Property<int> CLMT;
        /// @brief Power phases in use
        Property<int> PHSE;
        /// @brief Load limit - Phase 1
        ///
        /// Number of services that can be active on this phase before the keypad stops new services from starting.
        /// See SV-Series-OEM-Install-Manual.pdf page 20.
        Property<int> LLM1;
        /// @brief Load limit - Phase 2
        ///
        /// Number of services that can be active on this phase before the keypad stops new services from starting.
        /// See SV-Series-OEM-Install-Manual.pdf page 20.
        Property<int> LLM2;
        /// @brief Load limit - Phase 3
        ///
        /// Number of services that can be active on this phase before the keypad stops new services from starting.
        /// See SV-Series-OEM-Install-Manual.pdf page 20.
        Property<int> LLM3;
        /// @brief Software version
        Property<String> SVER;
        /// @brief Model
        Property<String> Model;
        /// @brief SerialNo1
        Property<String> SerialNo1;
        /// @brief SerialNo2
        Property<String> SerialNo2;
        /// @brief Dipswitch 1
        Property<bool> D1;
        /// @brief Dipswitch 2
        Property<bool> D2;
        /// @brief Dipswitch 3
        Property<bool> D3;
        /// @brief Dipswitch 4
        Property<bool> D4;
        /// @brief Dipswitch 5
        Property<bool> D5;
        /// @brief Dipswitch 6
        Property<bool> D6;
        /// @brief Pump
        Property<String> Pump;
        /// @brief Load shed count
        ///
        /// Number of services active at which the heater will turn itself off.
        Property<int> LS;
        /// @brief HV
        Property<bool> HV;
        /// @brief MR / name clash with MR constant from specreg.h
        Property<int> SnpMR;
        /// @brief Status (Filtering, etc)
        Property<String> Status;
        /// @brief PrimeCount
        Property<int> PrimeCount;
        /// @brief Heat element current draw (A)
        Property<float> EC;
        /// @brief HAMB
        Property<int> HAMB;
        /// @brief HCON
        Property<int> HCON;
        /* Unclear encoding of HV_2
        /// @brief HV_2
        Property<bool> HV_2;
        */
        #pragma endregion
        #pragma region R4
        //R4
        /// @brief Operation mode
        ///
        /// One of NORM, ECON, AWAY, WEEK
        Property<String> Mode;
        /// @brief Service Timer 1 (wks) 0 = off
        Property<int> Ser1_Timer;
        /// @brief Service Timer 2 (wks) 0 = off
        Property<int> Ser2_Timer;
        /// @brief Service Timer 3 (wks) 0 = off
        Property<int> Ser3_Timer;
        /// @brief Heat mode
        ///
        /// 1 = Standby
        /// 2 = HeatMix
        Property<int> HeatMode;
        /// @brief Pump idle time (sec)
        Property<int> PumpIdleTimer;
        /// @brief Pump run time (sec)
        Property<int> PumpRunTimer;
        /// @brief Pool temperature adaptive hysteresis
        Property<float> AdtPoolHys;
        /// @brief  Heater temperature adaptive hysteresis
        Property<float> AdtHeaterHys;
        // (W)
        Property<float> Power;
        Property<float> Power_kWh;
        // (kWh)
        Property<float> Power_Today;
        // (kWh)
        Property<float> Power_Yesterday;
        // 0 = ok
        Property<int> ThermalCutOut;
        Property<int> Test_D1;
        Property<int> Test_D2;
        Property<int> Test_D3;
        Property<float> ElementHeatSourceOffset;
        Property<int> Frequency;
        Property<float> HPHeatSourceOffset_Heat;
        // 100 = 0!?
        Property<float> HPHeatSourceOffset_Cool;
        Property<int> HeatSourceOffTime;
        Property<int> Vari_Speed;
        Property<int> Vari_Percent;
        // 5 = Filt
        // 4 = Off
        /// @brief Varible speed mode
        ///
        /// 5 = Filtering, 4 = Off
        Property<int> Vari_Mode;
        #pragma endregion
        #pragma region R5
        //R5
        // Unknown encoding - Attribute<int> TouchPad2;
        // Unknown encoding - Attribute<int> TouchPad1;
        /// @brief Pump 1 state
        ///
        /// 0 = off, 1 = running, 4 = auto
        Property<int> RB_TP_Pump1;
        /// @brief Pump 2 state
        ///
        /// 0 = off, 1 = running, 4 = auto
        Property<int> RB_TP_Pump2;
        /// @brief Pump 3 state
        ///
        /// 0 = off, 1 = running, 4 = auto
        Property<int> RB_TP_Pump3;
        /// @brief Pump 4 state
        ///
        /// 0 = off, 1 = running, 4 = auto
        Property<int> RB_TP_Pump4;
        /// @brief Pump 5 state
        ///
        /// 0 = off, 1 = running, 4 = auto
        Property<int> RB_TP_Pump5;
        Property<int> RB_TP_Blower;
        Property<int> RB_TP_Light;
        /// @brief Auto enabled
        ///
        /// True when auto enabled
        Property<bool> RB_TP_Auto;
        /// @brief Heating running
        ///
        /// True when heating/cooling active
        Property<bool> RB_TP_Heater;
        /// @brief Cleaning (UV/Ozone running)
        ///
        /// True when Ozone/UV is cleaning spa.
        Property<bool> RB_TP_Ozone;
        /// @brief Sleeping
        ///
        /// True when spa is sleeping due to sleep timer
        Property<bool> RB_TP_Sleep;
        /// @brief Water temperature ('C)
        Property<float> WTMP;
        /// @brief Clean cycle running
        ///
        /// True when a clean cycle is running
        Property<bool> CleanCycle;
        #pragma endregion     
        #pragma region R6
        //R6
        /// @brief Blower variable speed
        ///
        /// min 1, max 5
        Property<int> VARIValue;
        /// @brief Lights brightness
        ///
        /// min 1, max 5
        Property<int> LBRTValue;
        /// @brief Light colour
        ///
        /// min 0, max 31
        Property<int> CurrClr;
        /// @brief Lights mode
        ///
        /// 0 = white, 1 = colour, 2 = step, 3 = fade, 4 = party
        Property<int> ColorMode;
        /// @brief Light effect speed
        ///
        /// min 1, max 5
        Property<int> LSPDValue;
        /// @brief Filter run time (in hours) per block
        Property<int> FiltSetHrs;
        /// @brief Filter block duration (hours)
        Property<int> FiltBlockHrs;
        /// @brief Water temperature set point ('C)
        Property<float> STMP;
        // 1 = 12 hrs
        Property<int> L_24HOURS;
        /// @brief Power save level
        ///
        /// 0 = off, 1 = low, 2 = high
        Property<int> PSAV_LVL;
        /// @brief Peak power start time
        ///
        /// Formula h*256+m (ie: for 20:00, integer will be 20*256+0 = 5120; for 13:47, integer will be 13*256+47 = 3375)
        Property<int> PSAV_BGN;
        /// @brief Peak power end time
        ///
        /// Formula h*256+m (ie: for 20:00, integer will be 20*256+0 = 5120; for 13:47, integer will be 13*256+47 = 3375)
        Property<int> PSAV_END;
        /// @brief Sleep timer 1
        ///
        /// 128 = off, 127 = every day, 96 = weekends, 31 = weekdays
        Property<int> L_1SNZ_DAY;
        /// @brief Sleep timer 2
        ///
        /// 128 = off, 127 = every day, 96 = weekends, 31 = weekdays
        Property<int> L_2SNZ_DAY;
        /// @brief Sleep time 1 start time
        ///
        /// Formula h*256+m (ie: for 20:00, integer will be 20*256+0 = 5120; for 13:47, integer will be 13*256+47 = 3375)
        Property<int> L_1SNZ_BGN;
        /// @brief Sleep time 2 start time
        ///
        /// Formula h*256+m (ie: for 20:00, integer will be 20*256+0 = 5120; for 13:47, integer will be 13*256+47 = 3375)
        Property<int> L_2SNZ_BGN;
        /// @brief Sleep time 1 end time
        ///
        /// Formula h*256+m (ie: for 20:00, integer will be 20*256+0 = 5120; for 13:47, integer will be 13*256+47 = 3375)
        Property<int> L_1SNZ_END;
        /// @brief Sleep time 1 end time
        ///
        /// Formula h*256+m (ie: for 20:00, integer will be 20*256+0 = 5120; for 13:47, integer will be 13*256+47 = 3375)
        Property<int> L_2SNZ_END;
        /// @brief Default screen for control panels
        ///
        /// 0 = WTPM
        Property<int> DefaultScrn;
        /// @brief Time out duration (min)
        ///
        /// Time in min before pump and blower time out (min 10, max 30)
        Property<int> TOUT;
        Property<bool> VPMP;
        Property<bool> HIFI;
        /// @brief BRND
        ///
        /// 2 = VORT
        Property<int> BRND;
        /// @brief PRME
        ///
        /// 0 = 10secF
        Property<int> PRME;
        Property<int> ELMT;
        /// @brief TYPE
        ///
        /// 3 = SV3
        Property<int> TYPE;
        Property<int> GAS;
        #pragma endregion
        #pragma region R7
        // R7
        /// @brief Daily clean cycle start time
        ///
        /// Time with the formula h*256+m (ie: for 20:00, integer will be 20*256+0 = 5120; for 13:47, integer will be 13*256+47 = 3375)
        Property<int> WCLNTime;
        /// @brief Use 'F instead of 'C as the temp. UMO
        Property<bool> TemperatureUnits;
        Property<bool> OzoneOff;
        /// @brief Sanitiser 24 hrs
        ///
        /// True if sanitiser (ozone) power outlet on permanently, false if automatically controlled.
        /// See SV-Series-OEM-Install-Manual.pdf page 20.
        Property<bool> Ozone24;
        /// @brief Circulation pump 24hrs
        ///
        /// True if circulation pump is always on, false if automatically controlled.
        /// See SV-Series-OEM-Install-Manual.pdf page 20.
        Property<bool> Circ24;
        Property<bool> CJET;
        /// @brief Variable heat element operation
        ///
        /// If true allows variable power to be fed to the heating element.
        /// See SV-Series-OEM-Install-Manual.pdf page 19.
        Property<bool> VELE;
        /// @brief Date of comissioning
        Property<time_t> ComissionDate;
        /// @brief Highest voltage ever recorded (V)
        Property<int> V_Max;
        /// @brief Lowest voltage ever recorded (V)
        Property<int> V_Min;
        /// @brief Highest voltage in past 24 hrs (V)
        Property<int> V_Max_24;
        /// @brief Lowest voltage in past 24 hrs (V)
        Property<int> V_Min_24;
        Property<int> CurrentZero;
        Property<float> CurrentAdjust;
        Property<float> VoltageAdjust;
        Property<int> Ser1;
        Property<int> Ser2;
        Property<int> Ser3;
        /// @brief Variable heat element max power (A)
        ///
        /// Maximum current that the heat element is allowed to draw (between 3 and 25A)
        /// See SV-Series-OEM-Install-Manual.pdf page 19.
        Property<int> VMAX;
        /// @brief Adaptive Hysteresis
        ///
        /// Maximum adaptive hysteresis value (0=disabled).  See SV-Series-OEM-Install-Manual.pdf page 20.
        Property<float> AHYS;
        /// @brief HUSE
        ///
        /// 1 = Off
        Property<boolean> HUSE;
        /// @brief Heat pump active whilst spa is in use
        ///
        /// If false then when spa is in use then heat pump will not run to reduce noise levels
        /// See SV-Series-OEM-Install-Manual.pdf page 19.
        Property<bool> HELE;
        /// @brief Heatpump mode
        ///
        /// 0 = Auto, 1 = Heat, 2 = Cool, 3 = disabled
        Property<int> HPMP;
        /// @brief Varible pump minimum speed setting
        ///
        /// Min 20%, Max 100%
        /// See SV-Series-OEM-Install-Manual.pdf page 21.
        Property<int> PMIN;
        /// @brief Variable pump filtration speed setting
        ///
        /// Min 20%, Max 100%
        /// See SV-Series-OEM-Install-Manual.pdf page 21.
        Property<int> PFLT;
        /// @brief Varible pump heater speed setting
        ///
        /// Min 20%, Max 100%
        /// See SV-Series-OEM-Install-Manual.pdf page 21.
        Property<int> PHTR;
        /// @brief Varible pump maximum speed setting
        ///
        /// Maximum speed the varible pump will run at.
        /// Min 20%, Max 100%
        Property<int> PMAX;
        #pragma endregion
        #pragma region R9
        //R9
        /// @brief Fault runtime occurance (hrs)
        Property<float> F1_HR;
        /// @brief Fault time of day occurance
        Property<int> F1_Time;
        /// @brief Fault error codes
        ///
        /// 6 = ER612VOverload - High current detected on 12v line
        Property<int> F1_ER;
        /// @brief Supply current draw at time of error (A)
        Property<float> F1_I;
        /// @brief Supply voltage at time of error (V)
        Property<int> F1_V;
        /// @brief Pool temperature at time of error ('C)
        Property<float> F1_PT;
        /// @brief Heater temperature at time of error ('C)
        Property<float> F1_HT;
        Property<float> F1_CT;
        Property<int> F1_PU;
        Property<bool> F1_VE;
        /// @brief Heater setpoint at time of error ('C)
        Property<float> F1_ST;
        #pragma endregion
        #pragma region RA
        //RA
        /// @brief Fault runtime occurance (hrs)
        Property<float> F2_HR;
        /// @brief Fault time of day occurance
        Property<int> F2_Time;
        /// @brief Fault error codes
        ///
        /// 6 = ER612VOverload - High current detected on 12v line
        Property<int> F2_ER;
        /// @brief Supply current draw at time of error (A)
        Property<float> F2_I;
        /// @brief Supply voltage at time of error (V)
        Property<int> F2_V;
        /// @brief Pool temperature at time of error ('C)
        Property<float> F2_PT;
        /// @brief Heater temperature at time of error ('C)
        Property<float> F2_HT;
        Property<float> F2_CT;
        Property<int> F2_PU;
        Property<bool> F2_VE;
        /// @brief Heater setpoint at time of error ('C)
        Property<float> F2_ST;
        #pragma endregion
        #pragma region RB
        //RB
        /// @brief Fault runtime occurance (hrs)
        Property<float> F3_HR;
        /// @brief Fault time of day occurance
        Property<int> F3_Time;
        /// @brief Fault error codes
        ///
        /// 6 = ER612VOverload - High current detected on 12v line
        Property<int> F3_ER;
        /// @brief Supply current draw at time of error (A)
        Property<float> F3_I;
        /// @brief Supply voltage at time of error (V)
        Property<int> F3_V;
        /// @brief Pool temperature at time of error ('C)
        Property<float> F3_PT;
        /// @brief Heater temperature at time of error ('C)
        Property<float> F3_HT;
        Property<float> F3_CT;
        Property<int> F3_PU;
        Property<bool> F3_VE;
        /// @brief Heater setpoint at time of error ('C)
        Property<float> F3_ST;
        #pragma endregion
        #pragma region RC
        //RC
        // Encoding of the RC registers is not obvious
        //Attribute<bool> Outlet_Heater;
        //Attribute<bool> Outlet_Circ;
        //Attribute<bool> Outlet_Sanitise;
        //Attribute<bool> Outlet_Pump1;
        //Attribute<bool> Outlet_Pump2;
        //Attribute<bool> Outlet_Pump4;
        //Attribute<bool> Outlet_Pump5;
        /// @brief Blower status
        ///
        /// 0 = variable mode, 1 = ramp mode, 2 = off
        Property<int> Outlet_Blower;
        #pragma endregion
        #pragma region RE
        //RE
        /// @brief Heatpump installed / interface version
        Property<int> HP_Present;
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
        Property<int> HP_Ambient;
        /// @brief Compressor temperature ('C)
        Property<int> HP_Condensor;
        /// @brief Compressor running
        Property<bool> HP_Compressor_State;
        /// @brief Fan running
        Property<bool> HP_Fan_State;
        Property<bool> HP_4W_Valve;
        Property<bool> HP_Heater_State;
        /// @brief Heatpump state
        ///
        /// 0 = Standby
        Property<int> HP_State;
        /// @brief Heatpump mode
        ///
        /// 1 = Heat
        Property<int> HP_Mode;
        Property<int> HP_Defrost_Timer;
        Property<int> HP_Comp_Run_Timer;
        Property<int> HP_Low_Temp_Timer;
        Property<int> HP_Heat_Accum_Timer;
        Property<int> HP_Sequence_Timer;
        Property<int> HP_Warning;
        Property<int> FrezTmr;
        Property<int> DBGN;
        Property<int> DEND;
        Property<int> DCMP;
        Property<int> DMAX;
        Property<int> DELE;
        Property<int> DPMP;
        //Attribute<int> CMAX;
        //Attribute<int> HP_Compressor;
        //Attribute<int> HP_Pump_State;
        //Attribute<int> HP_Status;
        #pragma endregion
        #pragma region RG
        /// @brief Pump 1 install state
        ///
        /// (eg 1-1-014) First part (1- or 0-) indicates whether the pump is installed/fitted. If so (1- 
        /// means it is), the second part (1- above) indicates it's speed type. The third 
        /// part (014 above) represents it's possible states (0 OFF, 1 ON, 4 AUTO)
        Property<String> Pump1InstallState;
        /// @brief Pump 2 install state
        ///
        /// (eg 1-1-014) First part (1- or 0-) indicates whether the pump is installed/fitted. If so (1- 
        /// means it is), the second part (1- above) indicates it's speed type. The third 
        /// part (014 above) represents it's possible states (0 OFF, 1 ON, 4 AUTO)
        Property<String> Pump2InstallState;
        /// @brief Pump 3 install state
        ///
        /// (eg 1-1-014) First part (1- or 0-) indicates whether the pump is installed/fitted. If so (1- 
        /// means it is), the second part (1- above) indicates it's speed type. The third 
        /// part (014 above) represents it's possible states (0 OFF, 1 ON, 4 AUTO)
        Property<String> Pump3InstallState;
        /// @brief Pump 4 install state
        ///
        /// (eg 1-1-014) First part (1- or 0-) indicates whether the pump is installed/fitted. If so (1- 
        /// means it is), the second part (1- above) indicates it's speed type. The third 
        /// part (014 above) represents it's possible states (0 OFF, 1 ON, 4 AUTO)
        Property<String> Pump4InstallState;       
        /// @brief Pump 5 install state
        ///
        /// (eg 1-1-014) First part (1- or 0-) indicates whether the pump is installed/fitted. If so (1- 
        /// means it is), the second part (1- above) indicates it's speed type. The third 
        /// part (014 above) represents it's possible states (0 OFF, 1 ON, 4 AUTO)
        Property<String> Pump5InstallState;
        /// @brief Pump 1 is in safe state to start
        Property<bool> Pump1OkToRun;
        /// @brief Pump 2 is in safe state to start
        Property<bool> Pump2OkToRun;
        /// @brief Pump 3 is in safe state to start
        Property<bool> Pump3OkToRun;
        /// @brief Pump 4 is in safe state to start
        Property<bool> Pump4OkToRun;
        /// @brief Pump 5 is in safe state to start
        Property<bool> Pump5OkToRun;
        /// @brief Lock mode
        ///
        /// 0 = keypad unlocked, 1 = partial lock, 2 = full lock
        Property<int> LockMode;

#pragma endregion

    protected:
        #pragma region R2
        boolean update_MainsCurrent(String);
        boolean update_MainsVoltage(String);
        boolean update_CaseTemperature(String);
        boolean update_PortCurrent(String);
        boolean update_SpaTime(String);
        boolean update_HeaterTemperature(String);
        boolean update_PoolTemperature(String);
        boolean update_WaterPresent(String);
        boolean update_AwakeMinutesRemaining(String);
        boolean update_FiltPumpRunTimeTotal(String);
        boolean update_FiltPumpReqMins(String);
        boolean update_LoadTimeOut(String);
        boolean update_HourMeter(String);
        boolean update_Relay1(String);
        boolean update_Relay2(String);
        boolean update_Relay3(String);
        boolean update_Relay4(String);
        boolean update_Relay5(String);
        boolean update_Relay6(String);
        boolean update_Relay7(String);
        boolean update_Relay8(String);
        boolean update_Relay9(String);
        #pragma endregion
        #pragma region R3
        boolean update_CLMT(String);
        boolean update_PHSE(String);
        boolean update_LLM1(String);
        boolean update_LLM2(String);
        boolean update_LLM3(String);
        boolean update_SVER(String);
        boolean update_Model(String);
        boolean update_SerialNo1(String);
        boolean update_SerialNo2(String);
        boolean update_D1(String);
        boolean update_D2(String);
        boolean update_D3(String);
        boolean update_D4(String);
        boolean update_D5(String);
        boolean update_D6(String);
        boolean update_Pump(String);
        boolean update_LS(String);
        boolean update_HV(String);
        boolean update_SnpMR(String);
        boolean update_Status(String);
        boolean update_PrimeCount(String);
        boolean update_EC(String);
        boolean update_HAMB(String);
        boolean update_HCON(String);
        boolean update_HV_2(String);
        #pragma endregion
        #pragma region R4
        boolean update_Mode(String);
        boolean update_Ser1_Timer(String);
        boolean update_Ser2_Timer(String);
        boolean update_Ser3_Timer(String);
        boolean update_HeatMode(String);
        boolean update_PumpIdleTimer(String);
        boolean update_PumpRunTimer(String);
        boolean update_AdtPoolHys(String);
        boolean update_AdtHeaterHys(String);
        boolean update_Power(String);
        boolean update_Power_kWh(String);
        boolean update_Power_Today(String);
        boolean update_Power_Yesterday(String);
        boolean update_ThermalCutOut(String);
        boolean update_Test_D1(String);
        boolean update_Test_D2(String);
        boolean update_Test_D3(String);
        boolean update_ElementHeatSourceOffset(String);
        boolean update_Frequency(String);
        boolean update_HPHeatSourceOffset_Heat(String);
        boolean update_HPHeatSourceOffset_Cool(String);
        boolean update_HeatSourceOffTime(String);
        boolean update_Vari_Speed(String);
        boolean update_Vari_Percent(String);
        boolean update_Vari_Mode(String);
        #pragma endregion
        #pragma region R5
        //R5
        // Unknown encoding - TouchPad2.update_Value();
        // Unknown encoding - TouchPad1.update_Value();
        boolean update_RB_TP_Pump1(String);
        boolean update_RB_TP_Pump2(String);
        boolean update_RB_TP_Pump3(String);
        boolean update_RB_TP_Pump4(String);
        boolean update_RB_TP_Pump5(String);
        boolean update_RB_TP_Blower(String);
        boolean update_RB_TP_Light(String);
        boolean update_RB_TP_Auto(String);
        boolean update_RB_TP_Heater(String);
        boolean update_RB_TP_Ozone(String);
        boolean update_RB_TP_Sleep(String);
        boolean update_WTMP(String);
        boolean update_CleanCycle(String);
        #pragma endregion
        #pragma region R6
        boolean update_VARIValue(String);
        boolean update_LBRTValue(String);
        boolean update_CurrClr(String);
        boolean update_ColorMode(String);
        boolean update_LSPDValue(String);
        boolean update_FiltSetHrs(String);
        boolean update_FiltBlockHrs(String);
        boolean update_STMP(String);
        boolean update_L_24HOURS(String);
        boolean update_PSAV_LVL(String);
        boolean update_PSAV_BGN(String);
        boolean update_PSAV_END(String);
        boolean update_L_1SNZ_DAY(String);
        boolean update_L_2SNZ_DAY(String);
        boolean update_L_1SNZ_BGN(String);
        boolean update_L_2SNZ_BGN(String);
        boolean update_L_1SNZ_END(String);
        boolean update_L_2SNZ_END(String);
        boolean update_DefaultScrn(String);
        boolean update_TOUT(String);
        boolean update_VPMP(String);
        boolean update_HIFI(String);
        boolean update_BRND(String);
        boolean update_PRME(String);
        boolean update_ELMT(String);
        boolean update_TYPE(String);
        boolean update_GAS(String);
        #pragma endregion
        #pragma region R7
        boolean update_WCLNTime(String);
        // The following 2 may be reversed
        boolean update_TemperatureUnits(String);
        boolean update_OzoneOff(String);
        boolean update_Ozone24(String);
        // The following 2 may be reversed
        boolean update_Circ24(String);
        boolean update_CJET(String);
        boolean update_VELE(String);
        boolean update_StartDD(String);
        boolean update_StartMM(String);
        boolean update_StartYY(String);
        boolean update_V_Max(String);
        boolean update_V_Min(String);
        boolean update_V_Max_24(String);
        boolean update_V_Min_24(String);
        boolean update_CurrentZero(String);
        boolean update_CurrentAdjust(String);
        boolean update_VoltageAdjust(String);
        boolean update_Ser1(String);
        boolean update_Ser2(String);
        boolean update_Ser3(String);
        boolean update_VMAX(String);
        boolean update_AHYS(String);
        boolean update_HUSE(String);
        boolean update_HELE(String);
        boolean update_HPMP(String);
        boolean update_PMIN(String);
        boolean update_PFLT(String);
        boolean update_PHTR(String);
        boolean update_PMAX(String);
        #pragma endregion
        #pragma region R9
        boolean update_F1_HR(String);
        boolean update_F1_Time(String);
        boolean update_F1_ER(String);
        boolean update_F1_I(String);
        boolean update_F1_V(String);
        boolean update_F1_PT(String);
        boolean update_F1_HT(String);
        boolean update_F1_CT(String);
        boolean update_F1_PU(String);
        boolean update_F1_VE(String);
        boolean update_F1_ST(String);
        #pragma endregion
        #pragma region RA
        boolean update_F2_HR(String);
        boolean update_F2_Time(String);
        boolean update_F2_ER(String);
        boolean update_F2_I(String);
        boolean update_F2_V(String);
        boolean update_F2_PT(String);
        boolean update_F2_HT(String);
        boolean update_F2_CT(String);
        boolean update_F2_PU(String);
        boolean update_F2_VE(String);
        boolean update_F2_ST(String);
        #pragma endregion
        #pragma region RB
        boolean update_F3_HR(String);
        boolean update_F3_Time(String);
        boolean update_F3_ER(String);
        boolean update_F3_I(String);
        boolean update_F3_V(String);
        boolean update_F3_PT(String);
        boolean update_F3_HT(String);
        boolean update_F3_CT(String);
        boolean update_F3_PU(String);
        boolean update_F3_VE(String);
        boolean update_F3_ST(String);
        #pragma endregion
        #pragma region RC
        //Outlet_Heater.update_Value(String);
        //Outlet_Circ.update_Value(String);
        //Outlet_Sanitise.update_Value(String);
        //Outlet_Pump1.update_Value(String);
        //Outlet_Pump2.update_Value(String);
        //Outlet_Pump4.update_Value(String);
        //Outlet_Pump5.update_Value(String);
        boolean update_Outlet_Blower(String);
        #pragma endregion
        #pragma region RE
        boolean update_HP_Present(String);
        //HP_FlowSwitch.update_Value(String);
        //HP_HighSwitch.update_Value(String);
        //HP_LowSwitch.update_Value(String);
        //HP_CompCutOut.update_Value(String);
        //HP_ExCutOut.update_Value(String);
        //HP_D1.update_Value(String);
        //HP_D2.update_Value(String);
        //HP_D3.update_Value(String);
        boolean update_HP_Ambient(String);
        boolean update_HP_Condensor(String);
        boolean update_HP_Compressor_State(String);
        boolean update_HP_Fan_State(String);
        boolean update_HP_4W_Valve(String);
        boolean update_HP_Heater_State(String);
        boolean update_HP_State(String);
        boolean update_HP_Mode(String);
        boolean update_HP_Defrost_Timer(String);
        boolean update_HP_Comp_Run_Timer(String);
        boolean update_HP_Low_Temp_Timer(String);
        boolean update_HP_Heat_Accum_Timer(String);
        boolean update_HP_Sequence_Timer(String);
        boolean update_HP_Warning(String);
        boolean update_FrezTmr(String);
        boolean update_DBGN(String);
        boolean update_DEND(String);
        boolean update_DCMP(String);
        boolean update_DMAX(String);
        boolean update_DELE(String);
        boolean update_DPMP(String);
        //CMAX.update_Value(String);
        //HP_Compressor.update_Value(String);
        //HP_Pump_State.update_Value(String);
        //HP_Status.update_Value(String);
        #pragma endregion
        #pragma region RG
        boolean update_Pump1InstallState(String);
        boolean update_Pump2InstallState(String);
        boolean update_Pump3InstallState(String);
        boolean update_Pump4InstallState(String);
        boolean update_Pump5InstallState(String);
        boolean update_Pump1OkToRun(String);
        boolean update_Pump2OkToRun(String);
        boolean update_Pump3OkToRun(String);
        boolean update_Pump4OkToRun(String);
        boolean update_Pump5OkToRun(String);
        boolean update_LockMode(String);
        #pragma endregion
            

    public:
        float getMainsCurrent() { return MainsCurrent.getValue(); }
        void setMainsCurrentCallback(void (*callback)(float)) { MainsCurrent.setCallback(callback); }

        int getMainsVoltage() { return MainsVoltage.getValue(); }
        void setMainsVoltageCallback(void (*callback)(int)) { MainsVoltage.setCallback(callback); }

        int getCaseTemperature() { return CaseTemperature.getValue(); }
        void setCaseTemperatureCallback(void (*callback)(int)) { CaseTemperature.setCallback(callback); }

        int getPortCurrent() { return PortCurrent.getValue(); }
        void setPortCurrentCallback(void (*callback)(int)) { PortCurrent.setCallback(callback); }

        /* Not implemented 
        time_t getSpaTime() { return SpaTime.getValue(); }
        void setSpaTimeCallback(void (*callback)(time_t)) { SpaTime.setCallback(callback); }
        */

        float getHeaterTemperature() { return HeaterTemperature.getValue(); }
        void setHeaterTemperatureCallback(void (*callback)(float)) { HeaterTemperature.setCallback(callback); }

        float getPoolTemperature() { return PoolTemperature.getValue(); }
        void setPoolTemperatureCallback(void (*callback)(float)) { PoolTemperature.setCallback(callback); }

        bool getWaterPresent() { return WaterPresent.getValue(); }
        void setWaterPresentCallback(void (*callback)(bool)) { WaterPresent.setCallback(callback); }

        int getAwakeMinutesRemaining() { return AwakeMinutesRemaining.getValue(); }
        void setAwakeMinutesRemainingCallback(void (*callback)(int)) { AwakeMinutesRemaining.setCallback(callback); }

        int getFiltPumpRunTimeTotal() { return FiltPumpRunTimeTotal.getValue(); }
        void setFiltPumpRunTimeTotalCallback(void (*callback)(int)) { FiltPumpRunTimeTotal.setCallback(callback); }

        int getFiltPumpReqMins() { return FiltPumpReqMins.getValue(); }
        void setFiltPumpReqMinsCallback(void (*callback)(int)) { FiltPumpReqMins.setCallback(callback); }

        int getLoadTimeOut() { return LoadTimeOut.getValue(); }
        void setLoadTimeOutCallback(void (*callback)(int)) { LoadTimeOut.setCallback(callback); }

        float getHourMeter() { return HourMeter.getValue(); }
        void setHourMeterCallback(void (*callback)(float)) { HourMeter.setCallback(callback); }

        int getRelay1() { return Relay1.getValue(); }
        void setRelay1Callback(void (*callback)(int)) { Relay1.setCallback(callback); }

        int getRelay2() { return Relay2.getValue(); }
        void setRelay2Callback(void (*callback)(int)) { Relay2.setCallback(callback); }

        int getRelay3() { return Relay3.getValue(); }
        void setRelay3Callback(void (*callback)(int)) { Relay3.setCallback(callback); }

        int getRelay4() { return Relay4.getValue(); }
        void setRelay4Callback(void (*callback)(int)) { Relay4.setCallback(callback); }

        int getRelay5() { return Relay5.getValue(); }
        void setRelay5Callback(void (*callback)(int)) { Relay5.setCallback(callback); }

        int getRelay6() { return Relay6.getValue(); }
        void setRelay6Callback(void (*callback)(int)) { Relay6.setCallback(callback); }

        int getRelay7() { return Relay7.getValue(); }
        void setRelay7Callback(void (*callback)(int)) { Relay7.setCallback(callback); }

        int getRelay8() { return Relay8.getValue(); }
        void setRelay8Callback(void (*callback)(int)) { Relay8.setCallback(callback); }

        int getRelay9() { return Relay9.getValue(); }
        void setRelay9Callback(void (*callback)(int)) { Relay9.setCallback(callback); }

        int getCLMT() { return CLMT.getValue(); }
        void setCLMTCallback(void (*callback)(int)) { CLMT.setCallback(callback); }

        int getPHSE() { return PHSE.getValue(); }
        void setPHSECallback(void (*callback)(int)) { PHSE.setCallback(callback); }

        int getLLM1() { return LLM1.getValue(); }
        void setLLM1Callback(void (*callback)(int)) { LLM1.setCallback(callback); }

        int getLLM2() { return LLM2.getValue(); }
        void setLLM2Callback(void (*callback)(int)) { LLM2.setCallback(callback); }

        int getLLM3() { return LLM3.getValue(); }
        void setLLM3Callback(void (*callback)(int)) { LLM3.setCallback(callback); }

};
#endif