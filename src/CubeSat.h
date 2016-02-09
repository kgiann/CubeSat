//
//  CubeSat.h
//  CubeSat
//
//  Created by Kostis Giannousakis on 3/7/15.
//  Copyright (c) 2015 Kostis Giannousakis. All rights reserved.
//

#ifndef CubeSat_CubeSat_h
#define CubeSat_CubeSat_h

#include <stdint.h>


typedef struct _CSOrbitDataSet
{
    int mode :1;
    
    uint8_t batVolt;
    uint8_t batCurr;
    uint8_t bus3V3Curr;
    uint8_t bus5VCurr;
    uint8_t tempComm;
    uint8_t tempEPS;
    uint8_t tempBat;
    
} CSOrbitDataSet;

typedef struct _CSWholeOrbitData
{
    uint32_t time;
    uint8_t  data[228];
    
    uint8_t  count;
    
} __attribute__((packed)) CSWholeOrbitData;

void CSWholeOrbitDataLog(CSWholeOrbitData *data);

/**
 Intializes the WOD packet
 @discussion    Zeros data and sets the time of the first data set to @c time.
 */
void CSWholeOrbitDataInit(CSWholeOrbitData *data, uint32_t time);

/**
 Push orbit data in the WOD packet
 @param data        The WOD
 @param dt      
 @param mode        0b1: Normal operation with science unit functional
                    0b0: Safe mode or no science measurements can be performed
 @param batVolt     The measured raw battery voltage value in Volt. (3V:50mv:15.75V)
 @param batCurr     The battery (dis-)charge rate at the time-point of the measurement. (-1A:7.87mA:1.008A)
 @param bus3V3Curr  The power consumption on-board of the CubeSat on the 3V3 bus. (0A:25mA:6.375A)
 @param bus5VCurr   The power consumption on-board of the CubeSat on the 5V bus. (0A:25mA:6.375A)
 @param tempComm    The measured temperatures in oC at the specific locations on the communication system. (-15:0.25:48.75)
 @param tempEPS     The measured temperatures in oC at the specific locations on the EPS. (-15:0.25:48.75)
 @param tempBat     The measured temperatures in oC at the specific locations on the battery surface. (-15:0.25:48.75)
 */
void CSWholeOrbitDataPush(
            CSWholeOrbitData *data,
                         
            uint32_t dt,
                          
            uint8_t mode,
            float   batVolt,
            float   batCurr,
            float   bus3V3Curr,
            float   bus5VCurr,
            float   tempComm,
            float   tempEPS,
            float   tempBat
        );

/**
 
 */
uint16_t CSWholeOrbitDataBytesCount(CSWholeOrbitData *data);

void CSWholeOrbitDataGet(
            CSWholeOrbitData *data,
                         
            uint8_t i,
                          
            uint8_t *mode,
            float *batVolt,
            float *batCurr,
            float *bus3V3Curr,
            float *bus5VCurr,
            float *tempComm,
            float *tempEPS,
            float *tempBat
        );



typedef struct CSScienceHeader {
    
    uint32_t time;
    
    // Attitude          -  Units/bit
    int16_t roll;       //  2 deg
    int16_t pitch;      //  2 deg
    int16_t yaw;        //  2 deg
    int16_t rolldot;    //  milli-deg/sec
    int16_t pitchdot;   //  milli-deg/sec
    int16_t yawdot;     //  milli-deg/sec
    
    // Position
    uint16_t X_ECI;     // 5 km
    uint16_t Y_ECI;     // 5 km
    uint16_t Z_ECI;     // 5 km
    
    
} __attribute__((packed)) CSScienceHeader;

typedef enum _CSScriptType {
    
    CSScriptTypeGeneral     = 0x00,
    CSScriptTypeLowPower    = 0x01,
    CSScriptTypeStage1Test  = 0x02,
    
    CSScriptTypeStage2Test  = 0x04,
    
    CSScriptTypeCustom1     = 0x08,
    CSScriptTypeCustom2     = 0x09,
    CSScriptTypeCustom3     = 0x0A,
    CSScriptTypeCustom4     = 0x0B,
    CSScriptTypeCustom5     = 0x0C,
    CSScriptTypeCustom6     = 0x0D,
    CSScriptTypeCustom7     = 0x0E,
    CSScriptTypeCustom8     = 0x0F,
    
    CSScriptTypeFM1         = 0x10,
    CSScriptTypeFM2         = 0x11,
    CSScriptTypeFM3         = 0x12,
    CSScriptTypeFM4         = 0x13,
    CSScriptTypeFM5         = 0x14,
    CSScriptTypeFM6         = 0x15,
    CSScriptTypeFM7         = 0x16,
    CSScriptTypeFM8         = 0x17
    
} CSScriptType;

typedef struct _CSScriptHeader {
    
    uint16_t len;                       // Script length in BYTES of COMPLETE script file
    uint32_t t_startTime;               // UTC time at which to start running the script
    uint32_t serialNum;                 // File Serial Number
    
    uint8_t sw_ver              : 5;    // Version of SCRIPT TOOL used to write this script
    uint8_t su_id               : 1;    // Science Unit
    uint8_t _NA_1               : 2;    // Not used = ‘0’
    
    CSScriptType script_type    : 5;    // Identifies intented usage of script
    uint8_t su_md               : 1;    // SU model
    
    uint8_t _NA_2               : 2;    // Not used = ‘0’
    
    uint8_t _NA_3;                      // SPARE
    
} __attribute__((packed)) CSScriptHeader;


typedef enum _CSScriptIndex {
    
    CSScriptIndexS1  = 0x41,
    CSScriptIndexS2  = 0x42,
    CSScriptIndexS3  = 0x43,
    CSScriptIndexS4  = 0x44,
    CSScriptIndexS5  = 0x45,
    CSScriptIndexEOF = 0x55     // End-of-Table
    
} CSScriptIndex;

typedef struct _CSTimesTableField {
  
    uint8_t sec;    // Range "00" to "59"
    uint8_t min;    // Range "00" to "59"
    uint8_t hours;  // Range "00" to "23"
    
    uint8_t scrpt_idx;
    
} __attribute__((packed)) CSTimesTableField;

typedef struct _CSScriptSequenceField {
    
    // delta time
    uint8_t sec;    // Range "00" to "59"
    uint8_t min;    // Range "00" to "59"
    
    uint8_t cmd_id;
    
    uint8_t len;
//    uint8_t seq_cnt;
    
    uint8_t param[255];
    
} __attribute__((packed)) CSScriptSequenceField;


// TODO: pack
typedef enum _CSResponceType {
    
    CSResponceTypeSU_HC     = 0x06,
    CSResponceTypeSU_CAL    = 0x07,
    CSResponceTypeSU_SCI    = 0x08,
    CSResponceTypeSU_HK     = 0x09,
    CSResponceTypeSU_STM    = 0x0A,
    CSResponceTypeSU_DUMP   = 0x0B,
    CSResponceTypeSU_ERR    = 0xBB,
    
} __attribute__((aligned (1), packed)) CSResponceType;

typedef struct _CSResponce {
    
    CSResponceType  rsp_id;
    uint8_t         seq_cnt;
    
    uint8_t         data[172];
    
} __attribute__((packed)) CSResponce;

uint16_t CSScriptChecksum(uint8_t *data);



#endif
