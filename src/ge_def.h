#ifndef GE_DEF_H_INCLUDED
#define GE_DEF_H_INCLUDED


#define __GE_PASTE_TOKENS (A, B) A ## B
#define _GE_PASTE_TOKENS (A, B) __GE_PASTE_TOKENS (A, B)
#define GE_PASTE_TOKENS (A, B) _GE_PASTE_TOKENS (A, B)

#define GE_PADDING(X) char GE_PASTE_TOKENS (__padding, __LINE__ )[ X ];

#define GE_FORCE_DWORD 0x7FFFFFFFL

#define GE_UNREFERENCED_PARAMETER(P) (P)
#define GE_NORETURN __declspec (noreturn)

#define GE_CCALL __cdecl
#define GE_STDCALL __stdcall
#define GE_FASTCALL __fastcall

#define GE_DLLIMPORT __declspec (dllimport)
#define GE_DLLEXPORT __declspec (dllexport)

#define GE_DLLIMPORT_EXTC extern "C" GE_DLLIMPORT
#define GE_DLLIMPORT_DATA extern "C++" GE_DLLIMPORT

#define GE_THREAD_LOCAL __declspec (thread)

#define GEHWND_LAST_EXCEPT() eCWindow::eCHRException( __LINE__, __FILE__, GetLastError())

#define GEGFX_EXCEPT_NOINFO(hr) eCGraphic::eCHrException(__LINE__, __FILE__, (hr))
#define GEGFX_THROW_NOINFO(hrcall) if (FAILED (hr = hrcall)) throw eCGraphic::eCHrException(__LINE__, __FILE__, hr)

#ifndef NDEBUG
#define GEGFX_EXCEPT(hr) eCGraphic::eCHrException(__LINE__, __FILE__, (hr), infoManager.GetMessages())
#define GEGFX_THROW_INFO(hrcall) infoManager.Set(); if (FAILED (hr = hrcall)) throw GEGFX_EXCEPT(hr)
#define GFX_DEVICE_REMOVED_EXCEPT(hr) eCGraphic::eCDeviceRemovedException(__LINE__, __FILE__, (hr), infoManager.GetMessages())
#define GEGFX_THROW_INFO_ONLY(call) infoManager.Set(); (call); {auto v = infoManager.GetMessages(); if (!v.empty()) {throw eCGraphic::eCInfoException(__LINE__, __FILE__, v);}}
#else
#define GEGFX_EXCEPT(hr) eCGraphic::eCHrException(__LINE__, __FILE__, (hr))
#define GEGFX_THROW_INFO(hrcall) GEGFX_THROW_NOINFO(hrcall)
#define GFX_DEVICE_REMOVED_EXCEPT(hr) eCGraphic::eCDeviceRemovedException(__LINE__, __FILE__, (hr))
#define GEGFX_THROW_INFO_ONLY(call) (call)

#endif

#define FULL_WINTARD

// this.GetInfoManager() must exist
// this.GetInfoManager(eCGraphic& gfx) must exist
#ifdef NDEBUG
#define INFOMAN() HRESULT hr
#define INFOMAN(gfx) HRESULT hr
#else
#define INFOMAN() HRESULT hr; eCDXGIManager& infoManager = GetInfoManager()
#define INFOMAN(gfx) HRESULT hr; eCDXGIManager& infoManager = GetInfoManager((gfx))
#endif

#define noxnd noexcept(!IS_DEBUG)

namespace Genome
{
	template <bool match> struct SIZEOF_ASSERTION;
	template <> struct SIZEOF_ASSERTION <true>
	{
		enum
		{
			value = 1
		};
	};

	template <bool match, int expected, int actual> struct SIZEOF_ASSERTION_EQUALS;
	template <int expected, int actual> struct SIZEOF_ASSERTION_EQUALS <true, expected, actual>
	{
		enum
		{
			value = 1
		};
	};

	template <int x> struct sizeof_test {};
}

#define GE_STATIC_ASSERT (EXPR) typedef ::Genome::sizeof_test <sizeof ( ::Genome::SIZEOF_ASSERTION< !!(EXPR)>)> GE_PASTE_TOKENS (Genome_sizeof_, __COUNTER__);

#define GE_STATIC_ASSERT_EQUALS (ACTUAL, EXPECTED) typedef ::Genome::sizeof_test <sizeof(::Genome::SIZEOF_ASSERTION_EQUALS <ACTUAL == (EXPECTED), EXPECTED, ACTUAL>)> GE_PASTE_TOKENS (Genome_sizeof_, __COUNTER__);
#define GE_ASSERT_SIZEOF (TYPE, SIZE) GE_STATIC_ASSERT_EQUALS (sizeof (TYPE), SIZE);

#define GE_STATIC_BLOCK _GE_STATIC_BLOCK (GE_PASTE_TOKENS (_static_block_, __COUNTER__))
#define _GE_STATIC_BLOCK (prefix) \
    __GE_STATIC_BLOCK (GE_PASTE_TOKENS (prefix, _fn), GE_PASTE_TOKENS( prefix, _var ))
#define __GE_STATIC_BLOCK (FUNC_NAME, VAR_NAME) \
    static void FUNC_NAME();                     \
    static int VAR_NAME = ( FUNC_NAME(), 0 );    \
    static void FUNC_NAME()
#endif