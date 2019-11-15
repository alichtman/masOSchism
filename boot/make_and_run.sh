nasm -f bin simple_boot.asm -o boot_sector.bin
qemu-system-x86_64 -drive file=boot_sector.bin,format=raw
