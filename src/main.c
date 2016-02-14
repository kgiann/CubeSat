//
//  main.c
//  CubeSat
//
//  Created by Gostmare on 3/7/15.
//  Copyright (c) 2015 Kostis Giannousakis. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "CubeSat.h"

void loopTest();
void justTest();

int scriptScheduler();

int main(int argc, const char * argv[])
{

    // Choose the  one you need to test
    justTest();
    loopTest();

    return 0;
}

void justTest()
{

    printf("sizeof(CSOrbitDataSet)   = %ld bits\n", 8*sizeof(CSOrbitDataSet));
    printf("sizeof(CSWholeOrbitData) = %ld bits\n", 8*sizeof(CSWholeOrbitData));

    CSWholeOrbitData data;
    CSWholeOrbitDataInit(&data, 2009876);


    uint8_t mode        = 0;
    float   batVolt     = 8.5;
    float   batCurr     = 0.55;
    float   bus3V3Curr  = 0.40;
    float   bus5VCurr   = 0.20;
    float   tempComm    = 5.50;
    float   tempEPS     = 15.10;
    float   tempBat     = 38.30;

    printf("Inserting:\n");
    printf("\tmode       = %d\n"     , mode);
    printf("\tbatVolt    = %.3f\n"   , batVolt);
    printf("\tbatCurr    = %.3f\n"   , batCurr);
    printf("\tbus3V3Curr = %.3f\n"   , bus3V3Curr);
    printf("\tbus5VCurr  = %.3f\n"   , bus5VCurr);
    printf("\ttempComm   = %.3f\n"   , tempComm);
    printf("\ttempEPS    = %.3f\n"   , tempEPS);
    printf("\ttempBat    = %.3f\n"   , tempBat);

    CSWholeOrbitDataPush(&data,
                         60,
                         mode,
                         batVolt,
                         batCurr,
                         bus3V3Curr,
                         bus5VCurr,
                         tempComm,
                         tempEPS,
                         tempBat
                        );

    CSWholeOrbitDataGet(&data,
                        0,
                        &mode,
                        &batVolt,
                        &batCurr,
                        &bus3V3Curr,
                        &bus5VCurr,
                        &tempComm,
                        &tempEPS,
                        &tempBat
                       );

    printf("Reading:\n");
    printf("\tmode       = %d\n"     , mode);
    printf("\tbatVolt    = %.3f\n"   , batVolt);
    printf("\tbatCurr    = %.3f\n"   , batCurr);
    printf("\tbus3V3Curr = %.3f\n"   , bus3V3Curr);
    printf("\tbus5VCurr  = %.3f\n"   , bus5VCurr);
    printf("\ttempComm   = %.3f\n"   , tempComm);
    printf("\ttempEPS    = %.3f\n"   , tempEPS);
    printf("\ttempBat    = %.3f\n"   , tempBat);

    mode        = 1;
    batVolt     = 8.90;
    batCurr     = 0.65;
    bus3V3Curr  = 0.50;
    bus5VCurr   = 0.12;
    tempComm    = 6.30;
    tempEPS     = 14.80;
    tempBat     = 41.50;

    printf("Inserting:\n");
    printf("\tmode       = %d\n"     , mode);
    printf("\tbatVolt    = %.3f\n"   , batVolt);
    printf("\tbatCurr    = %.3f\n"   , batCurr);
    printf("\tbus3V3Curr = %.3f\n"   , bus3V3Curr);
    printf("\tbus5VCurr  = %.3f\n"   , bus5VCurr);
    printf("\ttempComm   = %.3f\n"   , tempComm);
    printf("\ttempEPS    = %.3f\n"   , tempEPS);
    printf("\ttempBat    = %.3f\n"   , tempBat);

    CSWholeOrbitDataPush(&data,
                         60,
                         mode,
                         batVolt,
                         batCurr,
                         bus3V3Curr,
                         bus5VCurr,
                         tempComm,
                         tempEPS,
                         tempBat
                        );

    CSWholeOrbitDataGet(&data,
                        0,
                        &mode,
                        &batVolt,
                        &batCurr,
                        &bus3V3Curr,
                        &bus5VCurr,
                        &tempComm,
                        &tempEPS,
                        &tempBat
                       );

    printf("Reading:\n");
    printf("\tmode       = %d\n"     , mode);
    printf("\tbatVolt    = %.3f\n"   , batVolt);
    printf("\tbatCurr    = %.3f\n"   , batCurr);
    printf("\tbus3V3Curr = %.3f\n"   , bus3V3Curr);
    printf("\tbus5VCurr  = %.3f\n"   , bus5VCurr);
    printf("\ttempComm   = %.3f\n"   , tempComm);
    printf("\ttempEPS    = %.3f\n"   , tempEPS);
    printf("\ttempBat    = %.3f\n"   , tempBat);

    //    printf("\nBytes count: %d\n", CSWholeOrbitDataBytesCount(&data));
    //    for (int i = 0; i < 19; i++)
    //        printf("%.2x ", *(((uint8_t*) &data) +i));
    //    printf("\n");

    CSWholeOrbitDataLog(&data);
}

void loopTest()
{

    printf("sizeof(CSOrbitDataSet)   = %ld bits\n", 8*sizeof(CSOrbitDataSet));
    printf("sizeof(CSWholeOrbitData) = %ld bits\n", 8*sizeof(CSWholeOrbitData));

    CSWholeOrbitData data;
    CSWholeOrbitDataInit(&data, 2009876);


    for (int i = 0; i < 35; i++)
    {
        uint8_t mode        = rand();
        float   batVolt     = 3 + (15.75 - 3) * rand() / (float)RAND_MAX;
        float   batCurr     = -1 + (1.008 + 1) * rand() / (float)RAND_MAX;
        float   bus3V3Curr  = 0 + (6.375 - 0) * rand() / (float)RAND_MAX;
        float   bus5VCurr   = 0 + (6.375 - 0) * rand() / (float)RAND_MAX;
        float   tempComm    = -15 + (48.75 + 15) * rand() / (float)RAND_MAX;
        float   tempEPS     = -15 + (48.75 + 15) * rand() / (float)RAND_MAX;
        float   tempBat     = -15 + (48.75 + 15) * rand() / (float)RAND_MAX;

        mode        = 1;
        batVolt     = 8.90;
        batCurr     = 0.65;
        bus3V3Curr  = 0.50;
        bus5VCurr   = 0.12;
        tempComm    = 6.30;
        tempEPS     = 14.80;
        tempBat     = 41.50;

        printf("Inserting:\n");
        printf("\tmode       = %d\n"     , mode);
        printf("\tbatVolt    = %.3f\n"   , batVolt);
        printf("\tbatCurr    = %.3f\n"   , batCurr);
        printf("\tbus3V3Curr = %.3f\n"   , bus3V3Curr);
        printf("\tbus5VCurr  = %.3f\n"   , bus5VCurr);
        printf("\ttempComm   = %.3f\n"   , tempComm);
        printf("\ttempEPS    = %.3f\n"   , tempEPS);
        printf("\ttempBat    = %.3f\n"   , tempBat);

        CSWholeOrbitDataPush(&data,
                             60,
                             mode,
                             batVolt,
                             batCurr,
                             bus3V3Curr,
                             bus5VCurr,
                             tempComm,
                             tempEPS,
                             tempBat
                            );

        CSWholeOrbitDataGet(&data,
                            i < 32 ? i:31,
                            &mode,
                            &batVolt,
                            &batCurr,
                            &bus3V3Curr,
                            &bus5VCurr,
                            &tempComm,
                            &tempEPS,
                            &tempBat
                           );

        printf("Reading:\n");
        printf("\tmode       = %d\n"     , mode);
        printf("\tbatVolt    = %.3f\n"   , batVolt);
        printf("\tbatCurr    = %.3f\n"   , batCurr);
        printf("\tbus3V3Curr = %.3f\n"   , bus3V3Curr);
        printf("\tbus5VCurr  = %.3f\n"   , bus5VCurr);
        printf("\ttempComm   = %.3f\n"   , tempComm);
        printf("\ttempEPS    = %.3f\n"   , tempEPS);
        printf("\ttempBat    = %.3f\n"   , tempBat);
    }

    uint8_t mode        = 0;
    float   batVolt     = 8.5;
    float   batCurr     = 0.55;
    float   bus3V3Curr  = 0.40;
    float   bus5VCurr   = 0.20;
    float   tempComm    = 5.50;
    float   tempEPS     = 15.10;
    float   tempBat     = 38.30;

    CSWholeOrbitDataPush(&data,
                         60,
                         mode,
                         batVolt,
                         batCurr,
                         bus3V3Curr,
                         bus5VCurr,
                         tempComm,
                         tempEPS,
                         tempBat
                        );

    CSWholeOrbitDataGet(&data,
                        7,
                        &mode,
                        &batVolt,
                        &batCurr,
                        &bus3V3Curr,
                        &bus5VCurr,
                        &tempComm,
                        &tempEPS,
                        &tempBat
                       );

    printf("Reading:\n");
    printf("\tmode       = %d\n"     , mode);
    printf("\tbatVolt    = %.3f\n"   , batVolt);
    printf("\tbatCurr    = %.3f\n"   , batCurr);
    printf("\tbus3V3Curr = %.3f\n"   , bus3V3Curr);
    printf("\tbus5VCurr  = %.3f\n"   , bus5VCurr);
    printf("\ttempComm   = %.3f\n"   , tempComm);
    printf("\ttempEPS    = %.3f\n"   , tempEPS);
    printf("\ttempBat    = %.3f\n"   , tempBat);
}
