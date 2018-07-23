#include <QMC5883L.h>

QMC5883L compass;

void setup()
{
	compass.init();
	compass.setSamplingRate(50);

	Serial.begin(9600);
	Serial.println("QMC5883L Compass Demo");
	Serial.println("Turn compass in all directions to calibrate....");
}

void loop()
{
	while(1) {
		int heading = compass.readHeading();
		if(heading==0) {
			/* Still calibrating, so measure but don't print */
		} else {
			Serial.println(heading);
		}
	}
}
