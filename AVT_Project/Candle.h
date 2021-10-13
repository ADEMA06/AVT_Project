#ifndef __CANDLE_H__
#define __CANDLE_H__

#define _USE_MATH_DEFINES
#include "GameObject.h"
#include <sstream>
#include <string>
#include "geometry.h"
#include "AVTmathLib.h"
#include "VSShaderlib.h"
#include <math.h>
#include "Light.h"
#include "vec.h"

/// The storage for matrices
extern float mMatrix[COUNT_MATRICES][16];
extern float mCompMatrix[COUNT_COMPUTED_MATRICES][16];

/// The normal matrix
extern float mNormal3x3[9];

const float radius = 0.5f;
const float height = 4.0f;

class Candle : public GameObject{
	struct MyMesh candle;
	Light pointlight;
	vec4 color;

public:
	Candle(vec3 position, vec4 color) : GameObject(position) {
		this->color = color;
		this->pointlight.position = vec4(position.x, position.y + height, position.z, 1.0f);
		this->pointlight.on = 1;
	}

	Light getPointLight() {
		return pointlight;
	}

	void createCandle() {
		float amb[] = { 0.2f, 0.15f, 0.1f, 1.0f };
		float diff[] = { color.x, color.y, color.z, color.w };
		float spec[] = { 0.8f, 0.8f, 0.8f, 1.0f };
		float emissive[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		float shininess = 10.0f;
		int texcount = 0;
		vec3 pos = getPosition();
		candle = createCylinder(height, radius, 20);
		candle = setMesh(candle, amb, diff, spec, emissive, shininess, texcount, pos);
	}


	void drawCandle(VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformId, GLint lPos_uniformId) {
		setShaders(shader, candle);

		pushMatrix(MODEL);
		translate(MODEL, getPosition().x, getPosition().y + height/2, getPosition().z);
		rotate(MODEL, 90, 0, 1, 0);
		drawMesh(candle, shader, pvm_uniformId, vm_uniformId, normal_uniformId, lPos_uniformId);
		popMatrix(MODEL);
		
	}
};

#endif