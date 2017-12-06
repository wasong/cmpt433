Preliminaries
=
- we assume all hardware is installed and ready to be used

Building Web Application
=
1. Go into `webapp` folder
2. If you have `yarn`, do `yarn` otherwise do `npm install`
3. To start the server + client, do either `yarn run serve` or `npm run serve`

    - this will build the client and serve it through the Node/Express server

Building BeagleBone Application
=

Attempt the installation steps specified in this guide http://www.cs.sfu.ca/CourseCentral/433/bfraser/other/2016-student-howtos/WebcamJPEGtoWeb.pdf

Steps 1 and 2 below are essentially the same with the difference being installing the linux packages on the host.

1. Install the linux packages `libv4l-dev`, `v4l-utils` on both the host and target
2. On the target, copy these files out of `/usr/lib/arm-linux-gnueabihf` and into your `public/` folder so the host can access them
    - libjpeg.so
    - libv4l2.so
    - libv4lconvert.so
3. On the target, run this command `sudo apt-get install imagemagick`
4. Inside `webcam` folder, run `make`
5. Start `main` from your target


Troubleshooting
=
