#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
/* СТРУКТУРА ПЕРЕДАЧИ ИНФОРМАЦИИ ОБ АТРИБУТАХ */
/* Служит вспомогательным звеном для упрощение передачи атрибутов */
struct informationAttribute
{
	std::string nameAttribute;
	std::string valueAttribute;
	std::string typeDataAttribute;
	std::string linkEntity;
};
/* АТРИБУТЫ ФРЕЙМА */
class Entity;
class Attribute
{
private:
	std::string nameAttribute;
	std::string valueAtribute;
	std::string typeDataAtribute;
	Entity* linkFrame;
public:
	//Создает пустой атрибут
	Attribute();
	//Конструктор. Создает атрибут со всеми значениями.
	Attribute(std::string name, std::string text, std::string typeData);
	//Изменение имени, значения, типа данных атрибута
	//Изменение имени атрибута
	void ChangeNameAttribute(std::string newname);
	//Изменение значения атрибута
	void ChangeValueAttribute(std::string newvalue);
	//Изменение типа данных атрибута
	void ChangeTypeDataAttribute(std::string newtype);
	//Получение информации об атрибуте: имя, значение, тип данных или полной информации, включающую все это
	//Получение имени атрибута
	std::string GetNameAttribute();
	//Получение значения атрибута
	std::string GetValueAttribute();
	//Получение типа данных атрибута
	std::string GetTypeDataAttribute();
	//Получение всей информации об атрибутах слота фрейма в виде вектора структур
	informationAttribute GetAllAttributeInformation();
	//Формирование связей с другими фреймами
	//Добавляет связь атрибуту. 
	void AddLink(Entity* link);
	//Получение имени фрейма, на который атрибут ссылается. Если его нет, возвращает пустую строку
	std::string GetLinkEntity();
	//Удаление связи с другим фреймом
	void DeleteLink();
	//Удалить связь с указанным фреймом
	void DeleteLinkToEntity(std::string nameEntity);
	//Печать атрибута сущности
	void printAttribute();
	//Деструктор 
	~Attribute();
};
/* СЛОТЫ ФРЕЙМА */
class Slot
{
private:
	std::string nameSlot;
	std::vector<Attribute*> listAttributes;
	//Поиск индекса атрибута в векторе по его имени.
	bool SearchIndexAttribute(std::string nameAttribute, unsigned int& index)
	{
		for (unsigned int i = 0; i < listAttributes.size(); i++)
		{
			if (listAttributes[i]->GetNameAttribute() == nameAttribute)
			{
				index = i;
				return true;
			}
		}
		index = 0;
		return false;
	}
public:
	//Конструктор по умолчанию
	Slot();
	//Конструктор, принимающий название слота
	Slot(std::string newnameslot);
	//Собственные функции слота, а именно получение и изменение его названия
	//Изменение имени слота
	void ChangeNameSlot(std::string newNameSlot);
	//Получить имя слота
	std::string GetNameSlot();
	//Создание, получение, изменение и удаление атрибутов, а также проверка имени атрибута на уникальность
	//Добавление атрибута
	bool AddAttribute(std::string nameAttribute, std::string valueAttribute, std::string typeDataAttribute);
	//Получение всех имен атрибутов. Результат записывается в переданный вектор
	void GetAllNamesAttributes(std::vector<std::string>& allNamesAttributes);
	//Получение подробной информации об атрибуте
	informationAttribute GetAtributeInformation(std::string nameAttribute);
	//Получение всех атрибутов слота в виде вектора структур всей информации об атрибутах
	std::vector<informationAttribute> GetAllSlotAttributeInformation();
	//Получение всех типы данных атрибутов. Результат записывается в переданный вектор
	void GetAllTypeDataAttributes(std::vector<std::string>& allTypeDataAttributes);
	//Получить тип данных атрибута по его имени. Если атрибута с таким именем нет, возвращает пустую строку
	std::string GetTypeDataAttribute(std::string nameAttribute);
	//Получить значения атрибута по его имени. Если атрибута с таким именем нет, возвращает пустую строку
	std::string GetValueAttribute(std::string nameAttribute);
	//Получение имени фрейма, на которую ссылается атрибут
	std::string GetNameLinkAttribute(std::string nameAttribute);
	//Получение всех значений атрибутов (без исключения)
	void GetAllValueAttribetes(std::vector<std::string>& allValueAttributes);
	//Получение всех имен тех атрибутов, которые ссылаются на другие фреймы
	std::vector<std::string> GetAllLinkAttributes();
	//Проверка имени атрибута на уникальность.
	bool UniqueAttribute(std::string nameAttribute);
	//Изменение имени атрибута по его имени
	bool ChangeNameAttribute(std::string nameAttribute, std::string newNameAttribute);
	//Изменение значения атрибута по его имени
	bool ChangeValueAttribute(std::string nameAttribute, std::string newValueAttribute);
	//Изменение типа данных атрибута
	bool ChangeTypeDataAttribute(std::string nameAttribute, std::string newTypeDataAttribute);
	//Удаление атрибута
	bool DeleteAttribute(std::string nameAttribute);
	//Добавление, удаление и проверка наличия связей атрибутов
	//Добавление связи атрибуту с фреймом
	bool AddLinkAttribute(std::string nameAttribute, Entity* link);
	//Удаление связи атрибута с фреймом
	bool DeleteLinkAttribute(std::string nameAttribute);
	//Удаление всех связей с указанным фреймом
	void DeleteLinkToEntity(std::string nameEntity);
	//Печать слота со всеми атрибутами
	void PrintSlot();
	//Получить указатель на атрибут
	Attribute* GetPointerToAttribute(std::string nameAttribute);
	//Деструктор
	~Slot();
};
/* ФРЕЙМ */
class Entity
{
private:
	std::string nameEntity;
	std::vector<Slot*> listSlotes;
	//Поиск индекса слота в векторе по его имени. 
	bool SearchIndexSlot(std::string nameSlot, unsigned int &index)
	{
		for (unsigned int i = 0; i < listSlotes.size(); i++)
		{
			if (listSlotes[i]->GetNameSlot() == nameSlot)
			{
				index = i;
				return true;
			}
		}
		index = 0;
		return false;
	}
public:
	//Стандартный конструктор
	Entity();
	//Конструктор, принимающий название сущности
	Entity(std::string name);
	//Получение и изменение имени фрейма
	//Получить имя фрейма
	std::string GetNameEntity();
	//Изменить имя фрейма
	void ChangeEntity(std::string newNameEntity);
	//Операции со слотами
	//Проверка на уникальность имени слотов
	bool UniqueSlot(std::string nameSlot);
	//Добавить слот
	bool AddSlot(std::string nameSlot);
	//Получение имен всех имеющихся слотов фрейма
	std::vector<std::string> GetAllSlotNames();
	//Получение всей информации обо всех атрибутах слота фрейма
	std::vector<informationAttribute> GetAllSlotAttributeInformation(std::string nameSlot);
	//Получение всей информации об атрибуте слота фрейма
	informationAttribute GetInformationAttributeSlot(std::string nameSlot, std::string nameAttribute);
	//Изменить имя слота
	bool ChangeNameSlot(std::string nameSlot, std::string newNameSlot);
	//Удалить слот
	bool DeleteSlot(std::string nameSlot);
	//Удаление всех имеющихся слотов фрейма
	void DeleteAllStots();
	//Операции с атрибутами слотов
	//Добавить в слот атрибут
	bool AddAttributeToSlot(std::string nameSlot, std::string nameAttribute, std::string valueAttribute, std::string typeDataAttribute);
	//Получение всех имен атрибутов слота фрейма
	std::vector<std::string>  GetAllSlotAttributeNames(std::string nameSlot);
	//Получение всей информации атрибута слота фрейма
	informationAttribute GetAtributeInformation(std::string nameSlot, std::string nameAttribute);
	//Изменить в слоте имя атрибута
	bool ChangeNameAttributeToSlot(std::string nameSlot, std::string nameAttribute, std::string newNameAttribute);
	//Изменить в слоте значение атрибута
	bool ChangeValueAttributeToSlot(std::string nameSlot, std::string nameAttribute, std::string newValue);
	//Изменить в слоте тип данных атрибута
	bool ChangeTypeDataAttributeToSlot(std::string nameSlot, std::string nameAttribute, std::string newTypeData);
	//Удалить из слота атрибут
	bool DeleteAttributeToSlot(std::string nameSlot, std::string nameAttribete);
	//Операции с ссылками атрибутов слота
	//Установить атрибуту слота ссылку на фрейм
	bool AddLinkAtributeToSlot(std::string nameSlot, std::string nameAtribute, Entity* linkEntity);
	//Получить все имена фреймов, на коротый ссылается атрибуты слота
	std::vector<std::string> GetLinkAttributeToSlot(std::string nameSlot);
	//Удалить связь атрибута слота
	bool DeleteLinkEntitySlotAttribute(std::string nameSlot, std::string nameAttribute);
	//Удаление всех имеющихся связей с определенной сущностью
	void DeleteLinkToEntity(std::string nameEntity);
	//Перчать фрейма
	void PrintEntity();	
	//Вспомогательные. Используются для заполнения процедур
	//Получить указатель на слот
	Slot* GetPointerToSlot(std::string nameSlot);
	//Получить указатель на атрибут
	Attribute* GetPointerToAttribute(std::string nameSlot, std::string nameAttribute);
	//Деструктов фрейма
	~Entity();
};
/* СОХРАНЕНИЕ СВОЙСТВ И МЕТОДОВ. УСЛОВНО МОЖНО НАЗВАТЬ ПРОЦЕДУРАМИ */
//Структура процедуры
struct Procedure
{
	Entity* entity = NULL;//Используется только для сохранения в файле
	Slot* slot = NULL;//Используется только для сохранения в файле
	Attribute* attribute = NULL; //Атрибут, к которому относится
	std::string value;
};
/* ФРЕЙМОВАЯ МОДЕЛЬ */
class Base
{
private:
	std::string nameBase;
	std::vector<Entity*> listEntities;
	Entity* prototypeEntity;//Прототип для поиска
	std::string fileName; //Имя файла для чтения и записи
	std::map<std::string, Procedure*> procederes;//Процедуры. Индексом является их название, значение - структура "Procedure", хранящая указатель на атрибут устанавливаемое значение
	//Поиск индекса фрейма в векторе по его имени
	bool SearchIndexEntity(std::string nameEntity, unsigned int& index)
	{
		for (unsigned int i = 0; i < listEntities.size(); i++)
		{
			if (listEntities[i]->GetNameEntity() == nameEntity)
			{
				index = i;
				return true;
			}
		}
		return false;
	}
public:
	//Конструктор по умолчанию
	Base();
	//Конструктор, принимающий название фреймовой модели
	Base(std::string name);
	//Работа с фреймами
	//Уникальность имени фрейма в модели
	bool UniqueEntity(std::string nameEntity);
	//Создать фрейм
	bool AddEntity(std::string nameEntity);
	//Изменить имя фрейма
	bool ChangeNameEntity(std::string nameEntity, std::string newNameEntity);
	//Удалить фрейм
	bool DeleteEntity(std::string nameEntity);
	//Получить имена всех фреймов в базе
	std::vector<std::string> GetAllEntities();
	//Работа со слотами фреймов
	//Создать слот фрейма
	bool AddSlotToEntity(std::string nameEntity, std::string nameSlot);
	//Удалить слот фрейма
	bool DeleteSlotToEntity(std::string nameEntity, std::string nameSlot);
	//Изменить имя слота фрейма
	bool ChangeNameSlotToEntity(std::string nameEntity, std::string nameSlot, std::string newNameSlot);
	//Получить имена всех слотов фрейма
	std::vector<std::string> GetAllEntitySloteName(std::string nameEntity);
	//Получение всех имен атрибутов слота фрейма
	std::vector<std::string> GetAllEntitySlotAttributeNames(std::string nameEntity, std::string nameSlot);
	//Работа с атрибута
	//Добавить в слот фрейма атрибут
	bool AddAttributeToSlotToEntity(std::string nameEntity, std::string nameSlot, std::string nameAttribute, std::string valueAttribute, std::string typeDataAttribute);
	//Удалить из слота фрейма атрибут
	bool DeleteAttributeToSlotToEntity(std::string nameEntity, std::string nameSlot, std::string nameAttribute);
	//Изменить имя атрибута в слоте фрейма
	bool ChangeNameAttributeToSlotToEntity(std::string nameEntity, std::string nameSlot, std::string nameAttribute, std::string newNameAttribute);
	//Изменить значение атрибута в слоте фрейма
	bool ChangeValueAttributeToSlotToEntity(std::string nameEntity, std::string nameSlot, std::string nameAttribute, std::string newValueAttribute);
	//Получить всю информацию об атрибуте слота фрейма.
	informationAttribute GetInformationAttribute(std::string nameEntity, std::string nameSlot, std::string nameAttribute);
	//Изменение значения и типа данных атрибута (не допускается тип данных "frame" т.к. обозначает ссылку на другой фрейм)
	bool ChangeValueAndTypedataAttributeToSlotToEntity(std::string nameEntity, std::string nameSlot, std::string nameAttribute, std::string newValueAttribute, std::string typeDataAttribute);
	//Изменить тип данных атрибута
	bool ChangeTypedataAttributeToSlotToEntity(std::string nameEntity, std::string nameSlot, std::string nameAttribute, std::string typeDataAttribute);	
	//Работа с ссылками атрибутов слотов фреймов
	//Установить ссылку на фрейм у атрибута слота фрейма
	bool AddLinkEntityAttributeToAnotherEntity(std::string nameEntity, std::string nameSlot, std::string nameAttribute, std::string linkEntity);
	//Удалить связь атрибута слота фрейма с другим фреймом
	bool DeleteLinkEntityAttributeToAnotherEntity(std::string nameEntity, std::string nameSlot, std::string nameAttribute);
	//Работа с прототипом для поиска
	//Добавить прототип
	void AddPrototype();
	//Получить имя прототипа
	std::string GetNamePrototype();
	//Поиск ничего лишнего
	bool SearchForNothingMore(std::string mode);
	//Поиск всего подходящего
	bool SearchForEverythingSuitable(std::string mode);
	//Печать прототипа
	void PrintPrototype();
	//Печать фрейма
	void PrintEntity(std::string nameEntity);
	//Добавить процедуру
	bool AddProcedure(std::string nameProcedure, std::string nameEntity, std::string nameSlot, std::string nameAttribute, std::string valueAttribute);
	//Использовать процедуру
	bool UsingProcedure(std::string nameProcedure, std::string newValueAttribute, std::string& result);
	//Функции чтения-записи в файл
	//Установить имя файла для чтения/записи
	void SetReadWhiteFile(std::string newFileName);
	//Запись фреймовой модели в файл
	void BaseToFile();
};
//Чтение файла.
Base* FileToBase(std::string nameBase, std::string filename);