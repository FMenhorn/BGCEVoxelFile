/*
 * VoxelToTopy.h
 *
 *  Created on: Aug 4, 2015
 *      Author: friedrich
 */

#ifndef VOXELTOTOPY_H_
#define VOXELTOTOPY_H_

#include <string>
#include <vector>

#include "VoxelListCategorizer.h"

/*
 *
 */
class VoxelToTopy {
public:
	VoxelToTopy();
	virtual ~VoxelToTopy();

	void calculateFixtureNodes(std::string data, VoxelListCategorizer &voxelListCategorizer,std::vector<int> cellArray, std::vector<int> dimensions);
	void calculateLoadNodes(std::string data, VoxelListCategorizer &voxelListCategorizer,std::vector<int> cellArray, std::vector<int> dimensions);

	static int convertIndexCell(int index, std::vector<int> dimensions);
	static int convertIndexNode(int index, std::vector<int> dimensions);
	static int getCellIndex(int xCoord, int yCoord, int zCoord, std::vector<int> dimensions);
	static int getNodeIndex(int xCoord, int yCoord, int zCoord,std::vector<int> dimensions);
	static std::vector<int> getCellCoordinates(int index, std::vector<int> dimensions);
};

#endif /* VOXELTOTOPY_H_ */
