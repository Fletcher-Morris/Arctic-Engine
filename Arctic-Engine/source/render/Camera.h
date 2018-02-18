#include "../entity/Entity.h"
#include "..\util\GlmTypedefs.h"
#include "CameraConfig.h"

class Camera : public Entity
{
public:
	Camera(const CameraConfig& config);
	void Update();

	const Matrix4& GetViewMatrix();
	const Matrix4& GetProjectionMatrix();
	const Matrix4& GetProjectionViewMatrix();

private:
	CameraConfig m_config;
	Matrix4 m_projMatrix;
	Matrix4 m_viewMatrix;
	Matrix4 m_projViewMatrix;
};