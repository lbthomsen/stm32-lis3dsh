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

#ifndef LIS3DSH_H_
#define LIS3DSH_H_

#ifdef DEBUG
#include <stdio.h>
#define LIS3DSH_DEBUG(...) printf(__VA_ARGS__)
#else
        LIS3DSH_DEBUG(...)
#endif

#define LIS3DSH_ID 0x3f  // MUST be returned from the WHO_AM_I register

#define LIS3DSH_WHO_AM_I 0x0f

typedef struct {
    SPI_HandleTypeDef *spi;
    GPIO_TypeDef *cs_port;
    uint16_t cs_pin;
} lis3dsh_handler_t;

typedef enum {
    OK,
    Error
} lis3dsh_result_t;

lis3dsh_result_t lis3dsh_init(lis3dsh_handler_t *lis3dsh, SPI_HandleTypeDef *spi, GPIO_TypeDef *cs_port, uint16_t cs_pin);

#endif /* LIS3DSH_H_ */
