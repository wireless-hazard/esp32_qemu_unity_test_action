#!/usr/bin/env bash
set -e
CODE_PATH="$1"
echo ${CODE_PATH}
. $IDF_PATH/export.sh
mkdir /project/components/
cp -r $GITHUB_WORKSPACE/component/ /project/components/component/
mv /project/components/component /project/components/$CODE_PATH
echo "cmake_minimum_required(VERSION 3.5) \n set(EXTRA_COMPONENT_DIRS \"./components\") \
\n set(TEST_COMPONENTS \"\$ENV{CODE_PATH}\" CACHE STRING \"List of components to test\") \
\n include(\$ENV{IDF_PATH}/tools/cmake/project.cmake) \n project(project_test)" > /project/components/$CODE_PATH/CMakeLists.txt
cat /project/components/$CODE_PATH/CMakeLists.txt
cd /project/
idf.py build
cd build 
esptool.py --chip esp32 merge_bin --fill-flash-size 4MB -o flash_image.bin @flash_args
/opt/qemu/bin/qemu-system-xtensa -nographic -no-reboot -machine esp32 -drive file=flash_image.bin,if=mtd,format=raw -serial file:output.log
ruby /opt/Unity-2.5.2/auto/parse_output.rb -xml output.log 
mv report.xml /github/workspace
