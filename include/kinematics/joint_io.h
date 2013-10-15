/**
* \file joint_io.h
* \brief io functions to save / load joints descriptions with text files.
* \author Steve T.
* \version 0.1
* \date 10/12/2013
*
* A joint is saved in a text file using the following format :
* ROOT ID xxx
* OFFSET xxx xxx xxx
* MINANGLES xxx xxx xxx
* MAXANGLES xxx xxx xxx
* DEFAULTANGLES xxx xxx xxx
* 
* JOINT ID xxx
* PARENT ID xxx
* OFFSET xxx xxx xxx
* MINANGLES xxx xxx xxx
* MAXANGLES xxx xxx xxx
* DEFAULTANGLES xxx xxx xxx
* 
*  ...
*/

#ifndef _STRUCT_JOINT_IO
#define _STRUCT_JOINT_IO

#include "joint.h"
#include <iostream>
#include <sstream>
#include <fstream>

namespace kinematics
{
///  \brief Saves a kinematic tree fromed by joints into a text
///  file.
///  \param joint the joint to save
///  \param file the name of the file in which the description must be written.
template<class T, int Dim>
void WriteTreeRec(const T& joint, std::stringstream& res, unsigned int& id)
{
	res << "\nOFFSET";
	for(int i = 0; i < Dim; ++i)
	{
		res << " " << joint.offset[i];
	} 
	res << "\nMINANGLES";
	for(int i = 0; i < Dim; ++i)
	{
		res << " " << joint.minAngleValues[i];
	} 
	res << "\nMAXANGLES";
	for(int i = 0; i < Dim; ++i)
	{
		res << " " << joint.maxAngleValues[i];
	}
	res << "\nDEFAULTANGLES";
	for(int i = 0; i < Dim; ++i)
	{
		res << " " << joint.defaultAngleValues[i];
	}
	res << "\n";
	unsigned int parentId = id;
	++id;
	for(int i=0; i < joint.nbChildren_; ++i)
	{
		res << "\nJOINT ID " << id;
		res << "\nPARENT ID " << parentId;
		WriteTreeRec<T, Dim>(*(joint.children[i]), res, id);
	}
}
		
///  \brief Saves a kinematic tree formed by joints into a text
///  file.
///  \param joint the root joint of the kinematic tree to save
///  \param file the name of the file in which the description must be written.
template<class T, int Dim>
bool WriteTree(const T& joint, const std::string& filename)
{
	unsigned int id =0;
	std::stringstream res; res << "ROOT ID 0 \n";
	WriteTreeRec<T, Dim>(joint, res, id);	
	std::ofstream myfile;
	myfile.open (filename.c_str());
	if (myfile.is_open())
	{
		myfile << res.rdbuf();
		myfile.close();
		return true;
	}
	return false;
}
}// end namespace kinematics
#endif //_STRUCT_JOINT_IO
