/*************************************************************************\

  Copyright(C) 2006 3D Inc.
  All Rights Reserved.
  
*************************************************************************/
#ifndef _SMART_COLLLISION_EXPORT_H_
#define _SMART_COLLLISION_EXPORT_H_

#ifndef SCDllExport
#ifdef WIN32
#  ifdef SC_EXPORTS
#    define SCDllExport __declspec(dllexport)
#  else
#    ifdef SC_STATIC_LIBRARY
#      define SCDllExport
#    else
#      define SCDllExport __declspec(dllimport)
#    endif
#  endif
#else  // for Linux
#  define SCDllExport
#endif  // WIN32
#endif

#endif
