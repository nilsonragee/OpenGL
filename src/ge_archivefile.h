#include "../SharedBase/SharedBase.h"

class eCArchiveFile : public bCIOStream
{
public:
	enum bEArchiveFileAccessMode
	{
		bEArchiveFileAccessMode_Read,
		bEArchiveFileAccessMode_Write,
		bEArchiveFileAccessMode_ReadWrite,
		bEArchiveFileAccessMode_ForceDWORD = GE_FORCE_DWORD
	};

public: virtual void     Destroy(void);
public: virtual bEResult Create(void);
public: virtual GEU32    ReadLine(bCString&);
public: virtual GEU32    WriteLine(GELPCChar);
public: using bCIStream::Read;
public: virtual GEU32    Read(GELPVoid, GEU32);
public: virtual GEU32    Read(bCString&);
public: virtual         ~eCArchiveFile(void);
public: virtual GEI64    GetPosition(void) const;
public: virtual GEBool   Seek(GEI64, bEStreamSeekMode);
public: using bCOStream::Write;
public: virtual GEU32    Write(GELPCVoid, GEU32);
public: virtual GEU32    Write(bCString const&);

public:
	// 0000 // eCArchiveFile::`vftable'{for `bCIStream'}
	// 0004 // eCArchiveFile::`vftable'{for `bCOStream'}
	/* 0008 */ bCString                      m_strFileName;
	/* 0020 */ GEBool                        m_bOpenForWrite;
public:
	eCArchiveFile(eCArchiveFile const&);
	eCArchiveFile(void);

public:
	eCArchiveFile const& operator = (eCArchiveFile const&);

public:
	void       Clear(void);
	GEBool     Close(void);
	void       CopyFrom(eCArchiveFile const&);
	void       CopyTo(eCArchiveFile&) const;
	bCString   GetFileBaseName(void) const;
	void       GetFileBaseName(bCString&) const;
	bCString   GetFileDir(void) const;
	bCString   GetFileExtension(void) const;
	void       GetFileExtension(bCString&) const;
	bCString   GetFileName(void) const;
	void       GetFileName(bCString&) const;
	bCString   GetFilePath(void) const;
	void       GetFilePath(bCString&) const;
	GEI64      GetFileSize(void) const;
	bCDateTime GetFileTime(void) const;
	GEBool     GetPhysicalPath(bCString&) const;
	bCString   GetRootPath(void) const;
	void       GetRootPath(bCString&) const;
	GEU16      GetVersion(void) const;
	GEBool     IsInLegacyMode(void) const;
	GEBool     IsOpen(void) const;
	GEBool     IsOpenForWrite(void) const;
	GEBool     IsReadOnly(void) const;
	GEBool     IsValid(void) const;
	// Fails if the file does not exist. In that case use eCArchiveManager::CreateFileA() to create the file.
	GEBool     Open(bEArchiveFileAccessMode a_enuAccessMode, GEBool a_bHandleGenomfleHeader);
	void       SetReadOnly(GEBool);
	void       SetType(bCString&) const;
	void       SetVersion(GEU16);

protected:
	void Invalidate(void);
};
