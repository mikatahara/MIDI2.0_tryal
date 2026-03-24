# MIDI2.0_tryal
## Using Raspberry Pi 2W to test a new MIDI 2.0 

- "midi2start.sh", shell script builds a MIDI 2.0 Gadget device on a Raspberry Pi 2W.  
Please run it with superuser privileges.

- "setudc.sh", shell script configures the UDC.  
Please run it after invoking midi2start.sh.

- "midi2noteon.c", send UMP MT4 Note ON and OFF messages 100 times at 250 ms intervals.  
Note Off: 0x4080xxxx xxxxxxxx  
Note On : 0x4090xxxx xxxxxxxx  
>gcc -o midi2noteon midi2noteon.c -lasound

- "midi2ctrl.c", send UMP MT4 Control Change messages 100 times at 250 ms intervals.  
Control Change: 0x40B0xxxx xxxxxxxx  
>gcc -o midi2ctrl midi2ctrl.c -lasound

- "midi2prgchg.c", Send UMP MT4 Program Change message.  
Enter three numbers, LSB/MSB.PC. Each number must be between 0 and 127.  
Program Change: 0x40C0xxxx xxxxxxxx  
>gcc -o midi2prgchg midi2prgchg.c -lasound

- "midi2newctrl.c",   
Send UMP MT4 registered/assignable controller messages 100 times at 250 ms intervals.  
Registered Controller : 0x4020xxxx xxxxxxxx  
Assignable Controller : 0x4030xxxx xxxxxxxx
>gcc -o midi2newcrtrl midi2newctrl.c -lasound

- "midi2pbend.c",   
Send UMP MT4 Pitchbend messages 100 times at 250 ms intervals.  
Pitchbend : 0x40E0xxxx xxxxxxxx  
>gcc -o midi2pbend midi2pbend.c -lasound


