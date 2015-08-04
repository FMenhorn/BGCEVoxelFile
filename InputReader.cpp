#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <bitset>
#include <cstring>
#include <vector>

#include "VtkWriter.h"
#include "TpdWriter.h"
#include "VoxelListCategorizer.h"
#include "VoxelToTopy.h"

/* Converts the voxelizer output file to an VTK file that can be viewed in Paraview. */

using namespace std;

int main(int argc, char** argv)
{
  /* The data_buffer is used to read data from the voxelizer output file and write to the VTK side-by-side. */
  /// TODO: Alter this buffer to make it of a larger size (currently only 1 Byte)

  char *data_buffer;
  int size_of_data_buffer = 1;
  std::vector<int> voxelArray;
  data_buffer = new char[size_of_data_buffer];

  /* The dimensions_buffer is used to pick up the x-, y-, and z-number of voxels in the voxelizer output file.
     It is destroyed after use.
     NOTE: Change the deltaDim to the voxelSize value that is provided to the voxelizer for this geometry! */
  /// TODO: Get deltaDim (the width of a voxel) from voxelizer

  char *dimensions_buffer;
  int size_of_dimensions_buffer = 3 * 8 * sizeof(char);
  dimensions_buffer = new char[size_of_dimensions_buffer];
  float deltaDim = 0.05;

  long int dimensionsLong[3];
  std::vector<int> dimensions(3);

  VtkWriter vtkWriter;

  ifstream infile;
  ofstream outfile;

  /// TODO: Add open success checks
  infile.open("STLFiles/Star.dat", ios::binary | ios::in);
  outfile.open("Star.vtk", ios::out);

  vtkWriter.writeHeader(outfile);

  /* Read in the dimensions from the voxelizer output file. Skip the first byte (useless) */
  infile.seekg(1, ios::beg);
  infile.read(dimensions_buffer, size_of_dimensions_buffer);
  std::memcpy(&dimensionsLong[0], &dimensions_buffer[0], 24);
  for(int i = 0; i<3; ++i){
	  dimensions[2-i] = static_cast<int>(dimensionsLong[i]);
  }
  free(dimensions_buffer);
  int total_points = dimensions[0]*dimensions[1]*dimensions[2];

  vtkWriter.writeStructuredGrid(outfile, dimensions, deltaDim);

  /* Skip the first 1 + 3*8 = 25 bytes, and start reading in the data. Write it simultaneous to the VTK file and to the voxelArray */
  infile.seekg(25, ios::beg);
  for (int i = 0; i < total_points; i++){
    infile.read(data_buffer, size_of_data_buffer);
    voxelArray.push_back((int)data_buffer[0]);
  }

  vtkWriter.writeScalars(outfile, std::string("density"), voxelArray);

  infile.close();
  outfile.close();

  free(data_buffer);

  outfile.open("ToPyTest.tpd", ios::out);
  TpdWriter tpdWriter;
  VoxelListCategorizer voxelListCategorizer;
  VoxelToTopy voxelToTopy;
  voxelListCategorizer.readArrayOfCells(voxelArray, dimensions);

  tpdWriter.writeHeader(outfile, std::string("Star_ToOp"));
  tpdWriter.writeDimensions(outfile, dimensions);
  tpdWriter.writeGreyScaleFilters(outfile);

  voxelToTopy.calculateFixtureNodes(std::string("Star"),voxelListCategorizer, voxelArray, dimensions);
  voxelToTopy.calculateLoadNodes(std::string("Star"), voxelListCategorizer, voxelArray, dimensions);
  tpdWriter.writeNodes(outfile, voxelListCategorizer);

  outfile.close();

  return 0;
}
