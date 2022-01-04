#pragma once
#include <assert.h>

#if _DEBUG
#define ASSERT_CORE_FATAL(x,y)  assert(x,y)
#else 
#define ASSERT_CORE_FATAL(x,y) x
#endif