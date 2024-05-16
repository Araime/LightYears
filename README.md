# LightYears

Игра про космос, в которой корабль уничтожает другие корабли. 
При столкновении корабль уничтожается.

https://github.com/Araime/LightYears/assets/82653875/ff11028a-7963-456f-a9d5-1be442887bd5

## TO DO: 
1. Выпадение оружия
1. Выпадение бонусов
1. Набор уровней
1. Битва с боссом

## Установка

### Скачать

VisualStudio и CMake должны быть уже установлены.
[Скачать](https://github.com/Araime/LightYears/archive/refs/heads/master.zip) этот 
репозиторий себе на компьютер. В репозиторий входят все необхдимые реурсы, 
библиотека SFML и движок Box2D скачиваются отдельно при компиляции проекта.

### Запуск

Открыть терминал в корне проекта и ввести `cmake -S .. -B .`
После билда, проект готов к запуску. Можно запустить с exe файла внутри проекта,
можно запустить в VisualStudio, тогда необходимо в качестве run as startup project,
выбрать LightYearsGame.

## Credits
- Ассеты:  
	- `Все спрайты` SpaceShooterRedux - [Kenney](https://kenney.nl/assets/space-shooter-redux) .

## Цель проекта

Создание игры на C++ с использованием библиотеки SFML и физического движка Box2D by [Erin Catto](https://github.com/erincatto).
