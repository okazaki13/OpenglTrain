#pragma once
#if 0
#if defined(_DLL)
	#if defined(_DEBUG)
		#pragma comment(lib, "foodd.lib")
	#else
		#pragma comment(lib, "food.lib")
	#endif /* _DEBUG */
#elif defined(_MT)
	#if defined(_DEBUG)
		#pragma comment(lib, "foomd.lib")
	#else
		#pragma comment(lib, "foom.lib")
	#endif /* _DEBUG */
#else
	#if defined(_DEBUG)
		#pragma comment(lib, "foosd.lib")
	#else
		#pragma comment(lib, "foos.lib")
	#endif /* _DEBUG */
#endif /* _DLL, _MT */

#endif