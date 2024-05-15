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
библиотека SFML и движок PhysBox скачиваются отдельно при компиляции проекта.

### Запуск

Открыть терминал в корне проекта и ввести cmake -S .. -B .
После билда, проект готов к запуску. Можно запустить с exe файла внутри проекта,
можно запустить в VisualStudio, тогда необходимо в качестве run as startup project,
выбрать LightYearsGame.

## Credits
- Ассеты:  
	- `Все спрайты` SpaceShooterRedux - [Kenney](www.kenney.nl) .

## Цель проекта

Создание игры на C++ с использованием библиотек SFML и PhysBox2D.
