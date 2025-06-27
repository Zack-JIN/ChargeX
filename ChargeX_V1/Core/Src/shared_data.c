/*
 * shared_data.c
 *
 *  Created on: [Your Date]
 *      Author: [Your Name]
 *
 *  Description:
 *  This file defines and initializes the single instance of the global system
 *  state structure. This is the central data hub for the entire application.
 */

// 1. 必须包含它自己的头文件
// 这样可以确保定义与声明一致，如果头文件有改动而这里没改，编译器会报错。
#include "shared_data.h"

// 2. 定义全局结构体变量的实体并进行初始化
// 'extern'关键字在.h文件中只是一个“预告”，告诉大家有这么个变量。
// 这里的定义才是真正地在内存中（通常是SRAM的.data段）为这个变量分配空间。
SystemState_t g_system_state = {

    // 初始化用户设置 (金's domain, read by 邓)
    // 这里设置的是系统上电后的默认参数。
    // 用户可以通过UI进行修改，修改后的值会直接更新到这个结构体中。
    .settings = {
        .fan_on_temp = 60.0f,     // 默认60摄氏度开启风扇
        .fan_off_temp = 50.0f     // 默认50摄氏度关闭风扇
        // ... other settings can be initialized here ...
    },

    // 初始化功率状态 (邓's domain, read by 金)
    // 这些值会在程序运行过程中，由邓的算法模块实时更新。
    // UI模块会读取这些值来显示。
    .power = {
        .pv_voltage = 0.0f,
        .pv_current = 0.0f,
        .pv_power = 0.0f,
        .battery_voltage = 0.0f,
        .mppt_duty_cycle = 0.0f,   // 初始占空比为0
        .system_mode = CHARGE_STATE_OFF, // 系统启动时处于关闭状态
        .fault_flags = FAULT_FLAG_NONE   // 初始无故障
    },

    // 初始化传感器数据 (金's domain, read by 邓)
    // 这些值会由金的驱动模块实时更新。
    .sensors = {
        .system_temperature = 25.0f // 假设一个室温作为初始值
    }
};

// --- 注意 ---
// 通常情况下，shared_data.c 文件中除了这个全局变量的定义和初始化之外，
// 不应该再包含其他的函数或逻辑。
// 它的职责非常单一，就是提供这个全局数据实例。
// 这样可以保持项目结构的清晰。