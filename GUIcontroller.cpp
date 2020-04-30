#include "GUIcontroller.h"

#include <iostream>
#include <fstream>
#include <math.h>

// Note that wheel radius and distances are in
// inches, while degrees are in... degrees

GUIcontroller::GUIcontroller() {
	wheel_radius = 1.50;
	wheel_distance = 10.00;
	degrees_per_step = 1.80;
	distance_between_dominoes = 1.0;

	distance_per_step = 2 * PI*wheel_radius * degrees_per_step / 360.0;
	turn_circumference = 2 * PI*wheel_distance;
	step_degree_change = distance_per_step / turn_circumference * 360.0;
	degrees_between_dominoes = distance_between_dominoes / turn_circumference * 360.0;

	total_actions = 0;

	head = NULL;
	tail = NULL;
}

GUIcontroller::GUIcontroller(double r = 1.5, double w = 10, double d = 1.8, double dd = 1.0) {
	wheel_radius = r;
	wheel_distance = w;
	degrees_per_step = d;
	distance_between_dominoes = dd;

	distance_per_step = 2*PI*wheel_radius * degrees_per_step / 360.0;
	turn_circumference = 2*PI*wheel_distance;
	step_degree_change = distance_per_step / turn_circumference * 360.0;
	degrees_between_dominoes = distance_between_dominoes / turn_circumference * 360.0;

	total_actions = 0;

	head = NULL;
	tail = NULL;
}

// Sets distance between dominoes
void GUIcontroller::set_domino_distance(double newDist) {
	distance_between_dominoes = newDist;
}

// Returns number of path actions currently input
int GUIcontroller::get_num_actions() {
	return total_actions;
}

// Adds desired path action
void  GUIcontroller::add_path_action(char moveType, int numDominoes, double turnDegrees, double newDist) {
	set_domino_distance(newDist);

	pathNode *newNode = new pathNode();
	newNode->moveType = moveType;
	newNode->nextNode = NULL;

	newNode->numDominoes = numDominoes;
	newNode->turnDegrees = turnDegrees;

	if (head == NULL) {
		newNode->lastNode = NULL;
		head = newNode;
		tail = newNode;
	}
	else {
		newNode->lastNode = tail;
		tail->nextNode = newNode;
		tail = tail->nextNode;
	}

	total_actions++;
}

// Removes last path action
void  GUIcontroller::remove_last() {
	if(head != NULL) {
		if (head == tail) {
			head = NULL;
		}

		pathNode *removeNode = tail;

		tail = tail->lastNode;
		if (tail != NULL) {
			tail->nextNode = NULL;
		}

		delete removeNode;

		total_actions--;
	}
}

// Outputs path instructions to .txt
void  GUIcontroller::finalize_path() {
	distance_per_step = 2 * PI*wheel_radius * degrees_per_step / 360.0;
	turn_circumference = 2 * PI*wheel_distance;
	step_degree_change = distance_per_step / turn_circumference * 360.0;
	degrees_between_dominoes = distance_between_dominoes / turn_circumference * 360.0;

	ofstream my_file;
	my_file.open("domino_effect_gui_output.txt");

	pathNode* curNode = head;

	while (curNode != NULL) {
		// Prints instructions for a straight line of dominoes
		if (curNode->moveType == 'W' || curNode->moveType == 'I') {
			for (int j = 0; j < curNode->numDominoes; j++) {
				my_file << 'F';

				for (double i = distance_per_step; i < distance_between_dominoes; i += distance_per_step) {
					my_file << curNode->moveType;
				}
			}
		}

		// Prints instructions for curve made up of dominoes
		else {
			//Input # Dominoes
			if (curNode->numDominoes > 0) {
				for (int j = 0; j < curNode->numDominoes; j++) {
					my_file << 'F';

					for (double i = distance_per_step; i < distance_between_dominoes; i += 2*distance_per_step) {
						my_file << 'W';
						my_file << curNode->moveType;
					}
				}
			}
			// Input degrees
			else
			{
				double d = 0.0;
				double distance_thresh = 0.0;

				while (d / 2 / turn_circumference * 360.0 < curNode->turnDegrees) {
					if (d >= distance_thresh) {
						my_file << 'F';
						distance_thresh += distance_between_dominoes;
					}

					my_file << 'W';
					my_file << curNode->moveType;
					d += 2 * distance_per_step;
				}

				while (d <= distance_thresh) {
					my_file << 'W';
					d += distance_per_step;
				}
			}
		}

		curNode = curNode->nextNode;
	}

	my_file.close();
}

// Deletes all path actions
void  GUIcontroller::clear_path() {
	while (head != NULL) {
		pathNode *removeNode = head;
		head = head->nextNode;
		delete removeNode;
	}

	tail = NULL;
	total_actions = 0;
}