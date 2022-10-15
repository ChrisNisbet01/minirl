#pragma once

#define ARRAY_SIZE(a) (sizeof(a)/sizeof((a)[0]))

#define BIT_IS_SET(var, bit) (((var) & (bit)) != 0)
