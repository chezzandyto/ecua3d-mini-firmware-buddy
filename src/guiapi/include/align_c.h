/**
 * @file align_c.h
 * @author Radek Vana
 * @brief low level alignment for display
 * @date 2021-02-01
 */
#pragma once

// alignment constants
enum {
    ALIGN_LEFT = 0x00,
    ALIGN_HCENTER = 0x01,
    ALIGN_RIGHT = 0x02,
    ALIGN_HMASK = 0x03,
    ALIGN_TOP = 0x00,
    ALIGN_VCENTER = 0x10,
    ALIGN_BOTTOM = 0x20,
    ALIGN_VMASK = 0x30,
    ALIGN_MASK = 0x33,

    ALIGN_CENTER = ALIGN_HCENTER | ALIGN_VCENTER,
    ALIGN_LEFT_TOP = ALIGN_LEFT | ALIGN_TOP,
    ALIGN_LEFT_CENTER = ALIGN_LEFT | ALIGN_VCENTER,
    ALIGN_LEFT_BOTTOM = ALIGN_LEFT | ALIGN_BOTTOM,
    ALIGN_RIGHT_TOP = ALIGN_RIGHT | ALIGN_TOP,
    ALIGN_RIGHT_CENTER = ALIGN_RIGHT | ALIGN_VCENTER,
    ALIGN_RIGHT_BOTTOM = ALIGN_RIGHT | ALIGN_BOTTOM,
    ALIGN_CENTER_TOP = ALIGN_HCENTER | ALIGN_TOP,
    ALIGN_CENTER_BOTTOM = ALIGN_HCENTER | ALIGN_BOTTOM,
};
