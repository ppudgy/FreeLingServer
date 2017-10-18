# FreeLingServer
Simple http interface for [FreeLing](https://github.com/TALP-UPC/FreeLing) NLP library with JSON data exchange format.

Depends of:

* [iod](https://github.com/matt-42/iod)
* [silicon](https://github.com/matt-42/silicon)
* [libmicrohttpd](http://www.gnu.org/software/libmicrohttpd/)
* [boost]()

# FreeLingServer
Простой интерфейс информационного взаимодействия с библиотекой обработки текста 
[FreeLing](https://github.com/TALP-UPC/FreeLing)

Требования:

* наличие пользовательского графического и машинного интерфейсов взаимодействия;
* возможность прозрачного удаленного сетевого взаимодействия;
* возможность прозрачного горизонтального масштабирования;
* использование простого, доступного в широком круге инструментов и сред программирования, протокола взаимодействия;
* реализация минимального набора функций (выделение предложений, слов, морфологический разбор);
* отсутствие необходимости конфигурирования и настройки (толко параметры командной строки, все параметры имеют значения по умолчанию, сохраняющие работоспособность программы);
* отсутствие состояния;
* минимальная зависимость от сторонних библиотек;

Применяемые решения: 

* транспортный протокол - HTTP
* формат данных - JSON
* интерфейс пользователя - HTML

Существующие зависимости:

* [iod](https://github.com/matt-42/iod)
* [silicon](https://github.com/matt-42/silicon)
* [libmicrohttpd](http://www.gnu.org/software/libmicrohttpd/)
* [boost](http://boost.org)

