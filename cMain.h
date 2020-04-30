#pragma once
#include "wx/wx.h"
#include "GUIcontroller.h"

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();
public:
	GUIcontroller *gui_control;

	char move_type;
	int num_dominoes;
	double turn_degrees;
	double domino_distance;
	bool left_or_right;

	wxArrayString inputPathActions;
	wxArrayString leftOrRight;

	wxStaticText *inputText1 = nullptr;
	wxTextCtrl *input1 = nullptr;

	wxStaticText *actionNumText = nullptr;

	wxStaticText *actionChoiceText = nullptr;
	wxChoice *chooseAction = nullptr;

	wxStaticText *inputText2 = nullptr;
	wxTextCtrl *input2 = nullptr;
	wxChoice *input2choice = nullptr;

	wxStaticText *inputText3 = nullptr;
	wxTextCtrl *input3 = nullptr;

	wxStaticText *currentPathText = nullptr;

	wxListBox *listPathActions = nullptr;

	wxButton *addPathAction = nullptr;
	wxButton *removePathAction = nullptr;
	wxButton *finalizePath = nullptr;
	wxButton *startOver = nullptr;

	void pathActionSelection(wxCommandEvent &evt);

	void addButtonClicked(wxCommandEvent &evt);
	void removeButtonClicked(wxCommandEvent &evt);
	void finalButtonClicked(wxCommandEvent &evt);
	void overButtonClicked(wxCommandEvent &evt);

	void changeDominoDistance(wxCommandEvent &evt);
	void changeDirection(wxCommandEvent &evt);
	void changeNumDominoes(wxCommandEvent &evt);
	void changeDegrees(wxCommandEvent &evt);

	void changeActionNum();

	wxDECLARE_EVENT_TABLE();
};

