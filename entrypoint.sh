#!/usr/bin/env bash
set -e
CODE_PATH="$1"
. $IDF_PATH/export.sh
cd examples/test/
echo ${CODE_PATH}
idf.py build
cd build 
esptool.py --chip esp32 merge_bin --fill-flash-size 4MB -o flash_image.bin @flash_args
/opt/qemu/bin/qemu-system-xtensa -nographic -no-reboot -machine esp32 -drive file=flash_image.bin,if=mtd,format=raw -serial file:output.log
ruby /opt/Unity-2.5.2/auto/parse_output.rb -xml output.log 
mv report.xml /github/workspace
