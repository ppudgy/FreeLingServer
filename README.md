# FreeLingServer
Simple http interface for [FreeLing](https://github.com/TALP-UPC/FreeLing) NLP library with JSON data exchange format.

Depends of:

* [FreeLing](https://github.com/TALP-UPC/FreeLing)
* [crow](https://github.com/ipkn/crow)

# FreeLingServer
Простой интерфейс информационного взаимодействия с библиотекой обработки текста 
[FreeLing](https://github.com/TALP-UPC/FreeLing)

## Требования:

* наличие пользовательского графического и машинного интерфейсов взаимодействия;
* возможность прозрачного удаленного сетевого взаимодействия;
* возможность прозрачного горизонтального масштабирования;
* использование простого, доступного в широком круге инструментов и сред программирования, протокола взаимодействия;
* реализация минимального набора функций (выделение предложений, слов, морфологический разбор);
* отсутствие необходимости конфигурирования и настройки (толко параметры командной строки, все параметры имеют значения по умолчанию, сохраняющие работоспособность программы);
* отсутствие состояния;
* минимальная зависимость от сторонних библиотек;

## Применяемые решения: 

* транспортный протокол - HTTP
* формат данных - JSON
* интерфейс пользователя - HTML

Существующие зависимости:

* [FreeLing](https://github.com/TALP-UPC/FreeLing)
* [crow](https://github.com/ipkn/crow)


## Сборка

	mkdir build
	cd build
	cmake ..
	make

## Установка
	
	cp freelingserver /usr/local/bin
	cp ../scripts/freelingserver.service /etc/systemd/system
	systemctl daemon-reload
	systemctl enable freelingserver.service
	systemctl start freelingserver.service
