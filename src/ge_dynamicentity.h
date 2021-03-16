#ifndef GE_DYNAMICENTITY_H_INCLUDED
#define GE_DYNAMICENTITY_H_INCLUDED

class GE_DLLIMPORT eCDynamicEntity : public eCEntity
{
public:
	enum eECreatureClass
	{
		eECreatureClass_Object = 0,
		eECreatureClass_NPC = 1,
		eECreatureClass_Player = 2
	};

public:    virtual eECreatureClass          GetCreatureClass(void) const;
public:    virtual void                     EnableMovementControlByPhysics(GEBool);
public:    virtual GEBool                   IsMovementControledByPhysics(void) const;
public:    virtual void                     OnTrigger(eCEntity*, eCEntity*);
public:    virtual void                     OnUntrigger(eCEntity*, eCEntity*);
protected: virtual void                     DoSaveGameEntityPostRead(void);
public:    virtual GEU16                    GetVersion(void) const;
public:    virtual bEResult                 Write(bCOStream&);
public:    virtual bEResult                 Read(bCIStream&);
public:    virtual void                     Destroy(void);
public:    virtual bEResult                 Create(void);
protected: virtual                         ~eCDynamicEntity(void);
protected: virtual eCDynamicEntity* DoClone(void) const;
public:    virtual GEBool                   IsDummy(void) const;
protected: virtual void                     OnUpdatedWorldMatrix(void);
protected: virtual void                     OnUpdatedWorldTreeBoundary(void);
public:    virtual void                     Decay(void);
public:    virtual GEBool                   IsAutoKillEnabled(void) const;
public:    virtual void                     SetCreator(eCTemplateEntity*);
public:    virtual eCTemplateEntity const* GetCreator(void) const;
public:    virtual GEBool                   HasCreator(void) const;
public:    virtual void                     CopyEntityPrivateData(eCEntity const&, GEBool);
protected: virtual void                     OnProcess(void);
protected: virtual void                     OnPreProcess(void);
protected: virtual void                     OnPostProcess(void);
protected: virtual void                     OnDeinitialize(void);
protected: virtual void                     OnPostRead(void);
public:    virtual void                     OnCacheIn(void);
public:    virtual void                     OnCacheOut(void);
public:    virtual void                     Render(GEI16);
public:    virtual void                     RenderAlpha(GEI16);

public:
	void                 EnableCollisionResponse(GEBool);
	GEU16                GetVisualizedRotAxes(void) const;
	GEU16                GetVisualizedTransAxes(void) const;
	GEBool               HasCollisionResponse(void) const;
	GEBool               HasDrawName(void) const;
	GEBool               IsNativeSaveGameEntity(void) const;
	bEResult             ReadSaveGame(bCIStream&);
	void                 SetDrawName(GEU8);
	void                 SetVisualizedRotAxes(GEU16);
	void                 SetVisualizedTransAxes(GEU16);
	bEResult             WriteSaveGame(bCOStream&);

protected:
	eCDynamicEntity(eCDynamicEntity const&);
	eCDynamicEntity(void);

protected:
	eCDynamicEntity const& operator = (eCDynamicEntity const&);

protected:
	void Invalidate(void);
};
#endif
