#해상도 1440*900
#22-02-07 Ver_220201
#22-04-08 Ver_220401 메뉴얼
#22-05-09 Ver_220501 메뉴얼부 수정
#22-06-13 Ver_220601 부가축 관련 발판 X
#22-06-13 Ver_220602 알람 처리 대아정공
#22-07-20 Ver_220701
#22-08-04 Ver_220801 지그 3존 처리 LE_data_0 = 2
#22-08-23 Ver_220802 대아정공 에어 및 종료
#22-08-24 Ver_220803 코드수정 /t/n 이상처리
#22-09-12 Ver_220901 지그 3존 비상정지 처리
#22-09-19 Ver_220902 지그 3존 처리 일시정지 기능 + tick 기능
#22-12-12 Ver 221201 대아정공 확인운전 속도 적용
#23-06-30 Ver_230601 레이저IPG 적용
#23-07-17 Ver_230701 ESAB 용접기 Sync 적용
#23-09-14 Ver_230901 한독기계 개조 적용 (주행 + 스테이션)
#23-11-02 Ver_231101 해상도 1440*900 적용
#23-11-12 Ver_231102 PC_NAME User 읽기
#23-12-01 Ver_231201 구간별 속도
#23-12-18 Ver_231202 프로니우스 프로그램 수정(구간별 속도)
#23-12-26 Ver_231203 위치이동,수정,교시점,프로그램 읽기부
#24-01-05 Ver_240101 용접중 위치수정,용접중 조건수정
#24-01-09 Ver_240101 용접중 기능 (조건변경, 위치조작)

QT       += core gui network multimedia multimediawidgets
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = JCT_Qt_welsystem
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    commonheader.h

FORMS    += mainwindow.ui

RESOURCES += \
    image.qrc
