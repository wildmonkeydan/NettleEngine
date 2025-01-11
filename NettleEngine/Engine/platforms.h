#pragma once

/// 
/// PLATFORM-DEPENDANT MACROS
/// 

#ifdef PLATFORM_DESKTOP

#include "System/desktop.h"
using HostOS = Nettle::System::Desktop;

#elif PLATFORM_PSX



#elif PLATFORM_SATURN



#elif PLATFORM_3DO



#endif // PLATFORM_DESKTOP
