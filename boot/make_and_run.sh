set -e
nasm -f bin boot.asm -o boot_sector.bin
qemu-system-x86_64 -fda boot_sector.bin
