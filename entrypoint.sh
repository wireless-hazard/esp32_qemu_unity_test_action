#!/usr/bin/env bash
set -e
CODE_PATH="$1"
echo ${CODE_PATH}
. $IDF_PATH/export.sh
mkdir /project/components/
cp -r $GITHUB_WORKSPACE/component/ /project/components/component/
mv /project/components/component /project/components/$CODE_PATH
export CODE_PATH="$1"
cd /project/
idf.py build
cd build 
esptool.py --chip esp32 merge_bin --fill-flash-size 4MB -o flash_image.bin @flash_args
/opt/qemu/bin/qemu-system-xtensa -nographic -no-reboot -machine esp32 -drive file=flash_image.bin,if=mtd,format=raw -serial file:output.log
grep -q -E '[[:digit:]]+ Tests [[:digit:]]+ Failures [[:digit:]]+ Ignored' output.log && ruby /opt/Unity-2.5.2/auto/parse_output.rb -xml output.log || exit 1
mv report.xml /github/workspace
