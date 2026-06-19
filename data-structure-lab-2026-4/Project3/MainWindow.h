#pragma once
#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QScrollArea>
#include <QMap>
#include <QList>
#include <QMouseEvent>
#include <QPainter>
#include <QMessageBox>

struct Flight {
    QString flightNum;
    QString from;
    QString to;
    QString price;
    QString duration;
};

struct Airport {
    QString code;
    QString name;
    float xRatio;
    float yRatio;
};

class MapLabel : public QLabel {
    Q_OBJECT
public:
    explicit MapLabel(QWidget* parent = nullptr) : QLabel(parent) {
        setCursor(Qt::PointingHandCursor);
    }

    void setAirports(const QList<Airport>& airports) {
        m_airports = airports;
        update();
    }

    void setSelectedAirport(const QString& code) {
        m_selectedCode = code;
        update();
    }

signals:
    void airportClicked(const QString& code);

protected:
    void mousePressEvent(QMouseEvent* event) override {
        for (const Airport& ap : m_airports) {
            int px = ap.xRatio * width();
            int py = ap.yRatio * height();
            int dx = event->pos().x() - px;
            int dy = event->pos().y() - py;
            if (dx*dx + dy*dy <= 18*18) {
                emit airportClicked(ap.code);
                return;
            }
        }
    }

    void paintEvent(QPaintEvent* event) override {
        QLabel::paintEvent(event);
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        for (const Airport& ap : m_airports) {
            int px = ap.xRatio * width();
            int py = ap.yRatio * height();
            bool selected = (ap.code == m_selectedCode);

            // 공항 원
            painter.setBrush(selected ? QColor("#e74c3c") : QColor("#3b8fdb"));
            painter.setPen(QPen(Qt::white, 2));
            painter.drawEllipse(QPoint(px, py), 13, 13);

            // 공항 코드
            painter.setPen(Qt::white);
            QFont f; f.setPointSize(6); f.setBold(true);
            painter.setFont(f);
            painter.drawText(QRect(px-16, py-8, 32, 16), Qt::AlignCenter, ap.code);

            // 이름 라벨
            QFont lf; lf.setPointSize(7);
            painter.setFont(lf);
            QRect nameRect(px-22, py+15, 44, 14);
            painter.fillRect(nameRect, QColor(0, 0, 0, 160));
            painter.setPen(Qt::white);
            painter.drawText(nameRect, Qt::AlignCenter, ap.name);
        }
    }

private:
    QList<Airport> m_airports;
    QString m_selectedCode;
};

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);

private slots:
    void onAirportClicked(const QString& code);
    void onFlightClicked(const Flight& flight);

private:
    void setupData();
    void setupUI();
    void updateSidebar(const QString& code);

    MapLabel*    m_mapLabel;
    QLabel*      m_sidebarTitle;
    QLabel*      m_sidebarSub;
    QVBoxLayout* m_flightListLayout;

    QList<Airport>               m_airports;
    QMap<QString, QList<Flight>> m_depFlights;
    QMap<QString, QList<Flight>> m_arrFlights;
};