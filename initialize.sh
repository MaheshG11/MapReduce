cd protofiles/
./generate_cpp.sh
cd ../
cmake -S . -B out/build
cd out/build
make