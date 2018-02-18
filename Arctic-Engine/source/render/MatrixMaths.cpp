#include "MatrixMaths.h"
#include "../entity/Entity.h"
#include "../util/GlmTypedefs.h"
#include "Camera.h"
#include "CameraConfig.h"

Matrix4 CreateModelMatrix(const Entity & entity)
{
	Matrix4 matrix;

	matrix = glm::rotate(matrix, glm::radians(entity.rotation.x), { 1,0,0 });
	matrix = glm::rotate(matrix, glm::radians(entity.rotation.y), { 0,1,0 });
	matrix = glm::rotate(matrix, glm::radians(entity.rotation.z), { 0,0,1 });
	matrix = glm::translate(matrix, entity.position);

	return matrix;
}

Matrix4 CreateViewMatrix(const Camera & camera)
{
	Matrix4 matrix;

	matrix = glm::rotate(matrix, glm::radians(camera.rotation.x), { 1,0,0 });
	matrix = glm::rotate(matrix, glm::radians(camera.rotation.y), { 0,1,0 });
	matrix = glm::rotate(matrix, glm::radians(camera.rotation.z), { 0,0,1 });
	matrix = glm::translate(matrix, -camera.position);

	return matrix;
}

Matrix4 CreateProjMatrix(const CameraConfig& config)
{
	Matrix4 matrix = glm::perspective(glm::radians(config.fov), (float)(config.width / config.height), config.nearClip, config.farClip);

	return matrix;
}
