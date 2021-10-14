#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include <GL/freeglut.h>
#include "vec.h"

/// The storage for matrices
extern float mMatrix[COUNT_MATRICES][16];
extern float mCompMatrix[COUNT_COMPUTED_MATRICES][16];

/// The normal matrix
extern float mNormal3x3[9];


class GameObject {
    vec3 position = {0, 0, 0};
    vec3 rotation = {0, 0, 0};
    vec3 scaling = {1, 1, 1};
    float speed = 0;
    float rotAngle = 0;
    float dirAngle = 0;
 

public:

    GameObject(vec3 position) {
        this->position = position;
    }
 
    GameObject(vec3 position, float speed) {
        this->position = position;
        this->speed = speed;
    }

    GameObject(vec3 position, float speed, float dirAngle) {
        this->position = position;
        this->speed = speed;
        this->dirAngle = dirAngle;
    }

    vec3 getPosition(){
        return this->position;
    }

    void setPosition(vec3 position) {
        this->position = position;
    }

    vec3 getRotation(){
        return this->rotation;
    }

    void setRotation(vec3 rotation) {
        this->rotation = rotation;
    }

    vec3 getScaling(){
        return this->scaling;
    }

    void setScaling(vec3 scaling) {
        this->scaling = scaling;
    }

    float getSpeed(){
        return this->speed;
    }

    void setSpeed(float speed) {
        this->speed = speed;
    }

    float getRotAngle() {
        return rotAngle;
    }

    void setRotAngle(float rotAngle) {
        this->rotAngle = rotAngle;
    }

    float getDirAngle() {
        return dirAngle;
    }

    void setDirAngle(float dirAngle) {
        this->dirAngle = dirAngle;
    }

    MyMesh setMesh(MyMesh amesh, float amb[], float diff[], float spec[], float emissive[], float shininess, int texcount, vec3 position) {
        memcpy(amesh.mat.ambient, amb, 4 * sizeof(float));
        memcpy(amesh.mat.diffuse, diff, 4 * sizeof(float));
        memcpy(amesh.mat.specular, spec, 4 * sizeof(float));
        memcpy(amesh.mat.emissive, emissive, 4 * sizeof(float));
        amesh.mat.shininess = shininess;
        amesh.mat.texCount = texcount;
        amesh.position = position;

        return amesh;
    }

    MyMesh* setMesh(MyMesh* amesh, float amb[], float diff[], float spec[], float emissive[], float shininess, int texcount, vec3 position) {
        memcpy(amesh->mat.ambient, amb, 4 * sizeof(float));
        memcpy(amesh->mat.diffuse, diff, 4 * sizeof(float));
        memcpy(amesh->mat.specular, spec, 4 * sizeof(float));
        memcpy(amesh->mat.emissive, emissive, 4 * sizeof(float));
        amesh->mat.shininess = shininess;
        amesh->mat.texCount = texcount;
        amesh->position = position;

        return amesh;
    }

    void setShaders(VSShaderLib shader, MyMesh mesh) {
        GLint loc;
        loc = glGetUniformLocation(shader.getProgramIndex(), "mat.ambient");
        glUniform4fv(loc, 1, mesh.mat.ambient);
        loc = glGetUniformLocation(shader.getProgramIndex(), "mat.diffuse");
        glUniform4fv(loc, 1, mesh.mat.diffuse);
        loc = glGetUniformLocation(shader.getProgramIndex(), "mat.specular");
        glUniform4fv(loc, 1, mesh.mat.specular);
        loc = glGetUniformLocation(shader.getProgramIndex(), "mat.shininess");
        glUniform1f(loc, mesh.mat.shininess);
        loc = glGetUniformLocation(shader.getProgramIndex(), "mat.texCount");
        glUniform1i(loc, mesh.mat.texCount);
    }

    void setShaders(VSShaderLib shader, MyMesh* mesh) {
        GLint loc;
        loc = glGetUniformLocation(shader.getProgramIndex(), "mat.ambient");
        glUniform4fv(loc, 1, mesh->mat.ambient);
        loc = glGetUniformLocation(shader.getProgramIndex(), "mat.diffuse");
        glUniform4fv(loc, 1, mesh->mat.diffuse);
        loc = glGetUniformLocation(shader.getProgramIndex(), "mat.specular");
        glUniform4fv(loc, 1, mesh->mat.specular);
        loc = glGetUniformLocation(shader.getProgramIndex(), "mat.shininess");
        glUniform1f(loc, mesh->mat.shininess);
        loc = glGetUniformLocation(shader.getProgramIndex(), "mat.texCount");
        glUniform1i(loc, mesh->mat.texCount);
    }

    void drawMesh(MyMesh mesh, VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformId, GLint lPos_uniformId) {
        // send matrices to OGL
        computeDerivedMatrix(PROJ_VIEW_MODEL);
        glUniformMatrix4fv(vm_uniformId, 1, GL_FALSE, mCompMatrix[VIEW_MODEL]);
        glUniformMatrix4fv(pvm_uniformId, 1, GL_FALSE, mCompMatrix[PROJ_VIEW_MODEL]);
        computeNormalMatrix3x3();
        glUniformMatrix3fv(normal_uniformId, 1, GL_FALSE, mNormal3x3);

        // Render mesh
        glBindVertexArray(mesh.vao);

        if (!shader.isProgramValid()) {
            printf("Program Not Valid!\n");
            exit(1);
        }
        glDrawElements(mesh.type, mesh.numIndexes, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    void drawMesh(MyMesh* mesh, VSShaderLib shader, GLint pvm_uniformId, GLint vm_uniformId, GLint normal_uniformId, GLint lPos_uniformId) {
        // send matrices to OGL
        computeDerivedMatrix(PROJ_VIEW_MODEL);
        glUniformMatrix4fv(vm_uniformId, 1, GL_FALSE, mCompMatrix[VIEW_MODEL]);
        glUniformMatrix4fv(pvm_uniformId, 1, GL_FALSE, mCompMatrix[PROJ_VIEW_MODEL]);
        computeNormalMatrix3x3();
        glUniformMatrix3fv(normal_uniformId, 1, GL_FALSE, mNormal3x3);

        // Render mesh
        glBindVertexArray(mesh->vao);

        if (!shader.isProgramValid()) {
            printf("Program Not Valid!\n");
            exit(1);
        }

        glDrawElements(mesh->type, mesh->numIndexes, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
};

#endif
