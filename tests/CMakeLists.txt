cmake_minimum_required(VERSION 3.23)
set(CMAKE_C_STANDARD 99)
include(CTest)

# Tests unitaires
enable_testing()

# Tests de la liste chainée
add_executable(test_liste tests_liste.c "../src/liste.c")
add_test(test_liste test_liste "../tests")

file(GLOB_RECURSE SIM_SOURCE_FILES "../src/sim/*.c")

add_executable(test_sim_habitation "sim/test_sim_habitation.c" ${SIM_SOURCE_FILES} "../src/liste.c")
add_test(test_sim_habitation test_sim_habitation "../tests")