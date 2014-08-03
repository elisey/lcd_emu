#ifndef PIXELDISPLAY_H
#define PIXELDISPLAY_H

#include <QWidget>
#include <QFrame>
#include <qimage.h>
#include <qwidget.h>
#include <stdint.h>

class PixelDisplay : public QFrame
{
    Q_OBJECT
public:
    explicit PixelDisplay(QWidget *parent = 0);

    typedef struct {
        QRgb pixelColor;
        QRgb backgroundColor;
    } monochrome_palette_t;

    typedef struct {
        int x;
        int y;
        bool isPressed;
    } touch_state_t;

    typedef enum {MONOCHROME_3310_8bit, RGB_888_32bit} LcdDataEncoding;

    monochrome_palette_t monoPalette;
    LcdDataEncoding dataEncoding;
    touch_state_t touchState;

    void setMonoPixelColor(const QColor &newColor);
    void setMonoBackgroundColor(const QColor &newColor);
    void setScale(float newScale);
    void setSize(int width, int height);
    void setDataEncoding(LcdDataEncoding newDataEncoding);

    void updateDisplay(void *buffer);   // Reads buffer depending on displayColorMode and updates display

signals:
    void touchMove(void);
    void touchPress(void);
    void touchRelease(void);

public slots:


protected:
    void paintEvent(QPaintEvent *event);
    QSize sizeHint(void) const;
    void mouseMoveEvent(QMouseEvent * event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    QImage image;
    float scale;
    QRect displayPixelArea;
    void updateFrom_MONOCHROME_3310_8bit(uint8_t *buffer);
    void updateFrom_RGB_888_32bit(uint32_t *buffer);
};

#endif // PIXELDISPLAY_H
