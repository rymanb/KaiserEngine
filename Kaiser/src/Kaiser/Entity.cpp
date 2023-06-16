#include "stdafx.h"
#include "Entity.h"



Kaiser::Entity::Entity(entt::entity handle, ECS* ecs) : mId(handle), m_ECS(ecs)
{
}
