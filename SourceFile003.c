#pragma config(StandardModel, "RVW Buggybot")
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


bool isTooCloseToWall() {
	string type = "%f";
	//	debugLine( type, SensorValue[S4]);

	if (SensorValue[S4] > 20)
		return true;
	else
		return false;
}

void turnRight90(){

	int rightAngle = 147;
	turnRight(rightAngle, degrees, 100);
}

int getTurnWithLongestDistance(float *distances) {

	int turnWithLongestDistance = 1;
	float currentDistance = distances[0];

	int length = sizeof(distances);

	for (int i = 1; i < length ; i = i + 1) {
		if (distances[i] > currentDistance) {
			currentDistance = distances[i];
			turnWithLongestDistance = i + turnWithLongestDistance;
		}
	}

	return turnWithLongestDistance;
}

void startVehicleAndSetDirection() {
	float distance[4];

	for ( int i = 0; i < 4; i = i + 1) {
		turnRight90();
		distance[i] = SensorValue[S4];
	}

	int longestTurn = getTurnWithLongestDistance(distance);

	for (int y = 0; y < longestTurn; y = y + 1){
		turnRight90();
	}
}

void spinVehicleAndSetDirection() {
	float distance[2];

	turnRight90();
	distance[0] = SensorValue[S4];

	turnRight90();
	turnRight90();
	distance[1] = SensorValue[S4];

	int longestTurn = getTurnWithLongestDistance(distance);

	if (longestTurn == 1) {
		turnRight90();
		turnRight90();
	}
}


task main()
{

startVehicleAndSetDirection();

while(isTooCloseToWall())
{
	forward(300, milliseconds, 100);
}

spinVehicleAndSetDirection();
}
