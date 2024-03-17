zmac --rel boot.z80
zmac --rel sorry.z80
zmac --rel ram.z80
zmac --rel patch.z80
zmac --rel main.z80
zmac --rel fpp.z80
zmac --rel exec.z80
zmac --rel eval.z80
zmac --rel cmos.z80

ld80 -m -O bin -o bbccriss.bin -P0100 zout/boot.rel -P0200 zout/main.rel zout/exec.rel zout/eval.rel zout/fpp.rel zout/sorry.rel zout/cmos.rel -P3b00 zout/ram.rel

a100 bbccriss.bin bbccriss.com

 