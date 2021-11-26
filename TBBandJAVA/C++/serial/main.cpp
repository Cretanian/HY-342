#include "InfoData.h"


std::vector<Body> myBodies;

int main(int argc, char* argv[]) {
    assert(argv[1] != NULL && argv[2] != NULL && "Wrong input format!");
    
    unsigned int IterationNumber = atoi(argv[2]);
    unsigned int NumberOfBodies = 0;
    double RangeOfUniverse = 0;

    assert(IterationNumber >= 0);


    std::ifstream InputFile;
    InputFile.open(argv[1]);
    if (!InputFile) {
        std::cout << "File not opened!\n";
        assert(false);
    }
    
    std::string line = "";
    std::string delimiter = " ";
    std::string token = "";


    std::getline(InputFile, line);
    NumberOfBodies = std::stoi(line);
    assert(NumberOfBodies >= 0 && "BAD INPUT: Negative num of bodies");
 //   std::cout << "The number of Bodies is: " << NumberOfBodies << std::endl;

    std::getline(InputFile, line);
    RangeOfUniverse = std::stod(line);
    assert(RangeOfUniverse >= 0 && "BAD INPUT: Negative num of Range");
  //  std::cout << "The Range is: " << RangeOfUniverse << std::endl << std::endl;

    std::vector<double> HelperVector;
    std::string HelperName = "";

    for (unsigned int i = 0; i < NumberOfBodies; ++i)
    {
        std::getline(InputFile, line);
        auto start = 0U;
        auto end = line.find(delimiter);
        while (end != std::string::npos)
        {

            if (HelperVector.size() < 6)
                HelperVector.push_back(std::stof(line.substr(start, end - start)));

            start = end + delimiter.length();
            end = line.find(delimiter, start);
        }
        HelperName = line.substr(start, end - start);

        assert(HelperName != "" && HelperVector.size() == 5 && "Wrong file format!");
        assert(HelperVector.at(4) != 0 && "BAD INPUT: A body has a M == 0");
        assert( (abs(HelperVector.at(0)) <= RangeOfUniverse && abs(HelperVector.at(1)) <= RangeOfUniverse) 
                && "BAD INPUT: A body is out of range");
        
        Body HelperBody;
        HelperBody.SetMyParams(HelperVector, HelperName, i);

        myBodies.push_back(HelperBody);
        HelperName = "";
        HelperVector.clear();
    }

    InputFile.close();

  //  std::cout << "Size of myBodies vector: " << myBodies.size() << std::endl << std::endl;

    std::vector<TreeNode*> Trees;

    auto start = std::chrono::high_resolution_clock::now();

    for (unsigned int i = 0; i < IterationNumber; ++i) 
    {

        TreeNode* Root = nullptr;
        Root = createTree(Root, 0, 0, RangeOfUniverse, 1);

        for (unsigned int k = 0; k < myBodies.size(); ++k)
            assert(myBodies.at(k).getMarked() == -1 && "Input Error Body out of Range");
           
        for (unsigned int o = 0; o < myBodies.size(); ++o)
            FindForce(&myBodies.at(o), Root);

        for (unsigned int u = 0; u < myBodies.size(); ++u)
            myBodies.at(u).newPosition();

        for (unsigned int y = 0; y < myBodies.size(); ++y)
        {
            double X = myBodies.at(y).getX();
            double Y = myBodies.at(y).getY();

            for (unsigned int j = y + 1; j < myBodies.size(); ++j)
                if (X == myBodies.at(j).getX() && Y == myBodies.at(j).getY())
                {
                    myBodies.at(j).setX(X + 0.001);
                    myBodies.at(j).setY(Y + 0.001);
                }
        }

        for (unsigned int h = 0; h < myBodies.size(); ++h)
        {
            myBodies.at(h).setMarked(0);
            myBodies.at(h).setBoxsR(0);
        }

        Trees.push_back(Root);
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Timer took " << duration.count() << " ms ( " << ((double)duration.count() / 1000.0d) << " sec )\n";

    for (unsigned int i = 0; i < IterationNumber; ++i) {
        FreeTrees(Trees.at(i));
        Trees.at(i)->~TreeNode();
    }

    createOutputFile(myBodies, NumberOfBodies, RangeOfUniverse);

    return 0;
}
