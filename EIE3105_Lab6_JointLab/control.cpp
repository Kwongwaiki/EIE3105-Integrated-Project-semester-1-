#include <stdlib.h>
#include <stdio.h>

//Proportional gain and integral gain for inner loop and outer loop
double kp = 900.8, ki = 864;   //Inner loop: PI controller for left or right wheels (from observation, they share the same gain)
double kp2 = 0.5257, ki2 = 0.4891;   //outer loop: PI controller for speed difference
int Target_VL = 0;
int Target_VR = 0;
//The target counts per 50ms (both right and left wheels)
int Target_V = 35;
int PWM_VL = 0;
int PWM_VR = 0;
int error = 0;
int u = 0;
int errorL = 0;
int errorR = 0;
int errorL_T = 0;
int errorR_T = 0;
int errorLR_T = 0;
int countL = 0;
int countR = 0;
int temp = 0;
int cnt = 0;

void control(int &left, int &right)
{
	//summing up all counts within every 50ms
	if (temp < 20)
	{
		temp = temp + 1;
		countL = countL + left;
		countR = countR + right;
	}
	
	if (temp == 20)
	{
		temp = 0;
		cnt = cnt + 1;
		error = countR - countL;
		
		// Proportional control
		Target_VL = Target_V - u;
		Target_VR = Target_V + u;
		errorL = Target_VL - countL;
		errorR = Target_VR - countR;
		
		
		// Integral control
		errorL_T = errorL_T + errorL;
		errorR_T = errorR_T + errorR;
		errorLR_T = errorLR_T + error;
		
		
		//Limit the range in which the integral is allowed to build up in. 
		//So if the error is too big for the integral to be useful in, we could just disable the integral for that area.
		if ((abs(error) > 5) || (error == 0))
		{
			errorLR_T = 0;
		}
		
		if ((abs(errorL) > 5) || (errorL == 0))
		{
			errorL_T = 0;
		}
		
		if ((abs(errorR) > 5) || (errorR == 0))
		{
			errorR_T = 0;
		}
		
		
		// Feedback and calculate the value of PWM for left and right wheels
		u = kp2 * error + ki2 * errorLR_T;
		PWM_VL = kp * errorL + ki * errorL_T;
		PWM_VR = kp * errorR + ki * errorR_T;
		
		//set to zero after every 50ms
		countL = 0;
		countR = 0;
		error = 0;
		errorL_T = 0;
		errorR_T = 0;
		errorLR_T = 0;
	}
	
	//Outputs
	left = PWM_VL;
	right = PWM_VR;
	
	//Reset every 1 loop finished (4 sec)
	if (cnt == 80)
		{
			u = 0;
			PWM_VL = 0;
			PWM_VR = 0;
			cnt = 0;
		}
}