#!/bin/bash

root_dir=$( cd "$(dirname "${BASH_SOURCE[0]}")" || exit ; cd ../; pwd -P ) # https://stackoverflow.com/questions/24112727/relative-paths-based-on-file-location-instead-of-current-working-directory

cd "$root_dir/vm" || exit;

qemu-system-arm -m 1G -smp 1 -hda Fedora-Minimal-armhfp-29-1.2-sda.qcow2 -machine virt-2.11 -kernel vmlinuz-4.18.16-300.fc29.armv7hl -initrd initramfs-4.18.16-300.fc29.armv7hl.img  -append "console=ttyAMA0 rw root=LABEL=_/ rootwait ipv6.disable=1" -nographic -device e1000,netdev=net0 -netdev user,id=net0,hostfwd=tcp::5555-:22;
