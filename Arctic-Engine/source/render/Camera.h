//#include "../util/GlmTypedefs.h"
//#include "CameraConfig.h"
//#include "../entity/ECS.h"
//
//class Camera : public EcsComponent
//{
//public:
//	void Configure(const CameraConfig& config);
//
//	const Matrix4& GetViewMatrix();
//	const Matrix4& GetProjectionMatrix();
//	const Matrix4& GetProjectionViewMatrix();
//
//	// Inherited via Component
//	virtual void OnInit() override;
//	virtual void OnUpdate(double deltaTime) override;
//	virtual void OnFixedUpdate(double fixedTime) override;
//	virtual void OnRender(int method) override;
//	virtual void OnEnable() override;
//	virtual void OnDisable() override;
//
//private:
//	CameraConfig m_config;
//	Matrix4 m_projMatrix;
//	Matrix4 m_viewMatrix;
//	Matrix4 m_projViewMatrix;
//};