#ifndef ENTITY_H
#define ENTITY_H

#include <glm\glm.hpp>
#include "../Models/TexturedModel.h"

class Entity
{
public:
	Entity(TexturedModel& model, glm::vec3& position, glm::vec3& rotation, glm::vec3& scale)
		: m_model(model), m_position(position), m_rotation(rotation), m_scale(scale) {}

	inline void ChangePosition(glm::vec3 position){ m_position += position; }
	inline void ChangeRotation(glm::vec3 rotation) { m_rotation += rotation; }
	void ChangeScale(glm::vec3 scale) { m_scale += scale; }

	inline TexturedModel GetModel() { return m_model; }
	inline glm::vec3 GetPosition() { return m_position; }
	inline glm::vec3 GetRotation() { return m_rotation; }
	inline glm::vec3 GetScale() { return m_scale; }

	inline void SetModel(TexturedModel model) { m_model = model; }
	inline void SetPosition(glm::vec3 position) { m_position = position; }
	inline void SetRotation(glm::vec3 rotation) { m_rotation = rotation; }
	inline void SetScale(glm::vec3 scale) { m_scale = scale; }
private:
	TexturedModel m_model;
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
};

#endif // ENTITY_H