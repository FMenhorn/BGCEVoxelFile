/*
 * TpdWriter.cpp
 *
 *  Created on: Aug 3, 2015
 *      Author: friedrich
 */

#include "TpdWriter.h"

TpdWriter::TpdWriter() {
	// TODO Auto-generated constructor stub

}

TpdWriter::~TpdWriter() {
	// TODO Auto-generated destructor stub
}

void TpdWriter::writeHeader(std::ofstream &outfile, std::string outputName){
	  outfile << "# vtk DataFile Version 2.0\n";
	  outfile << "BGCE Project 2015-16\n";
	  outfile << "ASCII\n";
	  outfile << "\n";

	  outfile << "[BGCE Project ToPy Definition File 2015]\n";
	  outfile << "\n";

	  outfile << "PROB_TYPE:   comp\n";
	  outfile << "PROB_NAME:   " << outputName << "\n";
	  outfile << "ETA:         0.4\n";
	  outfile << "DOF_PN:      3\n";
	  outfile << "VOL_FRAC:    0.15\n";
	  outfile << "FILT_RAD:    1.5\n";
	  outfile << "ELEM_K:      H8\n";
}


void TpdWriter::writeCellList(std::string variableName,
		std::list<int> cellIndices, std::ofstream &outfile) {

	outfile<< std::endl;
	outfile<< variableName << ": ";
	for (auto listIterator = cellIndices.begin(); listIterator != cellIndices.end(); ++listIterator)
	{
		outfile << *listIterator << "; ";
	}
	outfile << std::endl;

}

