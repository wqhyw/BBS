[[ ! -d build ]] && mkdir build
cd build

cmake -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles" ..

cmake --build . --target all -- -j 2 -o3

cd ..

rm -rf build

rm bin/BBS