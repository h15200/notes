# Vim motions, Neovim

- for quick text edit, just use `vi` as it's usually included in any os. You may need to apt install vim in a linux system
- always `set relative number`

## setup

- for macOS, use karabiner to set caps lock tap as Escape, and caps lock hold for control
- other global shortcuts include shift + escape (or caps lock) for divy, and caps lock + spacebar for tmux
- for vsCode, add `  "editor.lineNumbers": "relative",` and "vim.vimrc.enable": true to settings

## .vimrc

- use vim-plug to manage all plugins
  - vim-slash to unhighlight searches
- relative num, num, ruler, cmd, etc..
  set scrolloff=2
  nnoremap <C-u> <C-u>zz
  nnoremap <C-d> <C-d>zz
  nnoremap n nzzzv
  nnoremap N Nzzzv
  nnoremap H 0
  nnoremap L $
- use `:so` to source from within dotfiles inside vim

### mac terminal setup

- install iterm2 `brew install --cask iterm2`
- install oh my zsh `sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"`
- install powerlevel10k theme `git clone https://github.com/romkatv/powerlevel10k.git $ZSH_CUSTOM/themes/powerlevel10k`
  - cp -r that dir into regular ~/.oh-my-zsh/themes as well to prevent "not found" error on startup
- change .zshrc theme to ZSH_THEME="powerlevel10k/powerlevel10k"
  - for every change in .zshrc, always `source .zshrc`
- if you want to use the same 10k font in vscode, add `"terminal.integrated.fontFamily": "MesloLGS NF"` to settings.json
- restart iterm then run `p10k configure`
- to change anything else like font, go to iterm2 pref -> profiles -> text

### zsh plugins

- `git clone https://github.com/zsh-users/zsh-autosuggestions ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-autosuggestions`
- `git clone https://github.com/zsh-users/zsh-syntax-highlighting.git ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-syntax-highlighting`
  - add both zsh-autosuggestions and zsh-syntax-highlighting to .zshrc where it says plugins(). no commas, just whitespace as delimiter
  - no need to install, but also add web-search to plugins list
- also in .vimrc, add new keybinding for auto complete so it's not right arrow, but a semi-colon. "bindkey ';' autosuggest-accept"

## vertical movement

- gg to start
- G to end
- caps + { or } to scroll to blocks
- num + k , num + j (use relative lines)

## horizontal movement

- w or b, W or B to ignore symbols
- % to find brackets
- t or f + char for next instance, then ; or ,

## word object movement

- `viw` to select word, or `viW` for words with delimiters and parens
  - note that `vw` only goes from current point to end of word
- for parens, `vi{` will go to next content between {}.
- `va(` a instead of i will be inclusive of those brackets
  - same concept for paragraph `p` like `vip`

## whole doc search

- / or ? then string, then n or N

## other useful commands

- gh - error on hover
- gd - go to definition
- :%s/findString/replaceString/gc - find and replace in entire document (exclude % for just the 1 line) but confirm for each one. Just like `sed`, the delimiter can be "." or "|"

## delete all inside the nearest bracket

- `vi[` concept to go to nearest bracket, then either "inclusive" or a for "inclusive" to op the content
- d i [ will look for the closest [] content and delete all the content (not incuding the actual brackets)
- d i ] will do the same
- di " - nearest quote content

## delete until next bracket

- d t } is, delete until up to the closing bracket
- d f } - delete including bracket
- c t ], c f [ will do same but also be in insert mode

## visual mode

- v or V to toggle visual, visual line mode
- in visual mode, you can press `o` to toggle back and forth start to end

## visual block mode

- control v to start, then move j or k
- after selecting, use `I` or `A` only (no `i`, no `a`) and start editing, then escape to confirm
