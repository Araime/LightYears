# LightYears

Игра про космос, в которой корабль летит и уничтожает другие корабли. 

https://github.com/user-attachments/assets/64ec8c43-853e-47c2-9937-39019e7f9e47

## Установка

### Скачать

VisualStudio и CMake (3.27.7) должны быть уже установлены.
[Скачать](https://github.com/Araime/LightYears/archive/refs/heads/master.zip) этот 
репозиторий себе на компьютер, разархивировать и переименовать папку с проектом в LightYears.
В репозиторий входят все необхдимые реурсы, библиотека SFML и движок Box2D скачиваются отдельно 
при компиляции проекта.

Возможно потребуется скорректировать пути, смотрите в логи компиляции и запуска.

### Сборка

Создать папку `build` в корне проекта и перейти в неё.

Терминал:
```sh
mkdir build
```
```sh
cd build
```

В папке `build` ввести:
```sh
`cmake -S .. -B .`.
```
CMake произведет сборку проекта и скачает необходимые библиотеки.
После билда, проект готов к запуску.

### Запуск

Запустить в VisualStudio, открыв файл `LightYears.sln`
в папке `build`, необходимо в качестве `run as startup project`, в solution explorer выбрать
`LightYearsGame`. После первого запуска в VisualStudio, по пути `build`->`LightYearsGame`,
появится папка `debug` или `release`, в зависимости от выбранного режима, в которой будет
exe-файл приложения.

## Credits
- Ассеты:  
	- `Все спрайты` SpaceShooterRedux - [Kenney](https://kenney.nl/assets/space-shooter-redux).

## Цель проекта

Создание игры на C++ с использованием библиотеки SFML и физического движка Box2D by 
[Erin Catto](https://github.com/erincatto/box2d).
