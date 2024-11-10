**Instruction**

1. build with cmake: 

        mkdir build

        cd build

        cmake -DCMAKE_BUILD_TYPE=debug ..

        make

2. run e2e tests:

        ./tests/run_*case_name* 

        input: 
        
            1st triangle 3d points
            2nd triangle 3d points 
        
        output:

            is_intersect

3. run unit gtests: 

        ./tests/run_gtest* 