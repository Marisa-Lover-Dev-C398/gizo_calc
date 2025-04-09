# 電卓みたいな電卓
## toiletコマンドが入ってないと文字が正常に表示されません。
## また、ncursesw が無いとビルドできません。

---

### 必要なやつ

- gcc
- ncursesw（ワイド文字対応の画面制御ライブラリ）
- toilet（アスキーアート表示用）

---

### インストール方法！！！！！！！！！

#### Ubuntu / Debian

```bash
sudo apt update
sudo apt install build-essential libncursesw5-dev toilet
```

#### Arch Linux / Manjaro

```bash
sudo pacman -S base-devel ncurses toilet
```

#### Fedora

```bash
sudo dnf install gcc ncurses-devel toilet
```

#### openSUSE

```bash
sudo zypper install gcc ncurses-devel toilet
```

---

### コンパイル！！！

```bash
make
```
