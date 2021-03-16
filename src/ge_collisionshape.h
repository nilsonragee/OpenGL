#ifndef GE_COLLISIONSHAPE_H_INCLUDED
#define GE_COLLISIONSHAPE_H_INCLUDED

class NxShape;

class GE_DLLIMPORT eCCollisionShape
{
public:    virtual GEU16    GetVersion(void) const;
public:    virtual bEResult Write(bCOStream&);
public:    virtual bEResult Read(bCIStream&);
public:    virtual void     Destroy(void);
public:    virtual bEResult Create(void);
protected: virtual         ~eCCollisionShape(void);
public:    virtual bEResult PostInitializeProperties(void);

public:
	eCCollisionShape(eCCollisionShape const&);
	eCCollisionShape(void);

public:
	eCCollisionShape const& operator = (eCCollisionShape const&);

protected:
	void CalcShapeAABBLocal(void);
	void Invalidate(void);

};

#endif
