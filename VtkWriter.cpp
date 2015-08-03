/*
 * VtkWriter.cpp
 *
 *  Created on: Aug 3, 2015
 *      Author: friedrich
 */

#include "VtkWriter.h"

VtkWriter::VtkWriter() {
	// TODO Auto-generated constructor stub

}

VtkWriter::~VtkWriter() {
	// TODO Auto-generated destructor stub
}

void VtkWriter::writeHeader(std::ofstream &outfile) {
	  outfile << "# vtk DataFile Version 2.0\n";
	  outfile << "BGCE Project 2015-16\n";
	  outfile << "ASCII\n";
	  outfile << "\n";
}

void VtkWriter::writeStructuredGrid(std::ofstream &outfile,const long int dimensions[3],const float spacing){
	  outfile << "DATASET STRUCTURED_POINTS\n";
	  outfile << "DIMENSIONS  " << (int)dimensions[2] << " " << (int)dimensions[1] << " " << (int)dimensions[0] << "\n";
	  outfile << "ORIGIN " << 0 << " " << 0 << " " << 0 << "\n";
	  outfile << "SPACING " << spacing << " " << spacing << " " << spacing << "\n";
	  outfile << "\n";
}


void VtkWriter::writeScalars(std::ofstream &outfile, std::string scalarType, const std::vector<int> &scalars){
	  int totalSize = scalars.size();
	  outfile << "POINT_DATA " << totalSize << " \n";
	  outfile << "SCALARS " << scalarType << " float 1 \n";
	  outfile << "LOOKUP_TABLE default \n";
	  for (int i = 0; i < totalSize; i++){
	    outfile << (float)scalars[i] << "\n";
	  }
}
