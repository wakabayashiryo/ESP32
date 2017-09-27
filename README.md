# ESP32-Iot-Devolopment-FrameWork
----

#### ***Expected Package before install Toolchain***
- git
- python
- pyserial

## Install ESP-IDF on ubuntu or lubuntu

        Read "Set up of Toolchain for Linux" in "About-ESP-IDF.pdf" or About-ESP-IDF.html

        and Add PATH as follows in ~/.bashrc

~~~
    export PATH=$PATH:$HOME/ESP32/xtensa-esp32-elf/bin
    export IDF_PATH=~/ESP32/esp-idf
~~~

## After Installed Toolchain

        Read "esp-idf_getting_started_guide_en.pdf" in ESP32_Doc. 

        Try to compile test-project and write binary to flush.

## Projects Folder

        Put on Projects in "~/ESP32/WorkSpace"

## Others

        If IDF use python2,execute command as follows on Terminal.
    
~~~
    python2 /home/evaota/ESPworkspace/esp-idf/components/esptool_py/esptool/espsecure.py generate_signing_key /home/evaota/ESPworkspace/myapp/secure_boot_signing_key.pem
    
~~~
## Version

|version  |Date|Contents|
|:-----:|:-------:|:----------------|
|ver1.0 |2017/6/27|add infomation of version|   
|ver1.1 |2017/9/27|Updated Documents|

    
## License Information
        This software is released under the MIT License, see LICENSE