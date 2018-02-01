#include "Camera.h"
#include "GameData.h"

Camera::Camera(float _fov, float _aspect, float _near, float _far, Vector3 _up, Vector3 _target)
	: field_of_view(_fov)
	, aspect_ratio(_aspect)
	, near_plane_distance(_near)
	, far_plane_distance(_far)
	, up(_up)
	, target(_target)
	, zoom(1.0f)
{
}


/* Update's the camera's position with a conversion between world space and screen space.
* Essentially, transformations to other objects are treated relative to the camera.
*/
void Camera::Tick(GameData* _GD)
{
		world_mat = Matrix::CreateTranslation(Vector3(-pos.x, -pos.y, 0)) *
		Matrix::CreateRotationZ(roll) *
		Matrix::CreateScale(Vector3(zoom, zoom, 1)) *
		Matrix::CreateTranslation(Vector3(_GD->window_width * 0.5f, _GD->window_height * 0.5f, 0));
}


void Camera::Draw(DrawData* _DD)
{
	//standard camera doesn't draw ANYTHING
}
