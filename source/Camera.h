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

	void moveTo(const vec3f& p)
	{
		position = p;
	}

	void moveForward(const vec3f& v)
	{
		mat4f R, T, S, C, M, F;
		R = mat4f::rotation(angle, 0.0f, 1.0f, 0.0f);
		T = mat4f::translation(position);
		S = mat4f::scaling(1, 1, 1);
		M = T * R; // *S;
		C = mat4f(v.x, v.y, v.z, 0);//(0, 0, -1, 0);
		F = M * C;
		//M.operator*(vec4f(0, 0, -1, 0));//vec4f(v.x, v.y, v.z, 0));

		position += vec3f(F.col[2].x, F.col[2].y, F.col[2].z);

		int i = 1;
		//position += v;
	}

	void moveSide(const vec3f& v)
	{
		mat4f R, T, S, C, M, F;
		R = mat4f::rotation(angle, 0.0f, 1.0f, 0.0f);
		T = mat4f::translation(position);
		M = T * R;
		C = mat4f(v.x, v.y, v.z, 0);
		F = M * C;

		position += vec3f(F.col[0].x, F.col[0].y, F.col[0].z);

	}

	void moveUpDown(const vec3f& v)
	{
		mat4f R, T, S, C, M, F;
		R = mat4f::rotation(angle, 0.0f, 1.0f, 0.0f);
		T = mat4f::translation(position);
		M = T * R;
		C = mat4f(v.x, v.y, v.z, 0);
		F = M * C;

		position += vec3f(F.col[1].x, F.col[1].y, F.col[1].z);

	}

	void rotate(const float v)
	{
		angle += v;
	}

	mat4f get_WorldToViewMatrix() const
	{
		mat4f T, R, S, M;
		R = mat4f::rotation(-angle, 0.0f, 1.0f, 0.0f);
		T = mat4f::translation(-position);
		M = R * T;
		return M;
		/*view.rotation =*/ //mat4f::rotation(0.2f, 0.0f, 1.0f, 0.0f);

		//return view.translation(-position);
		//return mat4f::translation(-position); // *mat4f::rotation(angle, 1.0f, 0.0f, 0.0f);
	}

	mat4f get_ProjectionMatrix() const
	{
		return mat4f::projection(vfov, aspect, zNear, zFar);
	}
};

#endif