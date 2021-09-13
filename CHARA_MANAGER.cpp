//#include"common.h"
//#include"CONTAINER.h"
//#include "CHARA_MANAGER.h"
//#include"memLeakPlace_Start.h"
//CONTAINER* CHARA_MANAGER::C = 0;
//
//CHARA_MANAGER::CHARA_MANAGER(){
//	Total = C->data("CharasTotal");
//	Charas = new CHARACTER* [Total];
//
//	init();
//}
//
//CHARA_MANAGER::~CHARA_MANAGER(){
//	for (int i = 0; i < Total; i++) {
//		SAFE_DELETE(Charas[i]);
//	}
//	SAFE_DELETE_ARRAY(Charas);
//}
//
//void CHARA_MANAGER::init(){
//	for (int i = 0; i < Total;i++) {
//		Charas[i]->init();
//	}
//}
//
//void CHARA_MANAGER::update(){
//	for (int i = 0; i < Total; i++) {
//		Charas[i]->update();
//	}
//}
//
//void CHARA_MANAGER::draw(){
//	for (int i = 0; i < Total; i++) {
//		Charas[i]->draw();
//	}
//}
//
//
//#include"memLeakPlace_End.h"