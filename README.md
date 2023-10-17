# BMC-CrossCompile
- bitbake -c populate_sdk obmc-phosphor-image
- sdk exe file : https://drive.google.com/file/d/1eFS1rPOJ7_t6nb9XK12MFvkAOyTxHVWN/view?usp=sharing
- How to Use?
  1. download exe file from google drive
  2. execute sh file then files are downloaded in /usr/local/bin
  3. execute makeNewApplication.sh

##How to Compile dts file?
sudo apt install device-tree-compiler
dtc -I dts -O dtb -o my_device.dtb aspeed-bmc-phoenix-beechnutcity.dts
