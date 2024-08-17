# Flo
Qt Based Klipper/Moonraker Local Control for RaspberryPi and x86 based systems. I do not recommend running this on anything less than a RaspberryPi 5 in it's current state. Eventually, the core will be re-written and the GUI will be ported to QtQuick for optimal performance and better gesture recognition.

[![IMAGE ALT TEXT](http://img.youtube.com/vi/sa-G5-JLb-4/0.jpg)](http://www.youtube.com/watch?v=sa-G5-JLb-4 "Interface Overview (No Voiceover)")

# Issues
- !!Not yet ready for consistent use!! software in in RC1 for BETA. It is more a proof of concept than a legitimate addition to Klipper Control Software at this time. Play with it, compare it to mainsail, but expect things to missing and/or 
    broken.
- Confirmed not to work with Gnome4x. There seems to be an issue with the windowcapture methods that are needed for the current implementation of the Bed Mesh Viewer
- Only tested with KDE wayland on an Ubuntu core (Kubuntu 22.04) and raspberrypios-minimal with KDE installed and configured

# Depends

- Qt 6
- kde-standard (minimum)
- gstreamer1-0
- moonraker
- klipper

sudo apt-get install -y libgstreamer1.0-dev libgstreamer-plugins-base1.0-0 libgstreamer-plugins-base1.0-dev libgstreamer-plugins-bad1.0-0 libgstreamer-plugins-bad1.0-dev gstreamer1.0-plugins-ugly gstreamer1.0-tools gstreamer1.0-pipewire gstreamer1.0-qt6 gstreamer1.0-gl gstreamer1.0-gtk3 gstreamer1.0-libcamera gstreamer1.0-plugins-bad gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-libav gstreamer1.0-vaapi
