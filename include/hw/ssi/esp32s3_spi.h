#pragma once

#include "hw/hw.h"
#include "hw/registerfields.h"
#include "hw/misc/esp32s3_xts_aes.h"
#include "hw/ssi/ssi.h"

#define TYPE_ESP32S3_SPI "ssi.esp32s3.spi"
#define ESP32S3_SPI(obj) OBJECT_CHECK(ESP32S3SpiState, (obj), TYPE_ESP32S3_SPI)

/**
 * Size of the SPI I/O registers area
 */
#define ESP32S3_SPI_IO_SIZE (A_SPI_MEM_DATE + 4)


#define ESP32S3_SPI_BUF_WORDS 16

#define ESP32S3_SPI_CS_COUNT 3

typedef struct ESP32S3SpiState {
    SysBusDevice parent_obj;

    MemoryRegion iomem;
    SSIBus *spi;
    qemu_irq cs_gpio[ESP32S3_SPI_CS_COUNT];

    uint32_t mem_cmd;
    /**
     * In user mode, this register represents the flash address.
     * In other modes, bits 0 to 23 included is the memory address and bits 24 to 31 included
     * is the number of bytes to process.
     */
    uint32_t mem_addr;
    uint32_t mem_ctrl;
    uint32_t mem_ctrl1;
    uint32_t mem_ctrl2;
    uint32_t mem_clock;
    uint32_t mem_user;
    uint32_t mem_user1;
    uint32_t mem_user2;
    uint32_t mem_miso_len;
    uint32_t mem_mosi_len;
    uint32_t mem_rd_st;
    uint32_t data_reg[ESP32S3_SPI_BUF_WORDS];
    uint32_t mem_sus_st;
    ESP32S3XtsAesState *xts_aes;
} ESP32S3SpiState;


REG32(SPI_MEM_CMD, 0x000)
    FIELD(SPI_MEM_CMD, FLASH_READ, 31, 1)
    FIELD(SPI_MEM_CMD, FLASH_WREN, 30, 1)
    FIELD(SPI_MEM_CMD, FLASH_WRDI, 29, 1)
    FIELD(SPI_MEM_CMD, FLASH_RDID, 28, 1)
    FIELD(SPI_MEM_CMD, FLASH_RDSR, 27, 1)
    FIELD(SPI_MEM_CMD, FLASH_WRSR, 26, 1)
    FIELD(SPI_MEM_CMD, FLASH_PP, 25, 1)
    FIELD(SPI_MEM_CMD, FLASH_SE, 24, 1)
    FIELD(SPI_MEM_CMD, FLASH_BE, 23, 1)
    FIELD(SPI_MEM_CMD, FLASH_CE, 22, 1)
    FIELD(SPI_MEM_CMD, FLASH_DP, 21, 1)
    FIELD(SPI_MEM_CMD, FLASH_RES, 20, 1)
    FIELD(SPI_MEM_CMD, FLASH_HPM, 19, 1)
    FIELD(SPI_MEM_CMD, USR, 18, 1)
    FIELD(SPI_MEM_CMD, FLASH_PE, 17, 1)
    FIELD(SPI_MEM_CMD, MSPI_ST, 4, 4)
    FIELD(SPI_MEM_CMD, SPI1_MST_ST, 0, 4)

REG32(SPI_MEM_ADDR, 0x004)
    FIELD(SPI_MEM_ADDR, USR_ADDR_VALUE, 0, 32)

REG32(SPI_MEM_CTRL, 0x008)
    FIELD(SPI_MEM_CTRL, FREAD_QIO, 24, 1)
    FIELD(SPI_MEM_CTRL, FREAD_DIO, 23, 1)
    FIELD(SPI_MEM_CTRL, WRSR_2B, 22, 1)
    FIELD(SPI_MEM_CTRL, WP_REG, 21, 1)
    FIELD(SPI_MEM_CTRL, FREAD_QUAD, 20, 1)
    FIELD(SPI_MEM_CTRL, D_POL, 19, 1)
    FIELD(SPI_MEM_CTRL, Q_POL, 18, 1)
    FIELD(SPI_MEM_CTRL, RESANDRES, 15, 1)
    FIELD(SPI_MEM_CTRL, FREAD_DUAL, 14, 1)
    FIELD(SPI_MEM_CTRL, FASTRD_MODE, 13, 1)
    FIELD(SPI_MEM_CTRL, TX_CRC_EN, 11, 1)
    FIELD(SPI_MEM_CTRL, FCS_CRC_EN, 10, 1)
    FIELD(SPI_MEM_CTRL, FCMD_QUAD, 8, 1)
    FIELD(SPI_MEM_CTRL, FCMD_DUAL, 7, 1)
    FIELD(SPI_MEM_CTRL, FDUMMY_OUT, 3, 1)

REG32(SPI_MEM_CTRL1, 0x00C)
    FIELD(SPI_MEM_CTRL1, CS_HOLD_DLY_RES, 2, 10)
    FIELD(SPI_MEM_CTRL1, CLK_MODE, 0, 2)

REG32(SPI_MEM_CTRL2, 0x010)
    FIELD(SPI_MEM_CTRL2, SYNC_RESET, 31, 1)

REG32(SPI_MEM_CLOCK, 0x014)
    FIELD(SPI_MEM_CLOCK, CLK_EQU_SYSCLK, 31, 1)
    FIELD(SPI_MEM_CLOCK, CLKCNT_N, 16, 8)
    FIELD(SPI_MEM_CLOCK, CLKCNT_H, 8, 8)
    FIELD(SPI_MEM_CLOCK, CLKCNT_L, 0, 8)

REG32(SPI_MEM_USER, 0x018)
    FIELD(SPI_MEM_USER, USR_COMMAND, 31, 1)
    FIELD(SPI_MEM_USER, USR_ADDR, 30, 1)
    FIELD(SPI_MEM_USER, USR_DUMMY, 29, 1)
    FIELD(SPI_MEM_USER, USR_MISO, 28, 1)
    FIELD(SPI_MEM_USER, USR_MOSI, 27, 1)
    FIELD(SPI_MEM_USER, USR_DUMMY_IDLE, 26, 1)
    FIELD(SPI_MEM_USER, USR_MOSI_HIGHPART, 25, 1)
    FIELD(SPI_MEM_USER, USR_MISO_HIGHPART, 24, 1)
    FIELD(SPI_MEM_USER, FWRITE_QIO, 15, 1)
    FIELD(SPI_MEM_USER, FWRITE_DIO, 14, 1)
    FIELD(SPI_MEM_USER, FWRITE_QUAD, 13, 1)
    FIELD(SPI_MEM_USER, FWRITE_DUAL, 12, 1)
    FIELD(SPI_MEM_USER, CK_OUT_EDGE, 9, 1)
    FIELD(SPI_MEM_USER, CS_SETUP, 7, 1)
    FIELD(SPI_MEM_USER, CS_HOLD, 6, 1)

REG32(SPI_MEM_USER1, 0x01C)
    FIELD(SPI_MEM_USER1, USR_ADDR_BITLEN, 26, 6)
    FIELD(SPI_MEM_USER1, USR_DUMMY_CYCLELEN, 0, 6)

REG32(SPI_MEM_USER2, 0x020)
    FIELD(SPI_MEM_USER2, USR_COMMAND_BITLEN, 28, 4)
    FIELD(SPI_MEM_USER2, USR_COMMAND_VALUE, 0, 16)

REG32(SPI_MEM_MOSI_DLEN, 0x024)
    FIELD(SPI_MEM_MOSI_DLEN, USR_MOSI_DBITLEN, 0, 10)

REG32(SPI_MEM_MISO_DLEN, 0x028)
    FIELD(SPI_MEM_MISO_DLEN, USR_MISO_DBITLEN, 0, 10)

REG32(SPI_MEM_RD_STATUS, 0x02C)
    FIELD(SPI_MEM_RD_STATUS, WB_MODE, 16, 8)
    FIELD(SPI_MEM_RD_STATUS, STATUS, 0, 16)

REG32(SPI_MEM_MISC, 0x034)
    FIELD(SPI_MEM_MISC, CS_KEEP_ACTIVE, 10, 1)
    FIELD(SPI_MEM_MISC, CK_IDLE_EDGE, 9, 1)
    FIELD(SPI_MEM_MISC, CS1_DIS, 1, 1)
    FIELD(SPI_MEM_MISC, CS0_DIS, 0, 1)

REG32(SPI_MEM_TX_CRC, 0x038)
    FIELD(SPI_MEM_TX_CRC, TX_CRC_DATA, 0, 32)

REG32(SPI_MEM_CACHE_FCTRL, 0x03C)
    FIELD(SPI_MEM_CACHE_FCTRL, FADDR_QUAD, 8, 1)
    FIELD(SPI_MEM_CACHE_FCTRL, FDOUT_QUAD, 7, 1)
    FIELD(SPI_MEM_CACHE_FCTRL, FDIN_QUAD , 6, 1)
    FIELD(SPI_MEM_CACHE_FCTRL, FADDR_DUAL, 5, 1)
    FIELD(SPI_MEM_CACHE_FCTRL, FDOUT_DUAL, 4, 1)
    FIELD(SPI_MEM_CACHE_FCTRL, FDIN_DUAL , 3, 1)
    FIELD(SPI_MEM_CACHE_FCTRL, CACHE_USR_ADDR_4BYTE, 1, 1)

REG32(SPI_MEM_W0, 0x058)
    FIELD(SPI_MEM_W0, BUF0, 0, 32)

REG32(SPI_MEM_W1, 0x05C)
    FIELD(SPI_MEM_W1, BUF1, 0, 32)

REG32(SPI_MEM_W2, 0x060)
    FIELD(SPI_MEM_W2, BUF2, 0, 32)

REG32(SPI_MEM_W3, 0x064)
    FIELD(SPI_MEM_W3, BUF3, 0, 32)

REG32(SPI_MEM_W4, 0x068)
    FIELD(SPI_MEM_W4, BUF4, 0, 32)

REG32(SPI_MEM_W5, 0x06C)
    FIELD(SPI_MEM_W5, BUF5, 0, 32)

REG32(SPI_MEM_W6, 0x070)
    FIELD(SPI_MEM_W6, BUF6, 0, 32)

REG32(SPI_MEM_W7, 0x074)
    FIELD(SPI_MEM_W7, BUF7, 0, 32)

REG32(SPI_MEM_W8, 0x078)
    FIELD(SPI_MEM_W8, BUF8, 0, 32)

REG32(SPI_MEM_W9, 0x07C)
    FIELD(SPI_MEM_W9, BUF9, 0, 32)

REG32(SPI_MEM_W10, 0x080)
    FIELD(SPI_MEM_W10, BUF10, 0, 32)

REG32(SPI_MEM_W11, 0x084)
    FIELD(SPI_MEM_W11, BUF11, 0, 32)

REG32(SPI_MEM_W12, 0x088)
    FIELD(SPI_MEM_W12, BUF12, 0, 32)

REG32(SPI_MEM_W13, 0x08C)
    FIELD(SPI_MEM_W13, BUF13, 0, 32)

REG32(SPI_MEM_W14, 0x090)
    FIELD(SPI_MEM_W14, BUF14, 0, 32)

REG32(SPI_MEM_W15, 0x094)
    FIELD(SPI_MEM_W15, BUF15, 0, 32)

REG32(SPI_MEM_FLASH_WAITI_CTRL, 0x098)
    FIELD(SPI_MEM_FLASH_WAITI_CTRL, WAITI_DUMMY_CYCLELEN, 10, 6)
    FIELD(SPI_MEM_FLASH_WAITI_CTRL, WAITI_CMD, 2, 8)
    FIELD(SPI_MEM_FLASH_WAITI_CTRL, WAITI_DUMMY, 1, 1)

REG32(SPI_MEM_FLASH_SUS_CTRL, 0x09C)
    FIELD(SPI_MEM_FLASH_SUS_CTRL, SUS_TIMEOUT_CNT, 25, 7)
    FIELD(SPI_MEM_FLASH_SUS_CTRL, PES_END_EN, 24, 1)
    FIELD(SPI_MEM_FLASH_SUS_CTRL, PER_END_EN, 23, 1)
    FIELD(SPI_MEM_FLASH_SUS_CTRL, SPI_FMEM_RD_SUS_2B, 22, 1)
    FIELD(SPI_MEM_FLASH_SUS_CTRL, PESR_END_MSK, 6, 16)
    FIELD(SPI_MEM_FLASH_SUS_CTRL, FLASH_PES_EN, 5, 1)
    FIELD(SPI_MEM_FLASH_SUS_CTRL, PES_PER_EN, 4, 1)
    FIELD(SPI_MEM_FLASH_SUS_CTRL, FLASH_PES_WAIT_EN, 3, 1)
    FIELD(SPI_MEM_FLASH_SUS_CTRL, FLASH_PER_WAIT_EN, 2, 1)
    FIELD(SPI_MEM_FLASH_SUS_CTRL, FLASH_PES, 1, 1)
    FIELD(SPI_MEM_FLASH_SUS_CTRL, FLASH_PER, 0, 1)

REG32(SPI_MEM_FLASH_SUS_CMD, 0x0A0)
    FIELD(SPI_MEM_FLASH_SUS_CMD, WAIT_PESR_COMMAND, 16, 16)
    FIELD(SPI_MEM_FLASH_SUS_CMD, FLASH_PES_COMMAND, 8, 8)
    FIELD(SPI_MEM_FLASH_SUS_CMD, FLASH_PER_COMMAND, 0, 8)

REG32(SPI_MEM_SUS_STATUS, 0x0A4)
    FIELD(SPI_MEM_SUS_STATUS, SPI0_LOCK_EN, 7, 1)
    FIELD(SPI_MEM_SUS_STATUS, FLASH_PES_DLY_128, 6, 1)
    FIELD(SPI_MEM_SUS_STATUS, FLASH_PER_DLY_128, 5, 1)
    FIELD(SPI_MEM_SUS_STATUS, FLASH_DP_DLY_128, 4, 1)
    FIELD(SPI_MEM_SUS_STATUS, FLASH_RES_DLY_128, 3, 1)
    FIELD(SPI_MEM_SUS_STATUS, FLASH_HPM_DLY_128, 2, 1)
    FIELD(SPI_MEM_SUS_STATUS, WAIT_PESR_CMD_2B, 1, 1)
    FIELD(SPI_MEM_SUS_STATUS, FLASH_SUS, 0, 1)

REG32(SPI_MEM_TIMING_CALI, 0x0A8)
    FIELD(SPI_MEM_TIMING_CALI, EXTRA_DUMMY_CYCLELEN, 2, 3)
    FIELD(SPI_MEM_TIMING_CALI, TIMING_CALI, 1, 1)

REG32(SPI_MEM_INT_ENA, 0x0C0)
    FIELD(SPI_MEM_INT_ENA, MST_ST_END_INT_ENA, 4, 1)
    FIELD(SPI_MEM_INT_ENA, SLV_ST_END_INT_ENA, 3, 1)
    FIELD(SPI_MEM_INT_ENA, WPE_END_INT_ENA, 2, 1)
    FIELD(SPI_MEM_INT_ENA, PES_END_INT_ENA, 1, 1)
    FIELD(SPI_MEM_INT_ENA, PER_END_INT_ENA, 0, 1)

REG32(SPI_MEM_INT_CLR, 0x0C4)
    FIELD(SPI_MEM_INT_CLR, MST_ST_END_INT_CLR, 4, 1)
    FIELD(SPI_MEM_INT_CLR, SLV_ST_END_INT_CLR, 3, 1)
    FIELD(SPI_MEM_INT_CLR, WPE_END_INT_CLR, 2, 1)
    FIELD(SPI_MEM_INT_CLR, PES_END_INT_CLR, 1, 1)
    FIELD(SPI_MEM_INT_CLR, PER_END_INT_CLR, 0, 1)

REG32(SPI_MEM_INT_RAW, 0x0C8)
    FIELD(SPI_MEM_INT_RAW, MST_ST_END_INT_RAW, 4, 1)
    FIELD(SPI_MEM_INT_RAW, SLV_ST_END_INT_RAW, 3, 1)
    FIELD(SPI_MEM_INT_RAW, WPE_END_INT_RAW, 2, 1)
    FIELD(SPI_MEM_INT_RAW, PES_END_INT_RAW, 1, 1)
    FIELD(SPI_MEM_INT_RAW, PER_END_INT_RAW, 0, 1)

REG32(SPI_MEM_INT_ST, 0x0CC)
    FIELD(SPI_MEM_INT_ST, MST_ST_END_INT_ST, 4, 1)
    FIELD(SPI_MEM_INT_ST, SLV_ST_END_INT_ST, 3, 1)
    FIELD(SPI_MEM_INT_ST, WPE_END_INT_ST, 2, 1)
    FIELD(SPI_MEM_INT_ST, PES_END_INT_ST, 1, 1)
    FIELD(SPI_MEM_INT_ST, PER_END_INT_ST, 0, 1)

REG32(SPI_MEM_CLOCK_GATE, 0x0DC)
    FIELD(SPI_MEM_CLOCK_GATE, CLK_EN, 0, 1)

REG32(SPI_MEM_DATE, 0x3FC)
    FIELD(SPI_MEM_DATE, DATE, 0, 28)
