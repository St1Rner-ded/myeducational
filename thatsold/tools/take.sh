#!/usr/bin/env bash
# ============================================================
#  take — перенос файлов из «Загрузок» Windows в репозиторий WSL
#
#  Установка:
#     mkdir -p ~/bin && cp take.sh ~/bin/take && chmod +x ~/bin/take
#     echo 'export PATH="$HOME/bin:$PATH"' >> ~/.bashrc && source ~/.bashrc
#
#  Использование:
#     take              забрать всё новое из Загрузок, распаковать zip, показать git status
#     take --list       только показать, что есть нового (ничего не трогать)
#     take --ship       то же, что take, + git add -A + commit + push
#     take --move       убрать забранное из Загрузок (по умолчанию — копируем)
#     take --keep-zip   не распаковывать .zip, а положить в репо как есть
#     take --dest DIR   класть не в корень репо, а в DIR (относительно корня)
#     take --all        игнорировать память о уже забранном и взять всё
#     take --reset      очистить память о забранных файлах
#
#  Переопределение путей (если автопоиск не сработал):
#     TAKE_REPO=~/projects/myeducational TAKE_DOWNLOADS=/mnt/d/Downloads take
# ============================================================
set -uo pipefail

STATE="${TAKE_STATE:-$HOME/.take_state}"
TRASH="${TAKE_TRASH:-$HOME/.take_taken}"
MODE_LIST=0; SHIP=0; MOVE=0; KEEPZIP=0; ALL=0; DEST=""

while [ $# -gt 0 ]; do
  case "$1" in
    --list|-l)    MODE_LIST=1 ;;
    --ship|-s)    SHIP=1 ;;
    --move|-m)    MOVE=1 ;;
    --keep-zip)   KEEPZIP=1 ;;
    --all|-a)     ALL=1 ;;
    --reset)      rm -f "$STATE"; echo "память о забранных файлах очищена"; exit 0 ;;
    --dest)       shift; DEST="${1:-}" ;;
    --dest=*)     DEST="${1#--dest=}" ;;
    -h|--help)    sed -n '2,26p' "$0" | sed 's/^# \{0,1\}//'; exit 0 ;;
    *)            echo "неизвестный параметр: $1 (см. take --help)"; exit 1 ;;
  esac
  shift
done

# ---------- ищем «Загрузки» Windows ----------
find_downloads() {
  [ -n "${TAKE_DOWNLOADS:-}" ] && { echo "$TAKE_DOWNLOADS"; return; }
  local d
  for d in /mnt/c/Users/*/Downloads /mnt/*/Users/*/Downloads; do
    case "$d" in
      *Public*|*Default*|*All\ Users*|*desktop.ini*) continue ;;
    esac
    [ -d "$d" ] && { echo "$d"; return; }
  done
}

# ---------- ищем репозиторий ----------
CONF="${TAKE_CONF:-$HOME/.take_conf}"
is_repo() {  # $1 = кандидат
  [ -d "$1/.git" ] || return 1
  git -C "$1" remote get-url origin 2>/dev/null | grep -qi 'myeducational'
}
find_repo() {
  # 1) явное указание
  [ -n "${TAKE_REPO:-}" ] && { echo "$TAKE_REPO"; return; }
  # 2) запомненный путь
  if [ -f "$CONF" ]; then
    local saved; saved="$(head -1 "$CONF" 2>/dev/null)"
    [ -n "$saved" ] && [ -d "$saved" ] && { echo "$saved"; return; }
  fi
  # 3) текущая папка и её предки
  local d="$PWD"
  while [ "$d" != "/" ] && [ -n "$d" ]; do
    is_repo "$d" && { echo "$d" > "$CONF"; echo "$d"; return; }
    d="$(dirname "$d")"
  done
  # 4) поиск внутри $HOME
  while IFS= read -r d; do
    if is_repo "$d"; then echo "$d" > "$CONF"; echo "$d"; return; fi
  done < <(find "$HOME" -maxdepth 5 -type d -name .git 2>/dev/null | sed 's|/\.git$||')
}

DL="$(find_downloads)"
REPO="$(find_repo)"

if [ -z "$DL" ] || [ ! -d "$DL" ]; then
  echo "❌ Не нашёл папку «Загрузки» Windows."
  echo "   Укажи явно:  TAKE_DOWNLOADS=/mnt/c/Users/ИМЯ/Downloads take"
  echo "   Проверь, что диск смонтирован:  ls /mnt/c"
  exit 1
fi
if [ -z "$REPO" ] || [ ! -d "$REPO/.git" ]; then
  echo "❌ Не нашёл репозиторий myeducational."
  echo "   Варианты:"
  echo "     cd /путь/к/myeducational && take      # найдёт от текущей папки"
  echo "     TAKE_REPO=~/projects/myeducational take"
  echo "     echo ~/projects/myeducational > ~/.take_conf   # запомнить навсегда"
  exit 1
fi

echo "Загрузки: $DL"
echo "Репо:     $REPO"
echo

# ---------- распаковщик ----------
unzip_to() {  # $1=архив $2=куда
  if command -v unzip >/dev/null 2>&1; then
    unzip -oq "$1" -d "$2"
  elif command -v bsdtar >/dev/null 2>&1; then
    bsdtar -xf "$1" -C "$2"
  elif command -v python3 >/dev/null 2>&1; then
    python3 -m zipfile -e "$1" "$2"
  else
    echo "   ⚠️  нечем распаковать (нужен unzip: sudo apt install unzip) — кладу архив как есть"
    cp -f "$1" "$2/" && return 0
  fi
}

is_junk() {
  case "$(basename "$1")" in
    desktop.ini|Thumbs.db|.DS_Store|~\$*) return 0 ;;
  esac
  return 1
}

# ---------- собираем список нового ----------
touch "$STATE"
TAKEN=()
while IFS= read -r -d '' f; do
  base="$(basename "$f")"
  is_junk "$f" && continue
  key="$(stat -c '%Y_%s' "$f")_$base"
  if [ "$ALL" -eq 0 ] && grep -qxF "$key" "$STATE"; then continue; fi
  TAKEN+=("$f|$key")
done < <(find "$DL" -maxdepth 1 -type f -print0 | sort -z)

if [ "${#TAKEN[@]}" -eq 0 ]; then
  echo "Новых файлов нет. (Принудительно взять всё: take --all)"
  exit 0
fi

echo "Найдено новых файлов: ${#TAKEN[@]}"
i=0
for e in "${TAKEN[@]}"; do
  f="${e%%|*}"; i=$((i+1))
  printf '  %2d. %-45s %8s  %s\n' "$i" "$(basename "$f")" \
    "$(du -h "$f" | cut -f1)" "$(date -d "@$(stat -c %Y "$f")" '+%d.%m %H:%M')"
done
echo

if [ "$MODE_LIST" -eq 1 ]; then exit 0; fi

TARGET="$REPO${DEST:+/$DEST}"
REL="${TARGET#"$REPO"}"; REL="${REL#/}"; REL="${REL:-.}"
mkdir -p "$TARGET"
mkdir -p "$TRASH"

copied=0
for e in "${TAKEN[@]}"; do
  f="${e%%|*}"; key="${e##*|}"; base="$(basename "$f")"
  case "$base" in
    *.zip|*.ZIP)
      if [ "$KEEPZIP" -eq 1 ]; then
        cp -f "$f" "$TARGET/" && echo "  📄 $base → $REL/" && copied=$((copied+1))
      else
        echo "  📦 $base → распаковываю в корень репо"
        unzip_to "$f" "$TARGET" && copied=$((copied+1))
      fi ;;
    *)
      cp -f "$f" "$TARGET/" && echo "  📄 $base → $REL/" && copied=$((copied+1)) ;;
  esac
  echo "$key" >> "$STATE"
  if [ "$MOVE" -eq 1 ]; then
    mv -f "$f" "$TRASH/" 2>/dev/null || rm -f "$f"
  fi
done

[ "$copied" -eq 0 ] && { echo "ничего не перенесено"; exit 1; }

echo
echo "════ git status ════"
git -C "$REPO" status --short | head -30

if [ "$SHIP" -eq 1 ]; then
  echo
  echo "════ commit + push ════"
  git -C "$REPO" pull --quiet --no-edit 2>/dev/null
  git -C "$REPO" add -A
  if git -C "$REPO" diff --cached --quiet; then
    echo "изменений нет — коммитить нечего"
  else
    MSG="обновление материалов $(date '+%Y-%m-%d %H:%M')"
    git -C "$REPO" commit --quiet -m "$MSG" && echo "коммит: $MSG"
    if git -C "$REPO" push --quiet 2>/dev/null; then echo "✅ запушено"; else
      echo "❌ push не удался — выполни вручную: cd $REPO && git push"; fi
  fi
else
  echo
  echo "Дальше:  cd $REPO && git add -A && git commit -m \"...\" && git push"
  echo "Или сразу:  take --ship"
fi
