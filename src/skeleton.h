#ifndef SKELETON_H
#define SKELETON_H

#include "joint.h"
#include "la.h"
#include "iostream"
#include "QString"
#include "QFile"
#include "QJsonArray"
#include "QJsonDocument"
#include "QJsonObject"

class Skeleton
{
public:
    Skeleton();

    //store all the joint pointers
    //root should be at 0
    std::vector<Joint*> joints;



    //Functions
    bool loadJson(QString name);
    //Iteration function used to build skeleton
    //take in JsonObj and parent, return builded joint as child
    Joint *build_skeleton(QJsonObject item, Joint *parent);

    int selected_joint;

    bool update(Joint *j);

};

#endif // SKELETON_H
