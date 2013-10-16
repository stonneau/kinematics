#include "kinematics/joint.h"
#include "kinematics/joint_io.h"

#include "tools.h"


namespace kinematics
{
typedef joint<float, float, 2, 5, true> joint_2_t;
typedef joint<float, float, 3, 5, true> joint_3_t;
}

using namespace std;
using namespace tools;
using namespace kinematics;

void JointCreationTest(bool& error)
{
	joint_2_t joint2;
	joint_3_t joint;
	joint_3_t jointChild;
	joint.addChild(&jointChild);
}

void JointSaveTest(bool& error)
{
	std::string targetFile("./bin/Robot0.txt");
	joint_3_t j00, j10, j11, j12, j110, j111, j120;
	j00.addChild(&j10);
	j00.addChild(&j11);
	j00.addChild(&j12);
	j11.addChild(&j110);
	j11.addChild(&j111);
	j12.addChild(&j120);
	if(!kinematics::WriteTree<joint_3_t,3>(j00, targetFile))
	{
		std::cout << "In JointSaveTest: can not write file Robot0.txt."<< std::endl;
		error = true;
		return;
	}
	if(!CompareFiles(targetFile, std::string("./tests/Robot0.txt")))
	{
		error = true;
		std::cout << "In JointSaveTest: template file and resulting files have different content."<< std::endl;
	}
	if(!(remove(targetFile.c_str()) == 0))
	{
		error = true;
		std::cout << "In JointSaveTest: can not remove Robot0.txt."<< std::endl;
	}
}

int main(int argc, char *argv[])
{
	std::cout << "performing tests... \n";
	bool error = false;
	JointCreationTest(error);
	JointSaveTest(error);
	if(error)
	{
		std::cout << "There were some errors\n";
		return -1;
	}
	else
	{
		std::cout << "no errors found \n";
		return 0;
	}
}
