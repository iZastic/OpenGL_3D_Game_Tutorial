#include "Entity.h"


Entity::Entity(TexturedModel& model, glm::vec3& position, glm::vec3& rotation, glm::vec3& scale)
	: m_model(model), m_position(position), m_rotation(rotation), m_scale(scale)
{
}


Entity::~Entity()
{
}


void Entity::ChangePosition(glm::vec3 position)
{
	m_position += position;
}


void Entity::ChangeRotation(glm::vec3 rotation)
{
	m_rotation += rotation;
}


void Entity::ChangeScale(glm::vec3 scale)
{
	m_scale += scale;
}