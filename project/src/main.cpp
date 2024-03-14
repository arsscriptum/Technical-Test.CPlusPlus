
//==============================================================================
//
//     main.cpp
//
//============================================================================
//  Copyright (C) Guilaume Plante 2020 <cybercastor@icloud.com>
//==============================================================================



#include "stdafx.h"

#include "Shlwapi.h"



#include <codecvt>
#include <locale>
#include <vector>
#include <unordered_map>
#include <iterator>
#include <regex>
#include <filesystem>
#include <iostream>
#include <sstream>





//#pragma message( "Compiling " __FILE__ )
//#pragma message( "Last modified on " __TIMESTAMP__ )



#include <iostream>
using namespace std;


#include <iostream>
#include <string>

using namespace std;

// Enum for device states, I write them as enums and not class enum because I may need to cast them to int for output.
enum State {
    Idle            = 0,
    CallInit        = 1,
    CallActive      = 2,
    CallEnded       = 3
};

// Enum for device events
enum Event {
    PressButton     = 0,
    AnswerCall      = 1,
    EndCall         = 2
};

// Function prototypes
void updateState(State& currentState, Event event);

int main() {
    State currentState = State::Idle;

    cout << "State Machine Testv 1.0" << endl << endl;

    // run the state machine
    while (true) {

        // get my inpt
        string input;
        cout << "Enter event (PressButton (press 'P'), AnswerCall (press 'A'), EndCall (press 'E')): ";
        cin >> input;

        Event event;

        // check for entry
        if (input == "P") {
            event = Event::PressButton;
        }
        else if (input == "A") {
            event = Event::AnswerCall;
        }
        else if (input == "E") {
            event = Event::EndCall;
        }
        else {
            cout << "Invalid entry, try using 'P', 'A' or 'E'. Please try again." << endl;
            continue;
        }

        // update the new state
        updateState(currentState, event);

        if (currentState == State::CallEnded) {
            cout << "Call ended. Exiting." << endl;
            break;
        }
    }

    return 0;
}

void updateState(State& currentState, Event event) {
    switch (currentState) {
    case State::Idle:
        if (event == Event::PressButton) {
            cout << "Call initiated. Playing audio tone. Current State is " << currentState << endl;
            currentState = State::CallInit;
        }
        break;
    case State::CallInit:
        if (event == Event::AnswerCall) {
            cout << "Call answered by driver. Call active. Current State is " << currentState << endl;
            currentState = State::CallActive;
        }
        break;
    case State::CallActive:
        if (event == Event::EndCall) {
            cout << "Call ended by driver. Call terminated. Current State is " << currentState << endl;
            currentState = State::CallEnded;
        }
        break;
    case State::CallEnded:
        // No transitions from CallEnded state
        cout << "Call Ended!" << endl;
        break;
    }
}
