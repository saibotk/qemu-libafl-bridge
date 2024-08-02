/*
 * ESP32-C3 CPU Clock and Reset
 *
 * Copyright (c) 2023 Espressif Systems (Shanghai) Co. Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 or
 * (at your option) any later version.
 */
#pragma once

#include "hw/hw.h"
#include "hw/sysbus.h"
#include "hw/registerfields.h"

#define TYPE_ESP32C3_CLOCK "esp32c3.soc.clk"
#define ESP32C3_CLOCK(obj) OBJECT_CHECK(ESP32C3ClockState, (obj), TYPE_ESP32C3_CLOCK)
#define ESP32C3_CLOCK_GET_CLASS(obj) OBJECT_GET_CLASS(ESP32C3ClockClass, obj, TYPE_ESP32C3_CLOCK)
#define ESP32C3_CLOCK_CLASS(klass) OBJECT_CLASS_CHECK(ESP32C3ClockClass, klass, TYPE_ESP32C3_CLOCK)


#define ESP32C3_SYSTEM_CPU_INTR_COUNT   4

/**
 * Value for SYSTEM_SOC_CLK_SEL
 */
#define ESP32C3_CLK_SEL_XTAL    0
#define ESP32C3_CLK_SEL_PLL     1
#define ESP32C3_CLK_SEL_RCFAST  2

/**
 * Values for SYSTEM_PLL_FREQ_SEL
 */
#define ESP32C3_FREQ_SEL_PLL_480    0
#define ESP32C3_FREQ_SEL_PLL_320    1

/**
 * Values for SYSTEM_CPUPERIOD_SEL
*/
#define ESP32C3_PERIOD_SEL_80       0
#define ESP32C3_PERIOD_SEL_160      1


typedef struct ESP32C3ClockState {
    SysBusDevice parent_obj;
    MemoryRegion iomem;

    /* Registers for clocks configuration and frequency dividers */
    uint32_t cpuperconf;
    uint32_t sysclk;


    /* IRQs for crosscore interrupts */
    qemu_irq irqs[ESP32C3_SYSTEM_CPU_INTR_COUNT];

    /* Bitmap that keeps the level of the IRQs */
    uint32_t levels;

    uint32_t sys_ext_dev_enc_dec_ctrl;
} ESP32C3ClockState;

typedef struct ESP32C3ClockClass {
    SysBusDeviceClass parent_class;
    /* Virtual methods */
    uint32_t (*get_ext_dev_enc_dec_ctrl)(ESP32C3ClockState *s);
} ESP32C3ClockClass;

