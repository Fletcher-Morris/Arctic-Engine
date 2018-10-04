#include "Transform.h"

void Transform::SetParent(Transform * _newParent)
{
	m_parent = _newParent;
}

Transform * Transform::GetParent()
{
	return m_parent;
}
