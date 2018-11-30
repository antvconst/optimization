#pragma once

#include <random>

/**
 * @brief Singleton Mersenne Twister PRNG
 * 
 */
class SingletonGenerator {
	static std::mt19937 mersennetwister;
public:
	static std::mt19937& get_mt();
};