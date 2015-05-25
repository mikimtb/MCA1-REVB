#include <xc.h>
/** InitQEI(byte QEICON, byte DFLTCON, int16 MAXCNT)
 * Use | to initialize QEICON register
 */
#define VELOCITY_MODE_ENABLE        0b10000000
#define VELOCITY_MODE_DISABLE       0b00000000
#define QEI_MODULE_DISABLE          0b00000000
#define QEI_4X_RESET_ON_MAXCNT      0b00011000
#define QEI_4X_RESET_ON_INDX        0b00010100
#define QEI_2X_RESET_ON_MAXCNT      0b00001000
#define QEI_2X_RESET_ON_INDX        0b00000100
#define VELOCITY_POSTCALER_1        0b00000000
#define VELOCITY_POSTCALER_4        0b00000001
#define VELOCITY_POSTCALER_16       0b00000010
#define VELOCITY_POSTCALER_64       0b00000011
/**
 * Use | to initialize DFLTCON register
 */
#define T5CKI_FILTER_ENABLE         0b01000000
#define T5CKI_FILTER_DISABLE        0b00000000
#define QEB_FILTER_ENABLE           0b00100000
#define QEB_FILTER_DISABLE          0b00000000
#define QEA_FILTER_ENABLE           0b00010000
#define QEA_FILTER_DISABLE          0b00000000
#define INDX_FILTER_ENABLE          0b00001000
#define INDX_FILTER_DISABLE         0b00000000
#define FILTER_CLKDIV_BY_128        0b00000110
#define FILTER_CLKDIV_BY_64         0b00000101
#define FILTER_CLKDIV_BY_32         0b00000100
#define FILTER_CLKDIV_BY_16         0b00000011
#define FILTER_CLKDIV_BY_4          0b00000010
#define FILTER_CLKDIV_BY_2          0b00000001
#define FILTER_CLKDIV_BY_1          0b00000000
/**
 * MAXCNT is maximal count after QEI count will be reset to zero.
 * This is used is QEICON is set for QEI_4X_RESET_ON_MAXCNT or QEI_4X_RESET_ON_MAXCNT
 */

void InitQEI(unsigned char, unsigned char, unsigned int);
unsigned int GetPOSCNT(void);