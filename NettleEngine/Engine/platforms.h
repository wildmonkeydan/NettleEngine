#pragma once

/// 
/// PLATFORM-DEPENDANT MACROS
/// 

#ifdef PLATFORM_DESKTOP

#include "System/Platforms/desktop.h"
#include "System/File/standard.h"
#include "Render/Platforms/voodoo.h"

namespace Nettle {
	namespace System {
		using HostOS = Desktop;
		using File = FileStandard;
	}
	namespace Render {
		using HostPainter = Voodoo;
	}
}

#elif PLATFORM_PSX



#elif PLATFORM_SATURN



#elif PLATFORM_3DO



#endif // PLATFORM_DESKTOP