#include <QApplication> //Qt 애플리케이션의 핵심 기능을 제어하기 위한 헤더
#include "MainWindow.h" // 프로젝트의 메인 화면 클래스 정의가 담긴 헤더

int main(int argc, char *argv[]) {
    // 1. Qt 애플리케이션 객체 생성
    // 프로그램 실행 시 전달받은 인자(argc, argv)를 처리하며 애플리케이션의 환경을 구축함
    QApplication app(argc, argv);
    // 2. 메인 윈도우 인스턴스 생성
    // 실제 GUI 화면을 담당하는 MainWindow 클래스를 생성
    MainWindow window;
    // 3. 화면 표시
    // 생성된 윈도우 객체를 화면에 출력
    window.show();
    // 4. 이벤트 루프 시작
    // 프로그램이 종료될 때까지 사용자의 클릭, 버튼 조작 등 
    // 다양한 입력을 지속적으로 대기하고 처리하는 루프 실행
    return app.exec();
}