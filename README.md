# fuzzing

Демо проект для доклада "Безопасная разработка":
- Статический анализ и какие виды ошибок он позволяет обнаружить;
- Unit-тестирование;
- Использование санитайзеров или как за один шаг можно вывести unit-тесты на новый уровень;
- Может ли 100% тестовое покрытие быть гарантом отсутствия ошибок в коде;
- Динамический анализ и как фаззинг может помочь обнаружить ошибки.

## Сборка проекта
    - mkdir ./build
    - cd ./build
    - cmake <source dir>
    - make
## Тестирование:
    - cd ./build
    - ctest
## Анализ покрытия кода тестами:
    - cd ./build
    - cmake -DEXM_USE_CLANG=OFF -DEXM_COVERAGE_ENABLED=ON <source dir>
    - make
    - ctest
    - make coverage
    - ./coverage/index.html
## Статический анализ (cppcheck):
    - cd ./build
    - cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DEXM_USE_CLANG=OFF -DEXM_COVERAGE_ENABLED=ON <source dir>
    - make cppcheck
## Динамический анализ (фаззинг с LibFazzer):
    - cd ./build
    - rm -rf *
    - cmake -DEXM_USE_CLANG=ON -DEXM_COVERAGE_ENABLED=OFF <source dir>
    - make fuzzer
    - ./tests/example_fuzzer
    - ./tests/example_fuzzer_too
## Docker
### Использование
Сборку, тестирование, анализа покрытия, статический и динамический анализ рекомендуется выполнять в
[docker](https://docs.docker.com/get-started/overview/)-контейнере. Следующая команда соберет образ
с именем `fuzzing` и установит в него зависимости проекта:

    - docker build -t fuzzing .
    
В образ не копируется исходный код проекта. Вместо этого, в домашнем каталоге пользователя создаются
директории `/root/src/` и `/root/build/`. Первая директория при запуске контейнера будет примонтирована
к директории хоста с исходным кодом. Вторую директорию предлагается исопльзовать для сборки проекта.
Для старта контейнера с монтированием `/root/src/` необходимо выполнить команду:

    - sudo docker run -it -v `pwd`:/root/src --name fuzzing fuzzing /bin/bash
    
Данные, которые необходимо скопировать из контейнера на хост, можно поместить в примонтированную директорию.

    - cd ./build
    - cp -r ./coverage/ /root/src/
    
После выполнения этой команды результаты анализа покрытия появятся в директории с исходным кодом на хосте.
### Cheat sheet
Вывести список образов, хранящихся в системе:

    - docker images
    
Вывести список всех контейнеров:

    - docker ps -a
    
Удалить все остановленные контейнеры:

    - docker container prune [-f]
    
Удалить контейнер с именем `<name>` или идентификатором `<id>`:

    - docker rm (<name>|<id>)
    
Удалить все недействительные образы:

    - docker image prune [-f]
    
Удалить образ с именем `<name>` или идентификатором `<id>`:

    - docker rmi (<name>|<id>)
