/*
 * VoxelToTopy.cpp
 *
 *  Created on: Aug 4, 2015
 *      Author: friedrich
 */

#include "VoxelToTopy.h"

#include <iostream>
VoxelToTopy::VoxelToTopy() {
	// TODO Auto-generated constructor stub

}

VoxelToTopy::~VoxelToTopy() {
	// TODO Auto-generated destructor stub
}

void VoxelToTopy::calculateFixtureNodes(std::string data, VoxelListCategorizer &voxelListCategorizer,std::vector<int> cellArray, std::vector<int> dimensions){
	std::vector<int> coordinates;

	std::list<int> fixedIndicesXTmp, fixedIndicesYTmp, fixedIndicesZTmp;

	int counter = 0;
	if(data.compare("Star")==0	){
		for(int i = 0; i < cellArray.size(); ++i){
			if(cellArray[i] == 1){
				coordinates = VoxelToTopy::getCellCoordinates(i,dimensions);
				if(coordinates[0] <= 3 || coordinates[0] >= dimensions[0]-3 ||
				   coordinates[2] <= 3 || coordinates[2] >= dimensions[2]-3){

					voxelListCategorizer.getActiveIndices().push_back(VoxelToTopy::convertIndexCell(i,dimensions));

					std::cout << "Coordinates: " << i << "|" << coordinates[0] << "," << coordinates[1] << "," << coordinates[2] << "\n";

					//fixedIndicesXTmp.push_back(VoxelToTopy::convertIndex(i,dimensions));
					fixedIndicesYTmp.push_back(VoxelToTopy::convertIndexNode(i,dimensions));
					//fixedIndicesZTmp.push_back(VoxelToTopy::convertIndex(i,dimensions));

					counter = i;
				}
			}
		}
		fixedIndicesXTmp.push_back(VoxelToTopy::convertIndexNode(counter,dimensions));
		fixedIndicesZTmp.push_back(VoxelToTopy::convertIndexNode(counter,dimensions));
		voxelListCategorizer.setFixedIndicesX(fixedIndicesXTmp);
		voxelListCategorizer.setFixedIndicesY(fixedIndicesYTmp);
		voxelListCategorizer.setFixedIndicesZ(fixedIndicesZTmp);
	}
	else if(data.compare("Cube")==0)
	{
		for(int i = 0; i < cellArray.size(); ++i){
			if(cellArray[i] == 1){
				coordinates = VoxelToTopy::getCellCoordinates(i,dimensions);
				if(coordinates[0] == 0){

					voxelListCategorizer.getActiveIndices().push_back(VoxelToTopy::convertIndexCell(i,dimensions));

					std::cout << "Coordinates: " << i << "|" << coordinates[0] << "," << coordinates[1] << "," << coordinates[2] << "\n";

					fixedIndicesXTmp.push_back(VoxelToTopy::convertIndexNode(i,dimensions));
					fixedIndicesYTmp.push_back(VoxelToTopy::convertIndexNode(i,dimensions));
					//fixedIndicesZTmp.push_back(VoxelToTopy::convertIndex(i,dimensions));

					counter = i;
				}
			}
		}
		fixedIndicesZTmp.push_back(VoxelToTopy::convertIndexNode(counter,dimensions));
		voxelListCategorizer.setFixedIndicesX(fixedIndicesXTmp);
		voxelListCategorizer.setFixedIndicesY(fixedIndicesYTmp);
		voxelListCategorizer.setFixedIndicesZ(fixedIndicesZTmp);
	}
	else
	{
		std::cout << "VoxelToTopy::calculateFixtureNodes: Wrong scenario!\n";
		exit(-1);
	}
	std::cout << "LengthX" << cellArray.size() << "," << voxelListCategorizer.getFixedIndicesX().size() << std::endl;
	std::cout << "LengthY" << cellArray.size() << "," << voxelListCategorizer.getFixedIndicesY().size() << std::endl;
	std::cout << "LengthZ" << cellArray.size() << "," << voxelListCategorizer.getFixedIndicesZ().size() << std::endl;
}

void VoxelToTopy::calculateLoadNodes(std::string data, VoxelListCategorizer &voxelListCategorizer,std::vector<int> cellArray, std::vector<int> dimensions){
	std::vector<int> coordinates(3);
	std::vector<double> center(3);
	std::list<int> loadIndicesXTmp, loadIndicesYTmp, loadIndicesZTmp;
	double distx,distz;

	if(data.compare("Star")==0	){
		center[0] = (dimensions[0]/2.0);
		center[1] = (dimensions[1]/2.0);
		center[2] = (dimensions[2]/2.0);

		for(int i = 0; i < cellArray.size(); ++i){
			if(cellArray[i] == 1){
				coordinates = VoxelToTopy::getCellCoordinates(i,dimensions);
				distx = coordinates[0]-center[0];
				distz = coordinates[2]-center[2];
				if(distx*distx + distz*distz  <= 36 && distx*distx + distz*distz  >= 16){
					voxelListCategorizer.getActiveIndices().push_back(VoxelToTopy::convertIndexCell(i,dimensions));
					loadIndicesYTmp.push_back(VoxelToTopy::convertIndexNode(i,dimensions));
				}
			}
		}
		voxelListCategorizer.setLoadedIndicesY(loadIndicesYTmp);
	}
	else if(data.compare("Cube")==0)
	{
		for(int i = 0; i < cellArray.size(); ++i){
			if(cellArray[i] == 1){
				coordinates = VoxelToTopy::getCellCoordinates(i,dimensions);
				if(coordinates[0]  == dimensions[0]-2 && coordinates[1] == dimensions[1]-2 && coordinates[2] == static_cast<int>(dimensions[2]/2)){
					//voxelListCategorizer.getActiveIndices().push_back(VoxelToTopy::convertIndexCell(i,dimensions));
					loadIndicesYTmp.push_back(VoxelToTopy::convertIndexNode(i,dimensions));
				}
			}
		}
		voxelListCategorizer.setLoadedIndicesY(loadIndicesYTmp);
	}
	else
	{
		std::cout << "VoxelToTopy::calculateLoadNodes: Wrong scenario!\n";
		exit(-1);
	}
	std::cout << "LoadY" << cellArray.size() << "," << voxelListCategorizer.getLoadedIndicesY().size() << std::endl;
}

int VoxelToTopy::convertIndexCell(int index, std::vector<int> dimensions){
	std::vector<int> temp = VoxelToTopy::getCellCoordinates(index,dimensions);
	return VoxelToTopy::getCellIndex(temp[0],temp[1],temp[2],dimensions);
}

int VoxelToTopy::getCellIndex(int xCoord, int yCoord, int zCoord,
		std::vector<int> dimensions) {
	return yCoord + dimensions[1]*(xCoord + dimensions[0] * zCoord);
}

int VoxelToTopy::convertIndexNode(int index, std::vector<int> dimensions){
	std::vector<int> temp = VoxelToTopy::getCellCoordinates(index,dimensions);
	return VoxelToTopy::getNodeIndex(temp[0],temp[1],temp[2],dimensions);
}

int VoxelToTopy::getNodeIndex(int xCoord, int yCoord, int zCoord,
		std::vector<int> dimensions) {
	return yCoord + (dimensions[1]+1)*(xCoord + (dimensions[0]+1) * zCoord);
}

std::vector<int> VoxelToTopy::getCellCoordinates(int index, std::vector<int> dimensions)
{
std::vector<int> returnCoords(3);

returnCoords[0] = index%dimensions[0];
//temporary
returnCoords[2] = (index-returnCoords[0])/dimensions[0];
returnCoords[1] = returnCoords[2] % dimensions[1];
returnCoords[2] = (returnCoords[2] - returnCoords[1]) / dimensions[1];

return returnCoords;

}

