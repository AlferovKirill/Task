# RoboPro Task

<p align="justify">В качестве задания необходимо было найти координаты x, y, z последнего сочленения робота в декартовой системе координат с помощью четырех параметров Денавита–Хартенберга. Данные параметры представлены для всех шести звеньев манипулятора. Параметры растояний вдоль осей и уголы альфа считаются постоянным и задаются внутри программы, так как тип сочленений вращательный. Переменные углы тетта подаются на вход программы в качестве txt файла.</p>

## C

<p align="justify">Программа желательно должна была быть консольной утилитой на C, поэтому в папке ROBOPRO_C лежит C-style решение данной задачи. Система сборки - make. В makefile определены цели: общая, exe и clean. Также задана переменная file для передачи конкретного файла с данными.</p>

<p align="justify">Примеры команд:</p>

```console
make
make file=testData/degrees2.txt
make clean
make exe | ./coordinates testData/degrees2.txt
```

<p align="justify">Примеры работы программы:</p>

```console
make
gcc -o coordinates main.c kinematic.c -lm
./coordinates "testData/degrees.txt"
x = -0.489383
y = -0.536833
z = 1.215349
rm coordinates 2>/dev/null
```

<img src="https://github.com/AlferovKirill/SignalHandler/assets/59083480/60f06de8-5ebc-44ac-b5a9-5ab527e38506">
<p align="center">Sender demonstration work in network</p>

<img src="https://github.com/AlferovKirill/SignalHandler/assets/59083480/095da701-ade6-4fd8-bbf6-f888950b0f63">
<p align="center">Receiver demonstration work in network</p>

https://github.com/AlferovKirill/SignalHandler/assets/59083480/ce9b1e6d-d54f-43b1-8a8e-81e88e68ae6e
<p align="center">Demonstration video in local</p>
