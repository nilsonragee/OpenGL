#ifndef GE_SPATIALENTITY_H_INCLUDED
#define GE_SPATIALENTITY_H_INCLUDED

class GE_DLLIMPORT eCSpatialEntity :
	public eCEntity
{
public:    virtual GEU16                    GetVersion(void) const;
public:    virtual bEResult                 Write(bCOStream&);
public:    virtual bEResult                 Read(bCIStream&);
public:    virtual void                     Destroy(void);
public:    virtual bEResult                 Create(void);
protected: virtual                         ~eCSpatialEntity(void);
protected: virtual eCSpatialEntity* DoClone(void) const;
public:    virtual GEBool                   IsKilled(void) const;
protected: virtual void                     OnUpdatedWorldMatrix(void);
protected: virtual void                     UpdateLocalBoundary(void);
public:    virtual void                     SetCreator(eCTemplateEntity*);
public:    virtual eCTemplateEntity const* GetCreator(void) const;
public:    virtual GEBool                   HasCreator(void) const;
public:    virtual void                     OnCacheIn(void);
public:    virtual void                     OnCacheOut(void);
public:    virtual void                     Render(GEI16);
public:    virtual void                     RenderAlpha(GEI16);

public:
	GEBool                IsHybrid(void) const;
	GEBool                UpdateContents(void);

protected:
	eCSpatialEntity(eCSpatialEntity const&);
	eCSpatialEntity(void);

protected:
	eCSpatialEntity const& operator = (eCSpatialEntity const&);

protected:
	void Invalidate(void);

};

#endif
