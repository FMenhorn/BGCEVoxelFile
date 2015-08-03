/*
 * TpdWriter.h
 *
 *  Created on: Aug 3, 2015
 *      Author: friedrich
 */

#ifndef TPDWRITER_H_
#define TPDWRITER_H_

#include <fstream>
#include <list>
#include <string>
#include <vector>

#include "VoxelListCategorizer.h"
/*
 *
 */
class TpdWriter {
public:
	TpdWriter();
	virtual ~TpdWriter();

	void writeHeader(std::ofstream &outfile, const std::string outputName);
	void writeDimensions(std::ofstream &outfile, std::vector<int> dimensions);
	void writeGreyScaleFilters(std::ofstream &outfile);
	void writeNodes(std::ofstream &outfile, VoxelListCategorizer &voxelListCategorizer);
	void writeLoads(std::ofstream &outfile, std::string variableName, double value, int number);


	void calculateFixtureNodes(std::string data, VoxelListCategorizer &voxelListCategorizer,std::vector<int> cellArray, std::vector<int> dimensions);
	void calculateLoadNodes(std::string data, VoxelListCategorizer &voxelListCategorizer,std::vector<int> cellArray, std::vector<int> dimensions);

	void writeCellList(std::string variableName, std::list<int> cellIndices, std::ofstream &outfile);

	static int getCellIndex(int xCoord, int yCoord, int zCoord, std::vector<int> dimensions);
	static std::vector<int> getCellCoordinates(int index, std::vector<int> dimensions);


	void writeCellList(std::ofstream &outfile, std::string variableName, std::list<int> cellIndices);
};

#endif /* TPDWRITER_H_ */
