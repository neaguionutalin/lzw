## COMP0019 CW3 Grade Report
Report for commit SHA: 0b6be24ad4b7fdb05f88aa447cf0761e1a78c8c9

### Output


    -- The C compiler identification is GNU 5.4.0
    -- The CXX compiler identification is GNU 5.4.0
    -- Check for working C compiler: /usr/bin/cc
    -- Check for working C compiler: /usr/bin/cc -- works
    -- Detecting C compiler ABI info
    -- Detecting C compiler ABI info - done
    -- Detecting C compile features
    -- Detecting C compile features - done
    -- Check for working CXX compiler: /usr/bin/c++
    -- Check for working CXX compiler: /usr/bin/c++ -- works
    -- Detecting CXX compiler ABI info
    -- Detecting CXX compiler ABI info - done
    -- Detecting CXX compile features
    -- Detecting CXX compile features - done
    -- Setting build type to 'Debug' as none was specified.
    -- Looking for C++ include unistd.h
    -- Looking for C++ include unistd.h - found
    -- Looking for C++ include stdint.h
    -- Looking for C++ include stdint.h - found
    -- Looking for C++ include inttypes.h
    -- Looking for C++ include inttypes.h - found
    -- Looking for C++ include sys/types.h
    -- Looking for C++ include sys/types.h - found
    -- Looking for C++ include sys/stat.h
    -- Looking for C++ include sys/stat.h - found
    -- Looking for C++ include fnmatch.h
    -- Looking for C++ include fnmatch.h - found
    -- Looking for C++ include stddef.h
    -- Looking for C++ include stddef.h - found
    -- Check size of uint32_t
    -- Check size of uint32_t - done
    -- Looking for strtoll
    -- Looking for strtoll - found
    -- Configuring done
    -- Generating done
    -- Build files have been written to: /home/user/build
    Scanning dependencies of target gene_encode
    [  7%] Building C object CMakeFiles/gene_encode.dir/src/comp0019lib.c.o
    [ 14%] Building C object CMakeFiles/gene_encode.dir/src/comp0019.c.o
    /home/user/src/comp0019.c: In function 'Encode':
    /home/user/src/comp0019.c:3:19: warning: unused parameter 'in_file' [-Wunused-parameter]
     void Encode(FILE* in_file, FILE* out_file) {
                       ^
    /home/user/src/comp0019.c:3:34: warning: unused parameter 'out_file' [-Wunused-parameter]
     void Encode(FILE* in_file, FILE* out_file) {
                                      ^
    [ 21%] Building C object CMakeFiles/gene_encode.dir/src/decomp0019.c.o
    /home/user/src/decomp0019.c: In function 'Decode':
    /home/user/src/decomp0019.c:3:19: warning: unused parameter 'in_file' [-Wunused-parameter]
     void Decode(FILE* in_file, FILE* out_file) {
                       ^
    /home/user/src/decomp0019.c:3:34: warning: unused parameter 'out_file' [-Wunused-parameter]
     void Decode(FILE* in_file, FILE* out_file) {
                                      ^
    [ 28%] Linking C static library libgene_encode.a
    [ 28%] Built target gene_encode
    Scanning dependencies of target gflags_nothreads_static
    [ 35%] Building CXX object external/gflags/CMakeFiles/gflags_nothreads_static.dir/src/gflags.cc.o
    [ 42%] Building CXX object external/gflags/CMakeFiles/gflags_nothreads_static.dir/src/gflags_reporting.cc.o
    [ 50%] Building CXX object external/gflags/CMakeFiles/gflags_nothreads_static.dir/src/gflags_completions.cc.o
    [ 57%] Linking CXX static library libgflags_nothreads.a
    [ 57%] Built target gflags_nothreads_static
    Scanning dependencies of target lzw_test
    [ 64%] Building CXX object CMakeFiles/lzw_test.dir/src/lzw_test.cc.o
    [ 71%] Linking CXX executable lzw_test
    [ 71%] Built target lzw_test
    Scanning dependencies of target decode
    [ 78%] Building C object CMakeFiles/decode.dir/src/decode.c.o
    [ 85%] Linking C executable decode
    [ 85%] Built target decode
    Scanning dependencies of target encode
    [ 92%] Building C object CMakeFiles/encode.dir/src/encode.c.o
    [100%] Linking C executable encode
    [100%] Built target encode
    Scanning dependencies of target test-all
    Test group one (all possible sequences with N elements):
    testing encode for 4 sequences of size 1: FAILED
    	to repeat only this test run ./lzw_test --file ../test_data/all_bases_1 --test_index 0 --type encode
    	to extract input for test run ./lzw_test --file ../test_data/all_bases_1 --test_index 0 --type encode --dump
    testing decode for 4 sequences of size 1: FAILED
    	to repeat only this test run ./lzw_test --file ../test_data/all_bases_1 --test_index 0 --type decode
    	to extract input for test run ./lzw_test --file ../test_data/all_bases_1 --test_index 0 --type decode --dump
    testing encode for 16 sequences of size 2: FAILED
    	to repeat only this test run ./lzw_test --file ../test_data/all_bases_2 --test_index 0 --type encode
    	to extract input for test run ./lzw_test --file ../test_data/all_bases_2 --test_index 0 --type encode --dump
    testing decode for 16 sequences of size 2: FAILED
    	to repeat only this test run ./lzw_test --file ../test_data/all_bases_2 --test_index 0 --type decode
    	to extract input for test run ./lzw_test --file ../test_data/all_bases_2 --test_index 0 --type decode --dump
    testing encode for 64 sequences of size 3: FAILED
    	to repeat only this test run ./lzw_test --file ../test_data/all_bases_3 --test_index 0 --type encode
    	to extract input for test run ./lzw_test --file ../test_data/all_bases_3 --test_index 0 --type encode --dump
    testing decode for 64 sequences of size 3: FAILED
    	to repeat only this test run ./lzw_test --file ../test_data/all_bases_3 --test_index 0 --type decode
    	to extract input for test run ./lzw_test --file ../test_data/all_bases_3 --test_index 0 --type decode --dump
    testing encode for 256 sequences of size 4: FAILED
    	to repeat only this test run ./lzw_test --file ../test_data/all_bases_4 --test_index 0 --type encode
    	to extract input for test run ./lzw_test --file ../test_data/all_bases_4 --test_index 0 --type encode --dump
    testing decode for 256 sequences of size 4: FAILED
    	to repeat only this test run ./lzw_test --file ../test_data/all_bases_4 --test_index 0 --type decode
    	to extract input for test run ./lzw_test --file ../test_data/all_bases_4 --test_index 0 --type decode --dump
    testing encode for 1024 sequences of size 5: FAILED
    	to repeat only this test run ./lzw_test --file ../test_data/all_bases_5 --test_index 0 --type encode
    	to extract input for test run ./lzw_test --file ../test_data/all_bases_5 --test_index 0 --type encode --dump
    testing decode for 1024 sequences of size 5: FAILED
    	to repeat only this test run ./lzw_test --file ../test_data/all_bases_5 --test_index 0 --type decode
    	to extract input for test run ./lzw_test --file ../test_data/all_bases_5 --test_index 0 --type decode --dump
    testing encode for 4096 sequences of size 6: FAILED
    	to repeat only this test run ./lzw_test --file ../test_data/all_bases_6 --test_index 0 --type encode
    	to extract input for test run ./lzw_test --file ../test_data/all_bases_6 --test_index 0 --type encode --dump
    testing decode for 4096 sequences of size 6: FAILED
    	to repeat only this test run ./lzw_test --file ../test_data/all_bases_6 --test_index 0 --type decode
    	to extract input for test run ./lzw_test --file ../test_data/all_bases_6 --test_index 0 --type decode --dump
    Group one score: 0/12
    
    Test group two (pre-generated random sequences of size N):
    testing encode for sequence of size 1: FAILED
    	to repeat only this test run ./lzw_test --file ../test_data/rnd_0 --test_index 0 --type encode
    	to extract input for test run ./lzw_test --file ../test_data/rnd_0 --test_index 0 --type encode --dump
    testing decode for sequence of size 1: FAILED
    	to repeat only this test run ./lzw_test --file ../test_data/rnd_0 --test_index 0 --type decode
    	to extract input for test run ./lzw_test --file ../test_data/rnd_0 --test_index 0 --type decode --dump
    testing encode for sequence of size 4: FAILED
    	to repeat only this test run ./lzw_test --file ../test_data/rnd_1 --test_index 0 --type encode
    	to extract input for test run ./lzw_test --file ../test_data/rnd_1 --test_index 0 --type encode --dump
    testing decode for sequence of size 4: FAILED
    	to repeat only this test run ./lzw_test --file ../test_data/rnd_1 --test_index 0 --type decode
    	to extract input for test run ./lzw_test --file ../test_data/rnd_1 --test_index 0 --type decode --dump
    testing encode for sequence of size 16: FAILED
    	to repeat only this test run ./lzw_test --file ../test_data/rnd_2 --test_index 0 --type encode
    	to extract input for test run ./lzw_test --file ../test_data/rnd_2 --test_index 0 --type encode --dump
    testing decode for sequence of size 16: FAILED
    	to repeat only this test run ./lzw_test --file ../test_data/rnd_2 --test_index 0 --type decode
    	to extract input for test run ./lzw_test --file ../test_data/rnd_2 --test_index 0 --type decode --dump
    testing encode for sequence of size 64: FAILED
    	to repeat only this test run ./lzw_test --file ../test_data/rnd_3 --test_index 0 --type encode
    	to extract input for test run ./lzw_test --file ../test_data/rnd_3 --test_index 0 --type encode --dump
    testing decode for sequence of size 64: FAILED
    	to repeat only this test run ./lzw_test --file ../test_data/rnd_3 --test_index 0 --type decode
    	to extract input for test run ./lzw_test --file ../test_data/rnd_3 --test_index 0 --type decode --dump
    testing encode for sequence of size 256: FAILED
    	to repeat only this test run ./lzw_test --file ../test_data/rnd_4 --test_index 0 --type encode
    	to extract input for test run ./lzw_test --file ../test_data/rnd_4 --test_index 0 --type encode --dump
    testing decode for sequence of size 256: FAILED
    	to repeat only this test run ./lzw_test --file ../test_data/rnd_4 --test_index 0 --type decode
    	to extract input for test run ./lzw_test --file ../test_data/rnd_4 --test_index 0 --type decode --dump
    testing encode for sequence of size 1024: FAILED
    	to repeat only this test run ./lzw_test --file ../test_data/rnd_5 --test_index 0 --type encode
    	to extract input for test run ./lzw_test --file ../test_data/rnd_5 --test_index 0 --type encode --dump
    testing decode for sequence of size 1024: FAILED
    	to repeat only this test run ./lzw_test --file ../test_data/rnd_5 --test_index 0 --type decode
    	to extract input for test run ./lzw_test --file ../test_data/rnd_5 --test_index 0 --type decode --dump
    testing encode for sequence of size 4096: FAILED
    	to repeat only this test run ./lzw_test --file ../test_data/rnd_6 --test_index 0 --type encode
    	to extract input for test run ./lzw_test --file ../test_data/rnd_6 --test_index 0 --type encode --dump
    testing decode for sequence of size 4096: FAILED
    	to repeat only this test run ./lzw_test --file ../test_data/rnd_6 --test_index 0 --type decode
    	to extract input for test run ./lzw_test --file ../test_data/rnd_6 --test_index 0 --type decode --dump
    testing encode for sequence of size 16384: FAILED
    	to repeat only this test run ./lzw_test --file ../test_data/rnd_7 --test_index 0 --type encode
    	to extract input for test run ./lzw_test --file ../test_data/rnd_7 --test_index 0 --type encode --dump
    testing decode for sequence of size 16384: FAILED
    	to repeat only this test run ./lzw_test --file ../test_data/rnd_7 --test_index 0 --type decode
    	to extract input for test run ./lzw_test --file ../test_data/rnd_7 --test_index 0 --type decode --dump
    Group two score: 0/16
    
    Test group three (invalid inputs):
    testing encode for invalid encoder inputs: FAILED
    	to repeat only this test run ./lzw_test --file ../test_data/invalid_encoder_inputs --test_index 0 --type encode
    	to extract input for test run ./lzw_test --file ../test_data/invalid_encoder_inputs --test_index 0 --type encode --dump
    testing decode for invalid decoder inputs: FAILED
    	to repeat only this test run ./lzw_test --file ../test_data/invalid_decoder_inputs --test_index 0 --type decode
    	to extract input for test run ./lzw_test --file ../test_data/invalid_decoder_inputs --test_index 0 --type decode --dump
    Group three score: 0/2
    
    [100%] Built target test-all
    


### Marking

Total score: (0 / 12) * 35 + (0 / 16) * 35 + (0 / 2) * 30 = 0 / 100

