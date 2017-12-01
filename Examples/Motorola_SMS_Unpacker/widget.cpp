#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QPlainTextEdit>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->encodedTE->setReadOnly(true);
}

// See 3GPP TS 23.038 V4.2.0 for algorithm
// http://www.etsi.org/deliver/etsi_ts/123000_123099/123038/04.02.00_60/ts_123038v040200p.pdf
QString Widget::decodePackedGSM7HexString(unsigned char *in)
{
    char decoded_SMS[PATH_MAX];

    // ??? = 172 + 1 = 173
    // ??? = (173 * 8 + 6) / 7 = 198
    // ??? = (198 * 7) % 8 = 2
    // ??? = > 8 ? 2048?
    // ??? = ??? ? 1 : 0;
    // ??? = ??? - (??? * 7) = 662
    // ??? = ??? / 7

    u_int8_t bpos;
    u_int16_t x;
    u_int16_t y;
    u_int8_t n_ch;
    u_int16_t fill_bits = 1;

    for (x = 0, y = 0, bpos = fill_bits; x < PATH_MAX; x++) {
        switch (bpos) {
        case 0:
            n_ch = in[y];
            bpos = 7;
            break;
        case 1:
            n_ch = in[y] >> bpos;
            bpos--;
            y++;
            break;
        default:
            n_ch = in[y] >> bpos;
            n_ch |= in[y+1] << (8 - bpos);
            bpos--;
            y++;
            break;
        }
        decoded_SMS[x] = n_ch & 0x7F;
    }

    // FILE * pFile=fopen("hex_c", "wb");
    // if (pFile!=NULL) {
    //     fwrite (out , sizeof(u_int8_t), strlen(out), pFile);
    //     fclose (pFile);
    // }

    return QString(decoded_SMS);
}

void Widget::on_decodedTE_textChanged()
{
    QByteArray hexData = QByteArray::fromHex(ui->decodedTE->toPlainText().toStdString().c_str());
    ui->encodedTE->setPlainText(decodePackedGSM7HexString(reinterpret_cast<unsigned char *>(hexData.data())));
}

Widget::~Widget()
{
    delete ui;
}
