# Настройка среды компиляции на Windows

Тебе нужен **gcc/g++** (не MSVC/Visual Studio): на нём работает всё, что мы будем
использовать — `-Wall -Wextra`, санитайзеры, `gdb`, `valgrind`, `make`. Плюс в вузе
по «компьютерным системам» почти наверняка тоже gcc.

Выбери один вариант. **A — лучший**, **B — самый быстрый**.

---

## Вариант A · WSL2 + Ubuntu (рекомендую)

Полноценный Linux внутри Windows. Почему именно он: ты учишься на «компьютерных
системах», и рано или поздно всё равно окажешься в Linux — плюс только там полноценно
работают ASan/UBSan/valgrind, которые ловят 90% учебных ошибок с памятью.

В PowerShell **от администратора**:

```powershell
wsl --install -d Ubuntu
```

Перезагрузись, задай логин/пароль, затем внутри Ubuntu:

```bash
sudo apt update
sudo apt install -y build-essential gdb valgrind make cmake git
g++ --version && gcc --version && gdb --version | head -1
```

Дальше работаешь либо в терминале Ubuntu, либо в VS Code с расширением **WSL**
(команда `code .` из папки проекта — откроет VS Code, уже подключённый к Linux).

Алиасы, чтобы не набирать флаги руками (дописать в `~/.bashrc`):

```bash
echo 'alias cxx="g++ -std=c++20 -Wall -Wextra -Wpedantic -Wshadow -g -fsanitize=address,undefined"' >> ~/.bashrc
echo 'alias cc="gcc -std=c11 -Wall -Wextra -Wpedantic -Wshadow -g -fsanitize=address,undefined"' >> ~/.bashrc
source ~/.bashrc
```

Проверка: `cxx hello.cpp -o hello && ./hello`

---

## Вариант B · w64devkit (без установки, 5 минут)

Портативный набор: gcc, g++, make, gdb — просто распакованный архив.

1. Открой релизы: https://github.com/skeeto/w64devkit/releases
2. Скачай `w64devkit-x64-*.zip` (обычный, не `-llvm`)
3. Распакуй в `C:\w64devkit`
4. Запусти `C:\w64devkit\w64devkit.exe` — откроется shell, где уже есть `gcc`, `g++`, `make`, `gdb`
5. Проверь:
   ```
   gcc --version
   g++ --version
   make --version
   ```

Опционально — добавить в PATH, чтобы работало из любого терминала:
Параметры системы → Дополнительные параметры → Переменные среды → в `Path` добавить
`C:\w64devkit\bin`.

⚠️ `-fsanitize=address` под MinGW может не работать. Это не проблема: **я всё равно
прогоняю каждое твоё решение с ASan/UBSan у себя**, ты увидишь результат в отчёте.

---

## Вариант C · MSYS2

Если хочешь «взрослую» систему пакетов (пригодится позже для кросс-компиляции под МК):

1. Установщик: https://www.msys2.org/
2. В терминале **MINGW64**:
   ```bash
   pacman -Syu
   pacman -S mingw-w64-x86_64-toolchain make gdb
   ```
3. Добавь `C:\msys64\mingw64\bin` в PATH.

---

## Вариант D · Онлайн (если нужно начать прямо сейчас)

Для диагностики хватит и этого, но как постоянная среда — плохое решение
(нет нормального отладчика, нет санитайзеров, нет многофайловых проектов).

- **https://www.onlinegdb.com** — компилятор + отладчик + можно подать ввод. Выбирай C или C++17/20, в настройках включи `-Wall -Wextra`.
- **https://godbolt.org** — Compiler Explorer. Незаменим, чтобы увидеть, во что
  превращается твой код (включи `-O2` и смотрим справа ассемблер).
- **https://cppinsights.io** — показывает, во что C++ разворачивается на самом деле
  (конструкторы, шаблоны, лямбды). Будет очень полезен с модуля про классы.

---

## VS Code (любой вариант)

Расширения: **C/C++** (Microsoft), **WSL** (если выбрал вариант A).

`.vscode/tasks.json` — сборка по Ctrl+Shift+B:

```json
{
  "version": "2.0.0",
  "tasks": [
    {
      "label": "build c++ (strict)",
      "type": "shell",
      "command": "g++",
      "args": [
        "-std=c++20", "-Wall", "-Wextra", "-Wpedantic", "-Wshadow", "-Wconversion",
        "-g", "-fsanitize=address,undefined",
        "${file}", "-o", "${fileDirname}/${fileBasenameNoExtension}"
      ],
      "problemMatcher": ["$gcc"],
      "group": { "kind": "build", "isDefault": true }
    },
    {
      "label": "build c (strict)",
      "type": "shell",
      "command": "gcc",
      "args": [
        "-std=c11", "-Wall", "-Wextra", "-Wpedantic", "-Wshadow",
        "-g", "-fsanitize=address,undefined",
        "${file}", "-o", "${fileDirname}/${fileBasenameNoExtension}", "-lm"
      ],
      "problemMatcher": ["$gcc"]
    }
  ]
}
```

Отладка: F5 → выбрать `gdb` → `cppdbg`. Или просто `printf` — на первых порах он
быстрее и полезнее, чем ты думаешь.

---

## Проверка, что всё работает

Создай `hello.cpp`:

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v{1, 2, 3};
    int sum = 0;
    for (int x : v) sum += x;
    std::cout << "sum = " << sum << "\n";
}
```

Собери и запусти:

```bash
g++ -std=c++20 -Wall -Wextra -g -fsanitize=address,undefined hello.cpp -o hello && ./hello
```

Ожидание: `sum = 6` и ноль предупреждений. Пришло — среда готова, можно делать диагностику.
