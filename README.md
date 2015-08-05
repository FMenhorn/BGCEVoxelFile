# BGCEVoxelFile
Steps:

1. Convert `*.stl` file to voxelized `*.dat` file using the Voxelizer with size of voxel `voxelSize`. You need CVMLCPP for this - ask Friedi for more details.
	~/Path/To/CVMLCPP/bin/voxelize ./<stl_file>.stl <voxelSize>

2. Open `InputReader.cpp`.
   - Change `deltaDim` (line 29) to `voxelSize` value.
   - Provide the correct `infile` and `outfile` names.
Save `InputReader.cpp`

3. Open terminal in root and type:  

   `$ g++ -g -o InputReader InputReader.cpp`  
   `$ ./InputReader`

4. Open the VTK file with Paraview and visualize.
