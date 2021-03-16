#ifndef GE_ARCHIVEMANAGER_H_INCLUDED
#define GE_ARCHIVEMANAGER_H_INCLUDED

class GE_DLLIMPORT eCArchiveManager
{
public: virtual void     CopyTo(eCArchiveManager&) const;
public: virtual void     CopyFrom(eCArchiveManager const&);
public: virtual GEU16    GetVersion(void) const;
public: virtual void     Destroy(void);
public: virtual bEResult Create(void);
public: virtual         ~eCArchiveManager(void);

public:
	static eCArchiveManager& GE_STDCALL GetInstance(void);

public:
	eCArchiveManager(eCArchiveManager const&);
	eCArchiveManager(void);

public:
	eCArchiveFile    CreateFileA(bCString const&);
	eCArchiveFile    GetFile(bCString const&);
	GEBool           GetFile(bCString const&, eCArchiveFile&);
	bCString const& GetRootPath(void);
	void             SplitPath(bCString const&, bCString*, bCString*, bCString*);

protected:
	eCArchiveManager const& operator = (eCArchiveManager const&);

protected:
	void Invalidate(void);

};

#endif
