/*
 * VoxelListCategorizer.cpp
 *
 *  Created on: 3 Aug 2015
 *      Author: erik
 */

#include "VoxelListCategorizer.h"
#include "VoxelToTopy.h"

VoxelListCategorizer::VoxelListCategorizer() {
	// TODO Auto-generated constructor stub

}

VoxelListCategorizer::~VoxelListCategorizer() {
	// TODO Auto-generated destructor stub
}

void VoxelListCategorizer::addCellToLists(int cellIndex, VoxelCategories cellFlag, std::vector<int> dimensions) {
	switch(cellFlag)
	{
	case FIXED_X:
		fixedIndicesX.push_back(VoxelToTopy::convertIndexNode(cellIndex,dimensions));
		break;
	case FIXED_Y:
		fixedIndicesY.push_back(VoxelToTopy::convertIndexNode(cellIndex,dimensions));
		break;
	case FIXED_Z:
		fixedIndicesZ.push_back(VoxelToTopy::convertIndexNode(cellIndex,dimensions));
		break;
	case LOADED_X:
		loadedIndicesX.push_back(VoxelToTopy::convertIndexNode(cellIndex,dimensions));
		break;
	case LOADED_Y:
		loadedIndicesY.push_back(VoxelToTopy::convertIndexNode(cellIndex,dimensions));
		break;
	case LOADED_Z:
		loadedIndicesZ.push_back(VoxelToTopy::convertIndexNode(cellIndex,dimensions));
		break;
	case ACTIVE:
		activeIndices.push_back(VoxelToTopy::convertIndexCell(cellIndex,dimensions));
		break;
	case PASSIVE:
		passiveIndices.push_back(VoxelToTopy::convertIndexCell(cellIndex,dimensions));
		break;
	default:
		break;
	}

}

void VoxelListCategorizer::readArrayOfCells(std::vector<int> cellArray, std::vector<int> dimensions) {

	for(int cellIndex = 0; cellIndex < cellArray.size(); ++cellIndex )
	{
		addCellToLists(cellIndex,static_cast<VoxelCategories>(cellArray[cellIndex]), dimensions);
	}
}


