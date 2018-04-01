#include "skeleton.h"

Skeleton::Skeleton()
{
    selected_joint=0;
}

//get help from:
//https://stackoverflow.com/questions/15893040/how-to-create-read-write-json-files-in-qt5
//https://stackoverflow.com/questions/32275149/how-to-parse-multidimensional-json-array-in-qt
//load Json
bool Skeleton::loadJson(QString name)
{
    QByteArray data;
    QFile file;
    file.setFileName(name);

    if(! file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        std::cout<<"\n skeleton file error!";
        return false;
    }
    std::cout<<"\n skeleton file find!";

    data = file.readAll();
    file.close();
    //qWarning() << val;
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject obj = doc.object();

    //This stuff can be converted to QVariant Map...
    //QVariant var=obj.value("root").toVariant();

    QJsonValue value = obj.value(QString("root"));
    //qWarning() << value;
    QJsonObject item = value.toObject();
    //qWarning() << tr("QJsonObject of description: ") << item;

    /*
     * "name": "Hip",
     * "pos": [-3, 0, 0],
     * "rot": [0, 1, 0, 0],
     * "children": [
     */

    Joint* root=new Joint();
    root->Name="root";
    root->pos=glm::vec3(0);
    root->rot=glm::quat(0,1,0,0);
    root->parent=NULL;

    joints.push_back(root);

    root->children.push_back(build_skeleton(item,root));
    root->trans=glm::mat4(1);
    update(root);
    qDebug()<<"Building Finished! Size= "<< joints.size();


    return true;
}

Joint* Skeleton::build_skeleton(QJsonObject item, Joint* parent)
{
    Joint* j=new Joint();
    QJsonValue subobj;
    QJsonArray subarray;

    subobj= item["name"];
    j->Name=subobj.toString().toStdString();

    subarray=item["pos"].toArray();
    j->pos=glm::vec3(subarray.at(0).toDouble(),subarray.at(1).toDouble(),subarray.at(2).toDouble());

    //FUCK json!!!
    //Rotation is defined as [angle, axis_x, axis_y, axis_z] rather than [w, i, j, k].
    //You will need to use this data to compute a quaternion.
    //No, it is stored as i,j,k,w!

    subarray=item["rot"].toArray();
    //axis
    glm::vec3 dir=glm::vec3(subarray.at(1).toDouble(),
                     subarray.at(2).toDouble(),
                     subarray.at(3).toDouble());
    //angle

    float a=subarray.at(0).toDouble();

    j->rot=glm::angleAxis(a,dir);

    j->parent=parent;

    joints.push_back(j);

    /*
    qWarning() << "building= " << QString(j->Name.c_str());
    qWarning() << "pos= " << j->pos[0] << " , " << j->pos[1] <<" , "<<j->pos[2] ;
    qWarning() << "axis= " << dir[0] << " , " << dir[1] <<" , "<< dir[2] <<"angle=" <<a;
    qWarning() << "rot= " << j->rot[0] << " , " << j->rot[1] <<" , "<<j->rot[2] <<" , "<<j->rot[3] ;
    */

    subarray=item["children"].toArray();
    for(int i=0;i<subarray.size();i++)
    {
        Joint* tmp;
        tmp = Skeleton::build_skeleton( subarray.at(i).toObject(),j );
        if(tmp!=NULL)
        {
            j->children.push_back(tmp);
        }
    }

    return j;
}

bool Skeleton::update(Joint* j)
{
    //Update trans here!!!
    if(j->parent!=NULL)
    {
        j->trans=j->parent->trans*j->GetLocalTransformation();
    }
    else
    {
        j->trans=j->GetLocalTransformation();
    }

    //j->trans=j->GetOverallTransformation();

    //update pos
    glm::vec4 pos=j->GetLocalTransformation() * glm::vec4(j->pos,0.0f);

    j->pos=glm::vec3(pos);

    //update children
    for(int i=0;i<j->children.size();i++)
    {
        if(j->children.at(i)!=NULL)
        {
            update(j->children.at(i));
        }
    }

    return true;
}
