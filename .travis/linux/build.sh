# adding cmake to system path
export PATH=${TRAVIS_BUILD_DIR}/${CMAKE_DIRNAME}:${TRAVIS_BUILD_DIR}/${CMAKE_DIRNAME}/bin:$PATH

mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DMVVM_TESTS_AUTOEXEC=$TESTS_AUTOEXEC -DMVVM_TESTS_AUTODISCOVERY=$TESTS_AUTODISCOVERY ..
make -j4
