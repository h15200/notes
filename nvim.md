# neo vim

## netrw

- directory system within vim (and nvim)
- point to any directory and `nvim .`

- `%` to create a new file
- `d` will create a directory
- `:Ex` "explore" will go back to netrw


## config in lua

- `lua` is the programming language that's used to configurate nvim
- ease of use of lua is one of the main pro of using nvim over vim
    - note that using .lua files will only work in `nvim`, not regular vim
- `init.lua` is the index of all lua config
    - it should require any other directories containing .lua files

## file structure of nvim

- everything lives inside ~/.config/nvim
- inside nvim, there is one top level `init.lua`, and a lua dir that contains all config

## plugin packager

- the recommended packager for neovim is `packer`
- install it, then add the script inside lua/username/packer.lua
- `:PackerSync` will check the packer file and install any new plugins

## recommended remaps and plugins
- `packer` to manage all plugins
- leader to spacebar
- `:Ex` to leader pv

