#include "MainWindow.h"

//생성자: UI 초기화, 데이터 세팅, 윈도우 기본 설정 수행
MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setupData(); // 항공 데이터(공항,항공편)를 메모리에 로드
    setupUI(); // GUI 컴포넌트(지도, 사이드바 등) 생성 및 배치
    setWindowTitle("항공권 예매 시스템");
    resize(1000, 620);
}

// 데이터 초기화 함수: 프로젝트에서 사용하는 고정된 항공 데이터 정의
void MainWindow::setupData() {
     // 공항 위치 정보 (이름, 화면 좌표 등)
    m_airports = {
        {"ICN", "인천",   0.775f, 0.30f},
        {"NRT", "도쿄",   0.805f, 0.32f},
        {"PEK", "베이징", 0.740f, 0.28f},
        {"HKG", "홍콩",   0.740f, 0.38f},
        {"SIN", "싱가폴", 0.715f, 0.46f},
        {"LHR", "런던",   0.465f, 0.22f},
        {"JFK", "뉴욕",   0.180f, 0.28f},
        {"LAX", "LA",     0.105f, 0.31f},
        {"DXB", "두바이", 0.600f, 0.37f},
        {"SYD", "시드니", 0.840f, 0.65f},
    };

   // 출발 항공편 데이터 (Map을 사용하여 공항 코드로 접근)
    m_depFlights["ICN"] = {
        {"KE001", "ICN", "NRT", "₩85,000",  "2시간 0분"},
        {"KE101", "ICN", "JFK", "₩820,000", "13시간 30분"},
        {"OZ201", "ICN", "LHR", "₩750,000", "11시간 20분"},
        {"KE301", "ICN", "SIN", "₩380,000", "6시간 30분"},
    };
    m_depFlights["NRT"] = {
        {"NH001", "NRT", "LAX", "₩720,000", "9시간 30분"},
        {"JL003", "NRT", "LHR", "₩680,000", "12시간 0분"},
        {"NH071", "NRT", "ICN", "₩90,000",  "2시간 10분"},
    };
    m_depFlights["LHR"] = {
        {"BA001", "LHR", "JFK", "₩620,000", "7시간 30분"},
        {"BA017", "LHR", "ICN", "₩770,000", "11시간 20분"},
    };
    m_depFlights["JFK"] = {
        {"AA100", "JFK", "LAX", "₩220,000", "5시간 30분"},
        {"VS002", "JFK", "LHR", "₩590,000", "7시간 0분"},
    };
    m_depFlights["SIN"] = {
        {"SQ321", "SIN", "LHR", "₩890,000", "13시간 0분"},
        {"SQ607", "SIN", "ICN", "₩360,000", "6시간 20분"},
    };
    m_depFlights["HKG"] = {
        {"CX451", "HKG", "NRT", "₩270,000", "4시간 0분"},
        {"CX701", "HKG", "SYD", "₩490,000", "9시간 0분"},
    };
    m_depFlights["DXB"] = {
        {"EK321", "DXB", "ICN", "₩520,000", "9시간 30분"},
        {"EK002", "DXB", "LHR", "₩450,000", "7시간 10분"},
    };
    m_depFlights["PEK"] = {
        {"CA803", "PEK", "ICN", "₩115,000", "2시간 0분"},
        {"CA809", "PEK", "HKG", "₩145,000", "3시간 30분"},
    };
    m_depFlights["SYD"] = {
        {"QF002", "SYD", "LHR", "₩1,100,000", "22시간 0분"},
        {"MH067", "SYD", "SIN", "₩430,000",   "7시간 50분"},
    };
    m_depFlights["LAX"] = {
        {"UA002", "LAX", "JFK", "₩215,000", "5시간 10분"},
    };

    // 도착 항공편 데이터 (Map을 사용하여 공항 코드로 접근)
    m_arrFlights["ICN"] = {
        {"CA802", "PEK", "ICN", "₩120,000", "2시간 0분"},
        {"EK322", "DXB", "ICN", "₩530,000", "9시간 30분"},
    };
    m_arrFlights["NRT"] = {
        {"KE002", "ICN", "NRT", "₩88,000",  "2시간 0분"},
        {"CX450", "HKG", "NRT", "₩280,000", "4시간 0분"},
    };
    m_arrFlights["LHR"] = {
        {"VS003", "JFK", "LHR", "₩600,000", "7시간 0분"},
        {"KE908", "ICN", "LHR", "₩760,000", "11시간 30분"},
    };
    m_arrFlights["JFK"] = {
        {"BA002", "LHR", "JFK", "₩610,000", "7시간 30분"},
        {"KE082", "ICN", "JFK", "₩830,000", "13시간 30분"},
    };
    m_arrFlights["SIN"] = {
        {"KE643", "ICN", "SIN", "₩370,000", "6시간 30분"},
        {"MH066", "SYD", "SIN", "₩440,000", "7시간 40분"},
    };
    m_arrFlights["HKG"] = {
        {"KA808", "PEK", "HKG", "₩150,000", "3시간 30분"},
    };
    m_arrFlights["DXB"] = {
        {"EK003", "LHR", "DXB", "₩440,000", "7시간 0분"},
    };
    m_arrFlights["SYD"] = {
        {"CX702", "HKG", "SYD", "₩500,000", "9시간 0분"},
    };
    m_arrFlights["LAX"] = {
        {"NH002", "NRT", "LAX", "₩710,000", "9시간 40분"},
        {"AA101", "JFK", "LAX", "₩218,000", "5시간 30분"},
    };
}

// UI 구성 함수: 레이아웃 설계 및 위젯 배치
void MainWindow::setupUI() {
    QWidget* central = new QWidget(this);
    setCentralWidget(central);

    QHBoxLayout* mainLayout = new QHBoxLayout(central); // 전체 레이아웃 (좌:지도, 우:사이드바)
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // ── 지도 영역 ──
    m_mapLabel = new MapLabel(this);
    QPixmap map("세계지도.jpeg");
    m_mapLabel->setPixmap(map.scaled(740, 620,
                          Qt::KeepAspectRatio,
                          Qt::SmoothTransformation));
    m_mapLabel->setAirports(m_airports);
    connect(m_mapLabel, &MapLabel::airportClicked,
            this, &MainWindow::onAirportClicked);
    mainLayout->addWidget(m_mapLabel, 3);

    // ── 사이드바 ──
    QWidget* sidebar = new QWidget(this);
    sidebar->setFixedWidth(260);
    sidebar->setStyleSheet("background:#111827;");

    QVBoxLayout* sideLayout = new QVBoxLayout(sidebar);
    sideLayout->setContentsMargins(0, 0, 0, 0);
    sideLayout->setSpacing(0);

    // 헤더
    QWidget* header = new QWidget;
    header->setStyleSheet("background:#111827; border-bottom:1px solid #374151; padding:4px;");
    QVBoxLayout* headerLayout = new QVBoxLayout(header);
    headerLayout->setContentsMargins(12, 12, 12, 12);

    m_sidebarTitle = new QLabel("공항을 클릭하세요");
    m_sidebarTitle->setStyleSheet("color:white; font-size:14px; font-weight:bold;");

    m_sidebarSub = new QLabel("지도에서 공항(●)을 클릭하세요.");
    m_sidebarSub->setStyleSheet("color:#9ca3af; font-size:11px;");

    headerLayout->addWidget(m_sidebarTitle);
    headerLayout->addWidget(m_sidebarSub);
    sideLayout->addWidget(header);

    // 스크롤 가능한 항공편 목록
    QScrollArea* scroll = new QScrollArea;
    scroll->setWidgetResizable(true);
    scroll->setStyleSheet("QScrollArea { border:none; background:#111827; }");

    QWidget* listWidget = new QWidget;
    listWidget->setStyleSheet("background:#111827;");
    m_flightListLayout = new QVBoxLayout(listWidget);
    m_flightListLayout->setContentsMargins(8, 8, 8, 8);
    m_flightListLayout->setAlignment(Qt::AlignTop);

    QLabel* emptyLabel = new QLabel("공항 아이콘을 클릭하면\n출발/도착 항공편이 표시됩니다");
    emptyLabel->setStyleSheet("color:#6b7280; font-size:12px;");
    emptyLabel->setAlignment(Qt::AlignCenter);
    m_flightListLayout->addWidget(emptyLabel);

    scroll->setWidget(listWidget);
    sideLayout->addWidget(scroll);

    // 하단 안내
    QLabel* tip = new QLabel("공항 아이콘을 클릭하면 항공편이 표시됩니다");
    tip->setStyleSheet("color:#6b7280; font-size:10px; padding:8px;"
                       "border-top:1px solid #374151; background:#111827;");
    tip->setAlignment(Qt::AlignCenter);
    tip->setWordWrap(true);
    sideLayout->addWidget(tip);

    mainLayout->addWidget(sidebar, 0);
}

// 지도에서 공항 아이콘을 클릭했을 때 호출되는 슬롯
void MainWindow::onAirportClicked(const QString& code) {
    m_mapLabel->setSelectedAirport(code);
    updateSidebar(code);
}

// 선택된 공항에 맞춰 사이드바 내용을 업데이트하는 함수
void MainWindow::updateSidebar(const QString& code) {
    // 기존에 표시되던 항공편 리스트 위젯 삭제 (초기화)
    QLayoutItem* item;
    while ((item = m_flightListLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    // 선택된 공항 찾기
    Airport ap;
    for (const Airport& a : m_airports)
        if (a.code == code) { ap = a; break; }

    m_sidebarTitle->setText(QString("%1 (%2)").arg(ap.name, code));
    m_sidebarSub->setText("아래 항공편을 클릭하면 예매합니다.");

    // 항공편 카드(버튼)를 생성하고 레이아웃에 추가하는 람다 함수
    auto addSection = [&](const QString& title, const QList<Flight>& flights) {
        if (flights.isEmpty()) return;

        QLabel* secLabel = new QLabel(title);
        secLabel->setStyleSheet(
            "color:#60a5fa; font-size:11px; font-weight:bold; padding:6px 4px 2px;");
        m_flightListLayout->addWidget(secLabel);

        for (const Flight& f : flights) {
            QPushButton* card = new QPushButton;
            card->setFixedHeight(66);
            card->setStyleSheet(R"(
                QPushButton {
                    background: rgba(255,255,255,0.05);
                    border: 1px solid rgba(255,255,255,0.1);
                    border-radius: 8px;
                    text-align: left;
                    padding: 6px 10px;
                    color: white;
                }
                QPushButton:hover {
                    background: rgba(59,143,219,0.2);
                    border-color: rgba(59,143,219,0.5);
                }
            )");

            // 카드 내부 레이아웃
            QVBoxLayout* cardLayout = new QVBoxLayout(card);
            cardLayout->setContentsMargins(6, 4, 6, 4);
            cardLayout->setSpacing(2);

            QLabel* numLbl = new QLabel(f.flightNum);
            numLbl->setStyleSheet("color:#60a5fa; font-size:10px; background:transparent;");

            QLabel* routeLbl = new QLabel(QString("%1 → %2").arg(f.from, f.to));
            routeLbl->setStyleSheet("color:white; font-size:12px; background:transparent;");

            QWidget* detailRow = new QWidget;
            detailRow->setStyleSheet("background:transparent;");
            QHBoxLayout* detailLayout = new QHBoxLayout(detailRow);
            detailLayout->setContentsMargins(0, 0, 0, 0);

            QLabel* priceLbl = new QLabel(f.price);
            priceLbl->setStyleSheet("color:#34d399; font-size:11px; background:transparent;");

            QLabel* durLbl = new QLabel(f.duration);
            durLbl->setStyleSheet("color:#9ca3af; font-size:10px; background:transparent;");

            detailLayout->addWidget(priceLbl);
            detailLayout->addStretch();
            detailLayout->addWidget(durLbl);

            cardLayout->addWidget(numLbl);
            cardLayout->addWidget(routeLbl);
            cardLayout->addWidget(detailRow);

            // 클릭 → 예매 팝업
            Flight captured = f;
            connect(card, &QPushButton::clicked, this,
                    [this, captured]() { onFlightClicked(captured); });

            m_flightListLayout->addWidget(card);
        }
    };

    addSection("✈  출발 항공편", m_depFlights.value(code));
    addSection("🛬  도착 항공편", m_arrFlights.value(code));

    if (m_depFlights.value(code).isEmpty() && m_arrFlights.value(code).isEmpty()) {
        QLabel* empty = new QLabel("이 공항의 항공편 정보가 없습니다.");
        empty->setStyleSheet("color:#6b7280; font-size:12px;");
        empty->setAlignment(Qt::AlignCenter);
        m_flightListLayout->addWidget(empty);
    }

    m_flightListLayout->addStretch();
}

// 항공편 카드를 클릭했을 때 예매 완료 메시지를 띄우는 함수
void MainWindow::onFlightClicked(const Flight& f) {
    QMessageBox msg(this);
    msg.setWindowTitle("✔ 예매 완료");
    msg.setText(QString(
        "예매가 완료되었습니다.\n\n"
        "항공편: %1\n"
        "구간:   %2 → %3\n"
        "가격:   %4\n"
        "소요 시간: %5"
    ).arg(f.flightNum, f.from, f.to, f.price, f.duration));
    msg.setIcon(QMessageBox::Information);
    msg.exec();
}