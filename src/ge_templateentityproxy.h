#ifndef GE_TEMPLATEENTITYPROXY_H_INCLUDED
#define GE_TEMPLATEENTITYPROXY_H_INCLUDED

class eCTemplateEntity;

class GE_DLLIMPORT eCTemplateEntityProxy
{
public:    virtual GEU16    GetVersion(void) const;
public:    virtual bEResult Read(bCIStream&);
public:    virtual bEResult Write(bCOStream&);
protected: virtual bEResult CopyFrom(eCTemplateEntityProxy const&);
protected: virtual GEBool   Compare(eCTemplateEntityProxy const&) const;
public:    virtual         ~eCTemplateEntityProxy(void);

private:
	// 0000 // eCTemplateEntityProxy::`vftable'
	/* 0004 */ eCTemplateEntity* mEntityInternal;

public:
	eCTemplateEntityProxy(eCTemplateEntityProxy const&);
	eCTemplateEntityProxy(eCTemplateEntity*);
	eCTemplateEntityProxy(void);

public:
	eCTemplateEntityProxy const& operator =                        (eCTemplateEntityProxy const&);
	bCOStream& operator >>                       (bCOStream&);
	bCIStream& operator <<                       (bCIStream&);
	GEBool                        operator ==                       (eCTemplateEntityProxy const&) const;
	GEBool                        operator !=                       (eCTemplateEntityProxy const&) const;
	operator eCTemplateEntity* (void);
	operator eCTemplateEntity const* (void) const;
	eCTemplateEntity* operator ->                       (void);
	eCTemplateEntity const* operator ->                       (void) const;

public:
	eCTemplateEntity* GetEntity(void);
	eCTemplateEntity const* GetEntity(void) const;
	GEBool                   IsEntityIDValid(void) const;
	void                     SetEntity(eCTemplateEntity const*);

protected:
	bEResult Create(void);
	void     Destroy(void);
	void     Invalidate(void);
	void     SetEntityInternal(eCTemplateEntity const*);

};
#endif
