makerom workaround for creating 3DS files which work with gateway's "homebrew compatibility"

Notes with editing RSF file:
 - don't use tabs, use spaces
 - Use a new UniqueId for each app you build with a different icons, since the 3ds caches icons according to UniqueID
 - Don't edit below the line which says "# DO NOT EDIT BELOW HERE OR PROGRAMS WILL NOT LAUNCH (most likely)"

build.bat usage:
build.bat <elf file> <output 3ds file>

The key parts of the workaround include:
 - gw_workaround.rsf
 - These arguments to makerom: "-target d -rsf gw_workaround.rsf"
