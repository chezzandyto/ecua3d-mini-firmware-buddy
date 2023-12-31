/**
 * @file eeprom_v22.hpp
 * @brief version 22 from release 4.6.1
 */

#pragma once
#include "eeprom_v32789.hpp"
namespace config_store_ns::old_eeprom::v22 {

#pragma pack(push)
#pragma pack(1)

/**
 * @brief body of current eeprom
 * without head and crc
 */
struct vars_body_t : public old_eeprom::v32789::vars_body_t {
    float ODOMETER_E1;
    float ODOMETER_E2;
    float ODOMETER_E3;
    float ODOMETER_E4;
    float ODOMETER_E5;
    uint32_t ODOMETER_T0;
    uint32_t ODOMETER_T1;
    uint32_t ODOMETER_T2;
    uint32_t ODOMETER_T3;
    uint32_t ODOMETER_T4;
    uint32_t ODOMETER_T5;
    uint8_t HWCHECK_COMPATIBILITY;
};

#pragma pack(pop)

constexpr vars_body_t body_defaults = {
    old_eeprom::v32789::body_defaults,
    0, // EEVAR_ODOMETER_E1
    0, // EEVAR_ODOMETER_E2
    0, // EEVAR_ODOMETER_E3
    0, // EEVAR_ODOMETER_E4
    0, // EEVAR_ODOMETER_E5
    0, // EEVAR_ODOMETER_T0
    0, // EEVAR_ODOMETER_T1
    0, // EEVAR_ODOMETER_T2
    0, // EEVAR_ODOMETER_T3
    0, // EEVAR_ODOMETER_T4
    0, // EEVAR_ODOMETER_T5
    1, // EEVAR_HWCHECK_COMPATIBILITY
};

inline vars_body_t convert(const old_eeprom::v32789::vars_body_t &src) {
    vars_body_t ret = body_defaults;

    // copy entire v32789 struct
    memcpy(&ret, &src, sizeof(old_eeprom::v32789::vars_body_t));

    return ret;
}

} // namespace config_store_ns::old_eeprom::v22
