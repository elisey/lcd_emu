#include <qpainter.h>
#include <QMouseEvent>
#include "pixeldisplay.h"

// Constructor
PixelDisplay::PixelDisplay(QWidget *parent) :
    QFrame(parent)
{
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setLineWidth(1);
    scale = 1.0;
    monoPalette.pixelColor = qRgb(0, 0, 0);
    monoPalette.backgroundColor = qRgb(180, 230, 150);
    dataEncoding = RGB_888_32bit;
    image = QImage(128,128,QImage::Format_RGB32);
    image.fill(monoPalette.backgroundColor);
    setMinimumSize(QSize(image.width() + lineWidth()*2,image.height() + lineWidth()*2));
    setMouseTracking(1);
    touchState.x = 0;
    touchState.y = 0;
    touchState.isPressed = 0;
}


// Returns optimal size for widget
QSize PixelDisplay::sizeHint(void) const
{
    QSize size = QSize(image.width()*scale+lineWidth()*2,image.height()*scale+lineWidth()*2);
    return size;
}


void PixelDisplay::paintEvent(QPaintEvent *e)
{
    QFrame::paintEvent(e);
    QPainter painter(this);
    painter.drawImage(lineWidth(),lineWidth(),image.scaled(width()-2*lineWidth(),height()-2*lineWidth()));
    displayPixelArea.setCoords( lineWidth(),lineWidth(),this->width() - lineWidth(), this->height() - lineWidth() );
}


void PixelDisplay::mouseMoveEvent(QMouseEvent * event)
{
    int mouseX = event->x() - displayPixelArea.left();
    int mouseY = event->y() - displayPixelArea.top();
    double displayPixelScaleX = (double)displayPixelArea.width() / (double)image.width();
    double displayPixelScaleY = (double)displayPixelArea.height() / (double)image.height();

    int touchX = mouseX / displayPixelScaleX;
    int touchY = mouseY / displayPixelScaleY;

    if ( ((touchX >= 0) && (touchX < image.width())) &&
         ((touchY >= 0) && (touchY < image.height())) )
    {
        touchState.x = touchX;
        touchState.y = touchY;
        emit touchMove();
    }
}

void PixelDisplay::mousePressEvent(QMouseEvent *event)
{
    touchState.isPressed = 1;
    emit touchPress();
}

void PixelDisplay::mouseReleaseEvent(QMouseEvent *event)
{
    touchState.isPressed = 0;
    emit touchRelease();
}

//---------------------------------------------//
//---------------------------------------------//

// Sets new data encoding
void PixelDisplay::setDataEncoding(LcdDataEncoding newDataEncoding)
{
    dataEncoding = newDataEncoding;
}


// Sets new color for active pixels
void PixelDisplay::setMonoPixelColor(const QColor &newColor)
{
    monoPalette.pixelColor = newColor.Rgb;
    update();
}

// Sets new color for background pixels
void PixelDisplay::setMonoBackgroundColor(const QColor &newColor)
{
    monoPalette.backgroundColor = newColor.Rgb;
    update();
}

// Sets display width and height
void PixelDisplay::setSize(int width, int height)
{
 //   image.~QImage();
    image = QImage(width,height,QImage::Format_RGB32);
    image.fill(monoPalette.backgroundColor);
    setMinimumSize(QSize(image.width() + lineWidth()*2,image.height() + lineWidth()*2));
    updateGeometry();
}

void PixelDisplay::setScale(float newScale)
{
    scale = newScale;
    updateGeometry();
}


void PixelDisplay::updateDisplay(void *buffer)
{
    switch(dataEncoding)
    {
        case MONOCHROME_3310_8bit:
            updateFrom_MONOCHROME_3310_8bit((uint8_t *)buffer);
            break;
        case RGB_888_32bit:
            updateFrom_RGB_888_32bit((uint32_t *)buffer);
            break;
    }
}




void PixelDisplay::updateFrom_MONOCHROME_3310_8bit(uint8_t *buffer)
{
    unsigned int bitMask, bufferOffset, bufferIndex;
    int bitmap_x, bitmap_y;

    for (bitmap_y = 0; bitmap_y < image.height(); bitmap_y++)
    {
        bufferOffset = (bitmap_y / 8) * image.width();
        bufferIndex = 0;
        bitMask = 1<<(bitmap_y % 8);

        for (bitmap_x = 0; bitmap_x < image.width(); bitmap_x++)
        {
            if (buffer[bufferOffset + bufferIndex] & bitMask)
                image.setPixel(bitmap_x,bitmap_y,monoPalette.pixelColor);
            else
                image.setPixel(bitmap_x,bitmap_y,monoPalette.backgroundColor);
            bufferIndex++;
        }
    }
    this->update();
}

void PixelDisplay::updateFrom_RGB_888_32bit(uint32_t *buffer)
{
    int bitmap_x, bitmap_y;
    int bufferIndex = 0;
    uint32_t temp;
    uint8_t red,green,blue;

    for (bitmap_y = 0; bitmap_y < image.height(); bitmap_y++)
    {
        for (bitmap_x = 0; bitmap_x < image.width(); bitmap_x++)
        {
            temp = buffer[bufferIndex++];
            red = temp & 0xFF;
            green = (temp >> 8) & 0xFF;
            blue = (temp >> 16) & 0xFF;
            image.setPixel(bitmap_x,bitmap_y, qRgb( red,green,blue ));
        }
    }
    this->update();
}




