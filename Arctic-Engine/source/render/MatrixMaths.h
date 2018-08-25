#pragma once

#include "../util/GlmTypedefs.h"

class Entity;
class Camera;
struct CameraConfig;

Matrix4 CreateModelMatrix	(const Entity& entity);
Matrix4 CreateViewMatrix	(const Camera& camera);
Matrix4 CreateProjMatrix	(const CameraConfig& config);