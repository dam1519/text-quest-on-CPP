# text-quest-on-CPP


## русский

мой первый проект на c++. я даже не буду думаю писать подробный readme просто расскажу про архитектуру хз.

сначала мы создаем оружия через наследования от структуры weapon от которой происходят knife и rifle

потом класс игрока который по сути носит в себе чисто данные и по запросу отдает через свои геттеры и сеттеры
в нем из интересно только смена оружия через ссылки и указатели

далее идет структура врага в которой мы создаем переменные для координат и его радиус

далее класс доски который управляет игрой
сначала в нем мы создаем классы и струкуры к которым потом будем обращаться
потом идет move_check в котором мы по гипотинузе до врага узнаем есть ли он по близости
в нем же мы проверяем другие вещи например есть ли на координатах игрока таверна или клад и сообщаем если есть
далее функция fight в ней мы проверяем достает ли игрок до врага и потом проверяем достает ли враг до игрока
далее функция shop где мы преветствуем игрока и говорим список товаров и их характеристики
далее конструктор доски где мы задаем оружие игроку и координаты врага
далее main_loop где мы узнаем команду игрока и в зависимости от команды выполняем действие

и наконец после всего этого у нас функция main где мы создаем доску и вызываем главный цикл

## english

my first project on c++. i won't even think about writing a detailed readme i'll just tell about the architecture idk.

first we create weapons through inheritance from the weapon structure from which knife and rifle originate

then the player class which essentially carries pure data in itself and gives it upon request through its getters and setters
the only interesting thing in it is the weapon change through references and pointers

next comes the enemy structure in which we create variables for coordinates and its radius

next is the board class which manages the game
first in it we create classes and structures which we will access later
then comes move_check in which we find out by the hypotenuse to the enemy if he is nearby
in it we also check other things for example if there is a tavern or a treasure at the player's coordinates and inform if there is
next is the fight function in it we check if the player reaches the enemy and then check if the enemy reaches the player
next is the shop function where we welcome the player and tell the list of goods and their characteristics
next is the board constructor where we set the weapon to the player and the coordinates of the enemy
next is main_loop where we find out the player's command and depending on the command we perform an action

and finally after all this we have the main function where we create the board and call the main loop
