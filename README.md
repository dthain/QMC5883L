Arduino Library for the QMC5883L Magnetometer/Compass
-----------------------------------------------------

This library provides support for the *QMC5883L* chip which
is found in *some* inexpensive compass boards marked
as GY-271 and sold through a variety of online vendors.

The GY-271 is supposed to have an *H*MC5883L, but some
knockoff boards have a *Q*MC5883L which has the same
basic capability, but is not compatible with the H.

If you have a GY-271 board and observe an I2C address of 0x0C
and read back nothing but zeros from the board, then you
probably have a QMC5883L chip!  Try this library and see
if it works for you.

To install this library into your Arduino environment, download the latest release file to your desktop:
https://github.com/dthain/QMC5883L/releases

In the Arduino app, select the menu Sketch->Include Library->Add Zip Library and then select the downloaded file.

Then within your sketch, declare a compass instance at global scope:

```
#include <QMC5883L.h>
#include <Wire.h>

QMC5883L compass;
```


Initialize the compass, which will reset the hardware and
begin continuous measurement mode:

```
Wire.begin();
compass.init();
```

Read raw magnetometer and temperature values from the compass.

```
int r;
int16_t x,y,z,t;
r = compass.readRaw(&x,&y,&z,&t)
```

Read calibrated heading values from the compass.
This function will initially return 0,
indicating that the compass is uncalibrated.
Continue to call `readHeading()` while rotating the compass on all axes.
Once enough data is collected, `readHeading()` will begin to return
integer heading values between 1 and 360 degrees.

```
int heading = compass.readHeading();
```

Note that readings are only periodically available, depending
on the sampling rate of the compass.  If a reading is not immediately
available, both `readRaw` and `readHeading` will block until it is available.
If you want to perform a non-blocking check instead, use the
`ready()` method:

```
if(compass.ready()) {
	int heading = compass.readHeading();
}
```

You can adjust the performance of the chip with the following methods:

```
compass.setSamplingRate(rate);
compass.setRange(range);
compass.setOverampling(ovl);
```

Allowable values for `rate` are 10, 50, 100, or 200 Hertz.
`range` may be 2 or 8 (Gauss).
`ovl` may be 512, 256, 128, or 64.

Datasheet on which the code is based:
http://wiki.epalsite.com/images/7/72/QMC5883L-Datasheet-1.0.pdf

