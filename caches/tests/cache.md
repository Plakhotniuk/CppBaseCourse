**Instruction**

1. build with cmake from repository root directory: 

        mkdir build

        cd build

        cmake -DCMAKE_BUILD_TYPE=debug ..

        make

2. run e2e tests:

        ./tests/run_*case_name* 

        input: 
        
            cache_size sequence_length

            page_num_sequence 
        
        output:

            num_of_hits

3. run unit gtests: 

        ./tests/run_gtest* 