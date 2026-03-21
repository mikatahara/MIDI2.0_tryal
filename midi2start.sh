modprobe libcomposite
cd /sys/kernel/config
mkdir usb_gadget/g1

cd usb_gadget/g1
mkdir configs/c.1
mkdir functions/midi2.usb0

chmod 666 idProduct
chmod 666 idVendor
echo 0x0004 > idProduct
echo 0x17b3 > idVendor

mkdir strings/0x409

chmod 666 strings/0x409/manufacturer
chmod 666 strings/0x409/product
chmod 666 strings/0x409/serialnumber
echo "ACME Enterprises" > strings/0x409/manufacturer
echo "ACMESynth" > strings/0x409/product
echo "ABCD12345" > strings/0x409/serialnumber

mkdir configs/c.1/strings/0x409

chmod 666 configs/c.1/strings/0x409/configuration
chmod 666 configs/c.1/MaxPower
echo "Monosynth" > configs/c.1/strings/0x409/configuration
echo 120 > configs/c.1/MaxPower

chmod 666 functions/midi2.usb0/iface_name 
chmod 666 functions/midi2.usb0/ep.0/ep_name 
chmod 666 functions/midi2.usb0/ep.0/product_id 
echo "ACMESynth" > functions/midi2.usb0/iface_name
echo "ACMESynth" > functions/midi2.usb0/ep.0/ep_name
echo "ABCD12345" > functions/midi2.usb0/ep.0/product_id

chmod 666 functions/midi2.usb0/ep.0/family 
chmod 666 functions/midi2.usb0/ep.0/model
chmod 666 functions/midi2.usb0/ep.0/manufacturer
chmod 666 functions/midi2.usb0/ep.0/sw_revision
echo 0x0123 > functions/midi2.usb0/ep.0/family
echo 0x4567 > functions/midi2.usb0/ep.0/model
echo 0x123456 > functions/midi2.usb0/ep.0/manufacturer
echo 0x12345678 > functions/midi2.usb0/ep.0/sw_revision

chmod 666 functions/midi2.usb0/ep.0/protocol 
echo 2 > functions/midi2.usb0/ep.0/protocol

chmod 666 functions/midi2.usb0/ep.0/block.0/name 
chmod 666 functions/midi2.usb0/ep.0/block.0/first_group 
chmod 666 functions/midi2.usb0/ep.0/block.0/num_groups 
echo "Monosynth" > functions/midi2.usb0/ep.0/block.0/name
echo 0 > functions/midi2.usb0/ep.0/block.0/first_group
echo 1 > functions/midi2.usb0/ep.0/block.0/num_groups
echo "End of MIDI2.0 Gadget start"

