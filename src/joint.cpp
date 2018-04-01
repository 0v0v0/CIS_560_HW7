#include "joint.h"


Joint::Joint()
{

}

glm::mat4 Joint::GetLocalTransformation()
{
    glm::mat4 tmp;
    tmp= glm::translate(glm::mat4(1),pos);

    return glm::toMat4(rot)*tmp;
}


glm::mat4 Joint::GetOverallTransformation()
{
    Joint* up=parent;

    /*
    glm::mat4 tmp=GetLocalTransformation();

    while(up!=NULL)
    {
        tmp*=up->GetLocalTransformation();
        up=up->parent;
    }
    */

    if(up!=NULL)
    {
        return up->trans*GetLocalTransformation();
    }
    else
    {
        return trans;
    }


}

void Joint::rotate(float a,glm::vec3 axis)
{
    //rotate
    axis=glm::normalize(axis);

    glm::quat tmp=glm::angleAxis(a,axis);

    rot*=tmp;

    qWarning()<<"\n"<< Name.c_str() << " Rotated: " << rot[0] << " , " << rot[1] << " , "<< rot[2] << " , "<< rot[3];
}
