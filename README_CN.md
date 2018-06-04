# dht12
dht12 linux 驱动，在tiny4412平台上测试通过

# compile
```
git clone https://github.com/hokamyuen/dht12.git
cd dht12
#修改Makefile中的KDIR为测试平台的内核源码
#编译驱动
make
#编译测试APP，工具链改成目标平台的编译工具
cd test_app
arm-linux-gnueabihf-gcc dht12_app.c -o dht12_app -static
```
# test
```
#装载驱动复制dht12_drv.ko到开发板上
insmod ht12_drv.ko

#安装设备，修改内核mach文件，或者复制device/dht12_add_device.sh到开发板上
chmod +x dht12_add_device.sh
./dht12_add_device.sh

#测试驱动
#复制编译出的dht12_app到开发板上
./dht12_app
```
