/*
 * VtkWriter.h
 *
 *  Created on: Aug 3, 2015
 *      Author: friedrich
 */

#ifndef VTKWRITER_H_
#define VTKWRITER_H_

#include <fstream>
#include <string>
#include <vector>
/*
 *
 */
class VtkWriter {
public:
	VtkWriter();
	virtual ~VtkWriter();

	void writeHeader(std::ofstream &outfile);
	void writeStructuredGrid(std::ofstream &outfile,const long int dimensions[3],const float spacing);
	void writeScalars(std::ofstream &outfile, std::string scalarType, const std::vector<double> &scalars);
};

#endif /* VTKWRITER_H_ */
