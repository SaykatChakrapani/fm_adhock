# fm_adhoc transmitter

Raspberry Pi's GPIO4 (PIN 7 on GPIO header) to act as an antenna, and you are ready for broadcasting.

It is based on an idea originally presented by [Oliver Mattos and Oskar Weigl] at (http://icrobotics.co.uk/wiki/index.php/Turning_the_Raspberry_Pi_Into_an_FM_Transmitter).
## Setup
```
git clone https://github.com/SaykatChakrapani/fm_adhock
cd fm_adhock
make
``` 
After a successful build you can start transmitting by executing the "fm_transmitter" program:
```
sudo ./fm_transmitter -f 102.0 guitar_testfile.wav
```
Where:
* -f frequency - Specifies the frequency in MHz, 100.0 by default if not passed
* guitar_testfile.wav - Sample WAV file, you can use your own

Other options:
* -d dma_channel - Specifies the DMA channel to be used (0 by default), type 255 to disable DMA transfer, CPU will be used instead
* -b bandwidth - Specifies the bandwidth in kHz, 100 by default
* -r - Loops the playback

After transmission has begun, simply tune an FM receiver to chosen frequency, You should hear the playback.
### New Raspberry Pi 4 Setup Problem
On Raspberry Pi 4, other built-in hardware probably interfers somehow with this software making transmitting not possible on all standard FM broadcasting frequencies. In this case it is recommended to:
1. Compile executable with option to use GPIO21 instead of GPIO4 (PIN 40 on GPIO header):
```
make GPIO21=1
```
2. Change either ARM core frequency scaling governor settings to "performance" or to change ARM minimum and maximum core frequencies to one constant value (see: https://www.raspberrypi.org/forums/viewtopic.php?t=152692 ).
```
echo "performance"| sudo tee /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor
```
3. Using lower FM broadcasting frequencies (below 93 MHz) when transmitting.
### Supported audio formats
You can transmitt uncompressed WAV (.wav) files directly or read audio data from stdin, eg.:
```
sudo apt-get install sox
sox guitar_testfile.wav -r 22050 -c 1 -b 16 -t wav - | sudo ./fm_transmitter -f 100.6 -
```
Please note only uncompressed WAV files are supported. If you receive the "corrupted data" error try converting the file, eg. by using SoX:
```
sudo apt-get install sox libsox-fmt-mp3
sox my-audio.mp3 -r 22050 -c 1 -b 16 -t wav my-converted-audio.wav
sudo ./fm_transmitter -f 100.6 my-converted-audio.wav
```
### Microphone support
In order to use a microphone live input use the `arecord` command, eg.:
```
arecord -D hw:1,0 -c1 -d 0 -r 22050 -f S16_LE | sudo ./fm_transmitter -f 100.6 -
```
In cases of a performance drop down use ```plughw:1,0``` instead of ```hw:1,0``` like this:
```
arecord -D plughw:1,0 -c1 -d 0 -r 22050 -f S16_LE | sudo ./fm_transmitter -f 100.6 -
```
