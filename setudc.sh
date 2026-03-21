REM This shell script configures the UDC.
REM Please run it after invoking midi2start.sh.

cd /sys/kernel/config/usb_gadget/g1
ln -s functions/midi2.usb0 configs/c.1
chmod 666 UDC
ls /sys/class/udc |xargs echo > UDC
cat /proc/asound/cards

