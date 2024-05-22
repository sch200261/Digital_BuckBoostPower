/********************************************************************************
 * @file    canbus.c
 * @brief   This file provides code for the configuration
 *          of canbus.
 *******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include <canbus.hpp>
#include <userdata.hpp>
/* Includes End --------------------------------------------------------------*/

/* Typedef -------------------------------------------------------------------*/
/* Typedef End ---------------------------------------------------------------*/

/* Define --------------------------------------------------------------------*/
/* Define End ----------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/
/* Macro End -----------------------------------------------------------------*/

/* Variables -----------------------------------------------------------------*/
/* Variables End -------------------------------------------------------------*/

/* Function ------------------------------------------------------------------*/
/* Function End --------------------------------------------------------------*/
/// @brief Tx数据帧结构体
typedef struct TxFrame {
    uint16_t vol_in;
    uint16_t vol_out;
    uint8_t cur_in;
    uint8_t cur_out;
    uint8_t state;
    uint8_t id;
} __attribute__((packed)) TXFRAME;
/// @brief Rx回传帧结构体
typedef struct RxFrame {
    uint16_t vol_exp;
    uint8_t pwr_EN;
    uint8_t cmd;
    uint8_t null[4];
} __attribute__((packed)) RXFRAME;

TXFRAME txframe; // 发送数据帧
RXFRAME rxframe; // 接收数据帧

uint32_t TxID = 0x001; // 发送器ID
uint32_t RxID = 0x064; // 接收器ID

FDCAN_TxHeaderTypeDef txHeader;
FDCAN_RxHeaderTypeDef rxHeader;
FDCAN_FilterTypeDef rxFilter;

/// @brief 初始化发送Header
/// @param
void txHeader_init(void)
{
    txHeader.Identifier          = TxID;
    txHeader.IdType              = FDCAN_STANDARD_ID;
    txHeader.TxFrameType         = FDCAN_DATA_FRAME;
    txHeader.DataLength          = FDCAN_DLC_BYTES_8;
    txHeader.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
    txHeader.BitRateSwitch       = FDCAN_BRS_OFF;
    txHeader.FDFormat            = FDCAN_FD_CAN;
    txHeader.TxEventFifoControl  = FDCAN_NO_TX_EVENTS;
    txHeader.MessageMarker       = 0;
}

/// @brief 初始化Filter
/// @param
void rxFilter_init(void)
{
    rxFilter.IdType       = FDCAN_STANDARD_ID;
    rxFilter.FilterIndex  = 0;
    rxFilter.FilterType   = FDCAN_FILTER_MASK;
    rxFilter.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
    rxFilter.FilterID1    = RxID;
    rxFilter.FilterID2    = 0x111;

    if (HAL_FDCAN_ConfigFilter(&hfdcan1, &rxFilter) == HAL_OK) {
        printf("Filter OK\n");
    }
    if (HAL_FDCAN_ConfigGlobalFilter(&hfdcan1, FDCAN_REJECT, FDCAN_REJECT, FDCAN_REJECT_REMOTE, FDCAN_REJECT_REMOTE) == HAL_OK) {
        printf("Global Filter OK\n");
    }
}

/// @brief 发送一个数据包
/// @param
/// @return 0：发送正常 1：发送失败
uint8_t FDCAN_Send_Msg(void)
{
    if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &txHeader, (uint8_t *)&txframe) != HAL_OK) {
        return 1;
    }
    printf("ok\n");
    return 0;
}

/// @brief 接收一个数据包
/// @param
/// @return 0：接收正常 1：接收失败
uint8_t FDCAN_Get_Msg(void)
{
    if (HAL_FDCAN_GetRxMessage(&hfdcan1, FDCAN_RX_FIFO0, &rxHeader, (uint8_t *)&rxframe) != HAL_OK) {
        return 1;
    }
    return 0;
}

void set_exp_vol(void)
{
    double value = (double)rxframe.vol_exp * 75.0 / 65535.000;
    exp_voltage  = value;
}

uint16_t get_int_vol(double vol)
{
    uint16_t value = vol / 75.0 * 65535;
    return value;
}

uint8_t get_int_cur(double cur)
{
    double value = cur / 25.0 * 65535;
    return value;
}