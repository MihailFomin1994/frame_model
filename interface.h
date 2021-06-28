#pragma once
#include "base.h"
/* ИНТЕРФЕЙС ПРОГРАММЫ */
//Проверка на ввод числа
unsigned int isDigit(std::string number);
//Печать меню с возвратом индекса меню
inline  unsigned int printMenu(unsigned int& key, std::vector<std::string>& menu);
//Неаварийное завершение программы
void closeProgramm(Base* base);
//Меню атрибутов. Изменение имен и значений атрибутов, создание, изменение и удаление их связей, а также удаление атрибутов
void AttributeMenu(Base* base, std::string nameEntity, std::string nameSlot, std::string nameAttribute);
//Меню слота фрейма
void SlotMenu(Base* base, std::string nameEntity, std::string nameSlot);
//Меню фрейма
void EntityMenu(Base* base, std::string nameEntity);
//Меню поиска
void SearchMenu(Base* base);
//Меню процедур
void ProcedureMenu(Base* base);
//Основное меню
void MainMenu(Base* base);
//Запуск интерфейса
void Interface(std::string nameBase, std::string filename);