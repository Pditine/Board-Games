#pragma once
#include <iostream>
#ifdef _DEBUG
#define Log(x) std::cout<<x<<std::endl
#else Log(x)
#endif