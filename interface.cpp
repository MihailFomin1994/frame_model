#include "interface.h"
/* ИНТЕРФЕЙС ПРОГРАММЫ */
//Проверка на ввод числа
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
//Печать меню с возвратом индекса меню
inline  unsigned int printMenu(unsigned int& key, std::vector<std::string>& menu)
{
	std::string keyStr;
	std::cout << "-----------------------------------------" << std::endl;
	for (unsigned int i = 0; i < menu.size(); i++)
	{
		std::cout << i + 1 << ") " << menu[i] << std::endl;
	}
	std::cout << "-----------------------------------------" << std::endl;
	std::cout << "Выбранный пункт меню: ";
	std::cin >> keyStr;
	key = isDigit(keyStr);
	//Проверка коректности ввода пункта меню
	while (!(key > 0 && key <= menu.size()))
	{
		std::cout << "Неверный ввод пункта меню. Повторите ввод" << std::endl;
		std::cout << "Выбранный пункт меню: ";
		std::cin >> keyStr;
		key = isDigit(keyStr);
	}
	return key;
}
//Неаварийное завершение программы
void closeProgramm(Base* base)
{
	base->BaseToFile();
	exit(0);
}
//Меню атрибутов. Изменение имен и значений атрибутов, создание, изменение и удаление их связей, а также удаление атрибутов
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
	//Если атрибут имеет установленную связь с другим фреймом
	std::cout << "-----------------------------------------" << std::endl;
	//Информация об атрибуте
	std::cout << "Информация об атрибуте." << std::endl;	
	
	if (nameEntity == "ФРЕЙМ - ПРОТОТИП ДЛЯ ПОИСКА")
	{
		std::cout << infoAtr.nameAttribute << " = " << infoAtr.valueAttribute << " [" << infoAtr.typeDataAttribute << "]" << std::endl;
		menu.push_back("Изменить имя атрибута");
		menu.push_back("Изменить значение атрибута");
		menu.push_back("Удалить значение атрибута");
	}
	else
	{
		if (infoAtr.typeDataAttribute == "frame")
		{
			//Информация об атрибуте
			std::cout << infoAtr.nameAttribute << " -> " << infoAtr.linkEntity << std::endl;
			menu.push_back("Изменить связь");
			menu.push_back("Удалить связь");
			menu.push_back("Изменить имя атрибута");
		}
		else
		{	
			std::cout << infoAtr.nameAttribute << " = " << infoAtr.valueAttribute << " [" << infoAtr.typeDataAttribute << "]" << std::endl;
			menu.push_back("Добавить связь");
			menu.push_back("Изменить имя атрибута");
			menu.push_back("Изменить значение атрибута"); //В этом случае связь разрывается т.е. атрибут принимает фиксированное значение
			menu.push_back("Удалить значение атрибута");
		}
	}	
	menu.push_back("Удалить атрибут");
	menu.push_back("Назад");
	menu.push_back("Выход");
	printMenu(key, menu);
	if (menu[key - 1] == "Выход")
	{
		closeProgramm(base);
		return;
	}
	if (menu[key - 1] == "Назад")
	{
		SlotMenu(base, nameEntity, nameSlot);
		return;
	}
	if (menu[key - 1] == "Изменить имя атрибута")
	{
		std::cout << "-----------------------------------------" << std::endl;
		std::string newNameAttribute;
		std::cout << "Введите новое имя атрибута: ";
		std::cin >> newNameAttribute;
		if (base->ChangeNameAttributeToSlotToEntity(nameEntity, nameSlot, nameAttribute, newNameAttribute))
		{
			std::cout << "Успешное изменение имени атрибута!" << std::endl;
			nameAttribute = newNameAttribute;
			system("pause");
		}
		else
		{
			std::cout << "Изменение имени атрибута не удалось!" << std::endl;
			system("pause");
		}
		AttributeMenu(base, nameEntity, nameSlot, nameAttribute);
		return;
	}
	if (menu[key - 1] == "Изменить значение атрибута")
	{
		std::cout << "-----------------------------------------" << std::endl;
		std::string newValueAttribute, newTypeDataAttribute;
		std::cout << "Введите новое значение атрибута: ";
		std::cin >> newValueAttribute;
		std::cout << "Введите новый тип данных атрибута: ";
		std::cin >> newTypeDataAttribute;
		if (newValueAttribute == "-")
		{
			newValueAttribute = "";
		}
		if (newTypeDataAttribute == "-")
		{
			if (nameEntity == "ФРЕЙМ - ПРОТОТИП ДЛЯ ПОИСКА")
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
			std::cout << "Успешное изменение значения атрибута!" << std::endl;
			system("pause");
		}
		else
		{
			std::cout << "Изменение значения атрибута не удалось!" << std::endl;
			system("pause");
		}
		AttributeMenu(base, nameEntity, nameSlot, nameAttribute);
		return;
	}
	if (menu[key - 1] == "Удалить атрибут")
	{
		if (base->DeleteAttributeToSlotToEntity(nameEntity, nameSlot, nameAttribute))
		{
			std::cout << "Успешное удаление атрибута!" << std::endl;
			system("pause");
			SlotMenu(base, nameEntity, nameSlot);
			return;
		}
		else
		{
			std::cout << "Удаление атрибута не удалось!" << std::endl;
			system("pause");
		}
		AttributeMenu(base, nameEntity, nameSlot, nameAttribute);
		return;
	}
	if (menu[key - 1] == "Удалить значение атрибута")
	{
		//По сути, изменяем значение атрибута на "" и задаем ему тип данных "null"
		if (base->ChangeValueAndTypedataAttributeToSlotToEntity(nameEntity, nameSlot, nameAttribute, "", "null"))
		{
			std::cout << "Успешное удаление значения атрибута!" << std::endl;
			system("pause");
		}
		else
		{
			std::cout << "Удаление значения атрибута не удалось!" << std::endl;
			system("pause");
		}
		AttributeMenu(base, nameEntity, nameSlot, nameAttribute);
		return;
	}
	if (menu[key - 1] == "Удалить связь")
	{
		if (base->DeleteLinkEntityAttributeToAnotherEntity(nameEntity, nameSlot, nameAttribute))
		{
			std::cout << "Успешное удаление связи атрибута!" << std::endl;
			system("pause");
		}
		else
		{
			std::cout << "Удаление связи атрибута не удалось!" << std::endl;
			system("pause");
		}
		AttributeMenu(base, nameEntity, nameSlot, nameAttribute);
		return;
	}
	if (menu[key - 1] == "Изменить связь")
	{
		//Работает от удаление-создание связи. Другой реализации в данном случае не требуется
		std::cout << "-----------------------------------------" << std::endl;
		std::cout << "Выберите, с каким фреймом необходимо установить связь или 'Отмена'" << std::endl;
		std::vector<std::string> createLinkToEntity = base->GetAllEntities();//Получаем все имеющиеся фреймы
		for (unsigned int i = 0; i < createLinkToEntity.size(); i++)
		{
			if (createLinkToEntity[i] == nameEntity) //Чтоб не устанавливать связь с самим собой
			{
				createLinkToEntity.erase(createLinkToEntity.begin() + i);
			}
			if (createLinkToEntity[i] == infoAtr.linkEntity) //Чтоб не повторять туже связь
			{
				createLinkToEntity.erase(createLinkToEntity.begin() + i);
			}
		}
		createLinkToEntity.push_back("Отмена");
		printMenu(key, createLinkToEntity);
		if (createLinkToEntity[key - 1] != "Отмена")
		{
			if (base->DeleteLinkEntityAttributeToAnotherEntity(nameEntity, nameSlot, nameAttribute))
			{
				if (base->AddLinkEntityAttributeToAnotherEntity(nameEntity, nameSlot, nameAttribute, createLinkToEntity[key - 1]))
				{
					std::cout << "Успешное изменение связи!" << std::endl;
					system("pause");
				}							
			}
			else
			{
				std::cout << "Изменение связи не удалось!" << std::endl;
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
	if (menu[key - 1] == "Добавить связь")
	{
		//Работает от удаление-создание связи. Другой реализации в данном случае не требуется
		std::cout << "-----------------------------------------" << std::endl;
		std::cout << "Выберите, с каким фреймом необходимо установить связь или 'Отмена'" << std::endl;
		std::vector<std::string> createLinkToEntity = base->GetAllEntities();//Получаем все имеющиеся фреймы
		for (unsigned int i = 0; i < createLinkToEntity.size(); i++)
		{
			if (createLinkToEntity[i] == nameEntity) //Чтоб не устанавливать связь с самим собой
			{
				createLinkToEntity.erase(createLinkToEntity.begin() + i);
			}
			if (createLinkToEntity[i] == infoAtr.linkEntity) //Чтоб не повторять туже связь
			{
				createLinkToEntity.erase(createLinkToEntity.begin() + i);
			}
		}
		createLinkToEntity.push_back("Отмена");
		printMenu(key, createLinkToEntity);
		if (createLinkToEntity[key - 1] != "Отмена")
		{
			if (base->AddLinkEntityAttributeToAnotherEntity(nameEntity, nameSlot, nameAttribute, createLinkToEntity[key - 1]))
			{
				std::cout << "Успешное создание связи!" << std::endl;
				system("pause");
			}
			else
			{
				std::cout << "Cоздание связи не удалось!" << std::endl;
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
//Меню слота фрейма
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
	menu.insert(menu.begin(), "Добавить в слот новый атрибут");
	menu.insert(menu.begin(), "Изменить имя слота");
	menu.push_back("Удалить слот");
	menu.push_back("Назад");
	menu.push_back("Выход");
	printMenu(key, menu);
	if (menu[key - 1] == "Выход")
	{
		closeProgramm(base);
		return;
	}
	if (menu[key - 1] == "Назад")
	{
		EntityMenu(base, nameEntity);
		return;
	}
	if (menu[key - 1] == "Изменить имя слота")
	{
		std::cout << "-----------------------------------------" << std::endl;
		std::string newNameSlot;
		std::vector<std::string> allNameSlotes = base->GetAllEntitySloteName(nameEntity);
		std::cout << "Имеющиеся имена слотов в фрейме: ";
		for (unsigned int i = 0; i < allNameSlotes.size(); i++)
		{
			std::cout << "|" << allNameSlotes[i] << "| ";
		}
		std::cout << std::endl;
		std::cout << "-----------------------------------------" << std::endl;
		std::cout << "Введите новое имя слота фрейма, отличное от имеющихся: ";
		std::cin >> newNameSlot;
		if (base->ChangeNameSlotToEntity(nameEntity, nameSlot, newNameSlot))
		{
			std::cout << "-----------------------------------------" << std::endl;
			std::cout << "Успешное изменение имени слота! " << std::endl;
			system("pause");
			nameSlot = newNameSlot;
		}
		else
		{
			std::cout << "-----------------------------------------" << std::endl;
			std::cout << "Изменение имени слота не удалось! " << std::endl;
			system("pause");
		}
		SlotMenu(base, nameEntity, nameSlot);
		return;
	}
	if (menu[key - 1] == "Удалить слот")
	{
		std::cout << "-----------------------------------------" << std::endl;
		if (base->DeleteSlotToEntity(nameEntity, nameSlot))
		{
			std::cout << "-----------------------------------------" << std::endl;
			std::cout << "Успешноеe удаление слота! " << std::endl;
			system("pause");
			EntityMenu(base, nameEntity);
		}
		else
		{
			std::cout << "-----------------------------------------" << std::endl;
			std::cout << "Удаление слота не удалось! " << std::endl;
			system("pause");
		}
		SlotMenu(base, nameEntity, nameSlot);
		return;
	}
	if (menu[key - 1] == "Добавить в слот новый атрибут")
	{
		std::cout << "-----------------------------------------" << std::endl;
		std::string nameNewAttribute, valueNewAttribute, typedataNewAttribute;
		std::cout << "Ввод имени атрибута обязателен! Если не требуется\n заполнение значения атрибута и его типа, введите'-'." << std::endl;
		std::cout << "-----------------------------------------" << std::endl;
		std::cout << "Введите имя нового атрибута: ";
		std::cin >> nameNewAttribute;
		std::cout << "Введите значение нового атрибута: ";
		std::cin >> valueNewAttribute;
		std::cout << "Введите тип данных нового атрибута: ";
		std::cin >> typedataNewAttribute;
		if (valueNewAttribute == "-")
		{
			valueNewAttribute = "";
		}
		if (typedataNewAttribute == "-")
		{
			typedataNewAttribute = "";//Если значение и тип данных не указаны, то по умолчанию тип данных "null"
		}
		std::cout << "-----------------------------------------" << std::endl;
		if (base->AddAttributeToSlotToEntity(nameEntity, nameSlot, nameNewAttribute, valueNewAttribute, typedataNewAttribute))
		{
			std::cout << "Успешное добавление атрибута!" << std::endl;
			system("pause");
		}
		else
		{
			std::cout << "Добавление атрибута не удалось!" << std::endl;
			system("pause");
		}
		SlotMenu(base, nameEntity, nameSlot);
		return;
	}
	else //Любой иной выбор пункта меню подрузомевает выбор аргумента слота фрейма.
	{
		std::string nameAttribute = menu[key - 1];
		AttributeMenu(base, nameEntity, nameSlot, nameAttribute);
		return;
	}
}
//Меню фрейма
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
	if (nameEntity != "ФРЕЙМ - ПРОТОТИП ДЛЯ ПОИСКА")
	{
		menu.insert(menu.begin(), "Измененить имя фрейма");
	}	
	menu.insert(menu.begin(), "Добавить новый слот");
	menu.push_back("Показать фрейм");
	menu.push_back("Удалить фрейм");
	menu.push_back("Назад");
	menu.push_back("Выход");
	printMenu(key, menu);
	if (menu[key - 1] == "Выход")
	{
		closeProgramm(base);
		return;
	}
	if (menu[key - 1] == "Назад")
	{
		if (nameEntity == "ФРЕЙМ - ПРОТОТИП ДЛЯ ПОИСКА")
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
	if (menu[key - 1] == "Показать фрейм")
	{
		system("cls");
		std::cout << "Имя фрейма: " << nameEntity << std::endl;
		base->PrintEntity(nameEntity);
		system("pause");
		EntityMenu(base, nameEntity);
	}
	if (menu[key - 1] == "Добавить новый слот")
	{
		std::cout << "-----------------------------------------" << std::endl;
		std::string nameNewSlot;
		std::cout << "Введите имя нового слота: ";
		std::cin >> nameNewSlot;
		if (base->AddSlotToEntity(nameEntity, nameNewSlot))
		{
			std::cout << "-----------------------------------------" << std::endl;
			std::cout << "Успешное добавление слота! " << std::endl;
			system("pause");
		}
		else
		{
			std::cout << "-----------------------------------------" << std::endl;
			std::cout << "Добавление слота не удалось! " << std::endl;
			system("pause");
		}
		EntityMenu(base, nameEntity);
		return;
	}
	if (menu[key - 1] == "Измененить имя фрейма")
	{
		std::cout << "-----------------------------------------" << std::endl;
		std::string newNameEntity;
		std::vector<std::string> allNameEntity = base->GetAllEntities();
		std::cout << "Имеющиеся имена фреймов в базе: ";
		for (unsigned int i = 0; i < allNameEntity.size(); i++)
		{
			std::cout << "|" << allNameEntity[i] << "| ";
		}
		std::cout << std::endl;
		std::cout << "-----------------------------------------" << std::endl;
		std::cout << "Введите новое имя фрейма, отличное от имеющихся: ";
		std::cin >> newNameEntity;

		if (base->ChangeNameEntity(nameEntity, newNameEntity))
		{
			std::cout << "-----------------------------------------" << std::endl;
			std::cout << "Успешное изменение имени фрейма! " << std::endl;
			nameEntity = newNameEntity;
			system("pause");
		}
		else
		{
			std::cout << "-----------------------------------------" << std::endl;
			std::cout << "Изменение имени фрейма не удалось!" << std::endl;
			system("pause");
		}
		EntityMenu(base, nameEntity);
		return;
	}
	if (menu[key - 1] == "Удалить фрейм")
	{
		std::cout << "-----------------------------------------" << std::endl;
		if (base->DeleteEntity(nameEntity))
		{
			std::cout << "Успешное удаление фрейма! " << std::endl;
			system("pause");
			if (nameEntity == "ФРЕЙМ - ПРОТОТИП ДЛЯ ПОИСКА")
			{
				SearchMenu(base);
				return;
			}
			MainMenu(base);
			return;
		}
		else
		{
			std::cout << "Удаление фрейма не удалось! " << std::endl;
			system("pause");
		}
	}
	else //Любой иной выбор пункта меню подрузомевает выбор слота фрейма.
	{
		std::string nameSlot = menu[key - 1];
		SlotMenu(base, nameEntity, nameSlot);
		return;
	}
}
//Меню поиска
void SearchMenu(Base* base)
{
	std::string keyStr;
	unsigned int key = 0;
	std::string startLineFrame = "<<<<<<<<<<<<<<<<<";
	std::string endLineFrame = ">>>>>>>>>>>>>>>>>";
	system("cls");
	std::cout << startLineFrame << "МЕНЮ ПОИСКА" << endLineFrame << std::endl;
	base->PrintPrototype();
	std::vector<std::string> menu;
	menu.push_back("Задать прототип для поиска");
	menu.push_back("Изменить прототип для поиска");
	menu.push_back("Поиск по точному совпадению");
	menu.push_back("Поиск по включению");
	menu.push_back("Назад");
	menu.push_back("Выход");
	printMenu(key, menu);
	if (menu[key - 1] == "Выход")
	{
		closeProgramm(base);
		return;
	}
	if (menu[key - 1] == "Назад")
	{
		MainMenu(base);
		return;
	}
	if (menu[key - 1] == "Задать прототип для поиска")
	{
		std::string nameEntity = "ФРЕЙМ - ПРОТОТИП ДЛЯ ПОИСКА";
		base->AddPrototype();
		EntityMenu(base, nameEntity);
		return;
	}
	if (menu[key - 1] == "Изменить прототип для поиска")
	{
		std::string nameEntity = "ФРЕЙМ - ПРОТОТИП ДЛЯ ПОИСКА";
		EntityMenu(base, nameEntity);
		return;
	}
	std::vector<std::string> searchMenu = { "Синтаксический поиск", "Семантический поиск" };
	if (menu[key - 1] == "Поиск по точному совпадению")
	{
		printMenu(key, searchMenu);
		std::string mode;
		if (searchMenu[key - 1] == "Синтаксический поиск")
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
			std::cout << "Найдено совпадение с фреймом '" << base->GetNamePrototype() << "'" << std::endl;
		}
		else
		{
			std::cout << "Совпадения нет!" << std::endl;
		}
		system("pause");
		SearchMenu(base);
		return;
	}
	if (menu[key - 1] == "Поиск по включению")
	{
		printMenu(key, searchMenu);
		std::string mode;
		if (searchMenu[key - 1] == "Синтаксический поиск")
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
			std::cout << "Найдено совпадение с фреймом '" << base->GetNamePrototype() << "'" << std::endl;
		}
		else
		{
			std::cout << "Совпадения нет!" << std::endl;
		}
		system("pause");
		SearchMenu(base);
		return;
	}
}
//Меню процедур
void ProcedureMenu(Base* base)
{
	unsigned int key = 0;
	std::string startLineFrame = "<<<<<<<<<<<<<<<<<";
	std::string endLineFrame = ">>>>>>>>>>>>>>>>>";

	system("cls");
	std::cout << startLineFrame << "МЕНЮ ПРОЦЕДУР ФРЕЙМОВ" << endLineFrame << std::endl;
	std::vector<std::string> menu = { "Использование процедур", "Назад", "Выход" };
	printMenu(key, menu);
	if (menu[key - 1] == "Назад")
	{
		MainMenu(base);
		return;
	}
	if (menu[key - 1] == "Выход")
	{
		closeProgramm(base);
		return;
	}
	if (menu[key - 1] == "Использование процедур")
	{
		std::cout << "-----------------------------------------" << std::endl;
		std::cout << "Использование пробелов не допускается!" << std::endl;
		std::cout << "<Использование по чтению> имя_процедуры" << std::endl;
		std::cout << "<Использование по записи> имя_процедуры = устанавливаемое_в_результате_значение" << std::endl;
		std::cout << "<Для завершения введите> Завершить" << std::endl;
		std::cout << "-----------------------------------------" << std::endl;
		bool indicationWhite = false;//Индикатор что используется процедура по записи
		std::string line;
		std::cout << "Введите процедуру: ";
		std::cin >> line;
		while (line != "Завершить")
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
				std::cout << "Результат выполнения: < " << result << " >" << std::endl;
			}
			std::cout << "Введите процедуру: ";
			std::cin >> line;
			indicationWhite = false;
		}
		system("pause");
		MainMenu(base);
		return;
	}
}
//Основное меню
void MainMenu(Base* base)
{
	unsigned int key = 0;
	std::string startLineFrame = "<<<<<<<<<<<<<<<<<";
	std::string endLineFrame = ">>>>>>>>>>>>>>>>>";

	system("cls");
	std::cout << startLineFrame << "ГЛАВНОЕ МЕНЮ" << endLineFrame << std::endl;

	std::vector<std::string> menu = base->GetAllEntities();
	menu.insert(menu.begin(), "Добавить новый фрейм");
	menu.push_back("Поиск фрейма по образцу");
	menu.push_back("Процедуры фреймов");
	menu.push_back("Выход");
	printMenu(key, menu);
	if (menu[key - 1] == "Выход")
	{
		closeProgramm(base);
		return;
	}
	if (menu[key - 1] == "Добавить новый фрейм")
	{
		std::cout << "-----------------------------------------" << std::endl;
		std::string nameNewEntity;
		std::cout << "Введите имя нового фрейма: ";
		std::cin >> nameNewEntity;
		if (base->AddEntity(nameNewEntity))
		{
			std::cout << "Успешное создание фрейма!" << std::endl;
			system("pause");
		}
		else
		{
			std::cout << "Сздание фрейма не удалось!" << std::endl;
			system("pause");
		}
		MainMenu(base);
		return;
	}
	if (menu[key - 1] == "Поиск фрейма по образцу")
	{		
		SearchMenu(base);
		return;
	}
	if (menu[key - 1] == "Процедуры фреймов")
	{
		ProcedureMenu(base);
		return;
	}
	else//Выбран определенный фрейм
	{
		std::string nameEntity = menu[key - 1];
		EntityMenu(base, nameEntity);
		return;
	}
}
//Запуск интерфейса
void Interface(std::string nameBase, std::string filename)
{
	Base* base = FileToBase(nameBase, filename);
	MainMenu(base);
}