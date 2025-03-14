/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 Lars Boegild Thomsen <lbthomsen@gmail.com>
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include "main.h"
#include "lis3dsh.h"

// Private functions

lis3dsh_result_t lis3dsh_write(lis3dsh_handler_t *lis3dsh, uint8_t *data, uint16_t len) {
    lis3dsh_result_t res = OK;

    HAL_GPIO_WritePin(lis3dsh->cs_port, lis3dsh->cs_pin, GPIO_PIN_RESET);

    if (HAL_SPI_Transmit(lis3dsh->spi, data, len, HAL_MAX_DELAY) != HAL_OK) {
        res = Error;
    }

    HAL_GPIO_WritePin(lis3dsh->cs_port, lis3dsh->cs_pin, GPIO_PIN_SET);

    return res;
}

lis3dsh_result_t lis3dsh_read(lis3dsh_handler_t *lis3dsh, uint8_t addr, uint8_t *data, uint16_t len) {
    lis3dsh_result_t res = OK;

    HAL_GPIO_WritePin(lis3dsh->cs_port, lis3dsh->cs_pin, GPIO_PIN_RESET);

    if (HAL_SPI_Transmit(lis3dsh->spi, &addr, 1, HAL_MAX_DELAY) != HAL_OK) {
        res = Error;
    } else {
        if (HAL_SPI_Receive(lis3dsh->spi, data, len, HAL_MAX_DELAY) != HAL_OK) {
            res = Error;
        }
    }

    HAL_GPIO_WritePin(lis3dsh->cs_port, lis3dsh->cs_pin, GPIO_PIN_SET);

    return res;
}

// Public functions

lis3dsh_result_t lis3dsh_init(lis3dsh_handler_t *lis3dsh, SPI_HandleTypeDef *spi, GPIO_TypeDef *cs_port, uint16_t cs_pin) {
    lis3dsh_result_t res = OK;

    LIS3DSH_DEBUG("lis3dsh_init\n");

    lis3dsh->spi = spi;
    lis3dsh->cs_port = cs_port;
    lis3dsh->cs_pin = cs_pin;

    uint8_t buf[1] = {0};

    if (lis3dsh_read(lis3dsh, LIS3DSH_WHO_AM_I, buf, 1) == OK) {
        LIS3DSH_DEBUG("Whoami reports %02x, should be %02x\n", buf[1], LIS3DSH_ID);

    } else {
        res = Error;
    }

    return res;
}
