/*
 * VoxelListCategorizer.h
 *
 *  Created on: 3 Aug 2015
 *      Author: erik
 */

#ifndef VOXELLISTCATEGORIZER_H_
#define VOXELLISTCATEGORIZER_H_

#include <vector>
#include <list>

//class for reading in the cells to be optimized, sorting them into lists for
//easy outputting into a topology optimizer input file
class VoxelListCategorizer {
public:
	enum VoxelCategories {FIXED_X=3, FIXED_Y, FIXED_Z,
		LOADED_X=13, LOADED_Y, LOADED_Z,
		ACTIVE=2, PASSIVE=0};


	VoxelListCategorizer();




	virtual ~VoxelListCategorizer();

	void addCellToLists(int cellIndex, VoxelCategories cellFlag);
	void readArrayOfCells(std::vector<int> cellArray);


private:
	std::list<int> fixedIndicesX, fixedIndicesY, fixedIndicesZ;
	std::list<int> loadedIndicesX, loadedIndicesY, loadedIndicesZ;
	std::list<int> activeIndices, passiveIndices;


};

#endif /* VOXELLISTCATEGORIZER_H_ */
