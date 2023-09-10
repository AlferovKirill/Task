# RoboPro Task

<p align="justify">В качестве задания необходимо было найти координаты x, y, z последнего сочленения робота в декартовой системе координат с помощью четырех параметров Денавита–Хартенберга. Данные параметры представлены для всех шести звеньев манипулятора. Параметры растояний вдоль осей и уголы альфа считаются постоянным и задаются внутри программы, так как тип сочленений вращательный. Переменные углы тетта подаются на вход программы в качестве txt файла.</p>

## C-style

<p align="justify">В качестве пожелания программа должна быть консольной утилитой на C, поэтому в папке ROBOPRO_C лежит C-style решение данной задачи. Система сборки - make. В makefile определены цели: общая, exe и clean. Также задана переменная file для передачи конкретного файла с данными.</p>

<p align="justify">Примеры команд:</p>

```console
make
make file=testData/degrees2.txt
make clean
make exe | ./coordinates testData/degrees2.txt
```

<p align="justify">Пример работы программы:</p>

```console
make
gcc -o coordinates main.c kinematic.c -lm
./coordinates "testData/degrees.txt"
x = -0.489383
y = -0.536833
z = 1.215349
rm coordinates 2>/dev/null
```

<img src="https://github.com/AlferovKirill/Task/assets/59083480/f76f0a7b-08c5-4c32-9284-d84c6e38f5ae" align="middle">
<p align="center">degrees.txt</p>

<img src="https://github.com/AlferovKirill/Task/assets/59083480/1f5351e2-0ec6-49c0-9597-d81cf17fa716" align="middle">
<p align="center">degrees2.txt</p>

https://github.com/AlferovKirill/Task/assets/59083480/4385d298-6dc3-4f0f-8b18-9122fa568b0a
