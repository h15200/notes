"""""""""""""""""
"Normal config
"""""""""""""""""

" enable VIM stuff but makes vi not compatible 
set nocompatible

" auto indent when pressing return and o
set autoindent

set relativenumber
set number

" lower right ruler
set ruler

" shows current command 
set showcmd

set hlsearch
" show at least 2 lines above
set scrolloff=2

"""""""""""""""""
" Key Mapping
""""""""""""""""
" add page center after up and down jumps
nnoremap <C-u> <C-u>zz
nnoremap <C-d> <C-d>zz
nnoremap n nzzzv
nnoremap N Nzzzv
nnoremap H 0
nnoremap L $
" PLUGINS 
  " use :PlugInstall to install new plugins

" initialize vim-plug
let data_dir = has('nvim') ? stdpath('data') . '/site' : '~/.vim'
if empty(glob(data_dir . '/autoload/plug.vim'))
  silent execute '!curl -fLo '.data_dir.'/autoload/plug.vim --create-dirs  https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim'
  autocmd VimEnter * PlugInstall --sync | source $MYVIMRC
endif

call plug#begin()
" The default plugin directory will be as follows:
"   - Vim (Linux/macOS): '~/.vim/plugged'
"   - Vim (Windows): '~/vimfiles/plugged'
"   - Neovim (Linux/macOS/Windows): stdpath('data') . '/plugged'
" You can specify a custom plugin directory by passing it as the argument
"   - e.g. `call plug#begin('~/.vim/plugged')`
"   - Avoid using standard Vim directory names like 'plugin'
" ADD NEW PLUGINS HERE
" Make sure you use single quotes
Plug 'junegunn/vim-slash'
" Initialize plugin system
" - Automatically executes `filetype plugin indent on` and `syntax enable`.
call plug#end()
