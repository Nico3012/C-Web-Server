# CMake generated Testfile for 
# Source directory: C:/Users/nicom/Desktop/C-Web-Server/wolfssl/wolfssl-5.7.2
# Build directory: C:/Users/nicom/Desktop/C-Web-Server/wolfssl/wolfssl-5.7.2/out/build/x64-Debug
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(unit_test "C:/Users/nicom/Desktop/C-Web-Server/wolfssl/wolfssl-5.7.2/out/build/x64-Debug/tests/unit.test.exe")
set_tests_properties(unit_test PROPERTIES  WORKING_DIRECTORY "C:/Users/nicom/Desktop/C-Web-Server/wolfssl/wolfssl-5.7.2" _BACKTRACE_TRIPLES "C:/Users/nicom/Desktop/C-Web-Server/wolfssl/wolfssl-5.7.2/CMakeLists.txt;2481;add_test;C:/Users/nicom/Desktop/C-Web-Server/wolfssl/wolfssl-5.7.2/CMakeLists.txt;0;")
add_test(wolfcrypttest "C:/Users/nicom/Desktop/C-Web-Server/wolfssl/wolfssl-5.7.2/out/build/x64-Debug/wolfcrypt/test/testwolfcrypt.exe")
set_tests_properties(wolfcrypttest PROPERTIES  WORKING_DIRECTORY "C:/Users/nicom/Desktop/C-Web-Server/wolfssl/wolfssl-5.7.2" _BACKTRACE_TRIPLES "C:/Users/nicom/Desktop/C-Web-Server/wolfssl/wolfssl-5.7.2/CMakeLists.txt;2523;add_test;C:/Users/nicom/Desktop/C-Web-Server/wolfssl/wolfssl-5.7.2/CMakeLists.txt;0;")
