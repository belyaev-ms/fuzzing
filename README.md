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
    - cmake ..
    - make
## Тестирование:
    - cd ./build
    - ctest
## Анализ покрытия кода тестами:
    - cd ./build
    - cmake .. -DEXM_USE_CLANG=OFF -DEXM_COVERAGE_ENABLED=ON
    - make
    - ctest
    - make coverage
    - ./coverage/index.html
## Статический анализ (cppcheck):
    - cd ./build
    - cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DEXM_USE_CLANG=OFF -DEXM_COVERAGE_ENABLED=ON
    - make cppcheck
## Динамический анализ (фаззинг с LibFazzer):
    - cd ./build
    - cmake .. -DEXM_USE_CLANG=ON -DEXM_COVERAGE_ENABLED=OFF
    - make fuzzer
    - ./tests/example_fuzzer
    - ./tests/example_fuzzer_too

