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
	enum VoxelCategories {FIXED_X=3, FIXED_Y=8, FIXED_Z=4,
		LOADED_X=13, LOADED_Y=6, LOADED_Z=5,
		ACTIVE=2, PASSIVE=0};

	VoxelListCategorizer();

	virtual ~VoxelListCategorizer();

	void addCellToLists(int cellIndex, VoxelCategories cellFlag, std::vector<int> dimensions);
	void readArrayOfCells(std::vector<int> cellArray, std::vector<int> dimensions);

	std::list<int>& getActiveIndices() {
		return activeIndices;
	}

	std::list<int>& getPassiveIndices() {
		return passiveIndices;
	}

	const std::list<int>& getFixedIndicesX() const {
		return fixedIndicesX;
	}

	const std::list<int>& getLoadedIndicesX() const {
		return loadedIndicesX;
	}

	const std::list<int>& getFixedIndicesY() const {
		return fixedIndicesY;
	}

	const std::list<int>& getLoadedIndicesY() const {
		return loadedIndicesY;
	}

	const std::list<int>& getFixedIndicesZ() const {
		return fixedIndicesZ;
	}

	const std::list<int>& getLoadedIndicesZ() const {
		return loadedIndicesZ;
	}

	void setActiveIndices(const std::list<int>& activeIndices) {
		this->activeIndices = activeIndices;
	}

	void setFixedIndicesX(const std::list<int>& fixedIndicesX) {
		this->fixedIndicesX = fixedIndicesX;
	}

	void setFixedIndicesY(const std::list<int>& fixedIndicesY) {
		this->fixedIndicesY = fixedIndicesY;
	}

	void setFixedIndicesZ(const std::list<int>& fixedIndicesZ) {
		this->fixedIndicesZ = fixedIndicesZ;
	}

	void setLoadedIndicesX(const std::list<int>& loadedIndicesX) {
		this->loadedIndicesX = loadedIndicesX;
	}

	void setLoadedIndicesY(const std::list<int>& loadedIndicesY) {
		this->loadedIndicesY = loadedIndicesY;
	}

	void setLoadedIndicesZ(const std::list<int>& loadedIndicesZ) {
		this->loadedIndicesZ = loadedIndicesZ;
	}

	void setPassiveIndices(const std::list<int>& passiveIndices) {
		this->passiveIndices = passiveIndices;
	}

private:
	std::list<int> fixedIndicesX, fixedIndicesY, fixedIndicesZ;
	std::list<int> loadedIndicesX, loadedIndicesY, loadedIndicesZ;
	std::list<int> activeIndices, passiveIndices;
};

#endif /* VOXELLISTCATEGORIZER_H_ */
