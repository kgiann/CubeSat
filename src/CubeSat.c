//
//  CubeSat.c
//  CubeSat
//
//  Created by Kostis Giannousakis on 4/9/15.
//  Copyright (c) 2015 Kostis Giannousakis. All rights reserved.
//

#include <stdio.h>
#include "CubeSat.h"
#include <string.h>
#include "Endianness.h"
#include <math.h>

#define CSUint8CutOff(x) (x > 0 ? (x > 0xff ? 0xff:x):0)

void CSWholeOrbitDataLog(CSWholeOrbitData *data)
{
    printf("CSWholeOrbitData: ");
    uint8_t bCount = CSWholeOrbitDataBytesCount(data);
    printf("%d data sets, %d bytes\n", data->count, bCount);

    printf("--> Hexadecimal:\n");
    for (int i = 0; i < bCount; i++)
        printf("%.2x ", *(((uint8_t*)data) +i));
    printf("\n");

    printf("--> Binary:\n");
    for (int i = 0; i < bCount; i++) {
        uint8_t byte = *(((uint8_t*)data) +i);
        for (int j = 7; j >= 0; j--)
            printf("%d", (byte >> j) & 0x01);
        printf(" ");
    }
    printf("\n");
}

void CSWholeOrbitDataInit(CSWholeOrbitData *data, uint32_t time)
{
    memset(data, 0, sizeof(CSWholeOrbitData));

    data->time = htole_32(time);
}

uint16_t CSWholeOrbitDataBytesCount(CSWholeOrbitData *data)
{
    return 32/8 + ceil((data->count * 57.)/8.);
}

void CSWholeOrbitDataPush(
            CSWholeOrbitData *data,

            uint32_t dt,

            uint8_t mode,
            float _batVolt,
            float _batCurr,
            float _bus3V3Curr,
            float _bus5VCurr,
            float _tempComm,
            float _tempEPS,
            float _tempBat
        )
{
    uint8_t batVolt     = CSUint8CutOff(floorf(20  * _batVolt - 60));
    uint8_t batCurr     = CSUint8CutOff(floorf(127 * _batCurr + 127));
    uint8_t bus3V3Curr  = CSUint8CutOff(floorf(40  * _bus3V3Curr));
    uint8_t bus5VCurr   = CSUint8CutOff(floorf(40  * _bus5VCurr));
    uint8_t tempComm    = CSUint8CutOff(floorf(4   * _tempComm + 60));
    uint8_t tempEPS     = CSUint8CutOff(floorf(4   * _tempEPS + 60));
    uint8_t tempBat     = CSUint8CutOff(floorf(4   * _tempBat + 60));


    uint8_t  il, ir;
    uint32_t j;

    if (data->count < 32)
    {
        ir = data->count % 8; // 0-7
        j  = (data->count * 57) / 8;

        data->count++;
    }
    else
    {
        ir = (data->count -1) % 8; // 0-7
        j  = ((data->count-1) * 57) / 8;

        data->time += dt;

        // Shift the data sets
        uint32_t i0 = 0;
        uint32_t i1 = i0 + 7;

        while (i0 <= j) {
            i1++;
            data->data[i0++] = (data->data[i1-1] << 1) | (data->data[i1] >> 7);
        }

        // Zero the last data set
        memset(data->data + i0, 0, 7);
        data->data[--i0] &= 0xfe;
    }

    data->data[j  ] |= (mode ? 0x01:0x00) << (7-ir);

    il = 8 - ++ir;
    data->data[j++] |= batVolt      >> ir;
    data->data[j  ] |= batVolt      << il;

    data->data[j++] |= batCurr      >> ir;
    data->data[j  ] |= batCurr      << il;

    data->data[j++] |= bus3V3Curr   >> ir;
    data->data[j  ] |= bus3V3Curr   << il;

    data->data[j++] |= bus5VCurr    >> ir;
    data->data[j  ] |= bus5VCurr    << il;

    data->data[j++] |= tempComm     >> ir;
    data->data[j  ] |= tempComm     << il;

    data->data[j++] |= tempEPS      >> ir;
    data->data[j  ] |= tempEPS      << il;

    data->data[j++] |= tempBat      >> ir;
    data->data[j  ] |= tempBat      << il;
}

void CSWholeOrbitDataGet(
            CSWholeOrbitData *data,

            uint8_t i,

            uint8_t *mode,
            float *_batVolt,
            float *_batCurr,
            float *_bus3V3Curr,
            float *_bus5VCurr,
            float *_tempComm,
            float *_tempEPS,
            float *_tempBat
        )
{
    uint8_t batVolt;
    uint8_t batCurr;
    uint8_t bus3V3Curr;
    uint8_t bus5VCurr;
    uint8_t tempComm;
    uint8_t tempEPS;
    uint8_t tempBat;

    uint8_t  il = i % 8;
    uint32_t j  = (i * 57) / 8;

    *mode = (data->data[j  ] >> (7-il)) & 0x01;

    uint8_t ir = 8 - ++il;

    batVolt     = (data->data[j] << il) | (data->data[j+1] >> ir);
    j++; batCurr    = (data->data[j] << il) | (data->data[j+1] >> ir);
    j++; bus3V3Curr = (data->data[j] << il) | (data->data[j+1] >> ir);
    j++; bus5VCurr  = (data->data[j] << il) | (data->data[j+1] >> ir);
    j++; tempComm   = (data->data[j] << il) | (data->data[j+1] >> ir);
    j++; tempEPS    = (data->data[j] << il) | (data->data[j+1] >> ir);
    j++; tempBat    = (data->data[j] << il) | (data->data[j+1] >> ir);

    *_batVolt       = (batVolt + 60 ) / 20.;
    *_batCurr       = (batCurr - 127) / 127.;
    *_bus3V3Curr    = (bus3V3Curr   ) / 40.;
    *_bus5VCurr     = (bus5VCurr    ) / 40.;
    *_tempComm      = (tempComm - 60) / 4.;
    *_tempEPS       = (tempEPS  - 60) / 4.;
    *_tempBat       = (tempBat  - 60) / 4.;
}


uint16_t Fletcher16( uint8_t* data, int count )
{
    uint16_t sum1 = 0x0000;
    uint16_t sum2 = 0x0000;
    int index;

    for( index = 0; index < count; ++index )
    {
        sum1 = (sum1 + data[index]) % 0xFFFF;
        sum2 = (sum2 + sum1) % 0xFFFF;
    }

    return (sum2 << 8) | sum1;
}
