/*
 * TpdWriter.cpp
 *
 *  Created on: Aug 3, 2015
 *      Author: friedrich
 */

#include "TpdWriter.h"

#include <iostream>

TpdWriter::TpdWriter() {
	// TODO Auto-generated constructor stub

}

TpdWriter::~TpdWriter() {
	// TODO Auto-generated destructor stub
}

void TpdWriter::writeHeader(std::ofstream &outfile, std::string outputName){
	outfile << "[ToPy Problem Definition File v2007]\n";
	outfile << "\n";

	outfile << "PROB_TYPE:   comp\n";
	outfile << "PROB_NAME:   " << outputName << "\n";
	outfile << "ETA:         0.4\n";
	outfile << "DOF_PN:      3\n";
	outfile << "VOL_FRAC:    0.15\n";
	outfile << "FILT_RAD:    1.5\n";
	outfile << "ELEM_K:      H8\n";
	outfile << "NUM_ITER:    40\n";
}

void TpdWriter::writeDimensions(std::ofstream &outfile, std::vector<int> dimensions){
	outfile << "NUM_ELEM_X:  " << dimensions[0] << "\n";
	outfile << "NUM_ELEM_Y:  " << dimensions[1] << "\n";
	outfile << "NUM_ELEM_Z:  " << dimensions[2] << "\n";
	outfile << "\n";
}

void TpdWriter::writeGreyScaleFilters(std::ofstream &outfile){
	outfile << "# Grey-scale filter (GSF)\n";
	outfile << "P_FAC      : 1\n";
	outfile << "P_HOLD     : 15\n";
	outfile << "P_INCR     : 0.2\n";
	outfile << "P_CON      : 1\n";
	outfile << "P_MAX      : 3\n";
	outfile << "\n";
	outfile << "Q_FAC      : 1\n";
	outfile << "Q_HOLD     : 15\n";
	outfile << "Q_INCR     : 0.05\n";
	outfile << "Q_CON      : 1\n";
	outfile << "Q_MAX      : 5\n";
}

void TpdWriter::writeNodes(std::ofstream &outfile, VoxelListCategorizer &voxelListCategorizer){
	writeCellList(outfile, std::string("FXTR_NODE_X"), voxelListCategorizer.getFixedIndicesX());
	writeCellList(outfile, std::string("FXTR_NODE_Y"), voxelListCategorizer.getFixedIndicesY());
	writeCellList(outfile, std::string("FXTR_NODE_Z"), voxelListCategorizer.getFixedIndicesZ());

	writeCellList(outfile, std::string("LOAD_NODE_X"), voxelListCategorizer.getLoadedIndicesX());
	writeCellList(outfile, std::string("LOAD_NODE_Y"), voxelListCategorizer.getLoadedIndicesY());
	writeCellList(outfile, std::string("LOAD_NODE_Z"), voxelListCategorizer.getLoadedIndicesZ());

	writeCellList(outfile, std::string("PASV_ELEM"), voxelListCategorizer.getPassiveIndices());
	writeCellList(outfile, std::string("ACTV_ELEM"), voxelListCategorizer.getActiveIndices());

	writeLoads(outfile, "LOAD_VALU_Y", -1, voxelListCategorizer.getLoadedIndicesY().size());
}

void TpdWriter::writeLoads(std::ofstream &outfile, std::string variableName, double value, int number){
	outfile << variableName << ": " << value << "@" << number << "\n";
}

void TpdWriter::calculateFixtureNodes(std::string data, VoxelListCategorizer &voxelListCategorizer,std::vector<int> cellArray, std::vector<int> dimensions){
	std::vector<int> coordinates;

	std::list<int> fixedIndicesXTmp, fixedIndicesYTmp, fixedIndicesZTmp;

	if(data.compare("Star")==0	){
		for(int i = 0; i < cellArray.size(); ++i){
			if(cellArray[i] == 1){
				coordinates = VoxelListCategorizer::getCellCoordinates(i,dimensions);
				if(coordinates[0] <= 1 || coordinates[0] >= dimensions[0]-1 ||
				   coordinates[2] <= 1 || coordinates[2] >= dimensions[2]-1){
					std::cout << "Coordinates: " << i << "|" << coordinates[0] << "," << coordinates[1] << "," << coordinates[2] << "\n";
					//fixedIndicesXTmp.push_back(getCellIndex(coordinates[0],coordinates[1],coordinates[2],dimensions));
					fixedIndicesYTmp.push_back(getCellIndex(coordinates[0],coordinates[1],coordinates[2],dimensions));
					//fixedIndicesZTmp.push_back(getCellIndex(coordinates[0],coordinates[1],coordinates[2],dimensions));
			    }
			}
		}
		fixedIndicesXTmp.push_back(getCellIndex(coordinates[0],coordinates[1],coordinates[2],dimensions));
		fixedIndicesZTmp.push_back(getCellIndex(coordinates[0],coordinates[1],coordinates[2],dimensions));
		voxelListCategorizer.setFixedIndicesX(fixedIndicesXTmp);
		voxelListCategorizer.setFixedIndicesY(fixedIndicesYTmp);
		voxelListCategorizer.setFixedIndicesZ(fixedIndicesZTmp);
	}
	std::cout << "LengthX" << cellArray.size() << "," << voxelListCategorizer.getFixedIndicesX().size() << std::endl;
	std::cout << "LengthY" << cellArray.size() << "," << voxelListCategorizer.getFixedIndicesY().size() << std::endl;
	std::cout << "LengthZ" << cellArray.size() << "," << voxelListCategorizer.getFixedIndicesZ().size() << std::endl;
}

void TpdWriter::calculateLoadNodes(std::string data, VoxelListCategorizer &voxelListCategorizer,std::vector<int> cellArray, std::vector<int> dimensions){
	std::vector<int> coordinates(3);
	std::list<int> loadIndicesXTmp, loadIndicesYTmp, loadIndicesZTmp;

	if(data.compare("Star")==0	){
		coordinates[0] = static_cast<int>(dimensions[0]/2);
		coordinates[1] = static_cast<int>(dimensions[1]/2);
		coordinates[2] = static_cast<int>(dimensions[2]/2);

		loadIndicesYTmp.push_back(getCellIndex(coordinates[0],coordinates[1],coordinates[2],dimensions));

		voxelListCategorizer.setLoadedIndicesY(loadIndicesYTmp);
	}
}

void TpdWriter::writeCellList(std::ofstream &outfile,
		std::string variableName,
		std::list<int> cellIndices) {
	outfile<< variableName << ": ";
	if(cellIndices.size()>0)
	{

		auto listIterator = cellIndices.begin();
		outfile << *listIterator +1;
		++listIterator;

		if(cellIndices.size()>1)
		{
			for (; listIterator != cellIndices.end(); ++listIterator)
			{
				outfile << "; "<< *listIterator +1;
			}
		}
	}


	outfile << std::endl;

}

int TpdWriter::getCellIndex(int xCoord, int yCoord, int zCoord,
		std::vector<int> dimensions) {
	return yCoord + dimensions[1]*(xCoord + dimensions[0] * zCoord);
}

std::vector<int> TpdWriter::getCellCoordinates(int index,
		std::vector<int> dimensions) {
	std::vector<int> returnCoords(3);

	returnCoords[1] = index%dimensions[1];
	//temporary
	returnCoords[2] = (index-returnCoords[1])/dimensions[1];
	returnCoords[0] = returnCoords[2] % dimensions[0];
	returnCoords[2] = (returnCoords[2] - returnCoords[0]) / dimensions[0];

	return returnCoords;

}


