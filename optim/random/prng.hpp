#pragma once

#include <random>

class SingletonGenerator {
	static std::mt19937 mersennetwister;
public:
	static std::mt19937& get_mt();
};