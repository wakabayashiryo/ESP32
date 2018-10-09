# ESP32-Iot-Devolopment-FrameWork


#### ***Expected Package before install Toolchain***
- git
- python
- pyserial
- g++
    > sudo apt-get install g++

- ## Install ESP-IDF on ubuntu or lubuntu
    Access ESP-IDF startup guide [site](https://docs.espressif.com/projects/esp-idf/en/latest/get-started/linux-setup.html)

     Read "Set up of Toolchain for Linux" in "About-ESP-IDF.pdf" or     About-ESP-IDF.html

     and Add PATH as follows in ~/.bashrc

~~~
    export PATH=$PATH:$HOME/ESP32_IDF/xtensa-esp32-elf/bin
    export IDF_PATH=~/ESP32_IDF/esp-idf
~~~

- ## After Installed Toolchain

    Read "esp-idf_getting_started_guide_en.pdf" in ESP32_Doc. 

    Try to compile test-project and write binary to flush.

- ## Projects Folder

    Put on Projects in **"~/ESP32/WorkSpace"**

- ## Others

    If IDF use python2,execute command as follows on Terminal.   

~~~
python2 /home/evaota/ESPworkspace/esp-idf/components/esptool_py/esptool/espsecure.py generate_signing_key /home/evaota/ESPworkspace/myapp/secure_boot_signing_key.pem
    
~~~

- ## Version

|version  |Date|Contents|
|:-----:|:-------:|:----------------|
|ver1.0 |2017/6/27|add infomation of version|   
|ver1.1 |2017/9/27|Updated Documents|
|ver1.2 |2018/10/9|fixed layout|
    
- ## License Information
   This software is released under the MIT License, see LICENSE