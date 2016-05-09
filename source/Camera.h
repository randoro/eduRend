//
//  Camera.h
//
//	Basic camera class
//

#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "vec\vec.h"
#include "vec\mat.h"

using namespace linalg;

class camera_t
{
	float vfov, aspect;	// aperture attributes
	float zNear, zFar;	// clip planes
	vec3f position;
	float angle = 0;			// rad
	float angle_vel = fPI / 4;	// rad/s

public:

	camera_t(
		float vfov,
		float aspect,
		float zNear,
		float zFar):
		vfov(vfov), aspect(aspect), zNear(zNear), zFar(zFar)
	{

	}


	void MapCameraBuffers(
		ID3D11DeviceContext* device_context,
		ID3D11Buffer* camera_buffer)
	{
		// map the resource buffer, obtain a pointer to it and then write our matrices to it
		D3D11_MAPPED_SUBRESOURCE resource;
		device_context->Map(camera_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
		CameraBuffer_t* camera_buffer_ = (CameraBuffer_t*)resource.pData;

		camera_buffer_->cameraPosition = { position.x, position.y, position.z, 0 };
		device_context->Unmap(camera_buffer, 0);
	}


	void moveTo(const vec3f& p)
	{
		position = p;
	}

	void moveForward(const vec3f& v)
	{
		mat4f M, F, C;
		M = get_ViewToWorldMatrix();
		C = mat4f(v.x, v.y, v.z, 0);
		F = M * C;

		position += vec3f(F.col[2].x, F.col[2].y, F.col[2].z);

	}

	void moveSide(const vec3f& v)
	{
		mat4f M, F, C;
		M = get_ViewToWorldMatrix();
		C = mat4f(v.x, v.y, v.z, 0);
		F = M * C;

		position += vec3f(F.col[0].x, F.col[0].y, F.col[0].z);

	}

	void moveUpDown(const vec3f& v)
	{
		mat4f M, F, C;
		M = get_ViewToWorldMatrix();
		C = mat4f(v.x, v.y, v.z, 0);
		F = M * C;

		position += vec3f(F.col[1].x, F.col[1].y, F.col[1].z);

	}

	void rotate(const float v)
	{
		angle += v;
	}


	mat4f get_ViewToWorldMatrix() const
	{
		mat4f R, T, S, C, M, F;
		R = mat4f::rotation(angle, 0.0f, 1.0f, 0.0f);
		T = mat4f::translation(position);
		M = T * R;
		return M;
	}

	mat4f get_WorldToViewMatrix() const
	{
		mat4f T, R, S, M;
		R = mat4f::rotation(-angle, 0.0f, 1.0f, 0.0f);
		T = mat4f::translation(-position);
		M = R * T;
		return M;
	}

	mat4f get_ProjectionMatrix() const
	{
		return mat4f::projection(vfov, aspect, zNear, zFar);
	}
};

#endif