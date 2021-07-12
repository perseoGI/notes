# Arch Things

## Restart audio

- pulseaudio -k / pulseaudio --start
- pavucontrol
- parec   redirect internal OS sound throw standard output


## Install PKGBUILD

	makepkg -Acs
	sudo pacman -U x.pkg.tar.xz
	___________________________
	A: ignores Arch architecture
	c: clears after installation
	s: install dependencies


## Pacman

### Update Arch

    sudo pacman -Syyuu

### Get all packages installed

	pacman -Qe

## Edit keyboard layout:

    setxkbmap -print -verbose 10            Display current config

Configure US international:

    setxkbmap -rules evdev -model evdev -layout us -variant altgr-intl

To set Dvorak international:

    1. sudo cp dvorak_intl /usr/share/X11/xkb/symbols/dvorak_intl
    2. setxkbmap -verbose dvorak_intl      for international Dvorak

Get keycodes pressed:

	xev

## Random stuff

- neofetch: show cool stuff in a cool way
- tune2fs -l /dev/sdb5 -l | grep Block     get block size of filesystem

## Disk utilities

	- baobab
	- ncdu (ncurses disk utilities)

### Secure Unplug USB

After dd do:

1. sync: force write all cache block to disk
2. udiskctl power-off -b /dev/xxx: physically shutdown disk

## Useful libraries

### TUI (text user interfaces)

	- ncurses
	- dialog (ncurses simplified)

### GLIB

Key-value config files interpreter
