#include "../entity/Entity.h"
#include "../util/GlmTypedefs.h"
#include "CameraConfig.h"

class Camera : public Component
{
public:
	void Configure(const CameraConfig& config);

	const Matrix4& GetViewMatrix();
	const Matrix4& GetProjectionMatrix();
	const Matrix4& GetProjectionViewMatrix();

	void DoAThing()
	{
		std::cout << "DID A THING" << std::endl;
	}

	Vector3 position;
	Vector3 rotation;

private:
	CameraConfig m_config;
	Matrix4 m_projMatrix;
	Matrix4 m_viewMatrix;
	Matrix4 m_projViewMatrix;

	// Inherited via Component
	virtual void OnInit() override;
	virtual void OnUpdate() override;
	virtual void OnFixedUpdate() override;
	virtual void OnRender() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
};