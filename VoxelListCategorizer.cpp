/*
 * VoxelListCategorizer.cpp
 *
 *  Created on: 3 Aug 2015
 *      Author: erik
 */

#include "VoxelListCategorizer.h"

VoxelListCategorizer::VoxelListCategorizer() {
	// TODO Auto-generated constructor stub

}

VoxelListCategorizer::~VoxelListCategorizer() {
	// TODO Auto-generated destructor stub
}

void VoxelListCategorizer::addCellToLists(int cellIndex, VoxelCategories cellFlag) {
	switch(cellFlag)
	{
	case FIXED_X:
		fixedIndicesX.push_back(cellIndex);
		break;
	case FIXED_Y:
		fixedIndicesY.push_back(cellIndex);
		break;
	case FIXED_Z:
		fixedIndicesZ.push_back(cellIndex);
		break;
	case LOADED_X:
		loadedIndicesX.push_back(cellIndex);
		break;
	case LOADED_Y:
		loadedIndicesY.push_back(cellIndex);
		break;
	case LOADED_Z:
		loadedIndicesZ.push_back(cellIndex);
		break;
	case ACTIVE:
		activeIndices.push_back(cellIndex);
		break;
	case PASSIVE:
		passiveIndices.push_back(cellIndex);
		break;
	default:
		break;
	}

}

void VoxelListCategorizer::readArrayOfCells(std::vector<int> cellArray) {

	for(int cellIndex = 0; cellIndex < cellArray.size(); ++cellIndex )
	{
		addCellToLists(cellIndex,static_cast<VoxelCategories>(cellArray[cellIndex]));
	}
}


