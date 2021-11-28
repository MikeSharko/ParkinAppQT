/***************************************************************
 * Name:      ParkingMain.h
 * Purpose:   Defines Application Frame
 * Author:    mike ()
 * Created:   2021-11-25
 * Copyright: mike ()
 * License:
 **************************************************************/

#ifndef PARKINGMAIN_H
#define PARKINGMAIN_H



#include "ParkingApp.h"


#include "GUIFrame.h"

class ParkingFrame: public GUIFrame
{
    public:
        ParkingFrame(wxFrame *frame);
        ~ParkingFrame();
    private:
        virtual void OnClose(wxCloseEvent& event);
        virtual void OnQuit(wxCommandEvent& event);
        virtual void OnAbout(wxCommandEvent& event);
};

#endif // PARKINGMAIN_H
