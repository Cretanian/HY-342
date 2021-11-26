#pragma once

#include <iostream>
#include <cassert>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <cmath>
#include <math.h> 
#include <algorithm>


#define TESTPRINT ;std::cout << "test line\n";

class Body {
private:
    double X;
    double Y;
    double Vx;
    double Vy;
    double Ax;
    double Ay;
    double M;
    double BoxsR;
    std::string S;
    int marked;
    int ID;

public:

    Body() 
    {
        this->X = 0;
        this->Y = 0;
        this->Vx = 0;
        this->Vy = 0;
        this->M = 0;
        this->S = "";
        this->marked = 0;
        this->BoxsR = 0;
        this->ID = 0;
        this->Ax = 0;
        this->Ay = 0;
    };

    ~Body() {};

    void SetMyParams(std::vector<double> vectorPar, std::string str,int ID)
    {
        this->X = vectorPar[0];
        this->Y = vectorPar[1];
        this->Vx = vectorPar[2];
        this->Vy = vectorPar[3];
        this->M = vectorPar[4];
        this->S = str;
        this->marked = 0;
        this->BoxsR = 0;
        this->ID = ID;
        this->Ax = 0;
        this->Ay = 0;
    }

    void PrintInfo()
    {
        std::cout << "X: " << this->X << "\n";
        std::cout << "Y: " << this->Y << "\n";
        std::cout << "Vx: " << this->Vx << "\n";
        std::cout << "Vy: " << this->Vy << "\n";
        std::cout << "M: " << this->M << "\n";
        std::cout << "S: " << this->S << "\n\n";
    }

    void newPosition() {
        this->Vx += this->Ax;
        this->Vy += this->Ay;
        this->X  += this->Vx;
        this->Y  += this->Vy;
    }

    //SET && GET
    void setX_Y(double X, double Y) {
        this->X = X;
        this->Y = Y;
    }

    void setBoxsR(double R) {
        this->BoxsR = R;
    }

    void setX(double X) {
        this->X = X;
    }

    void setY(double Y) {
        this->Y = Y;
    }

    void setVx(double Vx) {
        this->Vx = Vx;
    }

    void setVy(double Vy) {
        this->Vy = Vy;
    }
    
    void setAx(double Ax) {
        this->Ax += Ax;
    }

    void setAy(double Ay) {
        this->Ay += Ay;
    }
    
    void setM(double M) {
        this->M = M;
    }

    void setMarked(int tmp) {
        this->marked = tmp;
    }

    double getX() {
        return this->X;
    }

    double getY() {
        return this->Y;
    }

    int getID() {
        return this->ID;
    }

    double getVx() {
        return this->Vx;
    }

    double getAx() {
        return this->Ax;
    }

    double getAy() {
        return this->Ay;
    }

    double getBoxR() {
        return this->BoxsR;
    }

    double getVy() {
        return this->Vy;
    }

    double getM() {
        return this->M;
    }

    int getMarked() {
        return this->marked;
    }

    std::string getName() {
        return this->S;
    }
};

class TreeNode {
private:
    double X;
    double Y;
    double M;
    double R;
    Body* mybody = nullptr;
    TreeNode* LLN = nullptr;
    TreeNode* LN = nullptr;
    TreeNode* RN = nullptr;
    TreeNode* RRN = nullptr;

public:
    std::vector<int> myBodiesID;

    TreeNode() = default;

    TreeNode(double X, double Y, double R)
    {
        this->X = X;
        this->Y = Y;
        this->M = 0;
        this->R = R;
    }

    ~TreeNode() {};

    //GET & SET

    double getX()
    {
        return this->X;
    }

    double getM()
    {
        return this->M;
    }

    double getY()
    {
        return this->Y;
    }

    double getR()
    {
        return this->R;
    }

    void setY(double Y)
    {
        this->Y = Y;
    }

    void setX(double X)
    {
        this->X = X;
    }

    void setR(double R)
    {
        this->R = R;
    }

    void setM(double M)
    {
        this->M = M;
    }

    TreeNode* getLLN() {
        return this->LLN;
    }

    TreeNode* getLN() {
        return this->LN;
    }

    TreeNode* getRRN() {
        return this->RRN;
    }

    TreeNode* getRN() {
        return this->RN;
    }

    Body* getMyBody() {
        return this->mybody;
    }

    void setMyBody(Body* tmp) {
        this->mybody = tmp;
    }

    void setLLN(TreeNode* tmp) {
        this->LLN = tmp;
    }

    void setLN(TreeNode* tmp) {
        this->LN = tmp;
    }

    void setRRN(TreeNode* tmp) {
        this->RRN = tmp;
    }

    void setRN(TreeNode* tmp) {
        this->RN = tmp;
    }
    
    void addmybodiesID(std::vector<int>* addthisvec)
    {
        for (unsigned int i = 0; i < addthisvec->size(); ++i)
            this->myBodiesID.push_back(addthisvec->at(i));
    }
};

extern std::vector<Body> myBodies;

int FindNumBodies(TreeNode* node, double X, double Y, double R, int flag)
{
    int counter = 0;
    double _X = 0;
    double _Y = 0;
    int indic = 0;

    node->setMyBody(nullptr);

    for (unsigned int i = 0; i < myBodies.size(); ++i)
    {
        _X = myBodies.at(i).getX();
        _Y = myBodies.at(i).getY();
        if (counter > 1)
            break;

        if (((X - R) <= _X && _X <= (X + R)) && ((Y - R) <= _Y && _Y <= (Y + R)))
        {
            if (myBodies.at(i).getMarked() == 0)
            {
                myBodies.at(i).setMarked(flag);
                indic = i;
                ++counter;
            }
        }
    }

    if (counter == 1)
    {
        myBodies.at(indic).setMarked(-1);
        myBodies.at(indic).setBoxsR(R);
        node->setMyBody(&(myBodies.at(indic)));
        node->myBodiesID.push_back(indic);
    }

    return counter;
}

TreeNode* createTree(TreeNode* node, double X, double Y, double R, int flag)
{
    node = new TreeNode(X, Y, R);

    int numHelper = FindNumBodies(node, X, Y, R, flag);

    if (-1 < numHelper && numHelper < 2)
    {
        node->setLLN(nullptr);
        node->setLN(nullptr);
        node->setRN(nullptr);
        node->setRRN(nullptr);
        node->setM(0);
        node->setX(0);
        node->setY(0);

        if (numHelper == 1)
        {
            node->setM(node->getMyBody()->getM());
            node->setX(node->getMyBody()->getX());
            node->setY(node->getMyBody()->getY());
        }
        return node;
    }
    else
    {
        for (unsigned int i = 0; i < myBodies.size(); ++i)
            if (myBodies.at(i).getMarked() != -1)
                myBodies.at(i).setMarked(0);

        double newR = R / 2;
        node->setLLN(createTree(node->getLLN(), X - newR, Y + newR, newR, 1));
        node->setLN(createTree (node->getLN(), X - newR, Y - newR, newR, 2));
        node->setRN(createTree (node->getRN(), X + newR, Y - newR, newR, 3));
        node->setRRN(createTree(node->getRRN(), X + newR, Y + newR, newR, 4));

        assert(node->getLLN() != nullptr && node->getLN() != nullptr && node->getRN() != nullptr && node->getRRN() != nullptr);
        
        double m1 = node->getLLN()->getM();
        double m2 = node->getLN()->getM();
        double m3 = node->getRN()->getM();
        double m4 = node->getRRN()->getM();

        double x1 = node->getLLN()->getX();
        double x2 = node->getLN()->getX();
        double x3 = node->getRN()->getX();
        double x4 = node->getRRN()->getX();

        double y1 = node->getLLN()->getY();
        double y2 = node->getLN()->getY();
        double y3 = node->getRN()->getY();
        double y4 = node->getRRN()->getY();

        node->setM(m1 + m2 + m3 + m4);

        assert(node->getM() != 0 && "One Body has M == 0");

        node->setX((x1 * m1 + x2 * m2 + x3 * m3 + x4 * m4) / node->getM());

        node->setY((y1 * m1 + y2 * m2 + y3 * m3 + y4 * m4) / node->getM());

        if(node->getLLN()->myBodiesID.size() != 0)
            node->addmybodiesID(&(node->getLLN()->myBodiesID));

        if (node->getLN()->myBodiesID.size() != 0)
            node->addmybodiesID(&(node->getLN()->myBodiesID));

        if (node->getRN()->myBodiesID.size() != 0)
            node->addmybodiesID(&(node->getRN()->myBodiesID));

        if (node->getRRN()->myBodiesID.size() != 0)
            node->addmybodiesID(&(node->getRRN()->myBodiesID));

    }
    return node;
}


bool ContainsBody(Body* b, TreeNode* n)
{
    if (std::find(n->myBodiesID.begin(), n->myBodiesID.end(), b->getID()) != n->myBodiesID.end())
        return true;
    else
        return false;
}

void FindForce(Body *b, TreeNode* n)
{
    bool iAmleaf = (n->getLLN() == nullptr && n->getLN() == nullptr && n->getRN() == nullptr && n->getRRN() == nullptr);
    
    if (iAmleaf && (n->getMyBody() == nullptr || n->getMyBody() == b))
        return;
    
    double X = n->getX() - b->getX();
    double Y = n->getY() - b->getY();
    
    double distance = sqrt(pow(X, 2) + pow(Y, 2));

    double range = 2 * b->getBoxR();

    if ((((distance - range) > 0) && !ContainsBody(b, n)) || iAmleaf)
    {
        assert(distance != 0 && "Bad Input: The distance between the points is Zero");
        
        double G = 6.67 * pow((double)10, (double)-11);

        double F = G * ((n->getM() * b->getM()) / pow(distance, 2));

        double Fx = (F * ((n->getX() - b->getX()) / distance));
        double Fy = (F * ((n->getY() - b->getY()) / distance));

        double Ax = Fx / b->getM();
        double Ay = Fy / b->getM();

        b->setAx(Ax);
        b->setAy(Ay);

    }
    else if (((distance - range) <= 0) || ContainsBody(b, n))
    {
        FindForce(b, n->getLLN());
        FindForce(b, n->getLN());
        FindForce(b, n->getRN());
        FindForce(b, n->getRRN());
    }
    else
        assert(false);

    return;
}

void createOutputFile(std::vector<Body> myBodies, double NumberOfBodies, double RangeOfUniverse)
{
    std::ofstream OutputFile;
    OutputFile.open("output.txt");
    assert(OutputFile && "Error in creating file!!!");

    OutputFile << NumberOfBodies << std::endl;
    OutputFile << RangeOfUniverse << std::endl;
    
    for (unsigned int i = 0; i < myBodies.size(); ++i)
    {
        OutputFile << myBodies.at(i).getX() << " ";
        OutputFile << myBodies.at(i).getY() << " ";
        OutputFile << myBodies.at(i).getVx() << " ";
        OutputFile << myBodies.at(i).getVy() << " ";
        OutputFile << myBodies.at(i).getM() << " ";
        OutputFile << myBodies.at(i).getName() << "\n";
    }

    OutputFile.close();
}

TreeNode* FreeTrees(TreeNode* node)
{
    if (node == nullptr)
        return nullptr;
    else
    {
        TreeNode* LLN = FreeTrees(node->getLLN());
        TreeNode* LN = FreeTrees(node->getLN());
        TreeNode* RN = FreeTrees(node->getRN());
        TreeNode* RRN = FreeTrees(node->getRRN());
        if (LLN != nullptr && LN != nullptr && RN != nullptr && RRN != nullptr)
        {
            LLN->~TreeNode();
            LN->~TreeNode();
            RN->~TreeNode();
            RRN->~TreeNode();
        }
    }

    return node;
}
