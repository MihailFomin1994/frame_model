# Фреймовая модель представления знаний
## Является учебным проектом по заданию:
1. Выполнить описание предметной области по варианту задания в виде фреймовой модели.
Необходимо описать предметную область в виде фреймов-прототипов вида «фрейм», «список слотов», где каждый слот обязательно имеет имя, и может быть либо пустым, либо содержать ссылку по имени на другой фрейм-прототип или фрейм-экземпляр, либо быть заполнен списком атрибутов – структура вида «имя атрибута», «список значений», и фреймов-экземпляров, где нет пустых слотов, во всех слотах все элементы списков значений всех атрибутов заполнены значениями вида «тип значения», «собственно значение», а все ссылки на другие фреймы указывают только на фреймы-экземпляры.
2. Выполнить разработку программы создания и редактирования фреймового представления предметной области согласно варианту задания, а также семантического и синтаксиче-ского сопоставления в ней фреймов-прототипов и фреймов-экземпляров.
Необходимо написать программу на любом известном языке программирования, реализующую основные операции над фреймами, представленными с помощью некото-рых структур данных, соответствующих п. 1 задания.
    1. Формирование фреймовой модели — добавление, удаление, изменение фреймов, слотов фреймов, списков атрибутов слотов и значений атрибутов, включая формирование связей между фреймами.
    2. Автоматическое сохранение фреймовой модели при неаварийном прекращении работы программы и компьютера.
    3. Восстановление сохраненного значения после повторного запуска.
    
В программе необходимо реализовать поиск в базе знаний путем формирования произвольного фрейма-прототипа («поискового образца»):
    - Не имеющего имени (слот «имя» заполняется по результатам поиска).
    - Имеющего произвольное число слотов с произвольными атрибутами, в том числе неиз-вестными системе, а также с произвольными значениями атрибутов. При этом может как указываться тип значения атрибута, так и не указываться (тип игнорируется)

С использованием формируемых фреймов-прототипов необходимо реализовать как синтаксический, так и семантический поиск (при этом если указан «тип», то он соот-носится либо с типом атрибута, либо с типом значения атрибута соответственно). При этом должна быть явно предоставлена возможность использовать как поиск «ничего лишнего» (все фреймы, имеющие другие слоты, кроме указанных во фрейме-прототипе, отвергаются), так и поиск «всего подходящего» (в результаты включаются фреймы, име-ющие наряду с найденными слотами из фрейма-прототипа, и какие-либо еще слоты).
Реализовать изменение состояния базы знаний путем обращения к определенным атрибутам определенных слотов как по чтению («завести двигатель»), так и по записи («педаль газа = нажата на 75%»).

3. С помощью разработанной программы представить полученную по варианту за-дания модель предметной области.

## Описание программы
Данная программа разрабатывалась и тестировалась в операционной системе Mi-crosoft Windows 10. Данная программа работает с использованием текстового интерфейса с ручным вводом пользователем номера пункта меню. При неверном или неправильном вводе программа сообщит об этом. Запись фреймов, их слотов и их атрибутов, связей между атрибутами слотов фреймов с другими фреймами, а также их процедуры поступа-ют в программу в виде текстового файла.
В данной программе отсутствует проверка типа данных. Следовательно, пользова-тель может ввести любой тип данных и его значение на свое усмотрение, но валидность введенных им данных проверяется им самим. По умолчанию программа работает со сле-дующими типами данных: frame (ссылка атрибута на другой фрейм), text (текст), bool (ло-гическое значение да или нет), integer (целое число) и null (пустое значение).
Также считает, что атрибут, содержащий в себе ссылку на фрейм, не имеет значе-ния. Следовательно, в случае того, что ему будет задано значение, связь с фреймом будет разорвана. Также не допускается создание атрибута с типом данных frame, но не имеюще-го связь с другим фреймом. Данный тип присваивается атрибуту автоматически в случае установления связи с ним и другим фреймом.
Изменение состояния «по чтению» и «по записи» производится процедурами. Каждая из них имеет имя, атрибут, значение которого она меняет и значение по умолча-нию. Следовательно, разделение процедур на «по чтению» и «по записи» условно, и в данной программе может быть выполнено единовременно. Данный аспект остается на усмотрение пользователя.
Также в программе при вводе нельзя использовать пробелы. Для разделения слов используется символ «_». 
В меню процедур ввод процедур производится рекурсивно. Для завершения ввода процедур введите «Завершить» 
Программа использует 6 видов меню и у каждого свое назначение:
1.	Главное меню – позволяет создавать фреймы, получить доступ к любому имеющемуся фрейму, а также получить доступ к «Меню поиска» и «Меню процедур».
2.	Меню поиска – в данном меню задается и изменяется прототип поискового фрейма и выбирается тип поиска, а именно «Поиск по точному совпадению» и «Поиск по включению», каждый из которых позволяет выбрать режим поиска, а именно синтак-сический или семантический поиск. При этом в случае «Поиск по точному совпаде-нию» результатом является фрейм, синтаксически или семантически точно совпада-ющий с поисковым прототипом. В ином случае в результат попадает тот фрейм, ко-торый включает в себя поисковый фрейм прототип.
3.	Меню процедур – данной меню позволяет вводить процедуры для обработки базой знаний. Более подробная информация отражена в самом меню.
4.	Меню фрейма – позволяет добавлять слоты текущему фрейму, а также получить до-ступ к уже имеющимся слотам фрейма. Также данной меню позволяет удалить теку-щий фрейм и изменить его имя.
5.	Меню слота – позволяет добавлять атрибуты текущему слоту текущего фрейма, а так-же получить доступ к любому имеющемуся атрибуту слота фрейма. Также данной ме-ню позволяет удалить текущий слот фрейма и изменить его имя.
6.	Меню атрибута – позволяет добавлять, изменять и удалять связи атрибута, его имя, значение, а также удалять текущий атрибут.

