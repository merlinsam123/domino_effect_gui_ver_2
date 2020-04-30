#ifndef GUICONTROLLER_H
#define GUICONTROLLER_H

#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

const double PI = 3.141592653589793238463;

struct pathNode {
	char moveType; // Indicates movement type for path action
	int numDominoes; // For forward/backward movement, set to -1 for other movement types
	double turnDegrees; // Desired degrees to turn for one-wheel movement, set to -1 for forward/backward
	pathNode *nextNode;
	pathNode *lastNode;
};

// Note that wheel radius and distances are in
// inches, while degrees are in... degrees
class GUIcontroller {
private:
	double wheel_radius; // Radius of wheels driven by motors
	double wheel_distance; // Distance between the two wheels controlling movement
	double degrees_per_step; // Degrees the motors move for each step
	double distance_between_dominoes; // Distance between dominoes

	double distance_per_step; // Distance traveled by each step of a motor
	double turn_circumference; // Circumference of a circle with a radius that is the distance between the two wheels
	double step_degree_change; // Degree change each step causes when traveling along the circumference
	double degrees_between_dominoes; // degrees between each domino around the circumference of the circle

	int total_actions; // Total actions set by the user

	pathNode *head;
	pathNode *tail;

public:
	GUIcontroller();
	GUIcontroller(double, double, double, double);

	int get_num_actions();

	// Sets distance between dominoes
	void set_domino_distance(double);

	// Adds desired path action
	void add_path_action(char, int, double, double);

	// Removes last path action
	void remove_last();

	// Outputs path instructions to .txt
	void finalize_path();

	// Deletes all path actions
	void clear_path();
};

#endif