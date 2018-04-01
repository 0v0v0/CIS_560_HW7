#include "mainwindow.h"
#include <ui_mainwindow.h>
#include "cameracontrolshelp.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mygl->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Update_button_clicked()
{
    int vert_size=ui->mygl->loaded_obj.vertices.size();
    int edge_size=ui->mygl->loaded_obj.halfedges.size();
    int face_size=ui->mygl->loaded_obj.faces.size();
    int joint_size=ui->mygl->loaded_skeleton.joints.size();

    ui->List_Edge->clear();
    ui->List_Face->clear();
    ui->List_Vertex->clear();
    ui->List_Joints->clear();

    std::cout<<'\n'<<"vert_num"<<std::to_string(vert_size);
    std::cout<<'\n'<<"vert_num"<<std::to_string(edge_size);
    std::cout<<'\n'<<"vert_num"<<std::to_string(face_size);
    std::cout<<'\n'<<"vert_num"<<std::to_string(joint_size);

    for(int i=0;i<vert_size;i++)
    {
        std::string name=std::to_string(i);

        ui->List_Vertex->addItem(QString::fromStdString(name));
    }
    for(int i=0;i<edge_size;i++)
    {
        std::string name=std::to_string(i);

        ui->List_Edge->addItem(QString::fromStdString(name));
    }
    for(int i=0;i<face_size;i++)
    {
        std::string name=std::to_string(i);

        ui->List_Face->addItem(QString::fromStdString(name));
    }
    for(int i=0;i<joint_size;i++)
    {
        std::string name=std::to_string(i);

        ui->List_Joints->addItem(QString::fromStdString(name));
    }

    ui->mygl->setFocus();

}

void MainWindow::on_Subdivide_button_clicked()
{
    ui->mygl->loaded_obj.subdivision();
    std::cout<<"subdivided!";
    ui->mygl->update();
    //ui->mygl->paintGL();
    ui->mygl->setFocus();
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::exit();
}

void MainWindow::on_actionCamera_Controls_triggered()
{
    CameraControlsHelp* c = new CameraControlsHelp();
    c->show();
}

void MainWindow::on_List_Vertex_itemActivated(QListWidgetItem *item)
{
    int ID=item->text().toInt();
    std::cout<<'\n'<<"Vertex "<<std::to_string(ID);
    glm::vec3 pos=ui->mygl->loaded_obj.vertices.at(ID)->pos;
    std::cout<<" at: "<<glm::to_string(pos);
    ui->mygl->setFocus();
}

void MainWindow::on_List_Edge_itemActivated(QListWidgetItem *item)
{
    int ID=item->text().toInt();
    std::cout<<'\n'<<"Edge "<<std::to_string(ID);
    int connect=ui->mygl->loaded_obj.halfedges.at(ID)->vert->id;
    std::cout<<" is connected to: "<<std::to_string(connect);
    ui->mygl->setFocus();

}

void MainWindow::on_List_Face_itemActivated(QListWidgetItem *item)
{
    int ID=item->text().toInt();
    std::cout<<'\n'<<"Face "<<std::to_string(ID);
    int edge_num=ui->mygl->loaded_obj.faces.at(ID)->start->id;
    std::cout<<" starts at: "<<std::to_string(edge_num);
    ui->mygl->setFocus();
}

///
/// HW7
/// new functions
///

void MainWindow::on_List_Joints_itemActivated(QListWidgetItem *item)
{
    int ID=item->text().toInt();
    std::cout<<'\n'<<"Joint "<<std::to_string(ID);
    Joint* j=ui->mygl->loaded_skeleton.joints.at(ID);
    std::cout<<" is: "<<j->Name;
    glm::vec3 pos=j->pos;
    std::cout<<" at: "<<glm::to_string(pos);
    std::cout<<"rot=" <<j->rot[0]<<" "<<j->rot[1]<<" "<<j->rot[2]<<" "<<j->rot[3];
    ui->mygl->loaded_skeleton.selected_joint=ID;
    ui->mygl->setFocus();
}

void MainWindow::on_Bind_Skin_clicked()
{
    ui->mygl->loaded_obj.bind_skin(ui->mygl->loaded_skeleton);
    ui->mygl->setFocus();
}

float degree = 5.0f*3.14159/180.0f;

void MainWindow::on_X_plus_clicked()
{
    ui->mygl->loaded_skeleton.joints.at(ui->mygl->loaded_skeleton.selected_joint)->rotate(degree,glm::vec3(1,0,0));
    ui->mygl->loaded_skeleton.update(ui->mygl->loaded_skeleton.joints.at(ui->mygl->loaded_skeleton.selected_joint));
    ui->mygl->loaded_obj.update_Vertices(ui->mygl->loaded_skeleton);
    ui->mygl->update();
    ui->mygl->setFocus();
}
void MainWindow::on_X_decrease_clicked()
{
    ui->mygl->loaded_skeleton.joints.at(ui->mygl->loaded_skeleton.selected_joint)->rotate(-degree,glm::vec3(1,0,0));
    ui->mygl->loaded_skeleton.update(ui->mygl->loaded_skeleton.joints.at(ui->mygl->loaded_skeleton.selected_joint));
    ui->mygl->loaded_obj.update_Vertices(ui->mygl->loaded_skeleton);
    ui->mygl->update();
    ui->mygl->setFocus();
}
void MainWindow::on_Y_plus_clicked()
{
    ui->mygl->loaded_skeleton.joints.at(ui->mygl->loaded_skeleton.selected_joint)->rotate(degree,glm::vec3(0,1,0));
    ui->mygl->loaded_skeleton.update(ui->mygl->loaded_skeleton.joints.at(ui->mygl->loaded_skeleton.selected_joint));
    ui->mygl->loaded_obj.update_Vertices(ui->mygl->loaded_skeleton);
    ui->mygl->update();
    ui->mygl->setFocus();
}
void MainWindow::on_Y_decrease_clicked()
{
    ui->mygl->loaded_skeleton.joints.at(ui->mygl->loaded_skeleton.selected_joint)->rotate(-degree,glm::vec3(0,1,0));
    ui->mygl->loaded_skeleton.update(ui->mygl->loaded_skeleton.joints.at(ui->mygl->loaded_skeleton.selected_joint));
    ui->mygl->loaded_obj.update_Vertices(ui->mygl->loaded_skeleton);
    ui->mygl->update();
    ui->mygl->setFocus();
}
void MainWindow::on_Z_plus_clicked()
{
    ui->mygl->loaded_skeleton.joints.at(ui->mygl->loaded_skeleton.selected_joint)->rotate(degree,glm::vec3(0,0,1));
    ui->mygl->loaded_skeleton.update(ui->mygl->loaded_skeleton.joints.at(ui->mygl->loaded_skeleton.selected_joint));
    ui->mygl->loaded_obj.update_Vertices(ui->mygl->loaded_skeleton);
    ui->mygl->update();
    ui->mygl->setFocus();
}
void MainWindow::on_Z_decrease_clicked()
{
    ui->mygl->loaded_skeleton.joints.at(ui->mygl->loaded_skeleton.selected_joint)->rotate(-degree,glm::vec3(0,0,1));
    ui->mygl->loaded_skeleton.update(ui->mygl->loaded_skeleton.joints.at(ui->mygl->loaded_skeleton.selected_joint));
    ui->mygl->loaded_obj.update_Vertices(ui->mygl->loaded_skeleton);
    ui->mygl->update();
    ui->mygl->setFocus();
}

