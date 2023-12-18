#pragma once
#ifdef _DEBUG
#define Log(x) std::cout<<x<<std::endl
#else Log(x)
#endif