#pragma once
#include "base.h"
/* ��������� ��������� */
//�������� �� ���� �����
unsigned int isDigit(std::string number);
//������ ���� � ��������� ������� ����
inline  unsigned int printMenu(unsigned int& key, std::vector<std::string>& menu);
//����������� ���������� ���������
void closeProgramm(Base* base);
//���� ���������. ��������� ���� � �������� ���������, ��������, ��������� � �������� �� ������, � ����� �������� ���������
void AttributeMenu(Base* base, std::string nameEntity, std::string nameSlot, std::string nameAttribute);
//���� ����� ������
void SlotMenu(Base* base, std::string nameEntity, std::string nameSlot);
//���� ������
void EntityMenu(Base* base, std::string nameEntity);
//���� ������
void SearchMenu(Base* base);
//���� ��������
void ProcedureMenu(Base* base);
//�������� ����
void MainMenu(Base* base);
//������ ����������
void Interface(std::string nameBase, std::string filename);