#include "chessGUI/ChessField.h"
#include <cmath>

namespace chessGUI {
    BEGIN_EVENT_TABLE(ChessField, wxPanel)
        EVT_PAINT(ChessField::paintEvent)
    END_EVENT_TABLE()

    ChessField::ChessField(wxFrame *parent, wxString file, wxBitmapType format)
        : wxPanel(parent) {
        m_image.LoadFile(file, format);
    }

    void ChessField::paintEvent(wxPaintEvent &evt) {
        wxPaintDC dc(this);

        if (m_image.IsOk()) {
            m_scale = fmin(this->GetSize().GetWidth() / m_image.GetWidth(),
                           this->GetSize().GetHeight() / m_image.GetHeight());
            dc.SetUserScale(m_scale, m_scale);
            render(dc);
        }
    }

    void ChessField::render(wxDC &dc) {
        dc.DrawBitmap(m_image, (this->GetSize().GetWidth() - m_image.GetWidth() * m_scale) / 2,
                      (this->GetSize().GetHeight() - m_image.GetHeight() * m_scale) / 2, false );
    }

    void ChessField::setImage(wxString file, wxBitmapType format) {
        m_image.LoadFile(file, format);
    }

    void ChessField::resetImage() {
        m_image.UnRef();
    }

    void ChessField::setFigureId(const int id) {
        m_figureId = id;
    }

    int ChessField::getFigureId() const {
        return m_figureId;
    }
}