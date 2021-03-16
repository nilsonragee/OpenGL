#ifndef SHAREDBASE_H_INCLUDED
#define SHAREDBASE_H_INCLUDED

#pragma warning( push, 1 )
#ifndef WINVER
#define WINVER 0x0501
#endif
#ifndef _WIN32_WINNT
#define _WIN32_WINNT WINVER
#endif
#define NOMINMAX
#include <windows.h>
#pragma warning( pop )

// PhysX declarations (external)
class NxVec3;

#include "SharedBaseEnum.h"

#include "ge_def.h"
#include "ge_types.h"
#include "ge_globals.h"
#include "../Engine/ge_timer.h"
#include "ge_clock.h"
#include "ge_memheap.h"
#include "ge_memoryadmin.h"
#include "ge_validatememory.h"
class bCIStream;
class bCOStream;
#include "ge_arraybase.h"
#include "ge_messageadmin.h"
#include "ge_message.h"
#include "ge_erroradmin.h"
#include "ge_error.h"
class bCUnicodeString;
#include "ge_string.h"
#include "ge_unicodestring.h"
#include "ge_guid.h"
#include "ge_datetime.h"
#include "ge_istream.h"
#include "ge_ostream.h"
#include "ge_iostream.h"
#include "ge_commandline.h"
#include "ge_file.h"
#include "ge_filesystem.h"
#include "ge_memorystream.h"
#include "ge_postream.h"
#include "ge_random.h"
#include "ge_threadobjectrefbase.h"
#include "ge_motionkeyframerdata.h"
#include "ge_spyadmin.h"
#endif




