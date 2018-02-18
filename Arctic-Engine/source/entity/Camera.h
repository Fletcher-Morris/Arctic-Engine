#include "Entity.h"
#include "..\util\GlmTypedefs.h"

class Camera : public Entity
{
public:
	Camera();
	void update();

	const Matrix4& GetViewMatrix();
	const Matrix4& GetProjectionMatrix();
	const Matrix4& GetProjectionViewMatrix();

private:
	const Entity* m_pEntity;
	Matrix4 m_projMatrix;
	Matrix4 m_viewMatrix;
	Matrix4 m_projViewMatrix;
};