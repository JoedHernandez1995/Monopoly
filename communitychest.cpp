#include "communitychest.h"

CommunityChest::CommunityChest(){

}

CommunityChest::CommunityChest(char code, QString info){
    codigo = code;
    descripcion = info;
}

CommunityChest::CommunityChest(const CommunityChest& card){
    codigo = card.codigo;
    descripcion = card.descripcion;
}

CommunityChest::~CommunityChest(){

}

void CommunityChest::setCodigo(char code){
    codigo = code;
}

char CommunityChest::getCodigo()const{
    return codigo;
}

void CommunityChest::setDescripcion(QString info){
    descripcion = info;
}

QString CommunityChest::getDescripcion(){
    return descripcion;
}
