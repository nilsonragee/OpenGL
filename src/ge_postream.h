#ifndef GE_POSTREAM_H_INCLUDED
#define GE_POSTREAM_H_INCLUDED

class GE_DLLIMPORT bCPOStream :
	public bCMemoryStream
{
public: virtual GEU32 Read(GELPVoid, GEU32);
public: virtual GEU32 Read(bCString&);
public: virtual      ~bCPOStream(void);
public: virtual GEU32 Write(GELPCVoid, GEU32);
public: virtual GEU32 Write(bCString const&);

protected:
	static GEBool                  ms_bLegacyMode;
	static bCPOStream* ms_pMainPOStream;

private:
	GEBool  m_bUnk;
	GEBool  m_bForcedLegacyMode;

public:
	static void GE_STDCALL   DisableLegacyMode(void);
	static GEBool GE_STDCALL IsInLegacyMode(void);

public:
	bCPOStream(bCPOStream const&);
	bCPOStream(void);

public:
	bCPOStream& operator = (bCPOStream const&);

public:
	void   ClearStringHeaderMap(void);
	void   Create(void);
	void   Destroy(void);
	void   FakeMainPOStream(GEBool);
	void   ForceLegacyMode(void);
	GEBool IsForcedLegacyMode(void) const;
	GEBool IsMain(void) const;
	GEBool ReadFile(bCIStream&);
	GEBool WriteFile(bCOStream&);

protected:
	void Invalidate(void);

};
#endif
