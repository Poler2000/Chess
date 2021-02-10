#include "chessGUI/ChessField.h"

namespace chessGUI {
    BEGIN_EVENT_TABLE(ChessField, wxPanel)
        EVT_PAINT(ChessField::paintEvent)
    END_EVENT_TABLE()

    ChessField::ChessField(wxFrame *parent, wxString file, wxBitmapType format) {
        m_image.LoadFile(file, format);
    }

    void ChessField::paintEvent(wxPaintEvent &evt) {
        wxPaintDC dc(this);
        if(m_image.IsOk())
        render(dc);
    }

    void ChessField::render(wxDC &dc) {
        dc.DrawBitmap(m_image, 0, 0, false );
    }

    void ChessField::setImage(wxString file, wxBitmapType format) {
        m_image.LoadFile(file, format);
    }
}