#include "MatrixMaths.h"
#include "Camera.h"

Matrix4 CreateModelMatrix(const Entity & entity)
{
	Matrix4 matrix;

	matrix = glm::rotate(matrix, glm::radians(entity.transform.rotation.x), { 1,0,0 });
	matrix = glm::rotate(matrix, glm::radians(entity.transform.rotation.y), { 0,1,0 });
	matrix = glm::rotate(matrix, glm::radians(entity.transform.rotation.z), { 0,0,1 });
	matrix = glm::translate(matrix, entity.transform.position);

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
