#ifndef __AABB_H__
#define __AABB_H__

#include "GameObject.h"

class AABB{
    std::vector<vec3> vertices;
    vec3 min_pos, max_pos;
    bool colliding;

public:
    AABB(){}

    AABB(vec3 min_pos, vec3 max_pos) {
        this->min_pos = min_pos;
        this->max_pos = max_pos;
        vertices.push_back(min_pos);
        vertices.push_back({ min_pos.x, min_pos.y, max_pos.z });
        vertices.push_back({ min_pos.x, max_pos.y, min_pos.z });
        vertices.push_back({ max_pos.x, min_pos.y, min_pos.z });
        vertices.push_back({ max_pos.x, max_pos.y, min_pos.z });
        vertices.push_back({ max_pos.x, min_pos.y, max_pos.z });
        vertices.push_back({ min_pos.x, max_pos.y, max_pos.z });
        vertices.push_back(max_pos);
        colliding = false;
        
    }

    bool checkCollision(AABB bounding_box) {
        return ((this->min_pos.x <= bounding_box.max_pos.x && this->max_pos.x >= bounding_box.min_pos.x) &&
            (this->min_pos.y <= bounding_box.max_pos.y && this->max_pos.y >= bounding_box.min_pos.y) &&
            (this->min_pos.z <= bounding_box.max_pos.z && this->max_pos.z >= bounding_box.min_pos.z));
    }

    void updateAABB(vec3 offset) {
        for (auto& vertex : vertices) {
            vertex = vertex + offset;
        }
        
        float min_x = vertices.at(0).x, min_y = vertices.at(0).y, min_z = vertices.at(0).z;
        float max_x = vertices.at(0).x, max_y = vertices.at(0).y, max_z = vertices.at(0).z;

        for (auto& vertex : vertices) {
            if (vertex.x > max_x) max_x = vertex.x;
            if (vertex.y > max_y) max_y = vertex.y;
            if (vertex.z > max_z) max_z = vertex.z;
            if (vertex.x < min_x) min_x = vertex.x;
            if (vertex.y < min_y) min_y = vertex.y;
            if (vertex.z < min_z) min_z = vertex.z;
        }

        this->min_pos = { min_x, min_y, min_z };
        this->max_pos = { max_x, max_y, max_z };
    }

    void setMinPos(vec3 min_pos) {
        this->min_pos = min_pos;
    }
    
    void setMaxPos(vec3 max_pos) {
        this->max_pos = max_pos;
    }

    vec3 getMinPos() {
        return this->min_pos;
    }
    
    vec3 getMaxPos() {
        return this->max_pos;
    }

    bool isColliding() {
        return this->colliding;
    }

    void setColliding(bool val) {
        this->colliding = val;
    }

};

#endif