# MakeNEB
This is the simple script by C++ to make POSCAR files for VASP NEB calculation.
I think this work in linux and mac.
I think it does not work in windows, because "mkdir" and "entry->d_type" are not working.


## How to make
1. cmake CMakeLists.txt
2. make

## How to Use
1. make dir 00 and the last directory 0*; ex. 04, 06 etc...
2. make POSCAR in 00 and the last directory.
3. run MakeNEB.
   Directoreis and POSCAR are generated.
   
