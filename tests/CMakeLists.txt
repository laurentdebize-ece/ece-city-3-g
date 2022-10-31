cmake_minimum_required(VERSION 3.23)
set(CMAKE_C_STANDARD 99)
include(CTest)

# Tests unitaires
enable_testing()

# Tests de la liste chainée
add_executable(test_liste tests_liste.c "../src/liste.c")
add_test(test_liste test_liste "../tests")
