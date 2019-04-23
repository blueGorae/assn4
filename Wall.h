#pragma once
#include "SceneNode.h"

class Wall :
	public SceneNode
{
private:
	bool (*criticalCollisionActionFunc)(SceneNode*);
public:
	Wall() {}
	Wall(string groupId,
		GLfloat w, GLfloat h,
		GLfloat x, GLfloat y,
		bool (*criticalCollisionActionFunc)(SceneNode*) = NULL,
		GLenum mode = GL_POLYGON,
		GLfloat r = 0.f, GLfloat g = 0.f, GLfloat b = 0.f)
		: SceneNode(groupId, w-FLT_EPSILON, h-FLT_EPSILON, mode, r, g, b, true, true),
		criticalCollisionActionFunc(criticalCollisionActionFunc) {
		translateOrigin(x, y);
	}
	virtual bool criticalCollisionAction(SceneNode* from) {
		if (criticalCollisionActionFunc) {
			return criticalCollisionActionFunc(from);
		}
		return false; 
	}
	virtual ~Wall() {}
};

