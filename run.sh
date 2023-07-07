
if [ ! -d './build' ]; then
  mkdir build
fi
cd build
set -xe
cmake .. && make && ./sierpinski-carpet
