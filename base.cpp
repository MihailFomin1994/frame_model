#include "base.h"
/* АТРИБУТЫ СЛОТА ФРЕЙМА */
//Создает пустой атрибут
Attribute::Attribute()
{
	nameAttribute = "";
	valueAtribute = "";
	typeDataAtribute = "";
	linkFrame = NULL;
}
//Конструктор. Создает атрибут со всеми значениями.
Attribute::Attribute(std::string name, std::string text, std::string typeData)
{
	linkFrame = NULL;
	nameAttribute = name;
	valueAtribute = text;
	if (valueAtribute.size() == 0 && typeDataAtribute == "frame")
	{
		typeDataAtribute = "null";
	}
	typeDataAtribute = typeData;
}
//Добавляет связь атрибуту. 
void Attribute::AddLink(Entity* link)
{
	valueAtribute = ""; //Сбрасываем значение значения атрибута
	typeDataAtribute = "frame"; //Присваиваем ему значение фрейма
	linkFrame = link; //Сохраняем ссылку на фрейм
}
//Получение имени атрибута
std::string Attribute::GetNameAttribute()
{
	return nameAttribute;
}
//Получение значения атрибута
std::string Attribute::GetValueAttribute()
{
	return valueAtribute;
}
//Получение типа данных атрибута
std::string Attribute::GetTypeDataAttribute()
{
	return typeDataAtribute;
}
//Получение имени фрейма, на который атрибут ссылается. Если его нет, возвращает пустую строку
std::string Attribute::GetLinkEntity()
{
	if (linkFrame == NULL)
	{
		return "";
	}
	return linkFrame->GetNameEntity();
}
//Изменение имени атрибута
void Attribute::ChangeNameAttribute(std::string newname)
{
	nameAttribute = newname;
}
//Изменение значения атрибута
void Attribute::ChangeValueAttribute(std::string newvalue)
{
	valueAtribute = newvalue;
	typeDataAtribute = "text";
	linkFrame = NULL; //Значение ссылки сбрасывается
}
//Изменение типа данных атрибута
void Attribute::ChangeTypeDataAttribute(std::string newtype)
{
	typeDataAtribute = newtype;
}
//Получение всей информации об атрибуте в виде структуры "informationAttribute"
informationAttribute Attribute::GetAllAttributeInformation()
{
	informationAttribute info;
	info.nameAttribute = nameAttribute;
	info.typeDataAttribute = typeDataAtribute;
	info.valueAttribute = valueAtribute;
	if (linkFrame != NULL)
	{
		info.linkEntity = linkFrame->GetNameEntity();
	}
	else
	{
		info.linkEntity = "Не имеет";
	}
	return info;
}
//Удаление связи с другим фреймом
void Attribute::DeleteLink()
{
	typeDataAtribute = "null";
	linkFrame = NULL;
}
//Удалить связь с указанным фреймом
void Attribute::DeleteLinkToEntity(std::string nameEntity)
{
	if (linkFrame != NULL)
	{
		if (linkFrame->GetNameEntity() == nameEntity)
		{
			linkFrame = NULL;
			typeDataAtribute = "null";

		}
	}
}
//Печать атрибута сущности
void Attribute::printAttribute()
{
	if (typeDataAtribute == "frame" && linkFrame != NULL)
	{
		std::cout << nameAttribute << " -> " << linkFrame->GetNameEntity() << " [" << typeDataAtribute << "] " << std::endl;		
	}
	else
	{
		std::cout << nameAttribute << " = " << valueAtribute << " [" << typeDataAtribute << "] " << std::endl;
	}
	
}
//Деструктор 
Attribute::~Attribute() {};

/* СЛОТЫ ФРЕЙМА */
//Конструктор по умолчанию
Slot::Slot()
{
	nameSlot = "";
}
//Конструктор, принимающий название слота
Slot::Slot(std::string newnameslot)
{
	nameSlot = newnameslot;
}

//Собственные функции слота, а именно получение и изменение его названия
//Изменение имени слота
void Slot::ChangeNameSlot(std::string newNameSlot)
{
	nameSlot = newNameSlot;
}
//Получить имя слота
std::string Slot::GetNameSlot()
{
	return nameSlot;
}
//Создание, получение, изменение и удаление атрибутов, а также проверка имени атрибута на уникальность
//Добавление атрибута
bool Slot::AddAttribute(std::string nameAttribute, std::string valueAttribute, std::string typeDataAttribute)
{
	//Проверяем уникальность имени атрибута в слоте
	if (UniqueAttribute(nameAttribute))
	{
		listAttributes.push_back(new Attribute(nameAttribute, valueAttribute, typeDataAttribute));
		return true;
	}
	return false;
}
//Получение всех имен атрибутов. Результат записывается в переданный вектор
void Slot::GetAllNamesAttributes(std::vector<std::string>& allNamesAttributes)
{
	for (unsigned int i = 0; i < listAttributes.size(); i++)
	{
		allNamesAttributes.push_back(listAttributes[i]->GetNameAttribute());
	}
}
//Получение подробной информации об атрибуте
informationAttribute Slot::GetAtributeInformation(std::string nameAttribute)
{
	informationAttribute info;
	unsigned int index = 0;
	if (SearchIndexAttribute(nameAttribute, index))
	{
		info = listAttributes[index]->GetAllAttributeInformation();
	}
	return info;
}
//Получение всех атрибутов слота в виде вектора структур всей информации об атрибутах
std::vector<informationAttribute> Slot::GetAllSlotAttributeInformation()
{
	std::vector<informationAttribute> allSlotAttributeInformation;
	for (unsigned int i = 0; i < listAttributes.size(); i++)
	{
		allSlotAttributeInformation.push_back(listAttributes[i]->GetAllAttributeInformation());
	}
	return allSlotAttributeInformation;
}
//Получение всех типы данных атрибутов. Результат записывается в переданный вектор
void Slot::GetAllTypeDataAttributes(std::vector<std::string>& allTypeDataAttributes)
{
	for (unsigned int i = 0; i < listAttributes.size(); i++)
	{
		allTypeDataAttributes.push_back(listAttributes[i]->GetTypeDataAttribute());
	}
}
//Получить тип данных атрибута по его имени. Если атрибута с таким именем нет, возвращает пустую строку
std::string Slot::GetTypeDataAttribute(std::string nameAttribute)
{
	std::string typeData = "";
	unsigned posAtr = 0;
	if (SearchIndexAttribute(nameAttribute, posAtr))
	{
		typeData = listAttributes[posAtr]->GetTypeDataAttribute();
	}
	return typeData;
}
//Получить значения атрибута по его имени. Если атрибута с таким именем нет, возвращает пустую строку
std::string Slot::GetValueAttribute(std::string nameAttribute)
{
	std::string value = "";
	unsigned posAtr = 0;
	if (SearchIndexAttribute(nameAttribute, posAtr))
	{
		value = listAttributes[posAtr]->GetValueAttribute();
	}
	return value;
}
//Получение имени фрейма, на которую ссылается атрибут
std::string Slot::GetNameLinkAttribute(std::string nameAttribute)
{
	std::string nameLink = "";
	unsigned posAtr = 0;
	if (SearchIndexAttribute(nameAttribute, posAtr))
	{
		nameLink = listAttributes[posAtr]->GetLinkEntity();
	}
	return nameLink;
}
//Получение всех значений атрибутов (без исключения)
void Slot::GetAllValueAttribetes(std::vector<std::string>& allValueAttributes)
{
	for (unsigned int i = 0; i < listAttributes.size(); i++)
	{
		allValueAttributes.push_back(listAttributes[i]->GetValueAttribute());
	}
}
//Получение всех имен тех атрибутов, которые ссылаются на другие фреймы
std::vector<std::string> Slot::GetAllLinkAttributes()
{
	std::vector<std::string> allLinkAttributes;
	for (unsigned int i = 0; i < listAttributes.size(); i++)
	{
		if (listAttributes[i]->GetTypeDataAttribute() == "frame")
		{
			allLinkAttributes.push_back(listAttributes[i]->GetValueAttribute());
		}
	}
	return allLinkAttributes;
}
//Проверка имени атрибута на уникальность.
bool Slot::UniqueAttribute(std::string nameAttribute)
{
	unsigned int result = 0;
	return !SearchIndexAttribute(nameAttribute, result);
}
//Изменение имени атрибута по его имени
bool Slot::ChangeNameAttribute(std::string nameAttribute, std::string newNameAttribute)
{
	unsigned int posAtribute = 0;
	if (SearchIndexAttribute(nameAttribute, posAtribute))//Если существует атрибут с таким именем
	{
		if (UniqueAttribute(newNameAttribute))//И данной имя не использует более не один слот
		{
			listAttributes[posAtribute]->ChangeNameAttribute(newNameAttribute);
			return true;
		}
	}
	return false;
}
//Изменение значения атрибута по его имени
bool Slot::ChangeValueAttribute(std::string nameAttribute, std::string newValueAttribute)
{
	unsigned int posAtribute = 0;
	if (SearchIndexAttribute(nameAttribute, posAtribute))
	{
		listAttributes[posAtribute]->ChangeValueAttribute(newValueAttribute);
		
		return true;
	}
	return false;
}
//Изменение типа данных атрибута
bool Slot::ChangeTypeDataAttribute(std::string nameAttribute, std::string newTypeDataAttribute)
{
	unsigned int posAtribute = 0;
	if (SearchIndexAttribute(nameAttribute, posAtribute))
	{
		listAttributes[posAtribute]->ChangeTypeDataAttribute(newTypeDataAttribute);
		return true;
	}
	return false;
}
//Удаление атрибута
bool Slot::DeleteAttribute(std::string nameAttribute)
{
	unsigned int posAtribute = 0;
	if (SearchIndexAttribute(nameAttribute, posAtribute))
	{
		listAttributes[posAtribute]->~Attribute(); //Запускаем деструктор атрибута
		listAttributes.erase(listAttributes.begin() + posAtribute); //Удаляем указатель на уже несуществующий атрибут по его индексу
		return true;
	}
	return false;
}
//Добавление, удаление и проверка наличия связей атрибутов
//Добавление связи атрибуту с фреймом
bool Slot::AddLinkAttribute(std::string nameAttribute, Entity* link)
{
	unsigned int posAtribute = 0;
	if (SearchIndexAttribute(nameAttribute, posAtribute))
	{
		listAttributes[posAtribute]->AddLink(link);
		return true;
	}
	return false;
}
//Удаление связи атрибута с фреймом
bool Slot::DeleteLinkAttribute(std::string nameAttribute)
{
	unsigned int index = 0;
	if (SearchIndexAttribute(nameAttribute, index))
	{
		listAttributes[index]->DeleteLink();
		return true;
	}
	return false;
}
//Удаление всех связей с указанным фреймом
void Slot::DeleteLinkToEntity(std::string nameEntity)
{
	for (unsigned int i = 0; i < listAttributes.size(); i++)
	{
		listAttributes[i]->DeleteLinkToEntity(nameEntity);
	}
}
//Печать слота со всеми атрибутами
void Slot::PrintSlot()
{
	for (unsigned int i = 0; i < listAttributes.size(); i++)
	{
		listAttributes[i]->printAttribute();
	}
}
//Получить указатель на атрибут
Attribute* Slot::GetPointerToAttribute(std::string nameAttribute)
{
	unsigned int index = 0;
	if (SearchIndexAttribute(nameAttribute, index))
	{
		return listAttributes[index];
	}
	return NULL;
}
//Деструктор
Slot::~Slot()
{
	//Ручной запуск деструктора у каждого имеющегося атрибута в слоте
	for (unsigned int i = 0; i < listAttributes.size(); i++)
	{
		listAttributes[i]->~Attribute();
	}
}
/* ФРЕЙМА */
//Стандартный конструктор
Entity::Entity()
{
	nameEntity = "";
}
//Конструктор, принимающий название сущности
Entity::Entity(std::string name)
{
	nameEntity = name;
}

//Получение и изменение имени фрейма
//Получить имя фрейма
std::string Entity::GetNameEntity()
{
	return nameEntity;
}
//Изменить имя фрейма
void Entity::ChangeEntity(std::string newNameEntity)
{
	nameEntity = newNameEntity;
}
//Операции со слотами
//Проверка на уникальность имени слотов
bool Entity::UniqueSlot(std::string nameSlot)
{
	unsigned int index = 0;
	return !SearchIndexSlot(nameSlot, index);
}
//Добавить слот
bool Entity::AddSlot(std::string nameSlot)
{
	if (UniqueSlot(nameSlot))
	{
		listSlotes.push_back(new Slot(nameSlot));
		return true;
	}
	return false;
}
//Получение имен всех имеющихся слотов фрейма
std::vector<std::string> Entity::GetAllSlotNames()
{
	std::vector<std::string> allSlotNames;
	for (unsigned int i = 0; i < listSlotes.size(); i++)
	{
		allSlotNames.push_back(listSlotes[i]->GetNameSlot());
	}
	return allSlotNames;
}
//Получение всей информации обо всех атрибутах слота фрейма
std::vector<informationAttribute> Entity::GetAllSlotAttributeInformation(std::string nameSlot)
{
	std::vector<informationAttribute> AllSlotAttributeInformation;
	unsigned int index = 0;
	if (SearchIndexSlot(nameSlot, index))
	{
		AllSlotAttributeInformation = listSlotes[index]->GetAllSlotAttributeInformation();
	}
	return AllSlotAttributeInformation;
}
//Получение всей информации об атрибуте слота фрейма
informationAttribute Entity::GetInformationAttributeSlot(std::string nameSlot, std::string nameAttribute)
{
	unsigned int index = 0;
	informationAttribute info;
	if (SearchIndexSlot(nameSlot, index))
	{
		info = listSlotes[index]->GetAtributeInformation(nameAttribute);
	}
	return info;
}
//Изменить имя слота
bool Entity::ChangeNameSlot(std::string nameSlot, std::string newNameSlot)
{
	unsigned int index = 0;
	if (SearchIndexSlot(nameSlot, index))//Если слот с таким именем существует
	{
		if (UniqueSlot(newNameSlot))//И более нет слота с таким именем
		{
			listSlotes[index]->ChangeNameSlot(newNameSlot);
			return true;
		}
	}
	return false;
}
//Удалить слот
bool Entity::DeleteSlot(std::string nameSlot)
{
	unsigned int index = 0;
	if (SearchIndexSlot(nameSlot, index))
	{
		listSlotes[index]->~Slot();
		listSlotes.erase(listSlotes.begin() + index);
		return true;
	}
	return false;
}
//Удаление всех имеющихся слотов фрейма
void Entity::DeleteAllStots()
{
	for (unsigned int i = 0; i < listSlotes.size(); i++)
	{
		listSlotes[i]->~Slot();
		listSlotes.clear();
	}
}
//Операции с атрибутами слотов
//Добавить в слот атрибут
bool Entity::AddAttributeToSlot(std::string nameSlot, std::string nameAttribute, std::string valueAttribute, std::string typeDataAttribute)
{
	unsigned int index = 0;
	if (SearchIndexSlot(nameSlot, index))
	{
		if (listSlotes[index]->AddAttribute(nameAttribute, valueAttribute, typeDataAttribute))
		{
			return true;
		}
	}
	return false;
}
//Получение всех имен атрибутов слота фрейма
std::vector<std::string> Entity::GetAllSlotAttributeNames(std::string nameSlot)
{
	std::vector<std::string> AllSlotAttributeNames;
	unsigned int index = 0;
	if (SearchIndexSlot(nameSlot, index))
	{
		listSlotes[index]->GetAllNamesAttributes(AllSlotAttributeNames);
	}
	return AllSlotAttributeNames;
}
//Получение всей информации атрибута слота фрейма
informationAttribute Entity::GetAtributeInformation(std::string nameSlot, std::string nameAttribute)
{
	informationAttribute info;
	unsigned int index = 0;
	if (SearchIndexSlot(nameSlot, index))
	{
		info = listSlotes[index]->GetAtributeInformation(nameAttribute);
	}
	return info;
}
//Изменить в слоте имя атрибута
bool Entity::ChangeNameAttributeToSlot(std::string nameSlot, std::string nameAttribute, std::string newNameAttribute)
{
	unsigned int index = 0;
	if (SearchIndexSlot(nameSlot, index))
	{
		if (listSlotes[index]->ChangeNameAttribute(nameAttribute, newNameAttribute))
		{
			return true;
		}
	}
	return false;
}
//Изменить в слоте значение атрибута
bool Entity::ChangeValueAttributeToSlot(std::string nameSlot, std::string nameAttribute, std::string newValue)
{
	unsigned int index = 0;
	if (SearchIndexSlot(nameSlot, index))
	{
		if (listSlotes[index]->ChangeValueAttribute(nameAttribute, newValue))
		{
			return true;
		}
	}
	return false;
}
//Изменить в слоте тип данных атрибута
bool Entity::ChangeTypeDataAttributeToSlot(std::string nameSlot, std::string nameAttribute, std::string newTypeData)
{
	unsigned int index = 0;
	if (SearchIndexSlot(nameSlot, index))
	{
		if (listSlotes[index]->ChangeTypeDataAttribute(nameAttribute, newTypeData))
		{
			return true;
		}
	}
	return false;
}
//Удалить из слота атрибут
bool Entity::DeleteAttributeToSlot(std::string nameSlot, std::string nameAttribete)
{
	unsigned int index = 0;
	if (SearchIndexSlot(nameSlot, index))
	{
		if (listSlotes[index]->DeleteAttribute(nameAttribete))
		{
			return true;
		}
	}
	return false;
}
//Операции с ссылками атрибутов слота
//Установить атрибуту слота ссылку на фрейм
bool Entity::AddLinkAtributeToSlot(std::string nameSlot, std::string nameAtribute, Entity* linkEntity)
{
	unsigned int index = 0;
	if (SearchIndexSlot(nameSlot, index))
	{
		if (listSlotes[index]->AddLinkAttribute(nameAtribute, linkEntity))
		{
			return true;
		}
	}
	return false;
}
//Получить все имена фреймов, на коротый ссылается атрибуты слота
std::vector<std::string> Entity::GetLinkAttributeToSlot(std::string nameSlot)
{
	std::vector<std::string> allLinkSlotAttributeToEntities;
	unsigned int index = 0;
	if (SearchIndexSlot(nameSlot, index))
	{
		allLinkSlotAttributeToEntities = listSlotes[index]->GetAllLinkAttributes();
	}
	return allLinkSlotAttributeToEntities;
}
//Удалить связь атрибута слота
bool Entity::DeleteLinkEntitySlotAttribute(std::string nameSlot, std::string nameAttribute)
{
	unsigned int index = 0;
	if (SearchIndexSlot(nameSlot, index))
	{
		return listSlotes[index]->DeleteLinkAttribute(nameAttribute);
	}
	return false;
}
//Удаление всех имеющихся связей с определенной сущностью
void Entity::DeleteLinkToEntity(std::string nameEntity)
{
	for (unsigned int i = 0; i < listSlotes.size(); i++)
	{
		listSlotes[i]->DeleteLinkToEntity(nameEntity);
	}
}
//Печать фрейма
void Entity::PrintEntity()
{
	for (unsigned int i = 0; i < listSlotes.size(); i++)
	{
		std::cout << "<" << listSlotes[i]->GetNameSlot() <<">"<< std::endl;
		listSlotes[i]->PrintSlot();
	}
}
//Получить указатель на слот
Slot* Entity::GetPointerToSlot(std::string nameSlot)
{
	unsigned int index = 0;
	if (SearchIndexSlot(nameSlot, index))
	{
		return listSlotes[index];
	}
	return NULL;
}
//Получить указатель на атрибут и его слот
Attribute* Entity::GetPointerToAttribute(std::string nameSlot, std::string nameAttribute)
{
	unsigned int index = 0;
	if (SearchIndexSlot(nameSlot, index))
	{
		return listSlotes[index]->GetPointerToAttribute(nameAttribute);
	}
	return NULL;
}
//Деструктов фрейма
Entity::~Entity()
{
	for (unsigned int i = 0; i < listSlotes.size(); i++)
	{
		listSlotes[i]->~Slot();
	}
}
/* ФРЕЙМОВАЯ МОДЕЛЬ */
//Конструктор по умолчанию
Base::Base()
{
	nameBase = "";
	fileName = "";
	prototypeEntity = new Entity();
}
//Конструктор, принимающий название фреймовой модели
Base::Base(std::string name)
{
	nameBase = name;
	fileName = "";
	prototypeEntity = new Entity();
}

//Работа с фреймами
//Уникальность имени фрейма в модели
bool Base::UniqueEntity(std::string nameEntity)
{
	unsigned index = 0;
	if (!(SearchIndexEntity(nameEntity, index)))
	{
		return true;
	}
	return false;
}
//Создать фрейм
bool Base::AddEntity(std::string nameEntity)
{
	if (UniqueEntity(nameEntity))
	{
		listEntities.push_back(new Entity(nameEntity));
		return true;
	}
	return false;
}
//Изменить имя фрейма
bool Base::ChangeNameEntity(std::string nameEntity, std::string newNameEntity)
{
	unsigned int index = 0;
	if (SearchIndexEntity(nameEntity, index))
	{
		if (UniqueEntity(newNameEntity))
		{
			listEntities[index]->ChangeEntity(newNameEntity);
			return true;
		}		
	}
	return false;
}
//Удалить фрейм
bool Base::DeleteEntity(std::string nameEntity)
{
	if (nameEntity == "ФРЕЙМ - ПРОТОТИП ДЛЯ ПОИСКА")
	{
		AddPrototype();
		return true;
	}
	else
	{
		unsigned int index = 0;
		if (SearchIndexEntity(nameEntity, index))
		{		
			//Найти все атрибуты, которые на него ссылались, и изменяем их на пустые
			for (unsigned int i = 0; i < listEntities.size(); i++)
			{
				listEntities[i]->DeleteLinkToEntity(nameEntity);
			}			
			//Найти среди процедур те, в которых данный фрейм указывается, и удалить их
			for (std::map<std::string, Procedure*>::iterator it = procederes.begin(); it != procederes.end(); )
			{
				if (it->second->entity->GetNameEntity() == nameEntity)
				{
					it = procederes.erase(it);
				}
				else
				{
					++it;
				}
			}			
			listEntities[index]->~Entity();
			listEntities.erase(listEntities.begin() + index);
			return true;
		}
	}	
	return false;
}
//Получить имена всех фреймов в базе
std::vector<std::string> Base::GetAllEntities()
{
	std::vector<std::string> allEntities;
	for (unsigned int i = 0; i < listEntities.size(); i++)
	{
		allEntities.push_back(listEntities[i]->GetNameEntity());
	}
	return allEntities;
}

//Работа со слотами фреймов
//Создать слот фрейма
bool Base::AddSlotToEntity(std::string nameEntity, std::string nameSlot)
{
	if (nameEntity == "ФРЕЙМ - ПРОТОТИП ДЛЯ ПОИСКА")
	{
		return prototypeEntity->AddSlot(nameSlot);
	}
	else
	{
		unsigned int index = 0;
		if (SearchIndexEntity(nameEntity, index))
		{
			return listEntities[index]->AddSlot(nameSlot);
		}
	}	
	return false;
}
//Удалить слот фрейма
bool Base::DeleteSlotToEntity(std::string nameEntity, std::string nameSlot)
{
	if (nameEntity == "ФРЕЙМ - ПРОТОТИП ДЛЯ ПОИСКА")
	{
		return prototypeEntity->DeleteSlot(nameSlot);
	}
	else
	{
		unsigned int index = 0;
		if (SearchIndexEntity(nameEntity, index))
		{
			//Найти среди процедур те, в которых данный фрейм с данным слотом указывается, и удалить их
			for (std::map<std::string, Procedure*>::iterator it = procederes.begin(); it != procederes.end(); )
			{
				std::string ent = it->second->entity->GetNameEntity();
				if (it->second->slot->GetNameSlot() == nameSlot && ent == nameEntity)
				{
					it = procederes.erase(it);
				}
				else
				{
					++it;
				}
			}
			return listEntities[index]->DeleteSlot(nameSlot);
		}
	}	
	return false;
}
//Изменить имя слота фрейма
bool Base::ChangeNameSlotToEntity(std::string nameEntity, std::string nameSlot, std::string newNameSlot)
{
	if (nameEntity == "ФРЕЙМ - ПРОТОТИП ДЛЯ ПОИСКА")
	{
		return prototypeEntity->ChangeNameSlot(nameSlot, newNameSlot);
	}
	else
	{
		unsigned int index = 0;
		if (SearchIndexEntity(nameEntity, index))
		{
			return listEntities[index]->ChangeNameSlot(nameSlot, newNameSlot);
		}
	}	
	return false;
}
//Получить имена всех слотов фрейма
std::vector<std::string> Base::GetAllEntitySloteName(std::string nameEntity)
{
	std::vector<std::string> AllSlotesName;
	if (nameEntity == "ФРЕЙМ - ПРОТОТИП ДЛЯ ПОИСКА")
	{
		AllSlotesName = prototypeEntity->GetAllSlotNames();
	}
	else
	{
		unsigned int index = 0;
		if (SearchIndexEntity(nameEntity, index))
		{
			AllSlotesName = listEntities[index]->GetAllSlotNames();
		}
	}	
	return AllSlotesName;
}
//Получение всех имен атрибутов слота фрейма
std::vector<std::string> Base::GetAllEntitySlotAttributeNames(std::string nameEntity, std::string nameSlot)
{
	unsigned int index = 0;
	std::vector<std::string> allSlotAttributeNames;
	if (nameEntity == "ФРЕЙМ - ПРОТОТИП ДЛЯ ПОИСКА")
	{
		allSlotAttributeNames = prototypeEntity->GetAllSlotAttributeNames(nameSlot);
	}
	else
	{
		if (SearchIndexEntity(nameEntity, index))
		{
			allSlotAttributeNames = listEntities[index]->GetAllSlotAttributeNames(nameSlot);

		}
	}	
	return allSlotAttributeNames;
}
//Работа с атрибутами
//Добавить в слот фрейма атрибут
bool Base::AddAttributeToSlotToEntity(std::string nameEntity, std::string nameSlot, std::string nameAttribute, std::string valueAttribute, std::string typeDataAttribute)
{
	if (nameEntity == "ФРЕЙМ - ПРОТОТИП ДЛЯ ПОИСКА")
	{
		return prototypeEntity->AddAttributeToSlot(nameSlot, nameAttribute, valueAttribute, typeDataAttribute);
	}
	else
	{
		unsigned int index = 0;
		if (SearchIndexEntity(nameEntity, index))
		{
			return listEntities[index]->AddAttributeToSlot(nameSlot, nameAttribute, valueAttribute, typeDataAttribute);
		}
	}	
	return false;
}
//Удалить из слота фрейма атрибут
bool Base::DeleteAttributeToSlotToEntity(std::string nameEntity, std::string nameSlot, std::string nameAttribute)
{
	if (nameEntity == "ФРЕЙМ - ПРОТОТИП ДЛЯ ПОИСКА")
	{
		prototypeEntity->DeleteAttributeToSlot(nameSlot, nameAttribute);
	}
	else
	{
		unsigned int index = 0;
		if (SearchIndexEntity(nameEntity, index))
		{
			//Найти среди процедур те, в которых данный фрейм с данным слотом указывается, и удалить их
			for (std::map<std::string, Procedure*>::iterator it = procederes.begin(); it != procederes.end(); )
			{
				std::string ent = it->second->entity->GetNameEntity();
				std::string slot = it->second->slot->GetNameSlot();
				if (it->second->attribute->GetNameAttribute() == nameAttribute && ent == nameEntity && slot == nameSlot)
				{
					it = procederes.erase(it);				
				}
				else
				{
					++it;
				}
			}
			return listEntities[index]->DeleteAttributeToSlot(nameSlot, nameAttribute);
		}
	}	
	return false;
}
//Изменить имя атрибута в слоте фрейма
bool Base::ChangeNameAttributeToSlotToEntity(std::string nameEntity, std::string nameSlot, std::string nameAttribute, std::string newNameAttribute)
{
	if (nameEntity == "ФРЕЙМ - ПРОТОТИП ДЛЯ ПОИСКА")
	{
		return prototypeEntity->ChangeNameAttributeToSlot(nameSlot, nameAttribute, newNameAttribute);
	}
	else
	{
		unsigned int index = 0;
		if (SearchIndexEntity(nameEntity, index))
		{
			return listEntities[index]->ChangeNameAttributeToSlot(nameSlot, nameAttribute, newNameAttribute);
		}
	}	
	return false;
}
//Изменить значение атрибута в слоте фрейма
bool Base::ChangeValueAttributeToSlotToEntity(std::string nameEntity, std::string nameSlot, std::string nameAttribute, std::string newValueAttribute)
{
	if (nameEntity == "ФРЕЙМ - ПРОТОТИП ДЛЯ ПОИСКА")
	{
		prototypeEntity->ChangeValueAttributeToSlot(nameSlot, nameAttribute, newValueAttribute);
	}
	else
	{
		unsigned int index = 0;
		if (SearchIndexEntity(nameEntity, index))
		{
			return listEntities[index]->ChangeValueAttributeToSlot(nameSlot, nameAttribute, newValueAttribute);
		}
	}	
	return false;
}
//Получить всю информацию об атрибуте слота фрейма.
informationAttribute Base::GetInformationAttribute(std::string nameEntity, std::string nameSlot, std::string nameAttribute)
{
	informationAttribute info;
	if (nameEntity == "ФРЕЙМ - ПРОТОТИП ДЛЯ ПОИСКА")
	{
		info = prototypeEntity->GetInformationAttributeSlot(nameSlot, nameAttribute);
	}
	else
	{
		unsigned int index = 0;
		if (SearchIndexEntity(nameEntity, index))
		{
			info = listEntities[index]->GetInformationAttributeSlot(nameSlot, nameAttribute);
		}
	}	
	return info;
}
//Изменение значения и типа данных атрибута
bool Base::ChangeValueAndTypedataAttributeToSlotToEntity(std::string nameEntity, std::string nameSlot, std::string nameAttribute, std::string newValueAttribute, std::string typeDataAttribute)
{
	if (nameEntity == "ФРЕЙМ - ПРОТОТИП ДЛЯ ПОИСКА")
	{
		if (prototypeEntity->ChangeValueAttributeToSlot(nameSlot, nameAttribute, newValueAttribute))
		{
			return prototypeEntity->ChangeTypeDataAttributeToSlot(nameSlot, nameAttribute, typeDataAttribute);
		}
	}
	else
	{
		unsigned int index = 0;
		if (SearchIndexEntity(nameEntity, index))
		{
			if (listEntities[index]->ChangeValueAttributeToSlot(nameSlot, nameAttribute, newValueAttribute))
			{
				return listEntities[index]->ChangeTypeDataAttributeToSlot(nameSlot, nameAttribute, typeDataAttribute);
			}
		}
	}	
	return false;
}
//Изменить тип данных атрибута
bool Base::ChangeTypedataAttributeToSlotToEntity(std::string nameEntity, std::string nameSlot, std::string nameAttribute, std::string typeDataAttribute)
{
	if (nameEntity == "ФРЕЙМ - ПРОТОТИП ДЛЯ ПОИСКА")
	{
		return prototypeEntity->ChangeTypeDataAttributeToSlot(nameSlot, nameAttribute, typeDataAttribute);
	}
	else
	{
		unsigned int index = 0;
		if (SearchIndexEntity(nameEntity, index))
		{
			return listEntities[index]->ChangeTypeDataAttributeToSlot(nameSlot, nameAttribute, typeDataAttribute);
		}
	}
	return false;
}

//Работа с ссылками атрибутов слотов фреймов
//Установить ссылку на фрейм у атрибута слота фрейма
bool Base::AddLinkEntityAttributeToAnotherEntity(std::string nameEntity, std::string nameSlot, std::string nameAttribute, std::string linkEntity)
{
	unsigned int indexEntity = 0, indexLinkEntity = 0;
	if (SearchIndexEntity(nameEntity, indexEntity) && nameEntity != linkEntity)
	{
		if (SearchIndexEntity(linkEntity, indexLinkEntity))
		{
			return listEntities[indexEntity]->AddLinkAtributeToSlot(nameSlot, nameAttribute, listEntities[indexLinkEntity]);
		}
	}
	return false;
}
//Удалить связь атрибута слота фрейма с другим фреймом
bool Base::DeleteLinkEntityAttributeToAnotherEntity(std::string nameEntity, std::string nameSlot, std::string nameAttribute)
{
	unsigned int index = 0;
	if (SearchIndexEntity(nameEntity, index))
	{
		return listEntities[index]->DeleteLinkEntitySlotAttribute(nameSlot, nameAttribute);
	}
	return false;
}
//Работа с прототипом для поиска
//Задать новый прототип (по суди, удаляются все слоты с атрибутами прототипа)
void Base::AddPrototype()
{
	prototypeEntity->ChangeEntity("");
	prototypeEntity->DeleteAllStots();
}
//Получить имя прототипа
std::string Base::GetNamePrototype()
{
	return prototypeEntity->GetNameEntity();
}
//Поиск ничего лишнего
bool Base::SearchForNothingMore(std::string mode)
{
	if (prototypeEntity->GetAllSlotNames().size() == 0)//Если у прототипа нет ни одного слота, то не подходит ни один другой фрейм
	{
		return false;
	}
	if (mode != "_SINTAX" && mode != "_SEMANTIC")
	{
		return false;
	}
	//Получение имен всех слотов прототипа
	for (unsigned int indexEnotity = 0; indexEnotity < listEntities.size(); indexEnotity++)
	{
		if (prototypeEntity->GetAllSlotNames().size() != listEntities[indexEnotity]->GetAllSlotNames().size())//Если количество слотов прототипа и текущего фрейма не совпадают
		{
			continue;//Сравниваем следующий по порядку фрейм
		}
		else
		{
			//Если количество слотов прототипа и текущего фрейма совпадает, сравниваем уже количество атрибутов слота прототипа и слота текущего фрейма
			//А также имена слотов фрейма
			std::vector<std::string> prototypeSlotes = prototypeEntity->GetAllSlotNames();
			std::vector<std::string> entitySlotes = listEntities[indexEnotity]->GetAllSlotNames();
			bool indicationNotMatch = false;//Индикатор несовпадения. Если имя слота, количество его атрибутов не совпадают
			for (unsigned int indexSlot = 0; indexSlot < prototypeSlotes.size() && !indicationNotMatch; indexSlot++)
			{
				std::string nameSlotPrototype = prototypeSlotes[indexSlot];//Сохраняем имя текущего слота прототипа
				std::string nameSlotEntity = entitySlotes[indexSlot];//Сохраняем имя текущего слота фрейма
				if (nameSlotPrototype != nameSlotEntity)//Если имена слотов фрейма не совпадают
				{
					//Прерываем текущий цикл и помечаем, что текущий фрейм не подходит
					indicationNotMatch = true;
					break;					
				}
				//Получаем всю информацию об атрибутах слота прототипа и текущего фрейма и сохраняем ее в отдельные вектора (для удобства)
				std::vector<informationAttribute> infoAttributeToSlotToPrototype = prototypeEntity->GetAllSlotAttributeInformation(nameSlotPrototype);
				std::vector<informationAttribute> infoAttributeToSlotToEntity = listEntities[indexEnotity]->GetAllSlotAttributeInformation(nameSlotEntity);
				//Сравниваем количество атрибутов слота прототипа и слота фрейма
				if (infoAttributeToSlotToPrototype.size() != infoAttributeToSlotToEntity.size())
				{
					//Прерываем текущий цикл и помечаем, что текущий фрейм не подходит
					indicationNotMatch = true;
					break;					
				}
				//Сравниваем атрибуты слота прототипа и слота текущего фрейма
				for (unsigned int indexAttribute = 0; indexAttribute < infoAttributeToSlotToPrototype.size(); indexAttribute++)
				{
					//Если тип данных требуется игнорировать
					if (infoAttributeToSlotToPrototype[indexAttribute].typeDataAttribute == "")
					{
						infoAttributeToSlotToEntity[indexAttribute].typeDataAttribute = "";
					}
					//У синтаксического и семантического поиска имя атрибута и его тип сравниваются. 
					if (infoAttributeToSlotToPrototype[indexAttribute].nameAttribute != infoAttributeToSlotToEntity[indexAttribute].nameAttribute
						|| infoAttributeToSlotToPrototype[indexAttribute].typeDataAttribute != infoAttributeToSlotToEntity[indexAttribute].typeDataAttribute)
					{
						indicationNotMatch = true;
						break;
					}
					//Только для семантического поиска. Сравнение значения атрибута прототипа и фрейма
					if (mode == "_SEMANTIC" && infoAttributeToSlotToPrototype[indexAttribute].valueAttribute != infoAttributeToSlotToEntity[indexAttribute].valueAttribute)
					{
						indicationNotMatch = true;
						break;
					}
				}
			}
			if (indicationNotMatch)//Если индикатор несовпадения сработал, берем следующую сущность
			{
				continue;
			}
			else
			{
				//Если все циклы прошли успешно, значит, фрейм был найден.
				prototypeEntity->ChangeEntity(listEntities[indexEnotity]->GetNameEntity());
				return true;
			}
		}
	}
	return false;
}
//Поиск всего подходящего
bool Base::SearchForEverythingSuitable(std::string mode)
{
	if (prototypeEntity->GetAllSlotNames().size() == 0)//Если у прототипа нет ни одного слота, то подходит любой фрейм. Указываем первый имеющийся
	{
		prototypeEntity->ChangeEntity(listEntities[0]->GetNameEntity());
		return true;
	}
	if (mode != "_SINTAX" && mode != "_SEMANTIC")
	{
		return false;
	}
	//Получение имен всех слотов прототипа
	for (unsigned int indexEnotity = 0; indexEnotity < listEntities.size(); indexEnotity++)
	{
		if (prototypeEntity->GetAllSlotNames().size() > listEntities[indexEnotity]->GetAllSlotNames().size())//Если количество слотов прототипа больше количества слотов текущего фрейма
		{
			continue;//Сравниваем следующий по порядку фрейм
		}
		else
		{
			//Если количество слотов прототипа меньше или равно количеству слотов у текущего фрейма,
			//то сравниваем уже количество атрибутов слота прототипа и слота текущего фрейма
			//А также имена слотов фрейма
			std::vector<std::string> prototypeSlotes = prototypeEntity->GetAllSlotNames();
			std::vector<std::string> entitySlotes = listEntities[indexEnotity]->GetAllSlotNames();
			unsigned int indexSlotEntity = 0;//Индекс слота фрейма
			bool indicationNotMatch = false;//Индикатор несовпадения. Если имя слота, количество его атрибутов не совпадают
			for (unsigned int indexSlotPrototipe = 0; indexSlotPrototipe < prototypeSlotes.size() && !indicationNotMatch; indexSlotPrototipe++)
			{
				std::string nameSlotPrototype = prototypeSlotes[indexSlotPrototipe];//Сохраняем имя текущего слота прототипа
				for (; indexSlotEntity <= entitySlotes.size(); indexSlotEntity++)
				{
					if (indexSlotEntity == entitySlotes.size())//Последний проход. Означает, что слота с именем, как у прототипа, нет
					{
						indicationNotMatch = true;
						break;
					}
					if (entitySlotes[indexSlotEntity] == nameSlotPrototype)//Если слот найден
					{
						break;
					}
				}
				if (indicationNotMatch)//Выход из внешнего цикла
				{
					break;
				}
				std::string nameSlotEntity = entitySlotes[indexSlotEntity];//Сохраняем имя найденого слота фрейма
				//Получаем всю информацию об атрибутах слота прототипа и соответствующего ему слота фрейма и сохраняем ее в отдельные вектора (для удобства)
				std::vector<informationAttribute> infoAttributeToSlotToPrototype = prototypeEntity->GetAllSlotAttributeInformation(nameSlotPrototype);
				std::vector<informationAttribute> infoAttributeToSlotToEntity = listEntities[indexEnotity]->GetAllSlotAttributeInformation(nameSlotEntity);
				//Сравниваем количество атрибутов слота прототипа и слота фрейма. Если у слота прототипа их больше, выходим и помечаем это
				if (infoAttributeToSlotToPrototype.size() > infoAttributeToSlotToEntity.size())
				{
					//Прерываем текущий цикл и помечаем, что текущий фрейм не подходит
					indicationNotMatch = true;					
					break;
				}
				unsigned int indexAttributeEntity = 0;
				//Сравниваем атрибуты слота прототипа и слота текущего фрейма
				for (unsigned int indexAttributePrototype = 0; indexAttributePrototype < infoAttributeToSlotToPrototype.size(); indexAttributePrototype++)
				{
					for (; indexAttributeEntity <= infoAttributeToSlotToEntity.size(); indexAttributeEntity++)
					{
						if (indexAttributeEntity == infoAttributeToSlotToEntity.size())
						{
							//Прерываем текущий цикл и помечаем, что текущий фрейм не подходит
							indicationNotMatch = true;
							break;
						}
						//Если атрибут прототипа найден среди атрибутов фрейма
						if (infoAttributeToSlotToPrototype[indexAttributePrototype].nameAttribute == infoAttributeToSlotToEntity[indexAttributeEntity].nameAttribute)
						{
							break;
						}
					}
					if (indicationNotMatch)
					{
						break;
					}
					//Если тип данных требуется игнорировать
					if (infoAttributeToSlotToPrototype[indexAttributePrototype].typeDataAttribute == "")
					{
						infoAttributeToSlotToEntity[indexAttributeEntity].typeDataAttribute = "";
					}
					//У синтаксического и семантического поиска имя атрибута и его тип сравниваются. 
					if (infoAttributeToSlotToPrototype[indexAttributePrototype].nameAttribute != infoAttributeToSlotToEntity[indexAttributeEntity].nameAttribute
						|| infoAttributeToSlotToPrototype[indexAttributePrototype].typeDataAttribute != infoAttributeToSlotToEntity[indexAttributeEntity].typeDataAttribute)
					{
						indicationNotMatch = true;
						break;
					}
					//Только для семантического поиска. Сравнение значения атрибута прототипа и фрейма
					if (mode == "_SEMANTIC" && infoAttributeToSlotToPrototype[indexAttributePrototype].valueAttribute != infoAttributeToSlotToEntity[indexAttributeEntity].valueAttribute)
					{
						indicationNotMatch = true;
						break;
					}
				}
			}
			if (indicationNotMatch)//Если индикатор несовпадения сработал, берем следующую сущность
			{
				continue;
			}
			else
			{
				//Если все циклы прошли успешно, значит, фрейм был найден.
				prototypeEntity->ChangeEntity(listEntities[indexEnotity]->GetNameEntity());
				return true;
			}
		}
	}
	return false;
}
//Печать прототипа
void Base::PrintPrototype()
{
	std::cout << "Прототип для поиска" << std::endl;
	if (prototypeEntity->GetAllSlotNames().size() == 0)
	{
		std::cout << "Прототип для поиска не задан!" << std::endl;
	}
	else
	{
		prototypeEntity->PrintEntity();
	}	
}
//Печать фрейма
void Base::PrintEntity(std::string nameEntity)
{
	if (nameEntity == "ФРЕЙМ - ПРОТОТИП ДЛЯ ПОИСКА")
	{
		PrintPrototype();
		return;
	}
	unsigned int index = 0;
	if (SearchIndexEntity(nameEntity, index))
	{
		std::cout << "Фрейм: " << nameEntity << std::endl;
		listEntities[index]->PrintEntity();
	}
}
/* В ДАННОМ МОМЕНТЕ БАЗА ДАННЫХ СТАНОВИТСЯ БАЗОЙ ЗНАНИЙ Т.Е. В ЗАВИСИМОСТИ ОТ ВЫПОЛНЯЕМЫХ ПРОЦЕДУР ПРОИСХОДИТ ИЗМЕНЕНИЕ БАЗЫ ДАННЫХ */
//Добавить процедуру
bool Base::AddProcedure(std::string nameProcedure, std::string nameEntity, std::string nameSlot, std::string nameAttribute, std::string valueAttribute)
{
	unsigned int index = 0;
	if (procederes.find(nameProcedure) == procederes.end() && SearchIndexEntity(nameEntity, index))
	{
		//Получаем указатели на сущность, слот и атрибут
		Entity* prtEntity = listEntities[index];
		Slot* prtSlot = listEntities[index]->GetPointerToSlot(nameSlot);
		Attribute* prtAttribute = listEntities[index]->GetPointerToAttribute(nameSlot, nameAttribute);
		if (prtAttribute != NULL && prtSlot != NULL)
		{
			Procedure* structureNewProcedure = new Procedure;
			structureNewProcedure->entity = prtEntity;
			structureNewProcedure->slot = prtSlot;
			structureNewProcedure->attribute = prtAttribute;
			structureNewProcedure->value = valueAttribute;
			std::pair<std::string, Procedure*> newProcedure;
			newProcedure.first = nameProcedure;
			newProcedure.second = structureNewProcedure;
			procederes.insert(newProcedure);
			return true;
		}
	}
	return false;
}
//Использовать процедуру
bool Base::UsingProcedure(std::string nameProcedure, std::string newValueAttribute, std::string &result)
{
	if (procederes.find(nameProcedure) != procederes.end())
	{
		Attribute* atr = procederes.find(nameProcedure)->second->attribute;
		if (newValueAttribute == "")//Использование "по чтению"
		{
			newValueAttribute = procederes.find(nameProcedure)->second->value;//Используется значение по умолчанию
		}
		std::string typeDataAttribute;
		typeDataAttribute = atr->GetTypeDataAttribute();
		atr->ChangeValueAttribute(newValueAttribute);
		atr->ChangeTypeDataAttribute(typeDataAttribute);
		result = atr->GetNameAttribute();
		result += " = ";
		result+=atr->GetValueAttribute();
		return true;
	}
	return false;
}
//Функции чтения-записи в файл
//Установить имя файла для чтения/записи
void Base::SetReadWhiteFile(std::string newFileName)
{
	fileName = newFileName;
}
//Чтение файла.
Base* FileToBase(std::string nameBase, std::string filename)
{	
	Base* base = new Base(nameBase);
	base->SetReadWhiteFile(filename);
	std::ifstream inputBase(filename);
	std::string line;
	std::string nameEntity = "", nameSlot = "";
	while (std::getline(inputBase, line))
	{
		//Комментарии и пустые строки
		if (line[0] == '/' || line[0] == '\n') continue;
		//Фреймы
		if (line[0] == '#')
		{
			nameEntity = "";
			for (unsigned int i = 1; i < line.size(); i++)
			{
				nameEntity += line[i];
			}
			if (!(base->AddEntity(nameEntity)))
			{
				exit(1);
			}
		}
		//Слоты фрейма
		if (line[0] == '@')
		{
			nameSlot = "";
			for (unsigned int i = 1; i < line.size(); i++)
			{
				nameSlot += line[i];
			}
			if (!(base->AddSlotToEntity(nameEntity, nameSlot)))
			{
				exit(2);
			}
		}
		//Атрибуты слота фрейма
		if (line[0] == '$')
		{
			std::string nameAttribute = "", valueAttribute = "", typeDataAttribute = "";
			unsigned int i = 1;
			for (; i < line.size(); i++)
			{
				if (line[i] == '=')
				{
					i++;
					break;
				}
				nameAttribute += line[i];
			}
			for (; i < line.size(); i++)
			{
				if (line[i] == '|')
				{
					i++;
					break;
				}
				valueAttribute += line[i];
			}
			for (; i < line.size(); i++)
			{
				typeDataAttribute += line[i];
			}
			if (nameAttribute.size() == 0 || typeDataAttribute.size() == 0)
			{
				exit(3);
			}
			if (!(base->AddAttributeToSlotToEntity(nameEntity, nameSlot, nameAttribute, valueAttribute, typeDataAttribute)))
			{
				exit(3);
			}
		}
		//Связи между атрибутами слотов фреймов и другими фреймами
		if (line[0] == '>')
		{
			nameEntity = "";
			nameSlot = "";
			std::string nameAttribute = "", linkEntity = "";
			unsigned int i = 1;
			for (; i < line.size(); i++)
			{
				if (line[i] == '|')
				{
					i++;
					break;
				}
				nameEntity += line[i];
			}
			for (; i < line.size(); i++)
			{
				if (line[i] == '|')
				{
					i++;
					break;
				}
				nameSlot += line[i];
			}
			for (; i < line.size(); i++)
			{
				if (line[i] == '|')
				{
					i++;
					break;
				}
				nameAttribute += line[i];
			}
			for (; i < line.size(); i++)
			{
				linkEntity += line[i];
			}
			if (!(base->AddLinkEntityAttributeToAnotherEntity(nameEntity, nameSlot, nameAttribute, linkEntity)))
			{
				exit(5);
			}
		}
		//Процедуры атрибутов фреймов
		if (line[0] == '!')
		{
			nameEntity = "";
			nameSlot = "";
			std::string nameAttribute = "", nameProcedure = "", valueProcedure = "";
			unsigned int i = 1;
			for (; i < line.size(); i++)
			{
				if (line[i] == '|')
				{
					i++;
					break;
				}
				nameEntity += line[i];
			}
			for (; i < line.size(); i++)
			{
				if (line[i] == '|')
				{
					i++;
					break;
				}
				nameSlot += line[i];
			}
			for (; i < line.size(); i++)
			{
				if (line[i] == '|')
				{
					i++;
					break;
				}
				nameAttribute += line[i];
			}
			for (; i < line.size(); i++)
			{
				if (line[i] == '|')
				{
					i++;
					break;
				}
				nameProcedure += line[i];
			}
			for (; i < line.size(); i++)
			{
				valueProcedure += line[i];
			}
			if (!(base->AddProcedure(nameProcedure, nameEntity, nameSlot, nameAttribute, valueProcedure)))
			{
				exit(6);
			}
		}
	}
	inputBase.close();
	return base;
}
//Запись фреймовой модели в файл
void Base::BaseToFile()
{
	std::ofstream outputBase;
	outputBase.open(fileName);
	if (!outputBase.is_open()) // если файл не был открыт
	{
		std::cout << "Файл не может быть открыт или создан" << std::endl;
		return;
	}
	//Запись фреймов, слотов фреймов и их список атрибутов
	for (unsigned int indexEntity = 0; indexEntity < listEntities.size(); indexEntity++)
	{
		outputBase << "#" << listEntities[indexEntity]->GetNameEntity() << std::endl;
		std::vector<std::string> allSlotNames = listEntities[indexEntity]->GetAllSlotNames();
		for (unsigned int indexSlot = 0; indexSlot < allSlotNames.size(); indexSlot++)
		{
			outputBase << "@" << allSlotNames[indexSlot] << std::endl;
			std::vector<informationAttribute> allAttribute = listEntities[indexEntity]->GetAllSlotAttributeInformation(allSlotNames[indexSlot]);
			for (unsigned int indexAttribute = 0; indexAttribute < allAttribute.size(); indexAttribute++)
			{
				outputBase << "$" << allAttribute[indexAttribute].nameAttribute << "=" << allAttribute[indexAttribute].valueAttribute << "|" << allAttribute[indexAttribute].typeDataAttribute << std::endl;
			}
		}		
	}
	//Запись связей атрибутов слотов фреймов с другими фреймами
	for (unsigned int indexEntity = 0; indexEntity < listEntities.size(); indexEntity++)
	{
		std::string nameEntity = listEntities[indexEntity]->GetNameEntity(), nameSlot, nameAttribute, linkEntity;
		std::vector<std::string> allSlotNames = listEntities[indexEntity]->GetAllSlotNames();
		for (unsigned int indexSlot = 0; indexSlot < allSlotNames.size(); indexSlot++)
		{
			nameSlot = allSlotNames[indexSlot];
			std::vector<informationAttribute> allAttribute = listEntities[indexEntity]->GetAllSlotAttributeInformation(allSlotNames[indexSlot]);
			for (unsigned int indexAttribute = 0; indexAttribute < allAttribute.size(); indexAttribute++)
			{
				nameAttribute = allAttribute[indexAttribute].nameAttribute;
				if (allAttribute[indexAttribute].linkEntity != "Не имеет")
				{
					outputBase << ">" << nameEntity << "|" << nameSlot << "|" << nameAttribute << "|" << allAttribute[indexAttribute].linkEntity << std::endl;
				}				
			}
		}
	}
	//Запись процедур атрибутов слотов фреймов
	for (std::map<std::string, Procedure*>::iterator it = procederes.begin(); it != procederes.end(); it++)
	{
		outputBase << "!" << it->second->entity->GetNameEntity() << "|" << it->second->slot->GetNameSlot() << "|" << it->second->attribute->GetNameAttribute() << "|" << it->first << "|" << it->second->value << std::endl;
	}
	outputBase.close();
}