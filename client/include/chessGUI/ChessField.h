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

        void setFigureId(const int id);
        int getFigureId() const;

    private:
        wxBitmap m_image;
    DECLARE_EVENT_TABLE()

        double m_scale;
        int m_figureId;
    };
}




#endif //CHESS_CHESSFIELD_H
