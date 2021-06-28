#include "base.h"
/* �������� ����� ������ */
//������� ������ �������
Attribute::Attribute()
{
	nameAttribute = "";
	valueAtribute = "";
	typeDataAtribute = "";
	linkFrame = NULL;
}
//�����������. ������� ������� �� ����� ����������.
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
//��������� ����� ��������. 
void Attribute::AddLink(Entity* link)
{
	valueAtribute = ""; //���������� �������� �������� ��������
	typeDataAtribute = "frame"; //����������� ��� �������� ������
	linkFrame = link; //��������� ������ �� �����
}
//��������� ����� ��������
std::string Attribute::GetNameAttribute()
{
	return nameAttribute;
}
//��������� �������� ��������
std::string Attribute::GetValueAttribute()
{
	return valueAtribute;
}
//��������� ���� ������ ��������
std::string Attribute::GetTypeDataAttribute()
{
	return typeDataAtribute;
}
//��������� ����� ������, �� ������� ������� ���������. ���� ��� ���, ���������� ������ ������
std::string Attribute::GetLinkEntity()
{
	if (linkFrame == NULL)
	{
		return "";
	}
	return linkFrame->GetNameEntity();
}
//��������� ����� ��������
void Attribute::ChangeNameAttribute(std::string newname)
{
	nameAttribute = newname;
}
//��������� �������� ��������
void Attribute::ChangeValueAttribute(std::string newvalue)
{
	valueAtribute = newvalue;
	typeDataAtribute = "text";
	linkFrame = NULL; //�������� ������ ������������
}
//��������� ���� ������ ��������
void Attribute::ChangeTypeDataAttribute(std::string newtype)
{
	typeDataAtribute = newtype;
}
//��������� ���� ���������� �� �������� � ���� ��������� "informationAttribute"
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
		info.linkEntity = "�� �����";
	}
	return info;
}
//�������� ����� � ������ �������
void Attribute::DeleteLink()
{
	typeDataAtribute = "null";
	linkFrame = NULL;
}
//������� ����� � ��������� �������
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
//������ �������� ��������
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
//���������� 
Attribute::~Attribute() {};

/* ����� ������ */
//����������� �� ���������
Slot::Slot()
{
	nameSlot = "";
}
//�����������, ����������� �������� �����
Slot::Slot(std::string newnameslot)
{
	nameSlot = newnameslot;
}

//����������� ������� �����, � ������ ��������� � ��������� ��� ��������
//��������� ����� �����
void Slot::ChangeNameSlot(std::string newNameSlot)
{
	nameSlot = newNameSlot;
}
//�������� ��� �����
std::string Slot::GetNameSlot()
{
	return nameSlot;
}
//��������, ���������, ��������� � �������� ���������, � ����� �������� ����� �������� �� ������������
//���������� ��������
bool Slot::AddAttribute(std::string nameAttribute, std::string valueAttribute, std::string typeDataAttribute)
{
	//��������� ������������ ����� �������� � �����
	if (UniqueAttribute(nameAttribute))
	{
		listAttributes.push_back(new Attribute(nameAttribute, valueAttribute, typeDataAttribute));
		return true;
	}
	return false;
}
//��������� ���� ���� ���������. ��������� ������������ � ���������� ������
void Slot::GetAllNamesAttributes(std::vector<std::string>& allNamesAttributes)
{
	for (unsigned int i = 0; i < listAttributes.size(); i++)
	{
		allNamesAttributes.push_back(listAttributes[i]->GetNameAttribute());
	}
}
//��������� ��������� ���������� �� ��������
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
//��������� ���� ��������� ����� � ���� ������� �������� ���� ���������� �� ���������
std::vector<informationAttribute> Slot::GetAllSlotAttributeInformation()
{
	std::vector<informationAttribute> allSlotAttributeInformation;
	for (unsigned int i = 0; i < listAttributes.size(); i++)
	{
		allSlotAttributeInformation.push_back(listAttributes[i]->GetAllAttributeInformation());
	}
	return allSlotAttributeInformation;
}
//��������� ���� ���� ������ ���������. ��������� ������������ � ���������� ������
void Slot::GetAllTypeDataAttributes(std::vector<std::string>& allTypeDataAttributes)
{
	for (unsigned int i = 0; i < listAttributes.size(); i++)
	{
		allTypeDataAttributes.push_back(listAttributes[i]->GetTypeDataAttribute());
	}
}
//�������� ��� ������ �������� �� ��� �����. ���� �������� � ����� ������ ���, ���������� ������ ������
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
//�������� �������� �������� �� ��� �����. ���� �������� � ����� ������ ���, ���������� ������ ������
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
//��������� ����� ������, �� ������� ��������� �������
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
//��������� ���� �������� ��������� (��� ����������)
void Slot::GetAllValueAttribetes(std::vector<std::string>& allValueAttributes)
{
	for (unsigned int i = 0; i < listAttributes.size(); i++)
	{
		allValueAttributes.push_back(listAttributes[i]->GetValueAttribute());
	}
}
//��������� ���� ���� ��� ���������, ������� ��������� �� ������ ������
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
//�������� ����� �������� �� ������������.
bool Slot::UniqueAttribute(std::string nameAttribute)
{
	unsigned int result = 0;
	return !SearchIndexAttribute(nameAttribute, result);
}
//��������� ����� �������� �� ��� �����
bool Slot::ChangeNameAttribute(std::string nameAttribute, std::string newNameAttribute)
{
	unsigned int posAtribute = 0;
	if (SearchIndexAttribute(nameAttribute, posAtribute))//���� ���������� ������� � ����� ������
	{
		if (UniqueAttribute(newNameAttribute))//� ������ ��� �� ���������� ����� �� ���� ����
		{
			listAttributes[posAtribute]->ChangeNameAttribute(newNameAttribute);
			return true;
		}
	}
	return false;
}
//��������� �������� �������� �� ��� �����
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
//��������� ���� ������ ��������
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
//�������� ��������
bool Slot::DeleteAttribute(std::string nameAttribute)
{
	unsigned int posAtribute = 0;
	if (SearchIndexAttribute(nameAttribute, posAtribute))
	{
		listAttributes[posAtribute]->~Attribute(); //��������� ���������� ��������
		listAttributes.erase(listAttributes.begin() + posAtribute); //������� ��������� �� ��� �������������� ������� �� ��� �������
		return true;
	}
	return false;
}
//����������, �������� � �������� ������� ������ ���������
//���������� ����� �������� � �������
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
//�������� ����� �������� � �������
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
//�������� ���� ������ � ��������� �������
void Slot::DeleteLinkToEntity(std::string nameEntity)
{
	for (unsigned int i = 0; i < listAttributes.size(); i++)
	{
		listAttributes[i]->DeleteLinkToEntity(nameEntity);
	}
}
//������ ����� �� ����� ����������
void Slot::PrintSlot()
{
	for (unsigned int i = 0; i < listAttributes.size(); i++)
	{
		listAttributes[i]->printAttribute();
	}
}
//�������� ��������� �� �������
Attribute* Slot::GetPointerToAttribute(std::string nameAttribute)
{
	unsigned int index = 0;
	if (SearchIndexAttribute(nameAttribute, index))
	{
		return listAttributes[index];
	}
	return NULL;
}
//����������
Slot::~Slot()
{
	//������ ������ ����������� � ������� ���������� �������� � �����
	for (unsigned int i = 0; i < listAttributes.size(); i++)
	{
		listAttributes[i]->~Attribute();
	}
}
/* ������ */
//����������� �����������
Entity::Entity()
{
	nameEntity = "";
}
//�����������, ����������� �������� ��������
Entity::Entity(std::string name)
{
	nameEntity = name;
}

//��������� � ��������� ����� ������
//�������� ��� ������
std::string Entity::GetNameEntity()
{
	return nameEntity;
}
//�������� ��� ������
void Entity::ChangeEntity(std::string newNameEntity)
{
	nameEntity = newNameEntity;
}
//�������� �� �������
//�������� �� ������������ ����� ������
bool Entity::UniqueSlot(std::string nameSlot)
{
	unsigned int index = 0;
	return !SearchIndexSlot(nameSlot, index);
}
//�������� ����
bool Entity::AddSlot(std::string nameSlot)
{
	if (UniqueSlot(nameSlot))
	{
		listSlotes.push_back(new Slot(nameSlot));
		return true;
	}
	return false;
}
//��������� ���� ���� ��������� ������ ������
std::vector<std::string> Entity::GetAllSlotNames()
{
	std::vector<std::string> allSlotNames;
	for (unsigned int i = 0; i < listSlotes.size(); i++)
	{
		allSlotNames.push_back(listSlotes[i]->GetNameSlot());
	}
	return allSlotNames;
}
//��������� ���� ���������� ��� ���� ��������� ����� ������
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
//��������� ���� ���������� �� �������� ����� ������
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
//�������� ��� �����
bool Entity::ChangeNameSlot(std::string nameSlot, std::string newNameSlot)
{
	unsigned int index = 0;
	if (SearchIndexSlot(nameSlot, index))//���� ���� � ����� ������ ����������
	{
		if (UniqueSlot(newNameSlot))//� ����� ��� ����� � ����� ������
		{
			listSlotes[index]->ChangeNameSlot(newNameSlot);
			return true;
		}
	}
	return false;
}
//������� ����
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
//�������� ���� ��������� ������ ������
void Entity::DeleteAllStots()
{
	for (unsigned int i = 0; i < listSlotes.size(); i++)
	{
		listSlotes[i]->~Slot();
		listSlotes.clear();
	}
}
//�������� � ���������� ������
//�������� � ���� �������
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
//��������� ���� ���� ��������� ����� ������
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
//��������� ���� ���������� �������� ����� ������
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
//�������� � ����� ��� ��������
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
//�������� � ����� �������� ��������
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
//�������� � ����� ��� ������ ��������
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
//������� �� ����� �������
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
//�������� � �������� ��������� �����
//���������� �������� ����� ������ �� �����
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
//�������� ��� ����� �������, �� ������� ��������� �������� �����
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
//������� ����� �������� �����
bool Entity::DeleteLinkEntitySlotAttribute(std::string nameSlot, std::string nameAttribute)
{
	unsigned int index = 0;
	if (SearchIndexSlot(nameSlot, index))
	{
		return listSlotes[index]->DeleteLinkAttribute(nameAttribute);
	}
	return false;
}
//�������� ���� ��������� ������ � ������������ ���������
void Entity::DeleteLinkToEntity(std::string nameEntity)
{
	for (unsigned int i = 0; i < listSlotes.size(); i++)
	{
		listSlotes[i]->DeleteLinkToEntity(nameEntity);
	}
}
//������ ������
void Entity::PrintEntity()
{
	for (unsigned int i = 0; i < listSlotes.size(); i++)
	{
		std::cout << "<" << listSlotes[i]->GetNameSlot() <<">"<< std::endl;
		listSlotes[i]->PrintSlot();
	}
}
//�������� ��������� �� ����
Slot* Entity::GetPointerToSlot(std::string nameSlot)
{
	unsigned int index = 0;
	if (SearchIndexSlot(nameSlot, index))
	{
		return listSlotes[index];
	}
	return NULL;
}
//�������� ��������� �� ������� � ��� ����
Attribute* Entity::GetPointerToAttribute(std::string nameSlot, std::string nameAttribute)
{
	unsigned int index = 0;
	if (SearchIndexSlot(nameSlot, index))
	{
		return listSlotes[index]->GetPointerToAttribute(nameAttribute);
	}
	return NULL;
}
//���������� ������
Entity::~Entity()
{
	for (unsigned int i = 0; i < listSlotes.size(); i++)
	{
		listSlotes[i]->~Slot();
	}
}
/* ��������� ������ */
//����������� �� ���������
Base::Base()
{
	nameBase = "";
	fileName = "";
	prototypeEntity = new Entity();
}
//�����������, ����������� �������� ��������� ������
Base::Base(std::string name)
{
	nameBase = name;
	fileName = "";
	prototypeEntity = new Entity();
}

//������ � ��������
//������������ ����� ������ � ������
bool Base::UniqueEntity(std::string nameEntity)
{
	unsigned index = 0;
	if (!(SearchIndexEntity(nameEntity, index)))
	{
		return true;
	}
	return false;
}
//������� �����
bool Base::AddEntity(std::string nameEntity)
{
	if (UniqueEntity(nameEntity))
	{
		listEntities.push_back(new Entity(nameEntity));
		return true;
	}
	return false;
}
//�������� ��� ������
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
//������� �����
bool Base::DeleteEntity(std::string nameEntity)
{
	if (nameEntity == "����� - �������� ��� ������")
	{
		AddPrototype();
		return true;
	}
	else
	{
		unsigned int index = 0;
		if (SearchIndexEntity(nameEntity, index))
		{		
			//����� ��� ��������, ������� �� ���� ���������, � �������� �� �� ������
			for (unsigned int i = 0; i < listEntities.size(); i++)
			{
				listEntities[i]->DeleteLinkToEntity(nameEntity);
			}			
			//����� ����� �������� ��, � ������� ������ ����� �����������, � ������� ��
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
//�������� ����� ���� ������� � ����
std::vector<std::string> Base::GetAllEntities()
{
	std::vector<std::string> allEntities;
	for (unsigned int i = 0; i < listEntities.size(); i++)
	{
		allEntities.push_back(listEntities[i]->GetNameEntity());
	}
	return allEntities;
}

//������ �� ������� �������
//������� ���� ������
bool Base::AddSlotToEntity(std::string nameEntity, std::string nameSlot)
{
	if (nameEntity == "����� - �������� ��� ������")
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
//������� ���� ������
bool Base::DeleteSlotToEntity(std::string nameEntity, std::string nameSlot)
{
	if (nameEntity == "����� - �������� ��� ������")
	{
		return prototypeEntity->DeleteSlot(nameSlot);
	}
	else
	{
		unsigned int index = 0;
		if (SearchIndexEntity(nameEntity, index))
		{
			//����� ����� �������� ��, � ������� ������ ����� � ������ ������ �����������, � ������� ��
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
//�������� ��� ����� ������
bool Base::ChangeNameSlotToEntity(std::string nameEntity, std::string nameSlot, std::string newNameSlot)
{
	if (nameEntity == "����� - �������� ��� ������")
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
//�������� ����� ���� ������ ������
std::vector<std::string> Base::GetAllEntitySloteName(std::string nameEntity)
{
	std::vector<std::string> AllSlotesName;
	if (nameEntity == "����� - �������� ��� ������")
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
//��������� ���� ���� ��������� ����� ������
std::vector<std::string> Base::GetAllEntitySlotAttributeNames(std::string nameEntity, std::string nameSlot)
{
	unsigned int index = 0;
	std::vector<std::string> allSlotAttributeNames;
	if (nameEntity == "����� - �������� ��� ������")
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
//������ � ����������
//�������� � ���� ������ �������
bool Base::AddAttributeToSlotToEntity(std::string nameEntity, std::string nameSlot, std::string nameAttribute, std::string valueAttribute, std::string typeDataAttribute)
{
	if (nameEntity == "����� - �������� ��� ������")
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
//������� �� ����� ������ �������
bool Base::DeleteAttributeToSlotToEntity(std::string nameEntity, std::string nameSlot, std::string nameAttribute)
{
	if (nameEntity == "����� - �������� ��� ������")
	{
		prototypeEntity->DeleteAttributeToSlot(nameSlot, nameAttribute);
	}
	else
	{
		unsigned int index = 0;
		if (SearchIndexEntity(nameEntity, index))
		{
			//����� ����� �������� ��, � ������� ������ ����� � ������ ������ �����������, � ������� ��
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
//�������� ��� �������� � ����� ������
bool Base::ChangeNameAttributeToSlotToEntity(std::string nameEntity, std::string nameSlot, std::string nameAttribute, std::string newNameAttribute)
{
	if (nameEntity == "����� - �������� ��� ������")
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
//�������� �������� �������� � ����� ������
bool Base::ChangeValueAttributeToSlotToEntity(std::string nameEntity, std::string nameSlot, std::string nameAttribute, std::string newValueAttribute)
{
	if (nameEntity == "����� - �������� ��� ������")
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
//�������� ��� ���������� �� �������� ����� ������.
informationAttribute Base::GetInformationAttribute(std::string nameEntity, std::string nameSlot, std::string nameAttribute)
{
	informationAttribute info;
	if (nameEntity == "����� - �������� ��� ������")
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
//��������� �������� � ���� ������ ��������
bool Base::ChangeValueAndTypedataAttributeToSlotToEntity(std::string nameEntity, std::string nameSlot, std::string nameAttribute, std::string newValueAttribute, std::string typeDataAttribute)
{
	if (nameEntity == "����� - �������� ��� ������")
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
//�������� ��� ������ ��������
bool Base::ChangeTypedataAttributeToSlotToEntity(std::string nameEntity, std::string nameSlot, std::string nameAttribute, std::string typeDataAttribute)
{
	if (nameEntity == "����� - �������� ��� ������")
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

//������ � �������� ��������� ������ �������
//���������� ������ �� ����� � �������� ����� ������
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
//������� ����� �������� ����� ������ � ������ �������
bool Base::DeleteLinkEntityAttributeToAnotherEntity(std::string nameEntity, std::string nameSlot, std::string nameAttribute)
{
	unsigned int index = 0;
	if (SearchIndexEntity(nameEntity, index))
	{
		return listEntities[index]->DeleteLinkEntitySlotAttribute(nameSlot, nameAttribute);
	}
	return false;
}
//������ � ���������� ��� ������
//������ ����� �������� (�� ����, ��������� ��� ����� � ���������� ���������)
void Base::AddPrototype()
{
	prototypeEntity->ChangeEntity("");
	prototypeEntity->DeleteAllStots();
}
//�������� ��� ���������
std::string Base::GetNamePrototype()
{
	return prototypeEntity->GetNameEntity();
}
//����� ������ �������
bool Base::SearchForNothingMore(std::string mode)
{
	if (prototypeEntity->GetAllSlotNames().size() == 0)//���� � ��������� ��� �� ������ �����, �� �� �������� �� ���� ������ �����
	{
		return false;
	}
	if (mode != "_SINTAX" && mode != "_SEMANTIC")
	{
		return false;
	}
	//��������� ���� ���� ������ ���������
	for (unsigned int indexEnotity = 0; indexEnotity < listEntities.size(); indexEnotity++)
	{
		if (prototypeEntity->GetAllSlotNames().size() != listEntities[indexEnotity]->GetAllSlotNames().size())//���� ���������� ������ ��������� � �������� ������ �� ���������
		{
			continue;//���������� ��������� �� ������� �����
		}
		else
		{
			//���� ���������� ������ ��������� � �������� ������ ���������, ���������� ��� ���������� ��������� ����� ��������� � ����� �������� ������
			//� ����� ����� ������ ������
			std::vector<std::string> prototypeSlotes = prototypeEntity->GetAllSlotNames();
			std::vector<std::string> entitySlotes = listEntities[indexEnotity]->GetAllSlotNames();
			bool indicationNotMatch = false;//��������� ������������. ���� ��� �����, ���������� ��� ��������� �� ���������
			for (unsigned int indexSlot = 0; indexSlot < prototypeSlotes.size() && !indicationNotMatch; indexSlot++)
			{
				std::string nameSlotPrototype = prototypeSlotes[indexSlot];//��������� ��� �������� ����� ���������
				std::string nameSlotEntity = entitySlotes[indexSlot];//��������� ��� �������� ����� ������
				if (nameSlotPrototype != nameSlotEntity)//���� ����� ������ ������ �� ���������
				{
					//��������� ������� ���� � ��������, ��� ������� ����� �� ��������
					indicationNotMatch = true;
					break;					
				}
				//�������� ��� ���������� �� ��������� ����� ��������� � �������� ������ � ��������� �� � ��������� ������� (��� ��������)
				std::vector<informationAttribute> infoAttributeToSlotToPrototype = prototypeEntity->GetAllSlotAttributeInformation(nameSlotPrototype);
				std::vector<informationAttribute> infoAttributeToSlotToEntity = listEntities[indexEnotity]->GetAllSlotAttributeInformation(nameSlotEntity);
				//���������� ���������� ��������� ����� ��������� � ����� ������
				if (infoAttributeToSlotToPrototype.size() != infoAttributeToSlotToEntity.size())
				{
					//��������� ������� ���� � ��������, ��� ������� ����� �� ��������
					indicationNotMatch = true;
					break;					
				}
				//���������� �������� ����� ��������� � ����� �������� ������
				for (unsigned int indexAttribute = 0; indexAttribute < infoAttributeToSlotToPrototype.size(); indexAttribute++)
				{
					//���� ��� ������ ��������� ������������
					if (infoAttributeToSlotToPrototype[indexAttribute].typeDataAttribute == "")
					{
						infoAttributeToSlotToEntity[indexAttribute].typeDataAttribute = "";
					}
					//� ��������������� � �������������� ������ ��� �������� � ��� ��� ������������. 
					if (infoAttributeToSlotToPrototype[indexAttribute].nameAttribute != infoAttributeToSlotToEntity[indexAttribute].nameAttribute
						|| infoAttributeToSlotToPrototype[indexAttribute].typeDataAttribute != infoAttributeToSlotToEntity[indexAttribute].typeDataAttribute)
					{
						indicationNotMatch = true;
						break;
					}
					//������ ��� �������������� ������. ��������� �������� �������� ��������� � ������
					if (mode == "_SEMANTIC" && infoAttributeToSlotToPrototype[indexAttribute].valueAttribute != infoAttributeToSlotToEntity[indexAttribute].valueAttribute)
					{
						indicationNotMatch = true;
						break;
					}
				}
			}
			if (indicationNotMatch)//���� ��������� ������������ ��������, ����� ��������� ��������
			{
				continue;
			}
			else
			{
				//���� ��� ����� ������ �������, ������, ����� ��� ������.
				prototypeEntity->ChangeEntity(listEntities[indexEnotity]->GetNameEntity());
				return true;
			}
		}
	}
	return false;
}
//����� ����� �����������
bool Base::SearchForEverythingSuitable(std::string mode)
{
	if (prototypeEntity->GetAllSlotNames().size() == 0)//���� � ��������� ��� �� ������ �����, �� �������� ����� �����. ��������� ������ ���������
	{
		prototypeEntity->ChangeEntity(listEntities[0]->GetNameEntity());
		return true;
	}
	if (mode != "_SINTAX" && mode != "_SEMANTIC")
	{
		return false;
	}
	//��������� ���� ���� ������ ���������
	for (unsigned int indexEnotity = 0; indexEnotity < listEntities.size(); indexEnotity++)
	{
		if (prototypeEntity->GetAllSlotNames().size() > listEntities[indexEnotity]->GetAllSlotNames().size())//���� ���������� ������ ��������� ������ ���������� ������ �������� ������
		{
			continue;//���������� ��������� �� ������� �����
		}
		else
		{
			//���� ���������� ������ ��������� ������ ��� ����� ���������� ������ � �������� ������,
			//�� ���������� ��� ���������� ��������� ����� ��������� � ����� �������� ������
			//� ����� ����� ������ ������
			std::vector<std::string> prototypeSlotes = prototypeEntity->GetAllSlotNames();
			std::vector<std::string> entitySlotes = listEntities[indexEnotity]->GetAllSlotNames();
			unsigned int indexSlotEntity = 0;//������ ����� ������
			bool indicationNotMatch = false;//��������� ������������. ���� ��� �����, ���������� ��� ��������� �� ���������
			for (unsigned int indexSlotPrototipe = 0; indexSlotPrototipe < prototypeSlotes.size() && !indicationNotMatch; indexSlotPrototipe++)
			{
				std::string nameSlotPrototype = prototypeSlotes[indexSlotPrototipe];//��������� ��� �������� ����� ���������
				for (; indexSlotEntity <= entitySlotes.size(); indexSlotEntity++)
				{
					if (indexSlotEntity == entitySlotes.size())//��������� ������. ��������, ��� ����� � ������, ��� � ���������, ���
					{
						indicationNotMatch = true;
						break;
					}
					if (entitySlotes[indexSlotEntity] == nameSlotPrototype)//���� ���� ������
					{
						break;
					}
				}
				if (indicationNotMatch)//����� �� �������� �����
				{
					break;
				}
				std::string nameSlotEntity = entitySlotes[indexSlotEntity];//��������� ��� ��������� ����� ������
				//�������� ��� ���������� �� ��������� ����� ��������� � ���������������� ��� ����� ������ � ��������� �� � ��������� ������� (��� ��������)
				std::vector<informationAttribute> infoAttributeToSlotToPrototype = prototypeEntity->GetAllSlotAttributeInformation(nameSlotPrototype);
				std::vector<informationAttribute> infoAttributeToSlotToEntity = listEntities[indexEnotity]->GetAllSlotAttributeInformation(nameSlotEntity);
				//���������� ���������� ��������� ����� ��������� � ����� ������. ���� � ����� ��������� �� ������, ������� � �������� ���
				if (infoAttributeToSlotToPrototype.size() > infoAttributeToSlotToEntity.size())
				{
					//��������� ������� ���� � ��������, ��� ������� ����� �� ��������
					indicationNotMatch = true;					
					break;
				}
				unsigned int indexAttributeEntity = 0;
				//���������� �������� ����� ��������� � ����� �������� ������
				for (unsigned int indexAttributePrototype = 0; indexAttributePrototype < infoAttributeToSlotToPrototype.size(); indexAttributePrototype++)
				{
					for (; indexAttributeEntity <= infoAttributeToSlotToEntity.size(); indexAttributeEntity++)
					{
						if (indexAttributeEntity == infoAttributeToSlotToEntity.size())
						{
							//��������� ������� ���� � ��������, ��� ������� ����� �� ��������
							indicationNotMatch = true;
							break;
						}
						//���� ������� ��������� ������ ����� ��������� ������
						if (infoAttributeToSlotToPrototype[indexAttributePrototype].nameAttribute == infoAttributeToSlotToEntity[indexAttributeEntity].nameAttribute)
						{
							break;
						}
					}
					if (indicationNotMatch)
					{
						break;
					}
					//���� ��� ������ ��������� ������������
					if (infoAttributeToSlotToPrototype[indexAttributePrototype].typeDataAttribute == "")
					{
						infoAttributeToSlotToEntity[indexAttributeEntity].typeDataAttribute = "";
					}
					//� ��������������� � �������������� ������ ��� �������� � ��� ��� ������������. 
					if (infoAttributeToSlotToPrototype[indexAttributePrototype].nameAttribute != infoAttributeToSlotToEntity[indexAttributeEntity].nameAttribute
						|| infoAttributeToSlotToPrototype[indexAttributePrototype].typeDataAttribute != infoAttributeToSlotToEntity[indexAttributeEntity].typeDataAttribute)
					{
						indicationNotMatch = true;
						break;
					}
					//������ ��� �������������� ������. ��������� �������� �������� ��������� � ������
					if (mode == "_SEMANTIC" && infoAttributeToSlotToPrototype[indexAttributePrototype].valueAttribute != infoAttributeToSlotToEntity[indexAttributeEntity].valueAttribute)
					{
						indicationNotMatch = true;
						break;
					}
				}
			}
			if (indicationNotMatch)//���� ��������� ������������ ��������, ����� ��������� ��������
			{
				continue;
			}
			else
			{
				//���� ��� ����� ������ �������, ������, ����� ��� ������.
				prototypeEntity->ChangeEntity(listEntities[indexEnotity]->GetNameEntity());
				return true;
			}
		}
	}
	return false;
}
//������ ���������
void Base::PrintPrototype()
{
	std::cout << "�������� ��� ������" << std::endl;
	if (prototypeEntity->GetAllSlotNames().size() == 0)
	{
		std::cout << "�������� ��� ������ �� �����!" << std::endl;
	}
	else
	{
		prototypeEntity->PrintEntity();
	}	
}
//������ ������
void Base::PrintEntity(std::string nameEntity)
{
	if (nameEntity == "����� - �������� ��� ������")
	{
		PrintPrototype();
		return;
	}
	unsigned int index = 0;
	if (SearchIndexEntity(nameEntity, index))
	{
		std::cout << "�����: " << nameEntity << std::endl;
		listEntities[index]->PrintEntity();
	}
}
/* � ������ ������� ���� ������ ���������� ����� ������ �.�. � ����������� �� ����������� �������� ���������� ��������� ���� ������ */
//�������� ���������
bool Base::AddProcedure(std::string nameProcedure, std::string nameEntity, std::string nameSlot, std::string nameAttribute, std::string valueAttribute)
{
	unsigned int index = 0;
	if (procederes.find(nameProcedure) == procederes.end() && SearchIndexEntity(nameEntity, index))
	{
		//�������� ��������� �� ��������, ���� � �������
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
//������������ ���������
bool Base::UsingProcedure(std::string nameProcedure, std::string newValueAttribute, std::string &result)
{
	if (procederes.find(nameProcedure) != procederes.end())
	{
		Attribute* atr = procederes.find(nameProcedure)->second->attribute;
		if (newValueAttribute == "")//������������� "�� ������"
		{
			newValueAttribute = procederes.find(nameProcedure)->second->value;//������������ �������� �� ���������
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
//������� ������-������ � ����
//���������� ��� ����� ��� ������/������
void Base::SetReadWhiteFile(std::string newFileName)
{
	fileName = newFileName;
}
//������ �����.
Base* FileToBase(std::string nameBase, std::string filename)
{	
	Base* base = new Base(nameBase);
	base->SetReadWhiteFile(filename);
	std::ifstream inputBase(filename);
	std::string line;
	std::string nameEntity = "", nameSlot = "";
	while (std::getline(inputBase, line))
	{
		//����������� � ������ ������
		if (line[0] == '/' || line[0] == '\n') continue;
		//������
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
		//����� ������
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
		//�������� ����� ������
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
		//����� ����� ���������� ������ ������� � ������� ��������
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
		//��������� ��������� �������
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
//������ ��������� ������ � ����
void Base::BaseToFile()
{
	std::ofstream outputBase;
	outputBase.open(fileName);
	if (!outputBase.is_open()) // ���� ���� �� ��� ������
	{
		std::cout << "���� �� ����� ���� ������ ��� ������" << std::endl;
		return;
	}
	//������ �������, ������ ������� � �� ������ ���������
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
	//������ ������ ��������� ������ ������� � ������� ��������
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
				if (allAttribute[indexAttribute].linkEntity != "�� �����")
				{
					outputBase << ">" << nameEntity << "|" << nameSlot << "|" << nameAttribute << "|" << allAttribute[indexAttribute].linkEntity << std::endl;
				}				
			}
		}
	}
	//������ �������� ��������� ������ �������
	for (std::map<std::string, Procedure*>::iterator it = procederes.begin(); it != procederes.end(); it++)
	{
		outputBase << "!" << it->second->entity->GetNameEntity() << "|" << it->second->slot->GetNameSlot() << "|" << it->second->attribute->GetNameAttribute() << "|" << it->first << "|" << it->second->value << std::endl;
	}
	outputBase.close();
}