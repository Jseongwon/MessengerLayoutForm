// ChatProfileProcessor.cpp
/*
파일명칭 : ChatProfileProcessor.cpp
기    능 : 대화내역 처리기 클래스를 정의한다.
작 성 자 : 정성원
작성일자 : 2022.04.22

목표 : ChatProfileCompiler의 처리들을 분할, 정리하여 가독성을 높이는데 사용될 클래스이다.
화면 영역 바깥에 있을 때 화면 영역 안에 있는 시작 위치를 찾고, 위치까지의 높이를 구하고, 시작되는 대화내역의 최하단 위치를 구하는 처리와
화면 영역 안에 있을 때 대화내역들을 만들고, 위치까지의 높이를 구하는 연산와
프로그램 실행 중 스크롤의 현재 위치가 0이 될 때 이전의 내역이 있으면 원하는 크기만큼 대화내역을 불러들여 높이를 측정한 후 측정된 높이를 반환하는 처리
이 세가지를 연산으로 구현할 예정이다.
*/
#include "ChatProfileProcessor.h"
using namespace parkcom;

ChatProfileProcessor::ChatProfileProcessor(Scanner* scanner, Parser* parser) {

}

ChatProfileProcessor::~ChatProfileProcessor() {

}

Profile* ChatProfileProcessor::MakingChatProfile() {
	return 0;
}