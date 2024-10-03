/**
* @file graphics.h
 *
 */

#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"
#include "st7789.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
/* Initialize low level display driver */
void lv_port_disp_init(const st7789_config *config);

/* Enable updating the screen (the flushing process) when disp_flush() is called by LVGL
 */
void disp_enable_update(void);

/* Disable updating the screen (the flushing process) when disp_flush() is called by LVGL
 */
void disp_disable_update(void);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*GRAPHICS_H_INCLUDED*/
