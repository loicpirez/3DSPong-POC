arm-none-eabi-strip test.elf
./makerom -f cci -o built.3ds -rsf gw_workaround.rsf -target d -exefslogo -elf test.elf -icon icon.bin -banner banner.bin
