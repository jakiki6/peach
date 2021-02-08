export PATH:=$(shell toolchain/use-it.sh):$(PATH)

all: run

run: os.img
	qemu-system-x86_64 -enable-kvm -m 256M -hda $< -serial stdio

include kernel/build.mk

os.img: kernel_all
	qemu-img create $@ 64M

	parted -s $@ mklabel gpt
	parted -s $@ mkpart primary 2048s 100%

	echfs-utils -g -p0 $@ quick-format 512

	echfs-utils -g -p0 $@ import config/limine.cfg limine.cfg
	echfs-utils -g -p0 $@ import kernel/kernel.elf kernel.elf

	limine-install $@

clean: kernel_clean
	rm os.img 2> /dev/null || true

.PHONY: all run clean