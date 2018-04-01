#ifndef JOINT_H
#define JOINT_H

#include "la.h"
#include <glm/gtc/quaternion.hpp>

class Joint
{
public:
    Joint();

    /*
•	Name: The name of this joint which will be displayed in your QTreeWidget of joints.
•	Parent: The joint that is the parent of this joint.
•	Children: The set of joints that have this joint as their parent.
•	Position: The position of this joint relative to its parent joint.
•	Rotation: The quaternion that represents this joint's current orientation.
•	Bind Matrix: The inverse of the joint's compound transformation matrix at the time a mesh is bound to the joint's skeleton.
     */

    std::string Name;
    Joint* parent;
    std::vector<Joint*> children;
    glm::vec3 pos;
    glm::quat rot;
    glm::mat4 bind_matrix;

    //when update, use this to store the overall transformatinos
    glm::mat4 trans;

    //Functions:

    glm::mat4 GetLocalTransformation();
    glm::mat4 GetOverallTransformation();

    //update rot from angle and axis
    void rotate(float a,glm::vec3 axis);

};

#endif // JOINT_H
