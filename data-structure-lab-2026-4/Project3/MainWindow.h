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

// 항공편 정보를 담는 데이터 구조체
struct Flight {
    QString flightNum; //항공편 번호
    QString from; // 출발지 공항 코드
    QString to; // 도착지 공항 코드
    QString price; // 가격
    QString duration; // 소요 시간
};

// 공항 위치 및 정보를 담는 데이터 구조체
struct Airport {
    QString code; // 공항 코드 (예: ICN)
    QString name; // 공항 이름 (예: 인천)
    float xRatio; // 화면 상의 x좌표 비율 (0.0 ~ 1.0)
    float yRatio; // 화면 상의 y좌표 비율 (0.0 ~ 1.0)
};

// 지도 화면을 담당하는 커스텀 위젯 클래스
class MapLabel : public QLabel {
    Q_OBJECT
public:
    explicit MapLabel(QWidget* parent = nullptr) : QLabel(parent) {
        setCursor(Qt::PointingHandCursor); // 마우스를 올리면 손가락 모양 커서 표시
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
    void airportClicked(const QString& code); // 공항 클릭 시 신호 발생

protected:
    // 마우스 클릭 이벤트 처리: 클릭한 좌표가 공항 반경 내에 있는지 계산
    void mousePressEvent(QMouseEvent* event) override {
        for (const Airport& ap : m_airports) {
            int px = ap.xRatio * width();
            int py = ap.yRatio * height();
            int dx = event->pos().x() - px;
            int dy = event->pos().y() - py;
            if (dx*dx + dy*dy <= 18*18) { // 반경 18px 내 클릭 시 공항 선택으로 간주
                emit airportClicked(ap.code);
                return;
            }
        }
    }

    // 지도 위에 공항 아이콘(원)과 텍스트를 그리는 함수
    void paintEvent(QPaintEvent* event) override {
        QLabel::paintEvent(event);
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing); // 부드러운 선 처리

        for (const Airport& ap : m_airports) {
            int px = ap.xRatio * width();
            int py = ap.yRatio * height();
            bool selected = (ap.code == m_selectedCode);

            // 공항 원 그리기 (선택된 공항은 빨간색, 기본은 파란색)
            painter.setBrush(selected ? QColor("#e74c3c") : QColor("#3b8fdb"));
            painter.setPen(QPen(Qt::white, 2));
            painter.drawEllipse(QPoint(px, py), 13, 13);

            // 공항 코드 텍스트
            painter.setPen(Qt::white);
            QFont f; f.setPointSize(6); f.setBold(true);
            painter.setFont(f);
            painter.drawText(QRect(px-16, py-8, 32, 16), Qt::AlignCenter, ap.code);

            // 공항 이름 배경 및 텍스트
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

// 메인 윈도우 클래스
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);

private slots:
    void onAirportClicked(const QString& code); // 공항 선택 시 동작
    void onFlightClicked(const Flight& flight); // 항공편 클릭 시 예매 알림창 호출

private:
    void setupData(); // 항공 데이터 로드
    void setupUI(); // UI 구성
    void updateSidebar(const QString& code); // 사이드바 정보 업데이트

    MapLabel*    m_mapLabel;
    QLabel*      m_sidebarTitle;
    QLabel*      m_sidebarSub;
    QVBoxLayout* m_flightListLayout;

   // 데이터 저장용 자료구조
    QList<Airport>               m_airports;
    QMap<QString, QList<Flight>> m_depFlights; // 출발편 앱
    QMap<QString, QList<Flight>> m_arrFlights; // 도착편 앱
};