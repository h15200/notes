# Vim motions, Neovim

- for quick text edit, just use `vi` as it's usually included in any os. You may need to apt install vim in a linux system
- always `set relative number`

## setup

- for macOS, use karabiner to set caps lock tap as Escape, and caps lock hold for control
- other global shortcuts include shift + escape (or caps lock) for divy, and caps lock + spacebar for tmux
- for vsCode, add `  "editor.lineNumbers": "relative",` to settings

## vertical movement
- gg to start
- G to end
- caps + { or } to scroll to blocks
- num + k , num + j (use relative lines)

## horizontal movement
- w or b, W or B to ignore symbols
- % to find brackets
- t or f + char for next instance, then ; or , 

## whole doc search
- / or ? then string, then n or N 

## other useful commands

- gh - error on hover
- gd - go to definition
- :%s/findString/replaceString/gc  - find and replace in entire document (exclude % for just the 1 line) but confirm for each one. Just like `sed`, the delimiter can be "." or "|"

## delete until next bracket
- d t }   is, delete until up to the closing bracket
- d f } - delete including bracket
- c t ], c f [ will do same but also be in insert mode 

