#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <bitset>
#include <cstring>

/* Converts the voxelizer output file to an VTK file that can be viewed in Paraview. */

using namespace std;

int main(int argc, char** argv)
{
  /* The data_buffer is used to reaf data from the voxelizer output file and write to the VTK side-by-side. */
  /// TODO: Alter this buffer to make it of a larger size (currently only 1 Byte)

  char *data_buffer;
  int size_of_data_buffer = 1;
  data_buffer = new char[size_of_data_buffer];

  /* The dimensions_buffer is used to pick up the x-, y-, and z-number of voxels in the voxelizer output file.
     It is destroyed after use.
     NOTE: Change the deltaDim to the voxelSize value that is provided to the voxelizer for this geometry! */
  /// TODO: Get deltaDim (the width of a voxel) from voxelizer

  char *dimensions_buffer;
  int size_of_dimensions_buffer = 3 * 8 * sizeof(char);
  dimensions_buffer = new char[size_of_dimensions_buffer];
  float deltaDim = 0.05;

  long int dimensions[3];

  ifstream infile;
  ofstream outfile;

  /// TODO: Add open success checks
  infile.open("STLFiles/Star.dat", ios::binary | ios::in);
  outfile.open("Star.vtk", ios::out);

  outfile << "# vtk DataFile Version 2.0\n";
  outfile << "BGCE Project 2015-16\n";
  outfile << "ASCII\n";
  outfile << "\n";
  outfile << "DATASET STRUCTURED_POINTS\n";

  /* Read in the dimensions from the voxelizer output file. Skip the first byte (useless) */
  infile.seekg(1, ios::beg);
  infile.read(dimensions_buffer, size_of_dimensions_buffer);
  std::memcpy(&dimensions[0], &dimensions_buffer[0], 24);
  free(dimensions_buffer);
  int total_points = dimensions[0]*dimensions[1]*dimensions[2];

  outfile << "DIMENSIONS  " << (int)dimensions[2] << " " << (int)dimensions[1] << " " << (int)dimensions[0] << "\n";
  outfile << "ORIGIN " << 0 << " " << 0 << " " << 0 << "\n";
  outfile << "SPACING " << deltaDim << " " << deltaDim << " " << deltaDim << "\n";

  outfile << "\n";
  outfile << "POINT_DATA " << total_points << " \n";
  outfile << "SCALARS density float 1 \n";
  outfile << "LOOKUP_TABLE default \n";

  /* Skip the first 1 + 3*8 = 25 bytes, and start reading in the data. Write it simultaneous to the VTK file */
  infile.seekg(25, ios::beg);
  for (int i = 0; i < total_points; i++){
    infile.read(data_buffer, size_of_data_buffer);
    outfile << (float)data_buffer[0] << "\n";
  }

  infile.close();
  outfile.close();
  free(data_buffer);

  return 0;
}
