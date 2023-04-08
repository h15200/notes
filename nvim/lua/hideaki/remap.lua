vim.g.mapleader = " "

local km = vim.keymap 

km.set("n", "<leader>pv", vim.cmd.Ex)

-- add page center after up and down jumps
km.set("n","<C-u>", "<C-u>zz")
km.set("n","<C-d>" ,"<C-d>zz")

-- add page center after word search
km.set("n","n", "nzzzv")
km.set("n", "N", "Nzzzv")

-- left jump, right jump
km.set("n", "H", "0")
km.set("n", "L", "$")

-- option up, down in vscode
km.set("v", "J", ":m '>+1<CR>gv=gv")
km.set("v", "K", ":m '<-2<CR>gv=gv")

-- special print to keep current register
km.set("x", "<leader>p", "\", _dP")

-- system clipboard commands
km.set("n", "<leader>y", "\"+y")
km.set("v", "<leader>y", "\"+y")
km.set("n", "<leader>Y", "\"+Y")

km.set("n", "<leader>d", "\"_d")
km.set("v", "<leader>d", "\"_d")

-- prevent quitting by accident
km.set("n", "Q", "<nop>")
