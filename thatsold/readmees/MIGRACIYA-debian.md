# Переезд курса на Debian в WSL2

## 0. Сначала хорошая новость

Всё, что ты сдал, **лежит на GitHub**: решения, конспекты, `SPRAVOCHNIK.md`, `notes/`,
твой Arduino-проект. При удалении Ubuntu потерялась только локальная копия и настройки
окружения. Переделывать ничего не нужно — достаточно клонировать репо заново.

---

## 1. Как посмотреть версию дистрибутива

### Из WSL

```bash
cat /etc/os-release       # PRETTY_NAME="Debian GNU/Linux 13 (trixie)"
cat /etc/debian_version   # точный номер, например 13.4
uname -r                  # ядро; в WSL будет ...-microsoft-standard-WSL2
lsb_release -a            # если стоит пакет lsb-release (после setup-скрипта — да)
hostnamectl               # только если в /etc/wsl.conf включён systemd
```

Основной и всегда работающий способ — **`cat /etc/os-release`**.

### Из Windows (PowerShell)

```powershell
wsl -l -v        # список дистрибутивов: NAME, STATE, VERSION
wsl --version    # версия самой платформы WSL
wsl --status     # дистрибутив по умолчанию
```

⚠️ **Частая путаница:** колонка `VERSION` в выводе `wsl -l -v` — это **версия WSL
(1 или 2)**, а не версия Debian. Версию самого дистрибутива показывает только
`/etc/os-release` или `/etc/debian_version`.

Пример того, что ты должен увидеть:

```
  NAME            STATE           VERSION
* Debian          Running         2
```

То есть: дистрибутив Debian, запущен, работает в режиме WSL **2**. А версия Debian —
отдельно, внутри.

### Заодно проверь окружение

```bash
gcc --version | head -1    # ожидаю: gcc (Debian 14.2.0-...) 14.2.0
echo "$HOME / $SHELL"      # /home/твой_логин и /bin/bash
id -u                      # 0 = root, иначе обычный пользователь
ls /mnt/c >/dev/null && echo "/mnt/c доступен" || echo "/mnt/c НЕТ"
```

Пришли мне вывод `cat /etc/os-release` и `gcc --version` — сверим ожидания.

---

## 2. Инвентаризация: что пропало

| Что | Статус после удаления Ubuntu | Как вернуть |
|---|---|---|
| Решения, конспекты, справочник | ✅ целы на GitHub | `git clone` |
| `gcc`, `g++`, `gdb`, `make` | ❌ | `setup-debian.sh` |
| `valgrind`, `cmake`, `clang-format`, `unzip` | ❌ | `setup-debian.sh` |
| `git config user.name / user.email` | ❌ | скрипт спросит |
| **Доступ к GitHub (push)** | ❌ | SSH-ключ или токен — §4 |
| `~/bin/take` | ❌ | `setup-debian.sh` |
| Алиасы `cxx` / `cc` в `.bashrc` | ❌ | `setup-debian.sh` |
| `~/.take_conf`, `~/.take_state` | ❌ | создадутся заново |
| VS Code Server внутри WSL | ❌ | поставится сам при подключении |
| Расширения VS Code для WSL | ❌ | переустановить в окне WSL |

Единственный пункт, который скрипт за тебя не сделает, — доступ к GitHub (§4).

---

## 3. Переезд за три шага

### Шаг 1. Скачать архив

Скачай `debian-migration.zip` из чата — он попадёт в `C:\Users\…\Downloads`.

### Шаг 2. Распаковать и запустить в WSL (Debian)

```bash
mkdir -p ~/mig && cd ~/mig
python3 -m zipfile -e "$(ls /mnt/c/Users/*/Downloads/debian-migration.zip | head -1)" .
bash setup-debian.sh
```

Если `python3` в свежем Debian ещё нет (образ минимальный) — распакуй zip в Windows
и скопируй папку в WSL через Проводник:
`\\wsl.localhost\Debian\home\ТВОЙ_ЛОГИН\mig`, либо перетащи в VS Code.

### Шаг 3. Проверить

```bash
source ~/.bashrc
take --list
```

### Что делает скрипт

1. Показывает, что за система (дистрибутив, ядро, WSL2 или нет, доступен ли `/mnt/c`).
2. Ставит пакеты: `build-essential gdb valgrind make cmake git unzip python3
   pkg-config clang-format man-db manpages-dev lsb-release`.
3. Проверяет наличие всех инструментов и их версии.
4. **Реально компилирует тестовую программу** полным набором флагов
   (`-Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion -Wformat=2
   -fsanitize=address,undefined`) и убеждается, что предупреждений ноль; отдельно
   проверяет, что UBSan ловит знаковое переполнение, а valgrind запускается.
5. Настраивает `git config user.name / user.email` (спросит, если не заданы).
6. Ищет репозиторий; если нет — клонирует в `~/projects/myeducational` и пишет путь
   в `~/.take_conf`.
7. Ставит `take` в `~/bin`, прописывает `PATH` и алиасы `cxx` / `cc` в `~/.bashrc`.
8. Печатает итог: что готово и что осталось сделать руками.

Скрипт **идемпотентен** — повторный запуск ничего не ломает (пропускает уже сделанное).

Режимы:

```bash
bash setup-debian.sh --check                                  # только диагностика, ничего не ставить
GIT_NAME="Имя" GIT_EMAIL="mail@example.com" bash setup-debian.sh   # без интерактивных вопросов
PROJECTS_DIR=~/code bash setup-debian.sh                      # клонировать в другую папку
```

---

## 4. Доступ к GitHub (единственный ручной шаг)

Пароль от GitHub для git больше не принимается. Два варианта.

### Вариант A · SSH-ключ — рекомендую

Настраивается один раз, дальше никаких токенов и ввода пароля.

```bash
ssh-keygen -t ed25519 -C "твоя_почта@example.com"
# на все вопросы можно нажать Enter (файл по умолчанию, без пароля)
cat ~/.ssh/id_ed25519.pub
```

Скопируй вывод **целиком** (начинается с `ssh-ed25519 AAAA...`).
GitHub → Settings → **SSH and GPG keys** → New SSH key → вставь → Add.

Проверка:

```bash
ssh -T git@github.com
# ожидаю: Hi St1Rner-ded! You've been successfully authenticated...
```

Перевести репозиторий на SSH:

```bash
cd ~/projects/myeducational
git remote set-url origin git@github.com:St1Rner-ded/myeducational.git
git remote -v        # проверить
```

### Вариант B · Personal Access Token

GitHub → Settings → Developer settings → Personal access tokens → Tokens (classic)
→ Generate new token → галочка **`repo`** → срок по вкусу.

```bash
git config --global credential.helper store
git push      # при первом запросе: Username = St1Rner-ded, Password = ТОКЕН
```

⚠️ `credential.helper store` сохраняет токен в `~/.git-credentials` **открытым текстом**.
Для учебного репозитория приемлемо, но знать об этом надо. Альтернатива — `cache`
(хранит в памяти 15 минут): `git config --global credential.helper 'cache --timeout=3600'`.

---

## 5. VS Code

1. Расширение **WSL** в Windows-части VS Code у тебя уже стоит.
2. `F1` → `WSL: Connect to WSL...` → выбрать **Debian**.
3. Сервер VS Code установится сам в `~/.vscode-server` — первое подключение займёт
   минуту-другую, это нормально.
4. Поставить расширение **C/C++** (Microsoft) именно в WSL: на странице расширения
   будет кнопка «Install in WSL: Debian».
5. Проверить, что окно подключено к Debian: зелёная плашка в **левом нижнем углу**
   окна VS Code должна показывать `WSL: Debian`.
6. Дальше из терминала WSL работает `code .` — открывает текущую папку в VS Code.

---

## 6. Что изменилось по сравнению с Ubuntu — важно для кода

Свежий Debian из Microsoft Store — это **Debian 13 «trixie»**, а в нём **gcc 14.2**.
В Ubuntu у тебя был gcc 12 или 13. Три отличия, которые ты заметишь:

### 1. Пропущенный `#include` теперь ошибка, а не предупреждение

В gcc 14 по умолчанию стали **ошибками** диагностики, которые раньше были предупреждениями:
`-Wimplicit-int`, `-Wimplicit-function-declaration`, `-Wint-conversion`, `-Wreturn-mismatch`.

```c
/* gcc 12: warning, программа собиралась и «как-то работала» */
/* gcc 14: error: implicit declaration of function 'printf'  */
int main(void) { printf("hi\n"); return 0; }
```

Для учёбы это **хорошо**: компилятор больше не даст молча собрать код, где функция
объявлена неявно (а неявное объявление в C означает «возвращает int», что почти всегда
баг). Но если увидишь такую ошибку — просто добавь недостающий `#include`.

### 2. Стандарт C по умолчанию — `gnu17`

То есть `bool`, `true`, `false` в C **без `#include <stdbool.h>` не работают**
(это изменится в gcc 15, где стандарт по умолчанию — C23). В C++ `bool` есть всегда.

Мы в курсе всё равно задаём стандарт явно — `-std=c11` для C и `-std=c++20` для C++ —
поэтому поведение зафиксировано и совпадает с тем, что проверяю я.

### 3. Строгий режим и расширения glibc

Если в режиме `-std=c11` glibc откажется давать объявления функций, которых нет в
стандарте (`strdup`, `fileno`, `getline` и т.п.), добавь `-D_DEFAULT_SOURCE` или
используй `-std=gnu11` вместо `-std=c11`.

### Отличия самого Debian от Ubuntu

- Нет `snap` — пакеты только из `apt`. Нам это не мешает.
- Debian консервативнее: версии пакетов чуть старее, чем в свежей Ubuntu, зато стабильнее.
- `sudo` может отсутствовать, если образ развёрнут под root:
  ```bash
  apt update && apt install -y sudo
  usermod -aG sudo ТВОЙ_ЛОГИН     # затем перезайти в шелл
  ```
- Минимальный образ может не содержать `python3` и `unzip` — скрипт их поставит.
- `systemd` по умолчанию выключен; если понадобиется — в `/etc/wsl.conf`:
  ```ini
  [boot]
  systemd=true
  ```
  затем из Windows: `wsl --shutdown` и снова открыть.

---

## 7. Чек-лист после переезда

- [ ] `cat /etc/os-release` → Debian 13 (trixie)
- [ ] `wsl -l -v` из Windows → Debian, VERSION = 2
- [ ] `gcc --version` → 14.x
- [ ] `bash setup-debian.sh` прошёл, в разделе 4 три зелёные галочки
- [ ] `ssh -T git@github.com` отвечает `Hi St1Rner-ded!` (или настроен токен)
- [ ] `git push` реально работает
- [ ] `take --list` находит и Загрузки, и репозиторий
- [ ] `source ~/.bashrc` → алиас `cxx` работает
- [ ] VS Code подключён к Debian (зелёная плашка `WSL: Debian`), расширение C/C++ стоит
- [ ] В клонированном репо на месте: `solutions/`, `SPRAVOCHNIK.md`, `theory/`, `notes/`

Проверочная команда «всё точно работает»:

```bash
mkdir -p ~/tmp && cd ~/tmp
cat > hello.cpp <<'EOF'
#include <iostream>
#include <vector>
int main() {
    std::vector<int> v{1, 2, 3};
    int s = 0; for (int x : v) s += x;
    std::cout << "sum = " << s << "\n";
}
EOF
cxx hello.cpp -o hello && ./hello      # ожидаю: sum = 6, ноль предупреждений
```

---

## 8. Частые проблемы

| Симптом | Решение |
|---|---|
| `sudo: command not found` | ты root — запускай без `sudo`, либо поставь: `apt install sudo` |
| `apt-get update` падает | проверь сеть: `ping -c1 deb.debian.org`; в WSL бывает после сна Windows — `wsl --shutdown` и заново |
| `/mnt/c` пуст или не существует | `sudo mkdir -p /mnt/c && sudo mount -t drvfs C: /mnt/c`; либо проверь `/etc/wsl.conf` на `automount` |
| `ls /mnt/c/Users/*/Downloads` даёт несколько путей | задай явно: `TAKE_DOWNLOADS="/mnt/c/Users/ИМЯ/Downloads" take` |
| `take: command not found` | `source ~/.bashrc`, либо запускай `~/bin/take` |
| `git push` просит пароль и не принимает его | пароль от GitHub больше не работает — нужен SSH-ключ или токен (§4) |
| `ssh -T git@github.com` → Permission denied | ключ не добавлен на GitHub, либо не тот файл: проверь `cat ~/.ssh/id_ed25519.pub` |
| `error: implicit declaration of function 'printf'` | gcc 14 сделал это ошибкой — добавь `#include <stdio.h>` |
| `bool` неизвестен в C-коде | `#include <stdbool.h>` (или компилируй как C++ / `-std=gnu23`) |
| VS Code подключается к Ubuntu, которой нет | `F1` → `WSL: Connect to WSL...` → выбрать Debian явно |
| valgrind ругается на «unhandled syscall» | на WSL2 часть syscall не поддержана; для поиска утечек используй ASan (`-fsanitize=address`) |
