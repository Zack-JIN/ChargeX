/*
 * shared_data.h
 *
 *  Description:
 *  Global data interface for the MPPT project, separating Algorithm/Power
 *  (邓's domain) from UI/Peripherals (金's domain).
 */

#ifndef INC_SHARED_DATA_H_
#define INC_SHARED_DATA_H_

#include <stdbool.h>
#include <stdint.h>

// --- Enums & Defines ---
typedef enum {
    CHARGE_STATE_OFF,
    CHARGE_STATE_MPPT,
    CHARGE_STATE_FAULT
} SystemMode_e;

#define FAULT_FLAG_NONE         (0UL)
#define FAULT_FLAG_OVER_TEMP    (1UL << 0)
// ... other fault flags ...

// --- UI & Peripheral Settings (Written by 金, Read by 邓) ---
typedef struct {
    float fan_on_temp;
    float fan_off_temp;
    // ... other user-configurable settings ...
} UserSettings_t;

// --- Algorithm & Power Status (Written by 邓, Read by 金) ---
typedef struct {
    float pv_voltage;
    float pv_current;
    float pv_power;
    float battery_voltage;
    float mppt_duty_cycle; // 0.0 to 1.0
    SystemMode_e system_mode;
    uint32_t fault_flags;
} PowerStatus_t;

// --- Real-time Sensor Data (Written by 金, Read by 邓) ---
typedef struct {
    float system_temperature;
    // ... other sensor data like humidity etc. if any ...
} SensorData_t;


// --- The Global System State Structure ---
typedef struct {
    UserSettings_t settings;    // 用户设置 (金 -> 邓)
    PowerStatus_t  power;       // 功率状态 (邓 -> 金)
    SensorData_t   sensors;     // 传感器数据 (金 -> 邓)
} SystemState_t;


// --- Declare the single global instance ---
extern SystemState_t g_system_state;

#endif /* INC_SHARED_DATA_H_ */