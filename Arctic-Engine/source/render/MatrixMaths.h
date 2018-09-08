#pragma once

#include "../util/GlmTypedefs.h"
#include "../entity/component/CameraComponent.h"

class EcsEntity;
class CameraComponent;
struct CameraConfig;

Matrix4 CreateModelMatrix	(const EcsEntity& entity);
Matrix4 CreateViewMatrix	(const CameraComponent& camera);
Matrix4 CreateProjMatrix	(const CameraConfig& config);