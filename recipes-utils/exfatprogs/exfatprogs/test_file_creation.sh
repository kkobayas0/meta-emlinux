#!/bin/sh -e

# This test is based on https://github.com/exfatprogs/exfatprogs/blob/1.2.5/.travis.yml

mountdir="$1"
loopdev="$2"

# create file/director test
truncate -s 10G test.img
losetup "${loopdev}" test.img
mkfs.exfat "${loopdev}"

mount -t exfat "${loopdev}" "${mountdir}"
cd "${mountdir}"

i=1;while [ $i -le 10000 ];do touch file$i;if [ $? != 0 ]; then exit 1; fi; i=$(($i + 1));done
sync
rm -rf *

i=1;while [ $i -le 10000 ];do mkdir dir$i;if [ $? != 0 ]; then exit 1; fi; i=$(($i + 1));done
sync
rm -rf *

i=1;while [ $i -le 10000 ];do touch file$i;if [ $? != 0 ]; then exit 1; fi; i=$(($i + 1));done
i=1;while [ $i -le 10000 ];do mkdir dir$i;if [ $? != 0 ]; then exit 1; fi; i=$(($i + 1));done
sync

fsck.exfat "${loopdev}"
find . -type f -print | xargs rm -f
fsck.exfat "${loopdev}"

echo "file/directory creation test passed."
