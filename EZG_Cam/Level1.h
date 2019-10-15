#pragma once

#ifndef LEVEL_1_H
#define LEVEL_1_H

#include <stdint.h>

struct  Level1 {
	static const char width = 11;// 10;
	static const char depth = 11;// 10;
	static const char height = 10;// 10;

	static uint8_t map[];
};

#endif // !LEVEL_1_H

