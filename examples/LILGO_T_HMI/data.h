#ifndef APP_DATA_H_
#define APP_DATA_H_

// #ifdef __cplusplus
// extern "C" {
// #endif

/******************************************************************************/
/***        include files                                                   ***/
/******************************************************************************/

#include <stdint.h>

/******************************************************************************/
/***        macro definitions                                               ***/
/******************************************************************************/

/******************************************************************************/
/***        type definitions                                                ***/
/******************************************************************************/

typedef struct touch_calibration_t {
	uint16_t rawX;
	uint16_t rawY;
} touch_calibration_t;

/******************************************************************************/
/***        exported variables                                              ***/
/******************************************************************************/

/******************************************************************************/
/***        exported functions                                              ***/
/******************************************************************************/

void data_init(void);
bool data_read(touch_calibration_t *data);
bool data_write(touch_calibration_t *data);

// #ifdef __cplusplus
// }
// #endif

#endif
/******************************************************************************/
/***        END OF FILE                                                     ***/
/******************************************************************************/