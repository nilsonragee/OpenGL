#ifndef GE_THREADOBJECTREFBASE_H_INCLUDED
#define GE_THREADOBJECTREFBASE_H_INCLUDED

class GE_DLLIMPORT bCThreadObjectRefBase
{
public: virtual ~bCThreadObjectRefBase(void);

public:
	bCThreadObjectRefBase(bCThreadObjectRefBase const&);
	bCThreadObjectRefBase(void);

public:
	bCThreadObjectRefBase& operator = (bCThreadObjectRefBase const&);

public:
	void                     ReleaseOwnership(void);
	GEBool                   TryToGetOwnership(void);
};
#endif
