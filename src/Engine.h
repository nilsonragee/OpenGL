#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

#include "EngineEnum.h"
class eCEntity;
#include "ge_archivefile.h"
#include "ge_archivemanager.h"
#include "ge_node.h"
#include "ge_scriptadminbase.h"

class eCEngine
{
public:
	eCEngine();
	~eCEngine();

public:
	virtual bEResult Initialize(void);
};

#include "ge_keyboard.h"
#include "ge_objectinspectordlg.h"
#include "ge_audiochannelgroup.h"
#include "ge_audiochannel.h"
#include "ge_audiomodule.h"
#include "ge_templateentityproxy.h"
#include "ge_entity.h"
#include "ge_templateentity.h"
#include "ge_dynamicentity.h"
#include "ge_collisionshape.h"
#include "ge_collisionshapebase_ps.h"
#include "ge_spatialentity.h"
class eCPVSPrefetcher3;
#endif