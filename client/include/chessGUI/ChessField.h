#ifndef CHESS_CHESSFIELD_H
#define CHESS_CHESSFIELD_H

#include <wx/wx.h>
#include <wx/sizer.h>

namespace chessGUI {
    class ChessField : public wxPanel {
    public:
        ChessField(wxFrame* parent, wxString file, wxBitmapType format);
        ChessField() = default;

        void paintEvent(wxPaintEvent & evt);
        void render(wxDC& dc);
        void setImage(wxString file, wxBitmapType format);
        void resetImage();
    private:
        wxBitmap m_image;
    DECLARE_EVENT_TABLE()

        double m_scale;
    };
}




#endif //CHESS_CHESSFIELD_H
