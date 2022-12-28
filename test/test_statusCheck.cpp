#include <Arduino.h>
#include <unity.h>
#include "SpaNetInterface.h"

SpaNetInterface sni;
String Resp_OK;
String Resp_Bad;
String Resp_Empty;


void setUp(void) {
    // set stuff up here

Resp_OK = "RF:\r\n\
,R2,93,234,42,234,6,20,49,55,10,10,2021,358,9999,1,0,11,706,186,33,7769,391,381,0,305,0,0,368,352,153,241,:\r\n\
,R3,32,1,255,4,4,SW V6 19 11 12,SV3,21110001,20000337,1,0,1,0,0,0,NA,1,0,473,In use,7,0,10,10,0,0,-1,:\r\n\
,R4,NORM,0,0,0,4,0,42535,4,12,21762,85236,2007,2665,0,8388608,0,0,2,5,100,0,0,4,80,100,0,0,4,:\r\n\
,R5,1,1,1,1,0,0,0,0,0,0,0,1,1,0,353,0,3,4,0,0,0,0,1,2,3,6,:\r\n\
,R6,2,5,0,4,5,12,3,360,1,0,3584,5120,127,128,5376,5632,2304,1792,0,30,0,0,2,0,2,3,0,410,:\r\n\
,R7,2304,0,1,4,1,0,2,22,9,2021,253,212,248,214,482,125,77,1,0,0,0,23,200,1,0,1,31,50,50,100,5,:\r\n\
,R9,F1,255,0,0,0,0,0,0,0,0,0,0,:\r\n\
,RA,F2,0,0,0,0,0,0,255,0,0,0,0,:\r\n\
,RB,F3,0,0,0,0,0,0,0,0,0,0,0,:\r\n\
,RC,0,1,0,0,0,0,0,0,0,2,0,0,1,0,:\r\n\
,RE,1,10,0,0,0,0,200,200,200,13,8,1,1,0,0,3,1,0,4036,0,0,240,0,0,-4,13,30,8,5,1,:*\r\n\
,RG,1,1,1,1,1,1,1-1-014,1-1-01,1-1-01,1-1-01,0-,0,0,0,3367,:*";

Resp_Bad = "RF:\r\n\
,R2,93,234,42,234,6,20,49,55,10,10,2021,358,9999,1,0,11,706,186,33,7769,391,381,0,305,0,0,368,352,153,241,:\r\n\
,R3,32,1,255,4,4,SW V6 19 11 12,SV3,21110001,20000337,1,0,1,0,0,0,NA,1,0,473,In use,7,0,10,10,0,0,-1,:\r\n\
,R4,NORM,0,0,0,4,0,42535,4,12,21762,85236,2007,2665,R5,1,1,1,1,0,0,0,0,0,0,0,1,1,0,353,0,3,4,0,0,0,0,1,2,3,6,:\r\n\
,R6,2,5,0,4,5,12,3,360,1,0,3584,5120,127,128,5376,5632,2304,1792,0,30,0,0,2,0,2,3,0,410,:\r\n\
,R7,2304,0,1,4,1,0,2,22,9,2021,253,212,248,214,482,125,77,1,0,0,0,23,200,1,0,1,31,50,50,100,5,:\r\n\
,R9,F1,255,0,0,0,0,0,0,0,0,0,0,:\r\n\
,RA,F2,0,0,0,0,0,0,255,0,0,0,0,:\r\n\
,RB,F3,0,0,0,0,0,0,0,0,0,0,0,:\r\n\
,RC,0,1,0,0,0,0,0,0,0,2,0,0,1,0,:\r\n\
,RE,1,10,0,0,0,0,200,200,200,13,8,1,1,0,0,3,1,0,4036,0,0,240,0,0,-4,13,30,8,5,1,:*\r\n\
,RG,1,1,1,1,1,1,1-1-014,1-1-01,1-1-01,1-1-01,0-,0,0,0,3367,:*";

Resp_Empty = "";


}

void tearDown(void) {
    // clean stuff up here

}

void test_loopBack(void) {
Serial2.print(Resp_OK);
String rec = Serial2.readString();
TEST_ASSERT(rec.equals(Resp_OK));
}


void test_readString_RespOK(void) {
Serial2.print(Resp_OK);
TEST_ASSERT(sni.readStatus());
}

void test_readString_RespBad(void) {
Serial.print(Resp_Bad);
TEST_ASSERT(!sni.readStatus());
}

void test_readString_RespEmpty(void){
Serial.print(Resp_Bad);
TEST_ASSERT(!sni.readStatus());
}

void test_MainsCurrent_getValue(void){
    TEST_ASSERT_EQUAL_FLOAT(9.3,sni.MainsCurrent.getValue());
}        


void setup()
{


    delay(2000); // service delay

    UNITY_BEGIN();

    RUN_TEST(test_loopBack);
    RUN_TEST(test_readString_RespOK);
    RUN_TEST(test_readString_RespBad);
    RUN_TEST(test_readString_RespEmpty);
    RUN_TEST(test_MainsCurrent_getValue);

    UNITY_END(); // stop unit testing
}


void loop()
{
}