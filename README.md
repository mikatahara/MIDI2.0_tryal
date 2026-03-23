# MIDI2.0_tryal
## Using Raspberry Pi 2W to test a new MIDI 2.0 

- "midi2start.sh", shell script builds a MIDI 2.0 Gadget device on a Raspberry Pi 2W.  
Please run it with superuser privileges.

- "setudc.sh", shell script configures the UDC.  
Please run it after invoking midi2start.sh.

- "midi2noteon.c", send UMP MT4 Note ON and OFF messages 100 times at 250 ms intervals.  
gcc -o midi2noteon midi2noteon.c -lasound

- "midi2ctrl.c", send UMP MT4 Control Change messages 100 times at 250 ms intervals.  
gcc -o midi2ctrl midi2ctrl.c -lasound

- "midi2prgchg.c", Send UMP MT4 Program Change message.  
  Enter three numbers, LSB/MSB.PC. Each number must be between 0 and 127.  
gcc -o midi2prgchg midi2prgchg.c -lasound

