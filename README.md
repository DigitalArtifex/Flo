# Flo
Qt Based Klipper/Moonraker Control for RaspberryPi and other desktop systems, with a focus on touchscreen interaction. 

[![alt text](https://github.com/DigitalArtifex/Flo/blob/main/data/screenshots/printer_overview.png)](http://www.youtube.com/watch?v=sa-G5-JLb-4 "Interface Overview (No Voiceover)")

It is best described as a software replacement for Klipper and Sonic pads that allows more freedom in selection of hardware and themes. 

# Depends

- Qt 6.8
- QuaZip https://github.com/stachenov/quazip/
- gstreamer
- moonraker
- klipper

# Setup
## gstreamer1-0 (Ubuntu 24.04)

```
sudo apt-get install -y libgstreamer1.0-dev libgstreamer-plugins-base1.0-0 libgstreamer-plugins-base1.0-dev libgstreamer-plugins-bad1.0-0 libgstreamer-plugins-bad1.0-dev gstreamer1.0-plugins-ugly gstreamer1.0-tools gstreamer1.0-pipewire gstreamer1.0-qt6 gstreamer1.0-gl gstreamer1.0-gtk3 gstreamer1.0-libcamera gstreamer1.0-plugins-bad gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-libav gstreamer1.0-vaapi
```

## QuaZip

Clone the QuaZip repo from https://github.com/stachenov/quazip/

```
git clone https://github.com/stachenov/quazip.git
cd quazip
```

To build QuaZip for Qt6, you will need to point it to the platform folder of your Qt6 installation. If you installed Qt6 through the Qt Maintenance Tool it will default to `~/Qt/` if run as a user or `/opt/Qt/` if installed with sudo. The example assumes a root install.

```
cmake -B build -DCMAKE_PREFIX_PATH="/opt/Qt/6.8.0/gcc_64/lib/cmake/Qt6/" -DQUAZIP_QT_MAJOR_VERSION=6
cmake --build build --config Release
sudo cmake --install build
sudo cp /usr/local/lib/libquazip* /usr/lib
```

## Building/Running FLO

It is important to note that FLO uses QtMultimedia to process webcam streams. While QtMultimedia defaults to FFMPEG, there are several known issues
that can occur while using this backend. If you have any issues (i.e. system lockups, scan lines etc) it may be necessary to specify the native backend
for your system. For example, on Linux the native backend is `gstreamer` and therefore would set the environment variable `QT_MEDIA_BACKEND=gstreamer`. 

### Temporarily Set QT_MEDIA_BACKEND

![alt text](https://github.com/DigitalArtifex/Flo/blob/main/data/screenshots/build_env.png)

If you would like to temporarily set the backend for testing purposes, you can add it to Flo's Project settings under `Build Environment`

### Permanently Set QT_MEDIA_BACKEND

To make the environment variable permanent, we will need to add a line in `~/.profile`. Open a terminal and execute the following command

```
echo export QT_MEDIA_BACKEND=gstreamer >> ~/.profile
```
