#include "interface.h"
/* ��������� ��������� */
//�������� �� ���� �����
unsigned int isDigit(std::string number)
{
	for (unsigned i = 0; i < number.size(); i++)
	{
		if (!(number[i] - '0' >= 0 && number[i] - '0' <= 9))
		{
			return 0;
		}
	}
	return stoi(number);
}
//������ ���� � ��������� ������� ����
inline  unsigned int printMenu(unsigned int& key, std::vector<std::string>& menu)
{
	std::string keyStr;
	std::cout << "-----------------------------------------" << std::endl;
	for (unsigned int i = 0; i < menu.size(); i++)
	{
		std::cout << i + 1 << ") " << menu[i] << std::endl;
	}
	std::cout << "-----------------------------------------" << std::endl;
	std::cout << "��������� ����� ����: ";
	std::cin >> keyStr;
	key = isDigit(keyStr);
	//�������� ����������� ����� ������ ����
	while (!(key > 0 && key <= menu.size()))
	{
		std::cout << "�������� ���� ������ ����. ��������� ����" << std::endl;
		std::cout << "��������� ����� ����: ";
		std::cin >> keyStr;
		key = isDigit(keyStr);
	}
	return key;
}
//����������� ���������� ���������
void closeProgramm(Base* base)
{
	base->BaseToFile();
	exit(0);
}
//���� ���������. ��������� ���� � �������� ���������, ��������, ��������� � �������� �� ������, � ����� �������� ���������
void AttributeMenu(Base* base, std::string nameEntity, std::string nameSlot, std::string nameAttribute)
{
	unsigned int key = 0;
	std::string startLineFrame = "<<<<<<<<<<<<<<<<<";
	std::string endLineFrame = ">>>>>>>>>>>>>>>>>";
	std::string startLineSlot = "+++++++++++++++++";
	std::string endLineSlot = "+++++++++++++++++";
	std::string startLineAttribute = "-----------------";
	std::string endLineAttribute = "-----------------";
	informationAttribute infoAtr;
	infoAtr = base->GetInformationAttribute(nameEntity, nameSlot, nameAttribute);
	system("cls");
	std::cout << startLineFrame << nameEntity << endLineFrame << std::endl;
	std::cout << startLineSlot << nameSlot << endLineSlot << std::endl;
	std::cout << startLineAttribute << nameAttribute << endLineAttribute << std::endl << std::endl;
	std::vector<std::string> menu;
	//���� ������� ����� ������������� ����� � ������ �������
	std::cout << "-----------------------------------------" << std::endl;
	//���������� �� ��������
	std::cout << "���������� �� ��������." << std::endl;	
	
	if (nameEntity == "����� - �������� ��� ������")
	{
		std::cout << infoAtr.nameAttribute << " = " << infoAtr.valueAttribute << " [" << infoAtr.typeDataAttribute << "]" << std::endl;
		menu.push_back("�������� ��� ��������");
		menu.push_back("�������� �������� ��������");
		menu.push_back("������� �������� ��������");
	}
	else
	{
		if (infoAtr.typeDataAttribute == "frame")
		{
			//���������� �� ��������
			std::cout << infoAtr.nameAttribute << " -> " << infoAtr.linkEntity << std::endl;
			menu.push_back("�������� �����");
			menu.push_back("������� �����");
			menu.push_back("�������� ��� ��������");
		}
		else
		{	
			std::cout << infoAtr.nameAttribute << " = " << infoAtr.valueAttribute << " [" << infoAtr.typeDataAttribute << "]" << std::endl;
			menu.push_back("�������� �����");
			menu.push_back("�������� ��� ��������");
			menu.push_back("�������� �������� ��������"); //� ���� ������ ����� ����������� �.�. ������� ��������� ������������� ��������
			menu.push_back("������� �������� ��������");
		}
	}	
	menu.push_back("������� �������");
	menu.push_back("�����");
	menu.push_back("�����");
	printMenu(key, menu);
	if (menu[key - 1] == "�����")
	{
		closeProgramm(base);
		return;
	}
	if (menu[key - 1] == "�����")
	{
		SlotMenu(base, nameEntity, nameSlot);
		return;
	}
	if (menu[key - 1] == "�������� ��� ��������")
	{
		std::cout << "-----------------------------------------" << std::endl;
		std::string newNameAttribute;
		std::cout << "������� ����� ��� ��������: ";
		std::cin >> newNameAttribute;
		if (base->ChangeNameAttributeToSlotToEntity(nameEntity, nameSlot, nameAttribute, newNameAttribute))
		{
			std::cout << "�������� ��������� ����� ��������!" << std::endl;
			nameAttribute = newNameAttribute;
			system("pause");
		}
		else
		{
			std::cout << "��������� ����� �������� �� �������!" << std::endl;
			system("pause");
		}
		AttributeMenu(base, nameEntity, nameSlot, nameAttribute);
		return;
	}
	if (menu[key - 1] == "�������� �������� ��������")
	{
		std::cout << "-----------------------------------------" << std::endl;
		std::string newValueAttribute, newTypeDataAttribute;
		std::cout << "������� ����� �������� ��������: ";
		std::cin >> newValueAttribute;
		std::cout << "������� ����� ��� ������ ��������: ";
		std::cin >> newTypeDataAttribute;
		if (newValueAttribute == "-")
		{
			newValueAttribute = "";
		}
		if (newTypeDataAttribute == "-")
		{
			if (nameEntity == "����� - �������� ��� ������")
			{
				newTypeDataAttribute = "";
			}
			else
			{
				newTypeDataAttribute = "null";
			}
			
		}
		if (base->ChangeValueAndTypedataAttributeToSlotToEntity(nameEntity, nameSlot, nameAttribute, newValueAttribute, newTypeDataAttribute))
		{
			std::cout << "�������� ��������� �������� ��������!" << std::endl;
			system("pause");
		}
		else
		{
			std::cout << "��������� �������� �������� �� �������!" << std::endl;
			system("pause");
		}
		AttributeMenu(base, nameEntity, nameSlot, nameAttribute);
		return;
	}
	if (menu[key - 1] == "������� �������")
	{
		if (base->DeleteAttributeToSlotToEntity(nameEntity, nameSlot, nameAttribute))
		{
			std::cout << "�������� �������� ��������!" << std::endl;
			system("pause");
			SlotMenu(base, nameEntity, nameSlot);
			return;
		}
		else
		{
			std::cout << "�������� �������� �� �������!" << std::endl;
			system("pause");
		}
		AttributeMenu(base, nameEntity, nameSlot, nameAttribute);
		return;
	}
	if (menu[key - 1] == "������� �������� ��������")
	{
		//�� ����, �������� �������� �������� �� "" � ������ ��� ��� ������ "null"
		if (base->ChangeValueAndTypedataAttributeToSlotToEntity(nameEntity, nameSlot, nameAttribute, "", "null"))
		{
			std::cout << "�������� �������� �������� ��������!" << std::endl;
			system("pause");
		}
		else
		{
			std::cout << "�������� �������� �������� �� �������!" << std::endl;
			system("pause");
		}
		AttributeMenu(base, nameEntity, nameSlot, nameAttribute);
		return;
	}
	if (menu[key - 1] == "������� �����")
	{
		if (base->DeleteLinkEntityAttributeToAnotherEntity(nameEntity, nameSlot, nameAttribute))
		{
			std::cout << "�������� �������� ����� ��������!" << std::endl;
			system("pause");
		}
		else
		{
			std::cout << "�������� ����� �������� �� �������!" << std::endl;
			system("pause");
		}
		AttributeMenu(base, nameEntity, nameSlot, nameAttribute);
		return;
	}
	if (menu[key - 1] == "�������� �����")
	{
		//�������� �� ��������-�������� �����. ������ ���������� � ������ ������ �� ���������
		std::cout << "-----------------------------------------" << std::endl;
		std::cout << "��������, � ����� ������� ���������� ���������� ����� ��� '������'" << std::endl;
		std::vector<std::string> createLinkToEntity = base->GetAllEntities();//�������� ��� ��������� ������
		for (unsigned int i = 0; i < createLinkToEntity.size(); i++)
		{
			if (createLinkToEntity[i] == nameEntity) //���� �� ������������� ����� � ����� �����
			{
				createLinkToEntity.erase(createLinkToEntity.begin() + i);
			}
			if (createLinkToEntity[i] == infoAtr.linkEntity) //���� �� ��������� ���� �����
			{
				createLinkToEntity.erase(createLinkToEntity.begin() + i);
			}
		}
		createLinkToEntity.push_back("������");
		printMenu(key, createLinkToEntity);
		if (createLinkToEntity[key - 1] != "������")
		{
			if (base->DeleteLinkEntityAttributeToAnotherEntity(nameEntity, nameSlot, nameAttribute))
			{
				if (base->AddLinkEntityAttributeToAnotherEntity(nameEntity, nameSlot, nameAttribute, createLinkToEntity[key - 1]))
				{
					std::cout << "�������� ��������� �����!" << std::endl;
					system("pause");
				}							
			}
			else
			{
				std::cout << "��������� ����� �� �������!" << std::endl;
				system("pause");
			}
			AttributeMenu(base, nameEntity, nameSlot, nameAttribute);
			return;
		}
		else
		{
			AttributeMenu(base, nameEntity, nameSlot, nameAttribute);
			return;
		}
	}
	if (menu[key - 1] == "�������� �����")
	{
		//�������� �� ��������-�������� �����. ������ ���������� � ������ ������ �� ���������
		std::cout << "-----------------------------------------" << std::endl;
		std::cout << "��������, � ����� ������� ���������� ���������� ����� ��� '������'" << std::endl;
		std::vector<std::string> createLinkToEntity = base->GetAllEntities();//�������� ��� ��������� ������
		for (unsigned int i = 0; i < createLinkToEntity.size(); i++)
		{
			if (createLinkToEntity[i] == nameEntity) //���� �� ������������� ����� � ����� �����
			{
				createLinkToEntity.erase(createLinkToEntity.begin() + i);
			}
			if (createLinkToEntity[i] == infoAtr.linkEntity) //���� �� ��������� ���� �����
			{
				createLinkToEntity.erase(createLinkToEntity.begin() + i);
			}
		}
		createLinkToEntity.push_back("������");
		printMenu(key, createLinkToEntity);
		if (createLinkToEntity[key - 1] != "������")
		{
			if (base->AddLinkEntityAttributeToAnotherEntity(nameEntity, nameSlot, nameAttribute, createLinkToEntity[key - 1]))
			{
				std::cout << "�������� �������� �����!" << std::endl;
				system("pause");
			}
			else
			{
				std::cout << "C������� ����� �� �������!" << std::endl;
				system("pause");
			}
			AttributeMenu(base, nameEntity, nameSlot, nameAttribute);
			return;
		}
		else
		{
			AttributeMenu(base, nameEntity, nameSlot, nameAttribute);
			return;
		}
	}
}
//���� ����� ������
void SlotMenu(Base* base, std::string nameEntity, std::string nameSlot)
{
	std::string keyStr;
	unsigned int key = 0;
	std::string startLineFrame = "<<<<<<<<<<<<<<<<<";
	std::string endLineFrame = ">>>>>>>>>>>>>>>>>";
	std::string startLineSlot = "+++++++++++++++++";
	std::string endLineSlot = "+++++++++++++++++";

	system("cls");
	std::cout << startLineFrame << nameEntity << endLineFrame << std::endl;
	std::cout << startLineSlot << nameSlot << endLineSlot << std::endl;
	std::cout << std::endl;
	std::vector<std::string> menu = base->GetAllEntitySlotAttributeNames(nameEntity, nameSlot); ;
	menu.insert(menu.begin(), "�������� � ���� ����� �������");
	menu.insert(menu.begin(), "�������� ��� �����");
	menu.push_back("������� ����");
	menu.push_back("�����");
	menu.push_back("�����");
	printMenu(key, menu);
	if (menu[key - 1] == "�����")
	{
		closeProgramm(base);
		return;
	}
	if (menu[key - 1] == "�����")
	{
		EntityMenu(base, nameEntity);
		return;
	}
	if (menu[key - 1] == "�������� ��� �����")
	{
		std::cout << "-----------------------------------------" << std::endl;
		std::string newNameSlot;
		std::vector<std::string> allNameSlotes = base->GetAllEntitySloteName(nameEntity);
		std::cout << "��������� ����� ������ � ������: ";
		for (unsigned int i = 0; i < allNameSlotes.size(); i++)
		{
			std::cout << "|" << allNameSlotes[i] << "| ";
		}
		std::cout << std::endl;
		std::cout << "-----------------------------------------" << std::endl;
		std::cout << "������� ����� ��� ����� ������, �������� �� ���������: ";
		std::cin >> newNameSlot;
		if (base->ChangeNameSlotToEntity(nameEntity, nameSlot, newNameSlot))
		{
			std::cout << "-----------------------------------------" << std::endl;
			std::cout << "�������� ��������� ����� �����! " << std::endl;
			system("pause");
			nameSlot = newNameSlot;
		}
		else
		{
			std::cout << "-----------------------------------------" << std::endl;
			std::cout << "��������� ����� ����� �� �������! " << std::endl;
			system("pause");
		}
		SlotMenu(base, nameEntity, nameSlot);
		return;
	}
	if (menu[key - 1] == "������� ����")
	{
		std::cout << "-----------------------------------------" << std::endl;
		if (base->DeleteSlotToEntity(nameEntity, nameSlot))
		{
			std::cout << "-----------------------------------------" << std::endl;
			std::cout << "��������e �������� �����! " << std::endl;
			system("pause");
			EntityMenu(base, nameEntity);
		}
		else
		{
			std::cout << "-----------------------------------------" << std::endl;
			std::cout << "�������� ����� �� �������! " << std::endl;
			system("pause");
		}
		SlotMenu(base, nameEntity, nameSlot);
		return;
	}
	if (menu[key - 1] == "�������� � ���� ����� �������")
	{
		std::cout << "-----------------------------------------" << std::endl;
		std::string nameNewAttribute, valueNewAttribute, typedataNewAttribute;
		std::cout << "���� ����� �������� ����������! ���� �� ���������\n ���������� �������� �������� � ��� ����, �������'-'." << std::endl;
		std::cout << "-----------------------------------------" << std::endl;
		std::cout << "������� ��� ������ ��������: ";
		std::cin >> nameNewAttribute;
		std::cout << "������� �������� ������ ��������: ";
		std::cin >> valueNewAttribute;
		std::cout << "������� ��� ������ ������ ��������: ";
		std::cin >> typedataNewAttribute;
		if (valueNewAttribute == "-")
		{
			valueNewAttribute = "";
		}
		if (typedataNewAttribute == "-")
		{
			typedataNewAttribute = "";//���� �������� � ��� ������ �� �������, �� �� ��������� ��� ������ "null"
		}
		std::cout << "-----------------------------------------" << std::endl;
		if (base->AddAttributeToSlotToEntity(nameEntity, nameSlot, nameNewAttribute, valueNewAttribute, typedataNewAttribute))
		{
			std::cout << "�������� ���������� ��������!" << std::endl;
			system("pause");
		}
		else
		{
			std::cout << "���������� �������� �� �������!" << std::endl;
			system("pause");
		}
		SlotMenu(base, nameEntity, nameSlot);
		return;
	}
	else //����� ���� ����� ������ ���� ������������� ����� ��������� ����� ������.
	{
		std::string nameAttribute = menu[key - 1];
		AttributeMenu(base, nameEntity, nameSlot, nameAttribute);
		return;
	}
}
//���� ������
void EntityMenu(Base* base, std::string nameEntity)
{
	std::string keyStr;
	unsigned int key = 0;
	std::string startLineFrame = "<<<<<<<<<<<<<<<<<";
	std::string endLineFrame = ">>>>>>>>>>>>>>>>>";

	system("cls");
	std::cout << startLineFrame << nameEntity << endLineFrame << std::endl;
	std::cout << std::endl;
	std::vector<std::string> menu;
	menu = base->GetAllEntitySloteName(nameEntity);
	if (nameEntity != "����� - �������� ��� ������")
	{
		menu.insert(menu.begin(), "���������� ��� ������");
	}	
	menu.insert(menu.begin(), "�������� ����� ����");
	menu.push_back("�������� �����");
	menu.push_back("������� �����");
	menu.push_back("�����");
	menu.push_back("�����");
	printMenu(key, menu);
	if (menu[key - 1] == "�����")
	{
		closeProgramm(base);
		return;
	}
	if (menu[key - 1] == "�����")
	{
		if (nameEntity == "����� - �������� ��� ������")
		{
			SearchMenu(base);
			return;
		}
		else
		{
			MainMenu(base);
			return;
		}		
	}
	if (menu[key - 1] == "�������� �����")
	{
		system("cls");
		std::cout << "��� ������: " << nameEntity << std::endl;
		base->PrintEntity(nameEntity);
		system("pause");
		EntityMenu(base, nameEntity);
	}
	if (menu[key - 1] == "�������� ����� ����")
	{
		std::cout << "-----------------------------------------" << std::endl;
		std::string nameNewSlot;
		std::cout << "������� ��� ������ �����: ";
		std::cin >> nameNewSlot;
		if (base->AddSlotToEntity(nameEntity, nameNewSlot))
		{
			std::cout << "-----------------------------------------" << std::endl;
			std::cout << "�������� ���������� �����! " << std::endl;
			system("pause");
		}
		else
		{
			std::cout << "-----------------------------------------" << std::endl;
			std::cout << "���������� ����� �� �������! " << std::endl;
			system("pause");
		}
		EntityMenu(base, nameEntity);
		return;
	}
	if (menu[key - 1] == "���������� ��� ������")
	{
		std::cout << "-----------------------------------------" << std::endl;
		std::string newNameEntity;
		std::vector<std::string> allNameEntity = base->GetAllEntities();
		std::cout << "��������� ����� ������� � ����: ";
		for (unsigned int i = 0; i < allNameEntity.size(); i++)
		{
			std::cout << "|" << allNameEntity[i] << "| ";
		}
		std::cout << std::endl;
		std::cout << "-----------------------------------------" << std::endl;
		std::cout << "������� ����� ��� ������, �������� �� ���������: ";
		std::cin >> newNameEntity;

		if (base->ChangeNameEntity(nameEntity, newNameEntity))
		{
			std::cout << "-----------------------------------------" << std::endl;
			std::cout << "�������� ��������� ����� ������! " << std::endl;
			nameEntity = newNameEntity;
			system("pause");
		}
		else
		{
			std::cout << "-----------------------------------------" << std::endl;
			std::cout << "��������� ����� ������ �� �������!" << std::endl;
			system("pause");
		}
		EntityMenu(base, nameEntity);
		return;
	}
	if (menu[key - 1] == "������� �����")
	{
		std::cout << "-----------------------------------------" << std::endl;
		if (base->DeleteEntity(nameEntity))
		{
			std::cout << "�������� �������� ������! " << std::endl;
			system("pause");
			if (nameEntity == "����� - �������� ��� ������")
			{
				SearchMenu(base);
				return;
			}
			MainMenu(base);
			return;
		}
		else
		{
			std::cout << "�������� ������ �� �������! " << std::endl;
			system("pause");
		}
	}
	else //����� ���� ����� ������ ���� ������������� ����� ����� ������.
	{
		std::string nameSlot = menu[key - 1];
		SlotMenu(base, nameEntity, nameSlot);
		return;
	}
}
//���� ������
void SearchMenu(Base* base)
{
	std::string keyStr;
	unsigned int key = 0;
	std::string startLineFrame = "<<<<<<<<<<<<<<<<<";
	std::string endLineFrame = ">>>>>>>>>>>>>>>>>";
	system("cls");
	std::cout << startLineFrame << "���� ������" << endLineFrame << std::endl;
	base->PrintPrototype();
	std::vector<std::string> menu;
	menu.push_back("������ �������� ��� ������");
	menu.push_back("�������� �������� ��� ������");
	menu.push_back("����� �� ������� ����������");
	menu.push_back("����� �� ���������");
	menu.push_back("�����");
	menu.push_back("�����");
	printMenu(key, menu);
	if (menu[key - 1] == "�����")
	{
		closeProgramm(base);
		return;
	}
	if (menu[key - 1] == "�����")
	{
		MainMenu(base);
		return;
	}
	if (menu[key - 1] == "������ �������� ��� ������")
	{
		std::string nameEntity = "����� - �������� ��� ������";
		base->AddPrototype();
		EntityMenu(base, nameEntity);
		return;
	}
	if (menu[key - 1] == "�������� �������� ��� ������")
	{
		std::string nameEntity = "����� - �������� ��� ������";
		EntityMenu(base, nameEntity);
		return;
	}
	std::vector<std::string> searchMenu = { "�������������� �����", "������������� �����" };
	if (menu[key - 1] == "����� �� ������� ����������")
	{
		printMenu(key, searchMenu);
		std::string mode;
		if (searchMenu[key - 1] == "�������������� �����")
		{
			mode = "_SINTAX";
		}
		else
		{
			mode = "_SEMANTIC";
		}
		std::cout << "-----------------------------------------" << std::endl;
		if (base->SearchForNothingMore(mode))
		{
			std::cout << "������� ���������� � ������� '" << base->GetNamePrototype() << "'" << std::endl;
		}
		else
		{
			std::cout << "���������� ���!" << std::endl;
		}
		system("pause");
		SearchMenu(base);
		return;
	}
	if (menu[key - 1] == "����� �� ���������")
	{
		printMenu(key, searchMenu);
		std::string mode;
		if (searchMenu[key - 1] == "�������������� �����")
		{
			mode = "_SINTAX";
		}
		else
		{
			mode = "_SEMANTIC";
		}
		std::cout << "-----------------------------------------" << std::endl;
		if (base->SearchForEverythingSuitable(mode))
		{
			std::cout << "������� ���������� � ������� '" << base->GetNamePrototype() << "'" << std::endl;
		}
		else
		{
			std::cout << "���������� ���!" << std::endl;
		}
		system("pause");
		SearchMenu(base);
		return;
	}
}
//���� ��������
void ProcedureMenu(Base* base)
{
	unsigned int key = 0;
	std::string startLineFrame = "<<<<<<<<<<<<<<<<<";
	std::string endLineFrame = ">>>>>>>>>>>>>>>>>";

	system("cls");
	std::cout << startLineFrame << "���� �������� �������" << endLineFrame << std::endl;
	std::vector<std::string> menu = { "������������� ��������", "�����", "�����" };
	printMenu(key, menu);
	if (menu[key - 1] == "�����")
	{
		MainMenu(base);
		return;
	}
	if (menu[key - 1] == "�����")
	{
		closeProgramm(base);
		return;
	}
	if (menu[key - 1] == "������������� ��������")
	{
		std::cout << "-----------------------------------------" << std::endl;
		std::cout << "������������� �������� �� �����������!" << std::endl;
		std::cout << "<������������� �� ������> ���_���������" << std::endl;
		std::cout << "<������������� �� ������> ���_��������� = ���������������_�_����������_��������" << std::endl;
		std::cout << "<��� ���������� �������> ���������" << std::endl;
		std::cout << "-----------------------------------------" << std::endl;
		bool indicationWhite = false;//��������� ��� ������������ ��������� �� ������
		std::string line;
		std::cout << "������� ���������: ";
		std::cin >> line;
		while (line != "���������")
		{		
			std::string nameProcedure, valueProcedure = "";
			for (unsigned int i = 0; i < line.size(); i++)
			{
				if (line[i] == '=')
				{
					indicationWhite = true;
					i++;
				}
				if (!indicationWhite)
				{
					nameProcedure += line[i];
				}
				else
				{
					valueProcedure += line[i];
				}
			}
			std::string result;
			if (nameProcedure.size() != 0 && base->UsingProcedure(nameProcedure, valueProcedure, result))
			{
				std::cout << "��������� ����������: < " << result << " >" << std::endl;
			}
			std::cout << "������� ���������: ";
			std::cin >> line;
			indicationWhite = false;
		}
		system("pause");
		MainMenu(base);
		return;
	}
}
//�������� ����
void MainMenu(Base* base)
{
	unsigned int key = 0;
	std::string startLineFrame = "<<<<<<<<<<<<<<<<<";
	std::string endLineFrame = ">>>>>>>>>>>>>>>>>";

	system("cls");
	std::cout << startLineFrame << "������� ����" << endLineFrame << std::endl;

	std::vector<std::string> menu = base->GetAllEntities();
	menu.insert(menu.begin(), "�������� ����� �����");
	menu.push_back("����� ������ �� �������");
	menu.push_back("��������� �������");
	menu.push_back("�����");
	printMenu(key, menu);
	if (menu[key - 1] == "�����")
	{
		closeProgramm(base);
		return;
	}
	if (menu[key - 1] == "�������� ����� �����")
	{
		std::cout << "-----------------------------------------" << std::endl;
		std::string nameNewEntity;
		std::cout << "������� ��� ������ ������: ";
		std::cin >> nameNewEntity;
		if (base->AddEntity(nameNewEntity))
		{
			std::cout << "�������� �������� ������!" << std::endl;
			system("pause");
		}
		else
		{
			std::cout << "������� ������ �� �������!" << std::endl;
			system("pause");
		}
		MainMenu(base);
		return;
	}
	if (menu[key - 1] == "����� ������ �� �������")
	{		
		SearchMenu(base);
		return;
	}
	if (menu[key - 1] == "��������� �������")
	{
		ProcedureMenu(base);
		return;
	}
	else//������ ������������ �����
	{
		std::string nameEntity = menu[key - 1];
		EntityMenu(base, nameEntity);
		return;
	}
}
//������ ����������
void Interface(std::string nameBase, std::string filename)
{
	Base* base = FileToBase(nameBase, filename);
	MainMenu(base);
}