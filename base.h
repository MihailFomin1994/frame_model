#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
/* ��������� �������� ���������� �� ��������� */
/* ������ ��������������� ������ ��� ��������� �������� ��������� */
struct informationAttribute
{
	std::string nameAttribute;
	std::string valueAttribute;
	std::string typeDataAttribute;
	std::string linkEntity;
};
/* �������� ������ */
class Entity;
class Attribute
{
private:
	std::string nameAttribute;
	std::string valueAtribute;
	std::string typeDataAtribute;
	Entity* linkFrame;
public:
	//������� ������ �������
	Attribute();
	//�����������. ������� ������� �� ����� ����������.
	Attribute(std::string name, std::string text, std::string typeData);
	//��������� �����, ��������, ���� ������ ��������
	//��������� ����� ��������
	void ChangeNameAttribute(std::string newname);
	//��������� �������� ��������
	void ChangeValueAttribute(std::string newvalue);
	//��������� ���� ������ ��������
	void ChangeTypeDataAttribute(std::string newtype);
	//��������� ���������� �� ��������: ���, ��������, ��� ������ ��� ������ ����������, ���������� ��� ���
	//��������� ����� ��������
	std::string GetNameAttribute();
	//��������� �������� ��������
	std::string GetValueAttribute();
	//��������� ���� ������ ��������
	std::string GetTypeDataAttribute();
	//��������� ���� ���������� �� ��������� ����� ������ � ���� ������� ��������
	informationAttribute GetAllAttributeInformation();
	//������������ ������ � ������� ��������
	//��������� ����� ��������. 
	void AddLink(Entity* link);
	//��������� ����� ������, �� ������� ������� ���������. ���� ��� ���, ���������� ������ ������
	std::string GetLinkEntity();
	//�������� ����� � ������ �������
	void DeleteLink();
	//������� ����� � ��������� �������
	void DeleteLinkToEntity(std::string nameEntity);
	//������ �������� ��������
	void printAttribute();
	//���������� 
	~Attribute();
};
/* ����� ������ */
class Slot
{
private:
	std::string nameSlot;
	std::vector<Attribute*> listAttributes;
	//����� ������� �������� � ������� �� ��� �����.
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
	//����������� �� ���������
	Slot();
	//�����������, ����������� �������� �����
	Slot(std::string newnameslot);
	//����������� ������� �����, � ������ ��������� � ��������� ��� ��������
	//��������� ����� �����
	void ChangeNameSlot(std::string newNameSlot);
	//�������� ��� �����
	std::string GetNameSlot();
	//��������, ���������, ��������� � �������� ���������, � ����� �������� ����� �������� �� ������������
	//���������� ��������
	bool AddAttribute(std::string nameAttribute, std::string valueAttribute, std::string typeDataAttribute);
	//��������� ���� ���� ���������. ��������� ������������ � ���������� ������
	void GetAllNamesAttributes(std::vector<std::string>& allNamesAttributes);
	//��������� ��������� ���������� �� ��������
	informationAttribute GetAtributeInformation(std::string nameAttribute);
	//��������� ���� ��������� ����� � ���� ������� �������� ���� ���������� �� ���������
	std::vector<informationAttribute> GetAllSlotAttributeInformation();
	//��������� ���� ���� ������ ���������. ��������� ������������ � ���������� ������
	void GetAllTypeDataAttributes(std::vector<std::string>& allTypeDataAttributes);
	//�������� ��� ������ �������� �� ��� �����. ���� �������� � ����� ������ ���, ���������� ������ ������
	std::string GetTypeDataAttribute(std::string nameAttribute);
	//�������� �������� �������� �� ��� �����. ���� �������� � ����� ������ ���, ���������� ������ ������
	std::string GetValueAttribute(std::string nameAttribute);
	//��������� ����� ������, �� ������� ��������� �������
	std::string GetNameLinkAttribute(std::string nameAttribute);
	//��������� ���� �������� ��������� (��� ����������)
	void GetAllValueAttribetes(std::vector<std::string>& allValueAttributes);
	//��������� ���� ���� ��� ���������, ������� ��������� �� ������ ������
	std::vector<std::string> GetAllLinkAttributes();
	//�������� ����� �������� �� ������������.
	bool UniqueAttribute(std::string nameAttribute);
	//��������� ����� �������� �� ��� �����
	bool ChangeNameAttribute(std::string nameAttribute, std::string newNameAttribute);
	//��������� �������� �������� �� ��� �����
	bool ChangeValueAttribute(std::string nameAttribute, std::string newValueAttribute);
	//��������� ���� ������ ��������
	bool ChangeTypeDataAttribute(std::string nameAttribute, std::string newTypeDataAttribute);
	//�������� ��������
	bool DeleteAttribute(std::string nameAttribute);
	//����������, �������� � �������� ������� ������ ���������
	//���������� ����� �������� � �������
	bool AddLinkAttribute(std::string nameAttribute, Entity* link);
	//�������� ����� �������� � �������
	bool DeleteLinkAttribute(std::string nameAttribute);
	//�������� ���� ������ � ��������� �������
	void DeleteLinkToEntity(std::string nameEntity);
	//������ ����� �� ����� ����������
	void PrintSlot();
	//�������� ��������� �� �������
	Attribute* GetPointerToAttribute(std::string nameAttribute);
	//����������
	~Slot();
};
/* ����� */
class Entity
{
private:
	std::string nameEntity;
	std::vector<Slot*> listSlotes;
	//����� ������� ����� � ������� �� ��� �����. 
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
	//����������� �����������
	Entity();
	//�����������, ����������� �������� ��������
	Entity(std::string name);
	//��������� � ��������� ����� ������
	//�������� ��� ������
	std::string GetNameEntity();
	//�������� ��� ������
	void ChangeEntity(std::string newNameEntity);
	//�������� �� �������
	//�������� �� ������������ ����� ������
	bool UniqueSlot(std::string nameSlot);
	//�������� ����
	bool AddSlot(std::string nameSlot);
	//��������� ���� ���� ��������� ������ ������
	std::vector<std::string> GetAllSlotNames();
	//��������� ���� ���������� ��� ���� ��������� ����� ������
	std::vector<informationAttribute> GetAllSlotAttributeInformation(std::string nameSlot);
	//��������� ���� ���������� �� �������� ����� ������
	informationAttribute GetInformationAttributeSlot(std::string nameSlot, std::string nameAttribute);
	//�������� ��� �����
	bool ChangeNameSlot(std::string nameSlot, std::string newNameSlot);
	//������� ����
	bool DeleteSlot(std::string nameSlot);
	//�������� ���� ��������� ������ ������
	void DeleteAllStots();
	//�������� � ���������� ������
	//�������� � ���� �������
	bool AddAttributeToSlot(std::string nameSlot, std::string nameAttribute, std::string valueAttribute, std::string typeDataAttribute);
	//��������� ���� ���� ��������� ����� ������
	std::vector<std::string>  GetAllSlotAttributeNames(std::string nameSlot);
	//��������� ���� ���������� �������� ����� ������
	informationAttribute GetAtributeInformation(std::string nameSlot, std::string nameAttribute);
	//�������� � ����� ��� ��������
	bool ChangeNameAttributeToSlot(std::string nameSlot, std::string nameAttribute, std::string newNameAttribute);
	//�������� � ����� �������� ��������
	bool ChangeValueAttributeToSlot(std::string nameSlot, std::string nameAttribute, std::string newValue);
	//�������� � ����� ��� ������ ��������
	bool ChangeTypeDataAttributeToSlot(std::string nameSlot, std::string nameAttribute, std::string newTypeData);
	//������� �� ����� �������
	bool DeleteAttributeToSlot(std::string nameSlot, std::string nameAttribete);
	//�������� � �������� ��������� �����
	//���������� �������� ����� ������ �� �����
	bool AddLinkAtributeToSlot(std::string nameSlot, std::string nameAtribute, Entity* linkEntity);
	//�������� ��� ����� �������, �� ������� ��������� �������� �����
	std::vector<std::string> GetLinkAttributeToSlot(std::string nameSlot);
	//������� ����� �������� �����
	bool DeleteLinkEntitySlotAttribute(std::string nameSlot, std::string nameAttribute);
	//�������� ���� ��������� ������ � ������������ ���������
	void DeleteLinkToEntity(std::string nameEntity);
	//������� ������
	void PrintEntity();	
	//���������������. ������������ ��� ���������� ��������
	//�������� ��������� �� ����
	Slot* GetPointerToSlot(std::string nameSlot);
	//�������� ��������� �� �������
	Attribute* GetPointerToAttribute(std::string nameSlot, std::string nameAttribute);
	//���������� ������
	~Entity();
};
/* ���������� ������� � �������. ������� ����� ������� ����������� */
//��������� ���������
struct Procedure
{
	Entity* entity = NULL;//������������ ������ ��� ���������� � �����
	Slot* slot = NULL;//������������ ������ ��� ���������� � �����
	Attribute* attribute = NULL; //�������, � �������� ���������
	std::string value;
};
/* ��������� ������ */
class Base
{
private:
	std::string nameBase;
	std::vector<Entity*> listEntities;
	Entity* prototypeEntity;//�������� ��� ������
	std::string fileName; //��� ����� ��� ������ � ������
	std::map<std::string, Procedure*> procederes;//���������. �������� �������� �� ��������, �������� - ��������� "Procedure", �������� ��������� �� ������� ��������������� ��������
	//����� ������� ������ � ������� �� ��� �����
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
	//����������� �� ���������
	Base();
	//�����������, ����������� �������� ��������� ������
	Base(std::string name);
	//������ � ��������
	//������������ ����� ������ � ������
	bool UniqueEntity(std::string nameEntity);
	//������� �����
	bool AddEntity(std::string nameEntity);
	//�������� ��� ������
	bool ChangeNameEntity(std::string nameEntity, std::string newNameEntity);
	//������� �����
	bool DeleteEntity(std::string nameEntity);
	//�������� ����� ���� ������� � ����
	std::vector<std::string> GetAllEntities();
	//������ �� ������� �������
	//������� ���� ������
	bool AddSlotToEntity(std::string nameEntity, std::string nameSlot);
	//������� ���� ������
	bool DeleteSlotToEntity(std::string nameEntity, std::string nameSlot);
	//�������� ��� ����� ������
	bool ChangeNameSlotToEntity(std::string nameEntity, std::string nameSlot, std::string newNameSlot);
	//�������� ����� ���� ������ ������
	std::vector<std::string> GetAllEntitySloteName(std::string nameEntity);
	//��������� ���� ���� ��������� ����� ������
	std::vector<std::string> GetAllEntitySlotAttributeNames(std::string nameEntity, std::string nameSlot);
	//������ � ��������
	//�������� � ���� ������ �������
	bool AddAttributeToSlotToEntity(std::string nameEntity, std::string nameSlot, std::string nameAttribute, std::string valueAttribute, std::string typeDataAttribute);
	//������� �� ����� ������ �������
	bool DeleteAttributeToSlotToEntity(std::string nameEntity, std::string nameSlot, std::string nameAttribute);
	//�������� ��� �������� � ����� ������
	bool ChangeNameAttributeToSlotToEntity(std::string nameEntity, std::string nameSlot, std::string nameAttribute, std::string newNameAttribute);
	//�������� �������� �������� � ����� ������
	bool ChangeValueAttributeToSlotToEntity(std::string nameEntity, std::string nameSlot, std::string nameAttribute, std::string newValueAttribute);
	//�������� ��� ���������� �� �������� ����� ������.
	informationAttribute GetInformationAttribute(std::string nameEntity, std::string nameSlot, std::string nameAttribute);
	//��������� �������� � ���� ������ �������� (�� ����������� ��� ������ "frame" �.�. ���������� ������ �� ������ �����)
	bool ChangeValueAndTypedataAttributeToSlotToEntity(std::string nameEntity, std::string nameSlot, std::string nameAttribute, std::string newValueAttribute, std::string typeDataAttribute);
	//�������� ��� ������ ��������
	bool ChangeTypedataAttributeToSlotToEntity(std::string nameEntity, std::string nameSlot, std::string nameAttribute, std::string typeDataAttribute);	
	//������ � �������� ��������� ������ �������
	//���������� ������ �� ����� � �������� ����� ������
	bool AddLinkEntityAttributeToAnotherEntity(std::string nameEntity, std::string nameSlot, std::string nameAttribute, std::string linkEntity);
	//������� ����� �������� ����� ������ � ������ �������
	bool DeleteLinkEntityAttributeToAnotherEntity(std::string nameEntity, std::string nameSlot, std::string nameAttribute);
	//������ � ���������� ��� ������
	//�������� ��������
	void AddPrototype();
	//�������� ��� ���������
	std::string GetNamePrototype();
	//����� ������ �������
	bool SearchForNothingMore(std::string mode);
	//����� ����� �����������
	bool SearchForEverythingSuitable(std::string mode);
	//������ ���������
	void PrintPrototype();
	//������ ������
	void PrintEntity(std::string nameEntity);
	//�������� ���������
	bool AddProcedure(std::string nameProcedure, std::string nameEntity, std::string nameSlot, std::string nameAttribute, std::string valueAttribute);
	//������������ ���������
	bool UsingProcedure(std::string nameProcedure, std::string newValueAttribute, std::string& result);
	//������� ������-������ � ����
	//���������� ��� ����� ��� ������/������
	void SetReadWhiteFile(std::string newFileName);
	//������ ��������� ������ � ����
	void BaseToFile();
};
//������ �����.
Base* FileToBase(std::string nameBase, std::string filename);