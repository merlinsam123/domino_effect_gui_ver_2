#include "cMain.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
	EVT_BUTTON(10001, addButtonClicked)
	EVT_BUTTON(10002, removeButtonClicked)
	EVT_BUTTON(10003, finalButtonClicked)
	EVT_BUTTON(10004, overButtonClicked)
	EVT_CHOICE(10005, pathActionSelection)
	EVT_TEXT(10006, changeDominoDistance)
	EVT_CHOICE(10007, changeDirection)
	EVT_TEXT(10008, changeNumDominoes)
	EVT_TEXT(10009, changeDegrees)
wxEND_EVENT_TABLE()

// moveType Guide:
//  F - Drop Domino

//	W - Both Wheels Forward
//	I - Both Wheels Backward

//  D - Left Wheel Forward 
//  A - Right Wheel Forward

//  J - Left Wheel Backward
//  L - Right Wheel Backward

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "DominoEffect GUI ver 2", wxPoint(50,50), wxSize(800, 800))
{
	gui_control = new GUIcontroller();

	move_type = 'W';
	num_dominoes = 10;
	turn_degrees = 90;
	domino_distance = 1.0;
	left_or_right = false;

	inputPathActions.Add("Drop Dominoes in a Straight Line");
	inputPathActions.Add("Turn - Input Degrees");
	inputPathActions.Add("Turn - Input # Dominoes");

	leftOrRight.Add("Left");
	leftOrRight.Add("Right");

	actionNumText = new wxStaticText(this, wxID_ANY, "This will be Path Action #1", wxPoint(200, 50), wxSize(400, 25), wxALIGN_CENTRE_HORIZONTAL, "actionNumText");
	
	inputText1 = new wxStaticText(this, wxID_ANY, "Distance Between Dominoes (Inches): ", wxPoint(150, 100), wxSize(200, 25), wxALIGN_RIGHT, "inputText1");
	input1 = new wxTextCtrl(this, 10006, "1.0", wxPoint(350, 100), wxSize(200, 25));

	actionChoiceText = new wxStaticText(this, wxID_ANY, "Desired Action: ", wxPoint(150, 150), wxSize(200, 25), wxALIGN_RIGHT, "actionChoiceText");
	chooseAction = new wxChoice(this, 10005, wxPoint(350, 150), wxSize(200, 25), inputPathActions);

	inputText2 = new wxStaticText(this, wxID_ANY, "# of Dominoes: ", wxPoint(150, 200), wxSize(200, 25), wxALIGN_RIGHT, "inputText2");
	input2 = new wxTextCtrl(this, wxID_ANY, "10", wxPoint(350, 200), wxSize(200, 25));
	input2choice = nullptr;

	inputText3 = nullptr;
	input3 = nullptr;

	currentPathText = new wxStaticText(this, wxID_ANY, "Current Path:", wxPoint(200, 320), wxSize(400, 25), wxALIGN_CENTRE_HORIZONTAL, "currentPathText");
	listPathActions = new wxListBox(this, wxID_ANY, wxPoint(250, 350), wxSize(300, 200));

	addPathAction = new wxButton(this, 10001, "Add Path Action",				wxPoint(410, 575), wxSize(175, 50));
	removePathAction = new wxButton(this, 10002, "Remove Path Action",			wxPoint(215, 575), wxSize(175, 50));
	finalizePath = new wxButton(this, 10003, "Finalize Path and Start Robot",	wxPoint(410, 640), wxSize(175, 50));
	startOver = new wxButton(this, 10004, "Start Over",							wxPoint(215, 640), wxSize(175, 50));
}

cMain::~cMain()
{

}

void cMain::pathActionSelection(wxCommandEvent &evt)
{
	if (inputText2 != nullptr) {
		inputText2->Destroy();
	}

	if (input2 != nullptr) {
		input2->Destroy();
	}

	if (input2choice != nullptr) {
		input2choice->Destroy();
	}

	if (inputText3 != nullptr) {
		inputText3->Destroy();
		input3->Destroy();
	}

	// Straight Line
	if (chooseAction->GetSelection() == 0) {
		move_type = 'W';
		num_dominoes = 10;
		turn_degrees = -1;

		inputText2 = new wxStaticText(this, wxID_ANY, "# of Dominoes: ", wxPoint(150, 200), wxSize(200, 25), wxALIGN_RIGHT, "inputText2");
		input2 = new wxTextCtrl(this, 10008, "10", wxPoint(350, 200), wxSize(200, 25));
		input2choice = nullptr;

		inputText3 = nullptr;
		input3 = nullptr;
	}
	// Turn by Degrees
	else if (chooseAction->GetSelection() == 1) {
		move_type = 'A';
		num_dominoes = -1;
		turn_degrees = 90;

		inputText2 = new wxStaticText(this, wxID_ANY, "Direction: ", wxPoint(150, 200), wxSize(200, 25), wxALIGN_RIGHT, "inputText2");
		input2 = nullptr;
		input2choice = new wxChoice(this, 10007, wxPoint(350, 200), wxSize(200, 25), leftOrRight);

		inputText3 = new wxStaticText(this, wxID_ANY, "Degrees to Turn: ", wxPoint(150, 250), wxSize(200, 25), wxALIGN_RIGHT, "inputText3");
		input3 = new wxTextCtrl(this, 10009, "90", wxPoint(350, 250), wxSize(200, 25));
	}
	// Turn by # Dominoes
	else {
		move_type = '1';
		num_dominoes = 10;
		turn_degrees = -1;

		inputText2 = new wxStaticText(this, wxID_ANY, "Direction: ", wxPoint(150, 200), wxSize(200, 25), wxALIGN_RIGHT, "inputText2");
		input2 = nullptr;
		input2choice = new wxChoice(this, 10007, wxPoint(350, 200), wxSize(200, 25), leftOrRight);

		inputText3 = new wxStaticText(this, wxID_ANY, "# of Dominoes: ", wxPoint(150, 250), wxSize(200, 25), wxALIGN_RIGHT, "inputText3");
		input3 = new wxTextCtrl(this, 10008, "10", wxPoint(350, 250), wxSize(200, 25));
	}
}

void cMain::addButtonClicked(wxCommandEvent &evt)
{
	char start_type = move_type;

	string add_to_list = "";
	if (move_type == 'W') {
		add_to_list = "Straight - " + to_string(num_dominoes) + " dominoes";
	}
	else if (move_type == 'A') {
		add_to_list = "Turn Left - " + to_string(turn_degrees) + " degrees";
	}
	else if (move_type == 'D') {
		add_to_list = "Turn Right - " + to_string(turn_degrees) + " degrees";
	}
	else if (move_type == '1') {
		add_to_list = "Turn Left - " + to_string(num_dominoes) + " dominoes";
		move_type = 'A';
	}
	else if (move_type == '2') {
		add_to_list = "Turn Right - " + to_string(num_dominoes) + " dominoes";
		move_type = 'D';
	}
	listPathActions->Append(add_to_list);

	gui_control->add_path_action(move_type, num_dominoes, turn_degrees, domino_distance);

	cMain::changeActionNum();

	move_type = start_type;
}

void cMain::removeButtonClicked(wxCommandEvent &evt)
{
	gui_control->remove_last();
	cMain::changeActionNum();
	listPathActions->Delete(gui_control->get_num_actions());
}

void cMain::finalButtonClicked(wxCommandEvent &evt)
{
	gui_control->finalize_path();
}

void cMain::overButtonClicked(wxCommandEvent &evt)
{
	gui_control->clear_path();
	cMain::changeActionNum();
	listPathActions->Clear();
}

void cMain::changeDominoDistance(wxCommandEvent &evt) {
	input1->GetLineText(0).ToDouble(&domino_distance);
}

void cMain::changeDirection(wxCommandEvent &evt) {
	if (input2choice->GetSelection() == 1) {
		left_or_right = true;

		if (move_type == 'A') { move_type = 'D'; }
		if (move_type == '1') { move_type = '2'; }
	}
	else {
		left_or_right = false;

		if (move_type == 'D') { move_type = 'A'; }
		if (move_type == '2') { move_type = '1'; }
	}
}

void cMain::changeNumDominoes(wxCommandEvent &evt) {
	if (input3 != nullptr) {
		num_dominoes = wxAtoi(input3->GetLineText(0));
	}
	else {
		num_dominoes = wxAtoi(input2->GetLineText(0));
	}
}

void cMain::changeDegrees(wxCommandEvent &evt) {
	input3->GetLineText(0).ToDouble(&turn_degrees);
}

void cMain::changeActionNum() {
	int nextActionNum = gui_control->get_num_actions() + 1;
	string nextActionOutput = "This will be Path Action # " + to_string(nextActionNum);
	actionNumText->SetLabel(nextActionOutput);
	actionNumText->Refresh();
}