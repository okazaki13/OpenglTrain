/*************************************************************************\

  Copyright 2006 3D Inc.
  All Rights Reserved.
  
*************************************************************************/
#ifndef _SMART_POLYGON_OPTIMIZER_EXPORT_H_
#define _SMART_POLYGON_OPTIMIZER_EXPORT_H_

#ifndef SPODllExport
#ifdef WIN32
#  ifdef SPO_EXPORTS
#    define SPODllExport __declspec(dllexport)
#  else
#    ifdef SPO_STATIC_LIBRARY
#      define SPODllExport
#    else
#      define SPODllExport __declspec(dllimport)
#    endif
#  endif
#else  // for Linux
#  ifdef HAVE_GCCVISIBILITYPATCH
#    ifdef SPO_EXPORTS
#      define SPODllExport __attribute__ ((visibility("default")))
#    else
#      ifdef SPO_STATIC_LIBRARY
#        define SPODllExport
#      else
#        define SPODllExport __declspec(dllimport)
#      endif
#    endif
#  else
#    define SPODllExport
#  endif
#endif  // WIN32
#endif

#endif
