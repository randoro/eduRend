
#pragma once
#ifndef MATRIXBUFFERS_H
#define MATRIXBUFFERS_H

#include "vec\vec.h"
#include "vec\mat.h"

using namespace linalg;

struct MatrixBuffer_t
{
	mat4f ModelToWorldMatrix;
	mat4f WorldToViewMatrix;
	mat4f ProjectionMatrix;
};

#endif

#ifndef MATERIALBUFFERS_H
#define MATERIALBUFFERS_H

#include "vec\vec.h"
#include "vec\mat.h"

using namespace linalg;

struct MaterialBuffer_t
{
	vec4f Ka, Kd, Ks;
};

#endif

#ifndef CAMERABUFFERS_H
#define CAMERABUFFERS_H

#include "vec\vec.h"
#include "vec\mat.h"

using namespace linalg;

struct CameraBuffer_t
{
	vec4f cameraPosition;
	vec4f lightPosition;
};

#endif